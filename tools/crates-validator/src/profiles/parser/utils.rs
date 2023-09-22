use std::{fmt::Display, fs};

use anyhow::{Context, Result};
use serde_yaml::Value;

pub(crate) fn read_profile(path: impl AsRef<str> + Display) -> Result<Value> {
    let content = fs::read_to_string(path.as_ref())
        .with_context(|| format!("Failed to read profile file: {path}",))?;
    serde_yaml::from_str(&content)
        .with_context(|| format!("Failed to parse yaml with content:\n{content}",))
}
