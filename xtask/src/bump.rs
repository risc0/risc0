// Copyright 2026 RISC Zero, Inc.
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

//! Sets the version of every released crate from the release declared in the workspace
//! `Cargo.toml`:
//!
//! ```toml
//! [workspace.metadata.release-version]
//! version = "3.1.0-rc.1"
//! lockstep = ["cargo-risczero", "risc0-r0vm", "risc0-zkvm"]
//! ```
//!
//! The lockstep crates get `version`. Every other crate is compared with its version at the last
//! stable `v*` tag, as published on crates.io, and gets the smallest bump that covers its changes,
//! with the pre-release of `version`: a patch if its packaged files changed or one of its
//! dependencies is bumped, a minor if `cargo-semver-checks` finds API additions. A crate that
//! needs a breaking change is an error. Unchanged crates keep the tag's version, and crates that
//! are new since the tag keep theirs with the pre-release. Since everything is computed from the
//! tag, running it again gives the same versions; going from a release candidate to the release
//! is a change to `version` only.

use std::collections::{BTreeMap, BTreeSet};
use std::fmt;
use std::path::{Path, PathBuf};
use std::process::Command;

use anyhow::{anyhow, bail, ensure, Context as _, Result};
use cargo_metadata::{DependencyKind, MetadataCommand};
use cargo_semver_checks::{Check, GlobalConfig, ReleaseType, Rustdoc};
use clap::Parser;
use semver::{Prerelease, Version};

#[derive(Parser)]
pub struct Bump {
    /// Only report, and fail if any crate's version differs from the computed one.
    #[arg(long)]
    check: bool,

    /// The release tag to compare with, instead of the last stable `v*` tag reachable from HEAD.
    #[arg(long)]
    baseline: Option<String>,
}

#[derive(Clone, Copy, Debug, PartialEq, Eq, PartialOrd, Ord)]
enum Level {
    None,
    Patch,
    Minor,
    Major,
}

impl fmt::Display for Level {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let s = match self {
            Level::None => "none",
            Level::Patch => "patch",
            Level::Minor => "minor",
            Level::Major => "major",
        };
        write!(f, "{s}")
    }
}

#[derive(Debug)]
struct Config {
    version: Version,
    lockstep: BTreeSet<String>,
}

/// A released crate of the workspace.
#[derive(Debug)]
struct Crate {
    name: String,
    manifest_path: PathBuf,
    version: Version,
    /// Normal and build dependencies on other released crates.
    deps: BTreeSet<String>,
    has_lib: bool,
}

/// What was found for one crate, and the version that follows from it.
#[derive(Debug, Default)]
struct Row {
    name: String,
    current: Option<Version>,
    baseline: Option<Version>,
    changed_files: Vec<String>,
    bumped_deps: Vec<String>,
    api: Option<Level>,
    new: Option<Version>,
}

impl Row {
    fn reasons(&self, lockstep: bool) -> String {
        let mut reasons = vec![];
        if lockstep {
            reasons.push("lockstep".to_string());
        }
        if self.baseline.is_none() {
            reasons.push("new since the baseline".to_string());
        }
        if !self.changed_files.is_empty() {
            let mut files = self
                .changed_files
                .iter()
                .take(3)
                .cloned()
                .collect::<Vec<_>>();
            if self.changed_files.len() > 3 {
                files.push(format!("{} more", self.changed_files.len() - 3));
            }
            reasons.push(format!("files: {}", files.join(", ")));
        }
        if !self.bumped_deps.is_empty() {
            reasons.push(format!("deps: {}", self.bumped_deps.join(", ")));
        }
        if let Some(api) = self.api.filter(|api| *api > Level::Patch) {
            reasons.push(format!("api: {api}"));
        }
        reasons.join("; ")
    }
}

