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
#[cfg(feature = "experimental")]
use cargo_risczero::BuildSubcommand;
use cargo_risczero::{Cargo, RisczeroCmd};
use clap::Parser;
use tracing_subscriber::EnvFilter;

fn main() -> Result<()> {
    tracing_subscriber::fmt()
        .with_env_filter(EnvFilter::from_default_env())
        .init();

    let Cargo::Risczero(args) = Cargo::parse();
    match args.command {
        RisczeroCmd::Build(cmd) => cmd.run(),
        RisczeroCmd::BuildToolchain(cmd) => cmd.run(),
        RisczeroCmd::Install(cmd) => cmd.run(),
        RisczeroCmd::New(cmd) => cmd.run(),
        RisczeroCmd::Deploy(cmd) => cmd.run(),
        RisczeroCmd::Verify(cmd) => cmd.run(),
        #[cfg(feature = "experimental")]
        RisczeroCmd::BuildCrate(build) => build.run(BuildSubcommand::Build),
        #[cfg(feature = "experimental")]
        RisczeroCmd::Test(build) => build.run(BuildSubcommand::Test),
    }
}
