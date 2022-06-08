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

use anyhow;
use cargo_metadata::MetadataCommand;
use risc0_zkvm_platform_sys::LINKER_SCRIPT;
use risc0_zkvm_sys::make_method_id_from_elf;
use serde::Deserialize;

const TARGET_JSON: &[u8] = include_bytes!("../riscv32im-unknown-none-elf.json");

#[derive(Debug, Deserialize)]
struct Risc0Metadata {
    methods: Vec<String>,
}

/// Build all RISC-V ELF binaries specified by risc0 `methods` metadata.
pub fn build_all() {
    let metadata = MetadataCommand::new().no_deps().exec().unwrap();
    for pkg in metadata.packages {
        if let Some(obj) = pkg.metadata.get("risc0") {
            let info: Risc0Metadata = serde_json::from_value(obj.clone()).unwrap();
            for method in info.methods {
                let manifest_path = Path::new(&pkg.manifest_path)
                    .parent()
                    .unwrap()
                    .join(method)
                    .join("Cargo.toml");
                eprintln!(
                    "Building methods for {} in {}",
                    pkg.name,
                    manifest_path.display()
                );
                let inner_metadata = MetadataCommand::new()
                    .manifest_path(&manifest_path)
                    .no_deps()
                    .exec()
                    .unwrap();
                build(
                    &manifest_path,
                    &inner_metadata.target_directory.as_std_path(),
                );
            }
        }
    }
}

/// Builds a crate for the RISC-V guest target.
///
/// * `manifest_path` - The manifest path of the crate containing binaries to be compiled for the RISC-V guest target.
/// * `target_dir` - The target directory where the resulting ELF binaries should be placed.
pub fn build(manifest_path: &Path, target_dir: &Path) {
    let target_path = target_dir.join("riscv32im-unknown-none-elf.json");
    fs::create_dir_all(target_dir).unwrap();
    fs::write(&target_path, TARGET_JSON).unwrap();

    let args = vec![
        "build",
        "--release",
        "--target",
        target_path.to_str().unwrap(),
        "-Z",
        "build-std=alloc,core",
        "--manifest-path",
        manifest_path.to_str().unwrap(),
        "--target-dir",
        target_dir.to_str().unwrap(),
    ];
    let status = Command::new(env!("CARGO")).args(args).status().unwrap();
    if !status.success() {
        std::process::exit(status.code().unwrap());
    }
}

/// Embeds methods built for RISC-V for use by host-side dependencies.
pub fn embed_methods() {
    let manifest_dir = env::var("CARGO_MANIFEST_DIR").unwrap();
    let manifest_path = Path::new(&manifest_dir).join("Cargo.toml");
    let metadata = MetadataCommand::new()
        .manifest_path(manifest_path)
        .no_deps()
        .exec()
        .unwrap();
    let pkg_name = env::var("CARGO_PKG_NAME").unwrap();
    let pkg = metadata
        .packages
        .iter()
        .find(|x| x.name == pkg_name)
        .unwrap();

    let obj = pkg.metadata.get("risc0").unwrap();
    let info: Risc0Metadata = serde_json::from_value(obj.clone()).unwrap();

    let out_dir = env::var_os("OUT_DIR").unwrap();
    let dest_path = Path::new(&out_dir).join("methods.rs");
    let mut file = File::create(&dest_path).unwrap();

    for rel_path in info.methods {
        let manifest_path = Path::new(&pkg.manifest_path)
            .parent()
            .unwrap()
            .join(rel_path)
            .join("Cargo.toml");

        let metadata = MetadataCommand::new()
            .manifest_path(&manifest_path)
            .no_deps()
            .exec()
            .unwrap();

        let pkg = metadata
            .packages
            .iter()
            .find(|x| x.manifest_path.as_std_path() == &manifest_path)
            .unwrap();

        for target in &pkg.targets {
            if target.kind.contains(&"bin".to_string()) {
                let method = target.name.clone();
                let elf_path = metadata
                    .target_directory
                    .as_std_path()
                    .join("riscv32im-unknown-none-elf")
                    .join("release")
                    .join(&method);
                if !elf_path.exists(){
                    eprintln!("RISC-V method file not found at: {}", elf_path.display());
                    eprintln!("Run method compiler before running this command.");
                    eprintln!("Try: `cargo run --bin risc0-build-methods`");
                    std::process::exit(-1);
                }
                let method_id = &elf_path
                    .to_str()
                    .ok_or(anyhow::Error::msg("empty elf path!"))
                    .and_then(make_method_id_from_elf)
                    .expect("Failed building MethodID!");
                file.write_all(&[
                    format!("pub const {}_PATH: &str = \"{}\";\n", method.to_uppercase(), elf_path.display()).as_bytes(),
                    format!("pub const {}_ID: &'static [u8; {}] = &", method.to_uppercase(), method_id.len()).as_bytes(),
                    format!("{:?}", method_id).as_bytes(),
                    format!(";\n").as_bytes(),
                ].concat()).expect("Failed writing methods file!");
                println!("cargo:rerun-if-changed={}", elf_path.display());
            }
        }
    }
}

/// Called inside the guest crate's build.rs to do special linking for the ZKVM
pub fn link() {
    if env::var("CARGO_CFG_TARGET_ARCH").unwrap() == "riscv32" {
        let out_dir = env::var_os("OUT_DIR").unwrap();
        let linker_script = Path::new(&out_dir).join("risc0.ld");
        fs::write(&linker_script, LINKER_SCRIPT).unwrap();
        println!("cargo:rustc-link-arg=-T{}", linker_script.to_str().unwrap());
    }
}
