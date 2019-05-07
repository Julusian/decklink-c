extern crate clang;
extern crate heck;
extern crate regex;

use heck::SnakeCase;
use regex::Regex;
use std::collections::HashMap;
use std::fs::File;
use std::io::{LineWriter, Write};
use std::ops::Range;

fn write_str(writer: &mut LineWriter<File>, s: String) {
    writer.write(s.as_bytes()).unwrap();
}

fn write_byte(writer: &mut LineWriter<File>, b: &[u8]) {
    writer.write(b).unwrap();
}

fn generate_types_files(
    tu: &clang::TranslationUnit,
    type_map: &mut HashMap<String, String>,
    file_c: &mut LineWriter<File>,
    file_cpp: &mut LineWriter<File>,
) {
    write_byte(file_c, b"#ifndef DECKLINK_C_TYPES_H\n");
    write_byte(file_c, b"#define DECKLINK_C_TYPES_H\n\n");

    //    write_byte(file_cpp, b"#ifndef DECKLINK_C_TYPES_H\n");
    write_byte(file_cpp, b"#define DECKLINK_C_TYPES_H\n\n");
    write_byte(
        file_cpp,
        b"#include \"../interop/Linux/include/DeckLinkAPI.h\"\n\n",
    );

    let class_names: Vec<clang::Entity> = tu
        .get_entity()
        .get_children()
        .into_iter()
        .filter(|e| e.get_kind() == clang::EntityKind::ClassDecl && e.get_children().len() == 0)
        .collect::<Vec<clang::Entity>>();

    for cl in class_names {
        let name = cl.get_name().unwrap();
        if name.starts_with("IDeckLink") {
            if let Some(prefix) = generate_class_prefix(&name) {
                let struct_name = format!("{}_t", prefix);

                write_str(file_c, format!("typedef void {};\n", struct_name));
                write_str(file_cpp, format!("typedef {} {};\n", name, struct_name));
                type_map.insert(name, struct_name);
            }
        }
    }

    write_byte(file_c, b"\n#endif //DECKLINK_C_TYPES_H\n");
    //    write_byte(file_cpp, b"\n#endif //DECKLINK_C_TYPES_H\n");
}

fn generate_class_prefix(name: &str) -> Option<String> {
    if name.starts_with("IDeckLink") {
        let mut name2 = name.to_string();
        name2.replace_range(Range { start: 0, end: 9 }, "");
        if name2.len() == 0 {
            name2 = "device".to_string();
        }

        let prefix = format!("cdecklink_{}", name2.to_snake_case());

        Some(prefix)
    } else {
        None
    }
}

fn trim_struct_name(name: &str) -> String {
    let mut trimmed = name.to_string();
    trimmed.replace_range(Range { start: 0, end: 10 }, "");
    trimmed.replace_range(
        Range {
            start: trimmed.len() - 2,
            end: trimmed.len(),
        },
        "",
    );
    trimmed
}

fn parse_args(
    type_alias: &HashMap<String, String>,
    callback_params: &HashMap<String, Vec<String>>,
    func: &clang::Entity,
    struct_name: &str,
) -> (Vec<String>, Vec<String>, Option<String>) {
    let mut args = Vec::new();
    args.push(format!("{} *obj", struct_name));
    let mut arg_names = Vec::new();

    let mut callback_type = None;

    for a in func.get_arguments().unwrap() {
        println!("{}", a.get_type().unwrap().get_display_name());
        if let Some(k) = convert_name2(&callback_params, &a.get_type().unwrap().get_display_name())
        {
            args.push("void *ctx".to_string());
            arg_names.push("ctx".to_string());

            let mut i = 0;
            for j in k {
                args.push(format!("{}* cb{}", j, i));
                arg_names.push(format!("cb{}", i));
                i += 1;
            }
            callback_type = Some(a.get_type().unwrap().get_display_name());
        } else {
            let type_name = convert_type(type_alias, &a.get_type().unwrap());

            args.push(format!("{} {}", type_name, a.get_display_name().unwrap()));
            arg_names.push(a.get_display_name().unwrap());
        }
    }

    (args, arg_names, callback_type)
}

fn convert_name2<'a, T>(type_alias: &'a HashMap<String, T>, name1: &str) -> Option<&'a T> {
    let basic_name = name1.to_string().replace(|a| !char::is_alphanumeric(a), "");
    type_alias.get(&basic_name)
}

fn convert_name(type_alias: &HashMap<String, String>, name1: &str) -> Option<String> {
    let name = name1.to_string();
    let basic_name = name.replace(|a| !char::is_alphanumeric(a), "");
    if let Some(a) = type_alias.get(&basic_name) {
        Some(name.replace(&basic_name, a))
    } else {
        None
    }
}

