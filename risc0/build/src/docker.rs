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

use std::{
    fs,
    path::{Path, PathBuf},
    process::Command,
};

use anyhow::{Context, Result};
use cargo_metadata::MetadataCommand;
use docker_generate::DockerFile;
use risc0_binfmt::{MemoryImage, Program};
use risc0_zkvm_platform::{
    memory::{GUEST_MAX_MEM, TEXT_START},
    PAGE_SIZE,
};
use tempfile::tempdir;

const DOCKER_IGNORE: &str = r#"
**/target
**/Dockerfile
**/.git
"#;

const TARGET_DIR: &str = "target/riscv-guest/riscv32im-risc0-zkvm-elf/docker";

/// Build the package in the manifest path using a docker environment.
pub fn docker_build(manifest_path: &PathBuf, features: Vec<String>) -> Result<()> {
    let meta = MetadataCommand::new()
        .manifest_path(manifest_path)
        .exec()
        .context("Manifest not found")?;
    let root_pkg = meta.root_package().context("failed to parse Cargo.toml")?;
    let pkg_name = &root_pkg.name;

    eprintln!("Building ELF binaries in {pkg_name} for riscv32im-risc0-zkvm-elf target...");

    Command::new("docker")
        .args(&["--version"])
        .stdout(std::process::Stdio::piped())
        .output()
        .with_context(|| format!("Could not find or execute docker"))?;

    if let Err(err) = check_cargo_lock(manifest_path) {
        eprintln!("{err}");
    }

    let pkg_name = pkg_name.replace('-', "_");
    {
        let temp_dir = tempdir()?;
        let temp_path = temp_dir.path();
        create_dockerfile(manifest_path, temp_path, pkg_name.as_str(), features)?;
        build(temp_path)?;
    }
    let target_dir = PathBuf::from(TARGET_DIR);
    println!("ELFs ready at:");

    for target in root_pkg.targets.iter() {
        if target.is_bin() {
            let elf_path = target_dir.join(&pkg_name).join(&target.name);
            let image_id = compute_image_id(&elf_path)?;
            println!("ImageID: {} - {:?}", image_id, elf_path);
        }
    }

    Ok(())
}

/// Create the dockerfile.
///
/// Overwrites if a dockerfile already exists.
fn create_dockerfile(
    manifest_path: &PathBuf,
    temp_dir: &Path,
    pkg_name: &str,
    features: Vec<String>,
) -> Result<()> {
    let manifest_env = &[("CARGO_MANIFEST_PATH", manifest_path.to_str().unwrap())];
    let rustflags = format!(
        "-C passes=loweratomic -C link-arg=-Ttext=0x{TEXT_START:08X} -C link-arg=--fatal-warnings",
    );
    let rustflags_env = &[("RUSTFLAGS", rustflags.as_str())];
    let mut build_command = "cargo +risc0 build \
                    --locked \
                    --release \
                    --target riscv32im-risc0-zkvm-elf \
                    --manifest-path $CARGO_MANIFEST_PATH"
        .to_string();

    let features_str = features.join(",");
    if !features.is_empty() {
        build_command.push_str(format!(" --features {}", features_str).as_str());
    }
    let build = DockerFile::new()
        .from_alias("build", "risczero/risc0-guest-builder:v0.17")
        .workdir("/src")
        .copy(".", ".")
        .env(manifest_env)
        .env(rustflags_env)
        .env(&[("CARGO_TARGET_DIR", "target")])
        // Fetching separately allows docker to cache the downloads, assuming the Cargo.lock
        // doesn't change.
        .run(
            "cargo +risc0 fetch \
                    --locked \
                    --target riscv32im-risc0-zkvm-elf \
                    --manifest-path $CARGO_MANIFEST_PATH",
        )
        .run(&build_command);

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

/// Build the dockerfile and ouputs the ELF.
///
/// Overwrites if an ELF with the same name already exists.
fn build(temp_dir: &Path) -> Result<()> {
    Command::new("docker")
        .arg("build")
        .arg(format!("--output={TARGET_DIR}"))
        .arg("-f")
        .arg(temp_dir.join("Dockerfile"))
        .arg(".")
        .output()
        .context("docker build failed")?;
    Ok(())
}

fn check_cargo_lock(manifest_path: &PathBuf) -> Result<()> {
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
    use std::path::PathBuf;

    use super::docker_build;
    use super::TARGET_DIR;

    fn build(manifest_path: &str) {
        std::env::set_current_dir("../../").unwrap();
        self::docker_build(&PathBuf::from(manifest_path), vec![]).unwrap()
    }

    fn compare_image_id(bin_path: &str, expected: &str) {
        let target_dir = PathBuf::from(TARGET_DIR);
        let elf_path = target_dir.join(bin_path);
        let actual = super::compute_image_id(&elf_path).unwrap();
        assert_eq!(expected, actual);
    }

    // Test build reproducibility for risc0_zkvm_methods_guest.
    // If the code of the package or any of its dependencies change,
    // it may be required to recompute the expected image_ids.
    // For that, run:
    // `cargo risczero build --manifest-path risc0/zkvm/methods/guest/Cargo.toml`
    #[test]
    fn test_reproducible_methods_guest() {
        build("risc0/zkvm/methods/guest/Cargo.toml");
        compare_image_id(
            "risc0_zkvm_methods_guest/multi_test",
            "ad6dfae83cfc5b8be6f9fd3695b89f6d369d176e4201c0e57c2d2074948b741b",
        );
        compare_image_id(
            "risc0_zkvm_methods_guest/hello_commit",
            "54cc7ec42fc6500ab29f4d46746946ddffaf8c720b3836c6e3b7476be23a2ee1",
        );
        compare_image_id(
            "risc0_zkvm_methods_guest/slice_io",
            "162ef3155436485e5a77fc6d57a064a45d97cc666ac426bf49bb87749d7e4011",
        );
    }
}
