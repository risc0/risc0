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
    collections::{btree_map::Entry, BTreeMap, HashMap, HashSet},
    fs::File,
    io::Write,
    path::{Path, PathBuf},
};

use anyhow::{bail, Context, Result};
use clap::Parser;
use db_dump::{
    categories::{CategoryId, Row as CategoryRow},
    crates::{CrateId, Row as CrateRow},
    crates_categories::Row as CratesCategoriesRow,
    versions::Row as VersionRow,
};
use indicatif::{ProgressBar, ProgressStyle};
use risc0_crates_validator::{profiles, selected_crates, CrateProfile, ProfileConfig};
use tokio_stream::StreamExt;
use tracing::{debug, info, warn};
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
    #[arg(short = 'b', long, conflicts_with = "risc0_path")]
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

    /// Path for the JSON specifying crates to be added to the profile.
    ///
    /// The expected format is a JSON as follows:
    ///    {
    ///       "<identifier>": [
    ///           "<crate_name_1>",
    ///           "<crate_name_2>",
    ///           ...
    ///       ],
    ///       ...
    ///    }
    #[arg(short, long, conflicts_with = "name")]
    selected_crates: Option<Vec<String>>,

    /// Add selected categories to the profile
    #[arg(
        short = 'C',
        long,
        conflicts_with = "name",
        value_parser,
        value_delimiter = ' '
    )]
    categories: Option<Vec<String>>,

    /// Number of crates per category to add to the profile
    ///
    /// This will add the top N crates per category to the profile, sorted by
    /// downloads.
    #[arg(short = 'L', long, default_value = None, requires = "categories")]
    category_count_limit: Option<usize>,
}

