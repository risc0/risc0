use std::collections::HashSet;

use super::{Profile, ProfileSettings};
use anyhow::{ensure, Result};
use serde_valid::Validate;

pub(crate) type ProfileTupleStr<'a> = (&'a str, Option<ProfileSettings>);
pub(crate) type ProfileTupleString = (String, Option<ProfileSettings>);
pub(crate) type ProfileVecStr<'a> = Vec<ProfileTupleStr<'a>>;
pub(crate) type ProfileVecString = Vec<ProfileTupleString>;

pub(crate) enum ProfileVariant {
    Single(Profile),
    Multiple(HashSet<Profile>)
}

pub(crate) trait ToProfile {
    fn to_profile(self) -> Result<ProfileVariant>;
}

pub(crate) trait ToProfiles {
    fn to_profiles(self) -> Vec<Result<Profile>>;
}

impl ToProfile for ProfileTupleString {
    fn to_profile(self) -> Result<Profile> {
        let (name, settings) = self;
        let profile = Profile {
            name,
            settings: settings.unwrap_or_default(),
        };
        ensure!(profile.validate().is_ok(), "Invalid profile: {:?}", profile);
        Ok(profile)
    }
}

impl<'a> ToProfile for ProfileTupleStr<'a> {
    fn to_profile(self) -> Result<Profile> {
        let (name, settings) = self;
        (name.to_string(), settings).to_profile()
    }
}

impl ToProfiles for ProfileVecString {
    fn to_profiles(self) -> Vec<Result<Profile>> {
        self.into_iter().map(|p| p.to_profile()).collect()
    }
}

impl<'a> ToProfiles for ProfileVecStr<'a> {
    fn to_profiles(self) -> Vec<Result<Profile>> {
        self.into_iter().map(|p| p.to_profile()).collect()
    }
}

impl ToProfile for Profile {
    fn to_profile(self) -> Result<Profile> {
        Ok(self)
    }
}

pub(crate) const fn default_true() -> bool {
    true
}

#[cfg(test)]
mod tests {
    use super::*;
    use rstest::*;
    use std::collections::HashSet;

    #[rstest]
    #[should_panic]
    #[case::empty(vec![])]
    #[should_panic]
    #[case::missing_name(vec![("", None)])]
    #[case::single_crate(vec![("example", None)])]
    #[case::multiple_crate(vec![
        ("example1", None),
        ("example2", None)
    ])]
    fn can_parse_profile(#[case] profiles: ProfileVecStr) {
        let len = profiles.len();
        let profiles = profiles
            .to_profiles()
            .into_iter()
            .map(|p| p.unwrap())
            .collect::<HashSet<Profile>>();

        assert!(!profiles.is_empty());
        assert_eq!(profiles.len(), len);
    }
}
