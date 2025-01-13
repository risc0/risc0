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
use crate::components::Component;
use crate::distribution::Platform;
use crate::env::Environment;
use crate::{BaseUrls, Result, RzupError, RzupEvent};

use downloader::{downloader::Builder, Download};
use fs2::FileExt;
use reqwest::blocking::Client;
use semver::Version;
use serde::Deserialize;
use std::{path::PathBuf, time::Duration};

#[derive(Deserialize)]
struct GithubReleaseResponse {
    tag_name: String,
}

pub struct GithubRelease<'a> {
    base_urls: &'a BaseUrls,
}

impl<'a> GithubRelease<'a> {
    pub fn new(base_urls: &'a BaseUrls) -> Self {
        Self { base_urls }
    }

    fn repo_name(&self, component: &Component) -> String {
        match component {
            Component::CargoRiscZero => "risc0",
            Component::RustToolchain => "rust",
            Component::CppToolchain => "toolchain",
            _ => "risc0",
        }
        .to_string()
    }

    fn asset_name(&self, component: &Component, platform: &Platform) -> (String, &'static str) {
        match component {
            Component::RustToolchain => (format!("rust-toolchain-{platform}"), "tar.gz"),
            Component::CargoRiscZero => (format!("cargo-risczero-{platform}"), "tgz"),
            Component::CppToolchain => {
                let triple = match (platform.arch, platform.os) {
                    ("x86_64", "linux") => "riscv32im-linux-x86_64",
                    ("aarch64", "macos") => "riscv32im-osx-arm64",
                    _ => panic!("Unsupported platform for cpp toolchain"),
                };
                (triple.to_string(), "tar.xz")
            }
            _ => (format!("{component}-{platform}"), "tgz"),
        }
    }

    fn get_version_str(&self, component: &Component, version: &Version) -> String {
        match component {
            // rust toolchain uses date-based versions with r0. prefix
            Component::RustToolchain => {
                format!("r0.{}.{}.{}", version.major, version.minor, version.patch)
            }
            // cpp toolchain uses date-based versions
            Component::CppToolchain => format!(
                "{:04}.{:02}.{:02}",
                version.major, version.minor, version.patch
            ),
            // cargo-risczero use v-prefixed versions
            _ => format!("v{version}"),
        }
    }

    fn download_url(
        &self,
        env: &Environment,
        component: &Component,
        version: Option<&Version>,
        platform: &Platform,
    ) -> Result<String> {
        let (asset, ext) = self.asset_name(component, platform);
        let version_str = match version {
            Some(v) => self.get_version_str(component, v),
            None => {
                env.emit(RzupEvent::Debug {
                    message: format!("No version specified, fetching latest for {component}"),
                });
                format!("v{}", self.latest_version(env, component)?)
            }
        };
        let repo = self.repo_name(component);
        Ok(format!(
            "{base_url}/{repo}/releases/download/{version_str}/{asset}.{ext}",
            base_url = self.base_urls.risc0_github_base_url
        ))
    }

    pub fn get_archive_name(
        &self,
        component: &Component,
        _version: Option<&Version>,
        platform: &Platform,
    ) -> PathBuf {
        let (asset_name, ext) = self.asset_name(component, platform);
        PathBuf::from(format!("{asset_name}.{ext}"))
    }

    fn check_release_exists(&self, component: &Component, version: &Version) -> Result<bool> {
        let client = Client::builder()
            .timeout(Duration::from_secs(10))
            .build()
            .map_err(|e| RzupError::Other(format!("Failed to create HTTP client: {e}")))?;

        let repo = self.repo_name(component);
        let version_str = self.get_version_str(component, version);
        let url = format!(
            "{base_url}/repos/risc0/{repo}/releases/tags/{version_str}",
            base_url = self.base_urls.github_api_base_url
        );

        let response = client
            .get(&url)
            .header("User-Agent", "rzup")
            .send()
            .map_err(|e| RzupError::Other(format!("Failed to check release: {e}")))?;

        match response.status() {
            reqwest::StatusCode::OK => Ok(true),
            reqwest::StatusCode::NOT_FOUND => Ok(false),
            reqwest::StatusCode::FORBIDDEN | reqwest::StatusCode::TOO_MANY_REQUESTS => {
                Err(RzupError::RateLimited(
                    "GitHub API rate limit exceeded. Please try again later.".to_string(),
                ))
            }
            status => Err(RzupError::Other(format!(
                "Unexpected response checking release: {status}",
            ))),
        }
    }

