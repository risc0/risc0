// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use crate::components::Component;
use crate::distribution::{
    DistributionPlatform, Platform, ProgressWriter, check_for_not_found, download_bytes,
    download_json, parse_cpp_version,
};
use crate::env::Environment;
use crate::{BaseUrls, Result, RzupError, RzupEvent, TransferKind};

use semver::Version;
use serde::Deserialize;

fn parse_version_from_tag_name(component: &Component, tag_name: &str) -> Result<Version> {
    match component {
        Component::RustToolchain => Ok(Version::parse(tag_name.strip_prefix("r0.").ok_or_else(
            || RzupError::InvalidVersion("Invalid Rust version tag format".into()),
        )?)?),
        Component::CppToolchain | Component::Gdb => parse_cpp_version(tag_name),
        Component::CargoRiscZero | Component::R0Vm => {
            Ok(Version::parse(tag_name.strip_prefix('v').ok_or_else(
                || RzupError::InvalidVersion("Invalid version tag format".into()),
            )?)?)
        }
        Component::Risc0Groth16 => Err(RzupError::UnsupportedDistributionPlatform(
            "github download not supported for risc0-groth16".into(),
        )),
    }
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

    fn download_url(
        &self,
        component: &Component,
        version: &Version,
        platform: &Platform,
    ) -> Result<String> {
        let (asset, ext) = component.asset_name(platform)?;
        let version_str = component.version_str(version);
        let repo = component.repo_name()?;
        Ok(format!(
            "{base_url}/{repo}/releases/download/{version_str}/{asset}.{ext}",
            base_url = self.base_urls.risc0_github_base_url
        ))
    }

    fn check_release_exists(
        &self,
        env: &Environment,
        component: &Component,
        version: &Version,
    ) -> Result<bool> {
        let repo = component.repo_name()?;
        let version_str = component.version_str(version);
        let url = format!(
            "{base_url}/repos/risc0/{repo}/releases/tags/{version_str}",
            base_url = self.base_urls.github_api_base_url
        );

        check_for_not_found(&url, env.github_token())
    }
}

impl<'a> DistributionPlatform for GithubRelease<'a> {
    fn latest_version(&self, env: &Environment, component: &Component) -> Result<Version> {
        env.emit(RzupEvent::Debug {
            message: format!("Fetching latest version for {component}"),
        });

        let repo = component.repo_name()?;
        let url = format!(
            "{base_url}/repos/risc0/{repo}/releases/latest",
            base_url = self.base_urls.github_api_base_url
        );

        let release: GithubReleaseResponse = download_json(&url, env.github_token())?;

        parse_version_from_tag_name(component, &release.tag_name)
    }

    fn download_version(
        &self,
        env: &Environment,
        component: &Component,
        version: &Version,
    ) -> Result<()> {
        // check if release exists before download
        if !self.check_release_exists(env, component, version)? {
            env.emit(RzupEvent::InstallationFailed {
                id: component.to_string(),
                version: version.to_string(),
            });
            return Err(RzupError::InvalidVersion(format!(
                "{version} is not available for {component}",
            )));
        }

        let platform = env.platform();
        let archive_name = component.archive_name(platform)?;

        let download_path = env.tmp_dir().join(archive_name);
        let mut download_file = std::fs::OpenOptions::new()
            .write(true)
            .create(true)
            .truncate(true)
            .open(&download_path)?;

        let download_url = self.download_url(component, version, platform)?;
        let mut resp = download_bytes(&download_url, env.github_token())?;

        env.emit(RzupEvent::TransferStarted {
            kind: TransferKind::Download,
            id: component.to_string(),
            version: Some(version.to_string()),
            url: Some(download_url.clone()),
            len: resp.content_length(),
        });

        resp.copy_to(&mut ProgressWriter::new(
            component.to_string(),
            env,
            &mut download_file,
        ))
        .map_err(|e| RzupError::Other(format!("Failed to download file: {e}")))?;

        env.emit(RzupEvent::TransferCompleted {
            kind: TransferKind::Download,
            id: component.to_string(),
            version: Some(version.to_string()),
        });

        Ok(())
    }
}
