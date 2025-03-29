// Copyright 2025 RISC Zero, Inc.
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

#[cfg(feature = "zkvm")]
mod bootstrap;
#[cfg(feature = "zkvm")]
mod bootstrap_groth16;
mod bootstrap_poseidon;
mod bootstrap_protos;
#[cfg(feature = "zkvm")]
mod gen_receipt;
mod install;
mod semver_checks;
mod update_lock_files;

use clap::{Parser, Subcommand};

#[cfg(feature = "zkvm")]
use self::{bootstrap::Bootstrap, bootstrap_groth16::BootstrapGroth16, gen_receipt::GenReceipt};
use self::{
    bootstrap_poseidon::BootstrapPoseidon, bootstrap_protos::BootstrapProtos, install::Install,
    semver_checks::SemverChecks, update_lock_files::UpdateLockFiles,
};

#[derive(Parser)]
struct Cli {
    #[command(subcommand)]
    cmd: Commands,
}

#[derive(Subcommand)]
enum Commands {
    #[cfg(feature = "zkvm")]
    Bootstrap(Bootstrap),
    #[cfg(feature = "zkvm")]
    BootstrapGroth16(BootstrapGroth16),
    BootstrapPoseidon(BootstrapPoseidon),
    BootstrapProtos(BootstrapProtos),
    #[cfg(feature = "zkvm")]
    GenReceipt(GenReceipt),
    Install(Install),
    SemverChecks(SemverChecks),
    UpdateLockFiles(UpdateLockFiles),
}

impl Commands {
    fn run(&self) {
        match self {
            #[cfg(feature = "zkvm")]
            Commands::Bootstrap(cmd) => cmd.run(),
            #[cfg(feature = "zkvm")]
            Commands::BootstrapGroth16(cmd) => cmd.run(),
            Commands::BootstrapPoseidon(cmd) => cmd.run(),
            Commands::BootstrapProtos(cmd) => cmd.run(),
            Commands::Install(cmd) => cmd.run(),
            #[cfg(feature = "zkvm")]
            Commands::GenReceipt(cmd) => cmd.run(),
            Commands::SemverChecks(cmd) => cmd.run(),
            Commands::UpdateLockFiles(cmd) => cmd.run(),
        }
    }
}

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();

    Cli::parse().cmd.run();
}
