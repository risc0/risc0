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
use clap::Args;

use crate::{extension::Extension, toolchain::Toolchain};

#[derive(Debug, Default, Args)]
pub struct UpdateOpts {
    #[arg(
        help = "TOOLCHAIN ARG HELP", // TODO
        num_args = 1..,
    )]
    pub toolchain: Option<Toolchain>,
    #[arg(
        help = "NOPE", // TODO
        num_args = 1..,
    )]
    pub extension: Option<Extension>,
}

pub async fn handler(opts: UpdateOpts) -> Result<()> {
    // TODO: Check for installed component updates, then apply only iof applicable
    // If no specific toolchain or extension is provided, update all by default
    if opts.toolchain.is_none() && opts.extension.is_none() {
        Toolchain::Rust.install(None).await?;
        Toolchain::Cpp.install(None).await?;
        Extension::CargoRiscZero.install(None).await?;
    } else {
        // Update specific toolchain or extension if provided
        if let Some(toolchain) = opts.toolchain {
            toolchain.install(None).await?;
        }
        if let Some(extension) = opts.extension {
            extension.install(None).await?;
        }
    }
    Ok(())
}
