use crate::profiles::Profile;

#[derive(Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
pub(crate) struct Crates {
    crates: Vec<Profile>,
}

impl From<Crates> for Vec<Profile> {
    fn from(value: Crates) -> Self {
        value.crates
    }
}

#[cfg(test)]
mod tests {
    use crate::profiles::{parser::utils, PATH_YAML_CONFIG};

    use super::*;

    #[test]
    fn can_read_config() {
        let config = utils::read_profile(PATH_YAML_CONFIG).unwrap();
        let crates = serde_yaml::from_value::<Crates>(config).unwrap();
        let profiles: Vec<Profile> = crates.into();
        assert!(!profiles.is_empty());
    }
}
