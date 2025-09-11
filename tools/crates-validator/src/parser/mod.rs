// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::fmt::Display;

use anyhow::Result;

use crate::{
    ProfileConfig,
    types::{
        aliases::Profiles,
        traits::{Merge, Reduce},
    },
};

mod batch;
mod individual;
mod utils;

#[cfg(test)]
mod test_helpers;

#[derive(Debug, Default, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize)]
pub struct Parser {
    #[serde(flatten)]
    batch: batch::Batches,
    #[serde(flatten)]
    individual: individual::Individual,
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
            .into_iter()
            .map(Ok)
            .collect::<Result<Profiles>>()
            .map(|p: Profiles| p.reduce())
    }
}

impl TryFrom<Parser> for ProfileConfig {
    type Error = anyhow::Error;
    fn try_from(value: Parser) -> anyhow::Result<Self> {
        Ok(Self {
            profiles: value.profiles()?,
        })
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::constants::PATH_YAML_CONFIG;

    #[test]
    fn can_parse_yaml() {
        let parser = Parser::new(PATH_YAML_CONFIG).unwrap();
        let profiles = parser.profiles().unwrap();
        assert!(!profiles.is_empty())
    }
}
