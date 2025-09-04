// Copyright 2025 RISC Zero, Inc.
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

//! Checks that a previous release continues to compile if the current branch's crates were
//! released. This is a similar thing to what the SemVer checks are checking, but this check is
//! more real, but also not all-encompassing.

use anyhow::{Context as _, Result, anyhow, bail};
use camino::Utf8Path;
use clap::Parser;
use tempfile::tempdir;
use xshell::{Shell, cmd};

use std::collections::HashMap;
use std::io::{Seek as _, SeekFrom, Write as _};
use std::path::Path;

#[derive(Parser)]
pub struct ReleaseBackwardsCompat {
    #[arg(long)]
    cuda: bool,
}

fn cargo_risc0_url(version: &semver::Version) -> url::Url {
    let platform = match std::env::consts::OS {
        "macos" => format!("{}-apple-darwin", std::env::consts::ARCH),
        "linux" => format!("{}-unknown-linux-gnu", std::env::consts::ARCH),
        unknown => unimplemented!("unsupported os {unknown}"),
    };

    format!(
        "https://github.com/risc0/risc0/releases/download/v{version}/cargo-risczero-{platform}.tgz"
    )
    .parse()
    .unwrap()
}

fn download_and_extract_cargo_risczero(
    sh: &Shell,
    base_version: &semver::Version,
    temp_dir: &tempfile::TempDir,
) -> Result<(), anyhow::Error> {
    let url = cargo_risc0_url(base_version);

    sh.change_dir(temp_dir.path());
    println!("downloading {url}...");

    let mut resp = reqwest::blocking::get(url.clone())?;

    if !resp.status().is_success() {
        let body = resp.text().ok();
        bail!("remote error: {body:?}: {url}");
    }
    resp.copy_to(&mut std::fs::File::create(
        temp_dir.path().join("cargo-risczero.tgz"),
    )?)?;

    cmd!(sh, "tar --extract --file cargo-risczero.tgz cargo-risczero").run()?;

    Ok(())
}

fn add_features_to_risc0_zkvm(manifest_path: &Utf8Path, features_to_add: &[&str]) -> Result<()> {
    let content = std::fs::read_to_string(manifest_path)
        .with_context(|| format!("failed to read manifest {manifest_path}"))?;
    let mut cargo_toml = content
        .parse::<toml_edit::DocumentMut>()
        .with_context(|| format!("failed to parse {manifest_path} as TOML"))?;
    let dependencies_table = cargo_toml
        .get_mut("dependencies")
        .ok_or_else(|| anyhow!("could not find dependencies section in {manifest_path}"))?;
    let dependencies_table = dependencies_table
        .as_table_like_mut()
        .ok_or_else(|| anyhow!("dependencies is not a table in {manifest_path}"))?;
    let (_, dep_item) = dependencies_table
        .iter_mut()
        .find(|(dep_name, _)| dep_name == "risc0-zkvm")
        .ok_or_else(|| anyhow!("failed to find risc0-zkvm dependency"))?;

    if !dep_item
        .as_table_like()
        .is_some_and(|t| t.get("features").is_some_and(|f| f.is_array()))
    {
        dep_item
            .as_table_like_mut()
            .unwrap()
            .insert("features", toml_edit::array());
    }

    let features = dep_item
        .get_mut("features")
        .and_then(|f| f.as_array_mut())
        .unwrap();
    for feature in features_to_add {
        features.push(*feature);
    }

    std::fs::write(manifest_path, cargo_toml.to_string())
        .with_context(|| format!("failed to write to {manifest_path}"))?;

    Ok(())
}

fn create_test_project(
    args: &ReleaseBackwardsCompat,
    temp_dir: &tempfile::TempDir,
    sh: &Shell,
) -> Result<(), anyhow::Error> {
    cmd!(
        sh,
        "./cargo-risczero risczero new test-project --guest-name methods"
    )
    .env_clear()
    .run()?;
    sh.change_dir(temp_dir.path().join("test-project"));

    // modify risc0-zkvm dependency to have the "prove" feature, to enable more compilation
    let mut features = vec!["prove"];

    if args.cuda {
        features.push("cuda");
    }

    add_features_to_risc0_zkvm(
        Utf8Path::from_path(&temp_dir.path().join("test-project/host/Cargo.toml"))
            .ok_or_else(|| anyhow!("path contains unexpected non-UTF8"))?,
        &features,
    )?;

    Ok(())
}

