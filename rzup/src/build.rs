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

use crate::components::Component;
use crate::env::Environment;
use crate::error::{Result, RzupError};
use crate::events::RzupEvent;
use crate::paths::Paths;
use semver::Version;

use std::path::{Path, PathBuf};
use std::process::Command;

const CONFIG_TOML: &str = include_str!("rust-toolchain-build-config.toml");

pub fn run_command(
    program: &str,
    args: &[&str],
    current_dir: Option<&Path>,
    env: &[(&str, &str)],
) -> Result<String> {
    let mut cmd = Command::new(program);
    cmd.args(args);
    cmd.envs(env.iter().copied());
    if let Some(path) = current_dir {
        cmd.current_dir(path);
    }
    let output = cmd.output()?;
    if !output.status.success() {
        let cmd_str =
            Vec::from_iter(std::iter::once(program).chain(args.iter().copied())).join(" ");
        return Err(RzupError::Other(format!(
            "Process `{cmd_str}` failed with status {}\n\
            stodout: {}\n\
            stderr: {}",
            &output.status,
            String::from_utf8_lossy(&output.stdout),
            String::from_utf8_lossy(&output.stderr)
        )));
    }
    String::from_utf8(output.stdout).map_err(|e| RzupError::Other(e.to_string()))
}

fn git_clone(src: &str, dest: &Path) -> Result<()> {
    run_command(
        "git",
        &[
            "clone",
            "--recurse-submodules",
            src,
            dest.to_str()
                .ok_or_else(|| RzupError::Other("non-UTF8 path".into()))?,
        ],
        None,
        &[],
    )?;
    Ok(())
}

fn git_checkout(path: &Path, tag_or_commit: &str) -> Result<()> {
    run_command("git", &["checkout", tag_or_commit], Some(path), &[])?;
    Ok(())
}

fn git_fetch(path: &Path) -> Result<()> {
    run_command("git", &["fetch", "--all", "--prune"], Some(path), &[])?;
    Ok(())
}

fn git_reset_hard(path: &Path) -> Result<()> {
    run_command("git", &["reset", "--hard"], Some(path), &[])?;
    Ok(())
}

fn git_submodule_update(path: &Path) -> Result<()> {
    run_command(
        "git",
        &["submodule", "update", "--init", "--recursive"],
        Some(path),
        &[],
    )?;
    Ok(())
}

pub fn git_short_rev_parse(path: &Path, tag: &str) -> Result<String> {
    Ok(
        run_command("git", &["rev-parse", "--short", tag], Some(path), &[])?
            .trim()
            .into(),
    )
}

fn find_build_directories(build_dir: &Path) -> Result<(PathBuf, PathBuf)> {
    if !build_dir.exists() {
        return Err(RzupError::Other(
            "failed to find Rust toolchain build directory".into(),
        ));
    }

    for entry in std::fs::read_dir(build_dir)? {
        let entry = entry?;
        let dir1 = entry.path().join("stage2");
        let dir2 = entry.path().join("stage2-tools-bin");
        if dir1.is_dir() && dir2.is_dir() && dir1.join("bin").is_dir() {
            return Ok((dir1, dir2));
        }
    }
    Err(RzupError::Other(
        "failed to find Rust toolchain stage2 build directories".into(),
    ))
}

pub fn build_rust_toolchain(
    env: &Environment,
    repo_url: &str,
    tag_or_commit: &str,
) -> Result<Version> {
    env.emit(RzupEvent::BuildingRustToolchain);

    env.emit(RzupEvent::BuildingRustToolchainUpdate {
        message: "cloning git repository".into(),
    });

    let repo_dir = env.tmp_dir().join("build-rust-toolchain");

    if !repo_dir.join(".git").exists() {
        git_clone(repo_url, &repo_dir)?;
    } else {
        git_fetch(&repo_dir)?;
    }
    git_checkout(&repo_dir, tag_or_commit)?;
    git_reset_hard(&repo_dir)?;
    git_submodule_update(&repo_dir)?;

    let commit = git_short_rev_parse(&repo_dir, "HEAD")?;

    let version_str = std::fs::read_to_string(repo_dir.join("src/version")).map_err(|e| {
        RzupError::Other(format!("failed to read Rust version from repository: {e}"))
    })?;
    let mut version = Version::parse(version_str.trim())?;
    version.build = semver::BuildMetadata::new(&commit).unwrap();

    let dest_dir = Paths::get_version_dir(env, &Component::RustToolchain, &version);
    if dest_dir.exists() {
        return Err(RzupError::Other(format!(
            "Rust toolchain version {version} already installed"
        )));
    }

    std::fs::write(repo_dir.join("config.toml"), CONFIG_TOML)?;

    env.emit(RzupEvent::BuildingRustToolchainUpdate {
        message: "./x build".into(),
    });

    run_command(
        "./x",
        &["build"],
        Some(&repo_dir),
        &[(
            "CARGO_TARGET_RISCV32IM_RISC0_ZKVM_ELF_RUSTFLAGS",
            "-Cpasses=loweratomic",
        )],
    )
    .map_err(|e| RzupError::Other(format!("failed to run Rust toolchain build: {e}")))?;

    env.emit(RzupEvent::BuildingRustToolchainUpdate {
        message: "./x build --stage 2".into(),
    });

    run_command(
        "./x",
        &["build", "--stage", "2"],
        Some(&repo_dir),
        &[(
            "CARGO_TARGET_RISCV32IM_RISC0_ZKVM_ELF_RUSTFLAGS",
            "-Cpasses=loweratomic",
        )],
    )
    .map_err(|e| RzupError::Other(format!("failed to run Rust toolchain build --stage 2: {e}")))?;

    env.emit(RzupEvent::BuildingRustToolchainUpdate {
        message: "installing".into(),
    });

    if let Some(parent) = dest_dir.parent() {
        std::fs::create_dir_all(parent)?;
    }

    let (stage2, stage2_tools) = find_build_directories(&repo_dir.join("build"))?;
    std::fs::rename(stage2, &dest_dir)?;

    for tool in std::fs::read_dir(stage2_tools)? {
        let tool = tool?;
        std::fs::rename(tool.path(), dest_dir.join("bin").join(tool.file_name()))?;
    }

    env.emit(RzupEvent::DoneBuildingRustToolchain {
        version: version.to_string(),
    });

    Ok(version)
}
