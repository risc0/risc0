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

use std::path::PathBuf;

use anyhow::{Context, Result};
use bonsai_sdk::{alpha::Client, API_KEY_ENVVAR, API_URL_ENVVAR};
use clap::Parser;
use risc0_build::BuildStatus;

use crate::commands::build_guest;

// TODO: How to use the version from risc0_zkvm?
// use risc0_zkvm::VERSION;
const VERSION: &str = "0.21.0";

/// `cargo risczero build`
///
/// NOTE: Requires Docker to be installed and running.
#[derive(Parser)]
pub struct DeployCommand {
    /// Location of the Cargo.toml for the guest code.
    ///
    /// This path is relative to the current directory.
    #[arg(long)]
    pub manifest_path: PathBuf,

    /// Feature flags passed to cargo.
    #[arg(long, value_delimiter = ',')]
    pub features: Vec<String>,

    /// API URL for Bonsai.
    #[arg(long)]
    pub api_url: Option<String>,

    /// API key for Bonsai.
    #[arg(long)]
    pub api_key: Option<String>,
}

impl DeployCommand {
    pub fn run(&self) -> Result<()> {
        // Instantiate client first to check for errors
        let client = self.get_client()?;
        self.deploy(client)?;

        Ok(())
    }

    fn deploy(&self, client: Client) -> Result<()> {
        // Ensure we have an up to date artifact before deploying
        if let BuildStatus::Skipped = build_guest::build(&self.manifest_path, &self.features)? {
            eprintln!("Build skipped, nothing to deploy.");
            return Ok(());
        }

        let src_dir = std::env::current_dir().unwrap();
        let root_pkg = risc0_build::get_root_pkg(&self.manifest_path, &src_dir)?;
        for target in risc0_build::get_targets(&root_pkg) {
            if target.is_bin() {
                let elf_path = risc0_build::get_elf_path(&src_dir, &root_pkg.name, &target.name);
                let elf = std::fs::read(&elf_path).with_context(|| {
                    format!("Failed to read ELF file at path: {}", elf_path.display())
                })?;
                let image_id = risc0_binfmt::compute_image_id(&elf)?;
                let image_id_hex = hex::encode(image_id);
                client.upload_img(&image_id_hex, elf)?;
                eprintln!(
                    "Uploaded ELF `{}` with image ID `{}`.",
                    target.name, image_id_hex
                );
            }
        }

        Ok(())
    }

    fn get_client(&self) -> Result<Client> {
        let (api_url, api_key) = self.get_client_envs()?;

        Client::from_parts(api_url, api_key, VERSION).context("Failed to create Bonsai client")
    }

    fn get_client_envs(&self) -> Result<(String, String)> {
        let api_url = if let Some(api_url) = self.api_url.clone() {
            api_url
        } else {
            std::env::var(API_URL_ENVVAR).context(format!(
                "Either `--api-url` or `{}` env var must be set",
                API_URL_ENVVAR
            ))?
        };

        let api_key = if let Some(api_key) = self.api_key.clone() {
            api_key
        } else {
            std::env::var(API_KEY_ENVVAR).context(format!(
                "Either `--api-key` or `{}` env var must be set",
                API_KEY_ENVVAR
            ))?
        };

        Ok((api_url, api_key))
    }
}
