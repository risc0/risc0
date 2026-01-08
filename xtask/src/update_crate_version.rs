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

//! Sets the version of a crate or many crates.

use anyhow::{Context as _, Result, anyhow};
use camino::Utf8Path;
use clap::Parser;

use std::collections::BTreeMap;
use std::fs;
use std::path::Path;

/// Updates the version numbers for one or all the crates in the workspace.
///
/// If the `--package` argument isn't given, it applies the change to all packages in the
/// workspace.
///
/// If no arguments are provided it updates the workspace Cargo.toml to have version requirements
/// matching the workspace crates.
#[derive(Parser, Debug, Default)]
pub struct UpdateCrateVersion {
    /// Only update the crate version for the given package name.
    #[arg(long)]
    package: Option<String>,

    /// Add a `-rc.X` to the version number
    #[arg(long)]
    add_rc: Option<u32>,

    /// Remove a `-rc.X` to the version number, takes place before `--add-rc`
    #[arg(long)]
    remove_rc: bool,

    /// Increases the patch component of the version number. Takes place after `--bump-major` and
    /// `--bump-minor`
    #[arg(long)]
    bump_patch: bool,

    /// Increases the minor component of the version number. Takes place after `--bump-major`.
    /// Clears the patch component.
    #[arg(long)]
    bump_minor: bool,

    /// Increases the major component of the version number. Clears the minor and patch components.
    #[arg(long)]
    bump_major: bool,
}

fn update_version(args: &UpdateCrateVersion, old_version: &semver::Version) -> semver::Version {
    let mut new_version = old_version.clone();
    if args.bump_major {
        new_version.major += 1;
        new_version.minor = 0;
        new_version.patch = 0;
    }
    if args.bump_minor {
        new_version.minor += 1;
        new_version.patch = 0;
    }
    if args.bump_patch {
        new_version.patch += 1;
    }

    if args.remove_rc {
        new_version.pre = semver::Prerelease::EMPTY;
    }

    if let Some(rc_num) = args.add_rc {
        new_version.pre = semver::Prerelease::new(&format!("rc.{rc_num}"))
            .expect("should always be a valid pre-release value");
    }

    new_version
}

