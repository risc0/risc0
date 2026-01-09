// SPDX-License-Identifier: BSD-3-Clause
// See Notices.txt for copyright information

fn main() {
    use std::env;
    use std::path::Path;

    // Use pre-built Bazel library (.a file)
    let manifest_dir = env::var("CARGO_MANIFEST_DIR").unwrap();
    let lib_path = Path::new(&manifest_dir).join("libsoftfloat.a");

    if !lib_path.exists() {
        panic!(
            "libsoftfloat.a not found at {}. Please build it with Bazel first.",
            lib_path.display()
        );
    }

    // Link against pre-built library
    let lib_dir = lib_path.parent().unwrap();
    let lib_name = "softfloat"; // Remove "lib" prefix and ".a" extension

    let target_os = std::env::var("CARGO_CFG_TARGET_OS").unwrap();

    if target_os == "zkvm" {
        println!("cargo:rustc-link-search=native={}", lib_dir.display());
        println!("cargo:rustc-link-lib=static={}", lib_name);
        println!("cargo:rerun-if-changed={}", lib_path.display());
    }
}
