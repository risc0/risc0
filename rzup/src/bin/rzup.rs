use clap::{arg, CommandFactory, Parser, Subcommand};
use rzup::cmd::install::{handle_install, InstallSubcmd};
use rzup::cmd::show::{handle_show, ShowSubcmd};
use rzup::cmd::toolchain::{handle_toolchain, ToolchainSubcmd};
use rzup::{common, help};

fn main() {
    let matches = Rzup::parse();

    if std::env::args().len() == 1 {
        println!("{}", Rzup::command().render_long_help());
        std::process::exit(0);
    }

    let subcmd = matches.subcmd;

    match subcmd {
        Some(RzupSubcmd::Install { subcmd }) => handle_install(subcmd),

        Some(RzupSubcmd::Toolchain { subcmd }) => handle_toolchain(subcmd),

        Some(RzupSubcmd::Show { verbose, subcmd }) => handle_show(verbose, subcmd),

        Some(RzupSubcmd::Check { .. }) => todo!(),
        Some(RzupSubcmd::Update { .. }) => todo!(),
        Some(RzupSubcmd::Default { .. }) => todo!(),
        Some(RzupSubcmd::Uninstall { .. }) => todo!(),
        None => todo!(),
    }
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
