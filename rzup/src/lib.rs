#[cfg(feature = "cli")]
pub mod cli;
mod components;
mod distribution;
mod env;

mod events;
mod paths;
mod registry;
mod settings;

pub mod error;

use env::Environment;
use events::RzupEvent;
use paths::Paths;
use registry::Registry;
use semver::Version;
use settings::Settings;
use std::collections::HashMap;
use std::path::PathBuf;

pub use error::{Result, RzupError};

/// Rzup manages the RISC Zero toolchain components by handling installation, uninstallation,
/// and version management of various tools like the Rust toolchain and cargo extensions.
pub struct Rzup {
    environment: Environment,
    registry: Registry,
}

impl Rzup {
    /// Creates a new Rzup instance using default environment paths.
    ///
    /// This will initialize the registry, settings, and scan the environment for installed components.
    pub fn new() -> Result<Self> {
        let environment = Environment::new()?;
        let mut registry = Registry::new(&environment)?;
        Self::initialize_settings(&environment, &mut registry)?;
        registry.scan_environment(&environment)?;

        Ok(Self {
            environment,
            registry,
        })
    }

    /// Creates a new Rzup instance with a custom root directory.
    ///
    /// # Arguments
    /// * `root` - The root directory path for storing components and settings
    pub fn with_root<P: Into<PathBuf>>(root: P) -> Result<Self> {
        let environment = Environment::with_root(root)?;
        let mut registry = Registry::new(&environment)?;
        Self::initialize_settings(&environment, &mut registry)?;
        registry.scan_environment(&environment)?;

        Ok(Self {
            environment,
            registry,
        })
    }

