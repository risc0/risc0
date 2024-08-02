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

use crate::{cargo_risczero::CargoRisczero, toolchain::Toolchain};

#[derive(Debug, Args)]
pub struct InstallOpts {
    pub name: Option<String>,
    pub version: Option<String>,
    #[arg(short, long, help = "Force the update, ignoring existing directories")]
    pub force: bool,
}

pub async fn handler(opts: InstallOpts) -> Result<()> {
    if opts.name.is_none() {
        // Install all default
        Toolchain::Rust.install(None, opts.force).await?;
        Toolchain::Cpp.install(None, opts.force).await?;
        CargoRisczero::install(None, opts.force).await?;
    } else {
        let name = opts.name.unwrap();
        let version = opts.version.as_deref();
        if let Ok(toolchain) = name.parse::<Toolchain>() {
            toolchain.install(version, opts.force).await?
        } else if name.parse::<CargoRisczero>().is_ok() {
            CargoRisczero::install(version, opts.force).await?
        } else {
            return Err(anyhow!(
                "invalid value '{}' for '<install>...' \n\nFor more information try '--help'.",
                name
            ));
        }
    }
    Ok(())
}
