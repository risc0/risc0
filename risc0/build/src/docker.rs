// Copyright 2025 RISC Zero, Inc.
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

use std::{fs, path::Path, process::Command};

use anyhow::{bail, Context, Result};
use cargo_metadata::MetadataCommand;
use docker_generate::DockerFile;
use risc0_binfmt::{MemoryImage, Program};
use risc0_zkvm_platform::{memory::GUEST_MAX_MEM, PAGE_SIZE};
use tempfile::tempdir;

use crate::{config::GuestBuildOptions, encode_rust_flags, get_env_var, GuestOptions};

const DOCKER_IGNORE: &str = r#"
**/Dockerfile
**/.git
**/node_modules
**/target
**/tmp
"#;

/// The target directory for the ELF binaries.
pub const TARGET_DIR: &str = "target/riscv-guest/riscv32im-risc0-zkvm-elf/docker";

/// Indicates weather the build was successful or skipped.
pub enum BuildStatus {
    /// The build was successful.
    Success,
    /// The build was skipped.
    Skipped,
}

/// Build the package in the manifest path using a docker environment.
pub fn docker_build(
    manifest_path: &Path,
    src_dir: &Path,
    guest_opts: &GuestOptions,
) -> Result<BuildStatus> {
    build_guest_package_docker(manifest_path, src_dir, &guest_opts.clone().into())
}

pub(crate) fn build_guest_package_docker(
    manifest_path: &Path,
    src_dir: &Path,
    guest_opts: &GuestBuildOptions,
) -> Result<BuildStatus> {
    if !get_env_var("RISC0_SKIP_BUILD").is_empty() {
        eprintln!("Skipping build because RISC0_SKIP_BUILD is set");
        return Ok(BuildStatus::Skipped);
    }

    let manifest_path = manifest_path
        .canonicalize()
        .context(format!("manifest_path: {manifest_path:?}"))?;
    let src_dir = src_dir.canonicalize().context("src_dir")?;
    let meta = MetadataCommand::new()
        .manifest_path(&manifest_path)
        .exec()
        .context("Manifest not found")?;
    let root_pkg = meta.root_package().context("Failed to parse Cargo.toml")?;
    let pkg_name = &root_pkg.name;

    eprintln!("Docker context: {src_dir:?}");
    eprintln!("Building ELF binaries in {pkg_name} for riscv32im-risc0-zkvm-elf target...");

    if !Command::new("docker")
        .arg("--version")
        .status()
        .context("Could not find or execute docker")?
        .success()
    {
        bail!("`docker --version` failed");
    }

    if let Err(err) = check_cargo_lock(&manifest_path) {
        eprintln!("{err}");
    }

    let pkg_name = pkg_name.replace('-', "_");
    {
        let temp_dir = tempdir()?;
        let temp_path = temp_dir.path();
        let rel_manifest_path = manifest_path.strip_prefix(&src_dir)?;
        create_dockerfile(rel_manifest_path, temp_path, pkg_name.as_str(), guest_opts)?;
        build(&src_dir, temp_path)?;
    }
    println!("ELFs ready at:");

    let target_dir = src_dir.join(TARGET_DIR);
    for target in root_pkg.targets.iter().filter(|t| t.is_bin()) {
        let elf_path = target_dir.join(&pkg_name).join(&target.name);
        let image_id = compute_image_id(&elf_path)?;
        let rel_elf_path = Path::new(TARGET_DIR).join(&pkg_name).join(&target.name);
        println!("ImageID: {} - {:?}", image_id, rel_elf_path);
    }

    Ok(BuildStatus::Success)
}

