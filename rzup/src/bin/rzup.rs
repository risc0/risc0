use clap::{arg, Parser, Subcommand};
use rzup::cmd::install::InstallToolchain;
use rzup::cmd::show::ShowSubcmd;
use rzup::cmd::{install::InstallSubcmd, toolchain::ToolchainSubcmd};
use rzup::toolchain::repo::ToolchainRepo;
use rzup::utils::risc0_data;
use rzup::{common, help};
use std::fs;
use std::io::Write;
use termcolor::{Color, ColorChoice, ColorSpec, StandardStream, WriteColor};

fn main() {
    let matches = Rzup::parse();

    let subcmd = matches.subcmd;

    match subcmd {
        Some(RzupSubcmd::Install { subcmd }) => {
            match subcmd {
                InstallSubcmd::Rust { toolchain } => {
                    // Install Rust toolchain
                    InstallToolchain {
                        toolchain: Some(toolchain),
                        repo: ToolchainRepo::Rust,
                    }
                    .run()
                    .expect("Error during Rust toolchain installation");
                }
                InstallSubcmd::Cpp { toolchain } => {
                    // Install C++ toolchain
                    InstallToolchain {
                        toolchain: Some(toolchain),
                        repo: ToolchainRepo::Cpp,
                    }
                    .run()
                    .expect("Error during C++ toolchain installation");
                }
                InstallSubcmd::All => {
                    // Install all toolchains
                    InstallToolchain {
                        toolchain: None,
                        repo: ToolchainRepo::Rust,
                    }
                    .run()
                    .expect("Error during Rust toolchain installation");
                    InstallToolchain {
                        toolchain: None,
                        repo: ToolchainRepo::Cpp,
                    }
                    .run()
                    .expect("Error during C++ toolchain installation");
                }
            }
        }
        Some(RzupSubcmd::Toolchain { subcmd }) => {
            match subcmd {
                ToolchainSubcmd::List { verbose } => {
                    if let Err(e) = show_installed_toolchains(verbose) {
                        eprintln!("Error showing toolchains: {}", e);
                        std::process::exit(1);
                    }
                }
                ToolchainSubcmd::Install { subcmd } => {
                    match subcmd {
                        InstallSubcmd::Rust { toolchain } => {
                            // Install Rust toolchain
                            InstallToolchain {
                                toolchain: Some(toolchain),
                                repo: ToolchainRepo::Rust,
                            }
                            .run()
                            .expect("Error during Rust toolchain installation");
                        }
                        InstallSubcmd::Cpp { toolchain } => {
                            // Install C++ toolchain
                            InstallToolchain {
                                toolchain: Some(toolchain),
                                repo: ToolchainRepo::Cpp,
                            }
                            .run()
                            .expect("Error during C++ toolchain installation");
                        }
                        InstallSubcmd::All => {
                            // Install all toolchains
                            InstallToolchain {
                                toolchain: None,
                                repo: ToolchainRepo::Rust,
                            }
                            .run()
                            .expect("Error during Rust toolchain installation");
                            InstallToolchain {
                                toolchain: None,
                                repo: ToolchainRepo::Cpp,
                            }
                            .run()
                            .expect("Error during C++ toolchain installation");
                        }
                    }
                }
                ToolchainSubcmd::Build(cmd) => {
                    if let Err(e) = cmd.run() {
                        eprintln!("Error building toolchain: {}", e);
                        std::process::exit(1);
                    }
                }
            }
        }
        Some(RzupSubcmd::Show { verbose, subcmd }) => {
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
        Some(RzupSubcmd::Check { .. }) => todo!(),
        Some(RzupSubcmd::Update { .. }) => todo!(),
        Some(RzupSubcmd::Default { .. }) => todo!(),
        Some(RzupSubcmd::Uninstall { .. }) => todo!(),
        None => todo!(),
    }
}

fn show_installed_toolchains(verbose: bool) -> anyhow::Result<()> {
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
            // println!("{}", toolchain_name);
            let mut stdout = StandardStream::stdout(ColorChoice::Always);
            stdout.set_color(ColorSpec::new().set_fg(Some(Color::Green)))?;
            writeln!(&mut stdout, "{}", toolchain_name)?;
        }
    }

    Ok(())
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
