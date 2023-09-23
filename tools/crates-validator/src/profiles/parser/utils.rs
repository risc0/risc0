use std::{fmt::Display, fs};

use anyhow::{Context, Result};

pub(crate) fn read_profile(path: impl AsRef<str> + Display) -> Result<String> {
    fs::read_to_string(path.as_ref())
        .with_context(|| format!("Failed to read profile file: {path}",))
}
