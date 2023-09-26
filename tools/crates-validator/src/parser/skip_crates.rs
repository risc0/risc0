use crate::{CrateNames, Profile, ProfileSettings, Profiles};

#[derive(Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
#[serde(rename_all = "kebab-case")]
pub(crate) struct SkipCrates {
    skip_crates: CrateNames,
}

impl From<SkipCrates> for Profiles {
    fn from(value: SkipCrates) -> Self {
        value
            .skip_crates
            .into_iter()
            .map(|c| Profile {
                name: c,
                settings: ProfileSettings::default(),
            })
            .collect()
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::parser::{constants::PATH_YAML_CONFIG, test_helpers::profile_from_name, utils};

    #[test]
    fn can_parse_file() {
        let config = utils::read_profile(PATH_YAML_CONFIG).unwrap();
        let batches = serde_yaml::from_str::<SkipCrates>(&config).unwrap();
        let profiles: Profiles = batches.into();
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
        let profiles: Profiles = batches.into();

        assert_eq!(profiles.len(), 4);
        assert_eq!(profiles, expected_profiles);
    }
}
