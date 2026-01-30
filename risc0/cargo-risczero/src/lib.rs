// Copyright 2026 RISC Zero, Inc.
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

#![doc = include_str!("../README.md")]
#![deny(missing_docs)]
#![deny(rustdoc::broken_intra_doc_links)]
#![cfg_attr(docsrs, feature(doc_cfg))]

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
