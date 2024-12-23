use crate::env::Environment;
use crate::error::Result;
use crate::events::RzupEvent;
use crate::RzupError;
use semver::Version;
use serde::{Deserialize, Serialize};
use std::collections::HashMap;
use std::fs;

#[derive(Debug, Serialize, Deserialize, Default)]
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
    }
}