#[tracing::instrument]
async fn download_database() -> Result<PathBuf> {
    let url = "https://static.crates.io/db-dump.tar.gz";
    let path = "/tmp/db-dump.tar.gz";
    debug!("Downloading from {}", url);

    let tar_file_path = Path::new(path);
    if tar_file_path.exists() {
        debug!("File already exists at '{path}', skipping...");
        return Ok(tar_file_path.to_path_buf());
    }
    let mut file =
        File::create(tar_file_path).context("Failed to create file '{tar_file_path}'")?;
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
    let mut downloaded = 0;
    while let Some(item) = stream.next().await {
        let chunk = item.context("Error while downloading file")?;
        file.write_all(&chunk)
            .context("Error while writing to file")?;
        file.flush().context("Error while flushing file")?;
        let new = std::cmp::min(downloaded + (chunk.len() as u64), total_size);
        downloaded = new;
        pb.set_position(new);
    }
    pb.finish_and_clear();
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
    let mut categories = HashMap::new();
    let mut crates_categories = HashMap::new();

    debug!("Loading...");
    let crate_name = &args.name;
    if let Some(name) = crate_name {
        info!("Selecting only {name}");
    }

    let handle_categories = |row: CategoryRow| {
        categories.insert(row.id, row.slug.to_string());
    };

    let handle_crates = |row: CrateRow| {
        if let Some(crate_name) = &crate_name {
            if row.name != *crate_name {
                return;
            }
        }
        crates.push(row);
    };

    let handle_versions = |row: VersionRow| match most_recent.entry(row.crate_id) {
        Entry::Vacant(entry) => {
            entry.insert(row);
        }
        Entry::Occupied(mut entry) => {
            // find newest, non-pre-release version:
            if row.created_at > entry.get().created_at && row.num.pre.is_empty() {
                entry.insert(row);
            }
        }
    };

    let handle_crates_categories = |row: CratesCategoriesRow| {
        crates_categories.insert(row.crate_id, row.category_id);
    };

    db_dump::Loader::new()
        .crates_categories(handle_crates_categories)
        .categories(handle_categories)
        .crates(handle_crates)
        .versions(handle_versions)
        .load(db_path)
        .context("Failed to load database")?;

    debug!("Sorting...");
    crates.sort_by(|r1, r2| r2.downloads.cmp(&r1.downloads));

    let mut selected_crates = crates
        .iter()
        .take(args.crate_count)
        .map(|c| c.clone())
        .collect::<Vec<_>>();
    if let Some(json_files) = args.selected_crates {
        info!("Adding selected crates to profile");
        for file in json_files {
            let json = selected_crates::read_crates_selection(file)
                .context("Failed to read crates selection in file '{file}'")?;
            let handpicked = selected_crates::parse_crates_json(json)
                .context("Failed to parse crates selection JSON in file '{file}'")?;
            crates
                .iter()
                .filter(|c| handpicked.contains(&c.name))
                .for_each(|c| {
                    selected_crates.push(c.clone());
                });
        }
    };
    if args.categories.is_some() {
        info!("Adding selected categories to profile");
        let mut crates_from_categories =
            add_categories(&crates, &categories, &args.categories, &crates_categories);
        crates_from_categories.sort_by(|r1, r2| r2.downloads.cmp(&r1.downloads));
        if let Some(limit) = args.category_count_limit {
            selected_crates.extend(crates_from_categories.into_iter().take(limit));
        } else {
            selected_crates.extend(crates_from_categories);
        }
    };

    // Ensure that we don't have any duplicates
    let selected_crates = selected_crates
        .into_iter()
        .collect::<HashSet<_>>()
        .into_iter()
        .collect::<Vec<_>>();

    for cur_crate in &selected_crates {
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

    debug!(
        "Total of {} crates included in the profile.",
        selected_crates.len()
    );
    info!("Wrote profile to: {}", args.output_path.to_string_lossy());

    Ok(())
}

fn filter_categories(
    categories: &HashMap<CategoryId, String>,
    desired_categories: &Option<Vec<String>>,
) -> HashMap<CategoryId, String> {
    let filter = match desired_categories {
        None => return HashMap::new(),
        Some(c) => c.iter().map(String::from).collect::<HashSet<String>>(),
    };

    let mut show_existent_categories = false;
    let existent_categories = categories
        .values()
        .map(|v| v.clone())
        .collect::<HashSet<_>>();
    let included_categories = filter
        .intersection(&existent_categories)
        .collect::<HashSet<_>>();
    filter.difference(&existent_categories).for_each(|c| {
        show_existent_categories = true;
        warn!("Category '{}' does not exist, ignoring...", c);
    });
    if show_existent_categories {
        let mut c = existent_categories.iter().collect::<Vec<_>>();
        c.sort();
        warn!("Existent categories: {c:?}");
    }
    let mut filtered = HashMap::new();
    categories.iter().for_each(|(k, v)| {
        if included_categories.contains(v) {
            filtered.insert(*k, v.clone());
        }
    });

    filtered
}

fn add_categories(
    crates: &Vec<CrateRow>,
    categories: &HashMap<CategoryId, String>,
    filter: &Option<Vec<String>>,
    crates_categories: &HashMap<CrateId, CategoryId>,
) -> Vec<CrateRow> {
    let filtered_categories = filter_categories(categories, filter);
    crates
        .iter()
        .filter(|c| match crates_categories.get(&c.id) {
            Some(category_id) => filtered_categories.contains_key(category_id),
            None => false,
        })
        .map(|c| c.clone())
        .collect()
}

#[cfg(test)]
mod tests {
    use rstest::*;

    use super::*;

    type CategoryMap = HashMap<CategoryId, String>;

    #[fixture]
    fn categories(#[default(vec!["a", "b", "c"])] names: Vec<impl ToString>) -> CategoryMap {
        let mut categories = HashMap::new();
        names.into_iter().enumerate().for_each(|(i, name)| {
            categories.insert(CategoryId(i as u32), name.to_string());
        });
        categories
    }

    #[rstest]
    fn filter_categories_absent_filter(categories: CategoryMap) {
        let filter = None;
        let expected = HashMap::new();

        assert_eq!(expected, filter_categories(&categories, &filter));
    }

    #[rstest]
    fn filter_categories_empty_filter(categories: CategoryMap) {
        let filter = vec![];
        let expected = HashMap::new();

        assert_eq!(expected, filter_categories(&categories, &Some(filter)));
    }

    #[rstest]
    fn filter_categories_given_filter(categories: CategoryMap) {
        let filter = vec!["a".to_string()];
        let mut expected = HashMap::new();
        expected.insert(CategoryId(0), "a".into());

        assert_eq!(expected, filter_categories(&categories, &Some(filter)));
    }
}