fn read_config(metadata: &cargo_metadata::Metadata) -> Result<Config> {
    let table = metadata
        .workspace_metadata
        .get("release-version")
        .ok_or_else(|| {
            anyhow!("no [workspace.metadata.release-version] in the workspace Cargo.toml")
        })?;
    let version = table
        .get("version")
        .and_then(|v| v.as_str())
        .ok_or_else(|| anyhow!("[workspace.metadata.release-version] has no version string"))?;
    let version = Version::parse(version).context("failed to parse the release version")?;
    let lockstep = table
        .get("lockstep")
        .and_then(|v| v.as_array())
        .map(|names| {
            names
                .iter()
                .map(|name| {
                    name.as_str()
                        .map(str::to_string)
                        .ok_or_else(|| anyhow!("lockstep entries must be crate names"))
                })
                .collect::<Result<BTreeSet<_>>>()
        })
        .transpose()?
        .unwrap_or_default();
    Ok(Config { version, lockstep })
}

/// Workspace crates that cargo-release publishes, in dependency order.
fn released_crates(metadata: &cargo_metadata::Metadata) -> Result<Vec<Crate>> {
    let packages = metadata
        .workspace_packages()
        .into_iter()
        .filter(|package| {
            let release = package
                .metadata
                .get("release")
                .and_then(|release| release.get("release"))
                .and_then(|release| release.as_bool());
            release != Some(false) && package.publish.as_ref().is_none_or(|p| !p.is_empty())
        })
        .collect::<Vec<_>>();
    let names = packages
        .iter()
        .map(|package| package.name.to_string())
        .collect::<BTreeSet<_>>();

    let crates = packages
        .into_iter()
        .map(|package| Crate {
            name: package.name.to_string(),
            manifest_path: package.manifest_path.clone().into(),
            version: package.version.clone(),
            deps: package
                .dependencies
                .iter()
                .filter(|dep| dep.kind != DependencyKind::Development && names.contains(&dep.name))
                .map(|dep| dep.name.clone())
                .collect(),
            has_lib: package.targets.iter().any(|t| t.is_lib()),
        })
        .collect();
    dependency_order(crates)
}

fn dependency_order(crates: Vec<Crate>) -> Result<Vec<Crate>> {
    let mut pending = crates
        .into_iter()
        .map(|c| (c.name.clone(), c))
        .collect::<BTreeMap<_, _>>();
    let mut ordered = vec![];
    while !pending.is_empty() {
        let ready = pending
            .values()
            .filter(|c| c.deps.iter().all(|dep| !pending.contains_key(dep)))
            .map(|c| c.name.clone())
            .collect::<Vec<_>>();
        ensure!(
            !ready.is_empty(),
            "dependency cycle among {:?}",
            pending.keys().collect::<Vec<_>>()
        );
        for name in ready {
            ordered.push(pending.remove(&name).unwrap());
        }
    }
    Ok(ordered)
}

fn command_output(cmd: &mut Command) -> Result<String> {
    let output = cmd
        .output()
        .with_context(|| format!("failed to run {cmd:?}"))?;
    ensure!(
        output.status.success(),
        "{cmd:?} failed: {}",
        String::from_utf8_lossy(&output.stderr)
    );
    Ok(String::from_utf8(output.stdout)?)
}

/// The newest `v*` tag reachable from HEAD that is not a pre-release.
fn last_release_tag(root: &Path) -> Result<String> {
    let tags = command_output(
        Command::new("git")
            .current_dir(root)
            .args(["tag", "--merged", "HEAD", "--list", "v*"]),
    )?;
    tags.lines()
        .filter_map(|tag| Some((Version::parse(tag.strip_prefix('v')?).ok()?, tag)))
        .filter(|(version, _)| version.pre.is_empty())
        .max()
        .map(|(_, tag)| tag.to_string())
        .ok_or_else(|| anyhow!("no stable v* tag is reachable from HEAD"))
}

