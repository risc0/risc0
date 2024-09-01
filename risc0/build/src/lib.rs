// Copyright 2024 RISC Zero, Inc.
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
#![cfg_attr(docsrs, feature(doc_cfg, doc_auto_cfg))]

mod config;
mod docker;

use std::{
    borrow::Cow,
    collections::HashMap,
    default::Default,
    env,
    fs::{self, File},
    io::{BufRead, BufReader, Write},
    path::{Path, PathBuf},
    process::{Command, Stdio},
};

use anyhow::{anyhow, Context, Result};
use cargo_metadata::{Message, MetadataCommand, Package};
use risc0_binfmt::compute_image_id;
use risc0_zkp::core::digest::{Digest, DIGEST_WORDS};
use risc0_zkvm_platform::memory;
use serde::Deserialize;

use self::{
    config::{GuestBuildOptions, GuestMetadata},
    docker::build_guest_package_docker,
};

pub use self::config::{DockerOptions, GuestOptions};
pub use self::docker::{docker_build, BuildStatus, TARGET_DIR};

/// This const represents a filename that is used in the use to indicate to in
/// order to indicate to the client and the risc0-build crate that the new rust
/// implementation of rzup is in use. The rust implementation of rzup will place
/// a file with this name under `$RISC0_HOME`.
pub const RUST_RZUP_INDICATOR: &str = ".rzup";

const RUSTUP_TOOLCHAIN_NAME: &str = "risc0";

/// Get the path used by cargo-risczero that stores downloaded toolchains
pub fn risc0_data() -> Result<PathBuf> {
    risc0_data_new().or_else(|_| risc0_data_compat())
}

// use the new location from rzup install.
fn risc0_data_new() -> Result<PathBuf> {
    let dir = if let Ok(dir) = std::env::var("RISC0_HOME") {
        dir.into()
    } else if let Some(home) = dirs::home_dir() {
        home.join(".risc0")
    } else {
        anyhow::bail!("Could not determine risc0 home dir. Set RISC0_HOME env var.");
    };

    if !dir.join(RUST_RZUP_INDICATOR).exists() {
        anyhow::bail!("Could not determine risc0 home dir. Set RISC0_HOME env var.");
    }

    Ok(dir)
}

// check for backwards compatible cargo risczero install.
fn risc0_data_compat() -> Result<PathBuf> {
    let dir = if let Ok(dir) = std::env::var("RISC0_DATA_DIR") {
        dir.into()
    } else if let Some(root) = dirs::data_dir() {
        root.join("cargo-risczero")
    } else if let Some(home) = dirs::home_dir() {
        home.join(".cargo-risczero")
    } else {
        anyhow::bail!("Could not determine risc0 data dir. Set RISC0_DATA_DIR env var.");
    };

    Ok(dir)
}

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

trait GuestBuilder: Sized {
    fn build(name: &str, elf_path: &str) -> Result<Self>;
    fn codegen_consts(&self) -> String;
    #[cfg(feature = "guest-list")]
    fn codegen_list_entry(&self) -> String;
}

/// Represents an item in the generated list of compiled guest binaries
#[derive(Debug, Clone)]
pub struct MinGuestListEntry {
    /// The name of the guest binary
    pub name: Cow<'static, str>,
    /// The path to the ELF binary
    pub path: Cow<'static, str>,
}

impl GuestBuilder for MinGuestListEntry {
    fn build(name: &str, elf_path: &str) -> Result<Self> {
        Ok(Self {
            name: Cow::Owned(name.to_owned()),
            path: Cow::Owned(elf_path.to_owned()),
        })
    }

