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

pub mod constants;
pub mod parser;
pub mod types;

use std::{
    collections::BTreeMap,
    fs::File,
    io::{BufRead, BufReader, Write},
    ops::Not,
    path::{Path, PathBuf},
    process::Command,
    vec,
};

use anyhow::{Context, Result, bail};
use handlebars::Handlebars;
use serde::{Deserialize, Serialize};
use tempfile::tempdir;
use tracing::{debug, error, info, warn};
use types::{
    aliases::{CrateName, Profiles},
    profile::Profile,
    profile_settings::ProfileSettings,
    repo::{Repo, RepoCargoString, Value as _},
};

pub mod gen_profiles;

/// Validation Results fields
#[derive(Debug, Serialize, Deserialize)]
pub struct ValidationResults {
    /// Holds the crate name
    pub name: CrateName,

    /// Holds the profile settings
    pub settings: ProfileSettings,

    /// Holds the validator exit status
    pub status: RunStatus,

    /// Flag to represent if this profile has been customized
    pub custom_profile: bool,

    /// Holds the crate version
    pub version: Option<semver::Version>,

    /// Holds a sample of the guest build stdout
    ///
    /// Holds the first 200 lines of the guest build, if the build step fails
    #[serde(skip_serializing_if = "Option::is_none")]
    pub build_errors: Option<String>,
}

impl ValidationResults {
    fn new(
        name: impl ToString,
        settings: ProfileSettings,
        version: Option<semver::Version>,
        status: RunStatus,
        build_errors: Option<String>,
    ) -> Self {
        Self {
            custom_profile: settings.is_customized(),
            name: name.to_string(),
            settings,
            version,
            status,
            build_errors,
        }
    }
}

/// Profile for a given crate
///
/// Defines all information about a crate, including different possible
/// workarounds / customizations for a given crate, and optionally the results
#[derive(Debug, Default, Deserialize, Serialize)]
pub struct CrateProfile {
    /// Crate name
    pub name: String,

    /// Crate version
    pub version: String,

    /// Does the crate need 'std' feature
    pub std: bool,

    /// Inject a custom main() body
    ///
    /// # Example
    /// `println!("hello world");`
    pub custom_main: Option<String>,

    /// Inject a top level scope string, like a `use` statement.
    ///
    /// # Example
    /// `use lazy_static::lazy_static;`
    pub import_str: Option<String>,

    /// Toggle running the prover to test the guest crate
    #[serde(default = "bool::default")]
    pub run_prover: bool,

    /// Expect that build | run steps should fail
    #[serde(default = "bool::default")]
    pub should_fail: bool,

    /// Toggles if we should inject CC flags
    ///
    /// Reference: https://github.com/risc0/risc0/issues/443
    pub inject_cc_flags: bool,

    /// Toggles injecting a crossbeam atomics fix
    ///
    /// Reference: https://github.com/risc0/risc0/issues/444
    pub crossbeam_patch: bool,

    /// Validation results
    pub results: Option<ValidationResults>,

    /// Flag to represent if this profile has been customized
    pub customized: bool,
}

/// Top level profile config
///
/// The primary body of the YAML version of the config.
/// Defines the global variables for a given crates testing run.
#[derive(Debug, Clone, PartialEq, Eq, Serialize, Deserialize)]
pub struct ProfileConfig {
    pub profiles: Profiles,
}

impl ProfileConfig {
    pub fn profiles(&self) -> &Profiles {
        &self.profiles
    }

    pub fn replace_profiles(&self, profiles: Profiles) -> Self {
        Self { profiles }
    }
}

const CARGO_TOML_METHODS_TMP: &str = r#"
[package]
name = "methods"
version = "0.1.0"
edition = "2024"

[build-dependencies]
risc0-build = { {{ risc0_build }} }

[package.metadata.risc0]
methods = ["guest"]
"#;

const CARGO_TOML_TEMPLATE: &str = r#"
[package]
name = "method_name"
version = "0.1.0"
edition = "2024"

[workspace]

[dependencies]
risc0-zkvm = { {{ risc0_zkvm }}, default-features = false{{ risc0_feature_std }} }
{{ crate_line }}
"#;

