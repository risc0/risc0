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
    #[serde(default = "super::default_true")]
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
