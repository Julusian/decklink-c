use crate::heck::SnakeCase;
use std::collections::HashMap;
use std::fs::File;
use std::io::{LineWriter, Write};
use std::ops::Range;

pub fn write_str(writer: &mut LineWriter<File>, s: String) {
    writer.write(s.as_bytes()).unwrap();
}

pub fn write_byte(writer: &mut LineWriter<File>, b: &[u8]) {
    writer.write(b).unwrap();
}

pub struct Context {
    pub type_alias: HashMap<String, String>,
    pub callback_params: HashMap<String, Vec<String>>,
}
impl Context {
    pub fn parse_args(
        &self,
        func: &clang::Entity,
        struct_name: &str,
    ) -> (Vec<String>, Vec<String>, Option<String>) {
        let mut args = Vec::new();
        args.push(format!("{} *obj", struct_name));
        let mut arg_names = Vec::new();

        let mut callback_type = None;

        for a in func.get_arguments().unwrap() {
            println!("{}", a.get_type().unwrap().get_display_name());
            if let Some(k) = self.get_callback_params(&a.get_type().unwrap().get_display_name()) {
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
                let type_name = self.convert_type(&a.get_type().unwrap());

                args.push(format!("{} {}", type_name, a.get_display_name().unwrap()));
                arg_names.push(a.get_display_name().unwrap());
            }
        }

        (args, arg_names, callback_type)
    }

    pub fn get_callback_params(&self, name1: &str) -> Option<&Vec<String>> {
        let basic_name = name1.to_string().replace(|a| !char::is_alphanumeric(a), "");
        self.callback_params.get(&basic_name)
    }

    pub fn convert_name(&self, name1: &str) -> Option<String> {
        let name = name1.to_string();
        let basic_name = name.replace(|a| !char::is_alphanumeric(a), "");
        if let Some(a) = self.type_alias.get(&basic_name) {
            Some(name.replace(&basic_name, a))
        } else {
            None
        }
    }

    pub fn convert_type(&self, type_: &clang::Type) -> String {
        let name = type_.get_display_name();
        self.convert_name(&name).unwrap_or(name)
    }
}

pub fn generate_class_prefix(name: &str) -> Option<String> {
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

pub fn trim_struct_name(name: &str) -> String {
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
