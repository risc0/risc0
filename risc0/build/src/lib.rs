// Copyright 2023 RISC Zero, Inc.
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
use risc0_binfmt::{MemoryImage, Program};
use risc0_zkp::core::digest::{Digest, DIGEST_WORDS};
use risc0_zkvm_platform::{memory, PAGE_SIZE};
use serde::Deserialize;
use sha2::{Digest as ShaDigest, Sha256};
use tempfile::tempdir_in;
use zip::ZipArchive;

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

#[cfg(feature = "guest-list")]
/// Represents an item in the generated list of compiled guest binaries
pub struct GuestListEntry {
    /// The name of the guest binary
    pub name: &'static str,
    /// The compiled ELF guest binary
    pub elf: &'static [u8],
    /// The image id of the guest
    pub image_id: [u32; DIGEST_WORDS],
    /// The path to the ELF binary
    pub path: &'static str,
}

#[derive(Debug)]
struct Risc0Method {
    name: String,
    elf_path: PathBuf,
}

impl Risc0Method {
    fn make_image_id(&self) -> Digest {
        if !self.elf_path.exists() {
            eprintln!(
                "RISC-V method was not found at: {:?}",
                self.elf_path.to_str().unwrap()
            );
            std::process::exit(-1);
        }

        let elf = fs::read(&self.elf_path).unwrap();
        let program = Program::load_elf(&elf, memory::MEM_SIZE as u32).unwrap();
        let image = MemoryImage::new(&program, PAGE_SIZE as u32).unwrap();
        image.compute_id()
    }

    fn rust_def(&self) -> String {
        let elf_path = self.elf_path.display();

        // Quick check for '#' to avoid injection of arbitrary Rust code into the the
        // method.rs file. This would not be a serious issue since it would only
        // affect the user that set the path, but it's good to add a check.
        if let Some(_) = elf_path.to_string().find("#") {
            panic!("method path cannot include #: {}", elf_path);
        }

        let upper = self.name.to_uppercase().replace('-', "_");
        let image_id: [u32; DIGEST_WORDS] = self.make_image_id().into();
        let elf_contents = std::fs::read(&self.elf_path).unwrap();
        format!(
            r##"
pub const {upper}_ELF: &[u8] = &{elf_contents:?};
pub const {upper}_ID: [u32; 8] = {image_id:?};
pub const {upper}_PATH: &str = r#"{elf_path}"#;
"##
        )
    }

