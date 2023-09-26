use super::*;

#[derive(
    Debug, Clone, PartialEq, Eq, Hash, PartialOrd, Ord, serde::Serialize, serde::Deserialize,
)]
pub struct Versions(BTreeSet<Version>);

impl Versions {
    pub fn inner(&self) -> &BTreeSet<Version> {
        &self.0
    }
}

impl Default for Versions {
    fn default() -> Self {
        Self::from(Version::default())
    }
}

impl Merge for Versions {
    fn merge(self, other: Self) -> Self {
        self.0.union(&other.0).cloned().collect()
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
pub enum Version {
    #[default]
    Latest = 1,
    Specific(semver::Version) = 0,
}

impl FromIterator<Version> for Versions {
    fn from_iter<T: IntoIterator<Item = Version>>(iter: T) -> Self {
        Self(iter.into_iter().collect())
    }
}

impl From<Version> for Versions {
    fn from(value: Version) -> Self {
        Self::from_iter(vec![value])
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
