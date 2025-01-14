// Copyright 2025 RISC Zero, Inc.
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
pub(crate) mod commands;
pub(crate) mod ui;

use crate::error::Result;
use crate::Rzup;
use crate::RzupEvent;

use clap::{Parser, Subcommand};
use colored::Colorize;
use commands::UninstallCommand;
use commands::{CheckCommand, InstallCommand, ShowCommand, UseCommand};
use ui::Ui;

#[derive(Subcommand)]
enum Commands {
    /// Install and update RISC Zero components
    #[command(alias = "update")]
    Install(InstallCommand),
    /// Check for component updates
    Check(CheckCommand),
    /// Use a component version
    Use(UseCommand),
    /// Show installed components
    Show(ShowCommand),
    /// Uninstall a component
    #[command(hide = true)]
    Uninstall(UninstallCommand),
}

#[derive(Parser)]
#[command(name = "rzup", version)]
#[command(
    long_about = None,
    about = banner()
)]
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
        if !self.quiet {
            let ui = Ui::new(self.verbose);
            ui.progress.finish_and_clear();
            rzup.set_event_handler(move |event| match event {
                RzupEvent::DownloadStarted { id, version, url } => {
                    ui.handle_download(id, version, url)
                }
                RzupEvent::DownloadCompleted { id, version } => {
                    ui.handle_download_complete(id, version)
                }
                RzupEvent::InstallationStarted { id, version } => ui.handle_install(id, version),
                RzupEvent::InstallationCompleted { id, version } => {
                    ui.handle_install_complete(id, version)
                }
                RzupEvent::ComponentAlreadyInstalled { id, version } => {
                    ui.handle_already_installed(id, version)
                }
                RzupEvent::InstallationFailed { id: _, version: _ } => {
                    ui.progress.finish_and_clear();
                }
                RzupEvent::Uninstalled { id, version } => ui.handle_uninstall(id, version),
                RzupEvent::CheckUpdates { id } => ui.handle_checking_updates(id),
                RzupEvent::Debug { message } => ui.handle_debug(message),
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
            eprintln!(
                "{} {e}\n\nFor more information, try '--help'.",
                "error:".red(),
            );
            std::process::exit(1);
        }

        Ok(())
    }
}

fn banner() -> String {
    let version = env!("CARGO_PKG_VERSION");
    format!(
        r#"
rzup v{version}

   {}"#,
        r#"RISC
   ZERO"#
            .bold()
    )
}
