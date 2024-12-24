use crate::error::Result;
use crate::events::RzupEvent;
use crate::{Rzup, RzupError};
use clap::Parser;
use colored::Colorize;
use semver::Version;

#[derive(Parser)]
pub(crate) struct InstallCommand {
    /// Name of component to install (e.g. rust). If not provided, installs all default components.
    name: Option<String>,
    /// Version of the component to install (optional). If not provided, installs the latest version.
    version: Option<String>,
    /// Force the install
    #[arg(short, long)]
    force: bool,
}

impl InstallCommand {
    pub(crate) fn execute(self, rzup: &mut Rzup) -> Result<()> {
        let version = match self.version {
            Some(v) => Some(Version::parse(&v).map_err(|_| RzupError::InvalidVersion(v))?),
            None => None,
        };
        match self.name {
            None => {
                rzup.install_all(self.force)?;
            }

            Some(name) => {
                rzup.install_component(&name, version, self.force)?;
            }
        }
        Ok(())
    }
}

#[derive(Parser)]
pub(crate) struct ShowCommand;

impl ShowCommand {
    pub(crate) fn execute(self, rzup: &Rzup) -> Result<()> {
        let components = rzup.registry.list_components();
        if components.is_empty() {
            println!("! Nothing is installed\n  Please use 'rzup install' to install.");
            return Ok(());
        }
        println!("{}", "Installed components:".bold());
        println!("{}", "--------------------".bold());

        for component in components {
            let id = component.id();
            if let Some(versions) = rzup.registry.get_component_versions(id) {
                println!("\n{}", id);

                let settings_version = rzup.registry.settings().get_active_version(id);
                let active_version = versions.get_active_version(rzup.registry.settings(), id);

                let mut all_versions: Vec<&Version> = versions.list_versions();
                all_versions.sort_by(|a, b| b.cmp(a)); // sort newest to oldest

                for version in all_versions {
                    let active_marker = if Some(version) == active_version.map(|(v, _)| v) {
                        "* "
                    } else {
                        "  "
                    };
                    println!("{}{}", active_marker, version);
                }

                if let Some(settings_ver) = settings_version {
                    if active_version.is_none() {
                        println!(
                            "! Version {} specified in settings.toml is not installed.",
                            settings_ver
                        );
                        println!(
                            "  Please use 'rzup install {} {}' to install it",
                            id, settings_ver
                        );
                    }
                } else if active_version.is_none() {
                    println!("! No active version found.\n  Please use 'rzup use {} <version>' to set an active version", id);
                }
            }
        }
        Ok(())
    }
}

#[derive(Parser)]
pub(crate) struct UseCommand {
    /// Name of component to activate
    name: String,
    /// Version of component to acivate
    version: String,
}

impl UseCommand {
    pub(crate) fn execute(self, rzup: &mut Rzup) -> Result<()> {
        let version = Version::parse(&self.version)
            .map_err(|_| RzupError::InvalidVersion(self.version.clone()))?;

        if let Some(versions) = rzup.registry.get_component_versions(&self.name) {
            if versions.has_version(&version) {
                rzup.registry
                    .set_active_version(&rzup.environment, &self.name, version.clone())?;
                println!(
                    "Successfully set {} version {} as active",
                    self.name, version
                );
            } else {
                println!(
                    "! Version {} of {} is not installed.\n  Please use 'rzup install {} {}' to install",
                    version, self.name, self.name, version
                );
            }
        } else {
            println!(
                "! {} is not installed.\n  Please use 'rzup install {} {}' to install",
                self.name, self.name, version
            );
        }

        Ok(())
    }
}

#[derive(Parser)]
pub(crate) struct CheckCommand;

impl CheckCommand {
    pub(crate) fn execute(&self, rzup: &Rzup) -> Result<()> {
        let components = rzup.registry.list_components();
        if components.is_empty() {
            println!("! Nothing is installed\n  Please use 'rzup install' to install.")
        }

        let mut results = Vec::new();

        for component in components {
            let id = component.id();
            rzup.environment().emit(RzupEvent::CheckUpdates {
                id: Some(id.to_string()),
            });

            let latest_version = rzup.latest_version(id)?;
            let versions = rzup.installed_versions(id);
            let max_installed = versions.keys().max().unwrap();

            if !rzup.is_installed(id, &latest_version) {
                results.push(format!(
                    "{} - {} : {} -> {}",
                    id.bold(),
                    "Update Available".bold().yellow(),
                    max_installed,
                    latest_version,
                ));
            } else {
                results.push(format!(
                    "{} - {} : {}",
                    id.bold(),
                    "Up to date".bold().green(),
                    max_installed
                ));
            }
        }

        rzup.environment()
            .emit(RzupEvent::CheckUpdates { id: None });

        for result in results {
            println!("{}", result);
        }

        Ok(())
    }
}

#[derive(Parser)]
pub(crate) struct UninstallCommand {
    /// Name of component to uninstall
    name: String,
    /// Version of the component to uninstall
    version: String,
}

impl UninstallCommand {
    pub(crate) fn execute(&self, rzup: &mut Rzup) -> Result<()> {
        let version = Version::parse(&self.version)
            .map_err(|_| RzupError::InvalidVersion(self.version.clone()))?;
        rzup.uninstall_component(&self.name, version)
    }
}