/// The crate's version in its manifest at `tag`, or `None` if the manifest isn't there.
fn version_at_tag(root: &Path, tag: &str, manifest_path: &Path) -> Result<Option<Version>> {
    let path = manifest_path.strip_prefix(root)?;
    let output = Command::new("git")
        .current_dir(root)
        .arg("show")
        .arg(format!("{tag}:{}", path.display()))
        .output()?;
    if !output.status.success() {
        return Ok(None);
    }
    let manifest: toml::Table = toml::from_str(std::str::from_utf8(&output.stdout)?)?;
    let version = manifest
        .get("package")
        .and_then(|package| package.get("version"))
        .and_then(|version| version.as_str())
        .ok_or_else(|| anyhow!("{tag}:{} has no package.version string", path.display()))?;
    Ok(Some(Version::parse(version)?))
}

/// The crate's path in the crates.io index.
fn index_path(name: &str) -> String {
    let name = name.to_lowercase();
    match name.len() {
        1 | 2 => format!("{}/{name}", name.len()),
        3 => format!("3/{}/{name}", &name[..1]),
        _ => format!("{}/{}/{name}", &name[..2], &name[2..4]),
    }
}

fn published_versions(name: &str) -> Result<BTreeSet<Version>> {
    let output = Command::new("curl")
        .args(["-sSL", "-w", "\n%{http_code}"])
        .arg(format!("https://index.crates.io/{}", index_path(name)))
        .output()
        .context("failed to run curl")?;
    let body = String::from_utf8(output.stdout)?;
    let (index, status) = body.rsplit_once('\n').unwrap_or(("", &body));
    match status {
        "200" => {}
        "404" => return Ok(BTreeSet::new()),
        _ => bail!("the crates.io index returned {status} for {name}"),
    }
    index
        .lines()
        .map(|line| {
            let entry: serde_json::Value = serde_json::from_str(line)?;
            let vers = entry["vers"]
                .as_str()
                .ok_or_else(|| anyhow!("index entry for {name} without vers"))?;
            Ok(Version::parse(vers)?)
        })
        .collect()
}

/// Downloads `name` at `version` from crates.io and unpacks it into `dir`.
fn fetch_published(name: &str, version: &Version, dir: &Path) -> Result<PathBuf> {
    std::fs::create_dir_all(dir)?;
    let file = dir.join(format!("{name}-{version}.crate"));
    command_output(
        Command::new("curl")
            .args(["-fsSL", "-o"])
            .arg(&file)
            .arg(format!(
                "https://static.crates.io/crates/{name}/{name}-{version}.crate"
            )),
    )?;
    unpack(&file, dir)
}

fn unpack(file: &Path, dir: &Path) -> Result<PathBuf> {
    std::fs::create_dir_all(dir)?;
    command_output(Command::new("tar").arg("-xzf").arg(file).arg("-C").arg(dir))?;
    let stem = file
        .file_stem()
        .ok_or_else(|| anyhow!("bad crate file name {}", file.display()))?;
    Ok(dir.join(stem))
}

/// Packages every released crate into `target/package` as it would be published.
fn package_all(root: &Path, crates: &[Crate]) -> Result<()> {
    eprintln!("Packaging {} crates", crates.len());
    let mut cmd = Command::new("cargo");
    cmd.current_dir(root)
        .args(["package", "--no-verify", "--allow-dirty", "--quiet"]);
    for c in crates {
        cmd.args(["-p", &c.name]);
    }
    command_output(&mut cmd)?;
    Ok(())
}

/// Files that differ between two unpacked crates. Without `exact`, the manifests are compared
/// without the crate's own version and the versions of its workspace dependencies.
fn changed_files(
    base: &Path,
    current: &Path,
    workspace: &BTreeSet<String>,
    exact: bool,
) -> Result<Vec<String>> {
    let base_files = list_files(base)?;
    let current_files = list_files(current)?;
    let mut changed = vec![];
    for file in base_files.union(&current_files) {
        let same = match (base_files.contains(file), current_files.contains(file)) {
            (true, true) => {
                let a = std::fs::read(base.join(file))?;
                let b = std::fs::read(current.join(file))?;
                if file == "Cargo.toml" && !exact {
                    normalize_manifest(&a, workspace)? == normalize_manifest(&b, workspace)?
                } else {
                    a == b
                }
            }
            _ => false,
        };
        if !same {
            changed.push(file.clone());
        }
    }
    Ok(changed)
}

