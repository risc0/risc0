use crate::error::Result;
use crate::RzupError;
use std::path::{Path, PathBuf};

#[derive(Debug, Clone)]
pub struct Environment {
    root_dir: PathBuf,
    tmp_dir: PathBuf,
    settings_file: PathBuf,
}

impl Environment {
    pub fn with_root<P: Into<PathBuf>>(root: P) -> Result<Self> {
        let root_dir = root.into();
        let tmp_dir = root_dir.join("tmp");
        let settings_file = root_dir.join("settings.toml");

        Ok(Self {
            root_dir,
            tmp_dir,
            settings_file,
        })
    }

    pub fn new() -> Result<Self> {
        let root_dir = if let Ok(dir) = std::env::var("RISC0_HOME") {
            PathBuf::from(dir)
        } else {
            dirs::home_dir()
                .ok_or_else(|| {
                    RzupError::Environment("Could not determine home directory".to_string())
                })?
                .join(".risc02")
        };

        Self::with_root(root_dir)
    }

    pub fn root_dir(&self) -> &Path {
        &self.root_dir
    }

    pub fn component_dir(&self, id: &str) -> Result<PathBuf> {
        Ok(self.root_dir.join(id))
    }

    pub fn settings_path(&self) -> &Path {
        &self.settings_file
    }

    pub fn tmp_dir(&self) -> &Path {
        &self.tmp_dir
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::env;

    #[test]
    fn test_default_env() {
        let env = Environment::new().unwrap();
        let home_dir = dirs::home_dir().unwrap();
        let expected_root = home_dir.join(".risc02");

        assert_eq!(env.root_dir, expected_root);
        assert_eq!(env.tmp_dir, expected_root.join("tmp"));
        assert_eq!(env.settings_file, expected_root.join("settings.toml"));
    }

    #[test]
    fn test_custom_root() {
        let tmp_dir = tempfile::tempdir().unwrap();
        let tmp_path = tmp_dir.path().to_path_buf();

        let env = Environment::with_root(&tmp_path).unwrap();

        assert_eq!(env.root_dir, tmp_path);
        assert_eq!(env.tmp_dir, tmp_path.join("tmp"));
        assert_eq!(env.settings_file, tmp_path.join("settings.toml"));
    }

    #[test]
    fn test_environment_with_risc0_home() {
        let tmp_dir = tempfile::tempdir().unwrap();
        let r0_tmp_dir = tmp_dir.path().join("risc0");
        env::set_var("RISC0_HOME", &r0_tmp_dir);

        let env = Environment::new().unwrap();
        assert_eq!(env.root_dir, r0_tmp_dir);

        env::remove_var("RISC0_HOME");
    }
}
