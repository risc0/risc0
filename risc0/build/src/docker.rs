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
use cargo_metadata::Package;
use docker_generate::DockerFile;
use tempfile::tempdir;

use crate::{
    config::GuestInfo, encode_rust_flags, get_env_var, get_package, GuestOptions,
    RISC0_TARGET_TRIPLE,
};

const DOCKER_IGNORE: &str = r#"
**/Dockerfile
**/.git
**/node_modules
**/target
**/tmp
"#;

/// The target directory for the ELF binaries.
pub const TARGET_DIR: &str = "target/riscv-guest/riscv32im-risc0-zkvm-elf/docker";

/// Indicates whether the build was successful or skipped.
pub enum BuildStatus {
    /// The build was successful.
    Success,
    /// The build was skipped.
    Skipped,
}

/// Build the package in the manifest path using a docker environment.
pub fn docker_build(manifest_path: &Path, guest_opts: &GuestOptions) -> Result<BuildStatus> {
    let manifest_dir = manifest_path.parent().unwrap().canonicalize().unwrap();
    let pkg = get_package(manifest_dir);
    let src_dir = guest_opts.use_docker.clone().unwrap_or_default().root_dir();
    let guest_opts = guest_opts.clone();
    let guest_info = GuestInfo {
        options: guest_opts.clone(),
        metadata: (&pkg).into(),
    };
    let pkg_name = pkg.name.replace('-', "_");
    let target_dir = src_dir.join(TARGET_DIR).join(pkg_name);
    build_guest_package_docker(&pkg, &target_dir, &guest_info)
}

pub(crate) fn build_guest_package_docker(
    pkg: &Package,
    target_dir: impl AsRef<Path>,
    guest_info: &GuestInfo,
) -> Result<BuildStatus> {
    if !get_env_var("RISC0_SKIP_BUILD").is_empty() {
        eprintln!("Skipping build because RISC0_SKIP_BUILD is set");
        return Ok(BuildStatus::Skipped);
    }

    let src_dir = guest_info
        .options
        .use_docker
        .clone()
        .unwrap_or_default()
        .root_dir()
        .canonicalize()?;

    eprintln!("Docker context: {src_dir:?}");
    eprintln!(
        "Building ELF binaries in {} for {RISC0_TARGET_TRIPLE} target...",
        pkg.name
    );

    if !Command::new("docker")
        .arg("--version")
        .status()
        .context("Could not find or execute docker")?
        .success()
    {
        bail!("`docker --version` failed");
    }

    let manifest_path = pkg.manifest_path.as_std_path();
    if let Err(err) = check_cargo_lock(manifest_path) {
        eprintln!("{err}");
    }

    {
        let temp_dir = tempdir()?;
        let temp_path = temp_dir.path();
        let rel_manifest_path = manifest_path.strip_prefix(&src_dir)?;
        create_dockerfile(rel_manifest_path, temp_path, guest_info)?;
        let target_dir = target_dir.as_ref();
        let target_dir = target_dir.join(RISC0_TARGET_TRIPLE).join("docker");
        build(&src_dir, temp_path, &target_dir)?;
    }

    Ok(BuildStatus::Success)
}

