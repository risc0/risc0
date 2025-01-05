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
        Commands::Datasheet(cmd) => cmd.run(),
        Commands::Deploy(cmd) => cmd.run(),
        #[cfg(feature = "experimental")]
        Commands::Guest(cmd) => cmd.run(),
        Commands::Install(cmd) => cmd.run(),
        Commands::New(cmd) => cmd.run(),
        Commands::Verify(cmd) => cmd.run(),
        _ => unreachable!(),
    }
}
