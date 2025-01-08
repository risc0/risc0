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
use crate::env::Environment;
use crate::error::Result;
use crate::events::RzupEvent;
use semver::Version;
use std::path::PathBuf;

pub struct Paths;

impl Paths {
    pub fn get_component_dir(env: &Environment, component_id: &str) -> Result<PathBuf> {
        match component_id {
            "rust" => Ok(env.root_dir().join("toolchains")),
            "cargo-risczero" | "r0vm" => Ok(env.root_dir().join("extensions")),
            _ => Ok(env.root_dir().join(component_id)), // Default for new components
        }
    }

    pub fn get_version_dir(
        env: &Environment,
        component_id: &str,
        version: &Version,
    ) -> Result<PathBuf> {
        let base_path = Self::get_component_dir(env, component_id)?;
        Ok(base_path.join(format!("v{}-{}-{}", version, component_id, env.platform())))
    }

    pub fn get_bin_dir(
        env: &Environment,
        component_id: &str,
        version: &Version,
    ) -> Result<PathBuf> {
        let version_dir = Self::get_version_dir(env, component_id, version)?;
        Ok(version_dir.join("bin"))
    }

    pub fn get_bin_path(
        env: &Environment,
        component_id: &str,
        version: &Version,
        bin: &str,
    ) -> Result<PathBuf> {
        let bin_dir = Self::get_bin_dir(env, component_id, version)?;
        Ok(bin_dir.join(bin))
    }

    pub fn version_exists(
        env: &Environment,
        component_id: &str,
        version: &Version,
    ) -> Result<bool> {
        let component_dir = Self::get_component_dir(env, component_id)?;
        if !component_dir.exists() {
            return Ok(false);
        }

        for entry in std::fs::read_dir(component_dir)? {
            let entry = entry?;
            if !entry.path().is_dir() {
                continue;
            }

            let dir_name = entry.file_name().to_string_lossy().to_string();
            if let Some(parsed_version) = Self::parse_version_from_path(&dir_name, component_id) {
                if parsed_version == *version {
                    return Ok(true);
                }
            }
        }

        Ok(false)
    }

    pub fn create_version_dirs(
        env: &Environment,
        component_id: &str,
        version: &Version,
    ) -> Result<()> {
        let component_dir = Self::get_component_dir(env, component_id)?;
        if !component_dir.exists() {
            env.emit(RzupEvent::Debug {
                message: format!("Creating component directory: {}", component_dir.display()),
            });
            std::fs::create_dir_all(&component_dir)?;
        }

        let version_dir = Self::get_version_dir(env, component_id, version)?;
        if !version_dir.exists() {
            env.emit(RzupEvent::Debug {
                message: format!("Creating version directory: {}", version_dir.display()),
            });
            std::fs::create_dir_all(&version_dir)?;
        }

        if component_id != "rust" {
            let bin_dir = version_dir.join("bin");
            if !bin_dir.exists() {
                env.emit(RzupEvent::Debug {
                    message: format!("Creating bin directory: {}", bin_dir.display()),
                });
                std::fs::create_dir_all(bin_dir)?;
            }
        }

        // Also ensure tmp directory exists
        let tmp_dir = env.tmp_dir();
        if !tmp_dir.exists() {
            env.emit(RzupEvent::Debug {
                message: format!("Creating tmp directory: {}", tmp_dir.display()),
            });
            std::fs::create_dir_all(tmp_dir)?;
        }

        Ok(())
    }

    pub fn cleanup_version(env: &Environment, component_id: &str, version: &Version) -> Result<()> {
        let version_dir = Self::get_version_dir(env, component_id, version)?;
        if version_dir.exists() {
            std::fs::remove_dir_all(&version_dir)?;
        }

        let component_dir = Self::get_component_dir(env, component_id)?;
        if component_dir.exists() && std::fs::read_dir(&component_dir)?.count() == 0 {
            std::fs::remove_dir(component_dir)?;
        }

        Ok(())
    }

