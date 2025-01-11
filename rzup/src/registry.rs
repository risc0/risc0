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
use crate::components::{
    self, cargo_risczero::CargoRiscZero, cpp::CppToolchain, r0vm::R0Vm, rust::RustToolchain,
    Component,
};
use crate::env::Environment;
use crate::error::Result;
use crate::paths::Paths;
use crate::settings::Settings;
use crate::{BaseUrls, RzupError, RzupEvent};

use semver::Version;
use std::collections::HashMap;

static DEFAULT_COMPONENTS: &[&str] = &["rust", "cargo-risczero", "cpp"];

#[derive(Default, Debug)]
pub(crate) struct Registry {
    pub(crate) components: HashMap<&'static str, Box<dyn Component>>,
    settings: Settings,
    base_urls: BaseUrls,
}

impl Registry {
    pub fn new(env: &Environment, base_urls: BaseUrls) -> Result<Self> {
        let settings = Settings::load(env)?;
        Ok(Self {
            components: HashMap::new(),
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

        let components: Vec<Box<dyn Component>> = vec![
            Box::new(RustToolchain),
            Box::new(CargoRiscZero),
            Box::new(CppToolchain),
            Box::new(R0Vm),
        ];

        for component in components {
            let component_id = component.id();
            env.emit(RzupEvent::Debug {
                message: format!("Registering component: {component_id}"),
            });

            self.register_component(component);

            // Check if we already have an active version set
            if self.settings.get_active_version(component_id).is_none() {
                let mut all_versions = self.list_component_versions(env, component_id)?;

                all_versions.sort_by(|a, b| b.cmp(a));

                // If we found any versions, set the highest one as active
                if let Some(highest_version) = all_versions.first() {
                    env.emit(RzupEvent::Debug {
                        message: format!(
                            "Setting highest version {highest_version} as active for {component_id}",
                        ),
                    });
                    self.settings
                        .set_active_version(component_id, highest_version);
                }
            }
        }

        self.settings.save(env)?;
        Ok(())
    }

    pub fn list_component_versions(&self, env: &Environment, id: &str) -> Result<Vec<Version>> {
        let mut versions = Vec::new();

        // Handle virtual components first
        if let Some(component) = self.components.get(id) {
            if let Some(parent_id) = component.parent_component() {
                env.emit(RzupEvent::Debug {
                    message: format!("Component {id} using parent {parent_id}"),
                });
                return self.list_component_versions(env, parent_id);
            }
        }

        let component_dir = Paths::get_component_dir(env, id);
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

            if !dir_name.contains(id) {
                continue;
            }

            match Paths::parse_version_from_path(&dir_name, id) {
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
        id: &str,
    ) -> Result<Option<(Version, std::path::PathBuf)>> {
        // For virtual components, get active version from parent
        if let Some(component) = self.components.get(id) {
            if let Some(parent_id) = component.parent_component() {
                return self.get_active_component_version(env, parent_id);
            }
        }

        if let Some(version) = self.settings.get_active_version(id) {
            if Paths::version_exists(env, id, &version)? {
                let version_dir = Paths::get_version_dir(env, id, &version);
                return Ok(Some((version, version_dir)));
            }
        }
        Ok(None)
    }

    pub fn set_active_component_version(
        &mut self,
        env: &Environment,
        id: &str,
        version: Version,
    ) -> Result<()> {
        if !Paths::version_exists(env, id, &version)? {
            return Err(RzupError::InvalidVersion(format!(
                "Version {version} is not installed",
            )));
        }

        self.settings.set_active_version(id, &version);
        self.settings.save(env)?;
        Ok(())
    }

    pub fn list_components(&self) -> Vec<&dyn Component> {
        self.components
            .values()
            .map(|boxed| boxed.as_ref())
            .collect()
    }

    fn register_component(&mut self, component: Box<dyn Component>) {
        self.components.insert(component.id(), component);
    }

    pub fn create_component(&self, id: &str) -> Result<Box<dyn Component>> {
        match id {
            "rust" => Ok(Box::new(RustToolchain)),
            "cargo-risczero" => Ok(Box::new(CargoRiscZero)),
            "cpp" => Ok(Box::new(CppToolchain)),
            "r0vm" => Ok(Box::new(R0Vm)),
            _ => Err(RzupError::ComponentNotFound(id.to_string())),
        }
    }

    pub fn install_component(
        &mut self,
        env: &Environment,
        id: &str,
        version: Option<Version>,
        force: bool,
    ) -> Result<()> {
        env.emit(RzupEvent::Debug {
            message: format!(
                "Installing component {id} (version: {:?}, force: {force})",
                version
            ),
        });

        let component = self.create_component(id)?;

        // Handle virtual components
        let (component_to_install, version_to_install, component_id) =
            if let Some(parent_id) = component.parent_component() {
                (self.create_component(parent_id)?, version, parent_id)
            } else {
                (component, version, id)
            };

        let version = match version_to_install {
            Some(v) => v,
            None => {
                env.emit(RzupEvent::Debug {
                    message: format!("No version specified, fetching latest for {component_id}"),
                });
                components::get_latest_version(&component_to_install, env, &self.base_urls)?
            }
        };

        if !force && Paths::version_exists(env, component_id, &version)? {
            env.emit(RzupEvent::ComponentAlreadyInstalled {
                id: id.to_string(),
                version: version.to_string(),
            });
            return Ok(());
        }

        // Create necessary directories before installation
        Paths::create_version_dirs(env, component_id, &version)?;

        // Install component
        components::install(
            &component_to_install,
            env,
            &self.base_urls,
            Some(&version),
            force,
        )?;

        // Update settings
        self.settings.set_active_version(component_id, &version);
        self.settings.save(env)?;

        Ok(())
    }

    pub fn install_all_components(&mut self, env: &Environment, force: bool) -> Result<()> {
        for &component_id in DEFAULT_COMPONENTS {
            self.install_component(env, component_id, None, force)?;
        }
        Ok(())
    }

    pub fn uninstall_component(
        &mut self,
        env: &Environment,
        id: &str,
        version: Version,
    ) -> Result<()> {
        let component = self.create_component(id)?;
        components::uninstall(&component, env, &version)
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
        let component_id = "cargo-risczero";

        // Test installation
        registry
            .install_component(&env, component_id, Some(version.clone()), false)
            .unwrap();

        // Test version listing
        let versions = registry
            .list_component_versions(&env, component_id)
            .unwrap();
        assert!(versions.contains(&version));

        // Test active version
        let active = registry
            .get_active_component_version(&env, component_id)
            .unwrap();
        assert_eq!(active.map(|(v, _)| v), Some(version.clone()));
    }

    http_test_harness!(test_version_management);
}
