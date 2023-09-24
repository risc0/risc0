use std::{
    collections::{BTreeMap, BTreeSet},
    iter::Chain,
    vec::IntoIter,
};

use semver::Version;
use serde_valid::validation::Error as ValidationError;

pub(crate) type Profiles = Vec<Profile>;
pub(crate) type CrateName = String;
pub(crate) type CrateNames = Vec<CrateName>;
pub(crate) type GroupedProfiles = BTreeMap<String, Profiles>;
type Versions = BTreeSet<Version>;

#[derive(
    Debug, Clone, PartialEq, Eq, Hash, serde::Serialize, serde::Deserialize, serde_valid::Validate,
)]
pub struct Profile {
    #[validate(min_length = 1)]
    pub name: CrateName,
    #[serde(flatten)]
    pub settings: ProfileSettings,
}

#[derive(
    Debug, Clone, PartialEq, Eq, Hash, serde::Serialize, serde::Deserialize, serde_valid::Validate,
)]
#[serde(default)]
#[serde(rename_all = "kebab-case")]
pub struct ProfileSettings {
    pub run_prover: bool,
    pub should_fail: bool,
    pub inject_cc_flags: bool,
    pub std: bool,
    pub fast_mode: bool,
    pub patch: Option<String>,
    pub import_str: Option<String>,
    pub custom_main: Option<String>,
    #[serde(flatten)]
    pub repo: Option<Repo>,
    #[validate(custom(validate_versions))]
    pub versions: Option<Versions>,
}

impl Default for ProfileSettings {
    fn default() -> Self {
        Self {
            run_prover: false,
            should_fail: false,
            inject_cc_flags: false,
            std: false,
            fast_mode: true,
            patch: None,
            import_str: None,
            custom_main: None,
            repo: None,
            versions: None,
        }
    }
}

#[derive(Debug, Clone, PartialEq, Eq, Hash, serde::Serialize, serde::Deserialize)]
#[serde(rename_all = "kebab-case")]
pub enum Repo {
    Git(String),
    Local(String),
}

impl Default for Repo {
    fn default() -> Self {
        Self::Git("main".to_string())
    }
}

trait Group {
    fn group(self) -> GroupedProfiles;
}

impl Group for Chain<IntoIter<Profile>, IntoIter<Profile>> {
    fn group(self) -> GroupedProfiles {
        self.fold(GroupedProfiles::new(), |mut acc, p| {
            acc.entry(p.name.clone()).or_default().push(p.clone());
            acc
        })
    }
}

pub trait Merge {
    fn merge(self, other: Self) -> Self;
}

impl Merge for Profiles {
    fn merge(self, other: Self) -> Self {
        match (self.is_empty(), other.is_empty()) {
            (true, true) => Profiles::new(),
            (true, false) => self,
            (false, true) => other,
            (false, false) => self
                .into_iter()
                .chain(other)
                .group()
                .into_values()
                .map(|profiles| {
                    profiles
                        .into_iter()
                        .reduce(|acc, p| acc.merge(p))
                        .expect("Should never be empty")
                })
                .collect(),
        }
    }
}

impl Merge for Profile {
    fn merge(self, other: Self) -> Self {
        assert_eq!(self.name, other.name);
        Self {
            name: self.name,
            settings: self.settings.merge(other.settings),
        }
    }
}

impl Merge for ProfileSettings {
    fn merge(self, other: Self) -> Self {
        Self {
            run_prover: self.run_prover || other.run_prover,
            should_fail: self.should_fail || other.should_fail,
            inject_cc_flags: self.inject_cc_flags || other.inject_cc_flags,
            std: self.std || other.std,
            fast_mode: self.fast_mode || other.fast_mode,
            patch: self.patch.or(other.patch),
            import_str: self.import_str.or(other.import_str),
            custom_main: self.custom_main.or(other.custom_main),
            repo: self.repo.or(other.repo),
            versions: self.versions.merge(other.versions),
        }
    }
}

impl Merge for Option<Versions> {
    fn merge(self, other: Self) -> Self {
        self.unwrap_or_default()
            .union(&other.unwrap_or_default())
            .cloned()
            .map(Some)
            .collect()
    }
}

pub trait Exclude {
    fn exclude(self, other: Self) -> Self;
}

impl Exclude for Profiles {
    fn exclude(self, other: Self) -> Self {
        self.into_iter()
            .filter(|p| !other.iter().any(|o| o.name == p.name))
            .collect()
    }
}

fn validate_versions(versions: &Option<Versions>) -> Result<bool, ValidationError> {
    versions
        .as_ref()
        .map(|v| !v.is_empty())
        .ok_or(ValidationError::Custom("No versions specified".into()))
}
