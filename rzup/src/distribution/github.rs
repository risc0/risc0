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

use fs2::FileExt;
use reqwest::{blocking::Client, IntoUrl};
use semver::Version;
use serde::Deserialize;
use std::{path::PathBuf, time::Duration};

fn http_client_get(url: impl IntoUrl) -> Result<reqwest::blocking::Response> {
    let client = Client::builder()
        .timeout(Duration::from_secs(10))
        .build()
        .map_err(|e| RzupError::Other(format!("Failed to create HTTP client: {e}")))?;

    client
        .get(url)
        .header("User-Agent", "rzup")
        .send()
        .map_err(|e| RzupError::Other(e.to_string()))
}

fn error_on_status(status: reqwest::StatusCode) -> Result<()> {
    if !status.is_success() {
        match status {
            reqwest::StatusCode::FORBIDDEN | reqwest::StatusCode::TOO_MANY_REQUESTS => {
                Err(RzupError::RateLimited(
                    "GitHub API rate limit exceeded. Please try again later.".to_string(),
                ))
            }
            status => Err(RzupError::Other(format!("Unexpected response: {status}",))),
        }
    } else {
        Ok(())
    }
}

fn check_for_not_found(url: impl IntoUrl) -> Result<bool> {
    let response = http_client_get(url)?;
    let status = response.status();
    if status == reqwest::StatusCode::NOT_FOUND {
        return Ok(false);
    }
    error_on_status(status)?;
    Ok(true)
}

fn download_json<RetT: serde::de::DeserializeOwned>(url: impl IntoUrl) -> Result<RetT> {
    let response = http_client_get(url)?;
    error_on_status(response.status())?;
    response.json().map_err(|e| RzupError::Other(e.to_string()))
}

fn download_to_writer(url: impl IntoUrl, w: &mut impl std::io::Write) -> Result<()> {
    let mut response = http_client_get(url)?;
    error_on_status(response.status())?;
    response
        .copy_to(w)
        .map_err(|e| RzupError::Other(format!("Failed to download file: {e}")))?;
    Ok(())
}

fn parse_version_from_tag_name(component: &Component, tag_name: &str) -> Result<Version> {
    Ok(match component {
        Component::RustToolchain => {
            Version::parse(tag_name.strip_prefix("r0.").ok_or_else(|| {
                RzupError::InvalidVersion("Invalid Rust version tag format".into())
            })?)?
        }
        Component::CppToolchain => {
            let parts: Vec<_> = tag_name.split('.').collect();
            if parts.len() != 3 {
                return Err(RzupError::InvalidVersion(
                    "Invalid C++ version tag format".into(),
                ));
            }
            let numbers = parts
                .into_iter()
                .map(|p| {
                    p.parse::<u64>()
                        .map_err(|_| RzupError::InvalidVersion("Invalid cpp version number".into()))
                })
                .collect::<Result<Vec<_>>>()?;
            Version::new(numbers[0], numbers[1], numbers[2])
        }
        Component::CargoRiscZero | Component::R0Vm => Version::parse(
            tag_name
                .strip_prefix('v')
                .ok_or_else(|| RzupError::InvalidVersion("Invalid version tag format".into()))?,
        )?,
    })
}

#[test]
fn parse_version_from_tag_name_test() {
    assert_eq!(
        parse_version_from_tag_name(&Component::RustToolchain, "r0.1.2.3").unwrap(),
        Version::new(1, 2, 3)
    );
    assert!(parse_version_from_tag_name(&Component::RustToolchain, "r0.foo").is_err());
    assert!(parse_version_from_tag_name(&Component::RustToolchain, "").is_err());
    assert_eq!(
        parse_version_from_tag_name(&Component::CppToolchain, "1.2.3").unwrap(),
        Version::new(1, 2, 3)
    );
    assert!(parse_version_from_tag_name(&Component::CppToolchain, "1.2").is_err());
    assert!(parse_version_from_tag_name(&Component::CppToolchain, "1").is_err());
    assert!(parse_version_from_tag_name(&Component::CppToolchain, "a.b.c").is_err());
    assert!(parse_version_from_tag_name(&Component::CppToolchain, "1.2.c").is_err());
    assert!(parse_version_from_tag_name(&Component::CppToolchain, "").is_err());
    assert_eq!(
        parse_version_from_tag_name(&Component::CargoRiscZero, "v1.2.3").unwrap(),
        Version::new(1, 2, 3)
    );
    assert!(parse_version_from_tag_name(&Component::CargoRiscZero, "v1.2").is_err());
    assert!(parse_version_from_tag_name(&Component::CargoRiscZero, "v").is_err());
    assert!(parse_version_from_tag_name(&Component::CargoRiscZero, "").is_err());
    assert_eq!(
        parse_version_from_tag_name(&Component::R0Vm, "v1.2.3").unwrap(),
        Version::new(1, 2, 3)
    );
    assert!(parse_version_from_tag_name(&Component::R0Vm, "v1.2").is_err());
    assert!(parse_version_from_tag_name(&Component::R0Vm, "v").is_err());
    assert!(parse_version_from_tag_name(&Component::R0Vm, "").is_err());
}

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

    fn repo_name(&self, component: &Component) -> &'static str {
        match component {
            Component::CargoRiscZero => "risc0",
            Component::RustToolchain => "rust",
            Component::CppToolchain => "toolchain",
            _ => "risc0",
        }
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
        let repo = self.repo_name(component);
        let version_str = self.get_version_str(component, version);
        let url = format!(
            "{base_url}/repos/risc0/{repo}/releases/tags/{version_str}",
            base_url = self.base_urls.github_api_base_url
        );

        check_for_not_found(&url)
    }

    pub fn latest_version(&self, env: &Environment, component: &Component) -> Result<Version> {
        env.emit(RzupEvent::Debug {
            message: format!("Fetching latest version for {component}"),
        });

        let repo = self.repo_name(component);
        let url = format!(
            "{base_url}/repos/risc0/{repo}/releases/latest",
            base_url = self.base_urls.github_api_base_url
        );

        let release: GithubReleaseResponse = download_json(&url)?;

        parse_version_from_tag_name(component, &release.tag_name)
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

        let download_result = (|| {
            let download_path = env.tmp_dir().join(archive_name);
            let mut download_file = std::fs::OpenOptions::new()
                .write(true)
                .create(true)
                .truncate(true)
                .open(&download_path)?;

            download_to_writer(&download_url, &mut download_file)
        })();

        env.emit(RzupEvent::DownloadCompleted {
            id: component.to_string(),
            version: version.to_string(),
        });

        // clean up lock file
        std::fs::remove_file(lock_path)?;

        download_result
    }
}
