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

use anyhow::Result;
use clap::Subcommand;
use reqwest::Client;

use crate::{cmd::check::fetch_latest_release_info, help};

use super::{check::GithubReleaseData, install::InstallCargoRisczero};

#[derive(Debug, Subcommand, Clone)]
pub enum ExtensionSubcmd {
    /// Use a specific cargo-risczero version
    #[command(aliases = ["install", "add"])]
    Use {
        #[arg(help = help::INSTALL_HELP)]
        version: String,
    },
    /// Check for cargo-risczero updates
    Check,
    /// Update cargo-risczero extension
    Update,
}

pub fn handle_extension(subcmd: ExtensionSubcmd) {
    match subcmd {
        ExtensionSubcmd::Use { version } => {
            InstallCargoRisczero {
                version: Some(version),
            }
            .run()
            .expect("Error during cargo-risczero installation");
        }
        ExtensionSubcmd::Check => {
            let cargo_risczero_info =
                get_latest_extension_info().expect("Error fetching latest cargo-risczero info");
            // TODO: Clean up and make pretty
            println!(
                "Latest cargo-risczero release: {} : ({})",
                cargo_risczero_info.tag_name, cargo_risczero_info.published_at
            );
        }
        ExtensionSubcmd::Update => InstallCargoRisczero {
            version: Some("latest".to_string()),
        }
        .run()
        .expect("Error during cargo-risczero update"),
    }
}

pub fn get_latest_extension_info() -> Result<GithubReleaseData> {
    let client = Client::builder().user_agent("rzup").build()?;

    let cargo_risczero_repo = "https://api.github.com/repos/risc0/risc0/releases/latest";

    let rt = tokio::runtime::Runtime::new()?;

    let cargo_risczero_data =
        rt.block_on(fetch_latest_release_info(&client, cargo_risczero_repo))?;

    Ok(cargo_risczero_data)
}
