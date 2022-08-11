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
    collections::HashMap,
    default::Default,
    env,
    fs::{self, File},
    io::{BufRead, BufReader, Cursor, Read, Write},
    path::{Path, PathBuf},
    process::{Command, Stdio},
};

use cargo_metadata::{MetadataCommand, Package};
use risc0_zkvm::host::{MethodId, DEFAULT_METHOD_ID_LIMIT};
use risc0_zkvm_platform_sys::LINKER_SCRIPT;
use serde::Deserialize;
use sha2::{Digest, Sha256};
use zip::ZipArchive;

const TARGET_JSON: &[u8] = include_bytes!("../riscv32im-risc0-zkvm-elf.json");

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
    fn make_method_id(&self, code_limit: u32) -> Vec<u8> {
        if !self.elf_path.exists() {
            eprintln!(
                "RISC-V method was not found at: {:?}",
                self.elf_path.to_str().unwrap()
            );
            std::process::exit(-1);
        }

        // Method ID calculation is slow, so only recalculate it if we
        // actually get a different ELF file.
        let method_id_path = self.elf_path.with_extension("id");
        let elf_sha_path = self.elf_path.with_extension("sha");
        let elf_contents = std::fs::read(&self.elf_path).unwrap();
        let (elf_sha, elf_sha_hex) = sha_digest_with_hex(&elf_contents);
        if method_id_path.exists() {
            if let Ok(cached_sha) = std::fs::read(&elf_sha_path) {
                if cached_sha == elf_sha.as_slice() {
                    println!("MethodID for {} ({}) up to date", self.name, elf_sha_hex);
                    return std::fs::read(&method_id_path).unwrap();
                }
            }
        }

        println!("Computing MethodID for {} ({:})!", self.name, elf_sha_hex);
        let elf_contents = std::fs::read(&self.elf_path).unwrap();
        let method_id = MethodId::compute_with_limit(&elf_contents, code_limit).unwrap();
        let slice = method_id.as_slice().unwrap();
        std::fs::write(method_id_path, slice).unwrap();
        std::fs::write(elf_sha_path, elf_sha).unwrap();
        Vec::from(slice)
    }

    fn rust_def(&self, code_limit: u32) -> String {
        let elf_path = self.elf_path.display();
        let upper = self.name.to_uppercase();
        let method_id = self.make_method_id(code_limit);
        format!(
            r##"
pub const {upper}_PATH: &'static str = r#"{elf_path}"#;
pub const {upper}_ID: &'static [u8] = &{method_id:?};
            "##
        )
    }
}

#[derive(Debug)]
struct ZipMapEntry {
    zip_url: &'static str,
    src_prefix: &'static str,
    dst_prefix: &'static str,
}

/// ID of rust library source version.  This is an arbitrary string,
/// but must change if we need to download a new library version.  So
/// let's just use the GIT commit ID.
const RUST_LIB_ID: &str = "13dd9c85310093d42bed1528c07aec397cb76716";
const RUST_LIB_MAP : &[ZipMapEntry] = &[
    ZipMapEntry{
	zip_url: "https://github.com/risc0/rust/archive/9df34d93b963521ddb646840181aa9ee6494df48.zip",
	src_prefix: "rust-9df34d93b963521ddb646840181aa9ee6494df48/library",
	dst_prefix: "library"},
    ZipMapEntry{
	zip_url: "https://github.com/rust-lang/stdarch/archive/28335054b1f417175ab5005cf1d9cf7937737930.zip",
	src_prefix:"stdarch-28335054b1f417175ab5005cf1d9cf7937737930",
	dst_prefix: "library/stdarch"},
    ZipMapEntry{
	zip_url: "https://github.com/rust-lang/backtrace-rs/archive/4e5a3f72929f152752d5659e95bb15c8f6b41eff.zip",
	src_prefix:"backtrace-rs-4e5a3f72929f152752d5659e95bb15c8f6b41eff",
	dst_prefix: "library/backtrace"},
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
    fs::write(&target_spec_path, TARGET_JSON).unwrap();

    // Rust standard library
    let (_, src_id_hash) = sha_digest_with_hex(RUST_LIB_ID.as_bytes());
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

fn download_zip_map<P>(zip_map: &[ZipMapEntry], dest_base: P)
where
    P: AsRef<Path>,
{
    let tmp_dest_base = dest_base.as_ref().with_extension("downloadtmp");
    if tmp_dest_base.exists() {
        fs::remove_dir_all(&tmp_dest_base).unwrap();
    }
    for zm in zip_map.iter() {
        let src_prefix = Path::new(&zm.src_prefix);
        let dst_prefix = tmp_dest_base.join(&zm.dst_prefix);
        println!(
            "Downloading {}, mapping {} to {}",
            zm.zip_url,
            zm.src_prefix,
            dst_prefix.display()
        );

        fs::create_dir_all(&dst_prefix).unwrap();

        let mut response = reqwest::blocking::get(zm.zip_url).unwrap();
        let mut zip_buf: Vec<u8> = Vec::new();
        response.read_to_end(&mut zip_buf).unwrap();
        let mut zip = ZipArchive::new(Cursor::new(&zip_buf)).unwrap();
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
) where
    P: AsRef<Path>,
{
    fs::create_dir_all(target_dir.as_ref()).unwrap();
    let cargo = env::var("CARGO").unwrap();
    let mut args = vec![
        "build",
        "--release",
        "--target",
        guest_build_env.target_spec.to_str().unwrap(),
        "-Z",
        "build-std=core,alloc,std,proc_macro,panic_abort",
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
    /// The number of po2 entries to generate in the MethodID.
    pub code_limit: u32,

    /// Features for cargo to build the guest with.
    pub features: Vec<String>,
}

impl Default for GuestOptions {
    fn default() -> Self {
        GuestOptions {
            code_limit: DEFAULT_METHOD_ID_LIMIT,
            features: vec![],
        }
    }
}

/// Embeds methods built for RISC-V for use by host-side dependencies.
/// Specify custom options for a guest package by defining its [GuestOptions].
/// See [embed_methods].
pub fn embed_methods_with_options(mut guest_pkg_to_options: HashMap<&str, GuestOptions>) {
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
///     include!(concat!(env!("OUT_DIR"), "/methods.rs"));
/// ```
///
/// To conform to rust's naming conventions, the constants are mapped
/// to uppercase.  For instance, if you have a method named
/// "my_method", the method ID and elf filename will be defined as
/// "MY_METHOD_ID" and "MY_METHOD_PATH" respectively.
pub fn embed_methods() {
    embed_methods_with_options(HashMap::new())
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
