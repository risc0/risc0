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

use std::path::PathBuf;

use anyhow::{anyhow, Result};
use clap::Parser;
use const_format::concatcp;
use regex::Regex;
use semver::VersionReq;
use std::collections::BTreeMap;
use text_io::read;

const RISC0_DEFAULT_VERSION: &str = env!("CARGO_PKG_VERSION");
const RISC0_RELEASE_TAG: &str = concatcp!("v", RISC0_DEFAULT_VERSION);

const HOST_MAIN: &str = include_str!("../../templates/rust-starter/host/src/main.rs");
const HOST_CARGO_TOML: &str = include_str!("../../templates/rust-starter/host/Cargo-toml");
const PROJECT_CARGO_TOML: &str = include_str!("../../templates/rust-starter/Cargo-toml");
const METHODS_BUILD_SCRIPT: &str = include_str!("../../templates/rust-starter/methods/build.rs");
const METHODS_CARGO_TOML: &str = include_str!("../../templates/rust-starter/methods/Cargo-toml");
const METHODS_LIB: &str = include_str!("../../templates/rust-starter/methods/src/lib.rs");
const GUEST_CARGO_TOML: &str =
    include_str!("../../templates/rust-starter/methods/guest/Cargo-toml");
const GUEST_MAIN: &str = include_str!("../../templates/rust-starter/methods/guest/src/main.rs");
static PROJECT_TEMPLATED_FILES: &[(&str, &str)] = &[
    ("host/src/main.rs", HOST_MAIN),
    ("host/Cargo.toml", HOST_CARGO_TOML),
    ("Cargo.toml", PROJECT_CARGO_TOML),
    ("methods/build.rs", METHODS_BUILD_SCRIPT),
    ("methods/Cargo.toml", METHODS_CARGO_TOML),
    ("methods/src/lib.rs", METHODS_LIB),
    ("methods/guest/Cargo.toml", GUEST_CARGO_TOML),
    ("methods/guest/src/main.rs", GUEST_MAIN),
];

const RUST_TOOLCHAIN_TOML: &str = include_str!("../../templates/rust-starter/rust-toolchain.toml");
const README: &str = include_str!("../../templates/rust-starter/README.md");
const GIT_IGNORE: &str = include_str!("../../templates/rust-starter/.gitignore");
const LICENSE: &str = include_str!("../../templates/rust-starter/LICENSE");
static PROJECT_NON_TEMPLATED_FILES: &[(&str, &str)] = &[
    ("README.md", README),
    ("rust-toolchain.toml", RUST_TOOLCHAIN_TOML),
    (".gitignore", GIT_IGNORE),
    ("LICENSE", LICENSE),
];

/// The captured output of `cargo metadata` that was run on the current crate at build time.
fn own_cargo_metadata_output() -> cargo_metadata::Metadata {
    serde_json::from_str(include_str!(concat!(
        env!("OUT_DIR"),
        "/cargo_metadata_output.json"
    )))
    .expect("generated cargo_metadata_output.json contains invalid data")
}

fn build_own_dependency_graph(metadata: &cargo_metadata::Metadata) -> BTreeMap<&str, &VersionReq> {
    let crate_name = std::env!("CARGO_CRATE_NAME").replace("_", "-");
    let packages = &metadata.packages;
    let package = packages
        .iter()
        .find(|p| p.name == crate_name)
        .unwrap_or_else(|| {
            panic!(
                "cannot find crate {crate_name} in {:#?}",
                packages.iter().map(|p| &p.name).collect::<Vec<_>>()
            )
        });
    package
        .dependencies
        .iter()
        .map(|dep| (&dep.name[..], &dep.req))
        .collect()
}

/// `cargo risczero new`
#[derive(Parser)]
pub struct NewCommand {
    /// Name which will be used as the output project name.
    #[arg()]
    pub name: String,

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
    pub no_std: bool,

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

        let mut template_variables = Vec::new();

        if let Some(branch) = self.use_git_branch.as_ref() {
            let spec =
                format!("git = \"https://github.com/risc0/risc0.git\", branch = \"{branch}\"");
            template_variables.push((Regex::new(r"\{\{ *risc0_build *\}\}")?, spec.clone()));
            template_variables.push((Regex::new(r"\{\{ *risc0_zkvm *\}\}")?, spec));
        } else if let Some(path) = self.path.as_ref() {
            let path = path.to_str().unwrap();
            let build = format!("path = \"{path}/risc0/build\"");
            let zkvm = format!("path = \"{path}/risc0/zkvm\"");
            template_variables.push((Regex::new(r"\{\{ *risc0_build *\}\}")?, build));
            template_variables.push((Regex::new(r"\{\{ *risc0_zkvm *\}\}")?, zkvm));
        } else {
            let own_metadata = own_cargo_metadata_output();
            let own_dependencies = build_own_dependency_graph(&own_metadata);

            let build_spec = format!("version = \"{}\"", own_dependencies["risc0-build"]);
            template_variables.push((Regex::new(r"\{\{ *risc0_build *\}\}")?, build_spec));

            let zkvm_spec = format!("version = \"{}\"", own_dependencies["risc0-zkvm"]);
            template_variables.push((Regex::new(r"\{\{ *risc0_zkvm *\}\}")?, zkvm_spec));
        }

