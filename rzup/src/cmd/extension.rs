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

use crate::{cmd::check::fetch_release_info, help};

use super::{install::GithubReleaseData, install::InstallCargoRisczero};

#[derive(Debug, Subcommand, Clone)]
pub enum ExtensionSubcmd {
    /// Use a specific cargo-risczero version
    #[command(aliases = ["install", "add"])]
    Use {
        #[arg(help = help::INSTALL_HELP)]
        version: String,
    },
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
        ExtensionSubcmd::Update => InstallCargoRisczero {
            version: Some("latest".to_string()),
        }
        .run()
        .expect("Error during cargo-risczero update"),
    }
}

pub fn get_extension_info(version: Option<&str>) -> Result<GithubReleaseData> {
    let client = Client::builder().user_agent("rzup").build()?;

    let base_url = "https://api.github.com/repos/risc0/risc0/releases";
    let url = match version {
        Some(tag) => format!("{}/tags/{}", base_url, tag),
        None => format!("{}/latest", base_url),
    };

    let release_data = fetch_release_info(&client, &url)?;

    Ok(release_data)
}
