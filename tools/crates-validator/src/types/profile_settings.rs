use super::*;

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
    #[serde(skip_serializing_if = "Option::is_none")]
    pub patch: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub import_str: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub custom_main: Option<String>,
    #[serde(flatten)]
    #[serde(skip_serializing_if = "Option::is_none")]
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

fn validate_versions(versions: &Option<Versions>) -> Result<bool, ValidationError> {
    versions
        .as_ref()
        .map(|v| !v.is_empty())
        .ok_or(ValidationError::Custom("No versions specified".into()))
}
