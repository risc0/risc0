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

use clap::{CommandFactory, Parser, Subcommand};

use rzup::{cli, extension, toolchain, utils};

#[derive(Debug, Parser)]
#[command(
    name = "rzup",
    bin_name = "rzup",
    before_help = format!(
"rzup {}

    ██████  █▀▀▀██
    ██████  █ ▄▀ █        Prove anything.
    ██████  ██▄▄▄█       Verify everywhere.
    ██████
    ██████   RISC
    ██████   ZERO

Contribute      : https://github.com/risc0/
Documentation   : https://dev.risczero.com/
Chat & Support  : https://discord.com/invite/risczero/",
    utils::version(),
),
after_help = "AFTER HELP",
version = utils::version(),
)]
struct Rzup {
    /// Enable verbose output
    #[arg(short, long)]
    verbose: bool,

    #[command(subcommand)]
    subcmd: Option<RzupSubcmd>,
}

// TODO: Document commands and options
#[derive(Debug, Subcommand)]
#[command(name = "rzup", bin_name = "rzup")]
enum RzupSubcmd {
    #[command(after_help = "SHOW AFTER HELP")]
    Show {
        #[command(subcommand)]
        subcmd: Option<cli::show::ShowSubcmd>,
    },
    #[command(after_help = "INSTALL_AFTER_HELP")]
    Install {
        name: Option<String>,
        version: Option<String>,
    },
    #[command(after_help = "UPDATE_AFTER_HELP", aliases = ["upgrade", "up"])]
    Update {
        toolchain: Option<toolchain::Toolchain>,
        extension: Option<extension::Extension>,
    },
    Check,
    #[command(after_help = "DEFAULT_AFTER_HELP")]
    Default {
        /// RISC Zero toolchain language (i.e. rust, cpp)
        toolchain: Option<toolchain::Toolchain>,
        /// A toolchain name
        name: Option<String>,
    },
    Toolchain {
        #[command(subcommand)]
        subcmd: cli::toolchain::ToolchainSubcmd,
    },
    Extension {
        #[command(subcommand)]
        subcmd: cli::extension::ExtensionSubcmd,
    },
    Self_,
}

#[tokio::main]
async fn main() {
    if let Err(err) = run().await {
        eprintln!("Error: {}", err);
        std::process::exit(1);
    }
}

async fn run() -> Result<()> {
    let matches = Rzup::parse();

    let Some(subcmd) = matches.subcmd else {
        eprintln!("{}", Rzup::command().render_long_help());
        std::process::exit(1)
    };

    match subcmd {
        RzupSubcmd::Show { subcmd } => cli::show::handler(subcmd),
        RzupSubcmd::Install { name, version } => {
            cli::install::handler(cli::install::InstallOpts { name, version }).await
        }

        RzupSubcmd::Update {
            toolchain,
            extension,
        } => {
            cli::update::handler(cli::update::UpdateOpts {
                toolchain,
                extension,
            })
            .await
        }
        RzupSubcmd::Check => cli::check::handler().await,
        RzupSubcmd::Default { toolchain, name } => cli::default::handler(toolchain, name),
        RzupSubcmd::Toolchain { subcmd } => cli::toolchain::handler(subcmd).await,
        RzupSubcmd::Extension { subcmd } => cli::extension::handler(subcmd).await,
        RzupSubcmd::Self_ => todo!(), // TODO: Add self updater
    }
}