        let guest_name = match &self.guest_name {
            Some(name) => name.clone(),
            None => {
                eprint!(
                    "Guest name was not supplied through the --guest-name option. Please enter\x20\
                    package name for your template or press [enter] to use default guest package\x20\
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

        let guest_name_const = guest_name.replace('-', "_").to_ascii_uppercase();
        template_variables.push((
            Regex::new(r"\{\{ *guest_package_name *\}\}")?,
            format!("\"{guest_name}\""),
        ));
        template_variables.push((
            Regex::new(r"\{\{ *guest_id *\}\}")?,
            format!("{guest_name_const}_ID"),
        ));
        template_variables.push((
            Regex::new(r"\{\{ *guest_elf *\}\}")?,
            format!("{guest_name_const}_ELF"),
        ));

        if !self.no_std {
            template_variables.push((
                Regex::new(r"\{\{ *risc0_feature_std *\}\}")?,
                ", features = ['std']".to_string(),
            ));
            template_variables.push((Regex::new(r"\{\{ *no_std_preamble *\}\}")?, "".to_string()));
        } else {
            let no_std_preamble = "#![no_main]\n\
#![no_std]\n\
risc0_zkvm::guest::entry!(main);\n";
            template_variables.push((
                Regex::new(r"\{\{ *no_std_preamble *\}\}")?,
                no_std_preamble.to_string(),
            ));
            template_variables.push((
                Regex::new(r"\{\{ *risc0_feature_std *\}\}")?,
                "".to_string(),
            ));
        }
        self.gen_template(dest_dir, template_variables)?;

        Ok(())
    }

    fn gen_template(&self, dest: PathBuf, template_variables: Vec<(Regex, String)>) -> Result<()> {
        let root = dest.join(self.name.clone());

        // generate host directories
        std::fs::create_dir_all(root.join("host/src"))?;
        std::fs::create_dir_all(root.join("methods/src"))?;
        std::fs::create_dir_all(root.join("methods/guest/src"))?;

        for (filepath, content) in PROJECT_TEMPLATED_FILES {
            std::fs::write(
                root.join(filepath),
                Self::gen_file(content, template_variables.clone()),
            )?;
        }

        for (filepath, content) in PROJECT_NON_TEMPLATED_FILES {
            std::fs::write(root.join(filepath), content)?;
        }

        Ok(())
    }

    fn gen_file(haystack: &str, patterns: Vec<(Regex, String)>) -> String {
        let mut haystack: String = haystack.to_string();
        for (pattern, replace) in patterns {
            haystack = pattern.replace_all(&haystack, replace).to_string();
        }
        haystack
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

    fn make_test_env() -> (TempDir, &'static str) {
        let tmpdir = tempdir().expect("Failed to create tempdir");
        (tmpdir, "my_project")
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
        let new = NewCommand::parse_from(["new", "--guest-name", "method", "my_project"]);
        assert_eq!(new.name, "my_project");
    }

    #[test]
    fn basic_generate() {
        let (tmpdir, proj_name) = make_test_env();

        let new = NewCommand::parse_from([
            "new",
            "--dest",
            &tmpdir.path().to_string_lossy(),
            "--guest-name",
            "method",
            proj_name,
        ]);

        new.run().unwrap();

        let proj_path = tmpdir.path().join(proj_name);

        let own_metadata = own_cargo_metadata_output();
        let own_dependencies = build_own_dependency_graph(&own_metadata);

        assert!(proj_path.exists());

        let zkvm_version = own_dependencies["risc0-zkvm"];
        assert!(find_in_file(
            &format!("risc0-zkvm = {{ version = \"{zkvm_version}\" }}"),
            &proj_path.join("host/Cargo.toml")
        ));

        let build_version = own_dependencies["risc0-build"];
        assert!(!find_in_file(
            &format!("risc0-build = {{ version = \"{build_version}\" }}"),
            &proj_path.join("methods/guest/Cargo.toml")
        ));

        assert!(!find_in_file(
            "#![no_std]",
            &proj_path.join("methods/guest/src/main.rs")
        ));
    }

    #[test]
    fn generate_no_git_branch() {
        let (tmpdir, proj_name) = make_test_env();

        let new = NewCommand::parse_from([
            "new",
            "--dest",
            &tmpdir.path().to_string_lossy(),
            "--use-git-branch",
            "main",
            "--guest-name",
            "method",
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
    fn generate_no_std() {
        let (tmpdir, proj_name) = make_test_env();

        let new = NewCommand::parse_from([
            "new",
            "--dest",
            &tmpdir.path().to_string_lossy(),
            "--no-std",
            "--guest-name",
            "method",
            proj_name,
        ]);

        new.run().unwrap();

        let proj_path = tmpdir.path().join(proj_name);

        assert!(find_in_file(
            "#![no_std]",
            &proj_path.join("methods/guest/src/main.rs")
        ));
        assert!(!find_in_file(
            "feature = ['std']",
            &proj_path.join("methods/guest/Cargo.toml")
        ));
    }
}
