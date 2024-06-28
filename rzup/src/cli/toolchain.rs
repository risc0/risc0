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

use crate::{toolchain::Toolchain, utils::find_installed_toolchains};
use anyhow::Result;
use clap::Subcommand;

#[derive(Debug, Subcommand)]
#[command(
    arg_required_else_help = true,
    subcommand_required = true,
    after_help = "Toolchain help"
)]
pub enum ToolchainSubcmd {
    /// List installed toolchains
    List,
    // TODO: Help message
    #[command(after_help = "TOOLCHAIN_INSTALLL_AFTER_HELP", aliases = ["add"])]
    Install {
        /// Toolchain name (rust or cpp)
        toolchain: String,
        /// Version tag of the toolchain to install
        version: Option<String>,
    },
    /// Uninstall a toolchain
    Uninstall {
        /// Toolchain name (rust or cpp)
        toolchain: String,
    },
    /// Build a toolchain
    Build {
        /// Toolchain name (rust or cpp)
        toolchain: String,
        /// Version tag of the toolchain to build
        version: Option<String>,
    },
}

pub async fn handler(subcmd: ToolchainSubcmd) -> Result<()> {
    match subcmd {
        ToolchainSubcmd::List => {
            let installed_toolchains = find_installed_toolchains()?;
            for toolchain in installed_toolchains {
                eprintln!("{toolchain}");
            }
            Ok(())
        }
        ToolchainSubcmd::Install { toolchain, version } => {
            let toolchain = toolchain.parse::<Toolchain>()?;
            toolchain.install(version.as_deref()).await
        }
        ToolchainSubcmd::Uninstall { toolchain } => {
            let toolchain = toolchain.parse::<Toolchain>()?;
            toolchain.unlink(toolchain.to_str()) // TODO: More specific uninstall - by name
        }
        ToolchainSubcmd::Build { toolchain, version } => {
            let toolchain = toolchain.parse::<Toolchain>()?;
            toolchain.build(version.as_deref())
        }
    }
}
