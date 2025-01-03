use clap::Parser;
use rzup::{cli::Cli, error::Result, Rzup};

fn main() -> Result<()> {
    let mut rzup = Rzup::new()?;
    let cli = Cli::parse();

    cli.execute(&mut rzup)
}
