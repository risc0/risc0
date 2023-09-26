use crate::Profiles;

#[derive(Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
pub(crate) struct Individual {
    crates: Profiles,
}

impl From<Individual> for Profiles {
    fn from(value: Individual) -> Self {
        value.crates
    }
}

#[cfg(test)]
mod tests {
    use std::collections::HashSet;

    use crate::parser::{constants::PATH_YAML_CONFIG, utils};
    use crate::{Profile, ProfileSettings};

    use super::*;

    #[test]
    fn can_read_config() {
        let config = utils::read_profile(PATH_YAML_CONFIG).unwrap();
        let crates = serde_yaml::from_str::<Individual>(&config).unwrap();
        let profiles: Profiles = crates.into();
        assert!(!profiles.is_empty());
    }

    #[test]
    fn can_parse_config() {
        let config = r#"
            crates:
                - name: foo
                  std: false
                  fast-mode: true
                - name: bar
                  patch: |
                      use std::io;
                  inject-cc-flags: true
                - name: baz
                  custom-main: |
                    fn main() {
                        println!("Hello, world!");
                    }
                  run-prover: false
                - name: qux
                  should-fail: true
                  fast-mode: true
        "#;

        let foo = Profile {
            name: "foo".to_string(),
            settings: ProfileSettings {
                std: false,
                fast_mode: true,
                ..Default::default()
            },
        };
        let bar = Profile {
            name: "bar".to_string(),
            settings: ProfileSettings {
                patch: Some("use std::io;\n".to_string()),
                inject_cc_flags: true,
                ..Default::default()
            },
        };
        let baz = Profile {
            name: "baz".to_string(),
            settings: ProfileSettings {
                custom_main: Some(
                    r#"fn main() {
    println!("Hello, world!");
}
"#
                    .to_string(),
                ),
                run_prover: false,
                ..Default::default()
            },
        };
        let qux = Profile {
            name: "qux".to_string(),
            settings: ProfileSettings {
                should_fail: true,
                fast_mode: true,
                ..Default::default()
            },
        };
        let expected_profiles: HashSet<Profile> = [foo, bar, baz, qux].into_iter().collect();

        let batches = serde_yaml::from_str::<Individual>(config).unwrap();
        let profiles: Profiles = batches.into();

        assert_eq!(profiles.len(), 4);
        assert_eq!(expected_profiles, profiles.into_iter().collect());
    }
}
