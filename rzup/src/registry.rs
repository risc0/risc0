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
use crate::components::cargo_risczero::CargoRiscZero;
use crate::components::r0vm::R0Vm;
use crate::components::rust::RustToolchain;
use crate::components::Component;
use crate::env::Environment;
use crate::error::Result;
use crate::paths::Paths;
use crate::settings::Settings;
use crate::RzupError;
use crate::RzupEvent;

use semver::Version;
use std::collections::HashMap;

static DEFAULT_COMPONENTS: &[&str] = &["rust", "cargo-risczero"];

#[derive(Default, Debug)]
pub(crate) struct Registry {
    pub(crate) components: HashMap<&'static str, Box<dyn Component>>,
    settings: Settings,
}

impl Registry {
    pub fn new(env: &Environment) -> Result<Self> {
        let settings = Settings::load(env)?;
        Ok(Self {
            components: HashMap::new(),
            settings,
        })
    }

    pub fn settings(&self) -> &Settings {
        &self.settings
    }

    pub fn scan_environment(&mut self, env: &Environment) -> Result<()> {
        env.emit(RzupEvent::Debug {
            message: format!("Scanning environment at {}", env.root_dir().display()),
        });

        self.components.clear();

        let components: Vec<Box<dyn Component>> = vec![
            Box::new(RustToolchain),
            Box::new(CargoRiscZero),
            Box::new(R0Vm),
        ];

        for component in components {
            let component_id = component.id();
            env.emit(RzupEvent::Debug {
                message: format!("Registering component: {}", component_id),
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
                            "Setting highest version {} as active for {}",
                            highest_version, component_id
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
                    message: format!("Component {} using parent {}", id, parent_id),
                });
                return self.list_component_versions(env, parent_id);
            }
        }

        let component_dir = Paths::get_component_dir(env, id)?;
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

            match Paths::parse_version_from_path(&dir_name, id) {
                Some(version) => {
                    env.emit(RzupEvent::Debug {
                        message: format!(
                            "Successfully parsed version {} from {}",
                            version, dir_name
                        ),
                    });
                    if !versions.contains(&version) {
                        versions.push(version.clone());
                    }
                }
                None => {
                    env.emit(RzupEvent::Debug {
                        message: format!("Failed to parse version from directory: {}", dir_name),
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
                let version_dir = Paths::get_version_dir(env, id, &version)?;
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
                "Version {} is not installed",
                version
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
                "Installing component {} (version: {:?}, force: {})",
                id, version, force
            ),
        });

        let component = self.create_component(id)?;

        // Handle virtual components
        let (component_to_install, version_to_install) =
            if let Some(parent_id) = component.parent_component() {
                (self.create_component(parent_id)?, version)
            } else {
                (component, version)
            };

        let version = match version_to_install {
            Some(v) => v,
            None => {
                env.emit(RzupEvent::Debug {
                    message: format!("No version specified, fetching latest for {}", id),
                });
                component_to_install.get_latest_version(env)?
            }
        };

        if !force && Paths::version_exists(env, id, &version)? {
            env.emit(RzupEvent::ComponentAlreadyInstalled {
                id: id.to_string(),
                version: version.to_string(),
            });
            return Ok(());
        }

        // Create necessary directories before installation
        Paths::create_version_dirs(env, id, &version)?;

        // Install component
        component_to_install.install(env, Some(&version), force)?;

        // Update settings
        self.settings.set_active_version(id, &version);
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
        component.uninstall(env, &version)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use tempfile::TempDir;

    fn setup_test_registry() -> (TempDir, Environment, Registry) {
        let tmp_dir = TempDir::new().unwrap();
        let env = Environment::with_root(tmp_dir.path()).unwrap();
        let registry = Registry::new(&env).unwrap();
        (tmp_dir, env, registry)
    }

    #[test]
    fn test_registry_initialization() {
        let (_tmp_dir, _env, registry) = setup_test_registry();
        assert!(registry.list_components().is_empty());
    }

    #[test]
    #[ignore = "requires GitHub API access"]
    fn test_version_management() {
        let (_tmp_dir, env, mut registry) = setup_test_registry();
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
}
