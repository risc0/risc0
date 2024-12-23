use crate::components::implementations::{CargoRiscZero, RustToolchain};
use crate::components::Component;
use crate::env::Environment;
use crate::error::Result;
use crate::settings::Settings;
use crate::RzupError;
use crate::RzupEvent;
use semver::Version;
use std::collections::HashMap;
use std::path::PathBuf;

static DEFAULT_COMPONENTS: &[&str] = &["rust", "cargo-risczero"];

#[derive(Debug, Default, Clone)]
pub(crate) struct ComponentVersions {
    pub(crate) versions: HashMap<Version, PathBuf>,
}

impl ComponentVersions {
    fn new() -> Self {
        Self {
            versions: HashMap::new(),
        }
    }

    pub(crate) fn has_version(&self, version: &Version) -> bool {
        self.versions.contains_key(version)
    }

    fn add_version(&mut self, version: Version, path: PathBuf) {
        self.versions.insert(version, path);
    }

    pub(crate) fn get_active_version<'a>(
        &'a self,
        settings: &'a Settings,
        component_id: &str,
    ) -> Option<(&'a Version, &'a PathBuf)> {
        settings
            .get_active_version(component_id)
            .and_then(|v| self.versions.get_key_value(&v))
    }

    pub(crate) fn list_versions(&self) -> Vec<&Version> {
        self.versions.keys().collect()
    }
}

#[derive(Default, Debug)]
pub(crate) struct ComponentRegistry {
    pub(crate) components: HashMap<&'static str, Box<dyn Component>>,
    versions: HashMap<&'static str, ComponentVersions>,
    settings: Settings,
}

impl ComponentRegistry {
    pub(crate) fn new(env: &Environment) -> Result<Self> {
        let settings = Settings::load(env)?;
        Ok(Self {
            components: HashMap::new(),
            versions: HashMap::new(),
            settings,
        })
    }

    pub(crate) fn settings(&self) -> &Settings {
        &self.settings
    }

    fn register_component_versions(
        &mut self,
        component: Box<dyn Component>,
        versions: ComponentVersions,
    ) -> Result<()> {
        let component_id = component.id();

        if versions.versions.is_empty() {
            return Ok(());
        }

        self.register(component);
        self.versions.insert(component_id, versions.clone());

        // set active version if none exists
        if self.settings.get_active_version(component_id).is_none() {
            if let Some(latest) = versions.list_versions().into_iter().max() {
                self.settings.set_active_version(component_id, latest);
            }
        }

        Ok(())
    }

    pub(crate) fn scan_environment(&mut self, env: &Environment) -> Result<()> {
        env.emit(RzupEvent::Debug {
            message: format!("Scanning environment at {}", env.root_dir().display()),
        });

        self.components.clear();
        self.versions.clear();

        let components: Vec<Box<dyn Component>> =
            vec![Box::new(RustToolchain), Box::new(CargoRiscZero)];

        for component in components {
            let component_id = component.id();

            env.emit(RzupEvent::Debug {
                message: format!("Scanning versions for component: {}", component_id),
            });

            let versions = self.scan_component_versions(env, component_id)?;

            env.emit(RzupEvent::Debug {
                message: format!(
                    "Found {} versions for {}",
                    versions.versions.len(),
                    component_id
                ),
            });

            self.register_component_versions(component, versions)?;
        }

        Ok(())
    }

    fn scan_component_versions(&self, env: &Environment, id: &str) -> Result<ComponentVersions> {
        let component_path = env.component_dir(id)?;
        let mut versions = ComponentVersions::new();

        if !component_path.exists() {
            return Ok(versions);
        }

        let component_suffix = format!("-{}", id);

        for entry in std::fs::read_dir(component_path)? {
            let entry = entry?;

            if !entry.path().is_dir() {
                continue;
            }

            let version = entry
                .file_name()
                .to_string_lossy()
                .strip_suffix(&component_suffix)
                .and_then(|v| v.strip_prefix('v'))
                .and_then(|v| Version::parse(v).ok());

            if let Some(version) = version {
                versions.add_version(version, entry.path());
            }
        }

        Ok(versions)
    }