    fn initialize_settings(environment: &Environment, registry: &mut Registry) -> Result<()> {
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

    /// Sets an event handler for receiving notifications about operations.
    ///
    /// # Arguments
    /// * `handler` - Function that will be called for each event
    pub fn set_event_handler<F>(&mut self, handler: F)
    where
        F: Fn(RzupEvent) + Send + Sync + 'static,
    {
        self.environment.set_event_handler(handler);
    }

    /// Installs all default components.
    ///
    /// # Arguments
    /// * `force` - If true, reinstalls even if already installed
    pub fn install_all(&mut self, force: bool) -> Result<()> {
        self.registry
            .install_all_components(&self.environment, force)?;
        self.registry.scan_environment(&self.environment)?;
        Ok(())
    }

    /// Installs a specific component version.
    ///
    /// # Arguments
    /// * `component` - Component identifier (e.g. "rust", "cargo-risczero")
    /// * `version` - Specific version to install, or None for latest
    /// * `force` - If true, reinstalls even if already installed
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

    /// Uninstalls a specific component version.
    ///
    /// # Arguments
    /// * `component` - Component identifier
    /// * `version` - Version to uninstall
    pub fn uninstall_component(&mut self, component: &str, version: Version) -> Result<()> {
        self.registry
            .uninstall_component(&self.environment, component, version)?;
        self.registry.scan_environment(&self.environment)?;
        Ok(())
    }

    /// Lists all installed versions of a component.
    ///
    /// # Arguments
    /// * `id` - Component identifier
    pub fn list_versions(&self, id: &str) -> Result<Vec<Version>> {
        self.registry.list_component_versions(&self.environment, id)
    }

    /// Gets the currently active version of a component and its path.
    ///
    /// # Arguments
    /// * `id` - Component identifier
    pub fn get_active_version(&self, id: &str) -> Result<Option<(Version, std::path::PathBuf)>> {
        self.registry
            .get_active_component_version(&self.environment, id)
    }

    fn emit(&self, event: RzupEvent) {
        self.environment.emit(event)
    }

    /// Fetches the latest available version of a component.
    ///
    /// # Arguments
    /// * `id` - Component identifier
    pub fn get_latest_version(&self, id: &str) -> Result<Version> {
        let component = self.registry.create_component(id)?;
        component.get_latest_version(&self.environment)
    }

    /// Sets the active version for a component.
    ///
    /// # Arguments
    /// * `id` - Component identifier
    /// * `version` - Version to set as active
    pub fn set_active_version(&mut self, id: &str, version: Version) -> Result<()> {
        self.registry
            .set_active_component_version(&self.environment, id, version)
    }

    /// Checks if a specific version of a component exists.
    ///
    /// # Arguments
    /// * `id` - Component identifier
    /// * `version` - Version to check
    pub fn version_exists(&self, id: &str, version: &Version) -> Result<bool> {
        Paths::version_exists(&self.environment, id, version)
    }

    /// Gets the settings manager.
    pub fn settings(&self) -> &Settings {
        self.registry.settings()
    }

    pub fn latest_version(&self, component_id: &str) -> Result<Version> {
        let components = &self.registry.components;
        let component = components.get(component_id).unwrap();
        component.get_latest_version(&self.environment)
    }

    /// Gets the mapping of all installed versions and their paths for a component.
    ///
    /// # Arguments
    /// * `component_id` - Component identifier
    pub fn installed_versions(&self, component_id: &str) -> HashMap<Version, PathBuf> {
        let mut versions = HashMap::new();

        if let Ok(component_dir) = Paths::get_component_dir(&self.environment, component_id) {
            if let Ok(entries) = std::fs::read_dir(component_dir) {
                for entry in entries.filter_map(|e| e.ok()) {
                    let file_name = entry.file_name().to_string_lossy().to_string();
                    if let Some(version_str) = file_name
                        .strip_prefix('v')
                        .and_then(|s| s.strip_suffix(&format!("-{}", component_id)))
                    {
                        if let Ok(version) = Version::parse(version_str) {
                            versions.insert(version, entry.path());
                        }
                    }
                }
            }
        }

        versions
    }

    /// Checks if a specific version of a component is installed.
    ///
    /// # Arguments
    /// * `component_id` - Component identifier
    /// * `version` - Version to check
    pub fn is_installed(&self, component_id: &str, version: &Version) -> bool {
        Paths::version_exists(&self.environment, component_id, version).unwrap_or(false)
    }

    /// Gets the binary path for a component version.
    ///
    /// For virtual components, returns the path within the parent component.
    ///
    /// # Arguments
    /// * `component_id` - Component identifier
    /// * `version` - Version to get path for
    pub fn get_bin_path(&self, component_id: &str, version: &Version) -> Result<Option<PathBuf>> {
        let component = self.registry.create_component(component_id)?;

        if component.is_virtual() {
            // look at parent
            let parent_id = component.parent_component().ok_or_else(|| {
                RzupError::ComponentNotFound(format!(
                    "Virtual component {} has no parent",
                    component_id
                ))
            })?;

            if Paths::version_exists(&self.environment, parent_id, version)? {
                Ok(Some(Paths::get_bin_path(
                    &self.environment,
                    parent_id,
                    version,
                    component_id,
                )?))
            } else {
                Ok(None)
            }
        } else if Paths::version_exists(&self.environment, component_id, version)? {
            Ok(Some(Paths::get_bin_dir(
                &self.environment,
                component_id,
                version,
            )?))
        } else {
            Ok(None)
        }
    }

    /// Ensures version directories exist for a component.
    ///
    /// Creates the necessary directory structure if it doesn't exist.
    ///
    /// # Arguments
    /// * `component_id` - Component identifier
    /// * `version` - Version to create directories for
    pub fn ensure_version_dirs(&self, component_id: &str, version: &Version) -> Result<()> {
        Paths::create_version_dirs(&self.environment, component_id, version)
    }

    /// Gets the component directory path.
    ///
    /// # Arguments
    /// * `component_id` - Component identifier
    pub fn get_component_dir(&self, component_id: &str) -> Result<PathBuf> {
        Paths::get_component_dir(&self.environment, component_id)
    }

    /// Gets the version-specific directory path for a component.
    ///
    /// # Arguments
    /// * `component_id` - Component identifier
    /// * `version` - Version to get directory for
    pub fn get_version_dir(&self, component_id: &str, version: &Version) -> Result<PathBuf> {
        Paths::get_version_dir(&self.environment, component_id, version)
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

    #[test]
    fn test_path_operations() {
        let tmp_dir = TempDir::new().unwrap();
        let rzup = Rzup::with_root(tmp_dir.path()).unwrap();
        let version = Version::new(1, 0, 0);
        let component_id = "cargo-risczero";

        // Test directory creation
        rzup.ensure_version_dirs(component_id, &version).unwrap();
        assert!(rzup.is_installed(component_id, &version));

        // Test binary path retrieval
        let bin_path = rzup.get_bin_path(component_id, &version).unwrap();
        assert!(bin_path.is_some());
        assert!(bin_path
            .unwrap()
            .ends_with(format!("v{}-{}/bin", version, component_id)));

        // Test virtual component
        let virtual_component = "r0vm";
        let virtual_bin_path = rzup.get_bin_path(virtual_component, &version).unwrap();
        assert!(virtual_bin_path.is_some());
        assert!(virtual_bin_path
            .unwrap()
            .ends_with(format!("bin/{}", virtual_component)));
    }
}
