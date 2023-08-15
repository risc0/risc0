// Copyright 2023 RISC Zero, Inc.
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

mod bootstrap;
mod bootstrap_poseidon;
mod gen_receipt;
mod install;

use clap::{Parser, Subcommand};

use self::{
    bootstrap::Bootstrap, bootstrap_poseidon::BootstrapPoseidon, gen_receipt::GenReceipt,
    install::Install,
};

#[derive(Parser)]
struct Cli {
    #[command(subcommand)]
    cmd: Commands,
}

#[derive(Subcommand)]
enum Commands {
    Bootstrap(Bootstrap),
    BootstrapPoseidon(BootstrapPoseidon),
    GenReceipt(GenReceipt),
    Install(Install),
}

impl Commands {
    fn run(&self) {
        match self {
            Commands::Bootstrap(cmd) => cmd.run(),
            Commands::BootstrapPoseidon(cmd) => cmd.run(),
            Commands::Install(cmd) => cmd.run(),
            Commands::GenReceipt(cmd) => cmd.run(),
        }
    }
}

fn main() {
    Cli::parse().cmd.run();
}
