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

use clap::{arg, CommandFactory, Parser, Subcommand};
use rzup::cmd::{
    check::handle_check,
    install::{handle_install, InstallSubcmd},
    show::{handle_show, ShowSubcmd},
    toolchain::{handle_toolchain, ToolchainSubcmd},
};
use rzup::{common, help};

fn main() {
    let matches = Rzup::parse();

    if std::env::args().len() == 1 {
        println!("{}", Rzup::command().render_long_help());
        std::process::exit(0);
    }

    let subcmd = matches.subcmd;

    match subcmd {
        Some(RzupSubcmd::Install { subcmd }) => handle_install(subcmd),

        Some(RzupSubcmd::Toolchain { subcmd }) => handle_toolchain(subcmd),

        Some(RzupSubcmd::Show { verbose, subcmd }) => handle_show(verbose, subcmd),

        Some(RzupSubcmd::Check { .. }) => handle_check().expect("Error checking for updates"),

        Some(RzupSubcmd::Update { .. }) => todo!(),
        Some(RzupSubcmd::Default { .. }) => todo!(),
        Some(RzupSubcmd::Uninstall { .. }) => todo!(),
        None => todo!(),
    }
}

#[derive(Debug, Parser)]
#[command(
    name = "rzup",
    bin_name = "rustup[EXE]",
    version = common::version(),
    before_help = format!("rzup {}", common::version()),
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
    /// Update RISC Zero toolchains
    #[command(after_help = help::INSTALL_HELP)]
    Install {
        #[command(subcommand)]
        subcmd: InstallSubcmd,
    },

    /// Manage toolchains
    Toolchain {
        #[command(subcommand)]
        subcmd: ToolchainSubcmd,
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

    /// Set the default RISC Zero toolchain
    Default,

    /// Uninstall RISC Zero toolchains
    Uninstall,
}
