// Copyright 2022 RISC Zero, Inc.
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

//! Build RISC Zero zkVM guest code and provide handles to the host side
//!
//! In order for the host to execute guest code in the [RISC Zero
//! zkVM](risc0_zkvm), the host must be provided a compiled RISC-V ELF file and
//! the corresponding [MethodID](risc0_zkvm::MethodId). This crate
//! contains the functions needed to take zkVM guest code, build a corresponding
//! ELF file and MethodID, and make the MethodID and a path to the ELF file
//! available for the host to use.
//!
//! ## Using risc0-build to build guest methods
//!
//! Using this crate can be a bit delicate, so we encourage you to follow along
//! in our [RISC Zero Rust Starter repository](https://github.com/risc0/risc0-rust-starter).
//! In that repository, `risc0-build` is used in the
//! [`methods` directory](https://github.com/risc0/risc0-rust-starter/tree/main/methods).
//!
//! Guest methods are embedded for the host to use by calling [embed_methods]
//! (or [embed_methods_with_options]) in a [build script](https://doc.rust-lang.org/cargo/reference/build-scripts.html).
//! An example `build.rs` file would look like
//! ```no_run
//! fn main() {
//!     risc0_build::embed_methods();
//! }
//! ```
//!
//! This requires including `risc0-build` as a _build_ dependency. You will also
//! need add a `[package.metadata.risc0]` section to your cargo file. In this
//! section, put a `methods` field with a list of relative paths containing the
//! guest code. For example, if your guest code is in the `guest` directory,
//! then `Cargo.toml` might include
//! ```toml
//! [build-dependencies]
//! risc0-build = "1.0.0-rc.1"
//!
//! [package.metadata.risc0]
//! methods = ["guest"]
//! ```
//!
//! This builds a file `methods.rs` in your cargo output directory which you
//! must then include for the host to use. For example, you might make a file
//! `src/lib.rs` containing
//! ```text
//! include!(concat!(env!("OUT_DIR"), "/methods.rs"));
//! ```
//!
//! This process will generate a method ID (`*_ID`) and a path to an ELF file
//! (`*_PATH`). The names will be derived from the name of the file containing
//! the guest method, which will be converted to ALL_CAPS to comply with rust
//! naming conventions. Thus, in the [starter example](https://github.com/risc0/risc0-rust-starter),
//! where the guest method is in
//! [`multiply.rs`](https://github.com/risc0/risc0-rust-starter/blob/main/methods/guest/src/bin/multiply.rs),
//! the method ID is named `methods::MULTIPLY_ID` and the path to the ELF file
//! is named `methods::MULTIPLY_PATH`.
//! These are included at the beginning of the
//! [host code](https://github.com/risc0/risc0-rust-starter/blob/main/starter/src/main.rs):
//! ```text
//! use methods::{MULTIPLY_ID, MULTIPLY_PATH};
//! ```

#![deny(missing_docs)]
#![deny(rustdoc::broken_intra_doc_links)]

use std::{
    collections::HashMap,
    default::Default,
    env,
    fs::{self, File},
    io::{BufRead, BufReader, Write},
    path::{Path, PathBuf},
    process::{Command, Stdio},
};

use cargo_metadata::{MetadataCommand, Package};
use downloader::{Download, Downloader};
use risc0_zkp::adapter::TapsProvider;
use risc0_zkvm::{MethodId, DEFAULT_METHOD_ID_LIMIT};
use serde::Deserialize;
use sha2::{Digest, Sha256};
use zip::ZipArchive;

