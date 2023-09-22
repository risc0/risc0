use anyhow::{ensure, Result};
use semver::Version;

pub(crate) trait Combine {
    fn combine(&mut self, other: Self) -> Result<()>;
}

/// A profile is a collection of settings that can be applied to a crate.
#[derive(
    Debug, Clone, PartialEq, Eq, Hash, serde::Serialize, serde::Deserialize, serde_valid::Validate,
)]
pub struct Profile {
    #[validate(min_length = 1)]
    pub name: String,
    #[serde(flatten)]
    pub settings: ProfileSettings,
}

impl Combine for Profile {
    fn combine(&mut self, other: Self) -> Result<()> {
        ensure!(
            self.name == other.name,
            "Cannot combine profiles with different names"
        );
        self.settings.combine(other.settings)
    }
}

/// The settings that can be applied to a crate.
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
    #[serde(default = "super::default_true")]
    pub fast_mode: bool,
    pub patch: Option<String>,
    pub import_str: Option<String>,
    pub custom_main: Option<String>,
    #[serde(flatten)]
    pub repo: Option<Repo>,
    pub versions: Option<Vec<Version>>,
}

impl Combine for ProfileSettings {
    fn combine(&mut self, other: Self) -> Result<()> {
        match (self.versions.clone(), other.versions) {
            (Some(mut versions), Some(other_versions)) => {
                versions.extend(other_versions);
                versions.sort();
                versions.dedup();
                self.versions = Some(versions);
            }
            (Some(_), None) => {}
            (None, Some(other_versions)) => {
                self.versions = Some(other_versions);
            }
            (None, None) => {}
        }

        self.std = self.std || other.std;
        self.fast_mode = self.fast_mode || other.fast_mode;
        self.run_prover = self.run_prover || other.run_prover;
        self.should_fail = self.should_fail || other.should_fail;
        self.inject_cc_flags = self.inject_cc_flags || other.inject_cc_flags;

        Ok(())
    }
}

/// The RISC Zero repository location containing templates and crate imports
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
