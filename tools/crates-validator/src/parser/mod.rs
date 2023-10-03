use std::fmt::Display;

use crate::{Exclude, Merge, ProfileConfig, Profiles, Repo};
use anyhow::Result;

mod batch;
mod constants;
mod individual;
mod skip_crates;
mod utils;

#[cfg(test)]
mod test_helpers;

#[derive(Debug, Default, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
pub struct Parser {
    #[serde(flatten)]
    batch: batch::Batches,
    #[serde(flatten)]
    individual: individual::Individual,
    #[serde(flatten)]
    skip_crates: skip_crates::SkipCrates,
    repo: Repo,
}

impl Parser {
    #[tracing::instrument(level = "trace", skip(path))]
    pub fn new(path: impl AsRef<str> + Display) -> Result<Self> {
        let config = utils::read_profile(path)?;
        Ok(serde_yaml::from_str::<Parser>(&config)?)
    }

    pub fn profiles(&self) -> Result<Profiles> {
        Profiles::try_from(self.batch.clone())?
            .merge(self.individual.clone().into())
            // .exclude(self.skip_crates.clone().try_into()?)
            .into_iter()
            .map(Ok)
            .collect::<Result<Profiles>>()
    }

    pub fn skip_crates(&self) -> Result<Profiles> {
        self.skip_crates.clone().try_into()
    }

    pub fn repo(&self) -> &Repo {
        &self.repo
    }
}

impl TryFrom<Parser> for ProfileConfig {
    type Error = anyhow::Error;
    fn try_from(value: Parser) -> anyhow::Result<Self> {
        Ok(Self {
            profiles: value.profiles()?,
            repo: value.clone().repo,
            skip_crates: value.skip_crates()?,
        })
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    use constants::PATH_YAML_CONFIG;

    #[test]
    fn can_parse_yaml() {
        let parser = Parser::new(PATH_YAML_CONFIG).unwrap();
        let profiles = parser.profiles().unwrap();
        assert!(!profiles.is_empty())
    }
}
