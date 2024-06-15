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

use clap::{arg, Args, CommandFactory, Parser, Subcommand};
use rzup::cmd::extension::handle_extension;
use rzup::cmd::extension::ExtensionSubcmd;
use rzup::help;
use rzup::utils;
use rzup::{
    cmd::{
        check::handle_check_all,
        install::{InstallCargoRisczero, InstallToolchain},
        show::{handle_show, ShowSubcmd},
        toolchain::{handle_toolchain, ToolchainSubcmd},
    },
    toolchain::repo::ToolchainRepo,
};

fn main() {
    let matches = Rzup::parse();

    let Some(subcmd) = matches.subcmd else {
        println!("{}", Rzup::command().render_long_help());
        std::process::exit(0)
    };

    match subcmd {
        RzupSubcmd::Install { opts } => {
            InstallCargoRisczero {
                version: opts.version,
            }
            .run()
            .expect("Error during cargo-risczero installation");
            InstallToolchain {
                toolchain: Some("latest".to_string()),
                repo: ToolchainRepo::Rust,
            }
            .run()
            .expect("Error during Rust toolchain installation");
        }
        RzupSubcmd::Toolchain { subcmd } => handle_toolchain(subcmd),
        RzupSubcmd::Extension { subcmd } => handle_extension(subcmd),
        RzupSubcmd::Show { verbose, subcmd } => handle_show(verbose, subcmd),
        RzupSubcmd::Check => handle_check_all().expect("Error checking for updates"),
        RzupSubcmd::Update { .. } => {
            InstallCargoRisczero {
                version: Some("latest".to_string()),
            }
            .run()
            .expect("Error during cargo-risczero update");
        }
    }
}

#[derive(Debug, Parser)]
#[command(
    name = "rzup",
    bin_name = "rzup[EXE]",
    version = utils::version(),
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
    utils::version()
    ),
    after_help = help::RZUP_HELP
)]
pub struct Rzup {
    /// Enable verbose output
    #[arg(short, long)]
    verbose: bool,

    #[command(subcommand)]
    pub subcmd: Option<RzupSubcmd>,
}

#[derive(Debug, Subcommand)]
#[command(name = "rzup", bin_name = "rzup[EXE]")]
pub enum RzupSubcmd {
    #[command(after_help = help::INSTALL_HELP, hide = true)]
    Install {
        #[command(flatten)]
        opts: InstallOpts,
    },

    /// Manage and install RISC Zero toolchains
    Toolchain {
        #[command(subcommand)]
        subcmd: ToolchainSubcmd,
    },

    /// Manage cargo-risczero extensions
    Extension {
        #[command(subcommand)]
        subcmd: ExtensionSubcmd,
    },

    /// Show the active and installed toolchains
    #[command(after_help = help::SHOW_HELP)]
    Show {
        /// Enable verbose output for all installed toolchains
        #[arg(short, long)]
        verbose: bool,

        #[command(subcommand)]
        subcmd: Option<ShowSubcmd>,
    },

    /// Update RISC Zero toolchains and cargo-risczero
    #[command(after_help = help::UPDATE_HELP, aliases = ["upgrade", "up"])]
    Update {
        /// Toolchain name, such as latest, tag.
        #[arg(num_args = 1..)]
        toolchain: Vec<String>, // TODO

        /// Force an update
        #[arg(long)]
        force: bool,
    },

    /// Check for updates to RISC Zero toolchains and rzup
    Check,
}

#[derive(Debug, Default, Args, Clone)]
pub struct InstallOpts {
    #[arg(
        long,
        short,
        required = false,
        help = help::INSTALL_HELP,
        num_args = 1..,
    )]
    version: Option<String>,
}
