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

// This is based on cargo-wasix: https://github.com/wasix-org/cargo-wasix

use std::{
    path::{Path, PathBuf},
    process::Command,
};

use anyhow::{bail, Context, Result};
use clap::Parser;

use crate::{
    toolchain::{RustupToolchain, ToolchainRepo, RUSTUP_TOOLCHAIN_NAME, RUST_BRANCH},
    utils::{ensure_binary, CommandExt},
};

const CONFIG_TOML: &'static str = include_str!("config.toml");

/// `cargo risczero build-toolchain`
#[derive(Parser)]
pub struct BuildToolchain {
    /// Version tag of the toolchain to build.
    #[arg(long)]
    version: Option<String>,
}

/// Output info of a successful rust toolchain build.
pub struct RustBuildOutput {
    pub target: String,
    pub toolchain_dir: PathBuf,
}

impl BuildToolchain {
    pub fn run(&self) -> Result<()> {
        eprintln!("Building the riscv32im-risc0-zkvm-elf toolchain...");

        let root_dir = if let Ok(dir) = std::env::var("RISC0_BUILD_DIR") {
            PathBuf::from(dir)
        } else {
            dirs::home_dir()
                .context("Could not determine home dir. Set RISC0_BUILD_DIR env var!")?
                .join(".risc0")
        };
        let rust_dir = root_dir.join("rust");

        let tag = match &self.version {
            Some(tag) => tag,
            None => RUST_BRANCH,
        };
        let is_ci = std::env::var("CI").is_ok();
        if !is_ci {
            self.prepare_git_repo(ToolchainRepo::Rust.url(), tag, &rust_dir)?;
        }

        let out = self.build_toolchain(&rust_dir)?;
        let tools_bin_dir = out.toolchain_dir.parent().unwrap().join("stage2-tools-bin");
        let target_bin_dir = out.toolchain_dir.join("bin");

        for tool in tools_bin_dir.read_dir()? {
            let tool = tool?;
            let tool_name = tool.file_name();
            eprintln!("copy tool: {tool_name:?}");
            std::fs::copy(&tool.path(), target_bin_dir.join(tool_name))?;
        }

        RustupToolchain::link(RUSTUP_TOOLCHAIN_NAME, &out.toolchain_dir)?;

        Ok(())
    }

    /// Initialize a Git repo.
    ///
    /// Clone if it doesn't exist yet, otherwise update the branch/tag.
    fn prepare_git_repo(&self, source: &str, tag: &str, path: &Path) -> Result<()> {
        eprintln!("Preparing git repo {source} with tag/branch {tag}");
        ensure_binary("git", &["--version"])?;

        if !path.join(".git").is_dir() {
            Command::new("git")
                .args(["clone", source])
                .arg(path)
                .run_verbose()?;
        } else {
            // fetch to update tag names. Otherwise, new git tags will not appear.
            Command::new("git")
                .args(["fetch", "--all", "--prune"])
                .current_dir(path)
                .run_verbose()?;
        }

        Command::new("git")
            .args(["checkout", tag])
            .current_dir(path)
            .run_verbose()?;

        Command::new("git")
            .args(["reset", "--hard"])
            .current_dir(path)
            .run_verbose()?;

        Command::new("git")
            .args(["submodule", "update", "--init", "--recursive", "--progress"])
            .current_dir(path)
            .run_verbose()?;

        eprintln!("Git repo ready at {}", path.display());

        Ok(())
    }

    fn build_toolchain(&self, rust_dir: &Path) -> Result<RustBuildOutput> {
        std::fs::write(rust_dir.join("config.toml"), CONFIG_TOML)?;

        let has_python3 = Command::new("python3").arg("--version").run().is_ok();
        let python_cmd = if has_python3 { "python3" } else { "python" };

        // Stage 1.
        Command::new(python_cmd)
            .env(
                "CARGO_TARGET_RISCV32IM_RISC0_ZKVM_ELF_RUSTFLAGS",
                "-Cpasses=loweratomic",
            )
            .current_dir(&rust_dir)
            .args(["x.py", "build"])
            .run_verbose()?;

        // Stage 2.
        Command::new(python_cmd)
            .env(
                "CARGO_TARGET_RISCV32IM_RISC0_ZKVM_ELF_RUSTFLAGS",
                "-Cpasses=loweratomic",
            )
            .args(["x.py", "build", "--stage", "2"])
            .current_dir(&rust_dir)
            .run_verbose()?;

        eprintln!("Rust build complete!");

        for result in std::fs::read_dir(rust_dir.join("build"))? {
            let entry = result?;
            let toolchain_dir = entry.path().join("stage2");
            if toolchain_dir.is_dir() {
                let target = entry.file_name().to_string_lossy().to_string();
                return Ok(RustBuildOutput {
                    target,
                    toolchain_dir,
                });
            }
        }

        bail!("Could not find build directory")
    }
}
