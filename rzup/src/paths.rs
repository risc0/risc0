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
use crate::distribution::parse_cpp_version;
use crate::env::Environment;
use crate::error::Result;
use semver::Version;
use std::path::PathBuf;

pub struct Paths;

impl Paths {
    pub fn get_component_dir(env: &Environment, component: &Component) -> PathBuf {
        match component {
            Component::RustToolchain | Component::CppToolchain => env.root_dir().join("toolchains"),
            Component::CargoRiscZero | Component::R0Vm => env.root_dir().join("extensions"),
        }
    }

    pub fn get_version_dir(env: &Environment, component: &Component, version: &Version) -> PathBuf {
        let base_path = Self::get_component_dir(env, component);
        base_path.join(format!("v{version}-{component}-{}", env.platform()))
    }

    pub fn get_bin_dir(env: &Environment, component: &Component, version: &Version) -> PathBuf {
        let version_dir = Self::get_version_dir(env, component, version);
        version_dir.join("bin")
    }

    pub fn get_bin_path(
        env: &Environment,
        component: &Component,
        version: &Version,
        bin: &str,
    ) -> PathBuf {
        let bin_dir = Self::get_bin_dir(env, component, version);
        bin_dir.join(bin)
    }

    pub fn version_exists(
        env: &Environment,
        component: &Component,
        version: &Version,
    ) -> Result<bool> {
        let component_dir = Self::get_component_dir(env, component);
        if !component_dir.exists() {
            return Ok(false);
        }

        for entry in std::fs::read_dir(component_dir)? {
            let entry = entry?;
            if !entry.path().is_dir() {
                continue;
            }

            let dir_name = entry.file_name().to_string_lossy().to_string();
            if let Some(parsed_version) = Self::parse_version_from_path(&dir_name, component) {
                if parsed_version == *version {
                    return Ok(true);
                }
            }
        }

        Ok(false)
    }

    pub fn cleanup_version(
        env: &Environment,
        component: &Component,
        version: &Version,
    ) -> Result<()> {
        let version_dir = Self::get_version_dir(env, component, version);
        if version_dir.exists() {
            std::fs::remove_dir_all(&version_dir)?;
        }

        let component_dir = Self::get_component_dir(env, component);
        if component_dir.exists() && std::fs::read_dir(&component_dir)?.count() == 0 {
            std::fs::remove_dir(component_dir)?;
        }

        Ok(())
    }

    pub fn parse_version_from_path(dir_name: &str, component: &Component) -> Option<Version> {
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

        let result = if dir_name.starts_with("r0.") && component == &Component::RustToolchain {
            // Handle legacy rust format
            dir_name
                .strip_prefix("r0.")
                .and_then(|v| v.split('-').next())
                .and_then(|v| Version::parse(v).ok())
        } else if component == &Component::CppToolchain && !dir_name.starts_with('v') {
            // Handle legacy cpp format (YYYY.MM.DD-risc0-cpp-...)
            let v = dir_name.split('-').next()?;
            parse_cpp_version(&v).ok()
        } else if dir_name.starts_with('v') {
            let version_part = dir_name.strip_prefix('v')?;
            if version_part.contains(&format!("-{component}-")) {
                // New format with platform suffix
                version_part
                    .split(&format!("-{component}-"))
                    .next()
                    .and_then(extract_version)
            } else if version_part.ends_with(component.as_str()) {
                // Legacy format without platform suffix
                version_part
                    .split(&format!("-{component}"))
                    .next()
                    .and_then(extract_version)
            } else {
                extract_version(version_part.split('-').next()?)
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
        let version = Paths::parse_version_from_path(dir_name, &Component::RustToolchain);
        assert_eq!(version, Version::parse("1.81.0").ok());
    }

    #[test]
    fn test_parse_legacy_cargo_risczero_version() {
        let dir_name = "v1.2.1-rc.0-cargo-risczero";
        let version = Paths::parse_version_from_path(dir_name, &Component::CargoRiscZero);
        assert_eq!(version, Version::parse("1.2.1-rc.0").ok());
    }

    #[test]
    fn test_parse_new_format_version() {
        let dir_name = "v1.2.0-cargo-risczero-aarch64-apple-darwin";
        let version = Paths::parse_version_from_path(dir_name, &Component::CargoRiscZero);
        assert_eq!(version, Version::parse("1.2.0").ok());
    }

    #[test]
    fn test_parse_new_rust_format_version() {
        let dir_name = "v1.79.0-rust-aarch64-apple-darwin";
        let version = Paths::parse_version_from_path(dir_name, &Component::RustToolchain);
        assert_eq!(version, Version::parse("1.79.0").ok());
    }

    #[test]
    fn test_directory_creation_and_cleanup() {
        let (_tmp_dir, env) = setup_test_env();
        let version = Version::new(1, 0, 0);
        let component = Component::RustToolchain;

        let version_dir = Paths::get_version_dir(&env, &component, &version);
        std::fs::create_dir_all(&version_dir).unwrap();
        assert!(Paths::version_exists(&env, &component, &version).unwrap());

        // Test directory cleanup
        Paths::cleanup_version(&env, &component, &version).unwrap();
        assert!(!Paths::version_exists(&env, &component, &version).unwrap());
    }
}