fn run_inner(args: &UpdateCrateVersion, workspace_root: &Path) -> Result<()> {
    let metadata = cargo_metadata::MetadataCommand::new()
        .current_dir(workspace_root)
        .exec()
        .context("failed to run `cargo metadata`")?;

    let mut new_workspace_versions = BTreeMap::new();

    for package in metadata.workspace_default_packages() {
        if args
            .package
            .as_ref()
            .is_some_and(|p| p != package.name.as_str())
        {
            continue;
        }

        // check for package.metadata.release.release = false
        if let Some(release_metadata) = package.metadata.get("release")
            && let Some(release_flag) = release_metadata.get("release")
            && release_flag.as_bool().is_some_and(|v| !v)
        {
            continue;
        }

        let manifest_path = &package.manifest_path;
        let content = fs::read_to_string(manifest_path)
            .with_context(|| format!("failed to read manifest {manifest_path}"))?;
        let mut cargo_toml = content
            .parse::<toml_edit::DocumentMut>()
            .with_context(|| format!("failed to parse {manifest_path} as TOML"))?;

        let package_table = cargo_toml
            .get_mut("package")
            .ok_or_else(|| anyhow!("could not find package section in {manifest_path}"))?;

        let version = package_table
            .get_mut("version")
            .ok_or_else(|| anyhow!("could not find package.version in {manifest_path}",))?;
        let version_str = version
            .as_str()
            .ok_or_else(|| anyhow!("package.version not a string in {manifest_path}"))?;

        let old_version = semver::Version::parse(version_str)
            .with_context(|| format!("failed to parse version from {manifest_path}"))?;
        let new_version = update_version(args, &old_version);

        *version = toml_edit::value(new_version.to_string());
        fs::write(manifest_path, cargo_toml.to_string())
            .with_context(|| format!("failed to write to {manifest_path}"))?;

        if old_version != new_version {
            println!(
                "Updated version of {} from {old_version} to {new_version}",
                &package.name
            );
        }
        new_workspace_versions.insert(package.name.clone(), new_version);
    }

    let manifest_path = Utf8Path::from_path(workspace_root)
        .ok_or_else(|| anyhow!("workspace root path contains invalid UTF-8"))?
        .join("Cargo.toml");
    let content = fs::read_to_string(&manifest_path)
        .with_context(|| format!("failed to read manifest {manifest_path}"))?;
    let mut cargo_toml = content
        .parse::<toml_edit::DocumentMut>()
        .with_context(|| format!("failed to parse {manifest_path} as TOML"))?;

    let workspace_table = cargo_toml
        .get_mut("workspace")
        .ok_or_else(|| anyhow!("could not find workspace section in {manifest_path}"))?;

    if args.package.is_none() {
        let package_table = workspace_table.get_mut("package").ok_or_else(|| {
            anyhow!("could not find workspace.package section in {manifest_path}")
        })?;
        let version = package_table.get_mut("version").ok_or_else(|| {
            anyhow!("could not find workspace.package.version in {manifest_path}",)
        })?;
        let version_str = version
            .as_str()
            .ok_or_else(|| anyhow!("package.version not a string in {manifest_path}"))?;

        let old_version = semver::Version::parse(version_str)
            .with_context(|| format!("failed to parse version from {manifest_path}"))?;
        let new_version = update_version(args, &old_version);

        *version = toml_edit::value(new_version.to_string());

        if old_version != new_version {
            println!("Updated workspace version from {old_version} to {new_version}");
        }
    }

    let dependencies_table = workspace_table.get_mut("dependencies").ok_or_else(|| {
        anyhow!("could not find workspace.dependencies section in {manifest_path}")
    })?;

    let dependencies_table = dependencies_table
        .as_table_like_mut()
        .ok_or_else(|| anyhow!("workspace.dependencies is not a table in {manifest_path}"))?;

    for (dep_name, dep_item) in dependencies_table.iter_mut() {
        let Some(new_version) = new_workspace_versions.get(&*dep_name) else {
            continue;
        };
        let version = dep_item.get_mut("version").ok_or_else(|| {
            anyhow!("could not find workspace.package.version in {manifest_path}",)
        })?;
        let version_str = version
            .as_str()
            .ok_or_else(|| anyhow!("package.version not a string in {manifest_path}"))?;

        let old_version = semver::Version::parse(version_str)
            .with_context(|| format!("failed to parse version from {manifest_path}"))?;
        *version = toml_edit::value(new_version.to_string());

        println!(
            "Updated workspace dependency {dep_name} version from {old_version} to {new_version}"
        );
    }

    fs::write(&manifest_path, cargo_toml.to_string())
        .with_context(|| format!("failed to write to {manifest_path}"))?;

    Ok(())
}

impl UpdateCrateVersion {
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
    use semver::Version;
    use tempfile::tempdir;

    struct TestVersions {
        workspace: Version,
        workspace_foo_dep: Version,
        workspace_bar_dep: Version,
        foo: Version,
        bar: Version,
    }