const LINKER_SCRIPT: &str = include_str!("../risc0.ld");
const TARGET_JSON: &str = include_str!("../riscv32im-risc0-zkvm-elf.json");

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
    fn make_method_id(&self, code_limit: usize) -> MethodId {
        if !self.elf_path.exists() {
            eprintln!(
                "RISC-V method was not found at: {:?}",
                self.elf_path.to_str().unwrap()
            );
            std::process::exit(-1);
        }

        let method_id_path = self.elf_path.with_extension("id");
        let elf_sha_path = self.elf_path.with_extension("sha");
        let elf_contents = std::fs::read(&self.elf_path).unwrap();

        let elf_sha = Sha256::new()
            // Method ID calculation is slow, so only recalculate it if we
            // actually get a different ELF file.
            .chain_update(&elf_contents)
            // Take into account the current circuit; if the circuit
            // changes, the Method ID will change as well.
            .chain_update(format!(
                "{:?}",
                risc0_circuit_rv32im::CircuitImpl.get_taps()
            ))
            // If the Method ID version changes, we need to recreate the Method ID.
            .chain_update(format!("{}", MethodId::VERSION))
            .finalize();

        let elf_sha_hex: String = elf_sha
            .as_slice()
            .iter()
            .map(|x| format!("{:02x}", x))
            .collect();

        if method_id_path.exists() {
            if let Ok(cached_sha) = std::fs::read(&elf_sha_path) {
                if cached_sha == elf_sha.as_slice() {
                    println!("MethodID for {} ({}) up to date", self.name, elf_sha_hex);
                    let buf = std::fs::read(&method_id_path).unwrap();
                    return MethodId::from_slice(&buf).unwrap();
                }
            }
        }

        println!("Computing MethodID for {} ({:})!", self.name, elf_sha_hex);
        let method_id = MethodId::compute_with_limit(&elf_contents, code_limit).unwrap();
        std::fs::write(method_id_path, method_id.as_slice()).unwrap();
        std::fs::write(elf_sha_path, elf_sha).unwrap();
        method_id
    }

    fn rust_def(&self, code_limit: usize) -> String {
        let elf_path = self.elf_path.display();
        let upper = self.name.to_uppercase();
        let method_id = self.make_method_id(code_limit);
        let method_id = method_id.as_slice();
        let elf_contents = std::fs::read(&self.elf_path).unwrap();
        format!(
            r##"
pub const {upper}_PATH: &'static str = r#"{elf_path}"#;
pub const {upper}_ID: &'static [u8] = &{method_id:?};
pub const {upper}_CONTENTS: &'static [u8] = &{elf_contents:?};
            "##
        )
    }
}

#[derive(Debug)]
struct ZipMapEntry {
    filename: &'static str,
    zip_url: &'static str,
    src_prefix: &'static str,
    dst_prefix: &'static str,
}

// Sources for standard library, and where they should be mapped to.
const RUST_LIB_MAP : &[ZipMapEntry] = &[
    ZipMapEntry {
        filename: "97fe14f1b0bceaa053ca0b611a7375273b8398ba.zip",
        zip_url: "https://github.com/risc0/rust/archive/97fe14f1b0bceaa053ca0b611a7375273b8398ba.zip",
        src_prefix: "rust-97fe14f1b0bceaa053ca0b611a7375273b8398ba/library",
        dst_prefix: "library"
    },
    ZipMapEntry {
        filename: "28335054b1f417175ab5005cf1d9cf7937737930.zip",
        zip_url: "https://github.com/rust-lang/stdarch/archive/28335054b1f417175ab5005cf1d9cf7937737930.zip",
        src_prefix:"stdarch-28335054b1f417175ab5005cf1d9cf7937737930",
        dst_prefix: "library/stdarch"
    },
    ZipMapEntry {
        filename: "4e5a3f72929f152752d5659e95bb15c8f6b41eff.zip",
        zip_url: "https://github.com/rust-lang/backtrace-rs/archive/4e5a3f72929f152752d5659e95bb15c8f6b41eff.zip",
        src_prefix:"backtrace-rs-4e5a3f72929f152752d5659e95bb15c8f6b41eff",
        dst_prefix: "library/backtrace"
    },
];

fn sha_digest_with_hex(data: &[u8]) -> (Vec<u8>, String) {
    let bin_sha = Sha256::new().chain_update(data).finalize();
    (
        bin_sha.to_vec(),
        bin_sha
            .as_slice()
            .iter()
            .map(|x| format!("{:02x}", x))
            .collect(),
    )
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
            elf_path: target_dir
                .join("riscv32im-risc0-zkvm-elf")
                .join("release")
                .join(&target.name),
        })
        .collect()
}

#[derive(Debug)]
struct GuestBuildEnv {
    target_spec: PathBuf,
    rust_lib_src: PathBuf,
}

