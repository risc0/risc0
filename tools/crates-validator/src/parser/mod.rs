use std::fmt::Display;

use crate::{Exclude, Versions, Merge, Profiles, Repo};
use anyhow::Result;

mod batch;
mod constants;
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
    #[serde(flatten)]
    pub repo: Repo,
}

impl Parser {
    pub fn parse(path: impl AsRef<str> + Display) -> Result<Profiles> {
        let config = utils::read_profile(path)?;
        let parser = serde_yaml::from_str::<Parser>(&config)?;
        let profiles = Profiles::try_from(parser.batch)?
            .merge(parser.individual.into())
            .exclude(parser.skip_crates.try_into()?);
        Ok(profiles)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    use constants::PATH_YAML_CONFIG;

    #[test]
    fn can_parse_yaml() {
        let profiles = Parser::parse(PATH_YAML_CONFIG).unwrap();
        assert!(!profiles.is_empty())
    }
}