fn list_files(dir: &Path) -> Result<BTreeSet<String>> {
    // Written by cargo package, so they always differ
    const IGNORED: [&str; 3] = [".cargo_vcs_info.json", "Cargo.toml.orig", "Cargo.lock"];
    let mut files = BTreeSet::new();
    for entry in walkdir::WalkDir::new(dir) {
        let entry = entry?;
        if !entry.file_type().is_file() {
            continue;
        }
        let path = entry
            .path()
            .strip_prefix(dir)?
            .to_string_lossy()
            .to_string();
        if !IGNORED.contains(&path.as_str()) {
            files.insert(path);
        }
    }
    Ok(files)
}

fn normalize_manifest(manifest: &[u8], workspace: &BTreeSet<String>) -> Result<toml::Table> {
    fn strip_versions(deps: Option<&mut toml::Value>, workspace: &BTreeSet<String>) {
        let Some(deps) = deps.and_then(|deps| deps.as_table_mut()) else {
            return;
        };
        for (key, dep) in deps.iter_mut() {
            let name = dep
                .get("package")
                .and_then(|p| p.as_str())
                .unwrap_or(key)
                .to_string();
            if let (true, Some(dep)) = (workspace.contains(&name), dep.as_table_mut()) {
                dep.remove("version");
            }
        }
    }
    const DEP_TABLES: [&str; 3] = ["dependencies", "dev-dependencies", "build-dependencies"];

    let mut manifest: toml::Table = toml::from_str(std::str::from_utf8(manifest)?)?;
    if let Some(package) = manifest.get_mut("package").and_then(|p| p.as_table_mut()) {
        package.remove("version");
    }
    for key in DEP_TABLES {
        strip_versions(manifest.get_mut(key), workspace);
    }
    if let Some(targets) = manifest.get_mut("target").and_then(|t| t.as_table_mut()) {
        for (_, target) in targets.iter_mut() {
            if let Some(target) = target.as_table_mut() {
                for key in DEP_TABLES {
                    strip_versions(target.get_mut(key), workspace);
                }
            }
        }
    }
    Ok(manifest)
}

/// The API change `cargo-semver-checks` finds between the workspace crate and `baseline`.
fn api_level(root: &Path, name: &str, baseline: &Version) -> Result<Level> {
    eprintln!("Running cargo-semver-checks on {name} against {baseline}");
    let mut config = GlobalConfig::new();
    config.set_log_level(Some(log::Level::Info));
    let report = Check::new(Rustdoc::from_root(root))
        .set_baseline(Rustdoc::from_registry(baseline.to_string()))
        .set_packages(vec![name.to_string()])
        // Required bumps are relative to the assumed release, so the versions in the tree don't matter
        .set_release_type(ReleaseType::Patch)
        .with_default_features()
        .check_release(&mut config)?;
    Ok(
        match report
            .crate_reports()
            .get(name)
            .and_then(|r| r.required_bump())
        {
            None => Level::None,
            Some(ReleaseType::Major) => Level::Major,
            Some(ReleaseType::Minor) => Level::Minor,
            Some(_) => Level::Patch,
        },
    )
}

/// `base` raised by `level`, where a minor change of a 0.y crate bumps its patch number.
fn bump(base: &Version, level: Level, pre: &Prerelease) -> Version {
    let mut version = Version::new(base.major, base.minor, base.patch);
    match level {
        Level::None => return base.clone(),
        Level::Patch => version.patch += 1,
        Level::Minor if version.major == 0 => version.patch += 1,
        Level::Minor => {
            version.minor += 1;
            version.patch = 0;
        }
        Level::Major if version.major == 0 => {
            version.minor += 1;
            version.patch = 0;
        }
        Level::Major => {
            version.major += 1;
            version.minor = 0;
            version.patch = 0;
        }
    }
    version.pre = pre.clone();
    version
}