const MAIN_RS_TEMPLATE: &str = r#"
#![no_main]
{{ no_std_line }}

{{ use_lines }}

risc0_zkvm::guest::entry!(main);

fn main() {
    {{ main_body }}
}

"#;

const MAX_ERROR_LINES: u64 = 200;

pub struct Validator {
    context: ProfileConfig,
    proj_out_dir: PathBuf,
    repo: Repo,
}

impl Validator {
    pub fn context(&self) -> &ProfileConfig {
        &self.context
    }

    pub fn proj_out_dir(&self) -> &PathBuf {
        &self.proj_out_dir
    }

    pub fn repo(&self) -> &Repo {
        &self.repo
    }
}

#[derive(strum::AsRefStr, Debug, Serialize, Deserialize)]
pub enum RunStatus {
    BuildFail,
    RunFail,
    Skipped,
    Success,
}

impl Validator {
    /// Uses [cargo-risczero] to generate a new base project
    fn gen_initial_project(&self, profile: &Profile) -> Result<PathBuf> {
        let project_name = "template_project";
        let output_path = self.proj_out_dir.join(project_name);

        if output_path.exists() {
            debug!("Found existing project: {}", output_path.to_string_lossy());
            return Ok(output_path);
        }

        debug!("generating {}", profile.name());

        let filtered_env = filter_flags(&[
            "TERM",
            "TZ",
            "USER",
            "LANG",
            "PATH",
            "RUSTUP_HOME",
            "RUST_VERSION",
            "CARGO_HOME",
        ]);

        let mut cmd = std::process::Command::new("cargo");
        cmd.arg("risczero");
        cmd.arg("new");
        cmd.arg(project_name);
        cmd.arg("--dest");
        cmd.arg(&self.proj_out_dir);
        cmd.arg("--guest-name=method_name");
        cmd.env_clear();
        cmd.envs(&filtered_env);

        if !profile.settings.std {
            cmd.arg("--no-std");
        }

        match self.repo() {
            Repo::Tag(_) => {
                cmd.arg("--tag");
                cmd.arg(self.repo().value());
            }
            Repo::Branch(_) => {
                cmd.arg("--branch");
                cmd.arg(self.repo().value());
            }
            Repo::Path(_) => {
                cmd.arg("--path");
                cmd.arg(self.repo().value());
            }
        }

        debug!(
            "running: '{}{}'",
            cmd.get_program().to_string_lossy(),
            cmd.get_args()
                .fold(String::new(), |a, b| a + " " + &b.to_string_lossy())
        );

        let status = cmd
            .status()
            .context("Failed to run: 'cargo risczero new'")?;
        if !status.success() {
            bail!("cargo risczero failed to run");
        }

        Ok(output_path)
    }

    /// Renders a given template to a file
    fn render_file(out_file: &Path, template: &str, vars: BTreeMap<&str, &str>) -> Result<()> {
        let mut reg = Handlebars::new();
        reg.register_escape_fn(handlebars::no_escape);
        let rendered_contents = reg.render_template(template, &vars)?;
        debug!(
            "Rendered template, writing it to: {}",
            out_file.to_string_lossy()
        );
        let mut fd = File::create(out_file)?;
        fd.write_all(rendered_contents.as_bytes())?;
        fd.flush()?;

        Ok(())
    }

