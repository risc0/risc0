use std::fmt::Display;

use super::types::*;

use anyhow::{ensure, Result};

mod batch;
mod individual;
mod skip_crates;
mod utils;

#[cfg(test)]
mod test_helpers;

#[derive(Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
pub struct Parser {
    #[serde(flatten)]
    batch: batch::Batches,
    #[serde(flatten)]
    individual: individual::Individual,
    #[serde(flatten)]
    skip_crates: skip_crates::SkipCrates,
}

impl Parser {
    pub fn parse(path: impl AsRef<str> + Display) -> Result<Profiles> {
        let config = utils::read_profile(path)?;
        let parser = serde_yaml::from_str::<Parser>(&config)?;
        let profiles = Profiles::from(parser.batch)
            .merge(parser.individual.into())
            .exclude(parser.skip_crates.into());
        ensure!(
            profiles.is_valid().is_ok(),
            "Invalid profiles: {:?}",
            profiles
        );
        Ok(profiles)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    use crate::profiles::PATH_YAML_CONFIG;

    #[test]
    fn can_parse_yaml() {
        let profiles = Parser::parse(PATH_YAML_CONFIG).unwrap();
        assert!(!profiles.is_empty())
    }
}
