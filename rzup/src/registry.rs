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
use crate::components::{self, Component};
use crate::env::Environment;
use crate::error::Result;
use crate::paths::Paths;
use crate::settings::Settings;
use crate::{BaseUrls, RzupError, RzupEvent};

use semver::Version;
use std::collections::BTreeMap;
use std::path::PathBuf;

fn parse_version_from_entry(
    env: &Environment,
    component: &Component,
    entry: &std::fs::DirEntry,
) -> Result<Option<Version>> {
    if !entry.path().is_dir() {
        return Ok(None);
    }

    let dir_name = entry.file_name().to_string_lossy().to_string();

    match Paths::parse_version_from_path(&dir_name, component) {
        Some(version) => {
            env.emit(RzupEvent::Debug {
                message: format!("Successfully parsed version {version} from {dir_name}",),
            });
            Ok(Some(version))
        }
        None => {
            env.emit(RzupEvent::Debug {
                message: format!("Failed to parse version from directory: {dir_name}"),
            });
            Ok(None)
        }
    }
}

#[derive(Default, Debug)]
pub(crate) struct Registry {
    settings: Settings,
    base_urls: BaseUrls,
}

impl Registry {
    pub fn new(env: &Environment, base_urls: BaseUrls) -> Result<Self> {
        let settings = Settings::load(env)?;
        Ok(Self {
            settings,
            base_urls,
        })
    }

    pub fn settings(&self) -> &Settings {
        &self.settings
    }

    pub fn base_urls(&self) -> &BaseUrls {
        &self.base_urls
    }

    pub fn list_component_versions(
        env: &Environment,
        component: &Component,
    ) -> Result<Vec<(Version, PathBuf)>> {
        let mut versions: BTreeMap<Version, PathBuf> = BTreeMap::new();

        // Handle virtual components first
        if let Some(parent_id) = component.parent_component() {
            env.emit(RzupEvent::Debug {
                message: format!("Component {component} using parent {parent_id}"),
            });
            return Self::list_component_versions(env, &parent_id);
        }

        let component_dir = Paths::get_component_dir(env, component);
        env.emit(RzupEvent::Debug {
            message: format!("Scanning directory: {}", component_dir.display()),
        });

        if !component_dir.exists() {
            env.emit(RzupEvent::Debug {
                message: format!("Directory does not exist: {}", component_dir.display()),
            });
            return Ok(vec![]);
        }

        for entry in std::fs::read_dir(component_dir)? {
            let entry = entry?;
            if let Some(version) = parse_version_from_entry(env, component, &entry)? {
                versions.insert(version, entry.path());
            }
        }

        // Sort versions from newest to oldest
        Ok(versions.into_iter().rev().collect())
    }

    pub fn get_default_component_version(
        &self,
        env: &Environment,
        component: &Component,
    ) -> Result<Option<(Version, std::path::PathBuf)>> {
        let component_installed = component.parent_component().unwrap_or(*component);
        if let Some(version) = self.settings.get_default_version(component) {
            if let Some(path) = Paths::find_version_dir(env, &component_installed, &version)? {
                return Ok(Some((version, path)));
            }
        }

        // Components installed by old versions might leave us in a state where there is a
        // component installed, but no active version
        if let Some(version) = self.find_highest_installed_version(env, component)? {
            if let Some(path) = Paths::find_version_dir(env, &component_installed, &version)? {
                return Ok(Some((version, path)));
            }
        }

        Ok(None)
    }

    pub fn set_default_component_version(
        &mut self,
        env: &Environment,
        component: &Component,
        version: Version,
    ) -> Result<()> {
        let component_installed = component.parent_component().unwrap_or(*component);
        if Paths::find_version_dir(env, &component_installed, &version)?.is_none() {
            return Err(RzupError::InvalidVersion(format!(
                "Version {version} is not installed",
            )));
        }

        env.emit(RzupEvent::Debug {
            message: format!("Setting component {component} version: {version} as default",),
        });

        self.settings.set_default_version(component, &version);
        self.settings.save(env)?;

        components::set_default(env, component, &version)?;

        Ok(())
    }

    fn version_or_latest(
        &self,
        env: &Environment,
        component: &Component,
        version: Option<Version>,
    ) -> Result<Version> {
        if let Some(v) = version {
            Ok(v)
        } else {
            env.emit(RzupEvent::Debug {
                message: format!("No version specified, fetching latest for {component}"),
            });
            components::get_latest_version(component, env, &self.base_urls)
        }
    }

    pub fn install_component(
        &mut self,
        env: &Environment,
        component: &Component,
        version: Option<Version>,
        force: bool,
    ) -> Result<()> {
        env.emit(RzupEvent::Debug {
            message: format!(
                "Installing component {component} (version: {}, force: {force})",
                version
                    .as_ref()
                    .map(|v| v.to_string())
                    .unwrap_or("latest".into())
            ),
        });

        let component_to_install = component.parent_component().unwrap_or(*component);
        let version = self.version_or_latest(env, &component_to_install, version)?;

        let _lock_file = env.flock(&format!(".{component_to_install}-{version}"))?;

        if !force {
            if let Some(path) = Paths::find_version_dir(env, &component_to_install, &version)? {
                env.emit(RzupEvent::ComponentAlreadyInstalled {
                    id: component.to_string(),
                    version: version.to_string(),
                });
                env.emit(RzupEvent::Debug {
                    message: format!(
                        "Component {component} already installed at path {}",
                        path.display()
                    ),
                });
                self.set_default_component_version(env, component, version.clone())?;
                return Ok(());
            }
        }

        components::install(component, env, &self.base_urls, &version, force)?;

        self.set_default_component_version(env, component, version.clone())?;

        if self
            .settings
            .get_default_version(&component_to_install)
            .is_none()
        {
            self.set_default_component_version(env, &component_to_install, version)?;
        }

        Ok(())
    }

    pub fn install_all_components(&mut self, env: &Environment, force: bool) -> Result<()> {
        for component in Component::iter() {
            self.install_component(env, &component, None, force)?;
        }
        Ok(())
    }

    fn find_highest_installed_version(
        &self,
        env: &Environment,
        component: &Component,
    ) -> Result<Option<Version>> {
        let all_versions = Self::list_component_versions(env, component)?;

        // If we found any versions, set the highest one as default
        if let Some((highest_version, _)) = all_versions.first() {
            env.emit(RzupEvent::Debug {
                message: format!(
                    "Setting highest version {highest_version} as default for {component}",
                ),
            });
            return Ok(Some(highest_version.clone()));
        }
        Ok(None)
    }

    fn find_new_default_version(
        &mut self,
        env: &Environment,
        removed_version: &Version,
        component: &Component,
    ) -> Result<()> {
        // Check if we uninstalled the default version
        if self
            .settings
            .get_default_version(component)
            .is_some_and(|version| &version == removed_version)
        {
            if let Some(new_version) = self.find_highest_installed_version(env, component)? {
                self.set_default_component_version(env, component, new_version)?;
            }
        }
        Ok(())
    }

    pub fn uninstall_component(
        &mut self,
        env: &Environment,
        component: &Component,
        version: Version,
    ) -> Result<()> {
        if let Some(parent) = component.parent_component() {
            components::uninstall(&parent, env, &version)?;
            self.find_new_default_version(env, &version, &parent)?;
        } else {
            components::uninstall(component, env, &version)?;
        }
        env.emit(RzupEvent::Uninstalled {
            id: component.to_string(),
            version: version.to_string(),
        });

        self.find_new_default_version(env, &version, component)?;

        Ok(())
    }
}