fn release_part(version: &Version) -> (u64, u64, u64) {
    (version.major, version.minor, version.patch)
}

/// Computes every crate's version. `changed` gives the files that differ from the baseline and
/// `api` the API change, which is only asked for crates that are bumped anyway.
fn decide(
    config: &Config,
    crates: &[Crate],
    baselines: &BTreeMap<String, Option<Version>>,
    changed: &BTreeMap<String, Vec<String>>,
    mut api: impl FnMut(&Crate, &Version) -> Result<Level>,
) -> Result<Vec<Row>> {
    let pre = &config.version.pre;
    let mut rows: Vec<Row> = vec![];
    let mut errors = vec![];
    for c in crates {
        let baseline = baselines.get(&c.name).cloned().flatten();
        let changed_files = changed.get(&c.name).cloned().unwrap_or_default();
        let bumped_deps = c
            .deps
            .iter()
            .filter(|dep| {
                rows.iter()
                    .any(|row| &row.name == *dep && row.new != row.baseline)
            })
            .cloned()
            .collect::<Vec<_>>();
        let mut row = Row {
            name: c.name.clone(),
            current: Some(c.version.clone()),
            baseline: baseline.clone(),
            changed_files,
            bumped_deps,
            ..Default::default()
        };
        let lockstep = config.lockstep.contains(&c.name);

        let result = (|| -> Result<Version> {
            let Some(baseline) = &baseline else {
                return Ok(if lockstep {
                    config.version.clone()
                } else {
                    let mut version =
                        Version::new(c.version.major, c.version.minor, c.version.patch);
                    version.pre = pre.clone();
                    version
                });
            };
            let mut level = if row.changed_files.is_empty() && row.bumped_deps.is_empty() {
                Level::None
            } else {
                Level::Patch
            };
            if level > Level::None && c.has_lib {
                let found = api(c, baseline)?;
                row.api = Some(found);
                level = level.max(found);
            }
            if level == Level::Major {
                bail!("{} needs a breaking change against {baseline}", c.name);
            }
            if lockstep {
                let needed = bump(baseline, level.max(Level::Patch), pre);
                ensure!(
                    release_part(&config.version) >= release_part(&needed),
                    "{} needs at least {needed}, more than the declared {}",
                    c.name,
                    config.version
                );
                return Ok(config.version.clone());
            }
            Ok(bump(baseline, level, pre))
        })();

        match result {
            Ok(new) => row.new = Some(new),
            Err(error) => errors.push(error),
        }
        rows.push(row);
    }

    if !errors.is_empty() {
        print_rows(config, &rows);
        bail!(
            "{}",
            errors
                .iter()
                .map(|e| e.to_string())
                .collect::<Vec<_>>()
                .join("\n")
        );
    }
    Ok(rows)
}

fn print_rows(config: &Config, rows: &[Row]) {
    let show = |v: &Option<Version>| v.as_ref().map_or("-".to_string(), Version::to_string);
    println!(
        "{:<38} {:<12} {:<12} {:<14} why",
        "crate", "baseline", "current", "new"
    );
    for row in rows {
        println!(
            "{:<38} {:<12} {:<12} {:<14} {}",
            row.name,
            show(&row.baseline),
            show(&row.current),
            show(&row.new),
            row.reasons(config.lockstep.contains(&row.name))
        );
    }
}