    pub fn parse_version_from_path(dir_name: &str, component_id: &str) -> Option<Version> {
        fn extract_version(version_part: &str) -> Option<Version> {
            let segments: Vec<&str> = version_part.split('-').collect();
            match segments.len() {
                1 => Version::parse(version_part).ok(),
                2 | 3 => {
                    let version_with_pre = format!("{}-{}", segments[0], segments[1]);
                    Version::parse(&version_with_pre).ok()
                }
                _ => None,
            }
        }

        let result = if dir_name.starts_with("r0.") && component_id == "rust" {
            // Handle legacy rust format
            dir_name
                .strip_prefix("r0.")
                .and_then(|v| v.split('-').next())
                .and_then(|v| Version::parse(v).ok())
        } else if dir_name.starts_with('v') {
            if let Some(version_part) = dir_name.strip_prefix('v') {
                if version_part.contains(&format!("-{}-", component_id)) {
                    // New format with platform suffix
                    version_part
                        .split(&format!("-{}-", component_id))
                        .next()
                        .and_then(extract_version)
                } else if version_part.ends_with(component_id) {
                    // Legacy format without platform suffix
                    version_part
                        .split(&format!("-{}", component_id))
                        .next()
                        .and_then(extract_version)
                } else {
                    extract_version(version_part.split('-').next()?)
                }
            } else {
                None
            }
        } else {
            None
        };

        result
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use semver::Version;
    use tempfile::TempDir;

    fn setup_test_env() -> (TempDir, Environment) {
        let tmp_dir = TempDir::new().unwrap();
        let env = Environment::with_root(tmp_dir.path()).unwrap();
        (tmp_dir, env)
    }

    #[test]
    fn test_parse_legacy_rust_version() {
        let dir_name = "r0.1.81.0-risc0-rust-aarch64-apple-darwin";
        let version = Paths::parse_version_from_path(dir_name, "rust");
        assert_eq!(version, Version::parse("1.81.0").ok());
    }

    #[test]
    fn test_parse_legacy_cargo_risczero_version() {
        let dir_name = "v1.2.1-rc.0-cargo-risczero";
        let version = Paths::parse_version_from_path(dir_name, "cargo-risczero");
        assert_eq!(version, Version::parse("1.2.1-rc.0").ok());
    }

    #[test]
    fn test_parse_new_format_version() {
        let dir_name = "v1.2.0-cargo-risczero-aarch64-apple-darwin";
        let version = Paths::parse_version_from_path(dir_name, "cargo-risczero");
        assert_eq!(version, Version::parse("1.2.0").ok());
    }

    #[test]
    fn test_parse_new_rust_format_version() {
        let dir_name = "v1.79.0-rust-aarch64-apple-darwin";
        let version = Paths::parse_version_from_path(dir_name, "rust");
        assert_eq!(version, Version::parse("1.79.0").ok());
    }
    #[test]
    fn test_component_paths() {
        let (_tmp_dir, env) = setup_test_env();
        let version = Version::new(1, 0, 0);
        let component_id = "test-component";

        // Test component directory path
        let component_dir = Paths::get_component_dir(&env, component_id).unwrap();
        assert_eq!(component_dir, env.root_dir().join("test-component"));

        // Test version directory path
        let version_dir = Paths::get_version_dir(&env, component_id, &version).unwrap();
        assert_eq!(
            version_dir,
            env.root_dir()
                .join("test-component")
                .join(format!("v{}-{}-{}", version, component_id, env.platform()))
        );

        // Test bin directory path
        let bin_dir = Paths::get_bin_dir(&env, component_id, &version).unwrap();
        assert_eq!(
            bin_dir,
            env.root_dir()
                .join("test-component")
                .join(format!("v{}-{}-{}", version, component_id, env.platform()))
                .join("bin")
        );
    }

    #[test]
    fn test_directory_creation_and_cleanup() {
        let (_tmp_dir, env) = setup_test_env();
        let version = Version::new(1, 0, 0);
        let component_id = "test-component";

        // Test directory creation
        Paths::create_version_dirs(&env, component_id, &version).unwrap();
        assert!(Paths::version_exists(&env, component_id, &version).unwrap());

        // Test directory cleanup
        Paths::cleanup_version(&env, component_id, &version).unwrap();
        assert!(!Paths::version_exists(&env, component_id, &version).unwrap());
    }
}
