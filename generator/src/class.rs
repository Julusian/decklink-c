use crate::heck::SnakeCase;
use crate::util::{generate_class_prefix, trim_struct_name, write_byte, write_str, Context};
use std::collections::HashMap;
use std::fs::File;
use std::io::LineWriter;
use std::ops::Range;

pub fn process_classes(
    tu: &clang::TranslationUnit,
    ctx: &mut Context,
    file: &mut LineWriter<File>,
    file_c: &mut LineWriter<File>,
) {
    let classes: Vec<clang::Entity> = tu
        .get_entity()
        .get_children()
        .into_iter()
        .filter(|e| e.get_kind() == clang::EntityKind::ClassDecl && !e.get_children().is_empty())
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
                    // println!("class: {:?}", cl.get_name().unwrap());

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
                        write_str(file, format!("typedef {};\n", func_str));

                        callbacks.push(format!("{}_{}", prefix, name.to_snake_case()));
                    }

                    ctx.callback_params.insert(name.clone(), callbacks.clone());

                    let mut class_name = name.clone();
                    class_name = class_name.replace(|a| !char::is_alphanumeric(a), "");
                    let mut class_name2 = class_name.to_string();
                    class_name2.replace_range(Range { start: 0, end: 1 }, ""); // Trim I

                    write_str(
                        file_c,
                        format!("class {} final : public {} {{\n", class_name2, class_name),
                    );
                    write_byte(file_c, b"\tstd::atomic<int> ref_count_{0};\n");
                    write_byte(file_c, b"\tvoid *ctx_;\n");

                    let mut cb_names = Vec::new();
                    let mut cb_names_and_types = Vec::new();

                    for (i, cb) in callbacks.iter().enumerate() {
                        cb_names.push(format!("cb{}", i));
                        cb_names_and_types.push(format!("{} *cb{}", cb, i));
                        write_str(file_c, format!("\t{} *cb{}_;\n", cb, i));
                    }

                    write_byte(file_c, b"\npublic:\n");

                    write_str(
                        file_c,
                        format!(
                            "\t{} (void *ctx, {})\n",
                            class_name2,
                            cb_names_and_types.join(", ")
                        ),
                    );

                    let setters = cb_names
                        .iter()
                        .map(|a| format!("{}_({})", a, a))
                        .collect::<Vec<String>>();
                    write_str(
                        file_c,
                        format!("\t: ctx_(ctx), {} {{}}\n", setters.join(", ")),
                    );

                    write_byte(file_c, b"\n");

                    write_byte(file_c,b"\tHRESULT STDMETHODCALLTYPE QueryInterface(REFIID, LPVOID *) override { return E_NOINTERFACE; }\n");
                    write_byte(
                        file_c,
                        b"\tULONG STDMETHODCALLTYPE AddRef() override { return ++ref_count_; }\n",
                    );
                    write_byte(file_c,b"\tULONG STDMETHODCALLTYPE Release() override {\n\t\tif (--ref_count_ == 0) {\n\t\t\tdelete this;\n\t\t\treturn 0;\n\t\t}\n\t\treturn ref_count_;\n\t}\n");
                    write_byte(file_c, b"\n");

                    let children = cl
                        .get_children()
                        .into_iter()
                        .filter(|c| c.get_kind() == clang::EntityKind::Method)
                        .collect::<Vec<clang::Entity>>();

                    let fake_ctx = Context {
                        type_alias: HashMap::new(),
                        callback_params: HashMap::new(),
                    };

                    for (i, ch) in children.iter().enumerate() {
                        let (mut args, mut arg_names, _) = fake_ctx.parse_args(&ch, "void");
                        let ret_name = ctx.convert_type(&ch.get_result_type().unwrap());

                        args.remove(0); // Drop ctx_ from the start

                        write_str(
                            file_c,
                            format!(
                                "\t{} {}({}) override {{\n",
                                ret_name,
                                ch.get_name().unwrap(),
                                args.join(", ")
                            ),
                        );
                        write_str(file_c, format!("\t\tif (cb{}_ != nullptr) {{\n", i));

                        arg_names.insert(0, "ctx_".to_string());

                        write_str(
                            file_c,
                            format!("\t\t\treturn cb{}_({});\n", i, arg_names.join(", ")),
                        );

                        write_byte(file_c, b"\t\t}\n");
                        write_byte(file_c, b"\t\treturn S_FALSE;\n");

                        write_byte(file_c, b"\t}\n\n");
                    }

                    write_byte(file_c, b"};\n\n");

                    write_byte(file, b"\n");
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
                            write_str(file, format!("{};\n", func_str));

                            write_str(file_c, format!("{} {{\n", func_str));
                            write_byte(file_c, b"\treturn obj;\n");
                            write_byte(file_c, b"}\n\n");
                        }
                    }

                    // Release and AddRef
                    {
                        let func_str =
                            format!("unsigned long {}_add_ref({} *obj)", prefix, struct_name);
                        write_str(file, format!("{};\n", func_str));

                        write_str(file_c, format!("{} {{\n", func_str));
                        write_byte(file_c, b"\treturn obj->AddRef();\n");
                        write_byte(file_c, b"}\n\n");
                    }
                    {
                        let func_str =
                            format!("unsigned long {}_release({} *obj)", prefix, struct_name);
                        write_str(file, format!("{};\n", func_str));

                        write_str(file_c, format!("{} {{\n", func_str));
                        write_byte(file_c, b"\treturn obj->Release();\n");
                        write_byte(file_c, b"}\n\n");
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
                        write_str(file, format!("{};\n", func_str));

                        write_str(file_c, format!("{} {{\n", func_str));

                        if let Some(cb) = &callback_type {
                            write_str(file_c, format!("\t{} handler = nullptr;\n", cb));

                            let params = arg_names
                                .iter()
                                .filter(|a| a.starts_with("cb"))
                                .map(|a| format!("{} != nullptr", a))
                                .collect::<Vec<String>>();
                            write_str(file_c, format!("\tif ({}) {{\n", params.join(" && ")));

                            let mut class_name = cb.clone();
                            class_name.replace_range(Range { start: 0, end: 1 }, ""); // Trim I
                            class_name = class_name.replace(|a| !char::is_alphanumeric(a), "");
                            let params2 = arg_names
                                .iter()
                                .filter(|a| a.starts_with("cb"))
                                .cloned()
                                .collect::<Vec<String>>();
                            write_str(
                                file_c,
                                format!(
                                    "\t\thandler = new {}(ctx, {});\n",
                                    class_name,
                                    params2.join(", ")
                                ),
                            );

                            write_byte(file_c, b"\t}\n");

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
                            write_str(
                                file_c,
                                format!("\treturn obj->{}({});\n", name, other_params.join(", ")),
                            );
                        } else {
                            write_str(
                                file_c,
                                format!("\treturn obj->{}({});\n", name, arg_names.join(", ")),
                            );
                        }

                        write_byte(file_c, b"}\n\n");
                    }

                    write_byte(file, b"\n");
                    write_byte(file_c, b"\n");
                }
            }
        }
    }
}
