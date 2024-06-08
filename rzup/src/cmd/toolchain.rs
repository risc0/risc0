use clap::Subcommand;

use crate::toolchain::build::BuildToolchain;

use super::install::InstallSubcmd;

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
