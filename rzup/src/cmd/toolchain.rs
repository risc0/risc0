use clap::Subcommand;

use super::{
    install::{handle_install, InstallSubcmd},
    show::show_installed_toolchains,
};
use crate::toolchain::build::BuildToolchain;

#[derive(Debug, Subcommand)]
pub enum ToolchainSubcmd {
    /// List installed toolchains
    List {
        #[arg(short, long)]
        verbose: bool,
    },

    /// Install or update a given toolchain
    Install {
        #[command(subcommand)]
        subcmd: InstallSubcmd,
    },

    /// Build the toolchain
    Build(BuildToolchain),
}

pub fn handle_toolchain(subcmd: ToolchainSubcmd) {
    match subcmd {
        ToolchainSubcmd::List { verbose } => {
            if let Err(e) = show_installed_toolchains(verbose) {
                eprintln!("Error showing toolchains: {}", e);
                std::process::exit(1);
            }
        }
        ToolchainSubcmd::Install { subcmd } => handle_install(subcmd),
        ToolchainSubcmd::Build(cmd) => {
            if let Err(e) = cmd.run() {
                eprintln!("Error building toolchain: {}", e);
                std::process::exit(1);
            }
        }
    }
}
