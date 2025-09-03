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

use crate::Rzup;
use crate::error::Result;
use crate::events::RzupEvent;

use clap::{Parser, Subcommand};
use colored::Colorize;
use commands::UninstallCommand;
use commands::{
    BuildCommand, CheckCommand, DefaultCommand, InstallCommand, PublishCommand, ShowCommand,
};
use ui::{TerminalUi, TextUi};

#[derive(Subcommand)]
enum Commands {
    /// Install and update components
    #[command(alias = "update", after_help = commands::install_help())]
    Install(InstallCommand),
    /// Check for new component versions
    #[command(after_help = commands::CHECK_HELP)]
    Check(CheckCommand),
    /// Set a component version as default
    #[command(after_help = commands::DEFAULT_HELP)]
    Default(DefaultCommand),
    /// Show installed components
    #[command(after_help = commands::SHOW_HELP)]
    Show(ShowCommand),
    /// Uninstall a component
    #[command(after_help = commands::UNINSTALL_HELP)]
    Uninstall(UninstallCommand),
    /// Build a component
    #[command(after_help = commands::BUILD_HELP)]
    Build(BuildCommand),
    /// Publish a component on S3
    #[command(after_help = commands::PUBLISH_HELP, subcommand)]
    Publish(PublishCommand),
}

pub const RZUP_HELP: &str = "Discussion:
    Installs and manages software components distributed by Risc Zero.

    Installed components are stored in the path specified by the `RISC0_HOME`
    environment variable, or in `~/.risc0` if not set.

    Rust software components symlink their binaries into ~/.cargo/bin/ when
    made default.";

#[derive(Parser)]
#[command(name = "rzup", version)]
#[command(
    long_about = None,
    about = banner(),
    after_help = RZUP_HELP,
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

fn spawn_ui<'scope, 'env>(
    verbose: bool,
    scope: &'scope std::thread::Scope<'scope, 'env>,
) -> impl Fn(RzupEvent) + Send + Sync + 'static
where
    'env: 'scope,
{
    use is_terminal::IsTerminal as _;

    let (ui_send, ui_recv) = std::sync::mpsc::channel();

    if std::io::stdout().is_terminal() {
        let ui = TerminalUi::new(verbose);
        scope.spawn(move || {
            ui.run(ui_recv);
        });
    } else {
        let ui = TextUi::new(verbose);
        scope.spawn(move || {
            ui.run(ui_recv);
        });
    }

    move |event| {
        let _ = ui_send.send(event);
    }
}

impl Cli {
    pub fn execute(self) -> Result<()> {
        let result = std::thread::scope(|scope| {
            let mut rzup = if !self.quiet {
                let event_handler = spawn_ui(self.verbose, scope);
                Rzup::new_with_event_handler(event_handler)?
            } else {
                Rzup::new()?
            };

            match self.command {
                Commands::Install(cmd) => cmd.execute(&mut rzup),
                Commands::Show(cmd) => cmd.execute(&rzup),
                Commands::Default(cmd) => cmd.execute(&mut rzup),
                Commands::Check(cmd) => cmd.execute(&rzup),
                Commands::Uninstall(cmd) => cmd.execute(&mut rzup),
                Commands::Build(cmd) => cmd.execute(&mut rzup),
                Commands::Publish(cmd) => cmd.execute(&mut rzup),
            }
        });

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

const LOGO: &str = "\n   RISC\n   ZERO";

fn banner() -> String {
    let version = env!("CARGO_PKG_VERSION");
    format!("rzup v{version}\n{}", LOGO.bold())
}
