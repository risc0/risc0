// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use anyhow::Result;
use cargo_risczero::{CargoCli, Commands};
use clap::Parser;
use tracing_subscriber::EnvFilter;

fn main() -> Result<()> {
    tracing_subscriber::fmt()
        .with_env_filter(EnvFilter::from_default_env())
        .init();

    let CargoCli::Risczero(args) = CargoCli::parse();
    match args.command {
        Commands::Bake(cmd) => cmd.run(),
        Commands::Build(cmd) => cmd.run(),
        Commands::BuildToolchain(cmd) => cmd.run(),
        #[cfg(feature = "experimental")]
        Commands::Guest(cmd) => cmd.run(),
        Commands::Install(cmd) => cmd.run(),
        Commands::New(cmd) => cmd.run(),
        Commands::Verify(cmd) => cmd.run(),
        _ => unreachable!(),
    }
}