/// Fails if a new version is already on crates.io with other contents than the crate would have
/// now, which happens when a crate changes after its release candidate was published.
fn check_published(
    rows: &[Row],
    crates: &[Crate],
    packaged: &Path,
    workspace: &BTreeSet<String>,
    scratch: &Path,
) -> Result<()> {
    let mut errors = vec![];
    for (row, c) in rows.iter().zip(crates) {
        let new = row.new.as_ref().unwrap();
        if row.baseline.as_ref() == Some(new) || !published_versions(&c.name)?.contains(new) {
            continue;
        }
        let dir = scratch.join("published").join(&c.name);
        let published = fetch_published(&c.name, new, &dir)?;
        let current = packaged.join(format!("{}-{}", c.name, c.version));
        let differ = changed_files(&published, &current, workspace, &c.version == new)?;
        if !differ.is_empty() {
            errors.push(format!(
                "{} {new} is already on crates.io and differs in {}; declare a later pre-release",
                c.name,
                differ.join(", ")
            ));
        }
    }
    ensure!(errors.is_empty(), "{}", errors.join("\n"));
    Ok(())
}

fn write_versions(root: &Path, rows: &[Row], crates: &[Crate]) -> Result<()> {
    for (row, c) in rows.iter().zip(crates) {
        let new = row.new.as_ref().unwrap();
        if new == &c.version {
            continue;
        }
        let content = std::fs::read_to_string(&c.manifest_path)?;
        let mut manifest = content.parse::<toml_edit::DocumentMut>()?;
        manifest["package"]["version"] = toml_edit::value(new.to_string());
        std::fs::write(&c.manifest_path, manifest.to_string())?;
    }

    let path = root.join("Cargo.toml");
    let mut manifest = std::fs::read_to_string(&path)?.parse::<toml_edit::DocumentMut>()?;
    let deps = manifest["workspace"]["dependencies"]
        .as_table_like_mut()
        .ok_or_else(|| anyhow!("workspace.dependencies is not a table"))?;
    for row in rows {
        if let Some(dep) = deps.get_mut(&row.name) {
            dep["version"] = toml_edit::value(row.new.as_ref().unwrap().to_string());
        }
    }
    std::fs::write(&path, manifest.to_string())?;
    Ok(())
}

fn run_inner(args: &Bump, root: &Path) -> Result<()> {
    let metadata = MetadataCommand::new()
        .current_dir(root)
        .no_deps()
        .exec()
        .context("failed to run `cargo metadata`")?;
    let config = read_config(&metadata)?;
    let crates = released_crates(&metadata)?;
    for name in &config.lockstep {
        ensure!(
            crates.iter().any(|c| &c.name == name),
            "lockstep crate {name} is not a released workspace crate"
        );
    }
    let workspace = crates
        .iter()
        .map(|c| c.name.clone())
        .collect::<BTreeSet<_>>();

    let tag = match &args.baseline {
        Some(tag) => tag.clone(),
        None => last_release_tag(root)?,
    };
    eprintln!("Baseline: {tag}");
    let mut baselines = BTreeMap::new();
    for c in &crates {
        baselines.insert(
            c.name.clone(),
            version_at_tag(root, &tag, &c.manifest_path)?,
        );
    }

    package_all(root, &crates)?;
    let scratch = tempfile::tempdir()?;
    let packaged_dir = PathBuf::from(metadata.target_directory.as_std_path()).join("package");
    let packaged = scratch.path().join("current");
    let mut changed = BTreeMap::new();
    for c in &crates {
        let current = unpack(
            &packaged_dir.join(format!("{}-{}.crate", c.name, c.version)),
            &packaged,
        )?;
        if let Some(Some(baseline)) = baselines.get(&c.name) {
            eprintln!("Comparing {} with {baseline} on crates.io", c.name);
            let base = fetch_published(&c.name, baseline, &scratch.path().join("baseline"))?;
            changed.insert(
                c.name.clone(),
                changed_files(&base, &current, &workspace, false)?,
            );
        }
    }

    let rows = decide(&config, &crates, &baselines, &changed, |c, baseline| {
        api_level(root, &c.name, baseline)
    })?;
    print_rows(&config, &rows);
    check_published(&rows, &crates, &packaged, &workspace, scratch.path())?;

    let outdated = rows
        .iter()
        .filter(|row| row.new != row.current)
        .map(|row| row.name.as_str())
        .collect::<Vec<_>>();
    if outdated.is_empty() {
        println!("All versions are up to date");
        return Ok(());
    }
    if args.check {
        bail!("Versions to update: {}", outdated.join(", "));
    }
    write_versions(root, &rows, &crates)?;
    println!("Updated {}; updating the lock files", outdated.join(", "));
    crate::update_lock_files::run_inner(root)
}

