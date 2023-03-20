use crate::util::{generate_class_prefix, trim_struct_name, write_byte, write_str, Context};
use heck::ToSnakeCase;
use regex::Regex;
use std::fs::File;
use std::io::LineWriter;
use std::ops::Range;

pub fn generate_types_files(
    tu: &clang::TranslationUnit,
    ctx: &mut Context,
    file_c: &mut LineWriter<File>,
    file_cpp: &mut LineWriter<File>,
) {
    write_byte(file_c, b"#ifndef DECKLINK_C_TYPES_H\n");
    write_byte(file_c, b"#define DECKLINK_C_TYPES_H\n\n");

    // write_byte(file_cpp, b"#ifndef DECKLINK_C_TYPES_H\n");
    write_byte(file_cpp, b"#define DECKLINK_C_TYPES_H\n\n");
    write_byte(
        file_cpp,
        b"#include \"../interop/Linux/include/DeckLinkAPI.h\"\n\n",
    );

    let class_names: Vec<clang::Entity> = tu
        .get_entity()
        .get_children()
        .into_iter()
        .filter(|e| e.get_kind() == clang::EntityKind::ClassDecl && e.get_children().is_empty())
        .collect::<Vec<clang::Entity>>();

    for cl in class_names {
        let name = cl.get_name().unwrap();
        if name.contains("Callback") {
            continue;
        } else if name.starts_with("IDeckLink") {
            if let Some(prefix) = generate_class_prefix(&name) {
                let struct_name = format!("{}_t", prefix);

                write_str(file_c, format!("typedef void {};\n", struct_name));
                write_str(file_cpp, format!("typedef {} {};\n", name, struct_name));
                ctx.type_alias.insert(name, struct_name);
            }
        }
    }

    write_byte(file_c, b"\n#endif //DECKLINK_C_TYPES_H\n");
    // write_byte(file_cpp, b"\n#endif //DECKLINK_C_TYPES_H\n");
}

pub fn process_enums(tu: &clang::TranslationUnit, ctx: &mut Context, file: &mut LineWriter<File>) {
    let enums: Vec<clang::Entity> = tu
        .get_entity()
        .get_children()
        .into_iter()
        .filter(|e| e.get_kind() == clang::EntityKind::EnumDecl)
        .collect::<Vec<clang::Entity>>();

    for e in enums {
        let name = e.get_name().unwrap();

        let mut new_name = name.clone();
        if new_name.starts_with("_BMDDeckLink") {
            new_name.replace_range(Range { start: 0, end: 12 }, "_Decklink");
        } else if new_name.starts_with("_BMD") {
            new_name.replace_range(Range { start: 0, end: 4 }, "_Decklink");
        }

        write_str(file, format!("enum {} {{\n", new_name));
        ctx.type_alias.insert(name.clone(), new_name.clone());

        for val in e.get_children() {
            let mut name = val.get_name().unwrap();
            if name.starts_with("bmdDeckLink") {
                name.replace_range(Range { start: 0, end: 11 }, "decklink");
            } else if name.starts_with("bmd") {
                name.replace_range(Range { start: 0, end: 3 }, "decklink");
            } else if name.starts_with("BMDDeckLink") {
                name.replace_range(Range { start: 0, end: 11 }, "decklink");
            } else if name.starts_with("BMD") {
                name.replace_range(Range { start: 0, end: 3 }, "decklink");
            }

            let val = val.get_enum_constant_value().unwrap();
            write_str(file, format!("\t{} = {},\n", name, val.1));
        }

        write_byte(file, b"};\n\n");
    }

    write_byte(file, b"\n");
}

pub fn process_enum_typedefs(
    tu: &clang::TranslationUnit,
    ctx: &mut Context,
    file: &mut LineWriter<File>,
) {
    let typedefs: Vec<clang::Entity> = tu
        .get_entity()
        .get_children()
        .into_iter()
        .filter(|e| e.get_kind() == clang::EntityKind::TypedefDecl)
        .collect::<Vec<clang::Entity>>();

    for t in typedefs {
        let n = t.get_name().unwrap();
        let v = t.get_typedef_underlying_type().unwrap().get_display_name();

        let mut n2 = n.clone();
        if n2.starts_with("BMDDeckLink") {
            n2.replace_range(Range { start: 0, end: 11 }, "Decklink");
        } else if n2.starts_with("BMD") {
            n2.replace_range(Range { start: 0, end: 3 }, "Decklink");
        } else {
            continue;
        }

        // println!("type: {} = {}", n, v);
        write_str(file, format!("typedef {} {};\n", v, n2));

        ctx.type_alias.insert(n, n2);
    }

    write_byte(file, b"\n");
}

pub fn process_query_interface(
    tu: &clang::TranslationUnit,
    ctx: &Context,
    file: &mut LineWriter<File>,
    file_c: &mut LineWriter<File>,
) {
    // Parse the QueryInterface conversions stated in comments
    let re = Regex::new(r"IDeckLink(\w+) (.*) QueryInterface(.*) IDeck(\w+)").unwrap();
    let src_tokens = tu.get_entity().get_range().unwrap().tokenize();
    for token in src_tokens {
        if token.get_kind() == clang::token::TokenKind::Comment {
            let raw_str = token.get_spelling();
            for cap in re.captures_iter(&raw_str) {
                let src_name = format!("IDeck{}", &cap[4]);
                let dst_name = format!("IDeckLink{}", &cap[1]);
                // println!("IDeckLink{} from IDeck{}", &cap[1], &cap[4]);

                if let Some(new_src_name) = ctx.type_alias.get(&src_name) {
                    if let Some(new_dst_name) = ctx.type_alias.get(&dst_name) {
                        let trimmed_src = trim_struct_name(new_src_name);
                        let trimmed_dst = trim_struct_name(new_dst_name);

                        // Cast to Base Class
                        let func_str = format!(
                            "HRESULT cdecklink_{}_query_{}({} *obj, {} **dst)",
                            trimmed_src, trimmed_dst, new_src_name, new_dst_name
                        );
                        write_str(file, format!("{};\n", func_str));

                        write_str(file_c, format!("{} {{\n", func_str));
                        write_str(file_c, format!("\treturn obj->QueryInterface(IID_{}, reinterpret_cast<void**>(dst));\n", dst_name));
                        write_byte(file_c, b"}\n\n");
                    }
                }
            }
        }
    }
}

pub fn process_c_functions(
    tu: &clang::TranslationUnit,
    ctx: &Context,
    file: &mut LineWriter<File>,
    file_c: &mut LineWriter<File>,
) {
    let funcs: Vec<clang::Entity> = tu
        .get_entity()
        .get_children()
        .into_iter()
        .filter(|e| e.get_kind() == clang::EntityKind::UnexposedDecl && e.get_name().is_none())
        .collect::<Vec<clang::Entity>>();

    for t in funcs {
        for t in t.get_children() {
            let n = t.get_name().unwrap();
            if n.starts_with("Create") {
                // println!("func {} {:?}", n, t.get_kind());

                let ret_name = ctx.convert_type(&t.get_result_type().unwrap());

                let mut snaked = n.to_snake_case();
                snaked = snaked.replace("deck_link", "decklink");

                let func_str = format!("{} cdecklink_{}()", ret_name, snaked);
                write_str(file, format!("{};\n", func_str));

                write_str(file_c, format!("{} {{\n", func_str));
                write_str(file_c, format!("\treturn {}();\n", n));
                write_byte(file_c, b"}\n\n");
            }
        }
    }
}
