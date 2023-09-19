use anyhow::{Context, Result, ensure};
use serde_valid::Validate;
use std::{collections::HashSet, fmt::Display};

#[derive(
    Debug, Clone, PartialEq, Eq, serde::Serialize, serde::Deserialize, serde_valid::Validate,
)]
struct ParseCrates {
    #[serde(default)]
    #[validate(min_items = 1)]
    pub crates: Vec<String>,
}

pub fn read_crates_to_skip(path: impl AsRef<str> + Display) -> Result<HashSet<String>> {
    let content = read_toml(path)?;
    parse_crates_to_skip(content)
}

pub fn parse_crates_to_skip(content: impl AsRef<str> + Display) -> Result<HashSet<String>> {
    let crates_vec = parse_crates(content)?;
    let crates_set = crates_vec.crates.into_iter().collect();
    Ok(crates_set)
}

fn parse_crates(content: impl AsRef<str> + Display) -> Result<ParseCrates> {
    let crates = toml::from_str::<ParseCrates>(content.as_ref())
        .with_context(|| format!("Failed to parse toml with content:\n{content}",))?;
    dbg!(content.as_ref(), &crates.validate(), crates.crates.len());
    crates.validate().context("Invalid configuration file")?;
    Ok(crates)
}

fn read_toml(path: impl AsRef<str> + Display) -> Result<String> {
    let content = std::fs::read_to_string(path.as_ref())
        .with_context(|| format!("Failed to read 'SKIP_CRATES' file at path: {path}",))?;
    ensure!(!content.is_empty(), "File is empty");
    Ok(content)
}

#[cfg(test)]
mod tests {
    use super::*;
    use rstest::*;

    #[test]
    fn can_read_toml_file() {
        let result = read_crates_to_skip("./profiles/SKIP_CRATES.toml").unwrap();
        assert!(!result.is_empty());
    }

    #[rstest]
    #[case::key_absent("")]
    #[case::key_null("crates = ")]
    #[case::empty_string("crates = ''")]
    #[case::empty_vector("crates = []")]
    #[should_panic]
    fn fail_to_parse_crates(#[case] content: &str) {
        parse_crates_to_skip(content).unwrap();
    }

    #[rstest]
    #[case::vector_with_crate("crates = ['crate1']", vec!["crate1"])]
    #[case::vector_with_crate("crates = ['crate1', 'crate1']", vec!["crate1"])]
    #[case::vector_with_crate("crates = ['crate1', 'crate2']", vec!["crate1", "crate2"])]
    fn can_parse_crates(#[case] content: &str, #[case] expected: Vec<&str>) {
        let result = parse_crates_to_skip(content).unwrap();
        assert_eq!(result.len(), expected.len());
        for crate_name in expected {
            assert!(result.contains(crate_name));
        }
    }
}
