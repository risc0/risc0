use super::Profile;
use super::ProfileSettings;

#[derive(Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
pub(crate) struct Batches {
    batch: Vec<BatchConfig>,
}

#[derive(Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
struct BatchConfig {
    name: String,
    crates: Vec<String>,
    settings: ProfileSettings,
}

impl From<Batches> for Vec<Profile> {
    fn from(value: Batches) -> Self {
        value
            .batch
            .into_iter()
            .flat_map(Vec::<Profile>::from)
            .collect()
    }
}

impl From<BatchConfig> for Vec<Profile> {
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
    use super::*;
    use crate::profiles::parser::utils;
    use crate::profiles::PATH_YAML_CONFIG;

    #[test]
    fn can_parse_file() {
        let config = utils::read_profile(PATH_YAML_CONFIG).unwrap();
        let batches = serde_yaml::from_value::<Batches>(config).unwrap();
        let profiles: Vec<Profile> = batches.into();
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
              - bar
              - baz
          - name: bar
            settings:
              inject-cc-flags: true
              patch: |
                [patch.crates-io]
                bar = { git = 'git://github.com/bar/bar.git' }
            crates:
              - foo
              - baz
        "#;
        let batches = serde_yaml::from_str::<Batches>(config).unwrap();
        let profiles: Vec<Profile> = batches.into();
        assert_eq!(profiles.len(), 4);
    }
}
