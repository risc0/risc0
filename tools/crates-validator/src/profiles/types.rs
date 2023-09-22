use std::collections::HashMap;

pub(crate) type Profiles = Vec<Profile>;
pub(crate) type GroupedProfiles = HashMap<String, Profiles>;

#[derive(
    Debug, Clone, PartialEq, Eq, Hash, serde::Serialize, serde::Deserialize, serde_valid::Validate,
)]
pub struct Profile {
    #[validate(min_length = 1)]
    pub name: String,
    #[serde(flatten)]
    pub settings: ProfileSettings,
}

#[derive(
    Default,
    Debug,
    Clone,
    PartialEq,
    Eq,
    Hash,
    serde::Serialize,
    serde::Deserialize,
    serde_valid::Validate,
)]
#[serde(default)]
#[serde(rename_all = "kebab-case")]
pub struct ProfileSettings {
    pub run_prover: bool,
    pub should_fail: bool,
    pub inject_cc_flags: bool,
    pub std: bool,
    #[serde(default = "default_true")]
    pub fast_mode: bool,
    pub patch: Option<String>,
    pub import_str: Option<String>,
    pub custom_main: Option<String>,
    #[serde(flatten)]
    pub repo: Option<Repo>,
    pub versions: Option<Vec<semver::Version>>,
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

// Find a way to merge Vec<Profile> with duplicated names into a single Profile
// batch_profiles.chain(individual_profiles).merge()
// -> This should return a Vec<Profile> with no duplicated crates, and if more
// than one Profile for a single crate specify settings, they should be combined
// in a sensible way.

// pub(crate) trait Group {
//     fn group(self, other: Self) -> GroupedProfiles;
// }

// impl Group for Profiles {
//     fn group(self, other: Self) -> GroupedProfiles {
//         self.into_iter()
//             .chain(other.into_iter())
//             .fold(GroupedProfiles::new(), |mut acc, p| {
//                 acc.entry(p.name.clone()).or_default().push(p);
//                 acc
//             })
//     }
// }

// pub(crate) trait Merge {
//     fn merge(self) -> Profiles;
// }

// impl Merge for GroupedProfiles {
//     fn merge(self) -> Profiles {
//         self.into_iter()
//             .flat_map(|(_, profiles)| profiles.into_iter())
//             .collect()
//     }
// }

const fn default_true() -> bool {
    true
}
