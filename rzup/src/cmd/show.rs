use clap::Subcommand;

use crate::help;

#[derive(Debug, Subcommand)]
pub enum ShowSubcmd {
    /// Show the active toolchain
    #[command(after_help = help::SHOW_ACTIVE_TOOLCHAIN_HELP)]
    ActiveToolchain {
        /// Enable verbose output with toolchain information
        #[arg(short, long)]
        verbose: bool,
    },

    /// Display the computed value or RZUP_HOME
    Home,
}
