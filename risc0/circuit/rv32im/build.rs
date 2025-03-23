extern crate qapi_codegen;

use std::{env, path};

fn main() {
    let out_dir = path::Path::new(&env::var("OUT_DIR").unwrap()).join("qmp.rs");
//    let schema_dir = path::Path::new(&env::var_os("CARGO_MANIFEST_DIR").unwrap())
//        .join("schema")
//        .join("qapi");
    let schema_dir = "/home/nils/rzlocal/qemu/qapi";
    for inc in qapi_codegen::codegen(schema_dir, out_dir, "QmpCommand".into()).unwrap() {
        println!("rerun-if-changed={}", inc.display());
    }
}
