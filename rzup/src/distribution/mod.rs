use std::{path::PathBuf, time::Duration};

pub mod github;

use crate::RzupError;
use crate::{env::Environment, Result, RzupEvent};
use downloader::{downloader::Builder, Download};
use semver::Version;

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

pub trait Distribution {
    fn download_url(
        &self,
        component_id: &str,
        version: Option<&Version>,
        platform: &Platform,
    ) -> String;
    fn get_archive_name(
        &self,
        component_id: &str,
        version: Option<&Version>,
        platform: &Platform,
    ) -> PathBuf;

    fn download_version(
        &self,
        env: &Environment,
        component_id: &str,
        version: Option<&Version>,
    ) -> Result<()> {
        let platform = Platform::new();

        let download_url = self.download_url(component_id, version, &platform);

        env.emit(RzupEvent::DownloadStarted {
            url: download_url.clone(),
        });

        let archive_name = self.get_archive_name(component_id, version, &platform);

        let archive = Download::new(&download_url).file_name(&archive_name);

        std::fs::create_dir_all(env.tmp_dir())?;

        let mut dl = Builder::default()
            .connect_timeout(Duration::from_secs(4))
            .download_folder(env.tmp_dir())
            .parallel_requests(1)
            .build()
            .unwrap();

        dl.download(&[archive])
            .map_err(|e| RzupError::Other(anyhow::anyhow!("Download failed: {}", e)))?;

        env.emit(RzupEvent::DownloadCompleted {
            id: component_id.to_string(),
        });

        Ok(())
    }

    fn latest_version(&self, component_id: &str) -> Result<Version>;
}