fn setup_guest_build_env<P>(out_dir: P) -> GuestBuildEnv
where
    P: AsRef<Path>,
{
    // RISCV target specification
    let target_spec_path = out_dir.as_ref().join("riscv32im-risc0-zkvm-elf.json");
    let linker_script: String = LINKER_SCRIPT.escape_default().to_string();
    fs::write(
        &target_spec_path,
        TARGET_JSON.replace("<LINKER-SCRIPT>", &linker_script),
    )
    .unwrap();

    // Rust standard library.  If any of the RUST_LIB_MAP changed, we
    // want to have a different hash so that we make sure we recompile.
    let (_, src_id_hash) = sha_digest_with_hex(format!("{:?}", RUST_LIB_MAP).as_bytes());
    let rust_lib_path = out_dir.as_ref().join(format!("rust-std_{}", src_id_hash));
    if !rust_lib_path.exists() {
        println!(
            "Standard library {} does not exist; downloading",
            rust_lib_path.display()
        );

        download_zip_map(RUST_LIB_MAP, &rust_lib_path);
    }

    GuestBuildEnv {
        target_spec: target_spec_path.to_owned(),
        rust_lib_src: rust_lib_path,
    }
}

fn risc0_root() -> PathBuf {
    home::home_dir().unwrap().join(".risc0").into()
}

fn download_zip_map<P>(zip_map: &[ZipMapEntry], dest_base: P)
where
    P: AsRef<Path>,
{
    let cache_dir = risc0_root().join("cache");
    if !cache_dir.is_dir() {
        fs::create_dir_all(&cache_dir).unwrap();
    }
    let mut downloader = Downloader::builder()
        .download_folder(&cache_dir)
        .build()
        .unwrap();

    let tmp_dest_base = dest_base.as_ref().with_extension("downloadtmp");
    if tmp_dest_base.exists() {
        fs::remove_dir_all(&tmp_dest_base).unwrap();
    }

    for zm in zip_map.iter() {
        let src_prefix = Path::new(&zm.src_prefix);
        let dst_prefix = tmp_dest_base.join(&zm.dst_prefix);
        fs::create_dir_all(&dst_prefix).unwrap();

        let zip_path = cache_dir.join(zm.filename);
        if !zip_path.is_file() {
            println!(
                "Downloading {}, mapping {} to {}",
                zm.zip_url,
                zm.src_prefix,
                dst_prefix.display()
            );
            let dl = Download::new(zm.zip_url);
            downloader.download(&[dl]).unwrap().iter().for_each(|x| {
                let summary = x.as_ref().unwrap();
                println!("Downloaded: {}", summary.file_name.display());
            });
        }

        let zip_file = File::open(zip_path).unwrap();
        let mut zip = ZipArchive::new(zip_file).unwrap();
        println!("Got zip with {} files", zip.len());

        let mut nwrote: u32 = 0;
        for i in 0..zip.len() {
            let mut f = zip.by_index(i).unwrap();
            let name = f.enclosed_name().unwrap();
            if let Ok(relative_src) = name.strip_prefix(src_prefix) {
                let dest_name = dst_prefix.join(relative_src);
                if f.is_dir() {
                    fs::create_dir_all(dest_name).unwrap();
                    continue;
                }
                if !f.is_file() {
                    continue;
                }
                std::io::copy(&mut f, &mut File::create(&dest_name).unwrap()).unwrap();
                nwrote += 1;
            }
        }
        println!("Wrote {} files", nwrote);
    }
    fs::rename(&tmp_dest_base, dest_base.as_ref()).unwrap();
}

