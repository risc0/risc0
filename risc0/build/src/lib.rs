// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#![allow(clippy::needless_doctest_main)]
#![doc = include_str!("../README.md")]
#![deny(missing_docs)]
#![deny(rustdoc::broken_intra_doc_links)]
#![cfg_attr(docsrs, feature(doc_cfg))]

mod config;
mod docker;

use std::{
    borrow::Cow,
    collections::HashMap,
    default::Default,
    env,
    ffi::OsStr,
    fmt::Write as _,
    fs::{self, File},
    io::{BufRead, BufReader, Write},
    path::{Path, PathBuf},
    process::{Command, Stdio},
    str::FromStr,
};

use anyhow::{Context, Result, anyhow};
use cargo_metadata::{Message, MetadataCommand, Package};
use config::GuestMetadata;
use rayon::prelude::*;
use risc0_binfmt::{KERNEL_START_ADDR, ProgramBinary};
use risc0_zkp::core::digest::Digest;
use risc0_zkvm_platform::memory;
use serde::Deserialize;

use self::{config::GuestInfo, docker::build_guest_package_docker};

pub use self::{
    config::{
        DockerOptions, DockerOptionsBuilder, DockerOptionsBuilderError, GuestOptions,
        GuestOptionsBuilder, GuestOptionsBuilderError,
    },
    docker::{BuildStatus, TARGET_DIR, docker_build},
};

const RISC0_TARGET_TRIPLE: &str = "riscv32im-risc0-zkvm-elf";
const DEFAULT_DOCKER_TAG: &str = "r0.1.91.1";

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

