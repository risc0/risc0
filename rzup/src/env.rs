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
use crate::error::Result;
use crate::RzupError;
use crate::RzupEvent;
use std::fs;

use crate::distribution::Platform;
use std::path::{Path, PathBuf};

type VarResult<T> = std::result::Result<T, std::env::VarError>;

pub struct Environment {
    risc0_dir: PathBuf,
    tmp_dir: PathBuf,
    cargo_bin_dir: PathBuf,
    rustup_toolchain_dir: PathBuf,
    settings_file: PathBuf,
    event_handler: Option<Box<dyn Fn(RzupEvent) + Send + Sync>>,
    platform: Platform,
}

impl Environment {
    fn ensure_directories(&self) -> Result<()> {
        if !self.risc0_dir.exists() {
            fs::create_dir_all(&self.risc0_dir)?;
        }

        // This sentinel file is used by older version of the `risc0-build` crate, and without it
        // it will error.
        let rzup_sentinel = self.risc0_dir.join(".rzup");
        if !rzup_sentinel.exists() {
            std::fs::write(rzup_sentinel, "")?;
        }

        if !self.tmp_dir.exists() {
            fs::create_dir_all(&self.tmp_dir)?;
        }

        Ok(())
    }

    pub fn with_paths(risc0_dir: impl Into<PathBuf>, home_dir: impl AsRef<Path>) -> Result<Self> {
        let risc0_dir = risc0_dir.into();
        let tmp_dir = risc0_dir.join("tmp");
        let cargo_bin_dir = home_dir.as_ref().join(".cargo/bin");
        let rustup_toolchain_dir = home_dir.as_ref().join(".rustup/toolchains");
        let settings_file = risc0_dir.join("settings.toml");
        let platform = Platform::detect()?;

        let env = Self {
            risc0_dir,
            tmp_dir,
            cargo_bin_dir,
            rustup_toolchain_dir,
            settings_file,
            event_handler: None,
            platform,
        };

        env.ensure_directories()?;
        Ok(env)
    }

    pub fn new(mut env_accessor: impl FnMut(&str) -> VarResult<String>) -> Result<Self> {
        let home_dir = dirs::home_dir().ok_or_else(|| {
            RzupError::Environment("Could not determine home directory".to_string())
        })?;

        let risc0_dir = if let Ok(dir) = env_accessor("RISC0_HOME") {
            PathBuf::from(dir)
        } else {
            home_dir.join(".risc0")
        };

        let env = Self::with_paths(risc0_dir, home_dir)?;
        env.emit(RzupEvent::Debug {
            message: format!("Initialized environment at {}", env.risc0_dir().display()),
        });
        Ok(env)
    }

    pub fn set_event_handler<F>(&mut self, handler: F)
    where
        F: Fn(RzupEvent) + Send + Sync + 'static,
    {
        self.event_handler = Some(Box::new(handler));
    }

    pub fn emit(&self, event: RzupEvent) {
        if let Some(handler) = &self.event_handler {
            handler(event);
        }
    }

    pub fn risc0_dir(&self) -> &Path {
        &self.risc0_dir
    }

    pub fn cargo_bin_dir(&self) -> &Path {
        &self.cargo_bin_dir
    }

    pub fn rustup_toolchain_dir(&self) -> &Path {
        &self.rustup_toolchain_dir
    }

    pub fn settings_path(&self) -> &Path {
        &self.settings_file
    }

    pub fn tmp_dir(&self) -> &Path {
        &self.tmp_dir
    }

    pub fn platform(&self) -> &Platform {
        &self.platform
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn no_env(_: &str) -> VarResult<String> {
        Err(std::env::VarError::NotPresent)
    }

    #[test]
    fn test_default_env() {
        let env = Environment::new(no_env).unwrap();
        let home_dir = dirs::home_dir().unwrap();
        let expected_risc0_dir = home_dir.join(".risc0");
        let expected_cargo_bin_dir = home_dir.join(".cargo/bin");
        let expected_rustup_toolchain_dir = home_dir.join(".rustup/toolchains");

        assert_eq!(env.risc0_dir, expected_risc0_dir);
        assert!(env.risc0_dir.join(".rzup").is_file());
        assert_eq!(env.cargo_bin_dir, expected_cargo_bin_dir);
        assert_eq!(env.rustup_toolchain_dir, expected_rustup_toolchain_dir);
        assert_eq!(env.tmp_dir, expected_risc0_dir.join("tmp"));
        assert_eq!(env.settings_file, expected_risc0_dir.join("settings.toml"));
    }

    #[test]
    fn test_custom_root() {
        let tmp_dir1 = tempfile::tempdir().unwrap();
        let tmp_dir2 = tempfile::tempdir().unwrap();
        let env = Environment::with_paths(tmp_dir1.path(), tmp_dir2.path()).unwrap();

        assert_eq!(env.risc0_dir, tmp_dir1.path());
        assert_eq!(env.cargo_bin_dir, tmp_dir2.path().join(".cargo/bin"));
        assert_eq!(env.tmp_dir, tmp_dir1.path().join("tmp"));
        assert_eq!(env.settings_file, tmp_dir1.path().join("settings.toml"));
    }

    #[test]
    fn test_environment_with_risc0_home() {
        let tmp_dir = tempfile::tempdir().unwrap();
        let r0_tmp_dir = tmp_dir.path().join("risc0");

        let env = Environment::new(|key| {
            assert_eq!(key, "RISC0_HOME");
            Ok(r0_tmp_dir.to_string_lossy().into())
        })
        .unwrap();
        assert_eq!(env.risc0_dir, r0_tmp_dir);
    }
}
