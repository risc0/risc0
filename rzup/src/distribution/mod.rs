use std::{path::PathBuf, time::Duration};

use crate::{env::Environment, Result, RzupError};
use downloader::{downloader::Builder, Download};
use semver::Version;
use serde::Deserialize;

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
        println!("URL: {}", download_url);
        let archive_name = self.get_archive_name(component_id, version, &platform);

        let archive = Download::new(&download_url).file_name(&archive_name);

        std::fs::create_dir_all(env.tmp_dir())?;

        let mut dl = Builder::default()
            .connect_timeout(Duration::from_secs(4))
            .download_folder(env.tmp_dir()) // or any arbitrary path
            .parallel_requests(1)
            .build()
            .unwrap();

        let _res = dl.download(&[archive]).unwrap(); // other error handling
                                                     //

        Ok(())
    }
    fn latest_version(&self, component_id: &str) -> Result<Version>;
}

#[derive(Deserialize)]
struct GithubReleaseResponse {
    tag_name: String,
}
pub struct GithubRelease;

impl GithubRelease {
    fn repo_name(&self, component_id: &str) -> String {
        match component_id {
            "cargo-risczero" => "risc0",
            "rust" => "rust",
            _ => "risc0",
        }
        .to_string()
    }

    fn asset_name(&self, component_id: &str, platform: &Platform) -> (String, &'static str) {
        match component_id {
            "rust" => (
                format!("rust-toolchain-{}", platform.target_triple()),
                "tar.gz",
            ),
            "cargo-risczero" => (format!("cargo-risczero-{}", platform), "tgz"),
            _ => (format!("{}-{}", component_id, platform), "tgz"),
        }
    }

    fn get_version_str(&self, component_id: &str, version: &Version) -> String {
        match component_id {
            // rust toolchain uses date-based versions with r0. prefix
            "rust" => format!("r0.{}.{}.{}", version.major, version.minor, version.patch),
            // cargo-risczero use v-prefixed versions
            _ => format!("v{}", version),
        }
    }
}

impl Distribution for GithubRelease {
    fn download_url(
        &self,
        component_id: &str,
        version: Option<&Version>,
        platform: &Platform,
    ) -> String {
        let (asset, ext) = self.asset_name(component_id, platform);
        let version_str = match version {
            Some(v) => self.get_version_str(component_id, v),
            None => self.latest_version(component_id).unwrap().to_string(),
        };

        let repo = self.repo_name(component_id);

        format!(
            "https://github.com/risc0/{}/releases/download/{}/{}.{}",
            repo, version_str, asset, ext
        )
    }

    fn get_archive_name(
        &self,
        component_id: &str,
        _version: Option<&Version>,
        platform: &Platform,
    ) -> PathBuf {
        let (asset_name, extension) = self.asset_name(component_id, platform);
        PathBuf::from(format!("{}.{}", asset_name, extension))
    }

    fn latest_version(&self, component_id: &str) -> Result<Version> {
        // let client = Client::builder()
        //     .timeout(Duration::from_secs(10))
        //     .build()
        //     .map_err(|e| RzupError::Other(e.into()))?;

        let repo = self.repo_name(component_id);
        let url = format!(
            "https://api.github.com/repos/risc0/{}/releases/latest",
            repo
        );

        let response = reqwest::blocking::get(&url).map_err(|e| RzupError::Other(e.into()))?;
        // .get(&url)
        // .header("User-Agent", "rzup")
        // .send()
        // .map_err(|e| RzupError::Other(e.into())?;

        let release: GithubReleaseResponse =
            response.json().map_err(|e| RzupError::Other(e.into()))?;

        // parse version from tag name
        let version_str = match component_id {
            "rust" => release
                .tag_name
                .strip_prefix("r0.")
                .ok_or_else(|| RzupError::InvalidVersion(release.tag_name.clone()))?,
            _ => release
                .tag_name
                .strip_prefix('v')
                .ok_or_else(|| RzupError::InvalidVersion(release.tag_name.clone()))?,
        };

        Version::parse(version_str).map_err(|_| RzupError::InvalidVersion(version_str.to_string()))
    }
}
