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

            // Set active version if none exists
            if self.settings.get_active_version(component_id).is_none() {
                if let Ok(versions) = self.list_component_versions(env, component_id) {
                    if let Some(latest) = versions.into_iter().max() {
                        self.settings.set_active_version(component_id, &latest);
                    }
                }
            }
        }

        Ok(())
    }

    pub fn list_component_versions(&self, env: &Environment, id: &str) -> Result<Vec<Version>> {
        let mut versions = Vec::new();
        let component_dir = Paths::get_component_dir(env, id)?;

        if !component_dir.exists() {
            return Ok(versions);
        }

        let component_suffix = format!("-{}", id);

        for entry in std::fs::read_dir(component_dir)? {
            let entry = entry?;
            if !entry.path().is_dir() {
                continue;
            }

            let version = entry
                .file_name()
                .to_string_lossy()
                .strip_prefix('v')
                .and_then(|v| v.strip_suffix(&component_suffix))
                .and_then(|v| Version::parse(v).ok());

            if let Some(version) = version {
                versions.push(version);
            }
        }

        Ok(versions)
    }

    pub fn get_active_component_version(
        &self,
        env: &Environment,
        id: &str,
    ) -> Result<Option<(Version, std::path::PathBuf)>> {
        if let Some(version) = self.settings.get_active_version(id) {
            if Paths::version_exists(env, id, &version)? {
                let path = Paths::get_version_dir(env, id, &version)?;
                return Ok(Some((version, path)));
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
        let (component_to_install, version_to_install) = if component.is_virtual() {
            if let Some(parent_id) = component.parent_component() {
                (self.create_component(parent_id)?, version)
            } else {
                return Err(RzupError::ComponentNotFound(format!(
                    "Virtual component {} has no parent",
                    id
                )));
            }
        } else {
            (component, version)
        };

        let version = match version_to_install {
            Some(v) => v,
            None => component_to_install.get_latest_version(env)?,
        };

        if !force && Paths::version_exists(env, id, &version)? {
            env.emit(RzupEvent::ComponentAlreadyInstalled {
                id: id.to_string(),
                version: version.to_string(),
            });
            return Ok(());
        }

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