trait GuestBuilder: Sized + Send {
    fn build(guest_info: &GuestInfo, name: &str, elf_path: &str) -> Result<Self>;

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
    fn build(_guest_info: &GuestInfo, name: &str, elf_path: &str) -> Result<Self> {
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

    /// The combined user ELF & kernel ELF guest binary
    pub elf: Cow<'static, [u8]>,

    /// The image id of the guest program.
    pub image_id: Digest,

    /// The path to the ELF binary
    pub path: Cow<'static, str>,
}

fn r0vm_image_id(path: &str, flag: &str) -> Result<Digest> {
    use hex::FromHex;
    let output = Command::new("r0vm")
        .env_remove("RUST_LOG")
        .args(["--elf", path, flag])
        .output()?;
    if output.status.success() {
        let stdout = String::from_utf8(output.stdout)?;
        let digest = stdout.trim();
        Ok(Digest::from_hex(digest).context("expecting a hex string")?)
    } else {
        let stderr = String::from_utf8(output.stderr)?;
        Err(anyhow!("{stderr}"))
    }
}

fn compute_image_id(elf: &[u8], elf_path: &str) -> Result<Digest> {
    Ok(match r0vm_image_id(elf_path, "--id") {
        Ok(image_id) => image_id,
        Err(err) => {
            tty_println(
                "Falling back to slow ImageID computation. Updating to the latest r0vm will speed this up.",
            );
            tty_println(&format!("  error: {err}"));
            risc0_binfmt::compute_image_id(elf)?
        }
    })
}

impl GuestBuilder for GuestListEntry {
    /// Builds the [GuestListEntry] by reading the ELF from disk, and calculating the associated
    /// image ID.
    fn build(guest_info: &GuestInfo, name: &str, elf_path: &str) -> Result<Self> {
        let mut elf = vec![];
        let mut elf_path = elf_path.to_owned();
        let mut image_id = Digest::default();
        let is_kernel = guest_info.metadata.kernel;

        if !is_skip_build() {
            if is_kernel {
                elf = std::fs::read(&elf_path)?;
            } else {
                let user_elf = std::fs::read(&elf_path)?;
                let kernel_elf = guest_info.options.kernel();
                let binary = ProgramBinary::new(&user_elf, &kernel_elf);
                elf = binary.encode();
                let combined_path = PathBuf::from_str(&(elf_path + ".bin"))?;
                std::fs::write(&combined_path, &elf)?;
                elf_path = combined_path.to_str().unwrap().to_owned();
                image_id = compute_image_id(&elf, &elf_path)?;
            }
        }

        Ok(Self {
            name: Cow::Owned(name.to_owned()),
            elf: Cow::Owned(elf),
            image_id,
            path: Cow::Owned(elf_path),
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

        let image_id = self.image_id.as_words();
        let elf = if is_skip_build() {
            "&[]".to_string()
        } else {
            format!("include_bytes!({:?})", self.path)
        };

        let mut str = String::new();

        writeln!(&mut str, "pub const {upper}_ELF: &[u8] = {elf};").unwrap();
        writeln!(&mut str, "pub const {upper}_PATH: &str = {:?};", self.path).unwrap();
        writeln!(&mut str, "pub const {upper}_ID: [u32; 8] = {image_id:?};").unwrap();

        str
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
    // Canonicalize the manifest directory specified by the user.
    let manifest_dir =
        fs::canonicalize(manifest_dir.as_ref()).expect("could not canonicalize manifest path");
    let manifest_path = manifest_dir.join("Cargo.toml");
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
        eprintln!("ERROR: No package found in {manifest_dir:?}");
        std::process::exit(-1);
    }
    if matching.len() > 1 {
        eprintln!("ERROR: Multiple packages found in {manifest_dir:?}",);
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
    let ret = env::var(name).unwrap_or_default();
    if let Some(pkg) = env::var_os("CARGO_PKG_NAME")
        && pkg != "cargo-risczero"
    {
        println!("cargo:rerun-if-env-changed={name}");
    }
    ret
}

/// Returns all methods associated with the given guest crate.
fn guest_methods<G: GuestBuilder>(
    pkg: &Package,
    target_dir: impl AsRef<Path>,
    guest_info: &GuestInfo,
    profile: &str,
) -> Vec<G> {
    pkg.targets
        .iter()
        .filter(|target| target.is_bin())
        .filter(|target| {
            target
                .required_features
                .iter()
                .all(|required_feature| guest_info.options.features.contains(required_feature))
        })
        .map(|target| {
            G::build(
                guest_info,
                &target.name,
                target_dir
                    .as_ref()
                    .join(RISC0_TARGET_TRIPLE)
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

fn cpp_toolchain() -> Option<PathBuf> {
    let rzup = rzup::Rzup::new().unwrap();
    let (version, path) = rzup
        .get_default_version(&rzup::Component::CppToolchain)
        .unwrap()?;
    println!("Using C++ toolchain version {version}");
    Some(path)
}

fn rust_toolchain() -> PathBuf {
    let rzup = rzup::Rzup::new().unwrap();
    let Some((version, path)) = rzup
        .get_default_version(&rzup::Component::RustToolchain)
        .unwrap()
    else {
        panic!("Risc Zero Rust toolchain not found. Try running `rzup install rust`");
    };
    println!("Using Rust toolchain version {version}");
    path
}

/// Creates a std::process::Command to execute the given cargo
/// command in an environment suitable for targeting the zkvm guest.
#[stability::unstable]
pub fn cargo_command(subcmd: &str, rustc_flags: &[String]) -> Command {
    let mut guest_info = GuestInfo::default();
    guest_info.metadata.rustc_flags = Some(rustc_flags.to_vec());
    cargo_command_internal(subcmd, &guest_info)
}

pub(crate) fn cargo_command_internal(subcmd: &str, guest_info: &GuestInfo) -> Command {
    let rustc = rust_toolchain().join("bin/rustc");
    println!("Using rustc: {}", rustc.display());

    let mut cmd = sanitized_cmd("cargo");
    let mut args = vec![subcmd, "--target", RISC0_TARGET_TRIPLE];

    if !get_env_var("RISC0_BUILD_LOCKED").is_empty() {
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

    let encoded_rust_flags = encode_rust_flags(&guest_info.metadata, false);

    if !cpp_toolchain_override() {
        if let Some(toolchain_path) = cpp_toolchain() {
            cmd.env("CC", toolchain_path.join("bin/riscv32-unknown-elf-gcc"));
        } else {
            // If you aren't compiling any C/C++ code, it might be just fine to not have a C++
            // toolchain installed, but if you are then your compilation will surely fail. To avoid
            // a potentially confusing error message, set the CC path to a bogus path that will
            // hopefully make the issue obvious.
            cmd.env(
                "CC",
                "/no_risc0_cpp_toolchain_installed_run_rzup_install_cpp",
            );
        }

        cmd.env("CFLAGS_riscv32im_risc0_zkvm_elf", "-march=rv32im -nostdlib");

        // Signal to dependencies, cryptography patches in particular, that the bigint2 zkVM
        // feature is available.
        // NOTE: This is no longer required when using an up to date version of risc0-bigint2.
        // It is kept to avoid breaking code that links older versions of that crate without cause.
        cmd.env("RISC0_FEATURE_bigint2", "");
    }

    cmd.env("RUSTC", rustc)
        .env("CARGO_ENCODED_RUSTFLAGS", encoded_rust_flags)
        .args(args);
    cmd
}

fn get_rust_toolchain_version() -> semver::Version {
    let rzup = rzup::Rzup::new().unwrap();
    let Some((version, _)) = rzup
        .get_default_version(&rzup::Component::RustToolchain)
        .unwrap()
    else {
        panic!("Risc Zero Rust toolchain not found. Try running `rzup install rust`");
    };
    version
}

/// Returns a string that can be set as the value of CARGO_ENCODED_RUSTFLAGS when compiling guests
pub(crate) fn encode_rust_flags(guest_meta: &GuestMetadata, escape_special_chars: bool) -> String {
    // llvm changed `loweratomic` to `lower-atomic`
    let lower_atomic = if get_rust_toolchain_version() > semver::Version::new(1, 81, 0) {
        "passes=lower-atomic"
    } else {
        "passes=loweratomic"
    };
    let rustc_flags = guest_meta.rustc_flags.clone().unwrap_or_default();
    let rustc_flags: Vec<_> = rustc_flags.iter().map(|s| s.as_str()).collect();
    let text_addr = if guest_meta.kernel {
        KERNEL_START_ADDR.0
    } else {
        memory::TEXT_START
    };
    [
        // Append other rust flags
        rustc_flags.as_slice(),
        &[
            // Replace atomic ops with nonatomic versions since the guest is single threaded.
            "-C",
            lower_atomic,
            // Specify where to start loading the program in
            // memory.  The clang linker understands the same
            // command line arguments as the GNU linker does; see
            // https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_mono/ld.html#SEC3
            // for details.
            "-C",
            &format!("link-arg=-Ttext={text_addr:#010x}"),
            // Apparently not having an entry point is only a linker warning(!), so
            // error out in this case.
            "-C",
            "link-arg=--fatal-warnings",
            "-C",
            "panic=abort",
            "--cfg",
            "getrandom_backend=\"custom\"",
        ],
    ]
    .concat()
    .iter()
    .map(|x| {
        if escape_special_chars {
            x.escape_default().to_string()
        } else {
            x.to_string()
        }
    })
    .collect::<Vec<String>>()
    .join("\x1f")
}

fn cpp_toolchain_override() -> bool {
    // detect if there's an attempt to override the Cpp toolchain.
    // Overriding the toolchain useful for troubleshooting crates.
    !get_env_var("CC_riscv32im_risc0_zkvm_elf").is_empty()
        || !get_env_var("CFLAGS_riscv32im_risc0_zkvm_elf").is_empty()
}

/// Builds a static library providing a rust runtime.
///
/// This can be used to build programs for the zkvm which don't depend on risc0_zkvm.
pub fn build_rust_runtime() -> String {
    build_rust_runtime_with_features(&[])
}

/// Builds a static library providing a rust runtime, with additional features given as arguments.
///
/// This can be used to build programs for the zkvm which don't depend on risc0_zkvm. Feature flags
/// given will be pass when building risc0-zkvm-platform.
pub fn build_rust_runtime_with_features(features: &[&str]) -> String {
    build_staticlib(
        "risc0-zkvm-platform",
        &[&["rust-runtime", "panic-handler", "entrypoint"], features].concat(),
    )
}

/// Builds a static library and returns the name of the resultant file.
fn build_staticlib(guest_pkg: &str, features: &[&str]) -> String {
    let guest_dir = get_guest_dir("static-lib", guest_pkg);

    let guest_info = GuestInfo::default();
    let mut cmd = cargo_command_internal("rustc", &guest_info);

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

    eprintln!("Building staticlib: {cmd:?}");

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
                eprint!("{msg}");
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
fn build_guest_package(pkg: &Package, target_dir: impl AsRef<Path>, guest_info: &GuestInfo) {
    if is_skip_build() {
        return;
    }

    let target_dir = target_dir.as_ref();
    fs::create_dir_all(target_dir).unwrap();

    let mut cmd = cargo_command_internal("build", guest_info);

    let features_str = guest_info.options.features.join(",");
    if !features_str.is_empty() {
        cmd.args(["--features", &features_str]);
    }

    cmd.args([
        "--manifest-path",
        pkg.manifest_path.as_str(),
        "--target-dir",
        target_dir.to_str().unwrap(),
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
        "{}: Starting build for {RISC0_TARGET_TRIPLE}",
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

fn get_out_dir() -> PathBuf {
    // This code is based on https://docs.rs/cxx-build/latest/src/cxx_build/target.rs.html#10-49

    if let Some(target_dir) = env::var_os("CARGO_TARGET_DIR").map(Into::<PathBuf>::into)
        && target_dir.is_absolute()
    {
        return target_dir.join("riscv-guest");
    }

    let mut dir: PathBuf = env::var_os("OUT_DIR").unwrap().into();
    loop {
        if dir.join(".rustc_info.json").exists()
            || dir.join("CACHEDIR.TAG").exists()
            || dir.file_name() == Some(OsStr::new("target"))
                && dir
                    .parent()
                    .is_some_and(|parent| parent.join("Cargo.toml").exists())
        {
            return dir.join("riscv-guest");
        }
        if dir.pop() {
            continue;
        }
        panic!("Cannot find cargo target dir location")
    }
}

fn get_guest_dir(host_pkg: impl AsRef<Path>, guest_pkg: impl AsRef<Path>) -> PathBuf {
    get_out_dir().join(host_pkg).join(guest_pkg)
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

struct GuestPackageWithOptions {
    name: String,
    pkg: Package,
    opts: GuestOptions,
    target_dir: PathBuf,
}

/// Embeds methods built for RISC-V for use by host-side dependencies.
/// Specify custom options for a guest package by defining its [GuestOptions].
/// See [embed_methods].
fn do_embed_methods<G: GuestBuilder>(mut guest_opts: HashMap<&str, GuestOptions>) -> Vec<G> {
    // Read the cargo metadata for info from `[package.metadata.risc0]`.
    let pkg = current_package();
    let guest_packages = guest_packages(&pkg);

    let mut pkg_opts = vec![];
    for guest_pkg in guest_packages {
        let guest_dir = get_guest_dir(&pkg.name, &guest_pkg.name);
        let opts = guest_opts
            .remove(guest_pkg.name.as_str())
            .unwrap_or_default();
        pkg_opts.push(GuestPackageWithOptions {
            name: format!("{}.{}", pkg.name, guest_pkg.name),
            pkg: guest_pkg,
            opts,
            target_dir: guest_dir,
        });
    }

    // If the user provided options for a package that wasn't built, abort.
    if let Some(package) = guest_opts.keys().next() {
        panic!(
            "Error: guest options were provided for package {package:?} but the package was not built."
        );
    }

    build_methods(&pkg_opts)
}

fn build_methods<G: GuestBuilder>(guest_packages: &[GuestPackageWithOptions]) -> Vec<G> {
    let out_dir_env = env::var_os("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir_env); // $ROOT/target/$profile/build/$crate/out

    let methods_path = out_dir.join("methods.rs");
    let mut methods_file = File::create(&methods_path).unwrap();

    let profile = if is_debug() { "debug" } else { "release" };

    let guest_list: Vec<G> = guest_packages
        .par_iter()
        .flat_map(|guest| {
            println!("Building guest package: {}", guest.name);

            let guest_info = GuestInfo {
                options: guest.opts.clone(),
                metadata: (&guest.pkg).into(),
            };

            if guest.opts.use_docker.is_some() {
                build_guest_package_docker(&guest.pkg, &guest.target_dir, &guest_info).unwrap();
                guest_methods(&guest.pkg, &guest.target_dir, &guest_info, "docker")
            } else {
                build_guest_package(&guest.pkg, &guest.target_dir, &guest_info);
                guest_methods(&guest.pkg, &guest.target_dir, &guest_info, profile)
            }
        })
        .collect();

    #[cfg(not(feature = "guest-list"))]
    for guest in guest_list.iter() {
        methods_file
            .write_all(guest.codegen_consts().as_bytes())
            .unwrap();
    }

    #[cfg(feature = "guest-list")]
    build_guest_list(&guest_list, methods_file);

    // HACK: It's not particularly practical to figure out all the
    // files that all the guest crates transitively depend on.  So, we
    // want to run the guest "cargo build" command each time we build.
    //
    // Since we generate methods.rs each time we run, it will always
    // be changed.
    println!("cargo:rerun-if-changed={}", methods_path.display());
    println!("cargo:rerun-if-env-changed=RISC0_GUEST_LOGFILE");

    guest_list
}

#[cfg(feature = "guest-list")]
fn build_guest_list<G: GuestBuilder>(guest_list: &[G], mut methods_file: File) {
    // NOTE: Codegen of the guest list is gated behind the "guest-list" feature flag,
    // although the data structure are not, because when the `GuestListEntry` type
    // is referenced in the generated code, this requires `risc0-build` be declared
    // as a dependency of the methods crate.

    // prefix
    methods_file
        .write_all(b"use risc0_build::GuestListEntry;\n")
        .unwrap();

    // body
    let mut guest_list_codegen = Vec::new();
    for method in guest_list.iter() {
        methods_file
            .write_all(method.codegen_consts().as_bytes())
            .unwrap();
        guest_list_codegen.push(method.codegen_list_entry());
    }

    // suffix
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

/// Build a guest package into the specified `target_dir` using the specified
/// `GuestOptions`.
pub fn build_package(
    pkg: &Package,
    target_dir: impl AsRef<Path>,
    options: GuestOptions,
) -> Result<Vec<GuestListEntry>> {
    println!("Building guest package: {}", pkg.name);

    let guest_info = GuestInfo {
        options: options.clone(),
        metadata: pkg.into(),
    };

    let profile = if is_debug() { "debug" } else { "release" };

    if options.use_docker.is_some() {
        build_guest_package_docker(pkg, target_dir.as_ref(), &guest_info)?;
        Ok(guest_methods(pkg, &target_dir, &guest_info, "docker"))
    } else {
        build_guest_package(pkg, &target_dir, &guest_info);
        Ok(guest_methods(pkg, &target_dir, &guest_info, profile))
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    const RUSTC_FLAGS: &[&str] = &[
        "--cfg",
        "foo=\"bar\"",
        "--cfg",
        "foo='bar'",
        "-C",
        "link-args=--fatal-warnings",
    ];

    #[test]
    fn encodes_rustc_flags() {
        let guest_meta = GuestMetadata {
            rustc_flags: Some(RUSTC_FLAGS.iter().map(ToString::to_string).collect()),
            ..Default::default()
        };
        let encoded = encode_rust_flags(&guest_meta, false);
        let expected = [
            "--cfg",
            "foo=\"bar\"",
            "--cfg",
            "foo='bar'",
            "-C",
            "link-args=--fatal-warnings",
        ]
        .join("\x1f");
        assert!(encoded.contains(&expected));
    }

    #[test]
    fn escapes_strings_when_encoding_when_requested() {
        let guest_meta = GuestMetadata {
            rustc_flags: Some(RUSTC_FLAGS.iter().map(ToString::to_string).collect()),
            ..Default::default()
        };
        let encoded = encode_rust_flags(&guest_meta, true);
        let expected = [
            "--cfg",
            "foo=\\\"bar\\\"",
            "--cfg",
            "foo=\\\'bar\\\'",
            "-C",
            "link-args=--fatal-warnings",
        ]
        .join("\x1f");
        assert!(encoded.contains(&expected));
    }
}
