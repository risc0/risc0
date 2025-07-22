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
use crate::distribution::{download_bytes, download_json, DistributionPlatform, ProgressWriter};
use crate::env::Environment;
use crate::{BaseUrls, Result, RzupError, RzupEvent};

use semver::Version;
use serde::Deserialize;
use std::collections::HashMap;
use std::fmt;

#[derive(Deserialize, Clone, PartialEq, Eq, Hash)]
#[serde(transparent)]
struct TargetTriple(String);

impl fmt::Display for TargetTriple {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        self.0.fmt(f)
    }
}

#[derive(Deserialize)]
struct Artifact {
    sha256: String,
}

#[derive(Deserialize)]
struct TargetSpecificRelease {
    artifacts: HashMap<TargetTriple, Artifact>,
}

#[derive(Deserialize)]
struct TargetAgnosticRelease {
    artifact: Artifact,
}

#[derive(Deserialize)]
#[serde(rename_all = "snake_case")]
enum Release {
    TargetSpecific(TargetSpecificRelease),
    TargetAgnostic(TargetAgnosticRelease),
}

#[derive(Deserialize)]
struct DistributionManifest {
    releases: HashMap<semver::Version, Release>,
    latest_version: semver::Version,
}

pub struct S3Bucket<'a> {
    base_urls: &'a BaseUrls,
}

impl<'a> S3Bucket<'a> {
    pub fn new(base_urls: &'a BaseUrls) -> Self {
        Self { base_urls }
    }

    fn get_distribution_manifest(
        &self,
        env: &Environment,
        component: &Component,
    ) -> Result<DistributionManifest> {
        env.emit(RzupEvent::Debug {
            message: format!("Fetching distribution information for {component}"),
        });

        let base_url = &self.base_urls.s3_base_url;
        let url = format!("{base_url}/rzup/components/{component}/distribution_manifest.json");
        download_json(&url, &None)
    }
}

impl<'a> DistributionPlatform for S3Bucket<'a> {
    fn latest_version(&self, env: &Environment, component: &Component) -> Result<Version> {
        env.emit(RzupEvent::Debug {
            message: format!("Fetching latest version for {component}"),
        });

        let manifest = self.get_distribution_manifest(env, component)?;

        Ok(manifest.latest_version)
    }

    fn download_version(
        &self,
        env: &Environment,
        component: &Component,
        version: &Version,
    ) -> Result<()> {
        let manifest = self.get_distribution_manifest(env, component)?;

        let Some(release) = manifest.releases.get(version) else {
            env.emit(RzupEvent::InstallationFailed {
                id: component.to_string(),
                version: version.to_string(),
            });
            return Err(RzupError::InvalidVersion(format!(
                "{version} is not available for {component}",
            )));
        };

        let platform = env.platform();
        let artifact = match release {
            Release::TargetSpecific(release) => {
                let target_triple = TargetTriple(platform.target_triple());

                let Some(artifact) = release.artifacts.get(&target_triple) else {
                    env.emit(RzupEvent::InstallationFailed {
                        id: component.to_string(),
                        version: version.to_string(),
                    });
                    return Err(RzupError::UnsupportedPlatform(format!(
                        "{component} is not available for platform {target_triple}",
                    )));
                };
                artifact
            }
            Release::TargetAgnostic(release) => &release.artifact,
        };

        let archive_name = component.archive_name(platform)?;

        let download_path = env.tmp_dir().join(archive_name);
        let mut download_file = std::fs::OpenOptions::new()
            .write(true)
            .create(true)
            .truncate(true)
            .open(&download_path)?;

        let base_url = &self.base_urls.s3_base_url;
        let sha256 = &artifact.sha256;
        let download_url = format!("{base_url}/rzup/components/{component}/sha256/{sha256}");
        let mut resp = download_bytes(&download_url, &None)?;

        env.emit(RzupEvent::DownloadStarted {
            id: component.to_string(),
            version: version.to_string(),
            url: download_url.clone(),
            len: resp.content_length(),
        });

        resp.copy_to(&mut ProgressWriter::new(
            component.to_string(),
            env,
            &mut download_file,
        ))
        .map_err(|e| RzupError::Other(format!("Failed to download file: {e}")))?;

        env.emit(RzupEvent::DownloadCompleted {
            id: component.to_string(),
            version: version.to_string(),
        });

        Ok(())
    }
}
