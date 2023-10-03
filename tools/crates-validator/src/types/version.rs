use std::fmt::Display;

use anyhow::anyhow;

use super::*;

pub type Versions = BTreeSet<Version>;

impl Merge for Versions {
    fn merge(self, other: Self) -> Self {
        self.union(&other).cloned().collect()
    }
}

#[derive(
    Default,
    Debug,
    Clone,
    PartialEq,
    Eq,
    Hash,
    PartialOrd,
    Ord,
    serde::Serialize,
    serde::Deserialize,
)]
#[repr(u8)]
#[serde(untagged)]
pub enum Version {
    #[default]
    Latest = 1,
    Specific(semver::Version) = 0,
}

impl From<Version> for Versions {
    fn from(value: Version) -> Self {
        Self::from_iter(vec![value])
    }
}

impl From<Option<semver::Version>> for Version {
    fn from(value: Option<semver::Version>) -> Self {
        match value {
            Some(v) => Self::Specific(v),
            None => Self::Latest,
        }
    }
}

impl TryFrom<Version> for semver::Version {
    type Error = anyhow::Error;
    fn try_from(value: Version) -> std::result::Result<Self, Self::Error> {
        match value {
            Version::Specific(v) => Ok(v),
            Version::Latest => Err(anyhow!("Cannot convert Version::Latest to semver::Version")),
        }
    }
}

impl Display for Version {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Version::Latest => write!(f, "latest"),
            Version::Specific(v) => write!(f, "{}", v),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use rstest::*;

    #[rstest]
    #[case::specific_same_order(
        Version::Specific(semver::Version::new(1, 0, 0)),
        Version::Specific(semver::Version::new(1, 0, 0)),
        std::cmp::Ordering::Equal
    )]
    #[case::latest_same_order(Version::Latest, Version::Latest, std::cmp::Ordering::Equal)]
    #[case::specific_latest_order(
        Version::Specific(semver::Version::new(1, 0, 0)),
        Version::Latest,
        std::cmp::Ordering::Less
    )]
    fn version_has_correct_order(
        #[case] v1: Version,
        #[case] v2: Version,
        #[case] order: std::cmp::Ordering,
    ) {
        assert_eq!(v1.cmp(&v2), order);
    }
}
