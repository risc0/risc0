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
