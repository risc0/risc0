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

//! Updates all the `Cargo.lock` files in the repository.

use anyhow::{Context as _, Result, anyhow, bail};
use clap::Parser;

use std::path::Path;
use std::process::{Command, Stdio};

#[derive(Parser)]
pub struct UpdateLockFiles;

/// Runs some command, checks for errors, and forwards output from stdout / stderr to `print` and
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

fn update_project_lock_file(manifest_path: &Path) -> Result<()> {
    // Running `cargo update` with the `--workspace` flag makes it update only workspace packages,
    // which has the effect we want which is to update the lock files in response to local changes,
    // not newly published crates from crates.io
    run_command(
        Command::new("cargo")
            .args(["update", "--workspace", "--manifest-path"])
            .arg(manifest_path),
        &format!(
            "Failed to update the lock file for {}",
            manifest_path.display()
        ),
    )?;
    Ok(())
}

fn visit_path(path: &Path) -> Result<()> {
    let Some(file_name) = path.file_name() else {
        return Ok(());
    };

    let file_name = file_name.to_str().ok_or_else(|| anyhow!("invalid UTF-8"))?;
    if file_name == "Cargo.lock" {
        update_project_lock_file(&path.parent().unwrap().join("Cargo.toml"))?;
        println!("Updated lock file {}", path.display());
    }

    Ok(())
}

fn run_inner(repo_root: &Path) -> Result<()> {
    let skip_dirs = [
        repo_root.join("external"),
        repo_root.join("tools"),
        repo_root.join("target"),
    ];

    for entry in walkdir::WalkDir::new(repo_root) {
        let entry = entry.context("failed listing directory")?;

        if skip_dirs.iter().any(|skip| entry.path().starts_with(skip)) {
            continue;
        }

        if let Err(err) = visit_path(entry.path()) {
            eprintln!(
                "Skipping path {} due to error: {err}",
                entry.path().display()
            );
        }
    }

    Ok(())
}

impl UpdateLockFiles {
    pub fn run(&self) {
        let current_dir = std::env::current_dir().expect("should be able to get current directory");
        if let Err(e) = run_inner(&current_dir) {
            panic!("{e}");
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use semver::Version;
    use tempfile::tempdir;

    #[test]
    fn basic_test() {
        let tempdir = tempdir().unwrap();

        let write_cargo_toml = |path: &Path, name: &str, version: &Version, dep: &str| {
            std::fs::write(
                path.join("Cargo.toml"),
                format!(
                    "\
                    [package]\n\
                    name = \"{name}\"\n\
                    version = \"{version}\"\n\
                    \n\
                    [dependencies]\n\
                    {dep}\n\
                    "
                ),
            )
            .unwrap();
        };

        let foo_root = tempdir.path().join("foo");
        let bar_root = tempdir.path().join("bar");
        let baz_root = tempdir.path().join("external/baz");

        let inputs = [
            (&foo_root, "foo", "bar = { path = \"../bar\" }"),
            (&bar_root, "bar", ""),
            (&baz_root, "baz", "bar = { path = \"../../bar\" }"),
        ];

        for (root, name, dep) in inputs {
            std::fs::create_dir_all(root.join("src")).unwrap();
            write_cargo_toml(root, name, &Version::new(1, 0, 0), dep);
            std::fs::write(root.join("src/main.rs"), "").unwrap();
        }

        for (root, _, _) in inputs {
            assert!(
                Command::new("cargo")
                    .args(["update"])
                    .current_dir(root)
                    .stdout(Stdio::null())
                    .stderr(Stdio::null())
                    .status()
                    .unwrap()
                    .success()
            );
        }

        // sanity check, foo depends on bar
        assert!(
            std::fs::read_to_string(foo_root.join("Cargo.lock"))
                .unwrap()
                .contains("name = \"bar\"\nversion = \"1.0.0\"")
        );

        // sanity check, baz depends on bar
        assert!(
            std::fs::read_to_string(baz_root.join("Cargo.lock"))
                .unwrap()
                .contains("name = \"bar\"\nversion = \"1.0.0\"")
        );

        // Update bar's version, this should require foo and baz's lock files to update
        write_cargo_toml(&bar_root, "bar", &Version::new(2, 0, 0), "");

        // This should update foo's lock file, but not baz
        run_inner(tempdir.path()).unwrap();

        // foo should be updated
        assert!(
            std::fs::read_to_string(foo_root.join("Cargo.lock"))
                .unwrap()
                .contains("name = \"bar\"\nversion = \"2.0.0\"")
        );

        // baz should have remained the same
        assert!(
            std::fs::read_to_string(baz_root.join("Cargo.lock"))
                .unwrap()
                .contains("name = \"bar\"\nversion = \"1.0.0\"")
        );
    }
}
