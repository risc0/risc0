use anyhow::{anyhow, ensure, Context, Result};
use serde_valid::Validate;
use serde_yaml::{Mapping, Sequence, Value};

use crate::profiles::helpers::ProfileVariant;
use crate::profiles::Profile;

pub(crate) trait ParseProfile {
    fn parse(self) -> Result<ProfileVariant>;
}

impl ParseProfile for Value {
    fn parse(self) -> Result<ProfileVariant> {
        match self {
            Value::Mapping(m) => m.parse(),
            Value::Sequence(s) => s.parse(),
            _ => Err(anyhow!("Invalid profile type: {self:?}")),
        }
    }
}

impl ParseProfile for Sequence {
    fn parse(self) -> Result<ProfileVariant> {
        let profiles = self
            .into_iter()
            .map(|p| p.parse())
            .collect::<Result<Vec<ProfileVariant>>>()?
            .into();
        Ok(profiles)
    }
}

impl ParseProfile for Mapping {
    fn parse(self) -> Result<ProfileVariant> {
        match self.get("crates") {
            None => parse_item(self.into()),
            Some(t) => t.clone().parse(),
        }
    }
}

fn parse_item(item: Value) -> Result<ProfileVariant> {
    let profile = serde_yaml::from_value::<Profile>(item).context("Failed to parse profile")?;
    ensure!(profile.validate().is_ok(), "Invalid profile: {:?}", profile);
    Ok(ProfileVariant::Single(profile))
}

#[cfg(test)]
mod tests {
    use crate::profiles::{parser::utils, ProfileSettings, PATH_YAML_CONFIG};

    use super::*;
    use rstest::*;

    fn get_profile(name: Option<&str>) -> Option<Profile> {
        name.map(|n| n.to_string()).map(|n| Profile {
            name: n,
            settings: ProfileSettings::default(),
        })
    }

    fn to_yaml(profiles: Vec<Option<&str>>) -> Value {
        profiles
            .into_iter()
            .map(get_profile)
            .map(|p| {
                p.and_then(|p| serde_yaml::to_value(p).ok())
                    .unwrap_or(Value::Null)
            })
            .collect()
    }

    #[test]
    fn can_read_config() {
        let config = utils::read_profile(PATH_YAML_CONFIG).unwrap();
        let profiles: Vec<Profile> = config.parse().unwrap().into();
        assert!(!profiles.is_empty());
    }

    #[rstest]
    #[should_panic]
    #[case::empty_config(to_yaml(vec![None]))]
    #[should_panic]
    #[case::empty_name(to_yaml(vec![Some("")]))]
    #[case::correct_file(to_yaml(vec![Some("example")]))]
    #[case::correct_file(to_yaml(vec![Some("example1"), Some("example2")]))]
    fn can_parse_config(#[case] config: Value) {
        let profiles: Vec<Profile> = dbg!(config).parse().unwrap().into();
        assert!(!profiles.is_empty());
    }
}
