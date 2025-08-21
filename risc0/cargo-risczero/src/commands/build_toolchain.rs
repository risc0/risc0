// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use anyhow::{Result, bail};
use clap::Parser;

/// `cargo risczero build-toolchain`
#[derive(Parser)]
pub struct BuildToolchainCommand {
    /// Version tag of the toolchain to build.
    #[arg(long)]
    version: Option<String>,
}

impl BuildToolchainCommand {
    pub fn run(&self) -> Result<()> {
        bail!("Run `rzup build rust` instead")
    }
}
