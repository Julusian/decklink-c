extern crate clang;
extern crate heck;
extern crate regex;

use crate::util::{write_byte, Context};
use std::collections::HashMap;
use std::fs::File;
use std::io::LineWriter;

mod class;
mod misc;
mod util;

fn main() {
    // A list of names to skip generation of, eg for special case handling
    let ignore_names = vec![
        "cdecklink_notification_subscribe",
        "cdecklink_notification_unsubscribe",
    ];

    // Acquire an instance of `Clang`
    let clang = clang::Clang::new().unwrap();

    // Create a new `Index`
    let index = clang::Index::new(&clang, false, true);

    // Parse a source file into a translation unit
    let tu: clang::TranslationUnit = index
        .parser("../interop/Linux/include/DeckLinkAPI.h")
        .arguments(&["-x", "c++", "-fparse-all-comments"])
        .parse()
        .unwrap();

    println!("starting");

    let file = File::create("../include/api.h").unwrap();
    let mut file = LineWriter::new(file);

    let file_c = File::create("../src/api.cpp").unwrap();
    let mut file_c = LineWriter::new(file_c);

    let file_types_c = File::create("../include/types.h").unwrap();
    let mut file_types_c = LineWriter::new(file_types_c);

    let file_types_cpp = File::create("../src/types.h").unwrap();
    let mut file_types_cpp = LineWriter::new(file_types_cpp);

    let callbacks_cpp = File::create("../src/callbacks.cpp").unwrap();
    let mut callbacks_cpp = LineWriter::new(callbacks_cpp);

    let callbacks_h = File::create("../src/callbacks.h").unwrap();
    let mut callbacks_h = LineWriter::new(callbacks_h);

    write_byte(&mut file, b"#ifndef DECKLINK_C_API_H\n");
    write_byte(&mut file, b"#define DECKLINK_C_API_H\n\n");

    write_byte(&mut file, b"#include \"common.h\"\n");
    write_byte(&mut file, b"#include \"types.h\"\n");
    //    write_byte(&mut file, b"#include \"util.h\"\n");
    write_byte(&mut file, b"\n");

    write_byte(&mut file_c, b"#include <atomic>\n");
    write_byte(&mut file_c, b"#include \"types.h\"\n");
    write_byte(&mut file_c, b"#include \"../include/api.h\"\n");
    write_byte(&mut file_c, b"#include \"callbacks.h\"\n");
    write_byte(&mut file_c, b"\n");

    write_byte(&mut file, b"#ifdef __cplusplus\nextern \"C\" {\n#endif\n\n");

    write_byte(&mut callbacks_h, b"#ifndef DECKLINK_C_CALLBACKS_H\n");
    write_byte(&mut callbacks_h, b"#define DECKLINK_C_CALLBACKS_H\n\n");

    write_byte(&mut callbacks_cpp, b"#include <atomic>\n");
    write_byte(&mut callbacks_cpp, b"#include \"types.h\"\n");
    write_byte(&mut callbacks_cpp, b"#include \"../include/api.h\"\n");
    write_byte(&mut callbacks_cpp, b"#include \"callbacks.h\"\n\n");

    let mut ctx = Context {
        type_alias: HashMap::new(),
        callback_params: HashMap::new(),
        ignore_names,
    };

    misc::generate_types_files(&tu, &mut ctx, &mut file_types_c, &mut file_types_cpp);

    misc::process_enum_typedefs(&tu, &mut ctx, &mut file);
    misc::process_enums(&tu, &mut ctx, &mut file);
    class::process_classes(
        &tu,
        &mut ctx,
        &mut file,
        &mut file_c,
        &mut callbacks_h,
        &mut callbacks_cpp,
    );

    misc::process_c_functions(&tu, &ctx, &mut file, &mut file_c);
    misc::process_query_interface(&tu, &ctx, &mut file, &mut file_c);

    write_byte(&mut file, b"#ifdef __cplusplus\n};\n#endif\n\n");

    write_byte(&mut file, b"\n#endif //DECKLINK_C_API_H\n");

    write_byte(&mut callbacks_h, b"\n#endif //DECKLINK_C_CALLBACKS_H\n");
}
