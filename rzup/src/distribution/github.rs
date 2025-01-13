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
use crate::distribution::{
    check_for_not_found, download_json, download_to_writer, parse_cpp_version, Os, Platform,
};
use crate::env::Environment;
use crate::{BaseUrls, Result, RzupError, RzupEvent};

use fs2::FileExt;
use semver::Version;
use serde::Deserialize;
use std::path::PathBuf;

fn parse_version_from_tag_name(component: &Component, tag_name: &str) -> Result<Version> {
    Ok(match component {
        Component::RustToolchain => {
            Version::parse(tag_name.strip_prefix("r0.").ok_or_else(|| {
                RzupError::InvalidVersion("Invalid Rust version tag format".into())
            })?)?
        }
        Component::CppToolchain => parse_cpp_version(tag_name)?,
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

fn component_repo_name(component: &Component) -> &'static str {
    match component {
        Component::CargoRiscZero | Component::R0Vm => "risc0",
        Component::RustToolchain => "rust",
        Component::CppToolchain => "toolchain",
    }
}

fn component_asset_name(
    component: &Component,
    platform: &Platform,
) -> Result<(String, &'static str)> {
    Ok(match component {
        Component::RustToolchain => (format!("rust-toolchain-{platform}"), "tar.gz"),
        Component::CargoRiscZero => (format!("cargo-risczero-{platform}"), "tgz"),
        Component::CppToolchain => {
            let triple = match (platform.arch, platform.os) {
                ("x86_64", Os::Linux) => "riscv32im-linux-x86_64",
                ("aarch64", Os::MacOs) => "riscv32im-osx-arm64",
                (other, os) => {
                    return Err(RzupError::UnsupportedPlatform(format!(
                        "unknown architecture {other} for {os}"
                    )))
                }
            };
            (triple.to_string(), "tar.xz")
        }
        Component::R0Vm => (format!("r0vm-{platform}"), "tgz"),
    })
}

#[test]
fn component_asset_name_test() {
    assert_eq!(
        component_asset_name(
            &Component::RustToolchain,
            &Platform::new("x86_64", Os::Linux)
        )
        .unwrap(),
        ("rust-toolchain-x86_64-unknown-linux-gnu".into(), "tar.gz")
    );
    assert_eq!(
        component_asset_name(
            &Component::CargoRiscZero,
            &Platform::new("x86_64", Os::Linux)
        )
        .unwrap(),
        ("cargo-risczero-x86_64-unknown-linux-gnu".into(), "tgz")
    );
    assert_eq!(
        component_asset_name(
            &Component::CppToolchain,
            &Platform::new("x86_64", Os::Linux)
        )
        .unwrap(),
        ("riscv32im-linux-x86_64".into(), "tar.xz")
    );
    assert_eq!(
        component_asset_name(&Component::R0Vm, &Platform::new("x86_64", Os::Linux)).unwrap(),
        ("r0vm-x86_64-unknown-linux-gnu".into(), "tgz")
    );

    assert_eq!(
        component_asset_name(
            &Component::CppToolchain,
            &Platform::new("aarch64", Os::MacOs)
        )
        .unwrap(),
        ("riscv32im-osx-arm64".into(), "tar.xz")
    );
    assert_eq!(
        component_asset_name(
            &Component::CppToolchain,
            &Platform::new("x86_64", Os::MacOs)
        )
        .unwrap_err(),
        RzupError::UnsupportedPlatform("unknown architecture x86_64 for Mac OS".into())
    );
}

fn component_version_str(component: &Component, version: &Version) -> String {
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
        Component::CargoRiscZero | Component::R0Vm => format!("v{version}"),
    }
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

    fn download_url(
        &self,
        env: &Environment,
        component: &Component,
        version: Option<&Version>,
        platform: &Platform,
    ) -> Result<String> {
        let (asset, ext) = component_asset_name(component, platform)?;
        let version_str = match version {
            Some(v) => component_version_str(component, v),
            None => {
                env.emit(RzupEvent::Debug {
                    message: format!("No version specified, fetching latest for {component}"),
                });
                format!("v{}", self.latest_version(env, component)?)
            }
        };
        let repo = component_repo_name(component);
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
    ) -> Result<PathBuf> {
        let (asset_name, ext) = component_asset_name(component, platform)?;
        Ok(PathBuf::from(format!("{asset_name}.{ext}")))
    }

    fn check_release_exists(&self, component: &Component, version: &Version) -> Result<bool> {
        let repo = component_repo_name(component);
        let version_str = component_version_str(component, version);
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

        let repo = component_repo_name(component);
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
        let archive_name = self.get_archive_name(component, Some(version), platform)?;
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
