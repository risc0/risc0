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

#[derive(Debug, Serialize, Deserialize, Default, Clone, PartialEq)]
pub struct Settings {
    #[serde(default)]
    default_versions: HashMap<String, String>,
    #[serde(flatten)]
    unknown_settings: toml::Table,
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

        let settings: Self = toml::from_str(&contents)
            .map_err(|e| RzupError::Other(format!("invalid TOML in settings.toml file: {e}")))?;

        // Emit warning for any invalid semver versions in [default_versions]
        for (component, version_str) in &settings.default_versions {
            if Version::parse(version_str).is_err() {
                env.emit(RzupEvent::Print {
                    message: format!(
                        "! Warning: settings.toml: invalid semver `{version_str}` for component `{component}`",
                    ),
                });
            }
        }

        for table_name in settings.unknown_settings.keys() {
            env.emit(RzupEvent::Print {
                message: format!("! Warning: settings.toml: unknown table `{table_name}`"),
            })
        }
        Ok(settings)
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

    pub(crate) fn get_default_version(&self, component: &Component) -> Option<Version> {
        self.default_versions
            .get(component.as_str())
            .and_then(|v| Version::parse(v).ok())
    }

    pub(crate) fn set_default_version(&mut self, component: &Component, version: &Version) {
        self.default_versions
            .insert(component.to_string(), version.to_string());
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::distribution::{Os, Platform};
    use tempfile::TempDir;

    fn test_env() -> (TempDir, Environment) {
        let tmp_dir = TempDir::new().unwrap();
        let env = Environment::with_paths_creds_platform_and_event_handler(
            tmp_dir.path().join(".risc0"),
            tmp_dir.path().join(".rustup"),
            tmp_dir.path().join(".cargo"),
            None,
            || None,
            Platform::new("x86_64", Os::Linux),
            |_| {},
        )
        .unwrap();
        (tmp_dir, env)
    }

    #[test]
    fn test_settings_save_and_load() {
        let (_tmp_dir, env) = test_env();
        let mut settings = Settings::default();

        // Add some test data
        let version = Version::new(1, 0, 0);
        settings.set_default_version(&Component::CargoRiscZero, &version);

        // Save settings
        settings.save(&env).unwrap();

        // Load settings and verify
        let loaded = Settings::load(&env).unwrap();
        assert_eq!(
            loaded.get_default_version(&Component::CargoRiscZero),
            Some(version)
        );
    }

    #[test]
    fn test_settings_load_invalid() {
        let (_tmp_dir, env) = test_env();

        std::fs::write(env.settings_path(), "foobar").unwrap();
        let error_str = Settings::load(&env).unwrap_err().to_string();
        assert!(
            error_str.starts_with("invalid TOML in settings.toml file: TOML parse error at line 1"),
            "actual = {error_str}"
        );
    }

    fn run_and_assert_events<RetT>(
        env: &mut Environment,
        body: impl FnOnce(&mut Environment) -> RetT,
        expected_events: Vec<RzupEvent>,
    ) -> RetT {
        let (event_send, event_recv) = std::sync::mpsc::channel();
        env.set_event_handler(move |event| {
            event_send.send(event).unwrap();
        });

        let ret = body(env);
        env.set_event_handler(|_| {});

        let mut events = vec![];
        while let Ok(event) = event_recv.recv() {
            if !matches!(event, RzupEvent::Debug { .. }) {
                events.push(event);
            }
        }
        assert_eq!(events, expected_events);

        ret
    }

    /// A future version of `rzup` might have other sections, in that scenario we want to ignore
    /// them, but produce a warning.
    #[test]
    fn unknown_section() {
        let (_tmp_dir, mut env) = test_env();

        std::fs::write(env.settings_path(), "[other]\na = 12").unwrap();
        let settings: Settings = run_and_assert_events(
            &mut env,
            |env| Settings::load(env).unwrap(),
            vec![RzupEvent::Print {
                message: "! Warning: settings.toml: unknown table `other`".into(),
            }],
        );

        // The produced settings should be default
        for c in Component::iter() {
            assert_eq!(settings.get_default_version(&c), None);
        }
    }

    /// A future version of `rzup` might have components unknown to this version, in that scenario
    /// we want to make sure we ignore them.
    #[test]
    fn unknown_component_is_ignored() {
        let (_tmp_dir, env) = test_env();

        std::fs::write(
            env.settings_path(),
            "[default_versions]\n\
            rust = \"1.81.0\"\n\
            foobar = \"1.3.4\"\n",
        )
        .unwrap();
        let settings = Settings::load(&env).unwrap();
        let version = settings
            .get_default_version(&Component::RustToolchain)
            .unwrap();
        assert_eq!(version, Version::new(1, 81, 0));
    }

    /// If the version string in default_versions is not a valid semver,
    /// it should be ignored without panicking.
    #[test]
    fn test_invalid_version_is_ignored() {
        let (_tmp_dir, mut env) = test_env();

        std::fs::write(
            env.settings_path(),
            "[default_versions]\ncargo-risczero = \"not-a-semver\"\n",
        )
        .unwrap();

        let settings: Settings = run_and_assert_events(
            &mut env,
            |env| Settings::load(env).unwrap(),
            vec![RzupEvent::Print {
                message: "! Warning: settings.toml: invalid semver `not-a-semver` for component `cargo-risczero`".into(),
            }],
        );

        assert_eq!(
            settings.get_default_version(&Component::CargoRiscZero),
            None
        );
    }

    #[test]
    fn test_settings_defaults() {
        let settings = Settings::default();
        assert!(settings.default_versions.is_empty());
    }
}
