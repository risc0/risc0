use anyhow::{anyhow, ensure, Context, Result};
use serde_valid::Validate;
use serde_yaml::{Mapping, Sequence, Value};

use crate::profiles::helpers::{ProfileVariant, ToProfile};
use crate::profiles::Profile;

pub(crate) fn parse(config: &Value) -> Result<ProfileVariant> {
    match config.get("crates") {
        None => config.clone().to_profile(),
        Some(Value::Mapping(m)) => m.clone().to_profile(),
        Some(Value::Sequence(s)) => s.clone().to_profile(),
        _ => Err(anyhow!("Invalid profile: {:?}", config)),
    }
}

impl ToProfile for Mapping {
    fn to_profile(self) -> Result<ProfileVariant> {
        dbg!(&self);
        let profile = serde_yaml::from_value::<Profile>(Value::Mapping(self.clone()))
            .context("Failed to parse profile")?;
        ensure!(profile.validate().is_ok(), "Invalid profile: {:?}", profile);
        Ok(ProfileVariant::Single(profile))
    }
}

impl ToProfile for Sequence {
    fn to_profile(self) -> Result<ProfileVariant> {
        let profiles = self
            .into_iter()
            .map(|p| p.to_profile())
            .collect::<Result<Vec<ProfileVariant>>>()?
            .into();
        Ok(profiles)
    }
}

impl ToProfile for Value {
    fn to_profile(self) -> Result<ProfileVariant> {
        match self {
            Value::Mapping(mapping) => mapping.to_profile(),
            Value::Sequence(sequence) => sequence.to_profile(),
            t => Err(anyhow!("Invalid profile type: {t:?}")),
        }
    }
}

#[cfg(test)]
mod tests {
    use crate::profiles::{ProfileSettings, parser::utils};

    use super::*;
    use rstest::*;

    fn get_profile(name: Option<&str>) -> Option<Profile> {
        name.map(|n| n.to_string()).map(|n| Profile {
            name: n,
            settings: ProfileSettings::default(),
        })
    }

    fn to_yaml(profiles: Vec<Option<&str>>) -> Value {
        profiles.into_iter().map(get_profile).map(|p| {
            p.and_then(|p| serde_yaml::to_value(p).ok())
                .unwrap_or(Value::Null)
        }).collect()
    }

    #[test]
    fn can_read_config() {
        let config = utils::read_profile("profiles/profiles.yaml").unwrap();
        let profiles: Vec<Profile> = parse(&config).unwrap().into();
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
        let profiles: Vec<Profile> = parse(&config).unwrap().into();
        assert!(!profiles.is_empty());
    }
}
