extern crate clang;
extern crate heck;
extern crate regex;

use crate::util::{generate_class_prefix, trim_struct_name, write_byte, Context};
use heck::SnakeCase;
use std::collections::HashMap;
use std::fs::File;
use std::io::{LineWriter, Write};
use std::ops::Range;

mod misc;
mod util;

fn main() {
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

    let file = File::create("../include/decklink_c.h").unwrap();
    let mut file = LineWriter::new(file);

    let file_c = File::create("../src/decklink_c.cpp").unwrap();
    let mut file_c = LineWriter::new(file_c);

    let file_types_c = File::create("../include/types.h").unwrap();
    let mut file_types_c = LineWriter::new(file_types_c);

    let file_types_cpp = File::create("../src/types.h").unwrap();
    let mut file_types_cpp = LineWriter::new(file_types_cpp);

    write_byte(&mut file, b"#ifndef DECKLINK_C_API_H\n");
    write_byte(&mut file, b"#define DECKLINK_C_API_H\n\n");

    file.write(b"#include \"common.h\"\n").unwrap();
    file.write(b"#include \"types.h\"\n").unwrap();
    file.write(b"#include \"util.h\"\n").unwrap();
    file.write(b"\n").unwrap();

    file_c.write(b"#include <atomic>\n").unwrap();
    file_c.write(b"#include \"types.h\"\n").unwrap();
    file_c
        .write(b"#include \"../include/decklink_c.h\"\n")
        .unwrap();
    file_c.write(b"\n").unwrap();

    file.write(b"#ifdef __cplusplus\nextern \"C\" {\n#endif\n\n")
        .unwrap();

    let mut ctx = Context {
        type_alias: HashMap::new(),
        callback_params: HashMap::new(),
    };

    misc::generate_types_files(&tu, &mut ctx, &mut file_types_c, &mut file_types_cpp);

    misc::process_enum_typedefs(&tu, &mut ctx, &mut file);
    misc::process_enums(&tu, &mut ctx, &mut file);

    // Class methods
    let classes: Vec<clang::Entity> = tu
        .get_entity()
        .get_children()
        .into_iter()
        .filter(|e| e.get_kind() == clang::EntityKind::ClassDecl && e.get_children().len() > 0)
        .collect::<Vec<clang::Entity>>();

    for cl in classes {
        //        let type_ = cl.get_type().unwrap();
        //        println!("class: {:?}", cl.get_name().unwrap());

        let name = cl.get_name().unwrap();
        if name.starts_with("IDeckLink") {
            if let Some(prefix) = generate_class_prefix(&name) {
                let struct_name = format!("{}_t", prefix);

                //            file.write(format!("typedef void {};\n", struct_name).as_bytes()).unwrap();
                //                println!("{}", struct_name);

                if name.contains("Callback") {
                    println!("class: {:?}", cl.get_name().unwrap());

                    //callback types

                    let mut callbacks = Vec::new();

                    for func in cl.get_children() {
                        //                    println!("    child: {:?} (kind: {:?})", func.get_name().unwrap_or("?".to_string()), func.get_kind());

                        if func.get_kind() != clang::EntityKind::Method {
                            continue;
                        }

                        let name = func.get_name().unwrap();

                        let (args, _, _) = ctx.parse_args(&func, "void");
                        let ret_name = ctx.convert_type(&func.get_result_type().unwrap());

                        let func_str = format!(
                            "{} {}_{}({})",
                            ret_name,
                            prefix,
                            name.to_snake_case(),
                            args.join(", ")
                        );
                        //                        println!("callback: {}", func_str);
                        file.write(format!("typedef {};\n", func_str).as_bytes())
                            .unwrap();

                        callbacks.push(format!("{}_{}", prefix, name.to_snake_case()));
                    }

                    ctx.callback_params.insert(name.clone(), callbacks.clone());

                    let mut class_name = name.clone();
                    class_name = class_name.replace(|a| !char::is_alphanumeric(a), "");
                    let mut class_name2 = class_name.to_string();
                    class_name2.replace_range(Range { start: 0, end: 1 }, ""); // Trim I

                    file_c
                        .write(
                            format!("class {} final : public {} {{\n", class_name2, class_name)
                                .as_bytes(),
                        )
                        .unwrap();
                    file_c
                        .write(b"\tstd::atomic<int> ref_count_{0};\n")
                        .unwrap();
                    file_c.write(b"\tvoid *ctx_;\n").unwrap();

                    let mut cb_names = Vec::new();
                    let mut cb_names_and_types = Vec::new();
                    for i in 0..callbacks.len() {
                        let cb = &callbacks[i];

                        cb_names.push(format!("cb{}", i));
                        cb_names_and_types.push(format!("{} *cb{}", cb, i));
                        file_c
                            .write(format!("\t{} *cb{}_;\n", cb, i).as_bytes())
                            .unwrap();
                    }

                    file_c.write(b"\npublic:\n").unwrap();

                    file_c
                        .write(
                            format!(
                                "\t{} (void *ctx, {})\n",
                                class_name2,
                                cb_names_and_types.join(", ")
                            )
                            .as_bytes(),
                        )
                        .unwrap();

                    let setters = cb_names
                        .iter()
                        .map(|a| format!("{}_({})", a, a))
                        .collect::<Vec<String>>();
                    file_c
                        .write(format!("\t: ctx_(ctx), {} {{}}\n", setters.join(", ")).as_bytes())
                        .unwrap();

                    file_c.write(b"\n").unwrap();

                    file_c.write(b"\tHRESULT STDMETHODCALLTYPE QueryInterface(REFIID, LPVOID *) override { return E_NOINTERFACE; }\n").unwrap();
                    file_c.write(b"\tULONG STDMETHODCALLTYPE AddRef() override { return ++ref_count_; }\n").unwrap();
                    file_c.write(b"\tULONG STDMETHODCALLTYPE Release() override {\n\t\tif (--ref_count_ == 0) {\n\t\t\tdelete this;\n\t\t\treturn 0;\n\t\t}\n\t\treturn ref_count_;\n\t}\n").unwrap();
                    file_c.write(b"\n").unwrap();

                    let children = cl
                        .get_children()
                        .into_iter()
                        .filter(|c| c.get_kind() == clang::EntityKind::Method)
                        .collect::<Vec<clang::Entity>>();
                    for i in 0..children.len() {
                        let ch = &children[i];

                        let fake_ctx = Context {
                            type_alias: HashMap::new(),
                            callback_params: HashMap::new(),
                        };
                        let (mut args, mut arg_names, _) = fake_ctx.parse_args(&ch, "void");
                        let ret_name = ctx.convert_type(&ch.get_result_type().unwrap());

                        args.remove(0); // Drop ctx_ from the start

                        file_c
                            .write(
                                format!(
                                    "\t{} {}({}) override {{\n",
                                    ret_name,
                                    ch.get_name().unwrap(),
                                    args.join(", ")
                                )
                                .as_bytes(),
                            )
                            .unwrap();
                        file_c
                            .write(format!("\t\tif (cb{}_ != nullptr) {{\n", i).as_bytes())
                            .unwrap();

                        arg_names.insert(0, "ctx_".to_string());

                        file_c
                            .write(
                                format!("\t\t\treturn cb{}_({});\n", i, arg_names.join(", "))
                                    .as_bytes(),
                            )
                            .unwrap();

                        file_c.write(b"\t\t}\n").unwrap();
                        file_c.write(b"\t\treturn S_FALSE;\n").unwrap();

                        file_c.write(b"\t}\n\n").unwrap();
                    }

                    file_c.write(b"};\n\n").unwrap();

                    file.write(b"\n").unwrap();
                } else {
                    let bases = cl
                        .get_children()
                        .into_iter()
                        .filter(|c| c.get_kind() == clang::EntityKind::BaseSpecifier)
                        .collect::<Vec<clang::Entity>>();
                    if let Some(base) = bases.first() {
                        let base_type = base.get_type().unwrap();
                        //                    if base_type.get_display_name() == "IUnknown" {
                        //                        println!("IUn");
                        //                    }
                        if let Some(alias) = ctx.type_alias.get(&base_type.get_display_name()) {
                            let trimmed = trim_struct_name(alias);
                            //                            println!(" base = {} ({})", alias, trimmed);

                            // Cast to Base Class
                            let func_str = format!(
                                "{} *{}_to_{}({} *obj)",
                                alias, prefix, trimmed, struct_name
                            );
                            file.write(format!("{};\n", func_str).as_bytes()).unwrap();

                            file_c
                                .write(format!("{} {{\n", func_str).as_bytes())
                                .unwrap();
                            file_c.write(b"\treturn obj;\n").unwrap();
                            file_c.write(b"}\n\n").unwrap();
                        }
                    }

                    // Release and AddRef
                    {
                        let func_str =
                            format!("unsigned long {}_add_ref({} *obj)", prefix, struct_name);
                        file.write(format!("{};\n", func_str).as_bytes()).unwrap();

                        file_c
                            .write(format!("{} {{\n", func_str).as_bytes())
                            .unwrap();
                        file_c.write(b"\treturn obj->AddRef();\n").unwrap();
                        file_c.write(b"}\n\n").unwrap();
                    }
                    {
                        let func_str =
                            format!("unsigned long {}_release({} *obj)", prefix, struct_name);
                        file.write(format!("{};\n", func_str).as_bytes()).unwrap();

                        file_c
                            .write(format!("{} {{\n", func_str).as_bytes())
                            .unwrap();
                        file_c.write(b"\treturn obj->Release();\n").unwrap();
                        file_c.write(b"}\n\n").unwrap();
                    }

                    // Methods
                    for func in cl.get_children() {
                        //                    println!("    child: {:?} (kind: {:?})", func.get_name().unwrap_or("?".to_string()), func.get_kind());

                        if func.get_kind() != clang::EntityKind::Method {
                            continue;
                        }

                        let name = func.get_name().unwrap();
                        //                    println!("    field: {:?} (offset: {} bits)", name, 0);

                        let (args, arg_names, callback_type) = ctx.parse_args(&func, &struct_name);
                        let ret_name = ctx.convert_type(&func.get_result_type().unwrap());

                        let func_str = format!(
                            "{} {}_{}({})",
                            ret_name,
                            prefix,
                            name.to_snake_case(),
                            args.join(", ")
                        );
                        file.write(format!("{};\n", func_str).as_bytes()).unwrap();

                        file_c
                            .write(format!("{} {{\n", func_str).as_bytes())
                            .unwrap();

                        if let Some(cb) = &callback_type {
                            file_c
                                .write(format!("\t{} handler = nullptr;\n", cb).as_bytes())
                                .unwrap();

                            let params = arg_names
                                .iter()
                                .filter(|a| a.starts_with("cb"))
                                .map(|a| format!("{} != nullptr", a))
                                .collect::<Vec<String>>();
                            file_c
                                .write(format!("\tif ({}) {{\n", params.join(" && ")).as_bytes())
                                .unwrap();

                            let mut class_name = cb.clone();
                            class_name.replace_range(Range { start: 0, end: 1 }, ""); // Trim I
                            class_name = class_name.replace(|a| !char::is_alphanumeric(a), "");
                            let params2 = arg_names
                                .iter()
                                .filter(|a| a.starts_with("cb"))
                                .map(|a| a.clone())
                                .collect::<Vec<String>>();
                            file_c
                                .write(
                                    format!(
                                        "\t\thandler = new {}(ctx, {});\n",
                                        class_name,
                                        params2.join(", ")
                                    )
                                    .as_bytes(),
                                )
                                .unwrap();

                            file_c.write(b"\t}\n").unwrap();

                            let other_params = arg_names
                                .iter()
                                .filter(|a| !a.starts_with("cb"))
                                .map(|a| {
                                    if a == "ctx" {
                                        "handler".to_string()
                                    } else {
                                        a.clone()
                                    }
                                })
                                .collect::<Vec<String>>();
                            file_c
                                .write(
                                    format!(
                                        "\treturn obj->{}({});\n",
                                        name,
                                        other_params.join(", ")
                                    )
                                    .as_bytes(),
                                )
                                .unwrap();
                        } else {
                            file_c
                                .write(
                                    format!("\treturn obj->{}({});\n", name, arg_names.join(", "))
                                        .as_bytes(),
                                )
                                .unwrap();
                        }

                        file_c.write(b"}\n\n").unwrap();
                    }

                    file.write(b"\n").unwrap();
                    file_c.write(b"\n").unwrap();
                }
            }
        }
    }

    misc::process_c_functions(&tu, &ctx, &mut file, &mut file_c);
    misc::process_query_interface(&tu, &ctx, &mut file, &mut file_c);

    file.write(b"#ifdef __cplusplus\n};\n#endif\n\n").unwrap();

    write_byte(&mut file, b"\n#endif //DECKLINK_C_API_H\n");
}
