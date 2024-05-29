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

#![doc = include_str!("../README.md")]
#![deny(missing_docs)]
#![deny(rustdoc::broken_intra_doc_links)]
#![cfg_attr(docsrs, feature(doc_cfg, doc_auto_cfg))]

mod commands;
mod toolchain;
mod utils;

#[cfg(feature = "experimental")]
pub use self::commands::build::BuildSubcommand;

use clap::{Parser, Subcommand};

#[cfg(feature = "experimental")]
use self::commands::build::BuildCommand;
use self::commands::{
    build_guest::BuildGuest, build_toolchain::BuildToolchain, deploy::DeployCommand,
    install::Install, new::NewCommand, verify::VerifyCommand,
};

#[derive(Parser)]
#[command(name = "cargo", bin_name = "cargo")]
/// Main cargo command
pub enum Cargo {
    /// The `risczero` command
    Risczero(Risczero),
}

#[derive(clap::Args)]
#[command(author, version, about, long_about = None)]
/// `cargo risczero`
pub struct Risczero {
    #[clap(subcommand)]
    /// Which `risczero` command to run
    pub command: RisczeroCmd,
}

#[derive(Subcommand)]
/// Primary commands  of `cargo risczero`.
pub enum RisczeroCmd {
    /// Build guest code.
    Build(BuildGuest),
    /// Build the riscv32im-risc0-zkvm-elf toolchain.
    BuildToolchain(BuildToolchain),
    /// Install the riscv32im-risc0-zkvm-elf toolchain.
    Install(Install),
    /// Creates a new risczero starter project.
    New(NewCommand),
    /// Uploads the guest code to Bonsai.
    Deploy(DeployCommand),
    /// Verifies if a receipt is valid.
    Verify(VerifyCommand),
    /// Build a crate for RISC Zero.
    #[cfg(feature = "experimental")]
    BuildCrate(BuildCommand),
    /// Build and test a crate for RISC Zero.
    #[cfg(feature = "experimental")]
    Test(BuildCommand),
}

#[cfg(test)]
mod tests {
    use clap::CommandFactory;

    use super::*;

    #[test]
    fn verify_app() {
        Cargo::command().debug_assert();
    }
}
