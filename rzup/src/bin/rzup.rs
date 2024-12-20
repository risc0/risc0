use clap::Parser;
use rzup::cli::Cli;
use rzup::error::Result;
use rzup::Rzup;

fn main() -> Result<()> {
    let mut rzup = Rzup::new()?;
    let cli = Cli::parse();
    cli.execute(&mut rzup)
}
