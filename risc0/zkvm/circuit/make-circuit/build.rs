use std::{env, fs, path::Path, process::Command};

fn main() {
    // prevent recursion
    if env::var("MAKE_CIRCUIT").is_ok() {
        return;
    }

    let out_dir = env::var("OUT_DIR").unwrap();
    let inc_dir = Path::new(&out_dir);
    let out_dir = inc_dir.join("risc0").join("zkvm").join("circuit");
    let out_path = out_dir.join("step.cpp.inc");

    fs::create_dir_all(out_dir).unwrap();

    let args = vec![
        "run",
        "--profile",
        "bootstrap",
        "--bin",
        "make-circuit",
        out_path.to_str().unwrap(),
    ];

    let status = Command::new(env!("CARGO"))
        .args(args)
        .env("MAKE_CIRCUIT", "1")
        .status()
        .unwrap();
    if !status.success() {
        std::process::exit(status.code().unwrap());
    }

    println!("cargo:inc={}", inc_dir.to_str().unwrap());
}
