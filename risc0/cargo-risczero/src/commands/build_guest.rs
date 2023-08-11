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

use std::{env, fs::File, io::Write, process::Command};

use anyhow::{Context, Result};
use clap::Parser;
use docker_generate::DockerFile;

use crate::utils::CommandExt;

// const CONFIG_TOML: &'static str = include_str!("config.toml");
const DOCKER_IGNORE: &'static str = "**/target\n**/Dockerfile\n**/.git";
/// `cargo risczero build-guest`
#[derive(Parser)]
pub struct BuildGuest {}

impl BuildGuest {
    pub fn run(&self) -> Result<()> {
        eprintln!("Building the riscv32im-risc0-zkvm-elf guest...");

        self.create_dockerfile()

        // Ok(())
    }

    /// Create the dockerfile.
    ///
    /// Overwrites if a dockerfile already exists.
    fn create_dockerfile(&self) -> Result<()> {
        eprintln!("Creating Dockerfile");

        let current_dir = env::current_dir()?;
        let working_dir = current_dir
            .iter()
            .last()
            .context("invalid path.")?
            .to_str()
            .context("invalid path.")?;
        eprintln!("{}", working_dir);

        let src_env = &[("SRC", working_dir)];
        let manifest_env = &[(
            "CARGO_MANIFEST_PATH",
            "examples/factors/methods/guest/Cargo.toml",
        )];

        let build = DockerFile::new()
            .comment("build stage")
            .from_alias("build", "rust:1.71.1@sha256:6b5a53fef2818e28548be943a622bfc52d73920fe0f8784f4296227bca30cdf1")
            .workdir(&working_dir)
            .run("cargo install cargo-risczero")
            .run("cargo risczero install")
            .copy(".", ".")
            .env(src_env)
            .env(manifest_env)
            .run("ls")
            .run("cargo +risc0 fetch --target riscv32im-risc0-zkvm-elf --manifest-path $CARGO_MANIFEST_PATH --locked")
            .run(
                "CARGO_TARGET_DIR=target \\\n\
            \tcargo +risc0 build \\\n\
            \t--offline \\\n\
            \t--release \\\n\
            \t--target riscv32im-risc0-zkvm-elf \\\n\
            \t--manifest-path $CARGO_MANIFEST_PATH \\\n\
            \t&& find `target/riscv-guest/riscv32im-risc0-zkvm-elf/release` \\\n\
            \t-maxdepth 1 -type f -exec test -x {} \\; -exec cp {} /tmp/ \\;",
            );

        let binary: DockerFile<'_> = DockerFile::new()
            .comment("binary stage")
            .from_alias("binary", "scratch")
            .copy_from("build", "/tmp/", "/elfs");

        let file = DockerFile::new().dockerfile(build).dockerfile(binary);

        eprintln!("{}", file.to_string());
        let mut dockerfile = File::create("Dockerfile")?;
        dockerfile.write_all(file.to_string().as_bytes())?;

        let mut dockerignore = File::create(".dockerignore")?;
        dockerignore.write_all(DOCKER_IGNORE.as_bytes())?;

        eprintln!("Dockerfile created at {}", current_dir.display());

        // docker build --build-env SRC=$SRC --build-arg MANIFEST_PATH=$MANIFEST_PATH
        // --build-arg PACKAGE=$PACKAGE --ssh default --output=elfs --target=binaries .

        Command::new("docker")
            .args(["build", "--output=.", "--target=binary", "."])
            .run_verbose()?;

        Ok(())
    }
}
