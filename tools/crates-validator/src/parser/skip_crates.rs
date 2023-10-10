// Copyright 2023 RISC Zero, Inc.
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

use anyhow::Result;

use crate::types::{
    aliases::{CrateNames, Profiles},
    profile::Profile,
};

#[derive(Debug, Default, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
#[serde(rename_all = "kebab-case")]
pub(crate) struct SkipCrates {
    pub skip_crates: CrateNames,
}

impl TryFrom<SkipCrates> for Profiles {
    type Error = anyhow::Error;
    fn try_from(value: SkipCrates) -> Result<Self> {
        value
            .skip_crates
            .into_iter()
            .map(Profile::try_from)
            .collect::<Result<Self>>()
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::constants::PATH_YAML_CONFIG;
    use crate::parser::{test_helpers::profile_from_name, utils};

    #[test]
    fn can_parse_file() {
        let config = utils::read_profile(PATH_YAML_CONFIG).unwrap();
        let batches = serde_yaml::from_str::<SkipCrates>(&config).unwrap();
        let profiles: Profiles = batches.try_into().unwrap();
        assert!(!profiles.is_empty());
    }

    #[test]
    fn can_parse_config() {
        let config = r#"
            skip-crates:
              - foo
              - bar
              - baz
              - qux
        "#;
        let expected_profiles: Profiles = ["foo", "bar", "baz", "qux"]
            .iter()
            .map(profile_from_name)
            .collect();

        let batches = serde_yaml::from_str::<SkipCrates>(config).unwrap();
        let profiles: Profiles = batches.try_into().unwrap();

        assert_eq!(profiles.len(), 4);
        assert_eq!(profiles, expected_profiles);
    }
}
