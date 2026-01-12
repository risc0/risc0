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

use std::{fs::File, io::BufReader, path::PathBuf};

use anyhow::{Context, Result, bail};
use clap::Parser;
use colored::Colorize;
use risc0_crates_validator::{ProfileConfig, RunStatus, ValidatorBuilder, types::repo::Repo};
use tracing::info;
use tracing_subscriber::EnvFilter;

#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
    /// Path to YAML version of [ProfileConfig]
    #[arg(short = 'P', long, default_value = "./profiles/primary.yaml")]
    profiles_path: PathBuf,

    /// Run just a single crate from the [ProfileConfig]
    #[arg(short = 'c', long)]
    crate_name: Option<String>,

    /// Output location to write temporary projects
    ///
    /// Defaults value is a new TempDir
    #[arg(short = 'd', long)]
    out_dir: Option<PathBuf>,

    /// Write profile data with results
    ///
    /// Optional: write out the profile data with all the validation results
    #[arg(short = 'o', long)]
    output: Option<PathBuf>,

    // TODO: Maybe it'd be possible to use `clap_serde_derive` as a way to simplify argument parsing?
    // (Doing this for each variant of the `Repo` enum - `path`, `branch` and `tag`)
    /// Specify the RISC Zero repository path to use as source for templates and
    /// crate imports.
    #[arg(short, long, conflicts_with_all = &["branch", "tag"])]
    path: Option<String>,

    /// Specify the RISC Zero repository branch to use as source for templates and
    /// crate imports.
    #[arg(short, long, conflicts_with_all = &["path", "tag"])]
    branch: Option<String>,

    /// Specify the RISC Zero repository tag to use as source for templates and
    /// crate imports.
    #[arg(short, long, conflicts_with_all = &["path", "branch"])]
    tag: Option<String>,
}

impl Args {
    fn repo(&self) -> Result<Repo> {
        match (self.path.as_ref(), self.branch.as_ref(), self.tag.as_ref()) {
            (Some(path), None, None) => Ok(Repo::path(path.clone())),
            (None, Some(branch), None) => Ok(Repo::branch(branch.clone())),
            (None, None, Some(tag)) => Ok(Repo::tag(tag.clone())),
            (None, None, None) => bail!("No repo specified"),
            _ => bail!("Only one repo type can be specified"),
        }
    }
}

#[tracing::instrument(level = "trace")]
fn main() -> Result<()> {
    tracing_subscriber::fmt()
        .with_env_filter(EnvFilter::from_default_env())
        .init();

    let args = Args::parse();

    let file = File::open(&args.profiles_path).context("Failed to open profiles_path file")?;
    let reader = BufReader::new(file);
    let profile_configs: ProfileConfig = serde_yaml::from_reader(reader)?;
    let validator = ValidatorBuilder::new(profile_configs, args.repo()?, args.out_dir).build()?;
    let profiles = validator.context().profiles();
    let profiles_num = validator.context().profiles().len();

    info!("Starting run of {profiles_num} profiles...");
    let results = match args.crate_name {
        Some(crate_name) => {
            info!("Running single crate: {crate_name}");
            validator.run_single(&crate_name, profiles)?
        }
        None => {
            info!("Running all crates");
            validator.run_all(profiles)?
        }
    };

    info!("Test results:");
    colored::control::set_override(true);
    let mut successful = 0;
    for (idx, result) in results.iter().enumerate() {
        let result_str = result.status.as_ref();
        info!(
            "{idx}: {} - {}",
            result.name,
            match result.status {
                RunStatus::Success => {
                    successful += 1;
                    result_str.green()
                }
                RunStatus::Skipped => result_str.yellow(),
                RunStatus::BuildFail => result_str.red(),
                RunStatus::RunFail => result_str.red(),
            }
        );
    }

    colored::control::unset_override();
    info!("{successful}/{profiles_num} successful");

    if let Some(out_path) = args.output {
        std::fs::write(
            out_path,
            serde_json::to_string(&results).context("Failed to serialize Validator context")?,
        )
        .context("Failed to write output json file")?;
    }

    Ok(())
}
