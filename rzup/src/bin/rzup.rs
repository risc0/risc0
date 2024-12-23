use clap::Parser;
use rzup::cli::Cli;
use rzup::error::Result;
use rzup::Rzup;
// use rzup::RzupEvent;
fn main() -> Result<()> {
    let mut rzup = Rzup::new()?;
    let cli = Cli::parse();

    if let Err(e) = cli.execute(&mut rzup) {
        eprintln!("✗ Error:\n   {}", e);
        std::process::exit(1);
    }

    Ok(())
}
