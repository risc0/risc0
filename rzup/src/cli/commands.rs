// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use crate::components::Component;
use crate::error::Result;
use crate::events::RzupEvent;
use crate::{Rzup, RzupError};

use clap::{ArgGroup, Args, Parser, Subcommand};
use colored::Colorize;
use semver::Version;

use std::path::PathBuf;

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

pub fn install_help() -> String {
    let default_components_str = Component::iter()
        .filter(|c| c.install_by_default())
        .map(|c| c.as_str())
        .collect::<Vec<_>>()
        .join(", ");

    format!(
        "Discussion:
    Installs a component (or all default components) of a particular version.

    The default components are: [{default_components_str}]

    If no version is specified, the latest version is used.

    Requires the given version to not be already installed, unless the
    `--force` flag is provided, in which case it will delete the existing
    version first.

    When communicating with GitHub, it tries using authentication. This can
    be useful to get around rate-limiting. It attempts to get a token from the
    `GITHUB_TOKEN` environment variable, then from ~/.config/gh/hosts.yml.

    The default version of the component is updated to the version that was
    just installed."
    )
}

#[derive(Parser)]
pub(crate) struct InstallCommand {
    /// Name of component to install (e.g. rust). If not provided, installs all default components.
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

fn parse_version(name: Option<&str>, v: &str) -> Result<Version> {
    // special handling for cpp date-based versions
    // TODO: Move away from date version tags to semver
    if name.is_some_and(|n| n == "cpp" || n == "gdb") {
        return parse_cpp_version(v);
    }

    Version::parse(v).map_err(|_| {
        RzupError::InvalidVersion(format!(
            "{v}\n\n  {}: use semantic version (e.g. 1.0.0)",
            "tip".green()
        ))
    })
}

impl InstallCommand {
    fn parse_version(&self) -> Result<Option<Version>> {
        let Some(v) = &self.version else {
            return Ok(None);
        };
        Ok(Some(parse_version(self.name.as_deref(), v)?))
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
            rzup.install_default(self.force)?;
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
                if let Some(settings_version) = current_version
                    && !versions.contains(&settings_version)
                {
                    rzup.print(format!(
                        "! Version {settings_version} specified in settings.toml is not installed",
                    ));
                    rzup.print(format!(
                        "  Please use 'rzup use {component} <VERSION>' to switch default component",
                    ));
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
#[command(group(
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

pub const PUBLISH_HELP: &str = "Discussion:
    Tools for publishing a component to S3.

    The create-archive sub-command creates a tar.xz file to send to S3.

    The upload sub-command uploads the tar.xz file to S3 as a component with a particular version
    and optional target.

    The set-version sub-command sets the latest version of a component.

    upload and set-version require that AWS credentials be available in the environment.
";

#[derive(Args)]
#[group(required = true, multiple = false)]
struct TargetGroup {
    /// Is the component the same for all targets
    #[arg(long, conflicts_with = "target_triple")]
    target_agnostic: bool,
    /// The target triple of the component
    #[arg(long, conflicts_with = "target_agnostic")]
    target_triple: Option<String>,
}

#[derive(Parser)]
pub struct PublishUploadCommand {
    /// Name of component to publish (e.g. rust).
    #[arg(value_parser=parser("publish"))]
    name: String,
    /// Version of the component to publish (e.g. 1.0.0).
    version: String,
    #[command(flatten)]
    target_group: TargetGroup,
    /// If the component at the given target / version already exists, replace it
    #[arg(long)]
    force: bool,
    /// The path to the archive
    payload: PathBuf,
}

#[derive(Parser)]
pub struct PublishSetLatestCommand {
    /// Name of component to update the latest version of (e.g. rust).
    #[arg(value_parser=parser("publish"))]
    name: String,
    /// Version to set (e.g. 1.0.0).
    version: String,
}

#[derive(Parser)]
pub struct PublishCreateArtifactCommand {
    /// Path to directory or file to create .tar.xz from.
    #[arg(long)]
    input: PathBuf,
    /// Output path to .tar.xz file we are creating
    #[arg(long)]
    output: PathBuf,
    /// The compression level, 0-9
    #[arg(long, default_value = "6")]
    compression_level: u32,
}

#[derive(Subcommand)]
pub(crate) enum PublishCommand {
    /// Uploads an artifact to S3 as a component.
    ///
    /// Each version of a component is either tagged with a target, or is target agnostic. A
    /// particular version can only have one target-agnostic artifact, or many target specific
    /// artifacts, but each target may only have one artifact each.
    ///
    /// Requires that AWS credentials be available in the environment.
    Upload(PublishUploadCommand),
    /// Sets the latest version for a component on S3.
    ///
    /// This will cause rzup install and rzup check to consider the given version as the latest.
    ///
    /// Requires that AWS credentials be available in the environment.
    SetLatest(PublishSetLatestCommand),
    /// Creates an artifact by creating a tar.xz file.
    ///
    /// The given input path can either be a directory or a file. If the path is a directory, all
    /// the contents are added and at a path relative to the directory root. If the input is a
    /// file, the file is added to the root of the archive.
    CreateArtifact(PublishCreateArtifactCommand),
}

impl PublishCommand {
    #[cfg_attr(not(feature = "publish"), allow(unused_variables))]
    pub(crate) fn execute(self, rzup: &mut Rzup) -> Result<()> {
        #[cfg(feature = "publish")]
        match self {
            Self::Upload(cmd) => {
                let version = parse_version(Some(&cmd.name), &cmd.version)?;
                let platform = cmd
                    .target_group
                    .target_triple
                    .map(|tt| {
                        crate::Platform::from_target_triple(&tt).ok_or_else(|| {
                            RzupError::Other("unsupported target-triple {tt}".into())
                        })
                    })
                    .transpose()?;

                let name = cmd.name.parse()?;
                rzup.publish_upload(&name, &version, platform, &cmd.payload, cmd.force)?;

                Ok(())
            }
            Self::SetLatest(cmd) => {
                let version = parse_version(Some(&cmd.name), &cmd.version)?;
                let name = cmd.name.parse()?;
                rzup.publish_set_latest(&name, &version)?;

                Ok(())
            }
            Self::CreateArtifact(cmd) => {
                rzup.publish_create_artifact(&cmd.input, &cmd.output, cmd.compression_level)?;

                Ok(())
            }
        }

        #[cfg(not(feature = "publish"))]
        Err(RzupError::Other("publish feature not enabled".into()))
    }
}
