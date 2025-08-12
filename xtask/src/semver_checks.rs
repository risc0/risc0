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

//! Runs `cargo-semver-checks` on the crates in the workspace found in the current directory.
//! Additionally, for any crates which have the same version as their baseline, we check if it has
//! changed at all. This is done by running `cargo publish` on the crate and comparing the output
//! to what `crates.io` has for the baseline. If changes are detected, we require a bump in the
//! patch version of the crate.

use anyhow::{anyhow, bail, Context as _, Result};
use cargo_semver_checks::{Check, GlobalConfig, Rustdoc};
use clap::Parser;
use semver::{Version, VersionReq};
use serde::{Deserialize, Serialize};
use serde_with::{serde_as, DisplayFromStr};
use tempfile::tempdir;

use std::collections::{BTreeMap, BTreeSet};
use std::fmt;
use std::io::Write;
use std::path::{Path, PathBuf};
use std::process::{Command, Stdio};
use std::str::FromStr;

#[derive(Parser)]
pub struct SemverChecks {
    /// Error if there is a difference between the existing `semver-baselines.lock` and what was
    /// checked.
    #[arg(long)]
    locked: bool,

    /// Ignore the existing `semver-baselines.lock`
    #[arg(long)]
    update: bool,
}

/// Sends all writes into the given channel.
struct ChannelWriter(std::sync::mpsc::Sender<Vec<u8>>);

impl Write for ChannelWriter {
    fn write(&mut self, buf: &[u8]) -> std::io::Result<usize> {
        let _ = self.0.send(buf.to_owned());
        Ok(buf.len())
    }

    fn flush(&mut self) -> std::io::Result<()> {
        Ok(())
    }
}

/// Lets writes go to the `print` call which can be captured by the test fixture.
struct PrintStdout;

impl Write for PrintStdout {
    fn write(&mut self, buf: &[u8]) -> std::io::Result<usize> {
        print!(
            "{}",
            std::str::from_utf8(buf).expect("cargo-semver-checks should output valid UTF-8")
        );
        Ok(buf.len())
    }

    fn flush(&mut self) -> std::io::Result<()> {
        Ok(())
    }
}

/// Receive output from `ChannelWriter`, echos them to `eprint` calls and also saves the output and
/// returns it.
fn tee_semver_output(recv: std::sync::mpsc::Receiver<Vec<u8>>) -> Vec<u8> {
    let mut output = vec![];
    while let Ok(chunk) = recv.recv() {
        output.extend(&chunk[..]);
        // Use `eprint` instead of `std::io::stderr()` so the tests can capture the output.
        eprint!(
            "{}",
            std::str::from_utf8(&chunk[..]).expect("cargo-semver-checks should output valid UTF-8")
        );
    }
    output
}

/// See [`SemverOutput`]
#[derive(Debug, Clone, PartialEq, Eq)]
struct VersionPair {
    current: Version,
    baseline: Version,
}

/// Used in the parsing code of [`SemverOutput`]
#[derive(Default)]
struct OptionalVersionPair {
    current: Option<Version>,
    baseline: Option<Version>,
}

impl TryFrom<OptionalVersionPair> for VersionPair {
    type Error = anyhow::Error;

    fn try_from(p: OptionalVersionPair) -> Result<Self> {
        Ok(Self {
            current: p
                .current
                .ok_or_else(|| anyhow!("missing current version"))?,
            baseline: p
                .baseline
                .ok_or_else(|| anyhow!("missing baseline version"))?,
        })
    }
}

/// Parsed output from `cargo-semver-checks`. Right now it just picks up the "current" and
/// "baseline" versions for any crates that it checks.
///
/// If `cargo-semver-checks` gave some programmatic way to get this information we wouldn't need to
/// parse it ourselves.
#[derive(Debug, Default, Clone, PartialEq, Eq)]
struct SemverOutput {
    crate_versions: BTreeMap<String, VersionPair>,
}

impl SemverOutput {
    /// Parse from output from `cargo-semver-checks`
    fn parse(s: &str) -> Result<Self> {
        let mut crate_versions: BTreeMap<String, OptionalVersionPair> = BTreeMap::new();

        for line in s.lines() {
            if let Some(contents) = line.trim().strip_prefix("Parsing ") {
                let parts = contents.split(" ").collect::<Vec<_>>();
                if parts.len() < 3 {
                    bail!("unexpected cargo-semver-checks output line: {line:?}");
                }
                let crate_name = parts[0].into();
                let version =
                    Version::parse(parts[1].strip_prefix("v").context("version missing 'v'")?)?;
                let rest = parts[2..].join(" ");
                if rest.contains("baseline") {
                    crate_versions.entry(crate_name).or_default().baseline = Some(version);
                } else {
                    crate_versions.entry(crate_name).or_default().current = Some(version);
                }
            }
        }

        Ok(Self {
            crate_versions: crate_versions
                .into_iter()
                .map(|(k, v)| Ok((k, v.try_into().context("{k} missing version")?)))
                .collect::<Result<_>>()?,
        })
    }

    fn extend(&mut self, other: Self) {
        self.crate_versions.extend(other.crate_versions)
    }
}

/// Run `cargo-semver-checks` on the given packages.
/// It captures, parses, and returns the output.
fn run_semver_checks(
    workspace_root: &Path,
    baseline: Rustdoc,
    packages: Vec<String>,
) -> Result<SemverOutput> {
    let (send, recv) = std::sync::mpsc::channel();

    let (report, output) = std::thread::scope(move |scope| -> Result<_> {
        let thread_handle = scope.spawn(|| tee_semver_output(recv));

        let report = {
            let mut config = GlobalConfig::new();
            config.set_log_level(Some(log::Level::Info));
            config.set_stderr(Box::new(ChannelWriter(send)));
            config.set_stdout(Box::new(PrintStdout));

            Check::new(Rustdoc::from_root(workspace_root))
                .set_baseline(baseline)
                .with_default_features()
                .set_packages(packages)
                .check_release(&mut config)?
        };
        Ok((report, thread_handle.join().unwrap()))
    })?;

    if !report.success() {
        bail!("SemVer checks failed. Minor or major version bump required.");
    }

    SemverOutput::parse(&String::from_utf8(output)?)
}

