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
use risc0_zkvm_sys::MethodID;
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
}

impl Risc0Method {
    fn make_method_id<P>(&self, method_id_path: P)
    where
        P: AsRef<Path>,
    {
        if !self.elf_path.exists() {
            eprintln!(
                "RISC-V method was not found at: {:?}",
                self.elf_path.to_str().unwrap()
            );
            std::process::exit(-1);
        }

        // Method ID calculation is slow, so only recalculate it if we
        // actually get a different ELF file.
        let elf_contents = std::fs::read(&self.elf_path).unwrap();
        let elf_sha = Sha256::new().chain_update(elf_contents).finalize();
        let elf_sha_hex: String = elf_sha
            .as_slice()
            .iter()
            .map(|x| format!("{:02x}", x))
            .collect();

        let cached_elf_sha_path = method_id_path.as_ref().with_extension("elf_sha");
        if method_id_path.as_ref().exists() {
            if let Ok(cached_sha) = std::fs::read(&cached_elf_sha_path) {
                if cached_sha == elf_sha.as_slice() {
                    println!("Method id for {} ({}) up to date", self.name, elf_sha_hex);
                    return;
                }
            }
        }

        println!(
            "Calculating method id for {} ({:})!",
            self.name, elf_sha_hex
        );

        let method_id = MethodID::new(&self.elf_path.to_str().unwrap()).unwrap();
        method_id
            .write(&method_id_path.as_ref().to_str().unwrap())
            .unwrap();
        std::fs::write(cached_elf_sha_path, elf_sha).unwrap();
    }

    fn rust_def(&self, method_id_path: &Path) -> String {
        let elf_path = self.elf_path.display();
        let id_path = method_id_path.display();
        let upper = self.name.to_uppercase();
        format!(
            r##"
    pub const {upper}_PATH: &str = r#"{elf_path}"#;
    pub const {upper}_ID: &[u8] = include_bytes!(r#"{id_path}"#);
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
fn guest_methods<P>(pkg: &Package, target_dir: P) -> Vec<Risc0Method>
where
    P: AsRef<Path>,
{
    pkg.targets
        .iter()
        .filter(|target| target.kind.iter().any(|kind| kind == "bin"))
        .map(|target| Risc0Method {
            name: target.name.clone(),
            elf_path: target_dir
                .as_ref()
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
    let guest_target_dir = out_dir.join("riscv-guest");

    let guest_packages = guest_packages(&pkg);
    let methods_path = out_dir.join("methods.rs");
    let mut methods_file = File::create(&methods_path).unwrap();

    for guest_pkg in guest_packages {
        println!(
            "Building guest package {} (parent={})",
            guest_pkg.name, pkg.name
        );

        build_guest_package(&guest_pkg, &guest_target_dir);

        let methods = guest_methods(&guest_pkg, &guest_target_dir);
        for method in methods {
            let method_id_path = out_dir.join(format!("{}.id", method.name));
            method.make_method_id(&method_id_path);
            methods_file
                .write_all(method.rust_def(&method_id_path).as_bytes())
                .unwrap();
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
        let linker_script = linker_script.to_str().unwrap();
        println!("cargo:rustc-link-arg=-T{linker_script}");
    }
}