    pub fn latest_version(&self, env: &Environment, component: &Component) -> Result<Version> {
        env.emit(RzupEvent::Debug {
            message: format!("Fetching latest version for {component}"),
        });

        let client = Client::builder()
            .timeout(Duration::from_secs(10))
            .build()
            .map_err(|e| RzupError::Other(e.to_string()))?;

        let repo = self.repo_name(component);
        let url = format!(
            "{base_url}/repos/risc0/{repo}/releases/latest",
            base_url = self.base_urls.github_api_base_url
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
        let version_str = match component {
            Component::RustToolchain => release
                .tag_name
                .strip_prefix("r0.")
                .expect("Invalid rust version tag format"),
            Component::CppToolchain => &*{
                let parts: Vec<_> = release.tag_name.split('.').collect();
                assert_eq!(parts.len(), 3, "Invalid cpp version tag format");
                format!(
                    "{}.{}.{}",
                    parts[0].parse::<u64>().expect("Invalid cpp version number"),
                    parts[1].parse::<u64>().expect("Invalid cpp version number"),
                    parts[2].parse::<u64>().expect("Invalid cpp version number")
                )
            },
            _ => release
                .tag_name
                .strip_prefix('v')
                .expect("Invalid version tag format"),
        };

        Version::parse(version_str).map_err(|_| RzupError::InvalidVersion(version_str.to_string()))
    }

    pub fn download_version(
        &self,
        env: &Environment,
        component: &Component,
        version: Option<&Version>,
    ) -> Result<()> {
        let version = match version {
            Some(v) => v,
            None => &self.latest_version(env, component)?,
        };

        // check if release exists before download
        if !self.check_release_exists(component, version)? {
            env.emit(RzupEvent::InstallationFailed {
                id: component.to_string(),
                version: version.to_string(),
            });
            return Err(RzupError::InvalidVersion(format!(
                "{version} is not available for {component}",
            )));
        }

        let platform = env.platform();
        let archive_name = self.get_archive_name(component, Some(version), platform);
        let lock_path = env
            .tmp_dir()
            .join(format!("{}.lock", archive_name.display()));

        let download_url = self.download_url(env, component, Some(version), platform)?;

        // create and lock the file
        let lock_file = std::fs::OpenOptions::new()
            .write(true)
            .create(true)
            .truncate(true)
            .open(&lock_path)?;

        lock_file.try_lock_exclusive().map_err(|_| {
            RzupError::Other(format!(
                "Another process is currently downloading {component} version {version}",
            ))
        })?;

        env.emit(RzupEvent::DownloadStarted {
            id: component.to_string(),
            version: version.to_string(),
            url: download_url.clone(),
        });

        let archive = Download::new(&download_url).file_name(&archive_name);
        let mut dl = Builder::default()
            .connect_timeout(Duration::from_secs(4))
            .download_folder(env.tmp_dir())
            .parallel_requests(1)
            .build()
            .unwrap();

        let download_result = dl
            .download(&[archive])
            .unwrap()
            .into_iter()
            .map(|res| res.map(|_| ()))
            .collect::<std::result::Result<(), _>>()
            .map_err(|e| RzupError::Other(format!("Error downloading: {e}")));

        env.emit(RzupEvent::DownloadCompleted {
            id: component.to_string(),
            version: version.to_string(),
        });

        // clean up lock file
        std::fs::remove_file(lock_path)?;

        download_result
    }
}
