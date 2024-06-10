use std::{fs, process::Command};

use risc0_build::risc0_data;

fn main() {
    let toolchain_path = risc0_data().unwrap();
    let gcc_path = toolchain_path
        .join("cpp")
        .join("bin")
        .join("riscv32-unknown-elf-gcc");

    let guest_dir = fs::canonicalize(env!("CARGO_MANIFEST_DIR"))
        .unwrap()
        // Go back a directory from `./host`
        .parent()
        .unwrap()
        // Use guest directory.
        .join("guest");

    println!("cargo:rerun-if-changed={}", guest_dir.display());

    // Build static lib of platform to link against.
    Command::new("cargo")
        .args([
            "+risc0",
            "rustc",
            "-p",
            "zkvm-platform",
            "--target",
            "riscv32im-risc0-zkvm-elf",
            "--lib",
            "--crate-type",
            "staticlib",
            "--release",
        ])
        .arg("--target-dir")
        .arg(guest_dir.join("out").join("platform"))
        .status()
        .unwrap();

    // Build the C code using gcc
    Command::new(gcc_path)
        .arg("-nostartfiles")
        .arg(guest_dir.join("main.c"))
        .arg("-o")
        .arg(guest_dir.join("out").join("main"))
        .arg(format!(
            "-L{}",
            guest_dir
                .join("out")
                .join("platform")
                .join("riscv32im-risc0-zkvm-elf")
                .join("release")
                .display()
        ))
        .arg("-lzkvm_platform")
        .arg("-T")
        .arg(guest_dir.join("riscv32im-risc0-zkvm-elf.ld"))
        .status()
        .unwrap();
}
