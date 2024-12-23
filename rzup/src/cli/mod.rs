mod commands;

use crate::cli::commands::{CheckCommand, InstallCommand, ShowCommand, UseCommand};
use crate::error::Result;
use crate::Rzup;
use crate::RzupEvent;
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
        // set up event handler
        rzup.set_event_handler(move |event| match event {
            RzupEvent::DownloadStarted { url } => {
                if self.verbose {
                    println!("Downloading from: {}", url)
                } else {
                    println!("▸ Downloading...")
                }
            }
            RzupEvent::DownloadCompleted { id } => {
                println!("✓ Download completed for {}", id);
            }
            RzupEvent::InstallationStarted { id, version } => {
                if self.verbose {
                    println!("Starting installation of {} version {}...", id, version);
                }
            }
            RzupEvent::InstallationCompleted { id, version } => {
                println!("✓ Successfully installed {} version {}", id, version);
            }
            RzupEvent::ComponentAlreadyInstalled { id, version } => {
                println!("{} version {} is already installed", id, version);
            }
            RzupEvent::SettingsCreated { path } => {
                println!(
                    "\n! Missing settings.toml\n  Created settings.toml at {}\n",
                    path.display()
                );
            }
            RzupEvent::Debug { message } => {
                if self.verbose {
                    println!("Debug: {}", message);
                }
            }
        });

        match self.command {
            Commands::Install(cmd) => cmd.execute(rzup),
            Commands::Show(cmd) => cmd.execute(rzup),
            Commands::Use(cmd) => cmd.execute(rzup),
            Commands::Check(cmd) => cmd.execute(rzup),
        }
    }
}
