pub mod github;

use crate::RzupError;
use crate::{env::Environment, Result, RzupEvent};

use downloader::{downloader::Builder, Download};
use semver::Version;
use std::{path::PathBuf, time::Duration};

pub struct Platform {
    arch: &'static str,
    os: &'static str,
}

impl Platform {
    pub fn new() -> Self {
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
                "Version {} is not available for {}",
                version, component_id
            )));
        }

        let platform = Platform::new();
        env.emit(RzupEvent::Debug {
            message: format!("Platform detected: {}", platform),
        });

        let download_url = self.download_url(env, component_id, Some(version), &platform)?;
        let version_str = version.to_string();

        env.emit(RzupEvent::Debug {
            message: format!(
                "Downloading {} version {}",
                component_id,
                version_str.clone()
            ),
        });

        env.emit(RzupEvent::DownloadStarted {
            id: component_id.to_string(),
            version: version_str.clone(),
            url: download_url.clone(),
        });

        let archive_name = self.get_archive_name(component_id, Some(version), &platform);
        env.emit(RzupEvent::Debug {
            message: format!("Download will be saved to: {}", archive_name.display()),
        });

        // TODO: Use custom client impl with blocking reqwest to utilize GITHUB TOKEN
        let archive = Download::new(&download_url).file_name(&archive_name);
        std::fs::create_dir_all(env.tmp_dir())?;

        let mut dl = Builder::default()
            .connect_timeout(Duration::from_secs(4))
            .download_folder(env.tmp_dir())
            .parallel_requests(1)
            .build()
            .map_err(|e| RzupError::Other(format!("Failed to create downloader: {}", e)))?;

        dl.download(&[archive])
            .map_err(|e| RzupError::Other(format!("Download failed: {}", e)))?;

        env.emit(RzupEvent::DownloadCompleted {
            id: component_id.to_string(),
            version: version_str,
        });

        Ok(())
    }

    fn latest_version(&self, env: &Environment, component_id: &str) -> Result<Version>;
}
