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
use crate::components::Component;
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
            .map_err(|e| RzupError::Environment(format!("Failed to read settings file: {e}")))?;

        Ok(toml::from_str(&contents).expect("Failed to parse settings file"))
    }

    pub(crate) fn save(&self, env: &Environment) -> Result<()> {
        if let Some(parent) = env.settings_path().parent() {
            fs::create_dir_all(parent).map_err(|e| {
                RzupError::Environment(format!("Failed to create settings directory: {e}"))
            })?;
        }

        env.emit(RzupEvent::Debug {
            message: format!("Saving settings to {}", env.settings_path().display()),
        });

        let contents = toml::to_string_pretty(self).expect("Failed to serialize settings");

        fs::write(env.settings_path(), contents)
            .map_err(|e| RzupError::Environment(format!("Failed to write settings file: {e}")))?;

        Ok(())
    }

    pub(crate) fn get_active_version(&self, component: &Component) -> Option<Version> {
        self.active_versions
            .get(component.as_str())
            .and_then(|v| Version::parse(v).ok())
    }

    pub(crate) fn set_active_version(&mut self, component: &Component, version: &Version) {
        self.active_versions
            .insert(component.to_string(), version.to_string());
        // if cargo-risczero, also set r0vm and vice-versa
        if component == &Component::CargoRiscZero {
            self.active_versions
                .insert(Component::R0Vm.to_string(), version.to_string());
        } else if component == &Component::R0Vm {
            self.active_versions
                .insert(Component::CargoRiscZero.to_string(), version.to_string());
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
        let env = Environment::with_paths(
            tmp_dir.path().join(".risc0"),
            tmp_dir.path().join(".cargo/bin"),
        )
        .unwrap();
        let mut settings = Settings::default();

        // Add some test data
        let version = Version::new(1, 0, 0);
        settings.set_active_version(&Component::CargoRiscZero, &version);

        // Save settings
        settings.save(&env).unwrap();

        // Load settings and verify
        let loaded = Settings::load(&env).unwrap();
        assert_eq!(
            loaded.get_active_version(&Component::CargoRiscZero),
            Some(version)
        );
    }

    #[test]
    fn test_settings_defaults() {
        let settings = Settings::default();
        assert!(settings.active_versions.is_empty());
    }
}
