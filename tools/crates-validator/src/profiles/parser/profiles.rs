use std::collections::HashSet;

use anyhow::{ensure, Context, Result, anyhow};
use serde_valid::Validate;
use serde_yaml::{Mapping, Sequence, Value};

use crate::profiles::helpers::{ToProfile, ToProfiles};
use crate::profiles::Profile;

impl ToProfile for Mapping {
    fn to_profile(self) -> Result<Profile> {
        let profile = serde_yaml::from_value::<Profile>(Value::Mapping(self.clone()))
            .context("Failed to parse profile")?;
        ensure!(profile.validate().is_ok(), "Invalid profile: {:?}", profile);
        Ok(profile)
    }
}

impl ToProfiles for Sequence {
    fn to_profiles(self) -> Vec<Result<Profile>> {
        self.into_iter().map(|p| p.to_profile()).collect()
    }
}

impl ToProfile for Value {
    fn to_profile(self) -> Result<Profile> {
        match self {
            Value::Mapping(mapping) => mapping.to_profile(),
            Value::Sequence(_) => Err(anyhow!("Can't convert ")) sequence.to_profile(),
            t => Err(anyhow!("Invalid profile type: {t:?}")),
        }
    }
}

#[tracing::instrument(skip(config))]
pub(crate) fn parse(config: Sequence) -> Result<HashSet<Profile>> {
    let mut profiles = HashSet::new();
    for value in config {
        let profile = parse_profile(value)?;
        profiles.insert(profile);
    }
    Ok(profiles)
}

fn parse_profile(value: Value) -> Result<Profile> {
    let profile = serde_yaml::from_value::<Profile>(value.clone());
    match profile {
        Ok(profile) => Ok(profile),
        Err(error) => {
            tracing::warn!(?error, ?value, "Failed to parse profile");
            Err(error.into())
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use rstest::*;

    // - Change the input for the test to receive a yaml instead.
    #[rstest]
    #[case::empty(Sequence::new())]
    #[case::single(Sequence::from(vec![Value::String("example".to_string())]))]
    fn can_parse_config(#[case] config: Sequence) {
        let len = config.len();
        let profiles = parse(config).unwrap();
        assert_eq!(profiles.len(), len);
    }
}
