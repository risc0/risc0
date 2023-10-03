#[derive(Debug, Clone, PartialEq, Eq, Hash, serde::Serialize, serde::Deserialize)]
#[serde(rename_all = "kebab-case")]
#[serde(untagged)]
pub enum Repo {
    Tag(TagRepo),
    Branch(BranchRepo),
    Path(PathRepo),
}

impl Repo {
    pub fn path(&self) -> &str {
        match self {
            Self::Tag(tag) => tag.tag.as_ref(),
            Self::Branch(git) => git.branch.as_ref(),
            Self::Path(local) => local.path.as_ref(),
        }
    }
}

#[derive(Debug, Clone, PartialEq, Eq, Hash, serde::Serialize, serde::Deserialize)]
pub struct TagRepo {
    tag: String,
}

#[derive(Debug, Clone, PartialEq, Eq, Hash, serde::Serialize, serde::Deserialize)]
pub struct BranchRepo {
    branch: String,
}

#[derive(Debug, Clone, PartialEq, Eq, Hash, serde::Serialize, serde::Deserialize)]
pub struct PathRepo {
    path: String,
}

impl Default for BranchRepo {
    fn default() -> Self {
        Self {
            branch: "main".to_string(),
        }
    }
}

impl Default for Repo {
    fn default() -> Self {
        Self::Branch(Default::default())
    }
}
