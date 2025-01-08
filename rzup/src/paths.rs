use crate::env::Environment;
use crate::error::Result;
use std::collections::HashSet;

use crate::distribution::Platform;
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
        // Check both formats
        Ok(Self::get_version_dir(env, component_id, version)?.exists()
            || Self::get_legacy_version_dir(env, component_id, version)?.exists())
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

    pub(crate) fn get_legacy_version_dir(
        env: &Environment,
        component_id: &str,
        version: &Version,
    ) -> Result<PathBuf> {
        let platform = Platform::detect();
        match component_id {
            "rust" => Ok(env.root_dir().join("toolchains").join(format!(
                "r0.{}-risc0-rust-{}",
                version,
                platform.target_triple()
            ))),
            "cargo-risczero" => Ok(env
                .root_dir()
                .join("extensions")
                .join(format!("v{}-cargo-risczero", version))),
            "r0vm" => Ok(env
                .root_dir()
                .join("extensions")
                .join(format!("v{}-cargo-risczero", version))),
            // For unknown components, use a consistent legacy format (mainly for testing)
            _ => Ok(env
                .root_dir()
                .join(component_id)
                .join(format!("v{}-{}", version, component_id))),
        }
    }

    pub fn list_component_versions(env: &Environment, component_id: &str) -> Result<Vec<Version>> {
        let mut versions = HashSet::new(); // Use HashSet to deduplicate
        let component_dir = Self::get_component_dir(env, component_id)?;

        env.emit(RzupEvent::Debug {
            message: format!("Scanning directory: {}", component_dir.display()),
        });

        if !component_dir.exists() {
            return Ok(Vec::new());
        }

        for entry in std::fs::read_dir(component_dir)? {
            let entry = entry?;
            if !entry.path().is_dir() {
                continue;
            }

            let file_name = entry.file_name();
            let name = file_name.to_string_lossy();

            env.emit(RzupEvent::Debug {
                message: format!("Found directory: {}", name),
            });

            let version_str = match component_id {
                "rust" => name
                    .strip_prefix("r0.")
                    .and_then(|s| s.split("-risc0-rust").next()),
                "cargo-risczero" => name
                    .strip_prefix('v')
                    .and_then(|s| s.split("-cargo-risczero").next()),
                _ => None,
            };

            if let Some(v_str) = version_str {
                if let Ok(v) = Version::parse(v_str) {
                    env.emit(RzupEvent::Debug {
                        message: format!("Adding version: {}", v),
                    });
                    versions.insert(v);
                }
            }
        }

        let mut versions: Vec<_> = versions.into_iter().collect();
        versions.sort();

        Ok(versions)
    }

    pub fn list_legacy_versions(env: &Environment, component_id: &str) -> Result<Vec<Version>> {
        let mut versions = HashSet::new();

        match component_id {
            "rust" => {
                let toolchain_dir = env.root_dir().join("toolchains");
                if toolchain_dir.exists() {
                    for entry in std::fs::read_dir(toolchain_dir)? {
                        let entry = entry?;
                        let name = entry.file_name().to_string_lossy().to_string();

                        if let Some(v_str) = name
                            .strip_prefix("r0.")
                            .and_then(|s| s.split("-risc0-rust").next())
                        {
                            if let Ok(v) = Version::parse(v_str) {
                                versions.insert(v);
                            }
                        }
                    }
                }
            }
            "cargo-risczero" => {
                let ext_dir = env.root_dir().join("extensions");
                if ext_dir.exists() {
                    for entry in std::fs::read_dir(ext_dir)? {
                        let entry = entry?;
                        let name = entry.file_name().to_string_lossy().to_string();

                        if let Some(v_str) = name
                            .strip_prefix('v')
                            .and_then(|s| s.split("-cargo-risczero").next())
                        {
                            if let Ok(v) = Version::parse(v_str) {
                                versions.insert(v);
                            }
                        }
                    }
                }
            }
            _ => {}
        }

        let mut versions: Vec<_> = versions.into_iter().collect();
        versions.sort();
        Ok(versions)
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
    fn test_component_paths() {
        let (_tmp_dir, env) = setup_test_env();
        let version = Version::new(1, 0, 0);
        let component_id = "test-component";

        // Test component directory path
        let component_dir = Paths::get_component_dir(&env, component_id).unwrap();
        assert_eq!(component_dir, env.root_dir().join(component_id));

        // Test version directory path
        let version_dir = Paths::get_version_dir(&env, component_id, &version).unwrap();
        assert_eq!(
            version_dir,
            env.root_dir().join(component_id).join(format!(
                "v{}-{}-{}",
                version,
                component_id,
                env.platform()
            ))
        );

        // Test bin directory path
        let bin_dir = Paths::get_bin_dir(&env, component_id, &version).unwrap();
        assert_eq!(
            bin_dir,
            env.root_dir()
                .join(component_id)
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
