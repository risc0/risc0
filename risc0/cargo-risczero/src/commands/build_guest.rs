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

use std::path::{Path, PathBuf};

use anyhow::Result;
use clap::Parser;
use risc0_build::{BuildStatus, GuestOptions};

/// `cargo risczero build`
///
/// NOTE: Requires Docker to be installed and running.
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
}

impl BuildGuest {
    pub fn run(&self) -> Result<()> {
        build(
            &self.manifest_path,
            &GuestOptions {
                features: self.features.clone(),
                ..Default::default()
            },
        )?;
        Ok(())
    }
}

pub(crate) fn build(manifest_path: &Path, guest_options: &GuestOptions) -> Result<BuildStatus> {
    let src_dir = std::env::current_dir().unwrap();
    risc0_build::docker_build(manifest_path, &src_dir, guest_options)
}
