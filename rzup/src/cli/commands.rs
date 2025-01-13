// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
use crate::components::Component;
use crate::error::Result;
use crate::events::RzupEvent;
use crate::{Rzup, RzupError};

use clap::Parser;
use colored::Colorize;
use semver::Version;

fn component_parser() -> Vec<&'static str> {
    let mut components: Vec<_> = Component::iter().map(|c| c.as_str()).collect();
    components.push("self");
    components
}

#[derive(Parser)]
pub(crate) struct InstallCommand {
    /// Name of component to install (e.g. rust). If not provided, installs all default components.
    #[arg(value_parser=component_parser())]
    name: Option<String>,
    /// Version of the component to install (e.g. 1.0.0). If not provided, installs the latest version.
    version: Option<String>,
    /// Force the installation
    #[arg(short, long)]
    force: bool,
}

impl InstallCommand {
    pub(crate) fn execute(self, rzup: &mut Rzup) -> Result<()> {
        let version = match self.version {
            Some(v) => Some(match self.name.as_deref() {
                // special handling for cpp date-based versions
                // TODO: Move away from date version tags to semver
                Some("cpp") => {
                    let parts: Vec<_> = v.split('.').collect();
                    if parts.len() != 3 || parts.iter().any(|p| p.parse::<u64>().unwrap_or(0) == 0)
                    {
                        return Err(RzupError::InvalidVersion(format!(
                            "{v}\n\n  {}: invalid date format YYYY.MM.DD",
                            "tip".green()
                        )));
                    }

                    Version::new(
                        parts[0].parse().unwrap_or(0),
                        parts[1].parse().unwrap_or(0),
                        parts[2].parse().unwrap_or(0),
                    )
                }
                // semver parsing for all others
                _ => Version::parse(&v).map_err(|_| {
                    RzupError::InvalidVersion(format!(
                        "{v}\n\n  {}: use semantic version (e.g. 1.0.0)",
                        "tip".green()
                    ))
                })?,
            }),
            None => None,
        };

        match self.name {
            None => {
                rzup.install_all(self.force)?;
            }
            Some(name) => {
                if name != "self" {
                    rzup.install_component(&name.parse()?, version, self.force)?;
                } else {
                    // update/install rzup by downloading and executing the installation script
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
                            RzupError::Other(format!("Failed to execute update script: {e}"))
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

        for component in &components {
            let versions = rzup.list_versions(component)?;
            if !versions.is_empty() {
                println!("\n{component}");

                let active_version = rzup.get_active_version(component)?;
                let current_version = rzup.settings().get_active_version(component);

                let mut sorted_versions = versions.clone();
                sorted_versions.sort_by(|a, b| b.cmp(a)); // sort newest to oldest

                for version in sorted_versions {
                    let is_active = active_version
                        .as_ref()
                        .map_or(false, |(v, _)| v == &version);
                    let marker = if is_active { "* " } else { "  " };
                    println!("{}{version}", marker.bold());
                }

                // Only show warning if version in settings doesn't exist in versions list
                if let Some(settings_version) = current_version {
                    if !versions.contains(&settings_version) {
                        println!(
                            "! Version {settings_version} specified in settings.toml is not installed",
                        );
                        println!(
                            "  Please use 'rzup use {component} <VERSION>' to switch active component",
                        );
                    }
                }
            }
        }
        println!(
            "\n{}: {}",
            "rzup home".bold(),
            rzup.environment.root_dir().display()
        );
        Ok(())
    }
}

#[derive(Parser)]
pub(crate) struct UseCommand {
    /// Name of component to activate
    #[arg(value_parser=component_parser())]
    name: String,
    /// Version of component to activate
    version: String,
}

impl UseCommand {
    pub(crate) fn execute(self, rzup: &mut Rzup) -> Result<()> {
        let version = Version::parse(&self.version)
            .map_err(|_| RzupError::InvalidVersion(self.version.clone()))?;
        let component = self.name.parse()?;
        if rzup.version_exists(&component, &version)? {
            rzup.set_active_version(&component, version.clone())?;
            println!("Successfully set {component} version {version} as active",);
        } else {
            println!(
                "! Version {version} of {component} is not installed.\n  Please use 'rzup install {component} {version}' to install",
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

        for component in &components {
            rzup.emit(RzupEvent::CheckUpdates {
                id: Some(component.to_string()),
            });

            let latest_version = rzup.get_latest_version(component)?;
            let installed_versions = rzup.list_versions(component)?;

            if let Some(max_installed) = installed_versions.iter().max() {
                if !rzup.version_exists(component, &latest_version)? {
                    results.push(format!(
                        "{} - {} : {max_installed} -> {latest_version}",
                        component.to_string().bold(),
                        "Update Available".bold().yellow(),
                    ));
                } else {
                    results.push(format!(
                        "{} - {} : {max_installed}",
                        component.to_string().bold(),
                        "Up to date".bold().green(),
                    ));
                }
            }
        }

        rzup.emit(RzupEvent::CheckUpdates { id: None });

        for result in results {
            println!("{result}");
        }

        Ok(())
    }
}

#[derive(Parser)]
pub(crate) struct UninstallCommand {
    /// Name of component to uninstall
    #[arg(value_parser=component_parser())]
    name: String,
    /// Version of the component to uninstall
    version: String,
}

impl UninstallCommand {
    pub(crate) fn execute(&self, rzup: &mut Rzup) -> Result<()> {
        let version = Version::parse(&self.version)
            .map_err(|_| RzupError::InvalidVersion(self.version.clone()))?;
        rzup.uninstall_component(&self.name.parse()?, version)
    }
}
