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

use crate::{r0vm::R0vm, toolchain::Toolchain};

#[derive(Debug, Default, Args)]
pub struct UpdateOpts {
    #[arg(
        help = "Specify the toolchain to update",
        num_args = 1..,
    )]
    pub toolchain: Option<Toolchain>,
    #[arg(help = "Update r0vm")]
    pub r0vm: bool,
    /// Force the update, ignoring existing installations and downloads
    #[arg(short, long)]
    pub force: bool,
}

pub async fn handler(opts: UpdateOpts) -> Result<()> {
    // Update all by default if no specific toolchain or extension is provided
    if opts.toolchain.is_none() && !opts.r0vm {
        Toolchain::Rust.install(None, opts.force).await?;
        Toolchain::Cpp.install(None, opts.force).await?;
        R0vm::install(None, opts.force).await?;
    } else {
        // Update specific toolchain or extension if provided
        if let Some(toolchain) = opts.toolchain {
            toolchain.install(None, opts.force).await?;
        }
        if opts.r0vm {
            R0vm::install(None, opts.force).await?;
        }
    }
    Ok(())
}