    fn codegen_consts(&self) -> String {
        // Quick check for '#' to avoid injection of arbitrary Rust code into the
        // method.rs file. This would not be a serious issue since it would only
        // affect the user that set the path, but it's good to add a check.
        if self.path.contains('#') {
            panic!("method path cannot include #: {}", self.path);
        }

        let upper = self.name.to_uppercase().replace('-', "_");
        let elf_path: &str = &self.path;

        format!(r##"pub const {upper}_PATH: &str = r#"{elf_path}"#;"##)
    }

    #[cfg(feature = "guest-list")]
    fn codegen_list_entry(&self) -> String {
        let upper = self.name.to_uppercase().replace('-', "_");
        format!(
            r##"
    MinGuestListEntry {{
        name: std::borrow::Cow::Borrowed("{upper}"),
        path: std::borrow::Cow::Borrowed({upper}_PATH),
    }}"##
        )
    }
}

/// Represents an item in the generated list of compiled guest binaries
#[derive(Debug, Clone)]
pub struct GuestListEntry {
    /// The name of the guest binary
    pub name: Cow<'static, str>,

    /// The compiled ELF guest binary
    pub elf: Cow<'static, [u8]>,

    /// The image id of the guest
    pub image_id: [u32; DIGEST_WORDS],

    /// The path to the ELF binary
    pub path: Cow<'static, str>,
}

fn r0vm_image_id(path: &str) -> Result<Digest> {
    use hex::FromHex;
    let output = Command::new("r0vm")
        .args(["--elf", path, "--id"])
        .output()?;
    if output.status.success() {
        let stdout = String::from_utf8(output.stdout)?;
        let digest = stdout.trim();
        Ok(Digest::from_hex(digest)?)
    } else {
        let stderr = String::from_utf8(output.stderr)?;
        Err(anyhow!("{stderr}"))
    }
}

impl GuestBuilder for GuestListEntry {
    /// Builds the [GuestListEntry] by reading the ELF from disk, and calculating the associated
    /// image ID.
    fn build(name: &str, elf_path: &str) -> Result<Self> {
        let (elf, image_id) = if !is_skip_build() {
            let elf = std::fs::read(elf_path)?;
            let image_id = match r0vm_image_id(elf_path) {
                Ok(image_id) => image_id,
                Err(err) => {
                    tty_println(&format!("{err}"));
                    compute_image_id(&elf)?
                }
            };
            (elf, image_id)
        } else {
            (vec![], Digest::default())
        };

        Ok(Self {
            name: Cow::Owned(name.to_owned()),
            elf: Cow::Owned(elf),
            image_id: image_id.into(),
            path: Cow::Owned(elf_path.to_owned()),
        })
    }

