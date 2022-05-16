use std::{env, fs, path::Path};

use risc0_zkvm_circuit_sys::make_circuit;

fn main() {
    let out_dir = env::var("OUT_DIR").unwrap();
    let inc_dir = Path::new(&out_dir);
    let out_dir = inc_dir.join("risc0").join("zkvm").join("circuit");
    let out_path = out_dir.join("step.cpp.inc");

    fs::create_dir_all(out_dir).unwrap();

    make_circuit(&out_path.to_str().unwrap()).unwrap();

    println!("cargo:inc={}", inc_dir.to_str().unwrap());
}
