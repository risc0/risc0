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
pub struct ProfileSettings {
    #[serde(default)]
    pub versions: Option<Vec<Version>>,
    #[serde(default)]
    pub std: bool,
    #[serde(default = "super::default_true")]
    pub fast_mode: bool,
    #[serde(flatten)]
    pub risc_zero_repository: RiscZeroRepo,
    #[serde(default)]
    pub custom_main: Option<String>,
    #[serde(default)]
    pub import_str: Option<String>,
    #[serde(default)]
    pub run_prover: bool,
    #[serde(default)]
    pub should_fail: bool,
    #[serde(default)]
    pub inject_cc_flags: bool,
    #[serde(default)]
    pub patch: Option<String>,
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
pub enum RiscZeroRepo {
    #[serde(rename = "risc0_gh_branch")]
    Github(String),
    #[serde(rename = "risc0_path")]
    Local(String),
}

impl Default for RiscZeroRepo {
    fn default() -> Self {
        Self::Github("main".to_string())
    }
}
