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

use anyhow::{anyhow, Result};
use cargo_generate::{GenerateArgs, TemplatePath, Vcs};
use clap::Parser;
use const_format::concatcp;
use text_io::read;

const RISC0_GH_REPO: &str = "https://github.com/risc0/risc0";
const RISC0_TEMPLATE_DIR: &str = "templates/rust-starter";
const RISC0_DEFAULT_VERSION: &str = env!("CARGO_PKG_VERSION");
const RISC0_RELEASE_TAG: &str = concatcp!("v", RISC0_DEFAULT_VERSION);

/// `cargo risczero new`
#[derive(Parser)]
pub struct NewCommand {
    /// Name which will be used as the output project name.
    #[arg()]
    pub name: String,

    /// GH repository URL.
    #[arg(long, short, default_value = RISC0_GH_REPO)]
    pub template: String,

    /// Location of the template
    ///
    /// The subdirectory location of the template used for generating the new
    /// project. This path is relative to the base repository specified by
    /// --template
    #[arg(long, default_value = RISC0_TEMPLATE_DIR)]
    pub templ_subdir: String,

    /// template git tag.
    #[arg(long, default_value = RISC0_RELEASE_TAG)]
    pub tag: String,

    /// template git branch, overrides `tag` option
    #[arg(long, default_value = "")]
    pub branch: String,

    /// Destination directory to create project in.
    ///
    /// Example `cargo risczero new --dest /tmp/ cool-project` ->
    /// `/tmp/cool-project/`
    ///
    /// Default: `pwd`
    #[arg(long)]
    pub dest: Option<PathBuf>,

    /// Disable init'ing a git repo in the dest project
    #[arg(long, global = true)]
    pub no_git: bool,

    /// Toggles templates to use crates from github
    ///
    /// Sets the value of the arg to be the cargo `branch` variable
    #[arg(long)]
    pub use_git_branch: Option<String>,

    /// Toggles `std` feature flag for guest code
    ///
    /// Toggles the `#![no_std]` in the guest main() and the `std` feature flag
    /// on the `risc0_zkvm` crate.
    #[arg(long, global = false)]
    pub std: bool,

    /// Use a path dependency for risc0.
    #[arg(long)]
    pub path: Option<PathBuf>,

    /// Name of the guest
    ///
    /// Sets the name of the guest method. This must be a valid rust identifier.
    #[arg(long)]
    pub guest_name: Option<String>,
}

impl NewCommand {
    /// Execute this command
    pub fn run(&self) -> Result<()> {
        let dest_dir = if let Some(dest_dir) = self.dest.clone() {
            dest_dir
        } else {
            std::env::current_dir().expect("Failed to fetch cwd")
        };

        let mut template_path = TemplatePath {
            auto_path: Some(self.template.clone()),
            subfolder: Some(self.templ_subdir.clone()),
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

        let mut template_variables = Vec::new();
        if let Some(branch) = self.use_git_branch.as_ref() {
            let spec =
                format!("git = \"https://github.com/risc0/risc0.git\", branch = \"{branch}\"");
            template_variables.push(format!("risc0_build={spec}"));
            template_variables.push(format!("risc0_zkvm={spec}"));
        } else if let Some(path) = self.path.as_ref() {
            let path = path.to_str().unwrap();
            let build = format!("path = \"{path}/risc0/build\"");
            let zkvm = format!("path = \"{path}/risc0/zkvm\"");
            template_variables.push(format!("risc0_build={build}"));
            template_variables.push(format!("risc0_zkvm={zkvm}"));
        } else {
            let spec = format!("version = \"{risc0_version}\"");
            template_variables.push(format!("risc0_build={spec}"));
            template_variables.push(format!("risc0_zkvm={spec}"));
        }

        let guest_name = match &self.guest_name {
            Some(name) => name.clone(),
            None => {
                eprint!(
                    "Guest name was not supplied through the --guest-name option. Please enter\
                    package name for your template or press [enter] to use default guest package\
                    name \"method\"\n\
                    Enter package name > "
                );
                let input_name: String = read!("{}\n");
                if input_name.is_empty() {
                    "method".to_string()
                } else {
                    input_name.clone()
                }
            }
        };

        syn::parse_str::<syn::Ident>(guest_name.as_str()).map_err(|_e| {
            anyhow!("guest name [{guest_name}] must be a rust valid rust identifier")
        })?;

        let guest_name_const = guest_name.replace("-", "_").to_ascii_uppercase();
        template_variables.push(format!("guest_package_name=\"{guest_name}\""));
        template_variables.push(format!("guest_id={guest_name_const}_ID"));
        template_variables.push(format!("guest_elf={guest_name_const}_ELF"));

        if self.std {
            template_variables.push("risc0_std=true".to_string());
            template_variables.push("risc0_feature_std=, features = ['std']".to_string());
        }

        cargo_generate::generate(GenerateArgs {
            template_path,
            list_favorites: false,
            name: Some(self.name.clone()),
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

        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use std::{
        fs::File,
        io::{BufRead, BufReader},
        path::Path,
    };

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
            "--templ-subdir",
            "",
            "--dest",
            &tmpdir.path().to_string_lossy(),
            proj_name,
        ]);

        new.run().unwrap();

        let proj_path = tmpdir.path().join(proj_name);

        assert!(proj_path.exists());
        assert!(proj_path.join(".git").exists());
        assert!(find_in_file(
            &format!("risc0-zkvm = {{ version = \"{RISC0_DEFAULT_VERSION}\" }}"),
            &proj_path.join("host/Cargo.toml")
        ));

        assert!(find_in_file(
            "#![no_std]",
            &proj_path.join("methods/guest/src/main.rs")
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
            "--templ-subdir",
            "",
            "--dest",
            &tmpdir.path().to_string_lossy(),
            "--no-git",
            "--use-git-branch",
            "main",
            proj_name,
        ]);

        new.run().unwrap();

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
            "--templ-subdir",
            "",
            "--dest",
            &tmpdir.path().to_string_lossy(),
            "--std",
            proj_name,
        ]);

        new.run().unwrap();

        let proj_path = tmpdir.path().join(proj_name);

        assert!(!find_in_file(
            "#![no_std]",
            &proj_path.join("methods/guest/src/main.rs")
        ));
        assert!(!find_in_file(
            "feature = ['std']",
            &proj_path.join("methods/guest/Cargo.toml")
        ));
    }
}
