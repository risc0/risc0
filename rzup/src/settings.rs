use crate::env::Environment;
use crate::error::Result;
use crate::events::RzupEvent;
use crate::RzupError;

use semver::Version;
use serde::{Deserialize, Serialize};
use std::collections::HashMap;
use std::fs;

#[derive(Debug, Serialize, Deserialize, Default, Clone)]
pub struct Settings {
    #[serde(default)]
    active_versions: HashMap<String, String>,
}

impl Settings {
    pub(crate) fn load(env: &Environment) -> Result<Self> {
        let settings_path = env.settings_path();
        if !settings_path.exists() {
            env.emit(RzupEvent::Debug {
                message: format!(
                    "No settings file found at {}, using defaults",
                    settings_path.display()
                ),
            });
            return Ok(Self::default());
        }

        env.emit(RzupEvent::Debug {
            message: format!("Loading settings from {}", settings_path.display()),
        });
        let contents = fs::read_to_string(settings_path)
            .map_err(|e| RzupError::Environment(format!("Failed to read settings file: {}", e)))?;

        toml::from_str(&contents)
            .map_err(|e| RzupError::Environment(format!("Failed to parse settings file: {}", e)))
    }

    pub(crate) fn save(&self, env: &Environment) -> Result<()> {
        if let Some(parent) = env.settings_path().parent() {
            fs::create_dir_all(parent).map_err(|e| {
                RzupError::Environment(format!("Failed to create settings directory: {}", e))
            })?;
        }

        env.emit(RzupEvent::Debug {
            message: format!("Saving settings to {}", env.settings_path().display()),
        });

        let contents = toml::to_string_pretty(self)
            .map_err(|e| RzupError::Environment(format!("Failed to serialize settings: {}", e)))?;

        fs::write(env.settings_path(), contents)
            .map_err(|e| RzupError::Environment(format!("Failed to write settings file: {}", e)))?;

        Ok(())
    }

    pub(crate) fn get_active_version(&self, component: &str) -> Option<Version> {
        self.active_versions
            .get(component)
            .and_then(|v| Version::parse(v).ok())
    }

    pub(crate) fn set_active_version(&mut self, component: &str, version: &Version) {
        self.active_versions
            .insert(component.to_string(), version.to_string());
        // if cargo-risczero, also set r0vm and vice-versa
        if component == "cargo-risczero" {
            self.active_versions
                .insert("r0vm".to_string(), version.to_string());
        } else if component == "r0vm" {
            self.active_versions
                .insert("cargo-risczero".to_string(), version.to_string());
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use tempfile::TempDir;

    #[test]
    fn test_settings_save_and_load() {
        let tmp_dir = TempDir::new().unwrap();
        let env = Environment::with_root(tmp_dir.path()).unwrap();
        let mut settings = Settings::default();

        // Add some test data
        let version = Version::new(1, 0, 0);
        settings.set_active_version("test-component", &version);

        // Save settings
        settings.save(&env).unwrap();

        // Load settings and verify
        let loaded = Settings::load(&env).unwrap();
        assert_eq!(loaded.get_active_version("test-component"), Some(version));
    }

    #[test]
    fn test_settings_defaults() {
        let settings = Settings::default();
        assert!(settings.active_versions.is_empty());
    }
}
