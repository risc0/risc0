// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{collections::btree_set::IntoIter, iter::Chain, str::FromStr};

use anyhow::{Result, ensure};
use serde_valid::Validate;

use super::{
    aliases::{CrateName, GroupedProfiles},
    profile_settings::ProfileSettings,
    traits::{GetVersions, Group, Merge},
    version::Versions,
};

#[derive(
    Debug,
    Clone,
    PartialEq,
    Eq,
    Hash,
    PartialOrd,
    Ord,
    serde::Serialize,
    serde::Deserialize,
    serde_valid::Validate,
)]
pub struct Profile {
    #[validate(min_length = 1)]
    name: CrateName,
    #[serde(flatten)]
    pub settings: ProfileSettings,
    #[serde(default = "Versions::default")]
    pub versions: Versions,
}

impl Profile {
    pub fn new(
        name: CrateName,
        settings: ProfileSettings,
        versions: Option<Versions>,
    ) -> Result<Self> {
        let profile = Self {
            name,
            settings,
            versions: versions.unwrap_or_default(),
        };
        ensure!(profile.validate().is_ok(), "Invalid profile: {:?}", profile);
        Ok(profile)
    }

    pub fn name(&self) -> &str {
        self.name.as_ref()
    }

    pub fn has_same_name(&self, other: &Self) -> bool {
        self.name == other.name
    }

    pub fn should_skip(&self) -> bool {
        self.settings.skip
    }

    pub fn settings(&self) -> &ProfileSettings {
        &self.settings
    }

    pub fn versions(&self) -> Vec<semver::Version> {
        self.versions.get_versions()
    }
}

impl FromStr for Profile {
    type Err = anyhow::Error;
    fn from_str(s: &str) -> std::result::Result<Self, Self::Err> {
        let name = CrateName::from_str(s)?;
        Self::new(name, ProfileSettings::default(), None)
    }
}

impl TryFrom<String> for Profile {
    type Error = anyhow::Error;
    fn try_from(name: String) -> Result<Self, Self::Error> {
        Profile::new(name, ProfileSettings::default(), None)
    }
}

impl TryFrom<(String, ProfileSettings)> for Profile {
    type Error = anyhow::Error;
    fn try_from(value: (String, ProfileSettings)) -> std::result::Result<Self, Self::Error> {
        Profile::new(value.0, value.1, None)
    }
}

impl Merge for Profile {
    fn merge(self, other: Self) -> Self {
        assert_eq!(self.name, other.name);
        Self {
            name: self.name,
            settings: self.settings.merge(other.settings),
            versions: self.versions.merge(other.versions),
        }
    }
}

impl Group for Chain<IntoIter<Profile>, IntoIter<Profile>> {
    fn group(self) -> GroupedProfiles {
        self.fold(GroupedProfiles::new(), |mut acc, p| {
            acc.entry(p.name.clone()).or_default().insert(p.clone());
            acc
        })
    }
}