    /// Customizes the template with crate profile specifics
    fn customize_guest(
        &self,
        profile: &Profile,
        version: &semver::Version,
        working_dir: &Path,
    ) -> Result<()> {
        let methods_dir = working_dir.join("methods");
        if !methods_dir.exists() {
            bail!(
                "Working directory {} missing methods/ dir",
                working_dir.to_string_lossy()
            )
        }

        let guest_dir = methods_dir.join("guest");
        if !guest_dir.exists() {
            bail!(
                "Working directory {} missing methods/guest dir",
                working_dir.to_string_lossy()
            );
        }

        let cargo_toml_file = guest_dir.join("Cargo.toml");
        if !cargo_toml_file.exists() {
            bail!("Guest methods missing Cargo.toml");
        }
        let main_file = guest_dir.join("src/main.rs");
        if !main_file.exists() {
            bail!("Guest methods missing src/main.rs");
        }

        // Generate the methods/Cargo.toml
        let methods_toml = methods_dir.join("Cargo.toml");

        let mut vars = BTreeMap::new();
        let risc0_build = self.repo.default_cargo_build();

        vars.insert("risc0_build", risc0_build.as_str());

        Self::render_file(&methods_toml, CARGO_TOML_METHODS_TMP, vars)?;

        // Generate the methods/guest/Cargo.toml file

        let mut vars = BTreeMap::new();

        let risc0_zkvm = self.repo.default_cargo_zkvm();

        let mut crate_line = format!("{} = {{ version = \"{version}\" }}", profile.name(),);
        if let Some(patch) = &profile.settings.patch {
            crate_line.push('\n');
            crate_line += patch;
        }

        profile
            .settings
            .std
            .then(|| vars.insert("risc0_feature_std", ", features = ['std']"));

        vars.insert("crate_line", &crate_line);
        vars.insert("risc0_zkvm", &risc0_zkvm);

        Self::render_file(&cargo_toml_file, CARGO_TOML_TEMPLATE, vars)?;

        // Generate the main.rs file
        let mut vars = BTreeMap::new();
        profile
            .settings
            .std
            .not()
            .then(|| vars.insert("no_std_line", "#![no_std]"));
        profile
            .settings
            .import_str
            .as_deref()
            .map(|import_str| vars.insert("use_lines", import_str));
        profile
            .settings
            .custom_main
            .as_deref()
            .map(|main_body| vars.insert("main_body", main_body));

        Self::render_file(&main_file, MAIN_RS_TEMPLATE, vars)?;

        Ok(())
    }

    // Builds the template project
    fn build_project(&self, profile: &Profile, working_dir: &Path) -> Result<(bool, String)> {
        debug!(
            "building {} - {}",
            profile.name(),
            working_dir.to_string_lossy()
        );

        // NOTE:
        // if you invoke this tool via `cargo run ...` it sets the CARGO_* and
        // RUST_TOOLCHAIN env vars, here we strip out all the extra env vars so
        // the cargo subcommands will correctly dispatch to rustup to pick the
        // target project's rust-toolchain.toml.
        let mut filtered_env = filter_flags(&["CC", "CXX", "HOME", "LANG", "PATH", "TERM", "TZ"]);

        // TODO: support GCC
        if profile.settings.inject_cc_flags {
            filtered_env.insert("CC".to_string(), "clang".to_string());
            filtered_env.insert(
                "CFLAGS_riscv32im_risc0_zkvm_elf".to_string(),
                "-target riscv32-unknown-elf".to_string(),
            );
        }

        let guest_log_file = tempfile::NamedTempFile::new()?;
        filtered_env.insert(
            "RISC0_GUEST_LOGFILE".to_string(),
            guest_log_file.path().to_string_lossy().to_string(),
        );

        let output = Command::new("cargo")
            .args(["build"])
            .env_clear()
            .envs(&filtered_env)
            .current_dir(working_dir)
            .output()?;

        let status = output.status;
        let res = if status.success() || (!status.success() && profile.settings.should_fail) {
            info!("{} - build - SUCCESS", profile.name());
            (true, String::new())
        } else {
            // Write out the build log to stderr
            // TODO: Capture and analyze this log for common classes of errors?
            let reader = BufReader::new(guest_log_file);
            let mut build_log_trimmed = String::new();
            let mut count = 0;
            for line in reader.lines().map_while(Result::ok) {
                if count < MAX_ERROR_LINES {
                    build_log_trimmed += &line;
                    build_log_trimmed += "\n";
                    count += 1;
                }
                writeln!(std::io::stderr(), "{line}")?;
            }

            std::io::stdout().write_all(&output.stdout).unwrap();
            std::io::stderr().write_all(&output.stderr).unwrap();

            error!("{} - build - FAILED", profile.name());
            (false, build_log_trimmed)
        };

        Ok(res)
    }

