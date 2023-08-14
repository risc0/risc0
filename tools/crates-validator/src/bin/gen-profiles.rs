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

use std::{
    cell::RefCell,
    collections::{btree_map::Entry, BTreeMap},
    fs::File,
    io::{Seek, Write},
    path::{Path, PathBuf},
};

use anyhow::{bail, Context, Result};
use clap::Parser;
use indicatif::{ProgressBar, ProgressStyle};
use risc0_crates_validator::{profiles, CrateProfile, ProfileConfig};
use tokio_stream::StreamExt;
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

#[tracing::instrument]
async fn download_database() -> Result<PathBuf> {
    let url = "https://static.crates.io/db-dump.tar.gz";
    debug!("Downloading from {}", url);

    debug!("Creating file...");
    let tar_file_path = Path::new("/tmp/db-dump.tar.gz");
    let (mut downloaded, mut file) = if tar_file_path.exists() {
        debug!("File already exists, resuming...");
        let mut file = std::fs::OpenOptions::new()
            .read(true)
            .append(true)
            .open(tar_file_path)
            .context("Failed to open file")?;

        let file_size = std::fs::metadata(tar_file_path)
            .context("Failed to get metadata for file '{tar_file_path}'")?
            .len();
        file.seek(std::io::SeekFrom::Start(file_size))
            .context("Failed to seek file.")?;
        debug!("Resuming from {} bytes", file_size);
        (file_size, file)
    } else {
        debug!("Creating new file...");
        let file =
            File::create(tar_file_path).context("Failed to create file '{tar_file_path}'")?;
        (0, file)
    };

    debug!("Starting download...");
    let resp = reqwest::Client::new()
        .get(url)
        .send()
        .await
        .context("Failed to GET from '{url}'")?;
    let total_size = resp
        .content_length()
        .context("Failed to get content length from '{url}'")?;
    let pb = ProgressBar::new(total_size);
    pb.set_style(ProgressStyle::default_bar()
    .template("{msg}\n{spinner:.green} [{elapsed_precise}] [{wide_bar:.white/blue}] {bytes}/{total_bytes} ({bytes_per_sec}, {eta})")
    .progress_chars("█  "));
    pb.set_message(&format!("Downloading {url}"));

    let mut stream = resp.bytes_stream();
    while let Some(item) = stream.next().await {
        let chunk = item.context("Error while downloading file")?;
        file.write_all(&chunk)
            .context("Error while writing to file")?;
        file.flush().context("Error while flushing file")?;
        let new = std::cmp::min(downloaded + (chunk.len() as u64), total_size);
        downloaded = new;
        pb.set_position(new);
    }
    pb.finish_with_message(&format!(
        "Downloaded {url} to {path}",
        url = url,
        path = tar_file_path
            .to_str()
            .context("Failed to convert path to string")?
    ));

    Ok(tar_file_path.to_path_buf())
}

#[tokio::main]
async fn main() -> Result<()> {
    tracing_subscriber::fmt()
        .with_env_filter(EnvFilter::from_default_env())
        .init();

    let args = Args::parse();

    if let (None, None) = (&args.risc0_path, &args.risc0_gh_branch) {
        bail!("No risc0_path or risc0_gh_branch provided, please provide one in order to generate profile.");
    }

    let db_path = if let Some(path) = args.db_path {
        path
    } else {
        download_database().await?
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
