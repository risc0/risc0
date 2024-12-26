#[cfg(feature = "cli")]
pub mod cli;
mod components;
mod distribution;
mod env;

mod events;
mod settings;

pub mod error;
use crate::components::registry::ComponentRegistry;
use crate::env::Environment;
use crate::settings::Settings;
use events::RzupEvent;
use semver::Version;
use std::collections::HashMap;
use std::path::PathBuf;

pub use error::{Result, RzupError};

pub struct Rzup {
    environment: Environment,
    registry: ComponentRegistry,
}

impl Rzup {
    pub fn new() -> Result<Self> {
        let environment = Environment::new()?;
        let mut registry = ComponentRegistry::new(&environment)?;
        Self::initialize_settings(&environment, &mut registry)?;
        registry.scan_environment(&environment)?;

        Ok(Self {
            environment,
            registry,
        })
    }

    pub fn with_root<P: Into<PathBuf>>(root: P) -> Result<Self> {
        let environment = Environment::with_root(root)?;
        let mut registry = ComponentRegistry::new(&environment)?;
        Self::initialize_settings(&environment, &mut registry)?;
        registry.scan_environment(&environment)?;

        Ok(Self {
            environment,
            registry,
        })
    }

    fn initialize_settings(
        environment: &Environment,
        registry: &mut ComponentRegistry,
    ) -> Result<()> {
        if !environment.settings_path().exists() {
            environment.emit(RzupEvent::Debug {
                message: format!(
                    "Creating new settings file at {}",
                    environment.settings_path().display()
                ),
            });
        }
        registry.settings().save(environment)?;
        Ok(())
    }

    pub fn set_event_handler<F>(&mut self, handler: F)
    where
        F: Fn(RzupEvent) + Send + Sync + 'static,
    {
        self.environment.set_event_handler(handler);
    }

    pub fn install_all(&mut self, force: bool) -> Result<()> {
        self.registry.install_all(&self.environment, force)?;
        self.registry.scan_environment(&self.environment)?;
        Ok(())
    }

    pub fn install_component(
        &mut self,
        component: &str,
        version: Option<Version>,
        force: bool,
    ) -> Result<()> {
        self.registry
            .install_component(&self.environment, component, version, force)?;
        self.registry.scan_environment(&self.environment)?;
        Ok(())
    }

    pub fn uninstall_component(&mut self, component: &str, version: Version) -> Result<()> {
        self.registry
            .uninstall_component(&self.environment, component, version)?;
        self.registry.scan_environment(&self.environment)?;
        Ok(())
    }

    pub fn environment(&self) -> &Environment {
        &self.environment
    }

    pub fn settings(&self) -> &Settings {
        self.registry.settings()
    }

    pub fn latest_version(&self, component_id: &str) -> Result<Version> {
        let components = &self.registry.components;
        let component = components.get(component_id).unwrap();
        component.get_latest_version(self.environment())
    }

    pub fn installed_versions(&self, component_id: &str) -> HashMap<Version, PathBuf> {
        self.registry
            .get_component_versions(component_id)
            .map_or_else(HashMap::new, |versions| versions.versions.clone())
    }

    pub fn is_installed(&self, component_id: &str, version: &Version) -> bool {
        self.installed_versions(component_id).contains_key(version)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use tempfile::TempDir;

    fn setup_test_env() -> (TempDir, Rzup) {
        let tmp_dir = TempDir::new().unwrap();
        let rzup = Rzup::with_root(tmp_dir.path()).unwrap();
        (tmp_dir, rzup)
    }

    #[test]
    fn test_rzup_initialization() {
        let (_tmp_dir, rzup) = setup_test_env();
        assert!(rzup.settings().get_active_version("rust").is_none());
        assert!(rzup
            .settings()
            .get_active_version("cargo-risczero")
            .is_none());
    }

    #[test]
    fn test_install_and_uninstall_component() {
        let (_tmp_dir, mut rzup) = setup_test_env();
        let version = Version::new(1, 0, 0);

        // Test installation
        rzup.install_component("cargo-risczero", Some(version.clone()), false)
            .unwrap();
        assert!(rzup.is_installed("cargo-risczero", &version));
        assert_eq!(
            rzup.settings()
                .get_active_version("cargo-risczero")
                .unwrap(),
            version
        );

        // Test uninstallation
        rzup.uninstall_component("cargo-risczero", version.clone())
            .unwrap();
        assert!(!rzup.is_installed("cargo-risczero", &version));
    }

    #[test]
    fn test_install_all() {
        let (_tmp_dir, mut rzup) = setup_test_env();
        rzup.install_all(false).unwrap();

        // Both default components should be installed
        assert!(!rzup.installed_versions("rust").is_empty());
        assert!(!rzup.installed_versions("cargo-risczero").is_empty());
    }
}
