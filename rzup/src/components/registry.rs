use crate::components::implementations::{CargoRiscZero, RustToolchain};
use crate::components::Component;
use crate::env::Environment;
use crate::error::Result;
use crate::settings::Settings;
use crate::RzupError;
use semver::Version;
use std::collections::HashMap;
use std::path::PathBuf;

static DEFAULT_COMPONENTS: &[&str] = &["rust", "cargo-risczero"];

#[derive(Debug, Default, Clone)]
pub(crate) struct ComponentVersions {
    versions: HashMap<Version, PathBuf>,
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
    components: HashMap<&'static str, Box<dyn Component>>,
    versions: HashMap<&'static str, ComponentVersions>,
    settings: Settings,
}

impl ComponentRegistry {
    pub(crate) fn new(env: &Environment) -> Result<Self> {
        let settings = Settings::load(env.settings_path())?;
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
        env: &Environment,
        component: Box<dyn Component>,
        versions: ComponentVersions,
    ) -> Result<()> {
        let component_id = component.id();

        if versions.versions.is_empty() {
            return Ok(());
        }

        self.register(component);
        self.versions.insert(component_id, versions.clone());

        // For fresh installations
        if !env.settings_path().exists() && self.settings.get_active_version(component_id).is_none()
        {
            if let Some(latest) = versions.list_versions().into_iter().max() {
                self.settings.set_active_version(component_id, latest);
            }
        }

        Ok(())
    }

    pub(crate) fn scan_environment(&mut self, env: &Environment) -> Result<()> {
        self.components.clear();
        self.versions.clear();

        let components: Vec<Box<dyn Component>> =
            vec![Box::new(RustToolchain), Box::new(CargoRiscZero)];

        let settings_missing = !env.settings_path().exists();
        let mut has_installed_components = false;

        for component in components {
            let component_id = component.id();
            let versions = self.scan_component_versions(env, component_id)?;
            if !versions.versions.is_empty() {
                has_installed_components = true;
            }
            self.register_component_versions(env, component, versions)?;
        }

        // save settings after all components are processed
        if settings_missing {
            self.settings.save(env.settings_path())?;
            if has_installed_components {
                println!("\n! Missing settings.toml\n  Created settings.toml with latest versions selected.\n");
            }
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
            self.settings.set_active_version(id, &version);
            self.settings.save(env.settings_path())?;
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

    fn parse_version(version: Option<String>) -> Result<Version> {
        let version_str = version.unwrap_or_else(|| "0.0.0".to_string());
        Version::parse(&version_str).map_err(|_| RzupError::InvalidVersion(version_str))
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
        version: Option<String>,
        force: bool,
    ) -> Result<()> {
        let component = Self::create_component(id)?;

        let parsed_version = Self::parse_version(version.clone())?;

        if !self.needs_installation(id, &parsed_version.clone(), force) {
            println!(
                "{} version {} is already installed",
                id,
                version.unwrap_or("latest".to_string())
            );
            return Ok(());
        }

        if !env.root_dir().exists() {
            std::fs::create_dir_all(env.root_dir())?;
        }

        component.install(env, version, force)?;

        self.settings.set_active_version(id, &parsed_version);
        self.settings.save(env.settings_path())?;
        self.scan_environment(env)?;

        Ok(())
    }

    pub(crate) fn install_all(
        &mut self,
        env: &Environment,
        version: Option<String>,
        force: bool,
    ) -> Result<()> {
        for &component in DEFAULT_COMPONENTS {
            self.install_component(env, component, version.clone(), force)?;
        }

        Ok(())
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
    fn test_version_parsing() {
        assert!(ComponentRegistry::parse_version(Some("1.0.0".to_string())).is_ok());
        assert!(ComponentRegistry::parse_version(None).is_ok());
        assert!(ComponentRegistry::parse_version(Some("invalid".to_string())).is_err());
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

    #[test]
    fn test_version_parsing_errors() {
        let invalid_versions = ["1.", "1.0.", "a.b.c", "-1.0.0"];
        for invalid in invalid_versions {
            assert!(matches!(
                ComponentRegistry::parse_version(Some(invalid.to_string())),
                Err(RzupError::InvalidVersion(_))
            ));
        }
    }

    #[test]
    fn test_component_installation() {
        let tmp_dir = TempDir::new().unwrap();
        let env = Environment::with_root(tmp_dir.path()).unwrap();
        let mut registry = ComponentRegistry::new(&env).unwrap();

        // Test installing valid component
        assert!(registry
            .install_component(&env, "rust", Some("1.0.0".to_string()), false)
            .is_ok());

        // Test installing invalid component
        assert!(matches!(
            registry.install_component(&env, "invalid", None, false),
            Err(RzupError::ComponentNotFound(_))
        ));
    }
}