/// Use `cargo vendor` as an easy way to gain access to the source code of the crates we care
/// about.
fn vendor_packages(
    cargo_vendor: impl FnOnce(&Path) -> Result<()>,
    tempdir: &tempfile::TempDir,
    packages: &[(String, Version)],
) -> Result<PathBuf> {
    let project_dir = tempdir.path();
    let mut cargo_toml_contents = String::new();
    cargo_toml_contents += "[package]\n";
    cargo_toml_contents += "name = \"placeholder-project\"\n";
    cargo_toml_contents += "[dependencies]\n";
    for (package, version) in packages {
        cargo_toml_contents += &format!("{package} = \"={version}\"\n");
    }
    std::fs::write(project_dir.join("Cargo.toml"), &cargo_toml_contents)?;
    std::fs::create_dir(project_dir.join("src"))?;
    std::fs::write(project_dir.join("src/lib.rs"), "")?;
    cargo_vendor(project_dir)?;
    Ok(project_dir.join("vendor"))
}

/// Runs some command, checks for errors, and forwards output from stdout / stderr to `print and
/// `eprint` which allows the test fixture to capture the output.
fn run_command(cmd: &mut Command, error_message: &str) -> Result<()> {
    let context = format!(
        "failure running `{}`",
        cmd.get_program().to_str().unwrap_or("<unknown>")
    );
    let output = cmd
        .stdout(Stdio::piped())
        .stderr(Stdio::piped())
        .output()
        .with_context(move || context)?;

    if !output.status.success() {
        // Outputting like this allows the test code to capture the output
        let stdout_str =
            std::str::from_utf8(&output.stdout).context("command produced invalid UTF-8 output")?;
        print!("{stdout_str}",);
        let stderr_str =
            std::str::from_utf8(&output.stderr).context("command produced invalid UTF-8 output")?;
        eprint!("{stderr_str}",);

        bail!("{error_message}");
    }
    Ok(())
}

fn compare_published_package_to_vendored_version(
    workspace_root: &Path,
    package: &String,
    version: &Version,
    vendored_packages: &Path,
) -> Result<(), anyhow::Error> {
    println!(
        "Comparing {package} v{version} to crates.io version \
        to see if it needs a patch version bump"
    );

    // Have cargo package up the package for publishing
    run_command(
        Command::new("cargo")
            .args([
                "publish",
                "--allow-dirty",
                "--dry-run",
                "--package",
                package,
            ])
            .current_dir(workspace_root),
        &format!(
            "Failed to create publishable version of {package}. \
            Patch version bump likely required."
        ),
    )?;
    let published_crate = workspace_root.join(format!("target/package/{package}-{version}"));

    // When publishing locally cargo will create this directory, it doesn't exist on crates stored
    // in `crates.io`
    let target_dir = published_crate.join("target");
    if target_dir.exists() {
        std::fs::remove_dir_all(&target_dir)
            .with_context(|| format!("failed to delete {target_dir:?}"))?;
    }

    // Run diff on the vendored package from crates.io and the local package
    run_command(
        Command::new("diff")
            .arg("-r")
            // This exists only in vendored crates
            .args(["-x", ".cargo-checksum.json"])
            // We don't want lockfile changes to require a new release, its too volatile
            .args(["-x", "Cargo.lock"])
            // This is only informational and doesn't affect behavior
            .args(["-x", "Cargo.toml.orig"])
            // This contains information about the commit it was published from
            .args(["-x", ".cargo_vcs_info.json"])
            .arg(vendored_packages.join(package))
            .arg(published_crate),
        &format!(
            "Differences found between published {package} and local version. \
            Patch version bump required."
        ),
    )?;

    Ok(())
}

fn combine_errors(errors: Vec<anyhow::Error>, message: &str) -> Result<()> {
    if errors.is_empty() {
        return Ok(());
    }

    let div = std::iter::repeat_n("=", message.len() + 1)
        .collect::<Vec<_>>()
        .join("");
    let mut message = format!("{div}\n{message}:\n{div}\n");
    for (n, error) in errors.iter().enumerate() {
        message += &format!("{}. {error}\n", n + 1);
    }

    bail!("{}", message);
}

/// Compare all the given packages with their crates.io versions to see if they differ
fn check_for_patch_version_bump(
    workspace_root: &Path,
    vendored_packages: &Path,
    packages: &[(String, Version)],
) -> Result<()> {
    let mut errors = vec![];
    for (package, version) in packages {
        let res = compare_published_package_to_vendored_version(
            workspace_root,
            package,
            version,
            vendored_packages,
        );

        if let Err(error) = res {
            errors.push(error);
        }
    }

    combine_errors(errors, "Patch version bump check issues")?;

    Ok(())
}

/// XXX remi: This is a kind-of lame way of comparing these things.
fn version_req_bumps_major(before: &VersionReq, after: &VersionReq) -> Result<bool> {
    if before.comparators.len() != 1 || after.comparators.len() != 1 {
        bail!("version requirement too complicated for current understanding");
    }
    for op in [before.comparators[0].op, after.comparators[0].op] {
        if op != semver::Op::Caret {
            bail!("version requirement uses unsupported operator: {op:?}");
        }
    }
    Ok(before.comparators[0].major != after.comparators[0].major)
}

