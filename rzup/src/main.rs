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

use std::fs::{self, OpenOptions};

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
    rzup::Rzup::version(),
),
after_help = cli::help::RZUP_HELP,
version = rzup::Rzup::version(),
)]
struct Rzup {
    /// Enable verbose output
    #[arg(short, long)]
    verbose: bool,

    #[command(subcommand)]
    subcmd: Option<RzupSubcmd>,
}

#[derive(Debug, Subcommand)]
#[command(name = "rzup", bin_name = "rzup")]
enum RzupSubcmd {
    /// Show the active and installed toolchains and extensions
    #[command(after_help = cli::help::SHOW_HELP)]
    Show {
        #[command(subcommand)]
        subcmd: Option<cli::show::ShowSubcmd>,
    },
    /// Install toolchains or extensions
    #[command(after_help = cli::help::INSTALL_HELP)]
    Install {
        /// Name of the toolchain or extension to install
        name: Option<String>,
        /// Version tag of the toolchain or extension to install
        version: Option<String>,
        /// Force the installation, ignoring existing installations and downloads
        #[arg(short, long)]
        force: bool,
    },
    /// Update toolchains or extensions
    #[command(after_help = cli::help::UPDATE_HELP, aliases = ["upgrade", "up"])]
    Update {
        /// Toolchain to update (i.e. rust or cpp)
        toolchain: Option<toolchain::Toolchain>,
        /// Extension to update (i.e. cargo-risczero)
        extension: Option<extension::Extension>,
        /// Force the update, ignoring existing installations and downloads
        #[arg(short, long)]
        force: bool,
    },
    /// Check for updates to toolchains and extensions
    #[command(after_help = cli::help::CHECK_HELP)]
    Check,
    /// Set the default toolchains
    #[command(after_help = cli::help::DEFAULT_HELP)]
    Default {
        /// RISC Zero toolchain (i.e. rust, cpp)
        toolchain: Option<toolchain::Toolchain>,
        /// The toolchain name
        name: Option<String>,
    },
    /// Modify or query the installed toolchains
    Toolchain {
        #[command(subcommand)]
        subcmd: cli::toolchain::ToolchainSubcmd,
    },
    /// Modify or query the installed extensions
    Extension {
        #[command(subcommand)]
        subcmd: cli::extension::ExtensionSubcmd,
    },
    /// Modify the rzup installation
    Self_ {
        #[command(subcommand)]
        subcmd: cli::self_::SelfSubcmd,
    },
}

#[tokio::main]
async fn main() {
    if let Err(err) = run().await {
        eprintln!("Error: {}", err);
        std::process::exit(1);
    }
}

fn init() -> Result<()> {
    // this is a rust revamp of rzup. Before this version, rzup was a bash
    // script. In order to facilitate compatibility within our tools, we touch a
    // file in a known location to indicate to the client that the rust
    // impelemtnation of rzup is being utilized.
    let new_rzup_indicator = utils::rzup_home()?.join(risc0_build::RUST_RZUP_INDICATOR);
    if !new_rzup_indicator.exists() {
        fs::create_dir_all(new_rzup_indicator.parent().unwrap())?;
        OpenOptions::new()
            .create(true)
            .write(true)
            .open(new_rzup_indicator)?;
    }
    Ok(())
}

async fn run() -> Result<()> {
    init()?;
    let matches = Rzup::parse();

    // Set verbosity flag based on the CLI argument
    utils::set_verbose(matches.verbose);

    let Some(subcmd) = matches.subcmd else {
        eprintln!("{}", Rzup::command().render_long_help());
        std::process::exit(1)
    };

    match subcmd {
        RzupSubcmd::Show { subcmd } => cli::show::handler(subcmd),
        RzupSubcmd::Install {
            name,
            version,
            force,
        } => {
            cli::install::handler(cli::install::InstallOpts {
                name,
                version,
                force,
            })
            .await
        }
        RzupSubcmd::Update {
            toolchain,
            extension,
            force,
        } => {
            cli::update::handler(cli::update::UpdateOpts {
                toolchain,
                extension,
                force,
            })
            .await
        }
        RzupSubcmd::Check => cli::check::handler().await,
        RzupSubcmd::Default { toolchain, name } => cli::default::handler(toolchain, name),
        RzupSubcmd::Toolchain { subcmd } => cli::toolchain::handler(subcmd).await,
        RzupSubcmd::Extension { subcmd } => cli::extension::handler(subcmd).await,
        RzupSubcmd::Self_ { subcmd } => cli::self_::handler(subcmd).await,
    }
}
