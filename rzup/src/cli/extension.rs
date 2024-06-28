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

use crate::{extension::Extension, utils::find_installed_extensions};
use anyhow::Result;
use clap::Subcommand;
use regex::Regex;

#[derive(Debug, Subcommand)]
#[command(
    arg_required_else_help = true,
    subcommand_required = true,
    after_help = "EXTENSION help"
)]
pub enum ExtensionSubcmd {
    /// List all installed extensions
    List,
    /// Install an extension (i.e cargo-risczero v1.0.1)
    #[command(aliases = ["add"])]
    Install {
        extension: Extension,
        version: Option<String>,
    },
    /// Use an installed extension version
    Use {
        extension: Extension,
        version: String,
    },
    /// Uninstall an installed extension
    Uninstall { extension: Extension },
}

pub async fn handler(subcmd: ExtensionSubcmd) -> Result<()> {
    match subcmd {
        ExtensionSubcmd::Install { extension, version } => {
            extension.install(version.as_deref()).await
        }
        ExtensionSubcmd::List => {
            let extensions = find_installed_extensions()?;
            for extension in extensions {
                eprintln!("{}", extension.file_name().unwrap().to_string_lossy());
            }
            Ok(())
        }
        ExtensionSubcmd::Use { extension, version } => {
            let extension_path = parse_extenstion_version(extension, version)?;
            extension.link(&extension_path)
        }
        ExtensionSubcmd::Uninstall { extension } => extension.unlink(),
    }
}

fn parse_extenstion_version(extension: Extension, version: String) -> Result<PathBuf> {
    let extensions = find_installed_extensions()?;
    let version_pattern = match extension {
        Extension::CargoRiscZero => {
            format!(r"^(v)?{}(?:-.+)?$", regex::escape(&version))
        }
    };

    let re = Regex::new(&version_pattern)?;

    for ext in extensions {
        if let Some(dir_name) = ext.file_name().and_then(|name| name.to_str()) {
            if re.is_match(dir_name) {
                return Ok(ext);
            }
        }
    }
    Err(anyhow::anyhow!(
        "No matching directory found for version {}",
        version
    ))
}
