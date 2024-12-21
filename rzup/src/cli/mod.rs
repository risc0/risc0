mod commands;

use crate::cli::commands::{CheckCommand, InstallCommand, ShowCommand, UseCommand};
use crate::error::Result;
use crate::Rzup;
use clap::{Parser, Subcommand};

#[derive(Subcommand)]
enum Commands {
    Install(InstallCommand),
    Check(CheckCommand),
    Use(UseCommand),
    Show(ShowCommand),
}

#[derive(Parser)]
#[command(name = "rzup", version)]
pub struct Cli {
    #[command(subcommand)]
    command: Commands,

    /// Enable verbose output
    #[arg(global = true, short, long)]
    verbose: bool,
}

impl Cli {
    pub fn execute(self, rzup: &mut Rzup) -> Result<()> {
        match self.command {
            Commands::Install(cmd) => cmd.execute(rzup),
            Commands::Show(cmd) => cmd.execute(rzup),
            Commands::Use(cmd) => cmd.execute(rzup),
            Commands::Check(cmd) => cmd.execute(rzup),
        }
    }
}
