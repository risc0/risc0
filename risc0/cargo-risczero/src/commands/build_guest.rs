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

use anyhow::Result;
use bonsai_sdk::alpha::Client;
use clap::Parser;
use risc0_build::get_elf_path;

/// `cargo risczero build`
#[derive(Parser)]
pub struct BuildGuest {
    /// Location of the Cargo.toml for the guest code.
    ///
    /// This path is relative to the current directory.
    #[arg(long)]
    pub manifest_path: PathBuf,

    /// Feature flags passed to cargo.
    #[arg(long, value_delimiter = ',')]
    pub features: Vec<String>,

    /// Sends the guest code to Bonsai.
    #[arg(short, long)]
    pub deploy: bool,
}

impl BuildGuest {
    pub fn run(&self) -> Result<()> {
        let src_dir = std::env::current_dir().unwrap();
        risc0_build::docker_build(&self.manifest_path, &src_dir, &self.features)?;

        if self.deploy {
            self.deploy()?;
        }

        Ok(())
    }

    pub fn deploy(&self) -> Result<()> {
        let src_dir = std::env::current_dir().unwrap();
        let root_pkg = risc0_build::export_root_pkg(&self.manifest_path, &src_dir)?;
        let client = Client::from_env(VERSION)?;
        for target in risc0_build::get_targets(&root_pkg) {
            if target.is_bin() {
                eprintln!("Deploying {} to Bonsai...", target.name);
                // TODO: proper handle pkg_name
                let pkg_name = &root_pkg.name;
                let elf_path = get_elf_path(&src_dir, pkg_name, &target.name);
                let elf = std::fs::read(&elf_path)?;
                let image_id = risc0_binfmt::compute_image_id(&elf)?;
                let image_id_hex = hex::encode(image_id);
                eprintln!("Uploading ELF with size {} bytes", elf.len());
                // TODO: Do we need to check for already uploaded image?
                client.upload_img(&image_id_hex, elf)?;
                eprintln!("Elf uploaded with image_id: {}", image_id_hex);
            }
        }

        Ok(())
    }
}

// TODO: move this to a shared location
// TODO: How can we use the version from the risc0 crate instead of hardcoding
// it here?
pub const VERSION: &str = "0.21.0";
