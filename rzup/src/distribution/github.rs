use crate::distribution::{Distribution, Platform};
use crate::env::Environment;
use crate::{Result, RzupError, RzupEvent};

use reqwest::blocking::Client;
use semver::Version;
use serde::Deserialize;
use std::path::PathBuf;
use std::time::Duration;

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
        env: &Environment,
        component_id: &str,
        version: Option<&Version>,
        platform: &Platform,
    ) -> Result<String> {
        let (asset, ext) = self.asset_name(component_id, platform);
        let version_str = match version {
            Some(v) => self.get_version_str(component_id, v),
            None => {
                env.emit(RzupEvent::Debug {
                    message: format!("No version specified, fetching latest for {}", component_id),
                });
                format!("v{}", self.latest_version(env, component_id)?)
            }
        };
        let repo = self.repo_name(component_id);
        Ok(format!(
            "https://github.com/risc0/{}/releases/download/{}/{}.{}",
            repo, version_str, asset, ext
        ))
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

    fn latest_version(&self, env: &Environment, component_id: &str) -> Result<Version> {
        env.emit(RzupEvent::Debug {
            message: format!("Fetching latest version for {}", component_id),
        });

        let client = Client::builder()
            .timeout(Duration::from_secs(10))
            .build()
            .map_err(|e| RzupError::Other(e.to_string()))?;

        let repo = self.repo_name(component_id);
        let url = format!(
            "https://api.github.com/repos/risc0/{}/releases/latest",
            repo
        );

        let response = client
            .get(&url)
            .header("User-Agent", "rzup")
            .send()
            .unwrap();

        let status = response.status();

        if status == 403 || status == 429 {
            return Err(RzupError::RateLimited(
                "GitHub API rate limit exceeded. Please try again later.".to_string(),
            ));
        }

        let release: GithubReleaseResponse = response
            .json()
            .map_err(|e| RzupError::Other(e.to_string()))?;

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
    fn check_release_exists(&self, component_id: &str, version: &Version) -> Result<bool> {
        let client = Client::builder()
            .timeout(Duration::from_secs(10))
            .build()
            .map_err(|e| RzupError::Other(format!("Failed to create HTTP client: {}", e)))?;

        let repo = self.repo_name(component_id);
        let version_str = self.get_version_str(component_id, version);
        let url = format!(
            "https://api.github.com/repos/risc0/{}/releases/tags/{}",
            repo, version_str
        );

        let response = client
            .get(&url)
            .header("User-Agent", "rzup")
            .send()
            .map_err(|e| RzupError::Other(format!("Failed to check release: {}", e)))?;

        match response.status() {
            reqwest::StatusCode::OK => Ok(true),
            reqwest::StatusCode::NOT_FOUND => Ok(false),
            reqwest::StatusCode::FORBIDDEN | reqwest::StatusCode::TOO_MANY_REQUESTS => {
                Err(RzupError::RateLimited(
                    "GitHub API rate limit exceeded. Please try again later.".to_string(),
                ))
            }
            status => Err(RzupError::Other(format!(
                "Unexpected response checking release: {}",
                status
            ))),
        }
    }
}
