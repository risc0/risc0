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

pub mod cli;
pub mod errors;
pub mod extension;
pub mod repo;
pub mod toolchain;
pub mod utils;

use std::fs;

// use crate::utils::notify::info_msg;
use anyhow::{anyhow, Context, Result};

pub struct Rzup;

impl Rzup {
    pub fn version() -> &'static str {
        env!("CARGO_PKG_VERSION")
    }
    pub async fn update() -> Result<()> {
        // TODO
        Ok(())
    }

    pub fn uninstall() -> Result<()> {
        let cargo_bin_path = dirs::home_dir()
            .ok_or_else(|| anyhow!("Could not determine home directory"))?
            .join(".cargo/bin");

        let rzup_path = cargo_bin_path.join("rzup");

        if rzup_path.exists() {
            verbose_msg!(format!("Removing rzup from {}", rzup_path.display()));

            fs::remove_file(&rzup_path).context("Failed to remove rzup.")?;
            info_msg!(format!(
                "Uninstalled rzup from {}",
                cargo_bin_path.display()
            ));
        }
        Ok(())
    }
}
