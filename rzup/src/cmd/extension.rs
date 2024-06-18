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

use clap::Subcommand;

use crate::{
    extension::{install::InstallExtension, repo::ExtensionRepo},
    help,
};

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
            InstallExtension {
                version: Some(version),
                repo: ExtensionRepo::CargoRisczero,
            }
            .run()
            .expect("Error during cargo-risczero installation");
        }
        ExtensionSubcmd::Update => InstallExtension {
            repo: ExtensionRepo::CargoRisczero,
            version: Some("latest".to_string()),
        }
        .run()
        .expect("Error during cargo-risczero update"),
    }
}
