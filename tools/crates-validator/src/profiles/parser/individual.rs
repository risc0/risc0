use crate::profiles::Profiles;

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
    use crate::profiles::{parser::utils, PATH_YAML_CONFIG};

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
                  settings:
                      std: false
                      fast-mode: true
                - name: bar
                  settings:
                      patch: |
                          use std::io;
                      inject-cc-flags: true
                - name: baz
                  settings:
                    custom-main: |
                      fn main() {
                          println!("Hello, world!");
                      }
                    run-prover: false
                - name: qux
                  settings:
                    std: true
                    fast-mode: true
        "#;
        let batches = serde_yaml::from_str::<Individual>(config).unwrap();
        let profiles: Profiles = batches.into();
        assert_eq!(profiles.len(), 4);
    }
}
