// Copyright 2024 RISC Zero, Inc.
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

use std::collections::HashMap;

use serde::Deserialize;

use crate::utils::target::Target;

pub struct GithubReleaseInfo {
    pub assets: HashMap<Target, GithubAsset>,
    pub tag_name: String,
    pub published_at: String,
}

#[derive(Deserialize)]
pub struct GithubAsset {
    pub browser_download_url: String,
    name: String,
}

impl GithubReleaseInfo {
    fn parse_assets(assets: Vec<GithubAsset>) -> HashMap<Target, GithubAsset> {
        let mut asset_map = HashMap::new();
        for asset in assets {
            if let Some(target) = Self::extract_target_from_name(&asset.name) {
                asset_map.insert(target, asset);
            }
        }
        asset_map
    }

    fn extract_target_from_name(name: &str) -> Option<Target> {
        if name.contains("aarch64-apple-darwin") || name.contains("osx-arm64") {
            Some(Target::Aarch64AppleDarwin)
        } else if name.contains("x86_64-unknown-linux-gnu") || name.contains("linux-x86_64") {
            Some(Target::X86_64UnknownLinuxGnu)
        } else {
            None
        }
    }
}

impl<'de> Deserialize<'de> for GithubReleaseInfo {
    fn deserialize<D>(deserializer: D) -> Result<Self, D::Error>
    where
        D: serde::Deserializer<'de>,
    {
        #[derive(Deserialize)]
        struct Release {
            assets: Vec<GithubAsset>,
            tag_name: String,
            published_at: String,
        }

        let release = Release::deserialize(deserializer)?;
        let assets = GithubReleaseInfo::parse_assets(release.assets);

        Ok(GithubReleaseInfo {
            assets,
            tag_name: release.tag_name,
            published_at: release.published_at,
        })
    }
}