    fn test_it(args: UpdateCrateVersion, before: TestVersions, after: TestVersions) {
        let tempdir = tempdir().unwrap();

        let build_package_cargo_toml = |name: &str, version: &Version| {
            format!(
                "\
                [package]\n\
                name = \"{name}\"\n\
                version = \"{version}\"\n\
                "
            )
        };

        let foo_root = tempdir.path().join("foo");
        let bar_root = tempdir.path().join("bar");

        let input = [
            (&foo_root, "foo", &before.foo),
            (&bar_root, "bar", &before.bar),
        ];

        for (root, name, version) in input {
            fs::create_dir_all(root.join("src")).unwrap();
            fs::write(
                root.join("Cargo.toml"),
                build_package_cargo_toml(name, version),
            )
            .unwrap();
            fs::write(root.join("src/main.rs"), "").unwrap();
        }

        let build_workspace_cargo_toml = |v: &TestVersions| {
            format!(
                "\
                [workspace]\n\
                resolver = \"2\"\n\
                members = [\"foo\", \"bar\"]\n\
                \n\
                [workspace.package]\n\
                version = \"{workspace_version}\"\n\
                \n\
                [workspace.dependencies]\n\
                foo = {{ version = \"{foo_version}\" }}\n\
                bar = {{ version = \"{bar_version}\" }}\n\
                ",
                workspace_version = v.workspace,
                foo_version = v.workspace_foo_dep,
                bar_version = v.workspace_bar_dep
            )
        };

        fs::write(
            tempdir.path().join("Cargo.toml"),
            build_workspace_cargo_toml(&before),
        )
        .unwrap();

        run_inner(&args, tempdir.path()).unwrap();

        assert_eq!(
            fs::read_to_string(tempdir.path().join("Cargo.toml")).unwrap(),
            build_workspace_cargo_toml(&after)
        );
        assert_eq!(
            fs::read_to_string(foo_root.join("Cargo.toml")).unwrap(),
            build_package_cargo_toml("foo", &after.foo)
        );
        assert_eq!(
            fs::read_to_string(bar_root.join("Cargo.toml")).unwrap(),
            build_package_cargo_toml("bar", &after.bar)
        );
    }

