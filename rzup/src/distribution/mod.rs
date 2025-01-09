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
pub mod github;

use crate::RzupError;
use crate::{env::Environment, Result, RzupEvent};

use downloader::{downloader::Builder, Download};
use fs2::FileExt;
use semver::Version;
use std::{path::PathBuf, time::Duration};

pub struct Platform {
    arch: &'static str,
    os: &'static str,
}

impl Platform {
    // TODO: allow specifying platform
    pub fn _new(arch: &'static str, os: &'static str) -> Self {
        Self { arch, os }
    }
    pub fn detect() -> Self {
        Self {
            arch: std::env::consts::ARCH,
            os: std::env::consts::OS,
        }
    }

    pub fn target_triple(&self) -> String {
        match self.os {
            "macos" => format!("{}-apple-darwin", self.arch),
            "linux" => format!("{}-{}-gnu", self.arch, self.os),
            _ => format!("{}-{}-{}", self.arch, self.os, std::env::consts::FAMILY),
        }
    }
}

impl std::fmt::Display for Platform {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{}", self.target_triple())
    }
}

pub(crate) trait Distribution {
    fn download_url(
        &self,
        env: &Environment,
        component_id: &str,
        version: Option<&Version>,
        platform: &Platform,
    ) -> Result<String>;

    fn get_archive_name(
        &self,
        component_id: &str,
        version: Option<&Version>,
        platform: &Platform,
    ) -> PathBuf;

    fn check_release_exists(&self, component_id: &str, version: &Version) -> Result<bool>;

    fn download_version(
        &self,
        env: &Environment,
        component_id: &str,
        version: Option<&Version>,
    ) -> Result<()> {
        let version = match version {
            Some(v) => v,
            None => &self.latest_version(env, component_id)?,
        };

        // check if release exists before download
        if !self.check_release_exists(component_id, version)? {
            env.emit(RzupEvent::InstallationFailed {
                id: component_id.to_string(),
                version: version.to_string(),
            });
            return Err(RzupError::InvalidVersion(format!(
                "{version} is not available for {component_id}",
            )));
        }

        let platform = env.platform();
        let archive_name = self.get_archive_name(component_id, Some(version), platform);
        let lock_path = env
            .tmp_dir()
            .join(format!("{}.lock", archive_name.display()));

        // create and lock the file
        let lock_file = std::fs::OpenOptions::new()
            .write(true)
            .create(true)
            .truncate(true)
            .open(&lock_path)?;

        lock_file.try_lock_exclusive().map_err(|_| {
            RzupError::Other(format!(
                "Another process is currently downloading {component_id} version {version}",
            ))
        })?;

        let download_url = self.download_url(env, component_id, Some(version), platform)?;

        // do download
        let archive = Download::new(&download_url).file_name(&archive_name);
        let mut dl = Builder::default()
            .connect_timeout(Duration::from_secs(4))
            .download_folder(env.tmp_dir())
            .parallel_requests(1)
            .build()
            .unwrap();

        dl.download(&[archive]).unwrap();

        // clean up lock file
        std::fs::remove_file(lock_path)?;
        Ok(())
    }

    fn latest_version(&self, env: &Environment, component_id: &str) -> Result<Version>;
}
