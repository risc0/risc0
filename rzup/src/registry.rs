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
    ) -> Result<Vec<Version>> {
        let mut versions = Vec::new();

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
            return Ok(versions);
        }

        for entry in std::fs::read_dir(component_dir)? {
            let entry = entry?;
            if !entry.path().is_dir() {
                continue;
            }

            let dir_name = entry.file_name().to_string_lossy().to_string();

            if !dir_name.contains(component.as_str()) {
                continue;
            }

            match Paths::parse_version_from_path(&dir_name, component) {
                Some(version) => {
                    env.emit(RzupEvent::Debug {
                        message: format!("Successfully parsed version {version} from {dir_name}",),
                    });
                    if !versions.contains(&version) {
                        versions.push(version.clone());
                    }
                }
                None => {
                    env.emit(RzupEvent::Debug {
                        message: format!("Failed to parse version from directory: {dir_name}"),
                    });
                }
            }
        }

        // Sort versions from newest to oldest
        versions.sort_by(|a, b| b.cmp(a));

        Ok(versions)
    }

    pub fn get_active_component_version(
        &self,
        env: &Environment,
        component: &Component,
    ) -> Result<Option<(Version, std::path::PathBuf)>> {
        // For virtual components, get active version from parent
        if let Some(parent_id) = component.parent_component() {
            return self.get_active_component_version(env, &parent_id);
        }

        if let Some(version) = self.settings.get_active_version(component) {
            if Paths::version_exists(env, component, &version)? {
                let version_dir = Paths::get_version_dir(env, component, &version);
                return Ok(Some((version, version_dir)));
            }
        }
        Ok(None)
    }

    pub fn set_active_component_version(
        &mut self,
        env: &Environment,
        component: &Component,
        version: Version,
    ) -> Result<()> {
        if !Paths::version_exists(env, component, &version)? {
            return Err(RzupError::InvalidVersion(format!(
                "Version {version} is not installed",
            )));
        }

        self.settings.set_active_version(component, &version);
        self.settings.save(env)?;

        components::set_active(env, component, &version)?;

        Ok(())
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
                "Installing component {component} (version: {:?}, force: {force})",
                version
            ),
        });

        // Handle virtual components
        let (component_to_install, version_to_install) =
            if let Some(parent_id) = component.parent_component() {
                (parent_id, version)
            } else {
                (*component, version)
            };

        let version = match version_to_install {
            Some(v) => v,
            None => {
                env.emit(RzupEvent::Debug {
                    message: format!(
                        "No version specified, fetching latest for {component_to_install}"
                    ),
                });
                components::get_latest_version(&component_to_install, env, &self.base_urls)?
            }
        };

        if !force && Paths::version_exists(env, &component_to_install, &version)? {
            env.emit(RzupEvent::ComponentAlreadyInstalled {
                id: component.to_string(),
                version: version.to_string(),
            });
            return Ok(());
        }

        // Install component
        components::install(&component, env, &self.base_urls, &version, force)?;

        self.set_active_component_version(env, &component_to_install, version.clone())?;
        self.set_active_component_version(env, component, version)?;

        Ok(())
    }

    pub fn install_all_components(&mut self, env: &Environment, force: bool) -> Result<()> {
        for component in Component::iter() {
            self.install_component(env, &component, None, force)?;
        }
        Ok(())
    }

    fn find_new_active_version(&mut self, env: &Environment, component: &Component) -> Result<()> {
        // Check if we uninstalled the active version
        if self.get_active_component_version(env, component)?.is_none() {
            let mut all_versions = Self::list_component_versions(env, component)?;

            all_versions.sort_by(|a, b| b.cmp(a));

            // If we found any versions, set the highest one as active
            if let Some(highest_version) = all_versions.first() {
                env.emit(RzupEvent::Debug {
                    message: format!(
                        "Setting highest version {highest_version} as active for {component}",
                    ),
                });
                self.set_active_component_version(env, &component, highest_version.clone())?;
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
            self.find_new_active_version(env, &parent)?;
        } else {
            components::uninstall(component, env, &version)?;
        }
        self.find_new_active_version(env, component)?;

        Ok(())
    }
}
