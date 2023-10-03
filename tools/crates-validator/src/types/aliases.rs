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

use super::*;

pub type Profiles = Vec<Profile>;
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
            (true, false) => self,
            (false, true) => other,
            (false, false) => self
                .into_iter()
                .chain(other)
                .group()
                .into_values()
                .map(|profiles| {
                    profiles
                        .into_iter()
                        .reduce(|acc, p| acc.merge(p))
                        .expect("Should never be empty")
                })
                .collect(),
        }
    }
}
