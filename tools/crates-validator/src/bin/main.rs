use std::fs::File;
use std::io::BufReader;
use std::path::PathBuf;

use anyhow::{Context, Result};
use clap::Parser;
use colored::Colorize;
use risc0_crates_validator::{ProfileConfig, RunStatus, ValidatorBuilder};
use tracing::info;
use tracing_subscriber::EnvFilter;

#[derive(Parser, Debug)]
#[command(author, version, about, long_about = None)]
struct Args {
    /// Path to json version of [ProfileConfig]
    #[arg(short = 'p', long, default_value = "./profiles/primary.json")]
    profiles_path: PathBuf,

    /// Run just a single crate from the [ProfileConfig]
    #[arg(short = 'c', long)]
    crate_name: Option<String>,

    /// Output location to write temporary projects
    ///
    /// Defaults value is a new TempDir
    #[arg(short = 'o', long)]
    out_dir: Option<PathBuf>,

    /// Write profile data with results
    ///
    /// Optional: write out the profile data with all the validation results
    #[arg(short = 'j', long)]
    json_output: Option<PathBuf>,
}

fn main() -> Result<()> {
    tracing_subscriber::fmt()
        .with_env_filter(EnvFilter::from_default_env())
        .init();

    let args = Args::parse();

    let file = File::open(args.profiles_path).context("Failed to open profiles_path file")?;
    let reader = BufReader::new(file);
    let context: ProfileConfig = serde_json::from_reader(reader)?;

    info!(
        "Starting run of {} profiles...",
        context.profiles.borrow().len()
    );
    let validator = ValidatorBuilder::new(context)
        .out_dir(args.out_dir)
        .build()?;

    if let Some(crate_name) = args.crate_name {
        validator.run_single(&crate_name)?;
    } else {
        validator.run_all()?;
    }

    info!("Test results:");
    colored::control::set_override(true);
    let mut successful = 0;
    for (idx, profile) in validator.context.profiles.borrow().iter().enumerate() {
        let result = profile
            .results
            .as_ref()
            .context(format!("crate {} does not have results", profile.name))?;
        let result_str = result.status.as_ref();
        info!(
            "{idx}: {} - {}",
            profile.name,
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
    info!(
        "{}/{} successful",
        successful,
        validator.context.profiles.borrow().len()
    );

    Ok(())
}