/// Create the dockerfile.
///
/// Overwrites if a dockerfile already exists.
fn create_dockerfile(manifest_path: &Path, temp_dir: &Path, guest_info: &GuestInfo) -> Result<()> {
    let manifest_env = &[("CARGO_MANIFEST_PATH", manifest_path.to_str().unwrap())];
    let encoded_rust_flags = encode_rust_flags(&guest_info.metadata, true);
    let rustflags_env = &[("CARGO_ENCODED_RUSTFLAGS", encoded_rust_flags.as_str())];

    let common_args = vec![
        "--locked",
        "--target",
        RISC0_TARGET_TRIPLE,
        "--manifest-path",
        "$CARGO_MANIFEST_PATH",
    ];

    let mut build_args = common_args.clone();
    let features_str = guest_info.options.features.join(",");
    if !guest_info.options.features.is_empty() {
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

    let docker_opts = guest_info.options.use_docker.clone().unwrap_or_default();
    let docker_tag = format!(
        "risczero/risc0-guest-builder:{}",
        docker_opts.docker_container_tag()
    );

    let mut build = DockerFile::new()
        .from_alias("build", &docker_tag)
        .workdir("/src")
        .copy(".", ".")
        .env(manifest_env)
        .env(rustflags_env)
        .env(&[("CARGO_TARGET_DIR", "target")])
        .env(&[("RISC0_FEATURE_bigint2", "")])
        .env(&[(
            "CC_riscv32im_risc0_zkvm_elf",
            "/root/.risc0/cpp/bin/riscv32-unknown-elf-gcc",
        )])
        .env(&[("CFLAGS_riscv32im_risc0_zkvm_elf", "-march=rv32im -nostdlib")]);

    let docker_env = docker_opts.env();
    if !docker_env.is_empty() {
        build = build.env(&docker_env);
    }

    build = build
        // Fetching separately allows docker to cache the downloads, assuming the Cargo.lock
        // doesn't change.
        .run(&fetch_cmd)
        .run(&build_cmd);

    let src_dir = format!("/src/target/{RISC0_TARGET_TRIPLE}/release");
    let binary = DockerFile::new()
        .comment("export stage")
        .from_alias("export", "scratch")
        .copy_from("build", &src_dir, "/");

    let file = DockerFile::new().dockerfile(build).dockerfile(binary);
    fs::write(temp_dir.join("Dockerfile"), file.to_string())?;
    fs::write(temp_dir.join("Dockerfile.dockerignore"), DOCKER_IGNORE)?;

    Ok(())
}

/// Build the dockerfile and outputs the ELF.
///
/// Overwrites if an ELF with the same name already exists.
fn build(src_dir: &Path, temp_dir: &Path, target_dir: &Path) -> Result<()> {
    if Command::new("docker")
        .arg("build")
        .arg(format!("--output={}", target_dir.to_str().unwrap()))
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

// requires Docker to be installed
#[cfg(feature = "docker")]
#[cfg(test)]
mod test {
    use crate::{build_package, DockerOptionsBuilder, GuestListEntry, GuestOptionsBuilder};

    use super::*;

    const SRC_DIR: &str = "../..";

    fn build(target_dir: &Path, manifest_path: &str) -> Vec<GuestListEntry> {
        let src_dir = Path::new(SRC_DIR).to_path_buf();
        let manifest_path = Path::new(manifest_path);
        let manifest_dir = manifest_path.parent().unwrap().canonicalize().unwrap();
        let pkg = get_package(manifest_dir);
        let docker_opts = DockerOptionsBuilder::default()
            .root_dir(src_dir)
            .build()
            .unwrap();
        let guest_opts = GuestOptionsBuilder::default()
            .use_docker(docker_opts)
            .build()
            .unwrap();
        build_package(&pkg, target_dir, guest_opts).unwrap()
    }

    fn compare_image_id(guest_list: &[GuestListEntry], name: &str, expected: &str) {
        let guest = guest_list.iter().find(|x| x.name == name).unwrap();
        assert_eq!(expected, guest.image_id.to_string());
    }

    // Test build reproducibility for risc0_zkvm_methods_guest.
    // If the code of the package or any of its dependencies change,
    // it may be required to recompute the expected image_ids.
    // For that, run:
    // `cargo run --bin cargo-risczero -- risczero build --manifest-path risc0/zkvm/methods/guest/Cargo.toml`
    #[test]
    fn test_reproducible_methods_guest() {
        let temp_dir = tempdir().unwrap();
        let temp_path = temp_dir.path();
        let guest_list = build(temp_path, "../../risc0/zkvm/methods/guest/Cargo.toml");
        compare_image_id(
            &guest_list,
            "hello_commit",
            "f55820be6ad61c5e889868f7b65cd61034ed48fe9be8ec186f5a8fddde70f4b7",
        );
    }
}
