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
    fs::{self, File},
    io::Write,
    path::PathBuf,
    process::Command,
};

use anyhow::{Context, Result};
use cargo_metadata::MetadataCommand;
use clap::Parser;
use docker_generate::DockerFile;
use risc0_zkvm::{sha::Digest, MemoryImage, Program, MEM_SIZE, PAGE_SIZE};
use risc0_zkvm_platform::memory;

use crate::utils::{ensure_binary, CommandExt};

const DOCKER_IGNORE: &str = r#"
**/elfs
**/target
**/Dockerfile
**/.git
"#;

/// `cargo risczero build-guest`
#[derive(Parser)]
pub struct BuildGuest {
    /// Location of the Cargo.toml of the guest code
    ///
    /// This path is relative to the current directory
    #[clap(value_parser, long)]
    pub manifest_path: String,
}

impl BuildGuest {
    pub fn run(&self) -> Result<()> {
        let meta = MetadataCommand::new()
            .manifest_path(self.manifest_path.as_str())
            .exec()?;
        let pkg_name = &meta
            .root_package()
            .context("failed to parse Cargo.toml")?
            .name;
        eprintln!("Building the riscv32im-risc0-zkvm-elf binary for {pkg_name}...");
        ensure_binary("docker", &["--version"])?;
        if let Err(err) = self.check_cargo_lock() {
            eprintln!("{err}");
        }
        let package_name = pkg_name.replace('-', "_");
        self.create_dockerfile(package_name.as_str())?;
        self.build()?;
        self.clean()?;

        let paths = fs::read_dir(&format!("./elfs/{package_name}/"))?;
        println!("ELFs ready at:");
        for path in paths {
            let entry = path.unwrap().path();
            println!("{} - ImageID: {}", entry.display(), self.image_id(&entry)?);
        }

        Ok(())
    }

    /// Create the dockerfile.
    ///
    /// Overwrites if a dockerfile already exists.
    fn create_dockerfile(&self, pkg_name: &str) -> Result<()> {
        let manifest_env = &[("CARGO_MANIFEST_PATH", self.manifest_path.as_str())];
        let pkg_env = &[("PKG_NAME", pkg_name)];
        let c_flags = format!(
            "-C passes=loweratomic -C link-arg=-Ttext=0x{:08X} -C link-arg=--fatal-warnings",
            memory::TEXT_START
        );
        let c_flags_env = &[("RUSTFLAGS", c_flags.as_str())];

        let build = DockerFile::new()
            .from_alias("build", "risczero/risc0-guest-builder:v0.17")
            .workdir("/src")
            .copy(".", ".")
            .env(manifest_env)
            .env(c_flags_env)
            .run(
                "cargo +risc0 fetch --target riscv32im-risc0-zkvm-elf --manifest-path $CARGO_MANIFEST_PATH --locked",
            )
            .run(
                "CARGO_TARGET_DIR=target \\\n\
                \tcargo +risc0 build \\\n\
                \t--locked \\\n\
                \t--release \\\n\
                \t--target riscv32im-risc0-zkvm-elf \\\n\
                \t--manifest-path $CARGO_MANIFEST_PATH")
            .run(r"find target/riscv32im-risc0-zkvm-elf/release -maxdepth 1 -type f -exec test -x {} \; -exec cp {} /tmp/ \;");

        let binary: DockerFile<'_> = DockerFile::new()
            .comment("binary stage")
            .from_alias("binary", "scratch")
            .env(pkg_env)
            .copy_from("build", "/tmp", "/$PKG_NAME");

        let file = DockerFile::new().dockerfile(build).dockerfile(binary);
        let mut dockerfile = File::create("Dockerfile")?;
        dockerfile.write_all(file.to_string().as_bytes())?;
        let mut dockerignore = File::create(".dockerignore")?;
        dockerignore.write_all(DOCKER_IGNORE.as_bytes())?;

        Ok(())
    }

    /// Build the dockerfile and ouputs the ELF.
    ///
    /// Overwrites if an ELF with the same name already exists.
    fn build(&self) -> Result<()> {
        Command::new("docker")
            .args(["build", "--output=elfs/", "--target=binary", "."])
            .run_verbose()?;

        Ok(())
    }

    /// Remove Dockerfile and .dockerignore files.
    fn clean(&self) -> Result<()> {
        Command::new("rm")
            .args(["Dockerfile", ".dockerignore"])
            .run_verbose()
    }

    fn check_cargo_lock(&self) -> Result<()> {
        let lock_file = PathBuf::from(&self.manifest_path)
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
    fn image_id(&self, elf_path: &PathBuf) -> Result<Digest> {
        let elf = fs::read(elf_path)?;
        let program = Program::load_elf(&elf, MEM_SIZE as u32).context("unable to load elf")?;
        let image = MemoryImage::new(&program, PAGE_SIZE as u32)
            .context("unable to create memory image")?;
        Ok(image.compute_id())
    }
}

#[cfg(test)]
mod test {
    use std::{env, path::Path};

    use super::BuildGuest;

    struct Tester {
        manifest_path: String,
        elf_path: String,
        expected_image_id: String,
    }

    impl Tester {
        fn run(&self) {
            env::set_current_dir("../../").unwrap();
            let builder = BuildGuest {
                manifest_path: self.manifest_path.clone(),
            };
            builder.run().unwrap();
            assert_eq!(
                builder
                    .image_id(&Path::new(&self.elf_path).to_path_buf())
                    .unwrap()
                    .to_string(),
                self.expected_image_id
            );
        }
    }
    #[test]
    #[ignore] // requires Docker to be installed
    fn test_reproducible_multiply_method() {
        let multiply_test = Tester {
            manifest_path: "examples/factors/methods/guest/Cargo.toml".to_string(),
            elf_path: "elfs/multiply/multiply".to_string(),
            expected_image_id: "9ee1612b0a7e270f8df248e47dc85d9908ff4c1e7df42f398a65ca878b57a23d"
                .to_string(),
        };
        multiply_test.run()
    }
}