    /// Run the prover a given [CrateProfile]
    ///
    /// Requires that the build step has been run before hand
    fn run_prover(&self, profile: &Profile, working_dir: &Path) -> Result<bool> {
        let cmd = working_dir.join("target/debug/host");
        if !cmd.exists() {
            bail!("Could not find 'host' binary in working_dir build dir, did the build run?");
        }

        info!("running: {}", cmd.display());
        let mut cmd = Command::new(cmd);
        let mut cmd = cmd.current_dir(working_dir);
        if profile.settings.fast_mode {
            cmd = cmd.env("RISC0_EXPERIMENTAL_PREFLIGHT", "1")
        }

        let output = cmd.output()?;

        let status = output.status;
        let res = if (status.success() && !profile.settings.should_fail)
            || (!status.success() && profile.settings.should_fail)
        {
            info!("{} - run - SUCCESS", profile.name());
            true
        } else {
            std::io::stdout().write_all(&output.stdout).unwrap();
            std::io::stderr().write_all(&output.stderr).unwrap();

            error!("{} - run - FAILED", profile.name());
            false
        };

        Ok(res)
    }

    /// Run a given profile through the set of tests
    fn run(&self, profile: &Profile) -> Result<Vec<ValidationResults>> {
        if profile.should_skip() {
            warn!("Skipping {}", profile.name());
            return Ok(vec![ValidationResults::new(
                profile.name(),
                profile.settings().clone(),
                None,
                RunStatus::Skipped,
                None,
            )]);
        }

        let working_dir = self.gen_initial_project(profile)?;
        let mut results = Vec::new();
        for version in profile.versions() {
            self.customize_guest(profile, &version, &working_dir)?;
            let (build_success, build_errors) = self.build_project(profile, &working_dir)?;
            let create_validation_results = |status: RunStatus, build_errors: Option<String>| {
                ValidationResults::new(
                    profile.name(),
                    profile.settings().clone(),
                    Some(version.clone()),
                    status,
                    build_errors,
                )
            };
            if !build_success {
                results.push(create_validation_results(
                    RunStatus::BuildFail,
                    Some(build_errors),
                ));
                continue;
            }
            if profile.settings.run_prover && !self.run_prover(profile, &working_dir)? {
                results.push(create_validation_results(RunStatus::RunFail, None));
                continue;
            }
            results.push(create_validation_results(RunStatus::Success, None));
        }

        Ok(results)
    }

    // Run a single profile in the config by `name`
    pub fn run_single(&self, name: &str, profiles: &Profiles) -> Result<Vec<ValidationResults>> {
        for profile in profiles {
            if profile.name() == name {
                return self.run(profile);
            }
        }

        bail!("Failed to find crate profile: {}", name)
    }

    // Run all profiles in config
    pub fn run_all(&self, profiles: &Profiles) -> Result<Vec<ValidationResults>> {
        let mut results = vec![];
        for profile in profiles {
            results.push(self.run(profile)?);
        }

        Ok(results.into_iter().flatten().collect())
    }
}

#[derive(Debug, Clone, PartialEq, Eq, Serialize, Deserialize)]
pub struct ValidatorBuilder {
    #[serde(flatten)]
    context: ProfileConfig,
    out_dir: Option<PathBuf>,
    #[serde(skip)]
    repo: Repo,
}

impl ValidatorBuilder {
    pub fn new(context: ProfileConfig, repo: Repo, out_dir: Option<PathBuf>) -> Self {
        Self {
            context,
            repo,
            out_dir,
        }
    }

    pub fn out_dir_val(self, out_dir: PathBuf) -> Self {
        self.out_dir(Some(out_dir))
    }

    pub fn out_dir(mut self, out_dir: Option<PathBuf>) -> Self {
        self.out_dir = out_dir;
        self
    }

    pub fn build(self) -> Result<Validator> {
        let proj_out_dir = match self.out_dir {
            Some(dir) => dir,
            None => tempdir()?.path().to_path_buf(),
        };

        Ok(Validator {
            context: self.context,
            repo: self.repo,
            proj_out_dir,
        })
    }
}

impl TryFrom<ValidatorBuilder> for Validator {
    type Error = anyhow::Error;
    fn try_from(builder: ValidatorBuilder) -> Result<Self> {
        builder.build()
    }
}

fn filter_flags(flags: &[&str]) -> BTreeMap<String, String> {
    std::env::vars()
        .filter(|(k, _)| flags.contains(&k.as_str()))
        .collect()
}
