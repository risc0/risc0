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

use anyhow::{anyhow, Result};
use clap::Args;

use crate::{extension::Extension, toolchain::Toolchain};

#[derive(Debug, Args)]
pub struct InstallOpts {
    pub name: Option<String>,
    pub version: Option<String>,
    #[arg(short, long, help = "Force the update, ignoring existing directories")]
    pub force: bool,
}

pub async fn handler(opts: InstallOpts) -> Result<()> {
    match (opts.name.as_deref(), opts.version.as_deref()) {
        (None, None) => {
            // Install latest versions of everything
            Toolchain::Rust.install(None, opts.force).await?;
            Toolchain::Cpp.install(None, opts.force).await?;
            Extension::CargoRiscZero.install(None, opts.force).await?;
        }
        (None, Some(version)) => {
            // Install cargo-risczero with specified version (e.g. rzup install v1.0.5), and default toolchains
            Toolchain::Rust.install(None, opts.force).await?;
            Toolchain::Cpp.install(None, opts.force).await?;
            Extension::CargoRiscZero
                .install(Some(version), opts.force)
                .await?;
        }
        (Some(name), Some(version)) => {
            if let Ok(toolchain) = name.parse::<Toolchain>() {
                toolchain.install(Some(version), opts.force).await?
            } else if let Ok(extension) = name.parse::<Extension>() {
                extension.install(Some(version), opts.force).await?
            } else {
                return Err(anyhow!(
                    "invalid value '{}' for '<install>...' \n\nFor more information try '--help'.",
                    name
                ));
            }
        }
        (Some(name), None) => {
            if let Ok(toolchain) = name.parse::<Toolchain>() {
                toolchain.install(None, opts.force).await?;
            }
        }
    }
    Ok(())
}
