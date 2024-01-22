// Copyright 2024 RISC Zero, Inc.
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
    fs::{self, DirBuilder},
    path::{Path, PathBuf},
    sync::OnceLock,
    time::{Duration, Instant},
};

use crate::utils::risc0_data;
use anyhow::{anyhow, bail, ensure, Context, Result};
use clap::Parser;
use reqwest::{header::HeaderMap, Client};
use risc0_zkvm::{
    get_prover_server,
    recursion::{join, lift},
    ExecutorEnv, ExecutorImpl, ProverOpts, VerifierContext,
};
use risc0_zkvm_methods::bench::{BenchmarkSpec, SpecWithIters};
use serde::{Deserialize, Serialize};
use serde_json::Value;
use sha2::{Digest, Sha256};
use tracing::{debug, error, info, instrument, trace, warn};

static ELF: OnceLock<Result<Vec<u8>>> = OnceLock::new();
static GITHUB_API_URL: &str = "https://api.github.com";
static GITHUB_OWNER: &str = "risc0";
static GITHUB_REPO: &str = "risc0";

/// `cargo risczero benchmark`
#[derive(Parser)]
pub struct BenchmarkCommand {
    /// Number of iterations.
    #[arg(short, long)]
    pub iterations: Option<u64>,

    /// Which hash function to use.
    #[arg(short = 'f', long, default_value_t = String::from("poseidon"), value_parser = ["poseidon", "sha-256"])]
    pub hashfn: String,

    /// Specify the segment po2.
    #[arg(short, long, default_value_t = 20)]
    po2: u32,

    /// Specify the benchmark ELF to download.
    ///
    /// Its format should be `name:sha256`, where `name` is the name of the ELF binary and `sha256` is the SHA256 hash of the ELF binary.
    #[arg(long, default_value_t = String::from("bench:dded5bbfb4034022c03dcc7150b4d00e73a67329c21406a0ada0dbbff7767536"))]
    pub elf: String,
}

impl BenchmarkCommand {
    /// Execute this command.
    pub fn run(&self) -> Result<()> {
        let query_name = QueryName::new(Some(&self.elf))?;
        if let Some(i) = self.iterations {
            return self.run_with_iterations(i, &query_name);
        } else {
            let iterations = [
                0,          // warm-up
                1,          // 16, 64K
                4 * 1024,   // 17, 128K
                16 * 1024,  // 18, 256K
                32 * 1024,  // 19, 512K
                64 * 1024,  // 20, 1M
                200 * 1024, // 21, 2M
                400 * 1024, // 22, 4M
                            // 900 * 1024,  // 23, 8M
                            // 1400 * 1024, // 24, 16M
            ];

            for i in iterations.into_iter() {
                self.run_with_iterations(i, &query_name)?;
            }
        }

        Ok(())
    }

    fn run_with_iterations(&self, iterations: u64, query_name: &QueryName) -> Result<()> {
        let bench_elf = get_elf_binary(query_name)?;
        let iterations = SpecWithIters(BenchmarkSpec::SimpleLoop, iterations);
        let env = ExecutorEnv::builder()
            .write(&iterations)?
            .segment_limit_po2(self.po2)
            .build()?;
        let mut exec = ExecutorImpl::from_elf(env, &bench_elf)?;

        // Execute
        let (session, exec_duration) = with_duration(|| exec.run())?;

        let cycles = session.get_cycles()?;
        let segments = session.resolve()?;

        let opts = ProverOpts::default();
        let ctx = VerifierContext::default();
        let prover = get_prover_server(&opts)?;

        let mut lifts = vec![];
        let mut prove_durations = vec![];
        let mut lift_durations = vec![];

        // Prove and Lift
        for segment in segments.iter() {
            let (receipt, receipt_duration) =
                with_duration(|| prover.prove_segment(&ctx, segment))?;
            prove_durations.push(receipt_duration);

            let (lift, lift_duration) = with_duration(|| lift(&receipt))?;
            lifts.push(lift);
            lift_durations.push(lift_duration);
        }

        let mut join_durations = vec![];
        // Optional Join
        if segments.len() > 1 {
            let (_final, duration) = with_duration(|| join(&lifts[0], &lifts[1]))?;
            join_durations.push(duration);
        }

        println!("\nSTATS:");
        println!("cycles:     {}", cycles.1);
        println!("segments:   {}", segments.len());
        println!("exec:       {exec_duration:?}");
        println!("prove:      {prove_durations:?}");
        println!("lift:       {lift_durations:?}");
        println!("prove+lift: {:?}", prove_durations[0] + lift_durations[0]);
        println!("join:       {join_durations:?}");

        Ok(())
    }
}

