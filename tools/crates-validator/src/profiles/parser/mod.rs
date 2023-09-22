use std::fmt::Display;

use anyhow::Result;

use super::Profile;
use super::ProfileSettings;

mod batch;
mod profiles;
mod utils;

pub fn get_profiles(path: impl AsRef<str> + Display) -> Result<Vec<Profile>> {
    // Read the whole configuration file
    let content = utils::read_profile(path)?;

    todo!()
    // Parse batch configurations
    // let batch_profiles = batch::parse(&content)?;

    // Parse individual crate configurations
    // let individual_profiles = profiles::parse(&content)?;

    // Combine the two, overwriting batch profiles with individual profiles if
    // crates are defined in both
    // let profiles = utils::combine_profiles(batch_profiles, individual_profiles)?;

    // Ok(profiles)
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