// Builds a package that targets the riscv guest into the specified target
// directory.
fn build_guest_package<P>(
    pkg: &Package,
    target_dir: P,
    guest_build_env: &GuestBuildEnv,
    features: Vec<String>,
    std: bool,
) where
    P: AsRef<Path>,
{
    fs::create_dir_all(target_dir.as_ref()).unwrap();
    let cargo = env::var("CARGO").unwrap();
    let mut std_parts = vec!["alloc", "core", "proc_macro", "panic_abort"];
    if std {
        std_parts.push("std");
    }
    let build_std = format!("build-std={}", std_parts.join(","));
    let mut args = vec![
        "build",
        "--release",
        "--target",
        guest_build_env.target_spec.to_str().unwrap(),
        "-Z",
        build_std.as_str(),
        "-Z",
        "build-std-features=compiler-builtins-mem",
        "--manifest-path",
        pkg.manifest_path.as_str(),
        "--target-dir",
        target_dir.as_ref().to_str().unwrap(),
    ];
    let features_str = features.join(",");
    if !features.is_empty() {
        args.push("--features");
        args.push(&features_str);
    }
    println!("Building guest package: {cargo} {}", args.join(" "));
    // The RISC0_STANDARD_LIB variable can be set for testing purposes
    // to override the downloaded standard library.  It should point
    // to the root of the rust repository.
    let risc0_standard_lib: String = if let Ok(path) = env::var("RISC0_STANDARD_LIB") {
        path
    } else {
        guest_build_env.rust_lib_src.to_str().unwrap().into()
    };

    println!("Using rust standard library root: {}", risc0_standard_lib);

    let mut cmd = Command::new(cargo);
    let mut child = cmd
        .env("CARGO_ENCODED_RUSTFLAGS", "-C\x1fpasses=loweratomic")
        .env("__CARGO_TESTS_ONLY_SRC_ROOT", risc0_standard_lib)
        .args(args)
        .stderr(Stdio::piped())
        .spawn()
        .unwrap();
    let stderr = child.stderr.take().unwrap();

    // HACK: Attempt to bypass the parent cargo output capture and
    // send directly to the tty, if available.  This way we get
    // progress messages from the inner cargo so the user doesn't
    // think it's just hanging.
    let mut tty = fs::OpenOptions::new()
        .read(true)
        .write(true)
        .open("/dev/tty")
        .ok();

    if let Some(tty) = &mut tty {
        write!(
            tty,
            "{}: Starting build for riscv32im-risc0-zkvm-elf   \n",
            pkg.name
        )
        .unwrap();
    }

    for line in BufReader::new(stderr).lines() {
        match &mut tty {
            Some(tty) => write!(tty, "{}: {}   \n", pkg.name, line.unwrap()).unwrap(),
            None => eprintln!("{}", line.unwrap()),
        }
    }

    let status = cmd.status().unwrap();

    if !status.success() {
        std::process::exit(status.code().unwrap());
    }
}

/// Options defining how to embed a guest package in
/// [`embed_methods_with_options`].
pub struct GuestOptions {
    /// The maximum number of cycles (in units of powers of 2) supported by a
    /// MethodID. The bigger this value is the longer it takes to compute a
    /// MethodID.
    pub code_limit: usize,

    /// Features for cargo to build the guest with.
    pub features: Vec<String>,

    /// Enable standard library support
    pub std: bool,
}

impl Default for GuestOptions {
    fn default() -> Self {
        GuestOptions {
            code_limit: DEFAULT_METHOD_ID_LIMIT,
            features: vec![],
            std: true,
        }
    }
}

/// Embeds methods built for RISC-V for use by host-side dependencies.
/// Specify custom options for a guest package by defining its [GuestOptions].
/// See [embed_methods].
pub fn embed_methods_with_options(mut guest_pkg_to_options: HashMap<&str, GuestOptions>) {
    if env::var("RISC0_SKIP_BUILD").is_ok() {
        return;
    }

    let out_dir_env = env::var_os("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir_env);

    let pkg = current_package();
    let guest_packages = guest_packages(&pkg);
    let methods_path = out_dir.join("methods.rs");
    let mut methods_file = File::create(&methods_path).unwrap();

    let guest_build_env = setup_guest_build_env(&out_dir);

    for guest_pkg in guest_packages {
        println!("Building guest package {}.{}", pkg.name, guest_pkg.name);

        let guest_options = guest_pkg_to_options
            .remove(guest_pkg.name.as_str())
            .unwrap_or_default();

        build_guest_package(
            &guest_pkg,
            &out_dir.join("riscv-guest"),
            &guest_build_env,
            guest_options.features,
            guest_options.std,
        );

        for method in guest_methods(&guest_pkg, &out_dir) {
            methods_file
                .write_all(method.rust_def(guest_options.code_limit).as_bytes())
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
/// include!(concat!(env!("OUT_DIR"), "/methods.rs"));
/// ```
///
/// To conform to rust's naming conventions, the constants are mapped
/// to uppercase.  For instance, if you have a method named
/// "my_method", the method ID and elf filename will be defined as
/// "MY_METHOD_ID" and "MY_METHOD_PATH" respectively.
pub fn embed_methods() {
    embed_methods_with_options(HashMap::new())
}