fn convert_type(type_alias: &HashMap<String, String>, type_: &clang::Type) -> String {
    let name = type_.get_display_name();
    convert_name(type_alias, &name).unwrap_or(name)
}

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

    let mut type_alias = HashMap::new();
    let mut callback_params = HashMap::new();

    generate_types_files(&tu, &mut type_alias, &mut file_types_c, &mut file_types_cpp);

    let typedefs: Vec<clang::Entity> = tu
        .get_entity()
        .get_children()
        .into_iter()
        .filter(|e| e.get_kind() == clang::EntityKind::TypedefDecl)
        .collect::<Vec<clang::Entity>>();

    for t in typedefs {
        let n = t.get_name().unwrap();
        let mut n2 = n.clone();
        let v = t.get_typedef_underlying_type().unwrap().get_display_name();
        if n2.starts_with("BMDDeckLink") {
            n2.replace_range(Range { start: 0, end: 11 }, "Decklink");
            println!("type: {} = {}", n, v);
            file.write(format!("typedef {} {};\n", v, n2).as_bytes())
                .unwrap();

            type_alias.insert(n, n2);
        } else if n2.starts_with("BMD") {
            n2.replace_range(Range { start: 0, end: 3 }, "Decklink");
            println!("type: {} = {}", n, v);
            file.write(format!("typedef {} {};\n", v, n2).as_bytes())
                .unwrap();

            type_alias.insert(n, n2);
        }
    }

    file.write(b"\n").unwrap();

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

        file.write(format!("enum {} {{\n", new_name).as_bytes())
            .unwrap();
        type_alias.insert(name.clone(), new_name.clone());

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
            file.write(format!("\t{} = {},\n", name, val.1).as_bytes())
                .unwrap();
        }

        file.write(b"};\n\n").unwrap();
    }

    file.write(b"\n").unwrap();

    // Class methods
    let classes: Vec<clang::Entity> = tu
        .get_entity()
        .get_children()
        .into_iter()
        .filter(|e| e.get_kind() == clang::EntityKind::ClassDecl && e.get_children().len() > 0)
        .collect::<Vec<clang::Entity>>();

    for cl in classes {
        let type_ = cl.get_type().unwrap();
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

                        let (args, _, _) = parse_args(&type_alias, &callback_params, &func, "void");
                        let ret_name = convert_type(&type_alias, &func.get_result_type().unwrap());

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

                    callback_params.insert(name.clone(), callbacks.clone());

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

                        let (mut args, mut arg_names, _) =
                            parse_args(&HashMap::new(), &HashMap::new(), &ch, "void");
                        let ret_name = convert_type(&type_alias, &ch.get_result_type().unwrap());

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
                        if let Some(alias) = type_alias.get(&base_type.get_display_name()) {
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

                        let (args, arg_names, callback_type) =
                            parse_args(&type_alias, &callback_params, &func, &struct_name);
                        let ret_name = convert_type(&type_alias, &func.get_result_type().unwrap());

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
                println!("func {} {:?}", n, t.get_kind());

                let ret_name = convert_type(&type_alias, &t.get_result_type().unwrap());

                let mut snaked = n.to_snake_case();
                snaked = snaked.replace("deck_link", "decklink");

                let func_str = format!("{} cdecklink_{}()", ret_name, snaked);
                file.write(format!("{};\n", func_str).as_bytes()).unwrap();

                file_c
                    .write(format!("{} {{\n", func_str).as_bytes())
                    .unwrap();
                file_c
                    .write(format!("\treturn {}();\n", n).as_bytes())
                    .unwrap();
                file_c.write(b"}\n\n").unwrap();
            }
        }
    }

    // Parse the QueryInterface conversions stated in comments
    let re = Regex::new(r"IDeckLink(\w+) (.*) QueryInterface(.*) IDeck(\w+)").unwrap();
    let src_tokens = tu.get_entity().get_range().unwrap().tokenize();
    for token in src_tokens {
        if token.get_kind() == clang::token::TokenKind::Comment {
            let raw_str = token.get_spelling();
            for cap in re.captures_iter(&raw_str) {
                let src_name = format!("IDeck{}", &cap[4]);
                let dst_name = format!("IDeckLink{}", &cap[1]);
                //                println!("IDeckLink{} from IDeck{}", &cap[1], &cap[4]);

                if let Some(new_src_name) = type_alias.get(&src_name) {
                    if let Some(new_dst_name) = type_alias.get(&dst_name) {
                        let trimmed_src = trim_struct_name(new_src_name);
                        let trimmed_dst = trim_struct_name(new_dst_name);

                        // Cast to Base Class
                        let func_str = format!(
                            "HRESULT cdecklink_{}_query_{}({} *obj, {} **dst)",
                            trimmed_src, trimmed_dst, new_src_name, new_dst_name
                        );
                        file.write(format!("{};\n", func_str).as_bytes()).unwrap();

                        file_c
                            .write(format!("{} {{\n", func_str).as_bytes())
                            .unwrap();
                        file_c.write(format!("\treturn obj->QueryInterface(IID_{}, reinterpret_cast<void**>(dst));\n", dst_name).as_bytes()).unwrap();
                        file_c.write(b"}\n\n").unwrap();
                    }
                }
            }
        }
    }

    file.write(b"#ifdef __cplusplus\n};\n#endif\n\n").unwrap();

    write_byte(&mut file, b"\n#endif //DECKLINK_C_API_H\n");
}
