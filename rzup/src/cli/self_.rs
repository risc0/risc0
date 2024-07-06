use crate::Rzup;
use anyhow::Result;
use clap::Subcommand;

#[derive(Debug, Subcommand)]
pub enum SelfSubcmd {
    /// Download and install updates to rzup
    Update,
    /// Uninstall rzup
    Uninstall,
}

pub async fn handler(subcmd: SelfSubcmd) -> Result<()> {
    match subcmd {
        SelfSubcmd::Update => Rzup::update().await,
        SelfSubcmd::Uninstall => Rzup::uninstall(),
    }
}
