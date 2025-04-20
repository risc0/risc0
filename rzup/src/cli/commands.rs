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

use clap::{ArgGroup, Parser};
use colored::Colorize;
use semver::Version;

fn parser(cmd: &str) -> Vec<&'static str> {
    match cmd {
        "build" => vec![Component::RustToolchain.as_str()],
        "default" => Component::iter().map(|c| c.as_str()).collect(),
        _ => Component::iter()
            .map(|c| c.as_str())
            .chain(std::iter::once("self"))
            .collect(),
    }
}

pub const INSTALL_HELP: &str = "Discussion:
    Installs a component (or all components) of a particular version.

    If no version is specified, the latest version is used.

    Requires the given version to not be already installed, unless the
    `--force` flag is provided, in which case it will delete the existing
    version first.

    When communicating with GitHub, it tries using authentication. This can
    be useful to get around rate-limiting. It attempts to get a token from the
    `GITHUB_TOKEN` environment variable, then from ~/.config/gh/hosts.yml.

    The default version of the component is updated to the version that was
    just installed.";

#[derive(Parser)]
pub(crate) struct InstallCommand {
    /// Name of component to install (e.g. rust). If not provided, installs all components.
    #[arg(value_parser=parser("install"))]
    name: Option<String>,
    /// Version of the component to install (e.g. 1.0.0). If not provided, installs the latest version.
    version: Option<String>,
    /// Force the installation
    #[arg(short, long)]
    force: bool,
}

fn parse_cpp_version(v: &str) -> Result<Version> {
    crate::distribution::parse_cpp_version(v).map_err(|_| {
        RzupError::InvalidVersion(format!(
            "{v}\n\n  {}: invalid date format YYYY.MM.DD",
            "tip".green()
        ))
    })
}

impl InstallCommand {
    fn parse_version(&self) -> Result<Option<Version>> {
        let Some(v) = &self.version else {
            return Ok(None);
        };

        // special handling for cpp date-based versions
        // TODO: Move away from date version tags to semver
        if self.name.as_ref().is_some_and(|n| n == "cpp") {
            return Ok(Some(parse_cpp_version(v)?));
        }

        Ok(Some(Version::parse(v).map_err(|_| {
            RzupError::InvalidVersion(format!(
                "{v}\n\n  {}: use semantic version (e.g. 1.0.0)",
                "tip".green()
            ))
        })?))
    }

    pub(crate) fn execute(self, rzup: &mut Rzup) -> Result<()> {
        let version = self.parse_version()?;

        if let Some(name) = &self.name {
            if name != "self" {
                rzup.install_component(&name.parse()?, version, self.force)?;
            } else {
                rzup.self_update()?
            }
        } else {
            rzup.install_all(self.force)?;
        }

        Ok(())
    }
}

pub const SHOW_HELP: &str = "Discussion:
    Lists the installed components and their versions.

    Default component versions are marked with a '*'.";

#[derive(Parser)]
pub(crate) struct ShowCommand;

impl ShowCommand {
    pub(crate) fn execute(self, rzup: &Rzup) -> Result<()> {
        rzup.print(format!("{}", "Installed components:".bold()));
        rzup.print(format!("{}", "--------------------".bold()));

        for component in Component::iter() {
            let versions = rzup.list_versions(&component)?;
            if !versions.is_empty() {
                rzup.print(format!("\n{component}"));

                let default_version = rzup.get_default_version(&component)?;
                let current_version = rzup.settings().get_default_version(&component);

                let mut sorted_versions = versions.clone();
                sorted_versions.sort_by(|a, b| b.cmp(a)); // sort newest to oldest

                for version in sorted_versions {
                    let is_default = default_version.as_ref().is_some_and(|(v, _)| v == &version);
                    let marker = if is_default { "* " } else { "  " };
                    rzup.print(format!("{}{version}", marker.bold()));
                }

                // Only show warning if version in settings doesn't exist in versions list
                if let Some(settings_version) = current_version {
                    if !versions.contains(&settings_version) {
                        rzup.print(format!(
                            "! Version {settings_version} specified in settings.toml is not installed",
                        ));
                        rzup.print(format!(
                            "  Please use 'rzup use {component} <VERSION>' to switch default component",
                        ));
                    }
                }
            }
        }
        rzup.print(format!(
            "\n{}: {}",
            "rzup home".bold(),
            rzup.environment.risc0_dir().display()
        ));
        Ok(())
    }
}

