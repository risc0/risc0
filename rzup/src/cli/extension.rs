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

use crate::extension::Extension;
use anyhow::Result;
use clap::Subcommand;

#[derive(Debug, Subcommand)]
#[command(
    arg_required_else_help = true,
    subcommand_required = true,
    after_help = "EXTENSION help"
)]
pub enum ExtensionSubcmd {
    List,
    #[command(aliases = ["add"])]
    Install {
        extension: Extension,
        version: Option<String>,
    },
    Uninstall,
    Use,
}

pub async fn handler(subcmd: ExtensionSubcmd) -> Result<()> {
    match subcmd {
        ExtensionSubcmd::Install { extension, version } => {
            extension.install(version.as_deref()).await
        }
        _ => todo!(),
    }
}
