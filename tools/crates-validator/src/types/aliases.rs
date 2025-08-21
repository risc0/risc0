// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

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
