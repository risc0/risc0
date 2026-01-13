// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

pub mod args;

use std::{
    collections::{BTreeMap, HashMap, HashSet, btree_map::Entry},
    fs::File,
    io::Write,
    path::{Path, PathBuf},
};

use anyhow::{Context, Result};
use db_dump::{
    categories::{CategoryId, Row as CategoryRow},
    crate_downloads::Row as CrateDownloadsRow,
    crates::{CrateId, Row as CrateRow},
    crates_categories::Row as CratesCategoriesRow,
    versions::Row as VersionRow,
};
use indicatif::{ProgressBar, ProgressStyle};
use tokio_stream::StreamExt;
use tracing::{debug, info, warn};

use crate::{
    Profile, ProfileConfig, Profiles,
    parser::Parser,
    types::{
        version::{Version, Versions},
    },
};

pub use args::Args;

// Define alias for ease of use.
pub type GenProfiles = StateMachine<Initialize>;

pub struct StateMachine<S> {
    args: Args,
    state: S,
}

// States
pub struct Initialize;
pub struct ReadProfilesConfig {
    profile_config: ProfileConfig,
}
pub struct DownloadDatabase {
    profile_config: ProfileConfig,
    database_path: PathBuf,
}
pub struct ProcessDatabase {
    profile_config: ProfileConfig,
    crates: Vec<CrateRow>,
    versions: BTreeMap<CrateId, VersionRow>,
    categories: HashMap<CategoryId, String>,
    crates_categories: HashMap<CrateId, CategoryId>,
    crate_downloads: HashMap<CrateId, u64>,
}
pub struct FilterSelectedCrates {
    profile_config: ProfileConfig,
}
pub struct WriteProfile;

// Starts StateMachine always in Initialize state
impl GenProfiles {
    #[tracing::instrument(skip_all)]
    pub fn new(args: Args) -> Self {
        Self {
            args,
            state: Initialize,
        }
    }
}

// Implement StateMachine for Initialize state
impl StateMachine<Initialize> {
    #[tracing::instrument(skip_all)]
    pub fn read_profiles_config(self) -> Result<StateMachine<ReadProfilesConfig>> {
        debug!("Reading profiles config...");
        let profile_config: ProfileConfig = match &self.args.profiles_file {
            Some(path) => Parser::new(path)?,
            None => Parser::default(),
        }
        .try_into()?;

        debug!("Loaded {} profiles", profile_config.profiles().len());
        Ok(StateMachine {
            args: self.args,
            state: ReadProfilesConfig { profile_config },
        })
    }
}

