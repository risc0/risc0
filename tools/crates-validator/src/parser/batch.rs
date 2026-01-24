// Copyright 2026 RISC Zero, Inc.
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

use crate::types::{
    aliases::{CrateName, Profiles},
    profile::Profile,
    profile_settings::ProfileSettings,
    traits::Reduce,
};
use anyhow::Result;

#[derive(Debug, Default, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
pub(crate) struct Batches {
    pub batch: Vec<BatchConfig>,
}

#[derive(Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
pub(crate) struct BatchConfig {
    pub name: CrateName,
    pub crates: Vec<String>,
    pub settings: Option<ProfileSettings>,
}

impl TryFrom<Batches> for Profiles {
    type Error = anyhow::Error;
    fn try_from(value: Batches) -> Result<Self> {
        value
            .batch
            .into_iter()
            .map(Profiles::try_from)
            .collect::<Result<Vec<Profiles>>>()?
            .into_iter()
            .flatten()
            .map(Ok)
            .collect::<Result<Self>>()
            .map(|p: Profiles| p.reduce())
    }
}

impl TryFrom<BatchConfig> for Profiles {
    type Error = anyhow::Error;
    fn try_from(value: BatchConfig) -> Result<Self> {
        let settings = value.settings.unwrap_or_default();
        value
            .crates
            .into_iter()
            .map(|c| (c, settings.clone()))
            .map(Profile::try_from)
            .collect::<Result<Self>>()
            .map(|p: Profiles| p.reduce())
    }
}

#[cfg(test)]
mod tests {
    use std::collections::HashSet;

    use super::*;
    use crate::{
        constants::PATH_YAML_CONFIG,
        parser::{test_helpers::profile_with_settings, utils},
        types::traits::Merge,
    };

    #[test]
    fn can_parse_file() {
        let config = utils::read_profile(PATH_YAML_CONFIG).unwrap();
        let batches = serde_yaml::from_str::<Batches>(&config).unwrap();
        let profiles: Profiles = batches.try_into().unwrap();

        profiles.iter().for_each(|p| {
            p.name().starts_with("crossbeam").then(|| {
                assert!(p.settings.patch.is_some());
            });
            (p.name().eq("zip") || p.name().eq("ring")).then(|| {
                assert!(p.settings.inject_cc_flags);
            });
            p.name().starts_with("serde").then(|| {
                assert!(p.settings.std);
            });
        });
        profiles.contains(&"tfhe".parse().unwrap());
        profiles.contains(&"openssl".parse().unwrap());

        assert!(!profiles.is_empty());
    }

    #[test]
    fn can_parse_config() {
        let config = r#"
        batch:
          - name: foo
            settings:
              std: true
              fast-mode: true
              patch: |
                [patch.crates-io]
                foo = { git = 'git://github.com/foo/foo.git' }
            crates:
              - foo1
              - foo2
          - name: bar
            settings:
              inject-cc-flags: true
              patch: |
                [patch.crates-io]
                bar = { git = 'git://github.com/bar/bar.git' }
            crates:
              - bar1
              - bar2
        "#;

        let foo_settings = ProfileSettings {
            std: true,
            fast_mode: true,
            patch: Some(
                r#"[patch.crates-io]
foo = { git = 'git://github.com/foo/foo.git' }
"#
                .into(),
            ),
            ..Default::default()
        };

        let bar_settings = ProfileSettings {
            inject_cc_flags: true,
            patch: Some(
                r#"[patch.crates-io]
bar = { git = 'git://github.com/bar/bar.git' }
"#
                .into(),
            ),
            ..Default::default()
        };

        let foo_batch = ["foo1", "foo2"]
            .iter()
            .map(|n| (n, foo_settings.clone()))
            .map(profile_with_settings)
            .collect::<Profiles>();
        let bar_batch = ["bar1", "bar2"]
            .iter()
            .map(|n| (n, bar_settings.clone()))
            .map(profile_with_settings)
            .collect::<Profiles>();
        let expected_profiles: HashSet<Profile> = foo_batch
            .clone()
            .merge(bar_batch.clone())
            .into_iter()
            .collect();

        let batches = serde_yaml::from_str::<Batches>(config).unwrap();
        let profiles: Profiles = batches.try_into().unwrap();

        profiles.iter().filter(|p| p.name() == "foo").for_each(|p| {
            if p.name().starts_with("foo") {
                assert_eq!(p.settings, foo_settings);
            } else if p.name().starts_with("bar") {
                assert_eq!(p.settings, bar_settings);
            } else {
                panic!("Unexpected profile: {:?}", p);
            }
        });

        assert_eq!(profiles.len(), 4);
        assert_eq!(expected_profiles, profiles.into_iter().collect());
    }
}