    fn codegen_consts(&self) -> String {
        // Quick check for '#' to avoid injection of arbitrary Rust code into the
        // method.rs file. This would not be a serious issue since it would only
        // affect the user that set the path, but it's good to add a check.
        if self.path.contains('#') {
            panic!("method path cannot include #: {}", self.path);
        }

        let upper = self.name.to_uppercase().replace('-', "_");
        let image_id = self.image_id;
        let elf_path = &self.path;

        let elf_value = if is_skip_build() {
            "&[]".to_string()
        } else {
            format!(r#"include_bytes!("{elf_path}")"#)
        };

        format!(
            r##"
pub const {upper}_ELF: &[u8] = {elf_value};
pub const {upper}_ID: [u32; 8] = {image_id:?};
pub const {upper}_PATH: &str = "{elf_path}";
"##
        )
    }

    #[cfg(feature = "guest-list")]
    fn codegen_list_entry(&self) -> String {
        let upper = self.name.to_uppercase().replace('-', "_");
        format!(
            r##"
    GuestListEntry {{
        name: std::borrow::Cow::Borrowed("{upper}"),
        elf: std::borrow::Cow::Borrowed({upper}_ELF),
        image_id: {upper}_ID,
        path: std::borrow::Cow::Borrowed({upper}_PATH),
    }}"##
        )
    }
}

/// Returns the given cargo Package from the metadata in the Cargo.toml manifest
/// within the provided `manifest_dir`.
pub fn get_package(manifest_dir: impl AsRef<Path>) -> Package {
    let manifest_path = manifest_dir.as_ref().join("Cargo.toml");
    let manifest_meta = MetadataCommand::new()
        .manifest_path(&manifest_path)
        .no_deps()
        .exec()
        .expect("cargo metadata command failed");
    let mut matching: Vec<Package> = manifest_meta
        .packages
        .into_iter()
        .filter(|pkg| {
            let std_path: &Path = pkg.manifest_path.as_ref();
            std_path == manifest_path
        })
        .collect();
    if matching.is_empty() {
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
    matching.pop().unwrap()
}

/// Determines and returns the build target directory from the Cargo manifest at
/// the given `manifest_path`.
pub fn get_target_dir(manifest_path: impl AsRef<Path>) -> PathBuf {
    MetadataCommand::new()
        .manifest_path(manifest_path.as_ref())
        .no_deps()
        .exec()
        .expect("cargo metadata command failed")
        .target_directory
        .into()
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

fn is_debug() -> bool {
    get_env_var("RISC0_BUILD_DEBUG") == "1"
}

fn is_skip_build() -> bool {
    !get_env_var("RISC0_SKIP_BUILD").is_empty()
}

fn get_env_var(name: &str) -> String {
    println!("cargo:rerun-if-env-changed={name}");
    env::var(name).unwrap_or_default()
}

/// Returns all methods associated with the given guest crate.
fn guest_methods<G: GuestBuilder>(
    pkg: &Package,
    target_dir: impl AsRef<Path>,
    guest_features: &[String],
) -> Vec<G> {
    let profile = if is_debug() { "debug" } else { "release" };
    pkg.targets
        .iter()
        .filter(|target| target.kind.iter().any(|kind| kind == "bin"))
        .filter(|target| {
            target
                .required_features
                .iter()
                .all(|required_feature| guest_features.contains(required_feature))
        })
        .map(|target| {
            G::build(
                &target.name,
                target_dir
                    .as_ref()
                    .join("riscv32im-risc0-zkvm-elf")
                    .join(profile)
                    .join(&target.name)
                    .to_str()
                    .context("elf path contains invalid unicode")
                    .unwrap(),
            )
            .unwrap()
        })
        .collect()
}

/// Returns all methods associated with the given guest crate.
fn guest_methods_docker<P, G>(pkg: &Package, target_dir: P) -> Vec<G>
where
    P: AsRef<Path>,
    G: GuestBuilder,
{
    pkg.targets
        .iter()
        .filter(|target| target.kind.iter().any(|kind| kind == "bin"))
        .map(|target| {
            G::build(
                &target.name,
                target_dir
                    .as_ref()
                    .join("riscv32im-risc0-zkvm-elf")
                    .join("docker")
                    .join(pkg.name.replace('-', "_"))
                    .join(&target.name)
                    .to_str()
                    .context("elf path contains invalid unicode")
                    .unwrap(),
            )
            .unwrap()
        })
        .collect()
}

/// Build a [Command] with CARGO and RUSTUP_TOOLCHAIN environment variables
/// removed.
fn sanitized_cmd(tool: &str) -> Command {
    let mut cmd = Command::new(tool);
    for (key, _val) in env::vars().filter(|x| x.0.starts_with("CARGO")) {
        cmd.env_remove(key);
    }
    cmd.env_remove("RUSTUP_TOOLCHAIN");
    cmd
}

/// Creates a std::process::Command to execute the given cargo
/// command in an environment suitable for targeting the zkvm guest.
pub fn cargo_command(subcmd: &str, rust_flags: &[&str]) -> Command {
    let rustc = sanitized_cmd("rustup")
        .args(["+risc0", "which", "rustc"])
        .output()
        .expect("rustup failed to find risc0 toolchain")
        .stdout;

    let rustc = String::from_utf8(rustc).unwrap();
    let rustc = rustc.trim();
    println!("Using rustc: {rustc}");

    let mut cmd = sanitized_cmd("cargo");
    let mut args = vec![subcmd, "--target", "riscv32im-risc0-zkvm-elf"];

    if std::env::var("RISC0_BUILD_LOCKED").is_ok() {
        args.push("--locked");
    }

    let rust_src = get_env_var("RISC0_RUST_SRC");
    if !rust_src.is_empty() {
        args.push("-Z");
        args.push("build-std=alloc,core,proc_macro,panic_abort,std");
        args.push("-Z");
        args.push("build-std-features=compiler-builtins-mem");
        cmd.env("__CARGO_TESTS_ONLY_SRC_ROOT", rust_src);
    }

    println!("Building guest package: cargo {}", args.join(" "));

    let encoded_rust_flags = encode_rust_flags(rust_flags);

    if !cpp_toolchain_override() {
        let cc_path = risc0_data()
            .unwrap()
            .join("cpp/bin/riscv32-unknown-elf-gcc");
        cmd.env("CC", cc_path)
            .env("CFLAGS_riscv32im_risc0_zkvm_elf", "-march=rv32im -nostdlib");
    }

    cmd.env("RUSTC", rustc)
        .env("CARGO_ENCODED_RUSTFLAGS", encoded_rust_flags)
        .args(args);
    cmd
}

/// Returns a string that can be set as the value of CARGO_ENCODED_RUSTFLAGS when compiling guests
pub(crate) fn encode_rust_flags(rustc_flags: &[&str]) -> String {
    [
        // Append other rust flags
        rustc_flags,
        &[
            // Replace atomic ops with nonatomic versions since the guest is single threaded.
            "-C",
            "passes=loweratomic",
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
            "-C",
            "panic=abort",
        ],
    ]
    .concat()
    .join("\x1f")
}

fn cpp_toolchain_override() -> bool {
    // detect if there's an attempt to override the Cpp toolchain.
    // Overriding the toolchain useful for troubleshooting crates.
    std::env::var("CC_riscv32im_risc0_zkvm_elf").is_ok()
        || std::env::var("CFLAGS_riscv32im_risc0_zkvm_elf").is_ok()
}

/// Builds a static library providing a rust runtime.
///
/// This can be used to build programs for the zkvm which don't depend on
/// risc0_zkvm.
pub fn build_rust_runtime() -> String {
    build_staticlib(
        "risc0-zkvm-platform",
        &["rust-runtime", "panic-handler", "entrypoint", "getrandom"],
    )
}

/// Builds a static library and returns the name of the resultant file.
fn build_staticlib(guest_pkg: &str, features: &[&str]) -> String {
    let guest_dir = get_guest_dir();

    let mut cmd = cargo_command("rustc", &[]);

    if !is_debug() {
        cmd.arg("--release");
    }

    // Add args to specify the package to be built, and to build is as a staticlib.
    cmd.args([
        "--package",
        guest_pkg,
        "--target-dir",
        guest_dir.to_str().unwrap(),
        "--lib",
        "--message-format=json",
        "--crate-type=staticlib",
    ]);

    for feature in features {
        cmd.args(["--features", &(guest_pkg.to_owned() + "/" + feature)]);
    }

    eprintln!("Building staticlib: {:?}", cmd);

    // Run the build command and extract the name of the resulting staticlib
    // artifact.
    let mut child = cmd.stdout(Stdio::piped()).spawn().unwrap();
    let reader = std::io::BufReader::new(child.stdout.take().unwrap());
    let mut libs = Vec::new();
    for message in Message::parse_stream(reader) {
        match message.unwrap() {
            Message::CompilerArtifact(artifact) => {
                for filename in artifact.filenames {
                    if let Some("a") = filename.extension() {
                        libs.push(filename.to_string());
                    }
                }
            }
            Message::CompilerMessage(msg) => {
                eprint!("{}", msg);
            }
            _ => (),
        }
    }

    let output = child.wait().expect("Couldn't get cargo's exit status");
    if !output.success() {
        panic!("Unable to build static library")
    }

    match libs.as_slice() {
        [] => panic!("No static library was built"),
        [lib] => lib.to_string(),
        _ => panic!("Multiple static libraries found: {:?}", libs.as_slice()),
    }
}

// HACK: Attempt to bypass the parent cargo output capture and
// send directly to the tty, if available.  This way we get
// progress messages from the inner cargo so the user doesn't
// think it's just hanging.
fn tty_println(msg: &str) {
    let tty_file = env::var("RISC0_GUEST_LOGFILE").unwrap_or_else(|_| "/dev/tty".to_string());

    let mut tty = fs::OpenOptions::new()
        .read(true)
        .write(true)
        .create(true)
        .truncate(false)
        .open(tty_file)
        .ok();

    if let Some(tty) = &mut tty {
        writeln!(tty, "{msg}").unwrap();
    } else {
        eprintln!("{msg}");
    }
}

// Builds a package that targets the riscv guest into the specified target
// directory.
fn build_guest_package<P>(
    pkg: &Package,
    target_dir: P,
    guest_opts: &GuestBuildOptions,
    runtime_lib: Option<&str>,
) where
    P: AsRef<Path>,
{
    if is_skip_build() {
        return;
    }

    fs::create_dir_all(target_dir.as_ref()).unwrap();

    let runtime_rust_flags = runtime_lib
        .map(|lib| vec![String::from("-C"), format!("link_arg={}", lib)])
        .unwrap_or_default();
    let rust_flags: Vec<_> = [
        runtime_rust_flags
            .iter()
            .map(|s| s.as_str())
            .collect::<Vec<_>>(),
        guest_opts.rustc_flags.iter().map(|s| s.as_str()).collect(),
    ]
    .concat();

    let mut cmd = cargo_command("build", &rust_flags);

    let features_str = guest_opts.features.join(",");
    if !features_str.is_empty() {
        cmd.args(["--features", &features_str]);
    }

    cmd.args([
        "--manifest-path",
        pkg.manifest_path.as_str(),
        "--target-dir",
        target_dir.as_ref().to_str().unwrap(),
    ]);

    if !is_debug() {
        cmd.args(["--release"]);
    }

    let mut child = cmd
        .stderr(Stdio::piped())
        .spawn()
        .expect("cargo build failed");
    let stderr = child.stderr.take().unwrap();

    tty_println(&format!(
        "{}: Starting build for riscv32im-risc0-zkvm-elf",
        pkg.name
    ));

    for line in BufReader::new(stderr).lines() {
        tty_println(&format!("{}: {}", pkg.name, line.unwrap()));
    }

    let res = child.wait().expect("Guest 'cargo build' failed");
    if !res.success() {
        std::process::exit(res.code().unwrap());
    }
}

fn detect_toolchain(name: &str) {
    let result = Command::new("rustup")
        .args(["toolchain", "list", "--verbose"])
        .stderr(Stdio::inherit())
        .output()
        .unwrap();
    if !result.status.success() {
        eprintln!("Failed to run: 'rustup toolchain list --verbose'");
        std::process::exit(result.status.code().unwrap());
    }

    let stdout = String::from_utf8(result.stdout).unwrap();
    if !stdout.lines().any(|line| line.trim().starts_with(name)) {
        eprintln!("The 'risc0' toolchain could not be found.");
        eprintln!("To install the risc0 toolchain, use rzup.");
        eprintln!("For example:");
        eprintln!("  curl -L https://risczero.com/install | bash");
        eprintln!("  rzup install");
        std::process::exit(-1);
    }
}

fn get_guest_dir() -> PathBuf {
    // Determine the output directory, in the target folder, for the guest binary.
    let out_dir_env = env::var_os("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir_env); // $ROOT/target/$profile/build/$crate/out
    out_dir
        .parent() // out
        .unwrap()
        .parent() // $crate
        .unwrap()
        .parent() // build
        .unwrap()
        .parent() // $profile
        .unwrap()
        .join("riscv-guest")
}

/// Embeds methods built for RISC-V for use by host-side dependencies.
/// Specify custom options for a guest package by defining its [GuestOptions].
/// See [embed_methods].
pub fn embed_methods_with_options(
    guest_pkg_to_options: HashMap<&str, GuestOptions>,
) -> Vec<GuestListEntry> {
    do_embed_methods(guest_pkg_to_options)
}

/// Build methods for RISC-V and embed minimal metadata - the `elf` name and path.
/// To embed the full elf, use [embed_methods_with_options].
///
/// Use this option if you wish to import the guest `elf` into your prover at runtime
/// rather than embedding it into the prover binary. This reduces build times for large
/// binaries, but makes prover initialization fallible.
///
/// Specify custom options for the package by defining its [GuestOptions].
pub fn embed_method_metadata_with_options(
    guest_pkg_to_options: HashMap<&str, GuestOptions>,
) -> Vec<MinGuestListEntry> {
    do_embed_methods(guest_pkg_to_options)
}

/// Embeds methods built for RISC-V for use by host-side dependencies.
/// Specify custom options for a guest package by defining its [GuestOptions].
/// See [embed_methods].
fn do_embed_methods<G: GuestBuilder>(
    mut guest_pkg_to_options: HashMap<&str, GuestOptions>,
) -> Vec<G> {
    let out_dir_env = env::var_os("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir_env); // $ROOT/target/$profile/build/$crate/out
    let guest_dir = get_guest_dir();
    // Read the cargo metadata for info from `[package.metadata.risc0]`.
    let pkg = current_package();
    let guest_packages = guest_packages(&pkg);
    let methods_path = out_dir.join("methods.rs");
    let mut methods_file = File::create(&methods_path).unwrap();

    // NOTE: Codegen of the guest list is gated behind the "guest-list" feature flag,
    // although the data structure are not, because when the `GuestListEntry` type
    // is referenced in the generated code, this requires `risc0-build` be declared
    // as a dependency of the methods crate.
    #[cfg(feature = "guest-list")]
    let mut guest_list_codegen = Vec::new();
    #[cfg(feature = "guest-list")]
    methods_file
        .write_all(b"use risc0_build::GuestListEntry;\n")
        .unwrap();

    if !is_skip_build() {
        detect_toolchain(RUSTUP_TOOLCHAIN_NAME);
    }

    let mut guest_list = vec![];
    for guest_pkg in guest_packages {
        println!("Building guest package {}.{}", pkg.name, guest_pkg.name);

        let guest_embed_opts = guest_pkg_to_options
            .remove(guest_pkg.name.as_str())
            .unwrap_or_default();
        let guest_build_opts = GuestBuildOptions::from(guest_embed_opts)
            .with_metadata(GuestMetadata::from(&guest_pkg));

        let methods: Vec<G> = if let Some(ref docker_opts) = guest_build_opts.use_docker {
            let src_dir = docker_opts
                .root_dir
                .clone()
                .unwrap_or_else(|| std::env::current_dir().unwrap());
            build_guest_package_docker(
                guest_pkg.manifest_path.as_std_path(),
                &src_dir,
                &guest_build_opts,
            )
            .unwrap();
            guest_methods_docker(&guest_pkg, &guest_dir)
        } else {
            build_guest_package(&guest_pkg, &guest_dir, &guest_build_opts, None);
            guest_methods(&guest_pkg, &guest_dir, &guest_build_opts.features)
        };

        for method in methods {
            methods_file
                .write_all(method.codegen_consts().as_bytes())
                .unwrap();

            #[cfg(feature = "guest-list")]
            guest_list_codegen.push(method.codegen_list_entry());
            guest_list.push(method);
        }
    }

    // If the user provided options for a package that wasn't built, abort.
    if let Some(package) = guest_pkg_to_options.keys().next() {
        panic!(
            "Error: guest options were provided for package '{}' but the package was not built.",
            package
        );
    }

    #[cfg(feature = "guest-list")]
    methods_file
        .write_all(
            format!(
                "\npub const GUEST_LIST: &[{}] = &[{}];\n",
                std::any::type_name::<G>(),
                guest_list_codegen.join(",")
            )
            .as_bytes(),
        )
        .unwrap();

    // HACK: It's not particularly practical to figure out all the
    // files that all the guest crates transitively depend on.  So, we
    // want to run the guest "cargo build" command each time we build.
    //
    // Since we generate methods.rs each time we run, it will always
    // be changed.
    println!("cargo:rerun-if-changed={}", methods_path.display());
    guest_list
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
pub fn embed_methods() -> Vec<GuestListEntry> {
    embed_methods_with_options(HashMap::new())
}