// Implement StateMachine for ReadProfilesConfig state
impl StateMachine<ReadProfilesConfig> {
    #[tracing::instrument(skip_all)]
    pub async fn download_database(self) -> Result<StateMachine<DownloadDatabase>> {
        debug!("Downloading database...");
        let url = "https://static.crates.io/db-dump.tar.gz";
        let path = self
            .args
            .db_path
            .clone()
            .unwrap_or("/tmp/db-dump.tar.gz".into());
        let tar_file_path = Path::new(&path);
        let state = StateMachine {
            args: self.args,
            state: DownloadDatabase {
                profile_config: self.state.profile_config,
                database_path: tar_file_path.to_path_buf(),
            },
        };
        debug!("Downloading from {}", url);

        if tar_file_path.exists() {
            debug!(
                "File already exists at '{path}', skipping...",
                path = tar_file_path.to_string_lossy()
            );
            return Ok(state);
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
        pb.set_style(
            ProgressStyle::default_bar()
                .template("{msg}\n{spinner:.green} [{elapsed_precise}] [{wide_bar:.white/blue}] {bytes}/{total_bytes} ({bytes_per_sec}, {eta})")
                .unwrap()
                .progress_chars("█  ")
        );
        pb.set_message(format!("Downloading {url}"));

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

        Ok(state)
    }
}

// Implement StateMachine for DownloadDatabase state
impl StateMachine<DownloadDatabase> {
    #[tracing::instrument(skip_all)]
    pub fn process_database(self) -> Result<StateMachine<ProcessDatabase>> {
        debug!("Extracting database...");
        // Process the db-dump...
        let mut versions = BTreeMap::new();
        let mut crates = Vec::new();
        let mut categories = HashMap::new();
        let mut crates_categories = HashMap::new();
        let mut crate_downloads = HashMap::new();

        debug!("Loading...");
        let crate_name = &self.args.name;
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

        let handle_versions = |row: VersionRow| match versions.entry(row.crate_id) {
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

        let handle_crate_downloads = |row: CrateDownloadsRow| {
            crate_downloads.insert(row.crate_id, row.downloads);
        };

        db_dump::Loader::new()
            .crates_categories(handle_crates_categories)
            .categories(handle_categories)
            .crates(handle_crates)
            .versions(handle_versions)
            .crate_downloads(handle_crate_downloads)
            .load(self.state.database_path)
            .context("Failed to load database")?;

        debug!("Sorting...");
        crates.sort_by(|r1, r2| {
            let r1_downloads = crate_downloads.get(&r1.id).unwrap_or(&0);
            let r2_downloads = crate_downloads.get(&r2.id).unwrap_or(&0);
            r2_downloads.cmp(r1_downloads)
        });

        Ok(StateMachine {
            args: self.args,
            state: ProcessDatabase {
                profile_config: self.state.profile_config,
                crates,
                versions,
                categories,
                crates_categories,
                crate_downloads,
            },
        })
    }
}

// Implement StateMachine for ProcessDatabase state
impl StateMachine<ProcessDatabase> {
    #[tracing::instrument(skip_all)]
    pub fn filter_selected_crates(self) -> Result<StateMachine<FilterSelectedCrates>> {
        debug!("Filtering crates...");
        // Add crates based on criteria
        let crates_by_count = self
            .state
            .crates
            .iter()
            .take(self.args.crate_count)
            .cloned()
            .collect::<HashSet<_>>();

        let crates_by_category = match &self.args.categories {
            Some(_) => {
                let mut categories = add_categories(
                    &self.state.crates,
                    &self.state.categories,
                    &self.args.categories,
                    &self.state.crates_categories,
                );
                categories.sort_by(|r1, r2| {
                    let r1_downloads = self.state.crate_downloads.get(&r1.id).unwrap_or(&0);
                    let r2_downloads = self.state.crate_downloads.get(&r2.id).unwrap_or(&0);
                    r2_downloads.cmp(r1_downloads)
                });
                match self.args.category_count_limit {
                    Some(limit) => categories.into_iter().take(limit).collect(),
                    None => categories,
                }
                .into_iter()
                .collect::<HashSet<_>>()
            }
            None => HashSet::new(),
        };

        // Combine crates selected by count and by category.
        let selected_crates_profiles: Profiles = crates_by_count
            .union(&crates_by_category)
            .cloned()
            .map(|r| r.name.clone())
            .map(Profile::try_from)
            .collect::<Result<Profiles>>()?;

        // Remove all crates in selected_crates that are also in self.state.profiles
        let selected_crates_profiles: Profiles = selected_crates_profiles
            .into_iter()
            .filter(|p| {
                !self
                    .state
                    .profile_config
                    .profiles()
                    .iter()
                    .any(|o| o.has_same_name(p))
            })
            .collect();

        let profiles: Profiles = self
            .state
            .profile_config
            .profiles()
            .iter()
            .chain(selected_crates_profiles.iter())
            .cloned()
            .map(|p| match p.versions.is_empty() {
                false => p,
                true => {
                    let versions = self
                        .state
                        .crates
                        .iter()
                        .filter(|&r| r.name == p.name())
                        .map(|r| {
                            Version::from(self.state.versions.get(&r.id).map(|v| v.num.clone()))
                        })
                        .collect::<Versions>();
                    let profile = Profile::new(p.name().into(), p.settings.clone(), Some(versions));
                    match profile {
                        Ok(p) => p,
                        Err(e) => {
                            warn!("Invalid profile: {:?}", e);
                            p
                        }
                    }
                }
            })
            .collect();

        // Update profile_config with new profiles
        let profile_config = self.state.profile_config.replace_profiles(profiles);

        Ok(StateMachine {
            args: self.args,
            state: FilterSelectedCrates { profile_config },
        })
    }
}

// Implement StateMachine for ProcessDatabase state
impl StateMachine<FilterSelectedCrates> {
    #[tracing::instrument(skip_all)]
    pub fn write_profile(self) -> Result<StateMachine<WriteProfile>> {
        debug!("Writing profile...");
        let total_crates = self.state.profile_config.profiles().len();
        let mut output = File::create(&self.args.output_path)?;
        output.write_all(serde_yaml::to_string(&self.state.profile_config)?.as_bytes())?;

        debug!("Total of {total_crates} crates included in the profile.",);
        info!(
            "Wrote profile to: {}",
            self.args.output_path.to_string_lossy()
        );
        Ok(StateMachine {
            args: self.args,
            state: WriteProfile,
        })
    }
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
    let existent_categories = categories.values().cloned().collect::<HashSet<_>>();
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
    crates: &[CrateRow],
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
        .cloned()
        .collect()
}

#[cfg(test)]
mod tests {
    use super::*;
    use rstest::*;

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
