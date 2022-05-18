// Copyright 2022 Risc0, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#![doc = include_str!("../README.md")]

use std::{
    env,
    fs::{self, File},
    io::Write,
    path::Path,
    process::Command,
};

use risc0_zkvm_platform_sys::LINKER_SCRIPT;
use risc0_zkvm_sys::MethodID;
use tempfile::tempdir;

const TARGET_JSON: &[u8] = include_bytes!("../riscv32im-unknown-none-elf.json");

fn build(path: &str) {
    let manifest_path = Path::new(path).join("Cargo.toml");
    let temp_dir = tempdir().unwrap();
    let target_path = temp_dir.path().join("riscv32im-unknown-none-elf.json");
    fs::write(&target_path, TARGET_JSON).unwrap();

    let out_dir = env::var("OUT_DIR").unwrap();
    let args = vec![
        "build",
        "--release",
        "--target",
        target_path.to_str().unwrap(),
        "-Z",
        "build-std=alloc,core",
        "--target-dir",
        &out_dir,
        "--manifest-path",
        manifest_path.to_str().unwrap()
    ];
    let status = Command::new(env!("CARGO")).args(args).status().unwrap();
    if !status.success() {
        std::process::exit(status.code().unwrap());
    }
}

fn generate_module(methods: &[&str]) {
    let out_dir = env::var_os("OUT_DIR").unwrap();
    let dest_path = Path::new(&out_dir).join("methods.rs");
    let mut file = File::create(&dest_path).unwrap();

    for method in methods {
        let elf_path = Path::new(&out_dir)
            .join("riscv32im-unknown-none-elf")
            .join("release")
            .join(method);
        let mut id_path = Path::new(&out_dir).join(method);
        id_path.set_extension("id");

        let method_id = MethodID::new(&elf_path.to_str().unwrap()).unwrap();
        method_id.write(&id_path.to_str().unwrap()).unwrap();

        let elf_path = elf_path.display();
        let id_path = id_path.display();
        let upper = method.to_uppercase();
        let content = format!(
            r##"
pub const {upper}_PATH: &str = r#"{elf_path}"#;
pub const {upper}_ID: &[u8] = include_bytes!(r#"{id_path}"#);
        "##
        );
        file.write_all(content.as_bytes()).unwrap();
    }
}

/// Build a crate for the guest, and packages up the methods in it for use by the host.
///
/// * `path` - The root of the crate holding the code to be compiled for the guest.
/// * `names` - The names of the methods to build, each method should be associated with a 'bin'.
pub fn methods(path: &str, names: &[&str]) {
    build(path);
    generate_module(names);
}

/// Called inside the guest crate's build.rs to do special linking for the ZKVM
pub fn link() {
    if env::var("CARGO_CFG_TARGET_ARCH").unwrap() == "riscv32" {
        let out_dir = env::var_os("OUT_DIR").unwrap();
        let linker_script = Path::new(&out_dir).join("risc0.ld");
        fs::write(&linker_script, LINKER_SCRIPT).unwrap();
        let linker_script = linker_script.to_str().unwrap();
        println!("cargo:rustc-link-arg=-T{linker_script}");
    }
}
