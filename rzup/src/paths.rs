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
use crate::components::{component_asset_name, Component};
use crate::distribution::parse_cpp_version;
use crate::env::Environment;
use crate::error::Result;
use semver::Version;
use std::path::PathBuf;

pub struct Paths;

impl Paths {
    pub fn get_component_dir(env: &Environment, component: &Component) -> PathBuf {
        match component {
            Component::RustToolchain | Component::CppToolchain => {
                env.risc0_dir().join("toolchains")
            }
            Component::CargoRiscZero | Component::R0Vm => env.risc0_dir().join("extensions"),
        }
    }

    pub fn get_version_dir(env: &Environment, component: &Component, version: &Version) -> PathBuf {
        let base_path = Self::get_component_dir(env, component);
        base_path.join(format!("v{version}-{component}-{}", env.platform()))
    }

    pub fn find_version_dir(
        env: &Environment,
        component: &Component,
        version: &Version,
    ) -> Result<Option<PathBuf>> {
        let component_dir = Self::get_component_dir(env, component);
        if !component_dir.exists() {
            return Ok(None);
        }

        for entry in std::fs::read_dir(component_dir)? {
            let entry = entry?;
            if !entry.path().is_dir() {
                continue;
            }

            let dir_name = entry.file_name().to_string_lossy().to_string();
            if let Some(parsed_version) = Self::parse_version_from_path(&dir_name, component) {
                if parsed_version == *version {
                    // The C++ archive has a child directory we want to ignore, but legacy installs
                    // don't have it
                    if component == &Component::CppToolchain {
                        let (asset_name, _) = component_asset_name(component, env.platform())?;
                        let sub_dir = entry.path().join(asset_name);
                        if sub_dir.exists() {
                            return Ok(Some(sub_dir));
                        }
                    }

                    return Ok(Some(entry.path()));
                }
            }
        }

        Ok(None)
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

        if dir_name.starts_with("r0.") && component == &Component::RustToolchain {
            // Handle legacy rust format
            Version::parse(dir_name.strip_prefix("r0.")?.split('-').next()?).ok()
        } else if component == &Component::CppToolchain && !dir_name.starts_with('v') {
            // Handle legacy cpp format (YYYY.MM.DD-risc0-cpp-...)
            parse_cpp_version(dir_name.split('-').next()?).ok()
        } else if dir_name.starts_with('v') {
            let version_part = dir_name.strip_prefix('v')?;
            if let Some(p) = version_part.find(&format!("-{component}")) {
                // New format with platform suffix
                extract_version(&version_part[..p])
            } else {
                let p = version_part.find('-')?;
                extract_version(&version_part[..p])
            }
        } else {
            None
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::distribution::{Os, Platform};
    use semver::Version;
    use tempfile::TempDir;

    fn setup_test_env() -> (TempDir, Environment) {
        let tmp_dir = TempDir::new().unwrap();
        let env = Environment::with_paths_token_platform_and_event_handler(
            tmp_dir.path().join(".risc0"),
            tmp_dir.path().join(".rustup"),
            tmp_dir.path().join(".cargo"),
            None,
            Platform::new("x86_64", Os::Linux),
            |_| {},
        )
        .unwrap();
        (tmp_dir, env)
    }

    fn test_version_dir_parse_and_find(
        component: Component,
        dir_name: &str,
        expected_version: Version,
    ) {
        let (_tmp_dir, env) = setup_test_env();

        let version = Paths::parse_version_from_path(dir_name, &component).unwrap();
        assert_eq!(&version, &expected_version);

        let expected_path = Paths::get_component_dir(&env, &component).join(dir_name);
        std::fs::create_dir_all(&expected_path).unwrap();

        let actual_path = Paths::find_version_dir(&env, &component, &version)
            .unwrap()
            .unwrap();
        assert_eq!(actual_path, expected_path);
    }

    #[test]
    fn test_get_and_parse_legacy_rust_version() {
        test_version_dir_parse_and_find(
            Component::RustToolchain,
            "r0.1.81.0-risc0-rust-aarch64-apple-darwin",
            Version::new(1, 81, 0),
        );
    }

    #[test]
    fn test_get_and_parse_legacy_cargo_risczero_version() {
        test_version_dir_parse_and_find(
            Component::CargoRiscZero,
            "v1.2.1-rc.0-cargo-risczero",
            Version::parse("1.2.1-rc.0").unwrap(),
        );
    }

    #[test]
    fn test_get_and_parse_new_format_version() {
        test_version_dir_parse_and_find(
            Component::CargoRiscZero,
            "v1.2.0-cargo-risczero-aarch64-apple-darwin",
            Version::new(1, 2, 0),
        );
    }

    #[test]
    fn test_get_and_parse_new_rust_format_version() {
        test_version_dir_parse_and_find(
            Component::RustToolchain,
            "v1.79.0-rust-aarch64-apple-darwin",
            Version::new(1, 79, 0),
        );
    }

    #[test]
    fn test_directory_creation_and_cleanup() {
        let (_tmp_dir, env) = setup_test_env();
        let version = Version::new(1, 0, 0);
        let component = Component::RustToolchain;

        let version_dir = Paths::get_version_dir(&env, &component, &version);
        std::fs::create_dir_all(&version_dir).unwrap();
        assert!(Paths::find_version_dir(&env, &component, &version)
            .unwrap()
            .is_some());

        // Test directory cleanup
        Paths::cleanup_version(&env, &component, &version).unwrap();
        assert!(Paths::find_version_dir(&env, &component, &version)
            .unwrap()
            .is_none());
    }
}