/// Create the dockerfile.
///
/// Overwrites if a dockerfile already exists.
fn create_dockerfile(
    manifest_path: &Path,
    temp_dir: &Path,
    pkg_name: &str,
    guest_opts: &GuestBuildOptions,
) -> Result<()> {
    let manifest_env = &[("CARGO_MANIFEST_PATH", manifest_path.to_str().unwrap())];
    let encoded_rust_flags = encode_rust_flags(
        &guest_opts
            .rustc_flags
            .iter()
            .map(|s| s.as_str())
            .collect::<Vec<_>>(),
    );
    let rustflags_env = &[("CARGO_ENCODED_RUSTFLAGS", encoded_rust_flags.as_str())];

    let common_args = vec![
        "--locked",
        "--target",
        "riscv32im-risc0-zkvm-elf",
        "--manifest-path",
        "$CARGO_MANIFEST_PATH",
    ];

    let mut build_args = common_args.clone();
    let features_str = guest_opts.features.join(",");
    if !guest_opts.features.is_empty() {
        build_args.push("--features");
        build_args.push(&features_str);
    }

    let fetch_cmd = [&["cargo", "+risc0", "fetch"], common_args.as_slice()]
        .concat()
        .join(" ");
    let build_cmd = [
        &["cargo", "+risc0", "build", "--release"],
        build_args.as_slice(),
    ]
    .concat()
    .join(" ");

    let mut build = DockerFile::new()
        .from_alias("build", "risczero/risc0-guest-builder:r0.1.81.0")
        .workdir("/src")
        .copy(".", ".")
        .env(manifest_env)
        .env(rustflags_env)
        .env(&[("CARGO_TARGET_DIR", "target")]);

    #[cfg(feature = "unstable")]
    {
        build = build.env(&[("RISC0_FEATURE_bigint2", "")]);
    }

    build = build
        .env(&[(
            "CC_riscv32im_risc0_zkvm_elf",
            "/root/.local/share/cargo-risczero/cpp/bin/riscv32-unknown-elf-gcc",
        )])
        .env(&[("CFLAGS_riscv32im_risc0_zkvm_elf", "-march=rv32im -nostdlib")])
        // Fetching separately allows docker to cache the downloads, assuming the Cargo.lock
        // doesn't change.
        .run(&fetch_cmd)
        .run(&build_cmd);

    let out_dir = format!("/{pkg_name}");
    let binary = DockerFile::new()
        .comment("export stage")
        .from_alias("export", "scratch")
        .copy_from(
            "build",
            "/src/target/riscv32im-risc0-zkvm-elf/release",
            out_dir.as_str(),
        );

    let file = DockerFile::new().dockerfile(build).dockerfile(binary);
    fs::write(temp_dir.join("Dockerfile"), file.to_string())?;
    fs::write(temp_dir.join("Dockerfile.dockerignore"), DOCKER_IGNORE)?;

    Ok(())
}

/// Build the dockerfile and outputs the ELF.
///
/// Overwrites if an ELF with the same name already exists.
fn build(src_dir: &Path, temp_dir: &Path) -> Result<()> {
    let target_dir = src_dir.join(TARGET_DIR);
    let target_dir = target_dir.to_str().unwrap();
    if Command::new("docker")
        .arg("build")
        .arg(format!("--output={target_dir}"))
        .arg("-f")
        .arg(temp_dir.join("Dockerfile"))
        .arg(src_dir)
        .status()
        .context("docker failed to execute")?
        .success()
    {
        Ok(())
    } else {
        Err(anyhow::anyhow!("docker build failed"))
    }
}

fn check_cargo_lock(manifest_path: &Path) -> Result<()> {
    let lock_file = manifest_path
        .parent()
        .context("invalid manifest path")?
        .join("Cargo.lock");
    fs::metadata(lock_file.clone()).context(format!(
        "Cargo.lock not found in path {}",
        lock_file.display()
    ))?;
    Ok(())
}

/// Compute the image ID for a given ELF.
fn compute_image_id(elf_path: &Path) -> Result<String> {
    let elf = fs::read(elf_path)?;
    let program = Program::load_elf(&elf, GUEST_MAX_MEM as u32).context("unable to load elf")?;
    let image =
        MemoryImage::new(&program, PAGE_SIZE as u32).context("unable to create memory image")?;
    Ok(image.compute_id().to_string())
}

// requires Docker to be installed
#[cfg(feature = "docker")]
#[cfg(test)]
mod test {
    use std::path::Path;

    use super::{build_guest_package_docker, TARGET_DIR};
    use crate::config::GuestBuildOptions;

    const SRC_DIR: &str = "../..";

    fn build(manifest_path: &str) {
        let src_dir = Path::new(SRC_DIR);
        let manifest_path = Path::new(manifest_path);
        build_guest_package_docker(manifest_path, src_dir, &GuestBuildOptions::default()).unwrap();
    }

    fn compare_image_id(bin_path: &str, expected: &str) {
        let src_dir = Path::new(SRC_DIR);
        let target_dir = src_dir.join(TARGET_DIR);
        let elf_path = target_dir.join(bin_path);
        let actual = super::compute_image_id(&elf_path).unwrap();
        assert_eq!(expected, actual);
    }

    // Test build reproducibility for risc0_zkvm_methods_guest.
    // If the code of the package or any of its dependencies change,
    // it may be required to recompute the expected image_ids.
    // For that, run:
    // `cargo run --bin cargo-risczero -- risczero build --manifest-path risc0/zkvm/methods/guest/Cargo.toml`
    #[test]
    fn test_reproducible_methods_guest() {
        build("../../risc0/zkvm/methods/guest/Cargo.toml");
        compare_image_id(
            "risc0_zkvm_methods_guest/hello_commit",
            "bc2b460e3e48208bda43a93a91a51bb66c8999ec38bd3778dd8438d76e01561e",
        );
    }
}
