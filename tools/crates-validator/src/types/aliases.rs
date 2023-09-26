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