fn check_for_major_version_bump_due_to_version_req_in_single_package(
    packages: &BTreeMap<String, cargo_metadata::Package>,
    package_name: &str,
    vendor_packages: &Path,
) -> Result<()> {
    println!(
        "Comparing {package_name} dependencies with crates.io version dependencies \
        to see if it needs a major version bump"
    );

    let current_package = packages
        .get(package_name)
        .ok_or_else(|| anyhow!("package {package_name} missing from workspace metadata"))?;

    let baseline_metadata = cargo_metadata::MetadataCommand::new()
        .current_dir(vendor_packages.join(package_name))
        .exec()
        .context("failed to run `cargo metadata`")?;
    let baseline_package = baseline_metadata
        .packages
        .iter()
        .find(|p| p.name.as_str() == package_name)
        .ok_or_else(|| anyhow!("vendored crate missing any package"))?;

    let mut problem_deps = vec![];
    for current_dep in &current_package.dependencies {
        let current_dep_name = &current_dep.name;
        if !packages.contains_key(current_dep_name) {
            // only consider dependencies to other workspace crates
            continue;
        }

        if current_dep.kind == cargo_metadata::DependencyKind::Development {
            // don't consider dev-dependencies, they are only used to build tests and benchmarks
            continue;
        }

        let Some(baseline_dep) = baseline_package
            .dependencies
            .iter()
            .filter(|dep| dep.kind != cargo_metadata::DependencyKind::Development)
            .find(|dep| &dep.name == current_dep_name)
        else {
            // baseline package doesn't have this dependency
            continue;
        };

        if version_req_bumps_major(&baseline_dep.req, &current_dep.req)
            .with_context(|| format!("failed to parse version requirement for {package_name}"))?
        {
            problem_deps.push(format!(
                "{current_dep_name}: {} -> {}",
                baseline_dep.req, current_dep.req
            ));
        }
    }

    if !problem_deps.is_empty() {
        bail!(
            "Package {package_name} has a major change in version requirement in dependencies: {}",
            problem_deps.join(", ")
        );
    }

    Ok(())
}

/// Compare the given package's version requirements with their crates.io versions. If any of the
/// packages have a bump of a version requirement for another risc0 crate, we need to make sure
/// that crates has also had a major version bump.
fn check_for_major_version_bump_due_to_version_req(
    baseline_package_without_breaking_changes: &Vec<String>,
    packages: &BTreeMap<String, cargo_metadata::Package>,
    vendor_packages: &Path,
) -> Result<()> {
    let mut errors = vec![];
    for package_name in baseline_package_without_breaking_changes {
        let res = check_for_major_version_bump_due_to_version_req_in_single_package(
            packages,
            package_name,
            vendor_packages,
        );
        if let Err(error) = res {
            errors.push(error);
        }
    }

    combine_errors(
        errors,
        "Major version bump version requirement change issues",
    )?;

    Ok(())
}

/// Find packages in the workspace that don't have `release = false` and have a `lib` target
fn find_publishable_packages_with_lib(
    workspace_root: &Path,
) -> Result<BTreeMap<String, cargo_metadata::Package>> {
    let metadata = cargo_metadata::MetadataCommand::new()
        .current_dir(workspace_root)
        .exec()
        .context("failed to run `cargo metadata`")?;

    let mut packages = BTreeMap::new();
    for package in metadata.workspace_default_packages() {
        // check for package.metadata.release.release = false
        if let Some(release_metadata) = package.metadata.get("release") {
            if let Some(release_flag) = release_metadata.get("release") {
                if release_flag.as_bool().is_some_and(|v| !v) {
                    continue;
                }
            }
        }

        // check if package has a `lib` target (semver won't run on non-libraries)
        if !package.targets.iter().any(|t| t.is_lib()) {
            continue;
        }

        packages.insert(package.name.to_string(), package.clone());
    }

    Ok(packages)
}

/// Run `cargo vendor` and puts the output in `<path>/vendor`. This is separated out like this so
/// it can be dependency injected.
fn real_cargo_vendor(path: &Path) -> Result<()> {
    run_command(
        Command::new("cargo")
            .current_dir(path)
            .args(["vendor", "vendor"]),
        "cargo vendor failed",
    )?;
    Ok(())
}

#[derive(Debug, PartialEq, Eq)]
enum VersionOrNone {
    Version(Version),
    None,
}

impl VersionOrNone {
    fn as_option(&self) -> Option<&Version> {
        match self {
            Self::Version(v) => Some(v),
            Self::None => None,
        }
    }
}

impl From<Version> for VersionOrNone {
    fn from(v: Version) -> Self {
        Self::Version(v)
    }
}

impl FromStr for VersionOrNone {
    type Err = anyhow::Error;

    fn from_str(s: &str) -> Result<Self> {
        if s == "none" {
            Ok(Self::None)
        } else {
            Ok(Self::Version(Version::parse(s)?))
        }
    }
}

impl fmt::Display for VersionOrNone {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::Version(v) => write!(f, "{v}"),
            Self::None => write!(f, "none"),
        }
    }
}

#[serde_as]
#[derive(Debug, Default, Serialize, Deserialize, PartialEq, Eq)]
struct SemverBaselines {
    #[serde_as(as = "BTreeMap<_, DisplayFromStr>")]
    versions: BTreeMap<String, VersionOrNone>,
}

impl SemverBaselines {
    fn get(&self, name: &str) -> Option<&VersionOrNone> {
        self.versions.get(name)
    }
}

impl fmt::Display for SemverBaselines {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{{")?;

        let mut iter = self.versions.iter();
        if let Some((name, version)) = iter.next() {
            write!(f, "{name}: {version}")?;
            for (name, version) in iter {
                write!(f, ", {name}: {version}")?;
            }
        }

