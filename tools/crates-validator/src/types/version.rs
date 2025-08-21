// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use super::traits::{GetVersions, Merge};

use anyhow::anyhow;

use std::{collections::BTreeSet, fmt::Display};

pub type Versions = BTreeSet<Version>;

impl Merge for Versions {
    fn merge(self, other: Self) -> Self {
        self.union(&other).cloned().collect()
    }
}

impl GetVersions for Versions {
    fn get_versions(&self) -> Vec<semver::Version> {
        self.iter()
            .filter_map(|v| match v {
                Version::Specific(v) => Some(v.clone()),
                Version::Latest => None,
            })
            .collect()
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

impl From<Version> for Option<semver::Version> {
    fn from(value: Version) -> Self {
        match value {
            Version::Specific(v) => Some(v),
            Version::Latest => None,
        }
    }
}

impl From<Option<semver::Version>> for Version {
    fn from(value: Option<semver::Version>) -> Self {
        match value {
            Some(v) => Version::Specific(v),
            None => Version::Latest,
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