impl Bump {
    pub fn run(&self) {
        let current_dir = std::env::current_dir().expect("should be able to get current directory");
        if let Err(e) = run_inner(self, &current_dir) {
            panic!("{e}");
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn v(s: &str) -> Version {
        Version::parse(s).unwrap()
    }

    fn krate(name: &str, version: &str, deps: &[&str]) -> Crate {
        Crate {
            name: name.into(),
            manifest_path: PathBuf::new(),
            version: v(version),
            deps: deps.iter().map(|d| d.to_string()).collect(),
            has_lib: true,
        }
    }

    fn config(version: &str, lockstep: &[&str]) -> Config {
        Config {
            version: v(version),
            lockstep: lockstep.iter().map(|l| l.to_string()).collect(),
        }
    }

    fn run(
        config: &Config,
        crates: Vec<Crate>,
        changed: &[&str],
        api: &[(&str, Level)],
    ) -> Result<BTreeMap<String, Version>> {
        let crates = dependency_order(crates)?;
        let baselines = crates
            .iter()
            .map(|c| (c.name.clone(), Some(c.version.clone())))
            .collect();
        let changed = changed
            .iter()
            .map(|name| (name.to_string(), vec!["src/lib.rs".to_string()]))
            .collect();
        let api = api
            .iter()
            .map(|(n, l)| (n.to_string(), *l))
            .collect::<BTreeMap<_, _>>();
        let rows = decide(config, &crates, &baselines, &changed, |c, _| {
            Ok(api.get(&c.name).copied().unwrap_or(Level::None))
        })?;
        Ok(rows
            .into_iter()
            .map(|row| (row.name, row.new.unwrap()))
            .collect())
    }

    #[test]
    fn bump_levels() {
        let pre = Prerelease::new("rc.1").unwrap();
        assert_eq!(bump(&v("3.0.5"), Level::Patch, &pre), v("3.0.6-rc.1"));
        assert_eq!(bump(&v("3.0.5"), Level::Minor, &pre), v("3.1.0-rc.1"));
        assert_eq!(bump(&v("0.4.3"), Level::Minor, &pre), v("0.4.4-rc.1"));
        assert_eq!(bump(&v("0.4.3"), Level::Major, &pre), v("0.5.0-rc.1"));
        assert_eq!(bump(&v("3.0.5"), Level::None, &pre), v("3.0.5"));
        assert_eq!(
            bump(&v("3.0.5"), Level::Patch, &Prerelease::EMPTY),
            v("3.0.6")
        );
    }

    #[test]
    fn unchanged_crates_keep_the_baseline() {
        let versions = run(
            &config("3.1.0-rc.1", &[]),
            vec![
                krate("core", "3.0.2", &[]),
                krate("zkp", "3.0.5", &["core"]),
            ],
            &[],
            &[],
        )
        .unwrap();
        assert_eq!(versions["core"], v("3.0.2"));
        assert_eq!(versions["zkp"], v("3.0.5"));
    }

    #[test]
    fn changes_and_bumped_dependencies_need_a_patch() {
        let versions = run(
            &config("3.1.0-rc.1", &[]),
            vec![
                krate("core", "3.0.2", &[]),
                krate("zkp", "3.0.5", &["core"]),
                krate("binfmt", "3.0.5", &["zkp"]),
                krate("other", "1.4.3", &[]),
            ],
            &["core"],
            &[],
        )
        .unwrap();
        assert_eq!(versions["core"], v("3.0.3-rc.1"));
        assert_eq!(versions["zkp"], v("3.0.6-rc.1"));
        assert_eq!(versions["binfmt"], v("3.0.6-rc.1"));
        assert_eq!(versions["other"], v("1.4.3"));
    }

    #[test]
    fn api_additions_need_a_minor() {
        let versions = run(
            &config("3.1.0", &[]),
            vec![krate("zkp", "3.0.5", &[]), krate("povw", "0.4.3", &[])],
            &["zkp", "povw"],
            &[("zkp", Level::Minor), ("povw", Level::Minor)],
        )
        .unwrap();
        assert_eq!(versions["zkp"], v("3.1.0"));
        assert_eq!(versions["povw"], v("0.4.4"));
    }

    #[test]
    fn lockstep_crates_get_the_declared_version() {
        let versions = run(
            &config("3.1.0-rc.1", &["zkvm", "r0vm"]),
            vec![
                krate("zkvm", "3.0.6", &[]),
                krate("r0vm", "3.0.6", &["zkvm"]),
                krate("povw", "0.4.3", &["zkvm"]),
            ],
            &[],
            &[],
        )
        .unwrap();
        assert_eq!(versions["zkvm"], v("3.1.0-rc.1"));
        assert_eq!(versions["r0vm"], v("3.1.0-rc.1"));
        assert_eq!(versions["povw"], v("0.4.4-rc.1"));
    }

    #[test]
    fn lockstep_too_small_for_the_api_fails() {
        let err = run(
            &config("3.0.7", &["zkvm"]),
            vec![krate("zkvm", "3.0.6", &[])],
            &["zkvm"],
            &[("zkvm", Level::Minor)],
        )
        .unwrap_err();
        assert!(err.to_string().contains("needs at least 3.1.0"), "{err}");
    }

    #[test]
    fn breaking_changes_fail() {
        let err = run(
            &config("3.1.0", &[]),
            vec![krate("zkp", "3.0.5", &[])],
            &["zkp"],
            &[("zkp", Level::Major)],
        )
        .unwrap_err();
        assert!(err.to_string().contains("breaking change"), "{err}");
    }

    #[test]
    fn new_crates_keep_their_version_with_the_pre_release() {
        let crates = vec![krate("zkrs", "4.0.6", &[])];
        let rows = decide(
            &config("3.1.0-rc.1", &[]),
            &crates,
            &[("zkrs".to_string(), None)].into_iter().collect(),
            &BTreeMap::new(),
            |_, _| unreachable!(),
        )
        .unwrap();
        assert_eq!(rows[0].new, Some(v("4.0.6-rc.1")));
    }

    #[test]
    fn manifests_compare_without_workspace_versions() {
        let workspace = ["risc0-zkp".to_string()].into_iter().collect();
        let a = br#"
[package]
name = "risc0-binfmt"
version = "3.0.5"
[dependencies.risc0-zkp]
version = "3.0.5"
default-features = false
[dependencies.serde]
version = "1.0"
"#;
        let b = br#"
[package]
name = "risc0-binfmt"
version = "3.0.6-rc.1"
[dependencies.risc0-zkp]
version = "3.0.6-rc.1"
default-features = false
[dependencies.serde]
version = "1.0"
"#;
        let c = br#"
[package]
name = "risc0-binfmt"
version = "3.0.6-rc.1"
[dependencies.risc0-zkp]
version = "3.0.6-rc.1"
default-features = false
[dependencies.serde]
version = "1.1"
"#;
        assert_eq!(
            normalize_manifest(a, &workspace).unwrap(),
            normalize_manifest(b, &workspace).unwrap()
        );
        assert_ne!(
            normalize_manifest(a, &workspace).unwrap(),
            normalize_manifest(c, &workspace).unwrap()
        );
    }

    #[test]
    fn index_paths() {
        assert_eq!(index_path("a"), "1/a");
        assert_eq!(index_path("ab"), "2/ab");
        assert_eq!(index_path("abc"), "3/a/abc");
        assert_eq!(index_path("risc0-zkvm"), "ri/sc/risc0-zkvm");
    }
}
