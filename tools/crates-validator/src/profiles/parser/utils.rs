use std::fmt::Display;
use std::{collections::HashMap};

use anyhow::{Context, Result};
use semver::Version;
use serde_yaml::{Mapping, Value};
use tracing::warn;

use super::batch;
use super::Profile;
use super::Combine;
use super::RiscZeroRepo;

pub(crate) fn read_profile(path: impl AsRef<str> + Display) -> Result<Value> {
    let content = std::fs::read_to_string(path.as_ref())
        .with_context(|| format!("Failed to read profile file: {path}",))?;
    serde_yaml::from_str(&content)
        .with_context(|| format!("Failed to parse yaml with content:\n{content}",))
}

pub(crate) fn parse_profiles(raw: Value) -> Result<Vec<Profile>> {
    let mut profiles: HashMap<String, Profile> = HashMap::new();
    if let Some(Value::Sequence(batches)) = raw.get("batch") {
        for batch in batches {
            let mapping = batch.as_mapping().unwrap();
            let parsed = batch::parse_batch_item(mapping)?;
            for (name, profile) in parsed {
                match profiles.get_mut(&name) {
                    Some(existing) => existing.combine(profile)?,
                    None => {
                        profiles.insert(name, profile);
                    }
                }
            }
        }
    }
    Ok(profiles.into_values().collect())
}

pub(crate) fn add_profile_settings(item: &Mapping, profile: &mut Profile) -> Result<()> {
    add_custom_main(item, profile);
    add_fast_mode(item, profile);
    add_import_str(item, profile);
    add_inject_cc_flags(item, profile);
    add_patch(item, profile);
    add_risc_zero_repository(item, profile)?;
    add_run_prover(item, profile);
    add_should_fail(item, profile);
    add_std(item, profile);
    add_versions(item, profile)?;
    Ok(())
}

fn add_versions(item: &Mapping, profile: &mut Profile) -> Result<()> {
    if let Some(Value::Sequence(versions)) = item.get("versions") {
        for v in versions {
            if let Value::String(version) = v {
                let version = Version::parse(version)
                    .with_context(|| format!("Invalid version: {version}",))?;
                match &mut profile.settings.versions {
                    Some(v) => {
                        if !v.contains(&version) {
                            v.push(version);
                        }
                    }
                    None => {
                        profile.settings.versions = Some(vec![version]);
                    }
                }
            }
        }
    }
    Ok(())
}

fn add_patch(item: &Mapping, profile: &mut Profile) {
    if let Some(Value::String(patch)) = item.get("patch") {
        profile.settings.patch = Some(patch.to_string());
    }
}

fn add_import_str(item: &Mapping, profile: &mut Profile) {
    if let Some(Value::String(import_str)) = item.get("import_str") {
        profile.settings.import_str = Some(import_str.to_string());
    }
}

fn add_std(item: &Mapping, profile: &mut Profile) {
    if let Some(Value::Bool(std)) = item.get("std") {
        profile.settings.std = *std;
    }
}

fn add_fast_mode(item: &Mapping, profile: &mut Profile) {
    if let Some(Value::Bool(fast_mode)) = item.get("fast_mode") {
        profile.settings.fast_mode = *fast_mode;
    }
}

fn add_custom_main(item: &Mapping, profile: &mut Profile) {
    if let Some(Value::String(custom_main)) = item.get("custom_main") {
        profile.settings.custom_main = Some(custom_main.to_string());
    }
}

fn add_run_prover(item: &Mapping, profile: &mut Profile) {
    if let Some(Value::Bool(run_prover)) = item.get("run_prover") {
        profile.settings.run_prover = *run_prover;
    }
}

fn add_should_fail(item: &Mapping, profile: &mut Profile) {
    if let Some(Value::Bool(should_fail)) = item.get("should_fail") {
        profile.settings.should_fail = *should_fail;
    }
}

fn add_inject_cc_flags(item: &Mapping, profile: &mut Profile) {
    if let Some(Value::Bool(inject_cc_flags)) = item.get("inject_cc_flags") {
        profile.settings.inject_cc_flags = *inject_cc_flags;
    }
}

fn add_risc_zero_repository(item: &Mapping, profile: &mut Profile) -> Result<()> {
    match (item.get("risc0_gh_branch"), item.get("risc0_path")) {
        (Some(Value::String(git)), None) => {
            profile.settings.risc_zero_repository = Some(RiscZeroRepo::Github(git.to_string()))
        }
        (None, Some(Value::String(path))) => {
            profile.settings.risc_zero_repository = Some(RiscZeroRepo::Local(path.to_string()))
        }
        (Some(Value::String(_)), Some(Value::String(r))) => {
            warn!("Cannot specify both 'risc0_gh_branch' and 'risc0_path'");
            warn!("Using 'risc0_path' as default");
            profile.settings.risc_zero_repository = Some(RiscZeroRepo::Local(r.to_string()))
        }
        (_, _) => {
            warn!("No 'risc0_gh_branch' or 'risc0_path' specified");
            warn!("Using default 'risc0_gh_branch'");
            profile.settings.risc_zero_repository = Some(RiscZeroRepo::default());
        }
    }
    Ok(())
}

