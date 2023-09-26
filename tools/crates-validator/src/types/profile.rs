use super::*;

#[derive(
    Debug, Clone, PartialEq, Eq, Hash, serde::Serialize, serde::Deserialize, serde_valid::Validate,
)]
pub struct Profile {
    #[validate(min_length = 1)]
    name: CrateName,
    #[serde(flatten)]
    pub settings: ProfileSettings,
}

impl Profile {
    pub fn new(name: CrateName, settings: ProfileSettings) -> Result<Self> {
        let profile = Self { name, settings };
        ensure!(profile.validate().is_ok(), "Invalid profile: {:?}", profile);
        Ok(profile)
    }

    pub fn name(&self) -> &str {
        self.name.as_ref()
    }

    pub fn has_same_name(&self, other: &Self) -> bool {
        self.name == other.name
    }
}

impl TryFrom<String> for Profile {
    type Error = anyhow::Error;

    fn try_from(name: String) -> Result<Self, Self::Error> {
        Profile::new(name, ProfileSettings::default())
    }
}

impl TryFrom<(String, ProfileSettings)> for Profile {
    type Error = anyhow::Error;
    fn try_from(value: (String, ProfileSettings)) -> std::result::Result<Self, Self::Error> {
        Profile::new(value.0, value.1)
    }
}

impl Merge for Profile {
    fn merge(self, other: Self) -> Self {
        assert_eq!(self.name, other.name);
        Self {
            name: self.name,
            settings: self.settings.merge(other.settings),
        }
    }
}

impl Group for Chain<IntoIter<Profile>, IntoIter<Profile>> {
    fn group(self) -> GroupedProfiles {
        self.fold(GroupedProfiles::new(), |mut acc, p| {
            acc.entry(p.name.clone()).or_default().push(p.clone());
            acc
        })
    }
}
