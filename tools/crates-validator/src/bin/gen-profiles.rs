// Copyright 2023 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use std::cell::RefCell;
use std::collections::{btree_map::Entry, BTreeMap};
use std::fs::File;
use std::io::{Cursor, Write};
use std::path::{Path, PathBuf};

use anyhow::{Context, Result};
use clap::Parser;
use risc0_crates_validator::{profiles, CrateProfile, ProfileConfig};
use tracing::{debug, info};
use tracing_subscriber::EnvFilter;

#[derive(Parser)]
#[command(author, version, about, long_about = None)]
struct Args {
    /// Path to existing database on disk
    ///
    /// If not supplied, will re-download to /tmp
    #[arg(short, long)]
    db_path: Option<PathBuf>,

    /// Should the profile toggle `RISC0_EXPERIMENTAL_PREFLIGHT`
    #[arg(short, long)]
    fast_mode: bool,

    /// Sets the risc0_path attribute
    #[arg(short, long)]
    risc0_path: Option<String>,

    /// Sets the risc0_gh_branch attribute
    #[arg(long, conflicts_with = "risc0_path")]
    risc0_gh_branch: Option<String>,

    /// Sets the output location of the json [ProfileConfig]
    #[arg(short, long)]
    output_path: PathBuf,

    /// Sets the number of crates, sorted by downloads to profile
    #[arg(short, long, default_value = "20")]
    crate_count: usize,

    /// Single crate mode
    ///
    /// Will only create a profile for the single crate provide
    #[arg(short, long, conflicts_with = "crate_count")]
    name: Option<String>,

    /// Disable profiles
    ///
    /// This will disable all crate-specific profile modifications
    #[arg(long)]
    no_profiles: bool,
}

fn download_database() -> Result<PathBuf> {
    let db_url = "https://static.crates.io/db-dump.tar.gz";
    debug!("Downloading from {}", db_url);

    let tar_file_path = Path::new("/tmp/db-dump.tar.gz");
    let mut tar_file = File::create(tar_file_path)?;
    let resp = reqwest::blocking::get(db_url)?;
    let mut content = Cursor::new(resp.bytes()?);
    std::io::copy(&mut content, &mut tar_file)?;
    Ok(tar_file_path.to_path_buf())
}

fn main() -> Result<()> {
    tracing_subscriber::fmt()
        .with_env_filter(EnvFilter::from_default_env())
        .init();

    let args = Args::parse();

    let db_path = if let Some(path) = args.db_path {
        path
    } else {
        download_database()?
    };

    let config = ProfileConfig {
        fast_mode: args.fast_mode,
        risc0_path: args.risc0_path,
        risc0_gh_branch: args.risc0_gh_branch,
        profiles: RefCell::new(vec![]),
    };

    // Process the db-dump...
    let mut most_recent = BTreeMap::new();
    let mut crates = Vec::new();

    debug!("Loading..");
    let crate_name = &args.name;
    if let Some(name) = crate_name {
        info!("Selecting only {name}");
    }

    db_dump::Loader::new()
        .crates(|row| {
            if let Some(crate_name) = &crate_name {
                if row.name != *crate_name {
                    return;
                }
            }
            crates.push(row);
        })
        .versions(|row| match most_recent.entry(row.crate_id) {
            Entry::Vacant(entry) => {
                entry.insert(row);
            }
            Entry::Occupied(mut entry) => {
                // find newest, non-pre-release version:
                if row.created_at > entry.get().created_at && row.num.pre.is_empty() {
                    entry.insert(row);
                }
            }
        })
        .load(db_path)
        .context("Failed to load database")?;

    debug!("Sorting...");
    crates.sort_by(|r1, r2| r2.downloads.cmp(&r1.downloads));

    for cur_crate in crates.iter().take(args.crate_count) {
        let version = &most_recent[&cur_crate.id];
        debug!("Processing: {} - {}", cur_crate.name, version.num);

        let profile = CrateProfile {
            name: cur_crate.name.clone(),
            version: Some(version.num.to_string()),
            ..Default::default()
        };

        // Optionally, apply manual profile fixes based on crate name
        let profile = if !args.no_profiles {
            profiles::lookup_crate(&cur_crate.name, profile)
        } else {
            profile
        };
        config.profiles.borrow_mut().push(profile);
    }

    let mut output = File::create(&args.output_path)?;
    output.write_all(serde_json::to_string(&config)?.as_bytes())?;

    info!("Wrote profile to: {}", args.output_path.to_string_lossy());

    Ok(())
}
