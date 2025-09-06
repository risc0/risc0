// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#![doc = include_str!("../README.md")]
#![deny(missing_docs)]
#![deny(rustdoc::broken_intra_doc_links)]
#![cfg_attr(docsrs, feature(doc_cfg, doc_auto_cfg))]

mod commands;
mod utils;

use clap::{Args, Parser, Subcommand};

use self::commands::{
    bake::BakeCommand, build::BuildCommand, build_toolchain::BuildToolchainCommand,
    install::InstallCommand, new::NewCommand, verify::VerifyCommand,
};

#[derive(Parser)]
#[command(name = "cargo", bin_name = "cargo")]
/// Main cargo command
pub enum CargoCli {
    /// The `risczero` command
    Risczero(RisczeroArgs),
}

#[derive(Args)]
#[command(author, version, about, long_about = None)]
#[non_exhaustive]
/// `cargo risczero`
pub struct RisczeroArgs {
    #[command(subcommand)]
    /// Which `risczero` command to run
    pub command: Commands,
}

#[derive(Subcommand)]
#[non_exhaustive]
/// Primary commands  of `cargo risczero`.
pub enum Commands {
    /// Bake guest code.
    Bake(BakeCommand),

    /// Build guest code.
    Build(BuildCommand),

    /// Build the riscv32im-risc0-zkvm-elf toolchain.
    BuildToolchain(BuildToolchainCommand),

    /// Guest commands
    #[cfg(feature = "experimental")]
    Guest(commands::guest::GuestCommand),

    /// Install the riscv32im-risc0-zkvm-elf toolchain.
    Install(InstallCommand),

    /// Creates a new risczero starter project.
    New(NewCommand),

    /// Verifies if a receipt is valid.
    Verify(VerifyCommand),
}

#[cfg(test)]
mod tests {
    use clap::CommandFactory;

    use super::*;

    #[test]
    fn verify_app() {
        CargoCli::command().debug_assert();
    }
}