    #[test]
    fn no_args() {
        test_it(
            UpdateCrateVersion::default(),
            TestVersions {
                workspace: Version::new(2, 0, 0),
                workspace_foo_dep: Version::new(1, 0, 0),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 0, 1),
                bar: Version::new(2, 0, 1),
            },
            TestVersions {
                workspace: Version::new(2, 0, 0),
                workspace_foo_dep: Version::new(1, 0, 1),
                workspace_bar_dep: Version::new(2, 0, 1),
                foo: Version::new(1, 0, 1),
                bar: Version::new(2, 0, 1),
            },
        )
    }

    #[test]
    fn add_rc() {
        test_it(
            UpdateCrateVersion {
                add_rc: Some(5),
                ..Default::default()
            },
            TestVersions {
                workspace: Version::new(2, 0, 0),
                workspace_foo_dep: Version::new(1, 0, 0),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 0, 1),
                bar: Version::new(2, 0, 1),
            },
            TestVersions {
                workspace: Version::parse("2.0.0-rc.5").unwrap(),
                workspace_foo_dep: Version::parse("1.0.1-rc.5").unwrap(),
                workspace_bar_dep: Version::parse("2.0.1-rc.5").unwrap(),
                foo: Version::parse("1.0.1-rc.5").unwrap(),
                bar: Version::parse("2.0.1-rc.5").unwrap(),
            },
        )
    }

    #[test]
    fn add_rc_only_one_package() {
        test_it(
            UpdateCrateVersion {
                add_rc: Some(5),
                package: Some("foo".into()),
                ..Default::default()
            },
            TestVersions {
                workspace: Version::new(2, 0, 0),
                workspace_foo_dep: Version::new(1, 0, 0),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 0, 1),
                bar: Version::new(2, 0, 1),
            },
            TestVersions {
                workspace: Version::new(2, 0, 0),
                workspace_foo_dep: Version::parse("1.0.1-rc.5").unwrap(),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::parse("1.0.1-rc.5").unwrap(),
                bar: Version::new(2, 0, 1),
            },
        )
    }

    #[test]
    fn remove_add_rc() {
        test_it(
            UpdateCrateVersion {
                add_rc: Some(6),
                remove_rc: true,
                ..Default::default()
            },
            TestVersions {
                workspace: Version::parse("2.0.0-rc.5").unwrap(),
                workspace_foo_dep: Version::parse("1.0.1-rc.5").unwrap(),
                workspace_bar_dep: Version::parse("2.0.1-rc.5").unwrap(),
                foo: Version::parse("1.0.1-rc.5").unwrap(),
                bar: Version::parse("2.0.1-rc.5").unwrap(),
            },
            TestVersions {
                workspace: Version::parse("2.0.0-rc.6").unwrap(),
                workspace_foo_dep: Version::parse("1.0.1-rc.6").unwrap(),
                workspace_bar_dep: Version::parse("2.0.1-rc.6").unwrap(),
                foo: Version::parse("1.0.1-rc.6").unwrap(),
                bar: Version::parse("2.0.1-rc.6").unwrap(),
            },
        )
    }

    #[test]
    fn remove_rc() {
        test_it(
            UpdateCrateVersion {
                remove_rc: true,
                ..Default::default()
            },
            TestVersions {
                workspace: Version::parse("2.0.0-rc.5").unwrap(),
                workspace_foo_dep: Version::parse("1.0.1-rc.5").unwrap(),
                workspace_bar_dep: Version::parse("2.0.1-rc.5").unwrap(),
                foo: Version::parse("1.0.1-rc.5").unwrap(),
                bar: Version::parse("2.0.1-rc.5").unwrap(),
            },
            TestVersions {
                workspace: Version::new(2, 0, 0),
                workspace_foo_dep: Version::new(1, 0, 1),
                workspace_bar_dep: Version::new(2, 0, 1),
                foo: Version::new(1, 0, 1),
                bar: Version::new(2, 0, 1),
            },
        )
    }

    #[test]
    fn remove_rc_only_one_package() {
        test_it(
            UpdateCrateVersion {
                remove_rc: true,
                package: Some("foo".into()),
                ..Default::default()
            },
            TestVersions {
                workspace: Version::new(2, 0, 0),
                workspace_foo_dep: Version::parse("1.0.1-rc.5").unwrap(),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::parse("1.0.1-rc.5").unwrap(),
                bar: Version::new(2, 0, 1),
            },
            TestVersions {
                workspace: Version::new(2, 0, 0),
                workspace_foo_dep: Version::new(1, 0, 1),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 0, 1),
                bar: Version::new(2, 0, 1),
            },
        )
    }

    #[test]
    fn bump_patch() {
        test_it(
            UpdateCrateVersion {
                bump_patch: true,
                ..Default::default()
            },
            TestVersions {
                workspace: Version::new(2, 0, 0),
                workspace_foo_dep: Version::new(1, 0, 0),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 0, 1),
                bar: Version::new(2, 0, 1),
            },
            TestVersions {
                workspace: Version::new(2, 0, 1),
                workspace_foo_dep: Version::new(1, 0, 2),
                workspace_bar_dep: Version::new(2, 0, 2),
                foo: Version::new(1, 0, 2),
                bar: Version::new(2, 0, 2),
            },
        )
    }

    #[test]
    fn bump_patch_only_one_package() {
        test_it(
            UpdateCrateVersion {
                bump_patch: true,
                package: Some("foo".into()),
                ..Default::default()
            },
            TestVersions {
                workspace: Version::new(2, 0, 0),
                workspace_foo_dep: Version::new(1, 0, 0),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 0, 1),
                bar: Version::new(2, 0, 1),
            },
            TestVersions {
                workspace: Version::new(2, 0, 0),
                workspace_foo_dep: Version::new(1, 0, 2),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 0, 2),
                bar: Version::new(2, 0, 1),
            },
        )
    }

    #[test]
    fn bump_minor() {
        test_it(
            UpdateCrateVersion {
                bump_minor: true,
                ..Default::default()
            },
            TestVersions {
                workspace: Version::new(2, 0, 0),
                workspace_foo_dep: Version::new(1, 0, 0),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 0, 1),
                bar: Version::new(2, 0, 1),
            },
            TestVersions {
                workspace: Version::new(2, 1, 0),
                workspace_foo_dep: Version::new(1, 1, 0),
                workspace_bar_dep: Version::new(2, 1, 0),
                foo: Version::new(1, 1, 0),
                bar: Version::new(2, 1, 0),
            },
        )
    }

    #[test]
    fn bump_minor_only_one_package() {
        test_it(
            UpdateCrateVersion {
                bump_minor: true,
                package: Some("foo".into()),
                ..Default::default()
            },
            TestVersions {
                workspace: Version::new(2, 0, 0),
                workspace_foo_dep: Version::new(1, 0, 0),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 0, 1),
                bar: Version::new(2, 0, 1),
            },
            TestVersions {
                workspace: Version::new(2, 0, 0),
                workspace_foo_dep: Version::new(1, 1, 0),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 1, 0),
                bar: Version::new(2, 0, 1),
            },
        )
    }

    #[test]
    fn bump_major() {
        test_it(
            UpdateCrateVersion {
                bump_major: true,
                ..Default::default()
            },
            TestVersions {
                workspace: Version::new(2, 1, 1),
                workspace_foo_dep: Version::new(1, 0, 0),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 1, 1),
                bar: Version::new(2, 1, 1),
            },
            TestVersions {
                workspace: Version::new(3, 0, 0),
                workspace_foo_dep: Version::new(2, 0, 0),
                workspace_bar_dep: Version::new(3, 0, 0),
                foo: Version::new(2, 0, 0),
                bar: Version::new(3, 0, 0),
            },
        )
    }

    #[test]
    fn bump_major_only_one_package() {
        test_it(
            UpdateCrateVersion {
                bump_major: true,
                package: Some("foo".into()),
                ..Default::default()
            },
            TestVersions {
                workspace: Version::new(2, 1, 1),
                workspace_foo_dep: Version::new(1, 0, 0),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 1, 1),
                bar: Version::new(2, 1, 1),
            },
            TestVersions {
                workspace: Version::new(2, 1, 1),
                workspace_foo_dep: Version::new(2, 0, 0),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(2, 0, 0),
                bar: Version::new(2, 1, 1),
            },
        )
    }

    #[test]
    fn bump_patch_and_minor() {
        test_it(
            UpdateCrateVersion {
                bump_patch: true,
                bump_minor: true,
                ..Default::default()
            },
            TestVersions {
                workspace: Version::new(2, 1, 1),
                workspace_foo_dep: Version::new(1, 0, 0),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 1, 2),
                bar: Version::new(2, 1, 2),
            },
            TestVersions {
                workspace: Version::new(2, 2, 1),
                workspace_foo_dep: Version::new(1, 2, 1),
                workspace_bar_dep: Version::new(2, 2, 1),
                foo: Version::new(1, 2, 1),
                bar: Version::new(2, 2, 1),
            },
        )
    }

    #[test]
    fn bump_patch_and_minor_only_one_package() {
        test_it(
            UpdateCrateVersion {
                bump_patch: true,
                bump_minor: true,
                package: Some("foo".into()),
                ..Default::default()
            },
            TestVersions {
                workspace: Version::new(2, 1, 1),
                workspace_foo_dep: Version::new(1, 0, 0),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 1, 2),
                bar: Version::new(2, 1, 2),
            },
            TestVersions {
                workspace: Version::new(2, 1, 1),
                workspace_foo_dep: Version::new(1, 2, 1),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 2, 1),
                bar: Version::new(2, 1, 2),
            },
        )
    }

    #[test]
    fn bump_patch_minor_and_major() {
        test_it(
            UpdateCrateVersion {
                bump_patch: true,
                bump_minor: true,
                bump_major: true,
                ..Default::default()
            },
            TestVersions {
                workspace: Version::new(2, 1, 1),
                workspace_foo_dep: Version::new(1, 0, 0),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 1, 2),
                bar: Version::new(2, 1, 2),
            },
            TestVersions {
                workspace: Version::new(3, 1, 1),
                workspace_foo_dep: Version::new(2, 1, 1),
                workspace_bar_dep: Version::new(3, 1, 1),
                foo: Version::new(2, 1, 1),
                bar: Version::new(3, 1, 1),
            },
        )
    }

    #[test]
    fn bump_patch_minor_and_major_only_one_package() {
        test_it(
            UpdateCrateVersion {
                bump_patch: true,
                bump_minor: true,
                bump_major: true,
                package: Some("foo".into()),
                ..Default::default()
            },
            TestVersions {
                workspace: Version::new(2, 1, 1),
                workspace_foo_dep: Version::new(1, 0, 0),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 1, 2),
                bar: Version::new(2, 1, 2),
            },
            TestVersions {
                workspace: Version::new(2, 1, 1),
                workspace_foo_dep: Version::new(2, 1, 1),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(2, 1, 1),
                bar: Version::new(2, 1, 2),
            },
        )
    }

    #[test]
    fn bump_patch_minor_major_and_add_rc() {
        test_it(
            UpdateCrateVersion {
                bump_patch: true,
                bump_minor: true,
                bump_major: true,
                add_rc: Some(2),
                ..Default::default()
            },
            TestVersions {
                workspace: Version::new(2, 1, 1),
                workspace_foo_dep: Version::new(1, 0, 0),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 1, 2),
                bar: Version::new(2, 1, 2),
            },
            TestVersions {
                workspace: Version::parse("3.1.1-rc.2").unwrap(),
                workspace_foo_dep: Version::parse("2.1.1-rc.2").unwrap(),
                workspace_bar_dep: Version::parse("3.1.1-rc.2").unwrap(),
                foo: Version::parse("2.1.1-rc.2").unwrap(),
                bar: Version::parse("3.1.1-rc.2").unwrap(),
            },
        )
    }

    #[test]
    fn bump_patch_minor_major_and_add_rc_only_one_package() {
        test_it(
            UpdateCrateVersion {
                bump_patch: true,
                bump_minor: true,
                bump_major: true,
                add_rc: Some(2),
                package: Some("foo".into()),
                ..Default::default()
            },
            TestVersions {
                workspace: Version::new(2, 1, 1),
                workspace_foo_dep: Version::new(1, 0, 0),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::new(1, 1, 2),
                bar: Version::new(2, 1, 2),
            },
            TestVersions {
                workspace: Version::new(2, 1, 1),
                workspace_foo_dep: Version::parse("2.1.1-rc.2").unwrap(),
                workspace_bar_dep: Version::new(2, 0, 0),
                foo: Version::parse("2.1.1-rc.2").unwrap(),
                bar: Version::new(2, 1, 2),
            },
        )
    }

    #[test]
    fn bump_patch_minor_major_and_remove_add_rc() {
        test_it(
            UpdateCrateVersion {
                bump_patch: true,
                bump_minor: true,
                bump_major: true,
                add_rc: Some(2),
                remove_rc: true,
                ..Default::default()
            },
            TestVersions {
                workspace: Version::parse("2.1.1-rc.6").unwrap(),
                workspace_foo_dep: Version::parse("1.0.0-rc.6").unwrap(),
                workspace_bar_dep: Version::parse("2.0.0-rc.6").unwrap(),
                foo: Version::parse("1.1.2-rc.6").unwrap(),
                bar: Version::parse("2.1.2-rc.6").unwrap(),
            },
            TestVersions {
                workspace: Version::parse("3.1.1-rc.2").unwrap(),
                workspace_foo_dep: Version::parse("2.1.1-rc.2").unwrap(),
                workspace_bar_dep: Version::parse("3.1.1-rc.2").unwrap(),
                foo: Version::parse("2.1.1-rc.2").unwrap(),
                bar: Version::parse("3.1.1-rc.2").unwrap(),
            },
        )
    }

    #[test]
    fn bump_patch_minor_major_and_remove_add_rc_only_one_package() {
        test_it(
            UpdateCrateVersion {
                bump_patch: true,
                bump_minor: true,
                bump_major: true,
                add_rc: Some(2),
                remove_rc: true,
                package: Some("foo".into()),
            },
            TestVersions {
                workspace: Version::parse("2.1.1-rc.6").unwrap(),
                workspace_foo_dep: Version::parse("1.0.0-rc.6").unwrap(),
                workspace_bar_dep: Version::parse("2.0.0-rc.6").unwrap(),
                foo: Version::parse("1.1.2-rc.6").unwrap(),
                bar: Version::parse("2.1.2-rc.6").unwrap(),
            },
            TestVersions {
                workspace: Version::parse("2.1.1-rc.6").unwrap(),
                workspace_foo_dep: Version::parse("2.1.1-rc.2").unwrap(),
                workspace_bar_dep: Version::parse("2.0.0-rc.6").unwrap(),
                foo: Version::parse("2.1.1-rc.2").unwrap(),
                bar: Version::parse("2.1.2-rc.6").unwrap(),
            },
        )
    }
}
