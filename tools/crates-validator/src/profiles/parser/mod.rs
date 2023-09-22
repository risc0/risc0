use std::fmt::Display;

use anyhow::Result;

use super::Profile;
use super::ProfileSettings;

mod batch;
mod crates;
mod utils;

pub fn get_profiles(path: impl AsRef<str> + Display) -> Result<Vec<Profile>> {
    // Read the configuration file containing the profiles
    let config = utils::read_profile(path)?;

    // Parse crate profiles defined in batches
    let batches = serde_yaml::from_value::<batch::Batches>(config.clone())?;
    let batch_profiles: Vec<Profile> = batches.into();

    // Parse crate profiles defined individually
    let individual = serde_yaml::from_value::<crates::Crates>(config)?;
    let individual_profiles: Vec<Profile> = individual.into();

    // Merge the two sets of profiles
    batch_profiles.merge(individual_profiles)
}

#[cfg(test)]
mod tests {
    use super::*;
    use rstest::*;
    use semver::Version;

    use crate::profiles::PATH_YAML_CONFIG;

    #[test]
    fn can_parse_yaml() {
        get_profiles(PATH_YAML_CONFIG).unwrap();
    }
}