    pub(crate) fn get_component_versions(&self, id: &str) -> Option<&ComponentVersions> {
        self.versions.get(id)
    }

    pub(crate) fn set_active_version(
        &mut self,
        env: &Environment,
        id: &str,
        version: Version,
    ) -> Result<()> {
        if let Some(versions) = self.versions.get(id) {
            if !versions.has_version(&version) {
                return Err(RzupError::InvalidVersion(format!(
                    "Version {} is not installed",
                    version
                )));
            }

            // only set if the version exists
            self.settings.set_active_version(id, &version);
            self.settings.save(env)?;
            Ok(())
        } else {
            Err(RzupError::ComponentNotFound(id.to_string()))
        }
    }

    pub(crate) fn list_components(&self) -> Vec<&dyn Component> {
        self.components
            .values()
            .map(|boxed| boxed.as_ref())
            .collect()
    }

    fn register(&mut self, component: Box<dyn Component>) {
        self.components.insert(component.id(), component);
    }

    fn create_component(id: &str) -> Result<Box<dyn Component>> {
        match id {
            "rust" => Ok(Box::new(RustToolchain)),
            "cargo-risczero" => Ok(Box::new(CargoRiscZero)),
            _ => Err(RzupError::ComponentNotFound(id.to_string())),
        }
    }

    fn needs_installation(&self, id: &str, version: &Version, force: bool) -> bool {
        force
            || self
                .versions
                .get(id)
                .map_or(true, |versions| !versions.has_version(version))
    }

    pub(crate) fn install_component(
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

        let component = Self::create_component(id)?;
        let version = match version {
            Some(v) => v,
            None => component.get_latest_version(env)?,
        };

        if !self.needs_installation(id, &version, force) {
            env.emit(RzupEvent::ComponentAlreadyInstalled {
                id: id.to_string(),
                version: version.to_string(),
            });
            return Ok(());
        }

        if !env.root_dir().exists() {
            std::fs::create_dir_all(env.root_dir())?;
        }

        component.install(env, Some(&version), force)?;

        let versions = self.scan_component_versions(env, id)?;
        let component = Self::create_component(id)?;

        self.settings.set_active_version(id, &version);

        self.register_component_versions(component, versions)?;
        self.settings.save(env)?;

        Ok(())
    }

    pub(crate) fn install_all(&mut self, env: &Environment, force: bool) -> Result<()> {
        for &component_id in DEFAULT_COMPONENTS {
            self.install_component(env, component_id, None, force)?;
        }

        Ok(())
    }

    pub(crate) fn uninstall_component(
        &mut self,
        env: &Environment,
        id: &str,
        version: Version,
    ) -> Result<()> {
        env.emit(RzupEvent::Debug {
            message: format!("Uninstalling component {} (version: {:?})", id, version),
        });

        let component = Self::create_component(id)?;
        component.uninstall(env, &version)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use tempfile::TempDir;

    #[test]
    fn test_component_creation() {
        assert!(ComponentRegistry::create_component("rust").is_ok());
        assert!(ComponentRegistry::create_component("cargo-risczero").is_ok());
        assert!(ComponentRegistry::create_component("invalid").is_err());
    }

    #[test]
    fn test_installation_needs() {
        let tmp_dir = TempDir::new().unwrap();
        let env = Environment::with_root(tmp_dir.path()).unwrap();
        let registry = ComponentRegistry::new(&env).unwrap();

        let version = Version::new(1, 0, 0);

        // Should need installation when component doesn't exist
        assert!(registry.needs_installation("rust", &version, false));

        // Should need installation when force is true
        assert!(registry.needs_installation("rust", &version, true));
    }
}
