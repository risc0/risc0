mod commands;
mod output;

use crate::error::Result;
use crate::Rzup;
use crate::RzupEvent;
use clap::{Parser, Subcommand};
use commands::UninstallCommand;
use commands::{CheckCommand, InstallCommand, ShowCommand, UseCommand};
use output::EventPrinter;

#[derive(Subcommand)]
enum Commands {
    Install(InstallCommand),
    Check(CheckCommand),
    Use(UseCommand),
    Show(ShowCommand),
    #[command(hide = true)]
    Uninstall(UninstallCommand),
}

#[derive(Parser)]
#[command(name = "rzup", version)]
pub struct Cli {
    #[command(subcommand)]
    command: Commands,
    /// Enable verbose output
    #[arg(global = true, short, long)]
    verbose: bool,
    /// Suppress output
    #[arg(global = true, short, long)]
    quiet: bool,
}

impl Cli {
    pub fn execute(self, rzup: &mut Rzup) -> Result<()> {
        let printer = EventPrinter::new(self.verbose);

        if !self.quiet {
            rzup.set_event_handler(move |event| match event {
                RzupEvent::DownloadStarted { id, version, url } => {
                    printer.handle_download(id, version, url)
                }
                RzupEvent::DownloadCompleted { id, version } => {
                    printer.handle_download_complete(id, version)
                }
                RzupEvent::InstallationStarted { id, version } => {
                    printer.handle_install(id, version)
                }
                RzupEvent::InstallationCompleted { id, version } => {
                    printer.handle_install_complete(id, version)
                }
                RzupEvent::ComponentAlreadyInstalled { id, version } => {
                    printer.handle_already_installed(id, version)
                }
                RzupEvent::InstallationFailed { id: _, version: _ } => {
                    printer.progress.finish_and_clear();
                }
                RzupEvent::Uninstalled { id, version } => printer.handle_uninstall(id, version),
                RzupEvent::CheckUpdates { id } => printer.handle_checking_updates(id),
                RzupEvent::Debug { message } => printer.handle_debug(message),
            });
        }

        let result = match self.command {
            Commands::Install(cmd) => cmd.execute(rzup),
            Commands::Show(cmd) => cmd.execute(rzup),
            Commands::Use(cmd) => cmd.execute(rzup),
            Commands::Check(cmd) => cmd.execute(rzup),
            Commands::Uninstall(cmd) => cmd.execute(rzup),
        };

        if let Err(e) = result {
            eprintln!("✗ Error:\n   {}", e);
            std::process::exit(1);
        }

        Ok(())
    }
}
