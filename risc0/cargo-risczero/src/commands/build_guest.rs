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
use clap::Parser;
use docker_generate::DockerFile;
use risc0_binfmt::{MemoryImage, Program};
use risc0_zkvm_platform::{
    memory::{MEM_SIZE, TEXT_START},
    PAGE_SIZE,
};
use tempfile::tempdir;

use crate::utils::{ensure_binary, CommandExt};

const DOCKER_IGNORE: &str = r#"
**/target
**/Dockerfile
**/.git
"#;

const TARGET_DIR: &str = "target/riscv-guest/riscv32im-risc0-zkvm-elf/docker";

/// `cargo risczero build`
#[derive(Parser)]
pub struct BuildGuest {
    /// Location of the Cargo.toml for the guest code.
    ///
    /// This path is relative to the current directory.
    #[arg(long)]
    pub manifest_path: PathBuf,
}

impl BuildGuest {
    pub fn run(&self) -> Result<()> {
        let meta = MetadataCommand::new()
            .manifest_path(&self.manifest_path)
            .exec()?;
        let root_pkg = meta.root_package().context("failed to parse Cargo.toml")?;
        let pkg_name = &root_pkg.name;

        eprintln!("Building ELF binaries in {pkg_name} for riscv32im-risc0-zkvm-elf target...");

        ensure_binary("docker", &["--version"])?;

        if let Err(err) = self.check_cargo_lock() {
            eprintln!("{err}");
        }

        let pkg_name = pkg_name.replace('-', "_");
        {
            let temp_dir = tempdir()?;
            let temp_path = temp_dir.path();
            self.create_dockerfile(temp_path, pkg_name.as_str())?;
            self.build(temp_path)?;
        }

        let target_dir = PathBuf::from(TARGET_DIR);
        println!("ELFs ready at:");

        for target in root_pkg.targets.iter() {
            if target.is_bin() {
                let elf_path = target_dir.join(&pkg_name).join(&target.name);
                let image_id = self.compute_image_id(&elf_path)?;
                println!("ImageID: {} - {:?}", image_id, elf_path);
            }
        }

        Ok(())
    }

    /// Create the dockerfile.
    ///
    /// Overwrites if a dockerfile already exists.
    fn create_dockerfile(&self, temp_dir: &Path, pkg_name: &str) -> Result<()> {
        let manifest_env = &[("CARGO_MANIFEST_PATH", self.manifest_path.to_str().unwrap())];
        let rustflags = format!(
            "-C passes=loweratomic -C link-arg=-Ttext=0x{TEXT_START:08X} -C link-arg=--fatal-warnings",
        );
        let rustflags_env = &[("RUSTFLAGS", rustflags.as_str())];

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
            .run(
                "cargo +risc0 build \
                    --locked \
                    --release \
                    --target riscv32im-risc0-zkvm-elf \
                    --manifest-path $CARGO_MANIFEST_PATH",
            );

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
    fn build(&self, temp_dir: &Path) -> Result<()> {
        Command::new("docker")
            .arg("build")
            .arg(format!("--output={TARGET_DIR}"))
            .arg("-f")
            .arg(temp_dir.join("Dockerfile"))
            .arg(".")
            .run_verbose()
    }

    fn check_cargo_lock(&self) -> Result<()> {
        let lock_file = self
            .manifest_path
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
    fn compute_image_id(&self, elf_path: &Path) -> Result<String> {
        let elf = fs::read(elf_path)?;
        let program = Program::load_elf(&elf, MEM_SIZE as u32).context("unable to load elf")?;
        let image = MemoryImage::new(&program, PAGE_SIZE as u32)
            .context("unable to create memory image")?;
        Ok(image.compute_id().to_string())
    }
}

// requires Docker to be installed
#[cfg(feature = "docker")]
#[cfg(test)]
mod test {
    use std::path::PathBuf;

    use super::{BuildGuest, TARGET_DIR};

    struct Tester {
        builder: BuildGuest,
    }

    impl Tester {
        fn new(manifest_path: &str) -> Self {
            std::env::set_current_dir("../../").unwrap();
            let builder = BuildGuest {
                manifest_path: PathBuf::from(manifest_path),
            };
            builder.run().unwrap();
            Self { builder }
        }

        fn compare_image_id(&self, bin_path: &str, expected: &str) {
            let target_dir = PathBuf::from(TARGET_DIR);
            let elf_path = target_dir.join(bin_path);
            let actual = self.builder.compute_image_id(&elf_path).unwrap();
            assert_eq!(expected, actual);
        }
    }

    // Test build reproducibility for risc0_zkvm_methods_guest.
    // If the code of the package or any of its dependencies change,
    // it may be required to recompute the expected image_ids.
    // For that, run:
    // `cargo risczero build --manifest-path risc0/zkvm/methods/guest/Cargo.toml`
    #[test]
    fn test_reproducible_methods_guest() {
        let tester = Tester::new("risc0/zkvm/methods/guest/Cargo.toml");
        tester.compare_image_id(
            "risc0_zkvm_methods_guest/multi_test",
            "aa593b59f897db9926bf90d3c252f01eb6ed805ea0ab5894ead20e18397fae08",
        );
        tester.compare_image_id(
            "risc0_zkvm_methods_guest/hello_commit",
            "c7c399c25ecf26b79e987ed060efce1f0836a594ad1059b138b6ed2f123dad38",
        );
        tester.compare_image_id(
            "risc0_zkvm_methods_guest/slice_io",
            "f5c6e9ed4296aff0db991f612794115010422465187a049ed72fb719ab94dcd9",
        );
    }
}