fn patch_test_project_dependencies(
    metadata: &cargo_metadata::Metadata,
    temp_dir: &tempfile::TempDir,
) -> Result<()> {
    let mut project_cargo_toml = std::fs::OpenOptions::new()
        .read(true)
        .append(true)
        .open(temp_dir.path().join("test-project/Cargo.toml"))?;
    project_cargo_toml.seek(SeekFrom::End(0))?;
    writeln!(&mut project_cargo_toml)?;
    writeln!(&mut project_cargo_toml, "[patch.crates-io]")?;
    for package in metadata.workspace_default_packages() {
        writeln!(
            &mut project_cargo_toml,
            "{} = {{ path = \"{}\" }}",
            package.name,
            package.manifest_path.parent().unwrap()
        )?;
    }
    Ok(())
}

fn get_release_versions() -> Result<Vec<semver::Version>> {
    let url = "https://api.github.com/repos/risc0/risc0/releases";
    let client = reqwest::blocking::Client::new();
    let resp = client.get(url).header("User-Agent", "reqwest").send()?;
    if !resp.status().is_success() {
        let body = resp.text().ok();
        bail!("remote error: {body:?}: {url}");
    }
    let body: serde_json::Value = resp
        .json()
        .context("unexpected GitHub release response body")?;
    let arr = body
        .as_array()
        .ok_or_else(|| anyhow!("unexpected GitHub release response body"))?;
    let mut releases = arr
        .iter()
        .map(|v| {
            let r = v
                .as_object()
                .ok_or_else(|| anyhow!("unexpected release shape"))?;
            Ok(r.get("name")
                .ok_or_else(|| anyhow!("missing release name"))?
                .as_str()
                .ok_or_else(|| anyhow!("release name not string"))?[1..]
                .parse()?)
        })
        .collect::<Result<Vec<semver::Version>>>()?;
    releases.sort();
    Ok(releases)
}

fn report_used_dependencies(
    temp_dir: &tempfile::TempDir,
    metadata: &cargo_metadata::Metadata,
) -> Result<(), anyhow::Error> {
    let workspace_packages: HashMap<String, semver::Version> = metadata
        .workspace_default_packages()
        .into_iter()
        .map(|package| (package.name.as_str().into(), package.version.clone()))
        .collect();

    let lock_file = cargo_lock::Lockfile::load(temp_dir.path().join("test-project/Cargo.lock"))?;
    for pkg in lock_file.packages {
        if let Some(version) = workspace_packages.get(pkg.name.as_str())
            && version == &pkg.version
        {
            println!("used {}@{} from current workspace", pkg.name, pkg.version);
        }
    }
    Ok(())
}

fn test_release(
    args: &ReleaseBackwardsCompat,
    metadata: &cargo_metadata::Metadata,
    base_version: &semver::Version,
) -> Result<(), anyhow::Error> {
    let temp_dir = tempdir()?;
    let sh = Shell::new()?;

    download_and_extract_cargo_risczero(&sh, base_version, &temp_dir)?;

    create_test_project(args, &temp_dir, &sh)?;

    patch_test_project_dependencies(metadata, &temp_dir)?;

    cmd!(sh, "cargo run").run()?;

    println!("========== done testing {base_version} ===========");
    report_used_dependencies(&temp_dir, metadata)?;

    Ok(())
}

fn run_inner(args: &ReleaseBackwardsCompat, workspace_dir: &Path) -> Result<()> {
    let metadata = cargo_metadata::MetadataCommand::new()
        .current_dir(workspace_dir)
        .exec()
        .context("failed to run `cargo metadata`")?;
    let current_release = metadata
        .packages
        .iter()
        .find(|package| package.name.as_str() == "risc0-zkvm")
        .ok_or_else(|| anyhow!("couldn't find risc0-zkvm in current workspace"))?
        .version
        .clone();

    let all_releases = get_release_versions()?;
    let all_releases = all_releases
        .into_iter()
        .filter(|r| r.pre.is_empty())
        .take_while(|r| r < &current_release)
        .collect::<Vec<_>>();

    // Grab latest release of each major version
    let mut releases: Vec<semver::Version> = vec![];
    for release in all_releases.into_iter().rev() {
        if let Some(last) = releases.last()
            && last.major == release.major
        {
            continue;
        }
        releases.push(release);
    }

    println!(
        "testing releases: [{}]",
        releases
            .iter()
            .map(|r| r.to_string())
            .collect::<Vec<_>>()
            .join(", ")
    );
    for release in releases {
        println!("testing release {release}");
        test_release(args, &metadata, &release)?;
    }

    Ok(())
}

impl ReleaseBackwardsCompat {
    pub fn run(&self) {
        let current_dir = std::env::current_dir().expect("should be able to get current directory");

        if let Err(e) = run_inner(self, &current_dir) {
            panic!("{e}");
        }
    }
}
