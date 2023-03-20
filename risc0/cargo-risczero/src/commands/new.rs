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
use convert_case::{Case, Casing};

const RISC0_GH_REPO: &str = "https://github.com/risc0/risc0";
const RICS0_TEMPLATE_DIR: &str = "templates/rust-stater";
const RISC0_RELEASE_TAG: &str = "v0.13.0";

#[derive(Parser)]
/// `cargo risczero new`
pub struct NewCommand {
    /// Name which will be used as the output project name.
    #[arg()]
    pub name: String,

    /// GH repository name.
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
}

impl NewCommand {
    pub fn run(&self) {
        let subfolder = if self.template == RISC0_GH_REPO {
            Some(RICS0_TEMPLATE_DIR.to_string())
        } else {
            None
        };

        let dest_dir = if let Some(dest_dir) = self.dest.clone() {
            dest_dir
        } else {
            std::env::current_dir()
                .expect("Failed to fetch cwd")
                .join(self.name.clone())
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

        let risc0_version = std::env::var("CARGO_PKG_VERSION").expect("Missing env var");

        let mut template_variables = vec![format!("risc0_version={risc0_version}")];
        if let Some(branch) = self.use_git_branch.as_ref() {
            template_variables.push(format!("risc0_crate_branch={branch}"))
        }

        cargo_generate::generate(GenerateArgs {
            template_path,
            list_favorites: false,
            name: Some(self.name.to_case(Case::Snake)),
            force: true,
            verbose: false,
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
    use super::*;

    #[test]
    fn basic_new() {
        let new = NewCommand::parse_from(["new", "my_project"]);
        assert_eq!(new.name, "my_project");
    }
}
