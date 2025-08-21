// Copyright 2025 RISC Zero, Inc.
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

use serde_valid::{Validate, validation::Errors as ValidationErrors};
use std::collections::{BTreeMap, BTreeSet};

use super::{
    profile::Profile,
    traits::{Exclude, Group, IsValid, Merge, Reduce},
};

pub type Profiles = BTreeSet<Profile>;
pub type CrateName = String;
pub type CrateNames = Vec<CrateName>;
pub type GroupedProfiles = BTreeMap<String, Profiles>;

impl Exclude for Profiles {
    fn exclude(self, other: Self) -> Self {
        self.into_iter()
            .filter(|p| !other.iter().any(|o| o.name() == p.name()))
            .collect()
    }
}

impl IsValid for Profiles {
    fn is_valid(&self) -> Result<(), ValidationErrors> {
        self.iter().try_for_each(|p| p.validate())
    }
}

impl Merge for Profiles {
    fn merge(self, other: Self) -> Self {
        match (self.is_empty(), other.is_empty()) {
            (true, true) => Profiles::new(),
            (false, true) => self.reduce(),
            (true, false) => other.reduce(),
            (false, false) => self.into_iter().chain(other).collect::<Self>().reduce(),
        }
    }
}

impl Reduce for Profiles {
    fn reduce(self) -> Self {
        self.into_iter()
            .chain::<Self>(Default::default())
            .group()
            .into_values()
            .map(|profiles| {
                profiles
                    .into_iter()
                    .reduce(|acc, p| acc.merge(p))
                    .expect("Should never be empty")
            })
            .collect()
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use rstest::*;

    fn pn() -> Profiles {
        Profiles::new()
    }

    fn p(name: &[&str]) -> Profiles {
        name.iter()
            .map(|n| Profile::try_from(n.to_string()).unwrap())
            .collect()
    }

    #[rstest]
    #[case::merge_empty(pn(), pn(), pn())]
    #[case::merge_empty_left(pn(), p(&["foo"]), p(&["foo"]))]
    #[case::merge_empty_right(p(&["foo"]), pn(), p(&["foo"]))]
    #[case::merge_same_crates(p(&["foo"]), p(&["foo"]), p(&["foo"]))]
    #[case::merge_different_crates(p(&["foo"]), p(&["bar"]), p(&["foo", "bar"]))]
    fn test_merge(#[case] profiles: Profiles, #[case] other: Profiles, #[case] expected: Profiles) {
        assert_eq!(profiles.merge(other), expected);
    }
}