pub const DEFAULT_HELP: &str = "Discussion:
    Sets the default version of a given component.

    The given component must have been installed previously.";

#[derive(Parser)]
pub(crate) struct DefaultCommand {
    /// Name of component to activate
    #[arg(value_parser=parser("default"))]
    name: String,
    /// Version of component to activate
    version: String,
}

impl DefaultCommand {
    pub(crate) fn execute(self, rzup: &mut Rzup) -> Result<()> {
        let version = Version::parse(&self.version)
            .map_err(|_| RzupError::InvalidVersion(self.version.clone()))?;
        let component = self.name.parse()?;
        if rzup.version_exists(&component, &version)? {
            rzup.set_default_version(&component, version.clone())?;
            rzup.print(format!(
                "Successfully set {component} version {version} as default"
            ));
        } else {
            rzup.print(format!(
                "! Version {version} of {component} is not installed.\n  Please use 'rzup install {component} {version}' to install",
            ));
        }

        Ok(())
    }
}

pub const CHECK_HELP: &str = "Discussion:
    Checks GitHub to see if the latest version of a component is installed or not.

    When communicating with GitHub, it tries using authentication. This can
    be useful to get around rate-limiting. It attempts to get a token from the
    `GITHUB_TOKEN` environment variable, then from ~/.config/gh/hosts.yml.";

#[derive(Parser)]
pub(crate) struct CheckCommand;

impl CheckCommand {
    pub(crate) fn execute(&self, rzup: &Rzup) -> Result<()> {
        let mut results = Vec::new();

        for component in Component::iter() {
            rzup.emit(RzupEvent::CheckUpdates {
                id: Some(component.to_string()),
            });

            let latest_version = rzup.get_latest_version(&component)?;
            let installed_versions = rzup.list_versions(&component)?;

            if let Some(max_installed) = installed_versions.iter().max() {
                if !rzup.version_exists(&component, &latest_version)? {
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
            rzup.print(result.to_string());
        }

        Ok(())
    }
}

pub const UNINSTALL_HELP: &str = "Discussion:
    Uninstalls the given version of a component by removing the files.

    If it is the current default version for that component, the latest
    remaining version is made default.";

#[derive(Parser)]
pub(crate) struct UninstallCommand {
    /// Name of component to uninstall
    #[arg(value_parser=parser("uninstall"))]
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

pub const BUILD_HELP: &str = "Discussion:
    Builds and installs the given component.

    Grabs the source code from GitHub, compiles it, installs it, and makes it
    the default version. The resulting component version contains the commit hash.";

#[derive(Parser)]
#[clap(group(
    ArgGroup::new("mode")
        .args(&["tag_or_commit", "path"])
        .required(true)
))]
pub(crate) struct BuildCommand {
    /// Name of component to build
    #[arg(value_parser=parser("build"))]
    name: String,

    /// Tag or commit of the component to build
    #[arg(short, long)]
    tag_or_commit: Option<String>,

    /// optional local path to build from
    #[arg(short, long)]
    path: Option<String>,
}

impl BuildCommand {
    pub(crate) fn execute(&self, rzup: &mut Rzup) -> Result<()> {
        let component: Component = self.name.parse()?;
        if component != Component::RustToolchain {
            return Err(RzupError::Other(format!("cannot build {component}")));
        }

        rzup.build_rust_toolchain(
            "https://github.com/risc0/rust.git",
            &self.tag_or_commit,
            &self.path,
        )
    }
}