fn with_duration<T, F: FnOnce() -> Result<T>>(f: F) -> Result<(T, Duration)> {
    let start = Instant::now();
    let result = f()?;
    let duration = start.elapsed();
    Ok((result, duration))
}

#[instrument]
fn get_elf_binary(query_name: &QueryName) -> Result<&'static Vec<u8>> {
    let elf = ELF
        .get_or_init(|| {
            let binding = elf_binary_path().context("Could not get elf binary path")?;
            let path = binding.as_path();
            let content = if !path.exists() {
                debug!("Getting elf binary");
                debug!("Elf binary does not exist");
                let content =
                    download_elf_binary(query_name).context("Could not download elf binary")?;
                save_elf_to_file(&content, path)?;
                debug!("Got elf binary");
                content
            } else {
                read_elf(&path).context("Could not read elf binary")?
            };
            if !has_valid_hash(&content, query_name)? {
                bail!("Invalid ELF hash")
            }
            Ok(content)
        })
        .as_ref()
        .map_err(|e| anyhow!("{:?}", e))?;
    Ok(elf)
}

fn has_valid_hash(content: impl AsRef<[u8]>, query_name: &QueryName) -> Result<bool> {
    let hash = compute_hash(content);
    let expected = query_name
        .elf_hash()
        .ok_or_else(|| anyhow!("elf hash not found"))?;
    Ok(hash == expected)
}

fn compute_hash(content: impl AsRef<[u8]>) -> String {
    let mut hasher = Sha256::new();
    hasher.update(content);
    let hash = hasher.finalize();
    format!("{:x}", hash)
}

#[instrument]
fn elf_binary_dir() -> Result<PathBuf> {
    Ok(elf_binary_path()?
        .parent()
        .context("ELF binary does not have a parent")?
        .to_path_buf())
}

#[instrument]
fn elf_binary_path() -> Result<PathBuf> {
    let path = risc0_data()?.join("benchmark").join("bench");
    trace!(?path);
    Ok(path)
}

#[instrument]
fn create_benchmark_dir() -> Result<()> {
    let path = elf_binary_dir()?;
    trace!("Creating benchmark directory at {path:?}");
    DirBuilder::new().recursive(true).create(path)?;
    Ok(())
}

#[instrument]
fn download_elf_binary(query_name: &QueryName) -> Result<Vec<u8>> {
    create_benchmark_dir()?;

    let client = get_client()?;
    let rt = tokio::runtime::Runtime::new()?;
    let response = rt
        .block_on(list_artifacts(&client, query_name))
        .context("Failed to get artifacts list")?;
    let artifacts = response
        .get("artifacts")
        .context("Failed to get artifacts")?
        .as_array()
        .context("Failed to get artifacts as array")?;

    if artifacts.is_empty() {
        bail!("No artifacts found");
    }

    for artifact in artifacts {
        info!("Downloading ELF binary");
        trace!(?artifact);
        let artifact: Artifact = artifact
            .clone()
            .try_into()
            .context("Failed to parse artifact")?;
        match rt.block_on(download_artifact(&client, &artifact)) {
            Ok(elf) => {
                info!("Downloaded ELF Binary");
                return Ok(elf);
            }
            Err(error) => {
                error!("Failed to download artifact: {error}");
            }
        }
    }

    bail!("Failed to download artifact")
}

