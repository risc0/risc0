use crate::env::Environment;
use crate::error::Result;

use semver::Version;
use std::path::PathBuf;

pub struct Paths;

impl Paths {
    pub fn get_component_dir(env: &Environment, component_id: &str) -> Result<PathBuf> {
        Ok(env.root_dir().join(component_id))
    }

    pub fn get_version_dir(
        env: &Environment,
        component_id: &str,
        version: &Version,
    ) -> Result<PathBuf> {
        let base_path = Self::get_component_dir(env, component_id)?;
        Ok(base_path.join(format!("v{}-{}", version, component_id)))
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
        let version_dir = Self::get_version_dir(env, component_id, version)?;
        Ok(version_dir.exists())
    }

    pub fn create_version_dirs(
        env: &Environment,
        component_id: &str,
        version: &Version,
    ) -> Result<()> {
        let version_dir = Self::get_version_dir(env, component_id, version)?;
        if !version_dir.exists() {
            std::fs::create_dir_all(&version_dir)?;
        }

        if component_id != "rust" {
            let bin_dir = version_dir.join("bin");
            if !bin_dir.exists() {
                std::fs::create_dir_all(bin_dir)?;
            }
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
            env.root_dir()
                .join(component_id)
                .join(format!("v{}-{}", version, component_id))
        );

        // Test bin directory path
        let bin_dir = Paths::get_bin_dir(&env, component_id, &version).unwrap();
        assert_eq!(
            bin_dir,
            env.root_dir()
                .join(component_id)
                .join(format!("v{}-{}", version, component_id))
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
