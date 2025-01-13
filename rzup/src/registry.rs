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

use enumset::EnumSet;
use semver::Version;

#[derive(Default, Debug)]
pub(crate) struct Registry {
    pub(crate) components: EnumSet<Component>,
    settings: Settings,
    base_urls: BaseUrls,
}

impl Registry {
    pub fn new(env: &Environment, base_urls: BaseUrls) -> Result<Self> {
        let settings = Settings::load(env)?;
        Ok(Self {
            components: EnumSet::new(),
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

    pub fn scan_environment(&mut self, env: &Environment) -> Result<()> {
        env.emit(RzupEvent::Debug {
            message: format!("Scanning environment at {}", env.root_dir().display()),
        });

        self.components.clear();

        for component in Component::iter() {
            env.emit(RzupEvent::Debug {
                message: format!("Registering component: {component}"),
            });

            self.register_component(component);

            // Check if we already have an active version set
            if self.settings.get_active_version(&component).is_none() {
                let mut all_versions = self.list_component_versions(env, &component)?;

                all_versions.sort_by(|a, b| b.cmp(a));

                // If we found any versions, set the highest one as active
                if let Some(highest_version) = all_versions.first() {
                    env.emit(RzupEvent::Debug {
                        message: format!(
                            "Setting highest version {highest_version} as active for {component}",
                        ),
                    });
                    self.settings
                        .set_active_version(&component, highest_version);
                }
            }
        }

        self.settings.save(env)?;
        Ok(())
    }

    pub fn list_component_versions(
        &self,
        env: &Environment,
        component: &Component,
    ) -> Result<Vec<Version>> {
        let mut versions = Vec::new();

        // Handle virtual components first
        if self.components.contains(*component) {
            if let Some(parent_id) = component.parent_component() {
                env.emit(RzupEvent::Debug {
                    message: format!("Component {component} using parent {parent_id}"),
                });
                return self.list_component_versions(env, &parent_id);
            }
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
        if self.components.contains(*component) {
            if let Some(parent_id) = component.parent_component() {
                return self.get_active_component_version(env, &parent_id);
            }
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
        Ok(())
    }

    pub fn list_components(&self) -> Vec<Component> {
        self.components.iter().collect()
    }

    fn register_component(&mut self, component: Component) {
        self.components.insert(component);
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

        // Create necessary directories before installation
        Paths::create_version_dirs(env, &component_to_install, &version)?;

        // Install component
        components::install(
            &component_to_install,
            env,
            &self.base_urls,
            Some(&version),
            force,
        )?;

        // Update settings
        self.settings
            .set_active_version(&component_to_install, &version);
        self.settings.save(env)?;

        Ok(())
    }

    pub fn install_all_components(&mut self, env: &Environment, force: bool) -> Result<()> {
        for component in Component::iter() {
            self.install_component(env, &component, None, force)?;
        }
        Ok(())
    }

    pub fn uninstall_component(
        &mut self,
        env: &Environment,
        component: &Component,
        version: Version,
    ) -> Result<()> {
        components::uninstall(component, env, &version)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::{http_test_harness, tests::invalid_base_urls, BaseUrls};
    use tempfile::TempDir;

    fn setup_test_registry(base_urls: BaseUrls) -> (TempDir, Environment, Registry) {
        let tmp_dir = TempDir::new().unwrap();
        let env = Environment::with_root(tmp_dir.path()).unwrap();

        let registry = Registry::new(&env, base_urls).unwrap();
        (tmp_dir, env, registry)
    }

    #[test]
    fn test_registry_initialization() {
        let (_tmp_dir, _env, registry) = setup_test_registry(invalid_base_urls());
        assert!(registry.list_components().is_empty());
    }

    fn test_version_management(base_urls: BaseUrls) {
        let (_tmp_dir, env, mut registry) = setup_test_registry(base_urls);
        let version = Version::new(1, 0, 0);
        let component = Component::CargoRiscZero;

        // Test installation
        registry
            .install_component(&env, &component, Some(version.clone()), false)
            .unwrap();

        // Test version listing
        let versions = registry.list_component_versions(&env, &component).unwrap();
        assert!(versions.contains(&version));

        // Test active version
        let active = registry
            .get_active_component_version(&env, &component)
            .unwrap();
        assert_eq!(active.map(|(v, _)| v), Some(version.clone()));
    }

    http_test_harness!(test_version_management);
}
