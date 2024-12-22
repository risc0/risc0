use clap::Parser;
use rzup::cli::Cli;
use rzup::error::Result;
use rzup::Rzup;
use rzup::RzupEvent;
fn main() -> Result<()> {
    let mut rzup = Rzup::new()?;
    let cli = Cli::parse();

    // set up event handler
    rzup.set_event_handler(|event| match event {
        RzupEvent::DownloadStarted { url } => {
            println!("!!Downloading from: {}", url);
        }
        RzupEvent::ComponentAlreadyInstalled { id, version } => {
            println!("{} version {} is already installed", id, version);
        }
        RzupEvent::SettingsCreated { path } => {
            println!(
                "\n! Missing settings.toml\n  Created settings.toml at {}\n",
                path.display()
            );
        }
    });

    rzup.init()?;

    cli.execute(&mut rzup)
}
