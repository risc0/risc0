use cargo_risczero::commands::new::NewCommand;
use clap::{Parser, Subcommand};
use tracing_subscriber::EnvFilter;

#[derive(Parser)]
#[clap(name = "cargo")]
#[clap(bin_name = "cargo")]
/// Main cargo command
pub enum Cargo {
    Risczero(Risczero),
}

#[derive(clap::Args)]
#[clap(author, version, about, long_about = None)]
/// `cargo risczero`
pub struct Risczero {
    #[clap(subcommand)]
    command: RisczeroCmd,
}

#[derive(Subcommand)]
/// Primary commands  of `cargo risczero`.
pub enum RisczeroCmd {
    /// Creates a new risczero starter project.
    New(NewCommand),
}

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(EnvFilter::from_default_env())
        .init();

    let Cargo::Risczero(args) = Cargo::parse();

    match args.command {
        RisczeroCmd::New(new) => {
            new.run();
        }
    }
}
