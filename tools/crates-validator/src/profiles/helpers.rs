use std::collections::HashSet;

use super::{Profile, ProfileSettings};
use anyhow::{ensure, Result};
use serde_valid::Validate;

pub(crate) type ProfileTupleStr<'a> = (&'a str, Option<ProfileSettings>);
pub(crate) type ProfileTupleString = (String, Option<ProfileSettings>);
pub(crate) type ProfileVecStr<'a> = Vec<ProfileTupleStr<'a>>;
pub(crate) type ProfileVecString = Vec<ProfileTupleString>;

#[derive(Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
pub(crate) enum ProfileVariant {
    Single(Profile),
    Multiple(HashSet<Profile>),
}

impl ProfileVariant {
    fn merge(self, other: Self) -> Self {
        match (self, other) {
            (Self::Single(p1), Self::Single(p2)) => vec![p1, p2].into(),
            (Self::Single(p1), Self::Multiple(mut p2)) => {
                p2.insert(p1);
                p2.into()
            }
            (Self::Multiple(mut p1), Self::Single(p2)) => {
                p1.insert(p2);
                p1.into()
            }
            (Self::Multiple(mut p1), Self::Multiple(p2)) => {
                p1.extend(p2);
                p1.into()
            }
        }
    }
}

impl From<Vec<ProfileVariant>> for ProfileVariant {
    fn from(profiles: Vec<ProfileVariant>) -> Self {
        profiles
            .into_iter()
            .fold(Self::Multiple(HashSet::new()), |acc, p| acc.merge(p))
    }
}

impl From<Vec<Profile>> for ProfileVariant {
    fn from(profiles: Vec<Profile>) -> Self {
        Self::Multiple(profiles.into_iter().collect())
    }
}

impl From<HashSet<Profile>> for ProfileVariant {
    fn from(profiles: HashSet<Profile>) -> Self {
        Self::Multiple(profiles)
    }
}

impl From<ProfileVariant> for Vec<Profile> {
    fn from(profiles: ProfileVariant) -> Self {
        match profiles {
            ProfileVariant::Single(p) => vec![p],
            ProfileVariant::Multiple(p) => p.into_iter().collect(),
        }
    }
}

impl From<ProfileVariant> for HashSet<Profile> {
    fn from(profiles: ProfileVariant) -> Self {
        profiles.into()
    }
}

impl From<Profile> for ProfileVariant {
    fn from(profile: Profile) -> Self {
        Self::Single(profile)
    }
}

impl FromIterator<ProfileVariant> for ProfileVariant {
    fn from_iter<I: IntoIterator<Item = ProfileVariant>>(iter: I) -> Self {
        iter.into_iter()
            .fold(Self::Multiple(HashSet::new()), |acc, p| acc.merge(p))
    }
}

pub(crate) trait ToProfile {
    fn to_profile(self) -> Result<ProfileVariant>;
}

impl ToProfile for ProfileTupleString {
    fn to_profile(self) -> Result<ProfileVariant> {
        let (name, settings) = self;
        let profile = Profile {
            name,
            settings: settings.unwrap_or_default(),
        };
        ensure!(profile.validate().is_ok(), "Invalid profile: {:?}", profile);
        Ok(profile.into())
    }
}

impl<'a> ToProfile for ProfileTupleStr<'a> {
    fn to_profile(self) -> Result<ProfileVariant> {
        let (name, settings) = self;
        (name.to_string(), settings).to_profile()
    }
}

impl ToProfile for ProfileVecString {
    fn to_profile(self) -> Result<ProfileVariant> {
        self.into_iter().map(|p| p.to_profile()).collect()
    }
}

impl<'a> ToProfile for ProfileVecStr<'a> {
    fn to_profile(self) -> Result<ProfileVariant> {
        self.into_iter().map(|p| p.to_profile()).collect()
    }
}

impl ToProfile for Profile {
    fn to_profile(self) -> Result<ProfileVariant> {
        Ok(self.into())
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
        let profiles: Vec<Profile> = profiles
            .into_iter()
            .map(|p| p.to_profile())
            .collect::<Result<ProfileVariant>>()
            .unwrap()
            .into();

        assert!(!profiles.is_empty());
        assert_eq!(profiles.len(), len);
    }
}