#[instrument]
fn read_elf(path: &Path) -> Result<Vec<u8>> {
    debug!("Reading elf binary");
    let elf = fs::read(path)?;
    trace!(elf_length = elf.len());
    Ok(elf)
}

#[derive(Debug, Serialize, Deserialize)]
struct Artifact {
    id: u64,
    node_id: String,
    name: String,
    size_in_bytes: u64,
    url: String,
    archive_download_url: String,
    expired: bool,
    created_at: String,
    expires_at: String,
    updated_at: String,
    workflow_run: WorkflowRun,
}

#[derive(Debug, Serialize, Deserialize)]
struct WorkflowRun {
    id: u64,
    repository_id: u64,
    head_repository_id: u64,
    head_branch: String,
    head_sha: String,
}

impl TryFrom<Value> for Artifact {
    type Error = anyhow::Error;

    fn try_from(value: Value) -> Result<Self, Self::Error> {
        serde_json::from_value(value).context("Failed to parse artifact")
    }
}

#[derive(Debug)]
struct QueryName(Option<String>);
impl QueryName {
    fn new(name: Option<impl Into<String>>) -> Result<Self> {
        let s = Self(name.map(|n| n.into()));
        ensure!(
            s.is_valid(),
            "Invalid query name. Expected format: `name:sha256`"
        );
        Ok(s)
    }

    fn is_valid(&self) -> bool {
        self.elf_name().is_some() && self.elf_hash().is_some()
    }

    fn elf_name(&self) -> Option<&str> {
        self.0.as_ref().map(|name| name.split(':').next()).flatten()
    }

    fn elf_hash(&self) -> Option<&str> {
        self.0.as_ref().map(|name| name.split(':').nth(1)).flatten()
    }
}

#[instrument]
async fn download_artifact(client: &Client, artifact: &Artifact) -> Result<Vec<u8>> {
    get_bytes(client, &artifact.archive_download_url).await
}

async fn list_artifacts(client: &Client, name: &QueryName) -> Result<Value> {
    let url = get_url(name);
    get_json(client, &url).await
}

fn save_elf_to_file(content: impl AsRef<[u8]>, path: impl AsRef<Path>) -> Result<()> {
    std::fs::write(path, content)?;
    Ok(())
}

fn read_json_file(path: impl AsRef<str>) -> Result<Value> {
    let json = std::fs::read_to_string(path.as_ref())?;
    let value = serde_json::from_str(&json)?;
    Ok(value)
}

fn get_client() -> Result<Client> {
    let client = Client::builder()
        .default_headers(get_headers()?)
        .user_agent("cargo-risc0")
        .build()?;
    Ok(client)
}

fn get_headers() -> Result<HeaderMap> {
    let github_token = std::env::var("GITHUB_TOKEN").context("Could not get GITHUB_TOKEN")?;
    let mut headers = HeaderMap::new();
    headers.insert("Accept", "application/vnd.github+json".parse()?);
    headers.insert("Authorization", format!("Bearer {github_token}").parse()?);
    headers.insert("X-GitHub-Api-Version", "2022-11-28".parse()?);
    Ok(headers)
}

fn get_url(name: &QueryName) -> String {
    let mut base = format!(
        "{}/repos/{}/{}/actions/artifacts",
        GITHUB_API_URL, GITHUB_OWNER, GITHUB_REPO
    );

    if let Some(ref name) = name.0 {
        base.push_str(&format!("?name={name}"));
    }

    base
}

#[instrument]
async fn get_json(client: &Client, url: &str) -> Result<Value> {
    Ok(client
        .get(url)
        .send()
        .await?
        .error_for_status()?
        .json::<Value>()
        .await?)
}

#[instrument]
async fn get_bytes(client: &Client, url: &str) -> Result<Vec<u8>> {
    Ok(client
        .get(url)
        .send()
        .await?
        .error_for_status()?
        .bytes()
        .await?
        .into())
}

pub fn init_logging() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();
}
