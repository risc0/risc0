// Copyright 2023 RISC Zero, Inc.
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

use std::path::PathBuf;

use cargo_generate::{GenerateArgs, TemplatePath, Vcs};
use clap::Parser;
use const_format::concatcp;
use convert_case::{Case, Casing};

const RISC0_GH_REPO: &str = "https://github.com/risc0/risc0";
const RISC0_TEMPLATE_DIR: &str = "templates/rust-starter";
const RISC0_DEFAULT_VERSION: &str = env!("CARGO_PKG_VERSION");
const RISC0_RELEASE_TAG: &str = concatcp!("v", RISC0_DEFAULT_VERSION);

#[derive(Parser)]
/// `cargo risczero new`
pub struct NewCommand {
    /// Name which will be used as the output project name.
    #[arg()]
    pub name: String,

    /// GH repository URL.
    #[clap(value_parser, long, short, default_value = RISC0_GH_REPO)]
    pub template: String,

    /// template git tag.
    #[clap(value_parser, long, default_value = RISC0_RELEASE_TAG)]
    pub tag: String,

    /// template git branch, overrides `tag` option
    #[clap(value_parser, long, default_value = "")]
    pub branch: String,

    /// Destination directory to create project in.
    ///
    /// Example `cargo risczero new --dest /tmp/ cool-project` ->
    /// `/tmp/cool-project/`
    ///
    /// Default: `pwd`
    #[clap(value_parser, long)]
    pub dest: Option<PathBuf>,

    /// Disable init'ing a git repo in the dest project
    #[clap(value_parser, long, global = true)]
    pub no_git: bool,

    /// Toggles templates to use crates from github
    ///
    /// Sets the value of the arg to be the cargo `branch` variable
    #[clap(value_parser, long)]
    pub use_git_branch: Option<String>,

    /// Toggles `std` feature flag for guest code
    ///
    /// Toggles the `#![no_std]` in the guest main() and the `std` feature flag
    /// on the `risc0_zkvm` crate.
    #[clap(value_parser, long, global = true)]
    pub std: bool,
}

impl NewCommand {
    /// Execute this command
    pub fn run(&self) {
        let subfolder = if self.template == RISC0_GH_REPO {
            Some(RISC0_TEMPLATE_DIR.to_string())
        } else {
            None
        };

        let dest_dir = if let Some(dest_dir) = self.dest.clone() {
            dest_dir
        } else {
            std::env::current_dir().expect("Failed to fetch cwd")
        };

        let mut template_path = TemplatePath {
            auto_path: Some(self.template.clone()),
            subfolder,
            git: None,
            branch: None,
            path: None,
            favorite: None,
            tag: Some(self.tag.clone()),
            test: false,
        };

        if !self.branch.is_empty() {
            template_path.branch = Some(self.branch.clone());
            template_path.tag = None;
        }

        let risc0_version = std::env::var("CARGO_PKG_VERSION")
            .unwrap_or_else(|_| RISC0_DEFAULT_VERSION.to_string());

        let mut template_variables = vec![format!("risc0_version={risc0_version}")];
        if let Some(branch) = self.use_git_branch.as_ref() {
            template_variables.push(format!("risc0_crate_branch={branch}"))
        }

        if self.std {
            template_variables.push(format!("risc0_std={}", self.std));
        }

        cargo_generate::generate(GenerateArgs {
            template_path,
            list_favorites: false,
            name: Some(self.name.to_case(Case::Snake)),
            force: true,
            verbose: true,
            template_values_file: None,
            silent: false,
            config: None,
            vcs: if self.no_git {
                Some(Vcs::None)
            } else {
                Some(Vcs::Git)
            },
            lib: false,
            bin: false,
            ssh_identity: None,
            define: template_variables,
            init: false,
            destination: Some(dest_dir),
            force_git_init: false,
            allow_commands: false,
            overwrite: false,
            other_args: None,
        })
        .expect("Failed to generate project");
    }
}

#[cfg(test)]
mod tests {
    use std::fs::File;
    use std::io::{BufRead, BufReader};
    use std::path::Path;

    use tempfile::{tempdir, TempDir};

    use super::*;

    fn make_test_env() -> (TempDir, PathBuf, &'static str) {
        let tmpdir = tempdir().expect("Failed to create tempdir");
        let manifest_path =
            std::env::var("CARGO_MANIFEST_DIR").expect("Missing CARGO_MANIFEST_DIR var");
        // NOTE: cargo run and cargo test have a slightly different idea of what the
        // manifest_dir is. https://github.com/rust-lang/cargo/issues/3946
        let template_path = Path::new(&manifest_path).join("../../");
        (tmpdir, template_path, "my_project")
    }

    fn find_in_file(needle: &str, file: &Path) -> bool {
        let file = File::open(file).unwrap();
        let reader = BufReader::new(file);
        for line in reader.lines() {
            let line_data = line.expect("Failed to readline");
            if line_data.contains(needle) {
                return true;
            }
        }
        false
    }

    #[test]
    fn basic_new() {
        let new = NewCommand::parse_from(["new", "my_project"]);
        assert_eq!(new.name, "my_project");
    }

    #[test]
    fn basic_generate() {
        let (tmpdir, template_path, proj_name) = make_test_env();

        let new = NewCommand::parse_from([
            "new",
            "--template",
            &template_path
                .join("templates/rust-starter")
                .to_string_lossy(),
            "--dest",
            &tmpdir.path().to_string_lossy(),
            proj_name,
        ]);

        new.run();

        let proj_path = tmpdir.path().join(proj_name);

        assert!(proj_path.exists());
        assert!(proj_path.join(".git").exists());
        assert!(find_in_file(
            &format!("risc0-zkvm = \"{RISC0_DEFAULT_VERSION}\""),
            &proj_path.join("host/Cargo.toml")
        ));

        assert!(find_in_file(
            "#![no_std]",
            &proj_path.join("methods/guest/src/bin/method_name.rs")
        ));
    }

    #[test]
    fn generate_no_git_branch() {
        let (tmpdir, template_path, proj_name) = make_test_env();

        let new = NewCommand::parse_from([
            "new",
            "--template",
            &template_path
                .join("templates/rust-starter")
                .to_string_lossy(),
            "--dest",
            &tmpdir.path().to_string_lossy(),
            "--no-git",
            "--use-git-branch",
            "main",
            proj_name,
        ]);

        new.run();

        let proj_path = tmpdir.path().join(proj_name);

        assert!(proj_path.exists());
        assert!(!proj_path.join(".git").exists());
        assert!(find_in_file(
            "risc0-zkvm = { git = \"https://github.com/risc0/risc0.git\", branch = \"main\"",
            &proj_path.join("host/Cargo.toml")
        ));
    }

    #[test]
    fn generate_std() {
        let (tmpdir, template_path, proj_name) = make_test_env();

        let new = NewCommand::parse_from([
            "new",
            "--template",
            &template_path
                .join("templates/rust-starter")
                .to_string_lossy(),
            "--dest",
            &tmpdir.path().to_string_lossy(),
            "--std",
            proj_name,
        ]);

        new.run();

        let proj_path = tmpdir.path().join(proj_name);

        assert!(!find_in_file(
            "#![no_std]",
            &proj_path.join("methods/guest/src/bin/method_name.rs")
        ));
        assert!(!find_in_file(
            "feature = ['std']",
            &proj_path.join("methods/guest/Cargo.toml")
        ));
    }
}
