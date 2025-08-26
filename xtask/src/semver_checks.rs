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
use semver::Version;
use tempfile::tempdir;

use std::collections::BTreeMap;
use std::io::Write;
use std::path::{Path, PathBuf};
use std::process::{Command, Stdio};

#[derive(Parser)]
pub struct SemverChecks;

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
#[derive(Debug, PartialEq, Eq)]
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
#[derive(Debug, PartialEq, Eq)]
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
        "Comparing {package} v{version} to crates.io version to see if it needs a patch version bump"
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
        &format!("failed to create publishable version of {package}"),
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
            "Differences found between published {package} and main. Patch version bump required."
        ),
    )?;

    Ok(())
}

/// Compare all the given packages with their crates.io versions to see if they differ
fn check_for_patch_version_bump(
    workspace_root: &Path,
    cargo_vendor: impl FnOnce(&Path) -> Result<()>,
    packages: &[(String, Version)],
) -> Result<()> {
    let tempdir = tempdir().unwrap();
    let vendored_packages = vendor_packages(cargo_vendor, &tempdir, packages)?;

    for (package, version) in packages {
        compare_published_package_to_vendored_version(
            workspace_root,
            package,
            version,
            &vendored_packages,
        )?;
    }
    Ok(())
}

/// Find packages in the workspace that don't have `release = false`
fn find_publishable_packages(
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

        packages.insert(package.name.clone(), package.clone());
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

/// Entrypoint for the tests. See the module doc-comment about what it does.
///
/// `workspace_root` : The path to the workspace we are checking
/// `semver_baseline`: The baseline version we are comparing to
/// `cargo_vendor`   : Function that runs `cargo vendor` command. We dependency inject this for the
///                    sake of the tests
fn run_inner(
    workspace_root: &Path,
    semver_baseline: Rustdoc,
    cargo_vendor: impl FnOnce(&Path) -> Result<()>,
) -> Result<()> {
    let packages = find_publishable_packages(workspace_root)?;
    let package_names = packages.keys().cloned().collect();

    let semver_output = run_semver_checks(workspace_root, semver_baseline, package_names)?;

    let unbumped_packages: Vec<_> = semver_output
        .crate_versions
        .into_iter()
        .filter_map(|(name, versions)| {
            (versions.current == versions.baseline).then_some((name, versions.current))
        })
        .collect();

    if !unbumped_packages.is_empty() {
        check_for_patch_version_bump(workspace_root, cargo_vendor, &unbumped_packages)?;
    }

    Ok(())
}

impl SemverChecks {
    pub fn run(&self) {
        let current_dir = std::env::current_dir().expect("should be able to get current directory");
        if let Err(e) = run_inner(
            &current_dir,
            Rustdoc::from_registry_latest_crate_version(),
            real_cargo_vendor,
        ) {
            panic!("{e}");
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

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

    /// Writes out a project twice with one crate called "foobar". Runs checks on the two versions
    /// with one being the "baseline" and the other being the "current" version.
    fn test_run(
        baseline_contents: &str,
        baseline_version: Version,
        current_contents: &str,
        current_version: Version,
    ) -> Result<()> {
        let tempdir = tempdir().unwrap();

        // Both copies need the same workspace Cargo.toml
        for d in ["baseline", "current"] {
            std::fs::create_dir_all(tempdir.path().join(d)).unwrap();
            std::fs::write(
                tempdir.path().join(d).join("Cargo.toml"),
                "
                [workspace]
                members = [\"foobar\"]
                resolve = \"2\"
                ",
            )
            .unwrap();
        }

        let write_cargo_toml = |path: &Path, version: &Version| {
            std::fs::write(
                path.join("Cargo.toml"),
                format!(
                    "\
                    [package]\n\
                    name = \"foobar\"\n\
                    version = \"{version}\"\n\
                    "
                ),
            )
            .unwrap();
        };

        // Create the baseline skeleton
        let baseline_foobar = tempdir.path().join("baseline/foobar");
        std::fs::create_dir_all(baseline_foobar.join("src")).unwrap();
        write_cargo_toml(&baseline_foobar, &baseline_version);
        std::fs::write(baseline_foobar.join("src/lib.rs"), baseline_contents).unwrap();

        // Create the current skeleton
        let current_foobar = tempdir.path().join("current/foobar");
        std::fs::create_dir_all(current_foobar.join("src")).unwrap();
        write_cargo_toml(&current_foobar, &current_version);
        std::fs::write(current_foobar.join("src/lib.rs"), current_contents).unwrap();

        // Create a published version of the baseline like what would exist on `crates.io` and save
        // it so we can move it into place in our test version of `cargo vendor`
        assert!(Command::new("cargo")
            .args([
                "publish",
                "--allow-dirty",
                "--dry-run",
                "--package",
                "foobar",
            ])
            .current_dir(tempdir.path().join("baseline"))
            .stdout(Stdio::null())
            .stderr(Stdio::null())
            .status()
            .unwrap()
            .success());

        // Locally published crates have this directory, but not ones on `crates.io`
        let published_crate = tempdir
            .path()
            .join("baseline")
            .join(format!("target/package/foobar-{baseline_version}"));
        std::fs::remove_dir_all(published_crate.join("target")).unwrap();

        let published_baseline = tempdir.path().join("published_baseline");
        std::fs::rename(
            tempdir
                .path()
                .join("baseline/target/package")
                .join(format!("foobar-{baseline_version}")),
            &published_baseline,
        )
        .unwrap();

        run_inner(
            &tempdir.path().join("current"),
            Rustdoc::from_root(tempdir.path().join("baseline")),
            |d| {
                // This is our test version of `cargo vendor`
                std::fs::create_dir_all(d.join("vendor")).unwrap();
                std::fs::rename(published_baseline, d.join("vendor/foobar")).unwrap();
                std::fs::write(d.join("vendor/foobar/.cargo-checksum.json"), "").unwrap();
                Ok(())
            },
        )
    }

    #[test]
    fn no_change_passes() {
        test_run(
            "pub fn foo() {}",
            Version::new(1, 0, 0),
            "pub fn foo() {}",
            Version::new(1, 0, 0),
        )
        .unwrap();
    }

    #[test]
    fn patch_change_fails() {
        assert_eq!(
            test_run(
                "pub fn foo() {}",
                Version::new(1, 0, 0),
                "pub fn foo() { /*hello*/ }",
                Version::new(1, 0, 0),
            )
            .unwrap_err()
            .to_string(),
            "Differences found between published foobar and main. Patch version bump required."
        );
    }

    #[test]
    fn patch_change_passes() {
        test_run(
            "pub fn foo() {}",
            Version::new(1, 0, 0),
            "pub fn foo() { /*hello*/ }",
            Version::new(1, 0, 1),
        )
        .unwrap();
    }

    #[test]
    fn minor_change_fails() {
        assert_eq!(
            test_run(
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
        test_run(
            "pub fn foo() {}",
            Version::new(1, 0, 0),
            "#[deprecated] pub fn foo() {}",
            Version::new(1, 1, 0),
        )
        .unwrap();
    }

    #[test]
    fn major_change_fails() {
        assert_eq!(
            test_run(
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
        test_run(
            "pub fn foo() {}",
            Version::new(1, 0, 0),
            "pub fn foo(_a: u32) {}",
            Version::new(2, 0, 0),
        )
        .unwrap();
    }
}
