// Copyright 2023 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#[derive(Debug, Clone, PartialEq, Eq, Hash, serde::Serialize, serde::Deserialize)]
#[serde(rename_all = "kebab-case")]
#[serde(untagged)]
pub enum Repo {
    Tag(TagRepo),
    Branch(BranchRepo),
    Path(PathRepo),
}

impl Repo {
    pub fn tag(tag: impl Into<String>) -> Self {
        Self::Tag(TagRepo { tag: tag.into() })
    }

    pub fn branch(branch: impl Into<String>) -> Self {
        Self::Branch(BranchRepo {
            branch: branch.into(),
        })
    }

    pub fn path(path: impl Into<String>) -> Self {
        Self::Path(PathRepo { path: path.into() })
    }

    pub fn value(&self) -> &str {
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
