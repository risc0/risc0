use std::{collections::HashMap};

use anyhow::{anyhow, bail, Context, Result};
use serde_yaml::{Mapping, Value};
use serde_valid::Validate;

use super::utils;
use super::Profile;
use super::ProfileSettings;

pub(crate) fn parse_batch_item(item: &Mapping) -> Result<HashMap<String, Profile>> {
    let mut map = HashMap::new();
    let (_identifier, crates) = match (item.get("name"), item.get("crates")) {
        (Some(Value::String(name)), Some(Value::Sequence(crates))) => (name, crates),
        (None, _) => bail!("Missing batch identifier: Add 'name' field"),
        (_, None) => bail!("Missing 'crates' field"),
        (_, _) => bail!(
            "Does not contain 'name' and 'crates' fields as `string` and `array` as expected."
        ),
    };
    for c in crates {
        let name = c
            .as_str()
            .ok_or_else(|| anyhow!("Invalid 'crates' field for crate: {c:?}"))?
            .to_string();
        let mut profile = Profile {
            name: name.clone(),
            settings: ProfileSettings::default(),
        };
        utils::add_profile_settings(item, &mut profile)?;
        profile.validate().context("Invalid Profile file")?;
        profile
            .settings
            .validate()
            .context("Invalid Profile file")?;
        map.insert(name, profile);
    }
    Ok(map)
}

