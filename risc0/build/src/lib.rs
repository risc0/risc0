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

#![deny(missing_docs)]
#![doc = include_str!("../README.md")]

use std::{
    env,
    fs::{self, File},
    io::Write,
    path::{Path, PathBuf},
    process::Command,
};

use cargo_metadata::{MetadataCommand, Package};
use risc0_zkvm_platform_sys::LINKER_SCRIPT;
use risc0_zkvm_sys::{make_method_id_from_elf, MethodId, METHOD_ID_LEN};
use serde::Deserialize;
use sha2::{Digest, Sha256};

#[derive(Debug, Deserialize)]
struct Risc0Metadata {
    methods: Vec<String>,
}

impl Risc0Metadata {
    fn from_package(pkg: &Package) -> Option<Risc0Metadata> {
        let obj = pkg.metadata.get("risc0").unwrap();
        serde_json::from_value(obj.clone()).unwrap()
    }
}

#[derive(Debug)]
struct Risc0Method {
    name: String,
    elf_path: PathBuf,
    cache_dir: PathBuf, // It's a bit questionable if this belongs here
}

impl Risc0Method {
    fn make_method_id(&self) -> MethodId {
        if !self.elf_path.exists() {
            eprintln!(
                "RISC-V method was not found at: {:?}",
                self.elf_path.to_str().unwrap()
            );
            std::process::exit(-1);
        }

        // Method ID calculation is slow, so only recalculate it if we
        // actually get a different ELF file.
        let method_id_cache_path = std::fs::read(&self.elf_path)
            .map(|content| Sha256::new().chain_update(content).finalize())
            .map(|vec| vec.iter().map(|byte| format!("{:02x}", byte)).collect())
            .map(|hash: String| self.cache_dir.join(hash))
            .map(|path| path.with_extension("cache"))
            .unwrap();

        println!("hash iis {}", method_id_cache_path.display());

        let cached_method_id = Ok(&method_id_cache_path)
            .and_then(std::fs::read)
            .map(|vec| <MethodId>::try_from(vec).unwrap());

        match cached_method_id {
            Ok(method_id) => method_id,
            Err(_) => {
                println!("Computing method_id for {}", self.name);
                let method_id = make_method_id_from_elf(&self.elf_path.to_str().unwrap()).unwrap();
                std::fs::write(method_id_cache_path, method_id).unwrap();
                method_id
            }
        }
    }

    fn rust_def(&self) -> String {
        let elf_path = self.elf_path.display();
        let upper = self.name.to_uppercase();
        let method_id = self.make_method_id();
        format!(
            r##"
pub const {upper}_PATH: &'static str = r#"{elf_path}"#;
pub const {upper}_ID: &'static [u8; {METHOD_ID_LEN}] = &{method_id:?};
            "##
        )
    }
}

/// Returns the given cargo Package from the metadata.
fn get_package<P>(manifest_dir: P) -> Package
where
    P: AsRef<Path>,
{
    let manifest_path = manifest_dir.as_ref().join("Cargo.toml");
    let manifest_meta = MetadataCommand::new()
        .manifest_path(&manifest_path)
        .no_deps()
        .exec()
        .unwrap();
    let mut matching: Vec<&Package> = manifest_meta
        .packages
        .iter()
        .filter(|pkg| {
            let std_path: &Path = pkg.manifest_path.as_ref();
            std_path == &manifest_path
        })
        .collect();
    if matching.len() == 0 {
        eprintln!(
            "ERROR: No package found in {}",
            manifest_dir.as_ref().display()
        );
        std::process::exit(-1);
    }
    if matching.len() > 1 {
        eprintln!(
            "ERROR: Multiple packages found in {}",
            manifest_dir.as_ref().display()
        );
        std::process::exit(-1);
    }
    matching.pop().unwrap().clone()
}

/// When called from a build.rs, returns the current package being built.
fn current_package() -> Package {
    get_package(env::var("CARGO_MANIFEST_DIR").unwrap())
}

/// Returns all inner packages specified the "methods" list inside
/// "package.metadata.risc0".
fn guest_packages(pkg: &Package) -> Vec<Package> {
    let manifest_dir = pkg.manifest_path.parent().unwrap();
    Risc0Metadata::from_package(pkg)
        .unwrap()
        .methods
        .iter()
        .map(|inner| get_package(manifest_dir.join(inner)))
        .collect()
}

/// Returns all methods associated with the given riscv guest package.
fn guest_methods<P>(pkg: &Package, out_dir: P) -> Vec<Risc0Method>
where
    P: AsRef<Path>,
{
    let target_dir = out_dir.as_ref().join("riscv-guest");
    pkg.targets
        .iter()
        .filter(|target| target.kind.iter().any(|kind| kind == "bin"))
        .map(|target| Risc0Method {
            name: target.name.clone(),
            cache_dir: out_dir.as_ref().to_path_buf(),
            elf_path: target_dir
                .join("riscv32im-unknown-none-elf")
                .join("release")
                .join(&target.name),
        })
        .collect()
}

// Builds a package that targets the riscv guest into the specified target directory.
fn build_guest_package<P>(pkg: &Package, target_dir: P)
where
    P: AsRef<Path>,
{
    fs::create_dir_all(target_dir.as_ref()).unwrap();

    let cargo = env::var("CARGO").unwrap();
    let args = vec![
        "build",
        "--release",
        "--target",
        "riscv32im-unknown-none-elf",
        "-Z",
        "build-std=alloc,core",
        "--manifest-path",
        pkg.manifest_path.as_str(),
        "--target-dir",
        target_dir.as_ref().to_str().unwrap(),
    ];
    println!("Building guest package: {cargo} {}", args.join(" "));
    let status = Command::new(cargo).args(args).status().unwrap();
    if !status.success() {
        std::process::exit(status.code().unwrap());
    }
}

/// Embeds methods built for RISC-V for use by host-side dependencies.
///
/// This method should be called from a package with a
/// [package.metadata.risc0] section including a "methods" property
/// listing the relative paths that contain riscv guest method
/// packages.
///
/// To access the generated method IDs and ELF filenames, include the
/// generated methods.rs:
///
/// ```text
///     include!(concat!(env!("OUT_DIR"), "/methods.rs"));
/// ```
///
/// To conform to rust's naming conventions, the constants are mapped
/// to uppercase.  For instance, if you have a method named
/// "my_method", the method ID and elf filename will be defined as
/// "MY_METHOD_ID" and "MY_METHOD_PATH" respectively.
pub fn embed_methods() {
    let pkg = current_package();

    let out_dir_env = env::var_os("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir_env);

    let guest_packages = guest_packages(&pkg);
    let methods_path = out_dir.join("methods.rs");
    let mut methods_file = File::create(&methods_path).unwrap();

    for guest_pkg in guest_packages {
        println!("Building guest package {}.{}", pkg.name, guest_pkg.name);
        
        build_guest_package(&guest_pkg, &out_dir.join("riscv-guest"));
        
        for method in guest_methods(&guest_pkg, &out_dir) {
            methods_file.write_all(method.rust_def().as_bytes()).unwrap();
        }
    }

    // HACK: It's not particularly practical to figure out all the
    // files that all the guest crates transtively depend on.  So, we
    // want to run the guest "cargo build" command each time we build.
    //
    // Since we generate methods.rs each time we run, it will always
    // be changed.
    println!("cargo:rerun-if-changed={}", methods_path.display());
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
