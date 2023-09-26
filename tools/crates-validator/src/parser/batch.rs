use crate::{CrateName, Profile, ProfileSettings, Profiles};

#[derive(Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
pub(crate) struct Batches {
    batch: Vec<BatchConfig>,
}

#[derive(Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
struct BatchConfig {
    name: CrateName,
    crates: Vec<String>,
    settings: ProfileSettings,
}

impl From<Batches> for Profiles {
    fn from(value: Batches) -> Self {
        value.batch.into_iter().flat_map(Profiles::from).collect()
    }
}

impl From<BatchConfig> for Profiles {
    fn from(value: BatchConfig) -> Self {
        value
            .crates
            .into_iter()
            .map(|c| Profile {
                name: c,
                settings: value.settings.clone(),
            })
            .collect()
    }
}

#[cfg(test)]

mod tests {
    use std::collections::HashSet;

    use super::*;
    use crate::parser::{constants::PATH_YAML_CONFIG, test_helpers::profile_with_settings, utils};
    use crate::Merge;

    #[test]
    fn can_parse_file() {
        let config = utils::read_profile(PATH_YAML_CONFIG).unwrap();
        let batches = serde_yaml::from_str::<Batches>(&config).unwrap();
        let profiles: Profiles = batches.into();
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
        let profiles: Profiles = batches.into();
        assert_eq!(profiles.len(), 4);
        assert_eq!(expected_profiles, profiles.into_iter().collect());
    }
}