    #[cfg(feature = "guest-list")]
    fn guest_list_entry(&self) -> String {
        let upper = self.name.to_uppercase().replace('-', "_");
        format!(
            r##"
    GuestListEntry {{
        name: "{upper}",
        elf: {upper}_ELF,
        image_id: {upper}_ID,
        path: {upper}_PATH,
    }}"##
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
        filename: "6d5dc1eb4c8bb8eaa1dde078396e488810181bdf.zip",
        zip_url: "https://github.com/risc0/rust/archive/6d5dc1eb4c8bb8eaa1dde078396e488810181bdf.zip",
        src_prefix: "rust-6d5dc1eb4c8bb8eaa1dde078396e488810181bdf/library",
        dst_prefix: "library"
    },
    ZipMapEntry {
        filename: "790411f93c4b5eada3c23abb4c9a063fb0b24d99.zip",
        zip_url: "https://github.com/rust-lang/stdarch/archive/790411f93c4b5eada3c23abb4c9a063fb0b24d99.zip",
        src_prefix:"stdarch-790411f93c4b5eada3c23abb4c9a063fb0b24d99",
        dst_prefix: "library/stdarch"
    },
    ZipMapEntry {
        filename: "07872f28cd8a65c3c7428811548dc85f1f2fb05b.zip",
        zip_url: "https://github.com/rust-lang/backtrace-rs/archive/07872f28cd8a65c3c7428811548dc85f1f2fb05b.zip",
        src_prefix:"backtrace-rs-07872f28cd8a65c3c7428811548dc85f1f2fb05b",
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

fn risc0_cache() -> PathBuf {
    directories::ProjectDirs::from("com.risczero", "RISC Zero", "risc0")
        .unwrap()
        .cache_dir()
        .into()
}

fn download_zip_map<P>(zip_map: &[ZipMapEntry], dest_base: P)
where
    P: AsRef<Path>,
{
    let cache_dir = risc0_cache();
    if !cache_dir.is_dir() {
        fs::create_dir_all(&cache_dir).unwrap();
    }

    let temp_dir = tempdir_in(&cache_dir).unwrap();
    let mut downloader = Downloader::builder()
        .download_folder(temp_dir.path())
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
            fs::rename(temp_dir.path().join(zm.filename), &zip_path).unwrap();
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
    let skip_var_name = "RISC0_SKIP_BUILD";
    println!("cargo:rerun-if-env-changed={}", skip_var_name);
    if env::var(skip_var_name).is_ok() {
        return;
    }

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
        .env(
            "CARGO_ENCODED_RUSTFLAGS",
            [
                // Replace atomic ops with nonatomic versions since the guest is single threaded.
                "-C",
                "passes=loweratomic",
                // Remap absolute pathnames in compiled ELFs for builds that are more reproducible.
                "-Z",
                "remap-cwd-prefix=.",
                // Specify where to start loading the program in
                // memory.  The clang linker understands the same
                // command line arguments as the GNU linker does; see
                // https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_mono/ld.html#SEC3
                // for details.
                "-C",
                &format!("link-arg=-Ttext=0x{:08X}", memory::TEXT_START),
                // Apparently not having an entry point is only a linker warning(!), so
                // error out in this case.
                "-C",
                "link-arg=--fatal-warnings",
            ]
            .join("\x1f"),
        )
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
    let tty_file = env::var("RISC0_GUEST_LOGFILE").unwrap_or_else(|_| "/dev/tty".to_string());

    let mut tty = fs::OpenOptions::new()
        .read(true)
        .write(true)
        .create(true)
        .open(tty_file)
        .ok();

    if let Some(tty) = &mut tty {
        writeln!(
            tty,
            "{}: Starting build for riscv32im-risc0-zkvm-elf",
            pkg.name
        )
        .unwrap();
    }

    for line in BufReader::new(stderr).lines() {
        match &mut tty {
            Some(tty) => writeln!(tty, "{}: {}", pkg.name, line.unwrap()).unwrap(),
            None => eprintln!("{}", line.unwrap()),
        }
    }

    let res = child.wait().expect("Guest 'cargo build' failed");
    if !res.success() {
        std::process::exit(res.code().unwrap());
    }
}

/// Options defining how to embed a guest package in
/// [`embed_methods_with_options`].
pub struct GuestOptions {
    /// Features for cargo to build the guest with.
    pub features: Vec<String>,

    /// Enable standard library support
    pub std: bool,
}

impl Default for GuestOptions {
    fn default() -> Self {
        GuestOptions {
            features: vec![],
            std: true,
        }
    }
}

/// Embeds methods built for RISC-V for use by host-side dependencies.
/// Specify custom options for a guest package by defining its [GuestOptions].
/// See [embed_methods].
pub fn embed_methods_with_options(mut guest_pkg_to_options: HashMap<&str, GuestOptions>) {
    let out_dir_env = env::var_os("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir_env); // $ROOT/target/$profile/build/$crate/out
    let guest_dir = out_dir
        .parent() // out
        .unwrap()
        .parent() // $crate
        .unwrap()
        .parent() // build
        .unwrap()
        .parent() // $profile
        .unwrap()
        .join("riscv-guest");

    let pkg = current_package();
    let guest_packages = guest_packages(&pkg);
    let methods_path = out_dir.join("methods.rs");
    let mut methods_file = File::create(&methods_path).unwrap();

    #[cfg(feature = "guest-list")]
    let mut guest_list_entries = Vec::new();
    #[cfg(feature = "guest-list")]
    methods_file
        .write_all(b"use risc0_build::GuestListEntry;\n")
        .unwrap();

    let guest_build_env = setup_guest_build_env(&out_dir);

    for guest_pkg in guest_packages {
        println!("Building guest package {}.{}", pkg.name, guest_pkg.name);

        let guest_options = guest_pkg_to_options
            .remove(guest_pkg.name.as_str())
            .unwrap_or_default();

        build_guest_package(
            &guest_pkg,
            &guest_dir,
            &guest_build_env,
            guest_options.features,
            guest_options.std,
        );

        for method in guest_methods(&guest_pkg, &guest_dir) {
            methods_file
                .write_all(method.rust_def().as_bytes())
                .unwrap();

            #[cfg(feature = "guest-list")]
            guest_list_entries.push(method.guest_list_entry());
        }

        #[cfg(feature = "guest-list")]
        methods_file
            .write_all(
                format!(
                    "\npub const GUEST_LIST: &[GuestListEntry] = &[{}];\n",
                    guest_list_entries.join(",")
                )
                .as_bytes(),
            )
            .unwrap();
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
/// To access the generated image IDs and ELF filenames, include the
/// generated methods.rs:
///
/// ```text
/// include!(concat!(env!("OUT_DIR"), "/methods.rs"));
/// ```
///
/// To conform to rust's naming conventions, the constants are mapped
/// to uppercase.  For instance, if you have a method named
/// "my_method", the image ID and elf contents will be defined as
/// "MY_METHOD_ID" and "MY_METHOD_ELF" respectively.
pub fn embed_methods() {
    embed_methods_with_options(HashMap::new())
}
