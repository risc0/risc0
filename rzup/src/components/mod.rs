mod implementations;
pub(crate) mod registry;

use crate::env::Environment;
use crate::error::Result;
use semver::Version;
use std::fs;
use std::path::PathBuf;

pub trait Component: std::fmt::Debug {
    fn id(&self) -> &'static str;

    fn install(&self, env: &Environment, version: Option<String>, force: bool) -> Result<()>;

    fn get_path(&self, env: &Environment) -> Result<PathBuf> {
        env.component_dir(self.id())
    }

    fn _uninstall(&self, env: &Environment) -> Result<()> {
        let install_path = self.get_path(env)?;
        if install_path.exists() {
            fs::remove_dir_all(install_path)?;
        }
        Ok(())
    }

    fn create_version_dir(&self, env: &Environment, version: &str) -> Result<PathBuf> {
        let component_dir = self.get_path(env)?;
        let parsed_version = Version::parse(version)
            .map_err(|_| crate::RzupError::InvalidVersion(version.to_string()))?;
        let version_dir = component_dir.join(format!("v{}-{}", parsed_version, self.id()));
        fs::create_dir_all(&version_dir)?;
        fs::create_dir_all(version_dir.join("bin"))?;
        Ok(version_dir)
    }
}
