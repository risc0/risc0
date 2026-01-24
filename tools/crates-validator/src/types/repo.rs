// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use crate::constants::{RISC_ZERO_REPO_GIT, RISC_ZERO_REPO_PATH_BUILD, RISC_ZERO_REPO_PATH_ZKVM};

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

/// Returns the Cargo.toml string entry on how to import the RISC Zero
/// repository.
pub trait RepoCargoString {
    /// Expects a `sub_directory` string to be passed in.
    ///
    /// Ex:
    /// ```
    /// # use risc0_crates_validator::types::repo::{Repo, RepoCargoString, TagRepo, BranchRepo, PathRepo, Value};
    /// const R0_REPO: &str = "https://github.com/risc0/risc0.git";
    /// const R0_PATH: &str = "risc0/build";
    ///
    /// let tag = Repo::tag("v0.1.0");
    /// let branch = Repo::branch("main");
    /// let path = Repo::path("/home/user/risc0");
    ///
    /// assert_eq!(
    ///     tag.cargo_string(R0_REPO),
    ///     format!("git = \"{R0_REPO}\" tag = \"{}\"", tag.value())
    /// );
    ///
    /// assert_eq!(
    ///     branch.cargo_string(R0_REPO),
    ///     format!("git = \"{R0_REPO}\" branch = \"{}\"", branch.value())
    /// );
    ///
    /// assert_eq!(
    ///     path.cargo_string(R0_PATH),
    ///     format!("path = \"{}/{R0_PATH}\"", path.value())
    /// );
    fn cargo_string(&self, sub_directory: impl AsRef<str>) -> String;
    /// Same as [RepoCargoString::cargo_string] but uses the defaults for the [Repo] variants.
    fn default_cargo_build(&self) -> String;
    /// Same as [RepoCargoString::cargo_string] but uses the defaults for the [Repo] variants.
    fn default_cargo_zkvm(&self) -> String;
}

impl RepoCargoString for Repo {
    fn cargo_string(&self, sub_directory: impl AsRef<str>) -> String {
        match self {
            Self::Tag(tag) => tag.cargo_string(sub_directory),
            Self::Branch(branch) => branch.cargo_string(sub_directory),
            Self::Path(path) => path.cargo_string(sub_directory),
        }
    }

    fn default_cargo_build(&self) -> String {
        match self {
            Self::Tag(tag) => tag.default_cargo_build(),
            Self::Branch(branch) => branch.default_cargo_build(),
            Self::Path(path) => path.default_cargo_build(),
        }
    }

    fn default_cargo_zkvm(&self) -> String {
        match self {
            Self::Tag(tag) => tag.default_cargo_zkvm(),
            Self::Branch(branch) => branch.default_cargo_zkvm(),
            Self::Path(path) => path.default_cargo_zkvm(),
        }
    }
}

impl RepoCargoString for TagRepo {
    fn cargo_string(&self, sub_directory: impl AsRef<str>) -> String {
        format!(
            "git = \"{}\" tag = \"{}\"",
            sub_directory.as_ref(),
            self.tag
        )
    }

    fn default_cargo_build(&self) -> String {
        format!("git = \"{}\" tag = \"{}\"", RISC_ZERO_REPO_GIT, self.tag)
    }

    fn default_cargo_zkvm(&self) -> String {
        self.default_cargo_build()
    }
}

impl RepoCargoString for BranchRepo {
    fn cargo_string(&self, sub_directory: impl AsRef<str>) -> String {
        format!(
            "git = \"{}\" branch = \"{}\"",
            sub_directory.as_ref(),
            self.branch
        )
    }

    fn default_cargo_build(&self) -> String {
        format!(
            "git = \"{}\" branch = \"{}\"",
            RISC_ZERO_REPO_GIT, self.branch
        )
    }

    fn default_cargo_zkvm(&self) -> String {
        self.default_cargo_build()
    }
}

impl RepoCargoString for PathRepo {
    fn cargo_string(&self, sub_directory: impl AsRef<str>) -> String {
        format!("path = \"{}/{}\"", self.path, sub_directory.as_ref())
    }

    fn default_cargo_build(&self) -> String {
        format!("path = \"{}/{}\"", self.path, RISC_ZERO_REPO_PATH_BUILD)
    }

    fn default_cargo_zkvm(&self) -> String {
        format!("path = \"{}/{}\"", self.path, RISC_ZERO_REPO_PATH_ZKVM)
    }
}

pub trait Value {
    fn value(&self) -> &str;
}

impl Value for TagRepo {
    fn value(&self) -> &str {
        self.tag.as_ref()
    }
}

impl Value for BranchRepo {
    fn value(&self) -> &str {
        self.branch.as_ref()
    }
}

impl Value for PathRepo {
    fn value(&self) -> &str {
        self.path.as_ref()
    }
}

impl Value for Repo {
    fn value(&self) -> &str {
        match self {
            Self::Tag(tag) => tag.value(),
            Self::Branch(branch) => branch.value(),
            Self::Path(path) => path.value(),
        }
    }
}