        write!(f, "}}")?;
        Ok(())
    }
}

impl From<SemverOutput> for SemverBaselines {
    fn from(o: SemverOutput) -> Self {
        Self {
            versions: o
                .crate_versions
                .into_iter()
                .map(|(name, version_pair)| (name, version_pair.baseline.into()))
                .collect(),
        }
    }
}

fn read_semver_lock_file(workspace_root: &Path) -> Result<Option<SemverBaselines>> {
    let path = workspace_root.join("semver-baselines.lock");
    if !path.exists() {
        return Ok(None);
    }

    toml::from_str(&std::fs::read_to_string(path).context("failed to read lock-file")?)
        .context("failed to decode lock-file")
}

fn write_semver_lock_file(workspace_root: &Path, baselines: &SemverBaselines) -> Result<()> {
    std::fs::write(
        workspace_root.join("semver-baselines.lock"),
        toml::to_string_pretty(baselines).context("failed to serialize lock-file")?,
    )
    .context("failed to write lock-file")?;
    Ok(())
}

fn semver_compatible(a: &semver::Version, b: &semver::Version) -> bool {
    if !a.pre.is_empty() || !b.pre.is_empty() {
        return false;
    }
    a.major == b.major
}

/// Entrypoint for the tests. See the module doc-comment about what it does.
///
/// `workspace_root`         : The path to the workspace we are checking
/// `semver_baseline_factory`: Constructor for baseline version
/// `cargo_vendor`           : Function that runs `cargo vendor` command. We dependency inject this
///                            for the sake of the tests
fn run_inner(
    args: &SemverChecks,
    workspace_root: &Path,
    mut semver_baseline_factory: impl FnMut(Option<&Version>) -> Rustdoc,
    cargo_vendor: impl FnOnce(&Path) -> Result<()>,
) -> Result<()> {
    let packages = find_publishable_packages_with_lib(workspace_root)?;

    let input_baselines = (!args.update)
        .then(|| read_semver_lock_file(workspace_root))
        .transpose()?
        .flatten()
        .unwrap_or_default();

    let mut skipped_packages = BTreeSet::new();
    let mut semver_output = SemverOutput::default();
    for package in packages.keys() {
        let version = input_baselines.get(package);
        if version.is_some_and(|v| v == &VersionOrNone::None) {
            println!("skipping {package} which has no baseline");
            skipped_packages.insert(package.clone());
            continue;
        }
        let baseline = semver_baseline_factory(version.and_then(|v| v.as_option()));
        let output = run_semver_checks(workspace_root, baseline, vec![package.into()])?;
        semver_output.extend(output);
    }

    let mut output_baselines: SemverBaselines = semver_output.clone().into();
    if !args.update {
        output_baselines.versions.extend(
            skipped_packages
                .into_iter()
                .map(|p| (p, VersionOrNone::None)),
        );
    }
    if args.locked && output_baselines != input_baselines {
        bail!(
            "`--locked` provided and baselines don't match: \
                output != input: {output_baselines} != {input_baselines}"
        );
    }

    write_semver_lock_file(workspace_root, &output_baselines)?;

    let baseline_package_without_breaking_changes = semver_output
        .crate_versions
        .iter()
        .filter_map(|(name, versions)| {
            (semver_compatible(&versions.current, &versions.baseline))
                .then_some((name.clone(), versions.baseline.clone()))
        })
        .collect::<Vec<_>>();

    let tempdir = tempdir().unwrap();
    let vendored_packages = vendor_packages(
        cargo_vendor,
        &tempdir,
        &baseline_package_without_breaking_changes,
    )?;

    let unbumped_packages: Vec<_> = semver_output
        .crate_versions
        .into_iter()
        .filter_map(|(name, versions)| {
            (versions.current == versions.baseline).then_some((name, versions.current))
        })
        .collect();

    if !unbumped_packages.is_empty() {
        check_for_patch_version_bump(workspace_root, &vendored_packages, &unbumped_packages)?;
    }

    check_for_major_version_bump_due_to_version_req(
        &baseline_package_without_breaking_changes
            .into_iter()
            .map(|(p, _)| p)
            .collect(),
        &packages,
        &vendored_packages,
    )?;

    Ok(())
}

impl SemverChecks {
    pub fn run(&self) {
        let current_dir = std::env::current_dir().expect("should be able to get current directory");
        let baseline_factory = |version: Option<&Version>| {
            if let Some(version) = version {
                Rustdoc::from_registry(version.to_string())
            } else {
                Rustdoc::from_registry_latest_crate_version()
            }
        };

        if let Err(e) = run_inner(self, &current_dir, baseline_factory, real_cargo_vendor) {
            panic!("{e}");
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::collections::HashMap;

    #[test]
    fn sermver_output_parsing() {
        let output = SemverOutput::parse(
            "
            Building risc0-foobar v1.4.0 (current)
               Built [   0.379s] (current)
             Parsing risc0-foobar v1.4.0 (current)
              Parsed [   0.003s] (current)
             Parsing risc0-foobar v1.2.5 (baseline, cached)
              Parsed [   0.005s] (baseline)
            Checking risc0-foobar v1.2.5 -> v1.4.0 (minor change)
             Checked [   0.003s] 126 checks: 126 pass, 22 skip
             Summary no semver update required
            Finished [   0.846s] risc0-foobar
            Building risc0-bazbin v1.4.0 (current)
               Built [   3.450s] (current)
             Parsing risc0-bazbin v1.4.0 (current)
              Parsed [   1.037s] (current)
             Parsing risc0-bazbin v1.2.5 (baseline, cached)
              Parsed [   0.634s] (baseline)
            Checking risc0-bazbin v1.2.5 -> v1.4.0 (minor change)
             Checked [   0.008s] 126 checks: 126 pass, 22 skip
             Summary no semver update required
            Finished [   6.204s] risc0-bazbin
        ",
        )
        .unwrap();

        let mut crate_versions = BTreeMap::new();
        crate_versions.insert(
            "risc0-foobar".into(),
            VersionPair {
                current: Version::new(1, 4, 0),
                baseline: Version::new(1, 2, 5),
            },
        );
        crate_versions.insert(
            "risc0-bazbin".into(),
            VersionPair {
                current: Version::new(1, 4, 0),
                baseline: Version::new(1, 2, 5),
            },
        );
        assert_eq!(output, SemverOutput { crate_versions })
    }

    fn write_cargo_toml(
        path: &Path,
        name: &str,
        version: &Version,
        dependencies: &HashMap<String, String>,
        dev_dependencies: &HashMap<String, String>,
    ) {
        let mut contents = format!(
            "\
            [package]\n\
            name = \"{name}\"\n\
            version = \"{version}\"\n\
            "
        );
        if !dependencies.is_empty() {
            contents += &format!(
                "[dependencies]\n{}",
                dependencies
                    .iter()
                    .map(|(k, v)| format!("{k} = {v}\n"))
                    .collect::<Vec<_>>()
                    .join("")
            )
        }
        if !dev_dependencies.is_empty() {
            contents += &format!(
                "[dev-dependencies]\n{}",
                dev_dependencies
                    .iter()
                    .map(|(k, v)| format!("{k} = {v}\n"))
                    .collect::<Vec<_>>()
                    .join("")
            )
        }
        std::fs::write(path.join("Cargo.toml"), contents).unwrap();
    }

    fn publish_baseline_crate(
        tempdir: &tempfile::TempDir,
        baseline_name: &str,
        baseline_version: &Version,
        crate_name: &str,
    ) {
        // Create a published version of the baseline like what would exist on `crates.io` and save
        // it so we can move it into place in our test version of `cargo vendor`
        assert!(Command::new("cargo")
            .args([
                "publish",
                "--allow-dirty",
                "--dry-run",
                "--package",
                crate_name
            ])
            .current_dir(tempdir.path().join(baseline_name))
            .stdout(Stdio::null())
            .stderr(Stdio::null())
            .status()
            .unwrap()
            .success());

        // Locally published crates have this directory, but not ones on `crates.io`
        let published_crate = tempdir
            .path()
            .join(baseline_name)
            .join(format!("target/package/{crate_name}-{baseline_version}"));
        std::fs::remove_dir_all(published_crate.join("target")).unwrap();

        let published_baseline = tempdir
            .path()
            .join(format!("published_{baseline_name}_{crate_name}"));
        std::fs::rename(
            tempdir
                .path()
                .join(baseline_name)
                .join("target/package")
                .join(format!("{crate_name}-{baseline_version}")),
            &published_baseline,
        )
        .unwrap();
    }

    struct CrateSpec {
        name: String,
        contents: String,
        version: Version,
        dev_dependencies: HashMap<String, String>,
        dependencies: HashMap<String, String>,
    }

    impl CrateSpec {
        fn new(name: &str, contents: &str, version: Version) -> Self {
            Self {
                name: name.into(),
                contents: contents.into(),
                version,
                dev_dependencies: HashMap::new(),
                dependencies: HashMap::new(),
            }
        }

        fn with_dep(mut self, key: &str, value: &str, dev_dep: bool) -> Self {
            if dev_dep {
                self.dev_dependencies.insert(key.into(), value.into());
            } else {
                self.dependencies.insert(key.into(), value.into());
            }
            self
        }
    }

    fn create_baseline(tempdir: &tempfile::TempDir, baseline_name: &str, crates: &[CrateSpec]) {
        std::fs::create_dir_all(tempdir.path().join(baseline_name)).unwrap();
        std::fs::write(
            tempdir.path().join(baseline_name).join("Cargo.toml"),
            format!(
                "
                [workspace]
                members = [{}]
                resolve = \"2\"
                ",
                crates
                    .iter()
                    .map(|c| format!("\"{}\"", &c.name))
                    .collect::<Vec<_>>()
                    .join(", ")
            ),
        )
        .unwrap();

        for c in crates {
            let crate_path = tempdir.path().join(baseline_name).join(&c.name);
            std::fs::create_dir_all(crate_path.join("src")).unwrap();
            write_cargo_toml(
                &crate_path,
                &c.name,
                &c.version,
                &c.dependencies,
                &c.dev_dependencies,
            );
            std::fs::write(crate_path.join("src/lib.rs"), &c.contents).unwrap();
        }

        for c in crates {
            publish_baseline_crate(tempdir, baseline_name, &c.version, &c.name);
        }
    }

    fn create_current(tempdir: &tempfile::TempDir, crates: &[CrateSpec]) {
        std::fs::create_dir_all(tempdir.path().join("current")).unwrap();
        std::fs::write(
            tempdir.path().join("current").join("Cargo.toml"),
            format!(
                "
                [workspace]
                members = [{}]
                resolve = \"2\"
                ",
                crates
                    .iter()
                    .map(|c| format!("\"{}\"", &c.name))
                    .collect::<Vec<_>>()
                    .join(", ")
            ),
        )
        .unwrap();

        for c in crates {
            let crate_path = tempdir.path().join("current").join(&c.name);
            std::fs::create_dir_all(crate_path.join("src")).unwrap();
            write_cargo_toml(
                &crate_path,
                &c.name,
                &c.version,
                &c.dependencies,
                &c.dev_dependencies,
            );
            std::fs::write(crate_path.join("src/lib.rs"), &c.contents).unwrap();
        }
    }

    fn run_with_temp_dir(
        tempdir: &tempfile::TempDir,
        latest_baseline: &str,
        update: bool,
        locked: bool,
    ) -> Result<()> {
        let args = SemverChecks { update, locked };
        run_inner(
            &args,
            &tempdir.path().join("current"),
            |passed_version| {
                if let Some(version) = passed_version {
                    Rustdoc::from_root(tempdir.path().join(format!("baseline_{version}")))
                } else {
                    Rustdoc::from_root(tempdir.path().join(latest_baseline))
                }
            },
            |d| {
                // This is our test version of `cargo vendor`
                let cargo_toml: toml::Value =
                    toml::from_str(&std::fs::read_to_string(d.join("Cargo.toml")).unwrap())
                        .unwrap();
                let deps = cargo_toml.get("dependencies").unwrap();

                for (dep_name, dep_value) in deps.as_table().unwrap() {
                    let published_baseline = tempdir.path().join(format!(
                        "published_baseline_{}_{dep_name}",
                        dep_value.as_str().unwrap().strip_prefix("=").unwrap()
                    ));

                    std::fs::create_dir_all(d.join("vendor")).unwrap();

                    let dep_path = d.join("vendor").join(dep_name);
                    let cp_status = Command::new("cp")
                        .arg("-r")
                        .args([&published_baseline, &dep_path])
                        .status()
                        .unwrap();
                    assert!(
                        cp_status.success(),
                        "cp -r {} {}: failed",
                        published_baseline.display(),
                        dep_path.display()
                    );
                    std::fs::write(dep_path.join(".cargo-checksum.json"), "").unwrap();
                }

                Ok(())
            },
        )
    }

    /// Writes out a project twice with one crate called "foobar". Runs checks on the two versions
    /// with one being the "baseline" and the other being the "current" version.
    fn test_run(
        tempdir: &tempfile::TempDir,
        baseline_contents: &str,
        baseline_version: Version,
        current_contents: &str,
        current_version: Version,
    ) -> Result<()> {
        create_current(
            tempdir,
            &[CrateSpec::new("foobar", current_contents, current_version)][..],
        );
        let baseline_name = format!("baseline_{baseline_version}");

        create_baseline(
            tempdir,
            &baseline_name,
            &[CrateSpec::new(
                "foobar",
                baseline_contents,
                baseline_version,
            )],
        );
        run_with_temp_dir(
            tempdir,
            &baseline_name,
            false, /* update */
            false, /* locked */
        )
    }

    #[test]
    fn no_change_passes() {
        let tempdir = tempdir().unwrap();
        test_run(
            &tempdir,
            "pub fn foo() {}",
            Version::new(1, 0, 0),
            "pub fn foo() {}",
            Version::new(1, 0, 0),
        )
        .unwrap();
    }

    #[test]
    fn patch_change_fails() {
        let tempdir = tempdir().unwrap();
        assert_eq!(
            test_run(
                &tempdir,
                "pub fn foo() {}",
                Version::new(1, 0, 0),
                "pub fn foo() { /*hello*/ }",
                Version::new(1, 0, 0),
            )
            .unwrap_err()
            .to_string(),
            "================================\n\
             Patch version bump check issues:\n\
             ================================\n\
             1. Differences found between published foobar and local version. \
                Patch version bump required.\n"
        );
    }

    #[test]
    fn patch_change_passes() {
        let tempdir = tempdir().unwrap();
        test_run(
            &tempdir,
            "pub fn foo() {}",
            Version::new(1, 0, 0),
            "pub fn foo() { /*hello*/ }",
            Version::new(1, 0, 1),
        )
        .unwrap();
    }

    #[test]
    fn minor_change_fails() {
        let tempdir = tempdir().unwrap();
        assert_eq!(
            test_run(
                &tempdir,
                "pub fn foo() {}",
                Version::new(1, 0, 0),
                "#[deprecated] pub fn foo() {}",
                Version::new(1, 0, 0),
            )
            .unwrap_err()
            .to_string(),
            "SemVer checks failed. Minor or major version bump required."
        );
    }

    #[test]
    fn minor_change_passes() {
        let tempdir = tempdir().unwrap();
        test_run(
            &tempdir,
            "pub fn foo() {}",
            Version::new(1, 0, 0),
            "#[deprecated] pub fn foo() {}",
            Version::new(1, 1, 0),
        )
        .unwrap();
    }

    #[test]
    fn major_change_fails() {
        let tempdir = tempdir().unwrap();
        assert_eq!(
            test_run(
                &tempdir,
                "pub fn foo() {}",
                Version::new(1, 0, 0),
                "pub fn foo(_a: u32) {}",
                Version::new(1, 0, 0),
            )
            .unwrap_err()
            .to_string(),
            "SemVer checks failed. Minor or major version bump required."
        );
    }

    #[test]
    fn major_change_passes() {
        let tempdir = tempdir().unwrap();
        test_run(
            &tempdir,
            "pub fn foo() {}",
            Version::new(1, 0, 0),
            "pub fn foo(_a: u32) {}",
            Version::new(2, 0, 0),
        )
        .unwrap();
    }

    #[allow(clippy::too_many_arguments)]
    fn lock_file_test(
        baseline1_contents: &str,
        baseline1_version: Version,
        baseline2_contents: &str,
        baseline2_version: Version,
        current_contents: &str,
        current_version: Version,
        update: bool,
        locked: bool,
    ) -> Result<()> {
        let tempdir = tempdir().unwrap();

        create_current(
            &tempdir,
            &[CrateSpec::new("foobar", current_contents, current_version)][..],
        );

        let baseline1_name = format!("baseline_{baseline1_version}");
        create_baseline(
            &tempdir,
            &baseline1_name,
            &[CrateSpec::new(
                "foobar",
                baseline1_contents,
                baseline1_version,
            )][..],
        );

        // Run once to populate the lock-file
        run_with_temp_dir(
            &tempdir,
            &baseline1_name,
            false, /* update */
            false, /* locked */
        )
        .unwrap();

        // Add a new baseline, if not for the lock-file keeping it comparing to the old baseline,
        // it would cause an error.
        let baseline2_name = format!("baseline_{baseline2_version}");
        create_baseline(
            &tempdir,
            &baseline2_name,
            &[CrateSpec::new(
                "foobar",
                baseline2_contents,
                baseline2_version,
            )][..],
        );

        run_with_temp_dir(&tempdir, &baseline2_name, update, locked)
    }

    #[test]
    fn lock_file_test_major_bump() {
        lock_file_test(
            "pub fn foo() {}",
            Version::new(1, 0, 0),
            "pub fn foo(_a: u32) {}",
            Version::new(2, 1, 0),
            "pub fn foo(_a: u32, _b: u32) {}",
            Version::new(2, 0, 0),
            false, /* update */
            false, /* locked */
        )
        .unwrap()
    }

    #[test]
    fn lock_file_test_major_bump_update() {
        assert_eq!(
            lock_file_test(
                "pub fn foo() {}",
                Version::new(1, 0, 0),
                "pub fn foo(_a: u32) {}",
                Version::new(2, 1, 0),
                "pub fn foo(_a: u32, _b: u32) {}",
                Version::new(2, 0, 0),
                true,  /* update */
                false, /* locked */
            )
            .unwrap_err()
            .to_string(),
            "SemVer checks failed. Minor or major version bump required."
        );
    }

    #[test]
    fn lock_file_test_new_version_update_locked() {
        assert_eq!(
            lock_file_test(
                "pub fn foo() {}",
                Version::new(1, 0, 0),
                "pub fn foo(_a: u32) {}",
                Version::new(2, 1, 0),
                "pub fn foo(_a: u32) {}",
                Version::new(2, 0, 0),
                true, /* update */
                true, /* locked */
            )
            .unwrap_err()
            .to_string(),
            "`--locked` provided and baselines don't match: output != input: {foobar: 2.1.0} != {}"
        );
    }

    #[test]
    fn lock_file_test_locked_no_change() {
        lock_file_test(
            "pub fn foo() {}",
            Version::new(1, 0, 0),
            "pub fn foo(_a: u32) {}",
            Version::new(2, 1, 0),
            "pub fn foo(_a: u32) {}",
            Version::new(2, 0, 0),
            false, /* update */
            true,  /* locked */
        )
        .unwrap();
    }

    #[test]
    fn lock_file_test_patch_bump() {
        lock_file_test(
            "pub fn foo() {}",
            Version::new(1, 0, 0),
            "pub fn foo(_a: u32) {}",
            Version::new(1, 0, 1),
            "pub fn foo() {}",
            Version::new(1, 0, 1),
            false, /* update */
            false, /* locked */
        )
        .unwrap()
    }

    #[test]
    fn locked_fails_due_to_empty_lockfile() {
        let tempdir = tempdir().unwrap();

        create_current(
            &tempdir,
            &[CrateSpec::new(
                "foobar",
                "pub fn foo() {}",
                Version::new(2, 0, 0),
            )][..],
        );

        let baseline1_version = Version::new(1, 0, 0);
        let baseline1_name = format!("baseline_{baseline1_version}");
        create_baseline(
            &tempdir,
            &baseline1_name,
            &[CrateSpec::new(
                "foobar",
                "pub fn foo(_a: u32) {}",
                baseline1_version,
            )][..],
        );

        assert_eq!(
            run_with_temp_dir(
                &tempdir,
                &baseline1_name,
                false, /* update */
                true,  /* locked */
            )
            .unwrap_err()
            .to_string(),
            "`--locked` provided and baselines don't match: output != input: {foobar: 1.0.0} != {}"
        );
    }

    #[test]
    fn add_new_crate() {
        let tempdir = tempdir().unwrap();

        create_current(
            &tempdir,
            &[CrateSpec::new(
                "foobar",
                "pub fn foo() {}",
                Version::new(2, 0, 0),
            )][..],
        );

        let baseline1_version = Version::new(1, 0, 0);
        let baseline1_name = format!("baseline_{baseline1_version}");
        create_baseline(
            &tempdir,
            &baseline1_name,
            &[CrateSpec::new(
                "foobar",
                "pub fn foo(_a: u32) {}",
                baseline1_version,
            )][..],
        );

        // Run once to populate the lock-file
        run_with_temp_dir(
            &tempdir,
            &baseline1_name,
            false, /* update */
            false, /* locked */
        )
        .unwrap();

        // Add a new crate
        std::fs::write(
            tempdir.path().join("current").join("Cargo.toml"),
            "
            [workspace]
            members = [\"foobar\", \"baz\"]
            resolve = \"2\"
            ",
        )
        .unwrap();

        // mark the new crate's baseline as "none"
        let mut f = std::fs::OpenOptions::new()
            .append(true)
            .open(tempdir.path().join("current/semver-baselines.lock"))
            .unwrap();
        write!(f, "\nbaz = \"none\"").unwrap();
        drop(f);

        let current_baz = tempdir.path().join("current/baz");
        std::fs::create_dir_all(current_baz.join("src")).unwrap();
        write_cargo_toml(
            &current_baz,
            "baz",
            &Version::new(1, 0, 0),
            &HashMap::new(),
            &HashMap::new(),
        );
        std::fs::write(current_baz.join("src/lib.rs"), "pub fn baz() {}").unwrap();

        run_with_temp_dir(
            &tempdir,
            &baseline1_name,
            false, /* update */
            true,  /* locked */
        )
        .unwrap();
    }

    #[test]
    fn update_with_new_crate() {
        let tempdir = tempdir().unwrap();

        create_current(
            &tempdir,
            &[CrateSpec::new(
                "foobar",
                "pub fn foo() {}",
                Version::new(2, 0, 0),
            )][..],
        );

        let baseline1_version = Version::new(1, 0, 0);
        let baseline1_name = format!("baseline_{baseline1_version}");
        create_baseline(
            &tempdir,
            &baseline1_name,
            &[CrateSpec::new(
                "foobar",
                "pub fn foo(_a: u32) {}",
                baseline1_version.clone(),
            )][..],
        );

        // Run once to populate the lock-file
        run_with_temp_dir(
            &tempdir,
            &baseline1_name,
            false, /* update */
            false, /* locked */
        )
        .unwrap();

        // Add a new crate
        std::fs::write(
            tempdir.path().join("current").join("Cargo.toml"),
            "
            [workspace]
            members = [\"foobar\", \"baz\"]
            resolve = \"2\"
            ",
        )
        .unwrap();

        // mark the new crate's baseline as "none"
        let mut f = std::fs::OpenOptions::new()
            .append(true)
            .open(tempdir.path().join("current/semver-baselines.lock"))
            .unwrap();
        write!(f, "\nbaz = \"none\"").unwrap();
        drop(f);

        let current_baz = tempdir.path().join("current/baz");
        std::fs::create_dir_all(current_baz.join("src")).unwrap();
        write_cargo_toml(
            &current_baz,
            "baz",
            &Version::new(1, 0, 0),
            &HashMap::new(),
            &HashMap::new(),
        );
        std::fs::write(current_baz.join("src/lib.rs"), "pub fn baz() {}").unwrap();

        // create baseline version of baz
        std::fs::write(
            tempdir.path().join(&baseline1_name).join("Cargo.toml"),
            "
            [workspace]
            members = [\"foobar\", \"baz\"]
            resolve = \"2\"
            ",
        )
        .unwrap();

        let baseline_baz = tempdir.path().join(&baseline1_name).join("baz");
        std::fs::create_dir_all(baseline_baz.join("src")).unwrap();
        write_cargo_toml(
            &baseline_baz,
            "baz",
            &baseline1_version,
            &HashMap::new(),
            &HashMap::new(),
        );
        std::fs::write(baseline_baz.join("src/lib.rs"), "pub fn baz() {}").unwrap();

        publish_baseline_crate(&tempdir, &baseline1_name, &baseline1_version, "baz");

        run_with_temp_dir(
            &tempdir,
            &baseline1_name,
            true,  /* update */
            false, /* locked */
        )
        .unwrap();
        let baselines = read_semver_lock_file(&tempdir.path().join("current"))
            .unwrap()
            .unwrap();

        let mut expected = SemverBaselines::default();
        expected
            .versions
            .insert("foobar".into(), Version::new(1, 0, 0).into());
        expected
            .versions
            .insert("baz".into(), Version::new(1, 0, 0).into());
        assert_eq!(baselines, expected);
    }

    fn dependency_version_check_test(
        serde_version: Version,
        baseline_has_dep: bool,
        current_dev_dep: bool,
        baseline_dev_dep: bool,
    ) -> Result<()> {
        let tempdir = tempdir().unwrap();

        create_current(
            &tempdir,
            &[
                CrateSpec::new("foobar", "pub fn foo() {}", Version::new(1, 0, 1))
                    .with_dep("syn", "\"2.0.0\"", false /* dev_dep */)
                    .with_dep(
                        "serde",
                        &format!("{{ version = \"{serde_version}\", path = \"../serde\" }}"),
                        current_dev_dep,
                    ),
                CrateSpec::new("serde", "pub fn baz() {}", serde_version),
            ][..],
        );

        let baseline_version = Version::new(1, 0, 0);
        let baseline_name = format!("baseline_{baseline_version}");

        let mut baseline_foobar = CrateSpec::new(
            "foobar",
            "pub fn foo() {}",
            baseline_version.clone(),
        )
        .with_dep("syn", "\"1.0.0\"", false /* dev_dep */);
        if baseline_has_dep {
            baseline_foobar = baseline_foobar.with_dep(
                "serde",
                "{ version = \"1.0.0\", path = \"../serde\" }",
                baseline_dev_dep,
            );
        }
        create_baseline(
            &tempdir,
            &baseline_name,
            &[
                baseline_foobar,
                CrateSpec::new("serde", "pub fn baz() {}", baseline_version),
            ][..],
        );

        run_with_temp_dir(
            &tempdir,
            &baseline_name,
            false, /* update */
            false, /* locked */
        )
    }

    #[test]
    fn version_req_dependency_check_passes_patch_version_bump() {
        dependency_version_check_test(
            Version::new(1, 0, 1),
            true,  /* baseline_has_dep */
            false, /* current_dev_dep */
            false, /* baseline_dev_dep */
        )
        .unwrap();
    }

    #[test]
    fn version_req_dependency_check_passes_minor_version_bump() {
        dependency_version_check_test(
            Version::new(1, 1, 0),
            true,  /* baseline_has_dep */
            false, /* current_dev_dep */
            false, /* baseline_dev_dep */
        )
        .unwrap();
    }

    #[test]
    fn version_req_dependency_check_passes_major_version_bump_but_new_dependency() {
        dependency_version_check_test(
            Version::new(2, 0, 0),
            false, /* baseline_has_dep */
            false, /* current_dev_dep */
            false, /* baseline_dev_dep */
        )
        .unwrap();
    }

    #[test]
    fn version_req_dependency_check_fails() {
        let err = dependency_version_check_test(
            Version::new(2, 0, 0),
            true,  /* baseline_has_dep */
            false, /* current_dev_dep */
            false, /* baseline_dev_dep */
        )
        .unwrap_err();
        assert_eq!(
            err.to_string(),
            "\
            =====================================================\n\
            Major version bump version requirement change issues:\n\
            =====================================================\n\
            1. Package foobar has a major change in version requirement in dependencies\
                : serde: ^1.0.0 -> ^2.0.0\n\
            "
        );
    }

    #[test]
    fn version_req_dependency_check_passes_major_version_bump_but_dev_dep() {
        dependency_version_check_test(
            Version::new(2, 0, 0),
            true, /* baseline_has_dep */
            true, /* current_dev_dep */
            true, /* baseline_dev_dep */
        )
        .unwrap();
    }

    #[test]
    fn version_req_dependency_check_passes_major_version_bump_but_new_normal_dependency() {
        dependency_version_check_test(
            Version::new(2, 0, 0),
            true,  /* baseline_has_dep */
            false, /* current_dev_dep */
            true,  /* baseline_dev_dep */
        )
        .unwrap();
    }

    #[test]
    fn version_req_dependency_check_passes_major_version_bump_but_baseline_has_normal_dep() {
        dependency_version_check_test(
            Version::new(2, 0, 0),
            true,  /* baseline_has_dep */
            true,  /* current_dev_dep */
            false, /* baseline_dev_dep */
        )
        .unwrap();
    }
}
