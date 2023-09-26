use super::*;



#[derive(
    Debug, Clone, PartialEq, Eq, Hash, serde::Serialize, serde::Deserialize, serde_valid::Validate,
)]
pub struct Profile {
    #[validate(min_length = 1)]
    pub name: CrateName,
    #[serde(flatten)]
    pub settings: ProfileSettings,
}

impl TryFrom<String> for Profile {
    type Error = anyhow::Error;

    fn try_from(name: String) -> Result<Self, Self::Error> {
        let profile = Self {
            name,
            settings: ProfileSettings::default(),
        };
        ensure!(profile.validate().is_ok(), "Invalid profile: {:?}", profile);
        ensure!(
            profile.settings.validate().is_ok(),
            "Invalid profile settings: {:?}",
            profile.settings
        );
        Ok(profile)
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
