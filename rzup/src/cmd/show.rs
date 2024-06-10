use crate::help;
use clap::Subcommand;

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

pub fn handle_show(verbose: bool, subcmd: Option<ShowSubcmd>) {
    match subcmd {
        Some(ShowSubcmd::ActiveToolchain { .. }) => {
            // Placeholder for active toolchain logic
            println!("Active toolchain logic not implemented yet.");
        }
        Some(ShowSubcmd::Home) => {
            // Placeholder for RZUP_HOME logic
            println!("RZUP_HOME logic not implemented yet.");
        }
        None => {
            // Call the function to list all installed toolchains
            if let Err(e) = show_installed_toolchains(verbose) {
                eprintln!("Error showing toolchains: {}", e);
                std::process::exit(1);
            }
        }
    }
}

pub fn show_installed_toolchains(verbose: bool) -> anyhow::Result<()> {
    use crate::utils::risc0_data;
    use std::fs;
    use std::io::Write;
    use termcolor::{Color, ColorChoice, ColorSpec, StandardStream, WriteColor};

    let toolchains_dir = risc0_data()?.join("toolchains");

    if !toolchains_dir.exists() {
        eprintln!("No toolchains directory found.");
        return Ok(());
    }

    let entries = fs::read_dir(&toolchains_dir)?
        .filter_map(|res| res.ok())
        .filter(|entry| entry.path().is_dir())
        .collect::<Vec<_>>();

    if entries.is_empty() {
        println!("No installed toolchains found.");
        return Ok(());
    }

    for entry in entries {
        let toolchain_name = entry.file_name().to_string_lossy().to_string();
        if verbose {
            println!("Toolchain: {}", toolchain_name);
            // Optionally add more detailed information about the toolchain here
        } else {
            let mut stdout = StandardStream::stdout(ColorChoice::Always);
            stdout.set_color(ColorSpec::new().set_fg(Some(Color::Green)))?;
            writeln!(&mut stdout, "{}", toolchain_name)?;
        }
    }

    Ok(())
}
