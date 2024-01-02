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

// This is based on cargo-wasix: https://github.com/wasix-org/cargo-wasix

use std::{
    path::{Path, PathBuf},
    process::Command,
};

use anyhow::{bail, Context, Result};

use crate::utils::CommandExt;

/// Custom rust repository.
pub const RUST_REPO: &str = "https://github.com/risc0/rust.git";

/// Branch to use in the custom Rust repo.
pub const RUST_BRANCH: &str = "risc0";

/// The name of the rustup toolchain
pub const RUSTUP_TOOLCHAIN_NAME: &str = "risc0";

/// A rustup toolchain manager
#[derive(Clone, Debug)]
pub struct RustupToolchain {
    /// The name of the rustup toolchain
    pub name: String,

    /// The path of the rustup toolchain
    pub path: PathBuf,
}

impl RustupToolchain {
    /// Verify if the toolchain is present in rustup.
    ///
    /// Returns the path to the toolchain.
    fn find_by_name(name: &str) -> Result<Option<Self>, anyhow::Error> {
        let out = Command::new("rustup")
            .args(["toolchain", "list", "--verbose"])
            .capture_stdout()?;
        let path_raw = out
            .lines()
            .find(|line| line.trim().starts_with(name))
            .and_then(|line| line.strip_prefix(name))
            .map(|line| line.trim());

        if let Some(path) = path_raw {
            Ok(Some(Self {
                name: name.to_string(),
                path: path.into(),
            }))
        } else {
            Ok(None)
        }
    }

    /// Link the toolchain to a local directory via rustup.
    pub fn link(name: &str, dir: &Path) -> Result<Self> {
        eprintln!(
            "Activating rustup toolchain {} at {}...",
            name,
            dir.display()
        );

        // Small sanity check.
        #[cfg(not(target_os = "windows"))]
        let rustc_exe = "rustc";
        #[cfg(target_os = "windows")]
        let rustc_exe = "rustc.exe";

        let rustc_path = dir.join("bin").join(rustc_exe);
        if !rustc_path.is_file() {
            bail!(
                "Invalid toolchain directory: rustc executable not found at {}",
                rustc_path.display()
            );
        }

        // If already present, unlink first.
        // This is required because otherwise rustup can get in a buggy state.
        if Self::find_by_name(name)?.is_some() {
            Command::new("rustup")
                .args(["toolchain", "remove", name])
                .run()
                .context("Could not remove existing toolchain")?;
        }

        Command::new("rustup")
            .args(["toolchain", "link", name])
            .arg(dir)
            .run_verbose()
            .context("Could not link toolchain: rustup not installed?")?;

        eprintln!("rustup toolchain {name} was linked and is now available!");

        Ok(Self {
            name: name.to_string(),
            path: dir.into(),
        })
    }
}
