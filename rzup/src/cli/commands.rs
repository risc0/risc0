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
    /// Force the installation
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
                if name == "self" {
                    rzup.emit(RzupEvent::InstallationStarted {
                        id: "rzup".to_string(),
                        version: "latest".to_string(),
                    });

                    let tmp_dir = rzup.environment.tmp_dir();
                    let update_script = tmp_dir.join("rzup_update.sh");

                    std::fs::write(
                        &update_script,
                        r#"#!/bin/bash
                    set -e
                    curl -sL https://risczero.com/install | bash -s -- --quiet
                    "#,
                    )?;

                    #[cfg(unix)]
                    {
                        use std::os::unix::fs::PermissionsExt;
                        let mut perms = std::fs::metadata(&update_script)?.permissions();
                        perms.set_mode(0o755);
                        std::fs::set_permissions(&update_script, perms)?;
                    }

                    // Execute quietly
                    let output = std::process::Command::new("/bin/sh")
                        .arg(&update_script)
                        .output()
                        .map_err(|e| {
                            RzupError::Other(format!("Failed to execute update script: {}", e))
                        })?;

                    let _ = std::fs::remove_file(update_script);

                    if !output.status.success() {
                        rzup.emit(RzupEvent::InstallationFailed {
                            id: "rzup".to_string(),
                            version: "latest".to_string(),
                        });
                        return Err(RzupError::Other(format!(
                            "Self-update failed: {}",
                            String::from_utf8_lossy(&output.stderr)
                        )));
                    }

                    rzup.emit(RzupEvent::InstallationCompleted {
                        id: "rzup".to_string(),
                        version: "latest".to_string(),
                    });

                    return Ok(());
                }

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
            let versions = rzup.list_versions(id)?;

            if !versions.is_empty() {
                println!("{}", id);

                let active_version = rzup.get_active_version(id)?;
                let mut sorted_versions = versions;
                sorted_versions.sort_by(|a, b| b.cmp(a)); // sort newest to oldest

                for version in sorted_versions {
                    let active_marker =
                        if Some(version.clone()) == active_version.clone().map(|(v, _)| v) {
                            "* ".bold()
                        } else {
                            "  ".normal()
                        };
                    println!("{}{}", active_marker, version);
                }
                println!();

                // Show warnings for missing active versions
                if let Some(settings_version) = rzup.registry.settings().get_active_version(id) {
                    if active_version.is_none() {
                        println!(
                            "! Version {} specified in settings.toml is not installed",
                            settings_version
                        );
                        println!(
                            "  Please use 'rzup use {} <VERSION>' to switch active component",
                            id,
                        );
                    }
                } else if active_version.is_none() {
                    println!(
                        "! No active version found.\n  Please use 'rzup use {} <version>' to set an active version",
                        id
                    );
                }
            }
        }

        println!(
            "{}: {}",
            "rzup home".bold(),
            rzup.environment.root_dir().display()
        );

        Ok(())
    }
}

#[derive(Parser)]
pub(crate) struct UseCommand {
    /// Name of component to activate
    name: String,
    /// Version of component to activate
    version: String,
}

impl UseCommand {
    pub(crate) fn execute(self, rzup: &mut Rzup) -> Result<()> {
        let version = Version::parse(&self.version)
            .map_err(|_| RzupError::InvalidVersion(self.version.clone()))?;

        if rzup.version_exists(&self.name, &version)? {
            rzup.set_active_version(&self.name, version.clone())?;
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

        Ok(())
    }
}

#[derive(Parser)]
pub(crate) struct CheckCommand;

impl CheckCommand {
    pub(crate) fn execute(&self, rzup: &Rzup) -> Result<()> {
        let components = rzup.registry.list_components();
        if components.is_empty() {
            println!("! Nothing is installed\n  Please use 'rzup install' to install.");
            return Ok(());
        }

        let mut results = Vec::new();

        for component in components {
            let id = component.id();
            rzup.emit(RzupEvent::CheckUpdates {
                id: Some(id.to_string()),
            });

            let latest_version = rzup.get_latest_version(id)?;
            let installed_versions = rzup.list_versions(id)?;

            if let Some(max_installed) = installed_versions.iter().max() {
                if !rzup.version_exists(id, &latest_version)? {
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
        }

        rzup.emit(RzupEvent::CheckUpdates { id: None });

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
