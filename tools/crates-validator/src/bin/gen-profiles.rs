// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use anyhow::Result;
use clap::Parser;
use risc0_crates_validator::gen_profiles::{Args, GenProfiles};

use tracing_subscriber::EnvFilter;

#[tokio::main]
async fn main() -> Result<()> {
    tracing_subscriber::fmt()
        .with_env_filter(EnvFilter::from_default_env())
        .init();

    let args = Args::parse();

    GenProfiles::new(args)
        .read_profiles_config()?
        .download_database()
        .await?
        .process_database()?
        .filter_selected_crates()?
        .write_profile()?;

    Ok(())
}
