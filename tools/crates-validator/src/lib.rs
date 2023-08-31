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

use std::{
    cell::RefCell,
    collections::BTreeMap,
    fs::File,
    io::{BufRead, BufReader, Write},
    path::{Path, PathBuf},
    process::Command,
};

use anyhow::{bail, Context, Result};
use handlebars::Handlebars;
use serde::{Deserialize, Serialize};
use tempfile::tempdir;
use tracing::{debug, error, info, warn};

pub mod profiles;
pub mod selected_crates;

/// Validation Results fields
#[derive(Debug, Serialize, Deserialize)]
pub struct ValidationResults {
    /// Holds the validator exit status
    pub status: RunStatus,

    /// Holds a sample of the guest build stdout
    ///
    /// Holds the first 200 lines of of the guest build, if the build step fails
    pub build_errors: Option<String>,
}

impl ValidationResults {
    fn from(status: RunStatus) -> Self {
        Self {
            status,
            build_errors: None,
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
    pub version: Option<String>,

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
/// The primary body of the JSON version of the config.
/// Defines the global variables for a given crates testing run.
#[derive(Debug, Serialize, Deserialize)]
pub struct ProfileConfig {
    /// Define which Github branch should be used for templates and crate
    /// imports
    pub risc0_gh_branch: Option<String>,
    /// Directory where risc0 is for templates and crate imports
    pub risc0_path: Option<String>,
    /// Enables `RISC0_EXPERIMENTAL_PREFLIGHT`
    #[serde(default = "bool::default")]
    pub fast_mode: bool,
    /// Array of [CrateProfile]
    pub profiles: RefCell<Vec<CrateProfile>>,
}

const CARGO_TOML_METHODS_TMP: &str = r#"
[package]
name = "methods"
version = "0.1.0"
edition = "2021"

[build-dependencies]
risc0-build = { {{ risc0_build }} }

[package.metadata.risc0]
methods = ["guest"]
"#;

const CARGO_TOML_TEMPLATE: &str = r#"
[package]
name = "method_name"
version = "0.1.0"
edition = "2021"

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

pub fn main() {
    {{ main_body }}
}

"#;

const CROSSBEAM_PATCH: &str = r#"
[patch.crates-io]
crossbeam = { git = "https://github.com/risc0/crossbeam", rev = "b25eb50f8c193f36dacb6739692261ea96827bb7" }
crossbeam-utils = { git = "https://github.com/risc0/crossbeam", rev = "b25eb50f8c193f36dacb6739692261ea96827bb7" }
crossbeam-channel = { git = "https://github.com/risc0/crossbeam", rev = "b25eb50f8c193f36dacb6739692261ea96827bb7" }"#;

const MAX_ERROR_LINES: u64 = 200;

pub struct Validator {
    pub context: ProfileConfig,
    proj_out_dir: PathBuf,
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
    fn gen_initial_project(&self, profile: &CrateProfile) -> Result<PathBuf> {
        let project_name = "template_project";
        let output_path = self.proj_out_dir.join(project_name);

        if output_path.exists() {
            debug!("Found existing project: {}", output_path.to_string_lossy());
            return Ok(output_path);
        }

        debug!("generating {}", profile.name);

        let filtered_env: std::collections::HashMap<String, String> = std::env::vars()
            .filter(|(k, _)| {
                k == "TERM"
                    || k == "TZ"
                    || k == "USER"
                    || k == "LANG"
                    || k == "PATH"
                    || k == "RUSTUP_HOME"
                    || k == "RUST_VERSION"
                    || k == "CARGO_HOME"
            })
            .collect();

        let mut cmd = std::process::Command::new("cargo");
        cmd.arg("risczero");
        cmd.arg("new");
        cmd.arg(project_name);
        cmd.arg("--no-git");
        cmd.arg("--dest");
        cmd.arg(&self.proj_out_dir);
        cmd.env_clear();
        cmd.envs(&filtered_env);

        if profile.std {
            cmd.arg("--std");
        }

        match (&self.context.risc0_path, &self.context.risc0_gh_branch) {
            (None, None) => {
                bail!("Profile must assign either 'risc0_template_path' or 'risc0_gh_branch'")
            }
            (Some(..), Some(..)) => bail!(
                "Profile assigns both 'risc0_template_path' and 'risc0_gh_branch' pick just one"
            ),
            (Some(r0_path), None) => {
                let r0_template_path = Path::new(r0_path).join("templates").join("rust-starter");
                if !r0_template_path.exists() {
                    bail!(
                        "Failed to find {} on disk",
                        r0_template_path.to_string_lossy()
                    );
                }
                cmd.arg("--template");
                cmd.arg(r0_template_path);
                cmd.arg("--templ-subdir");
                cmd.arg("");
                cmd.arg("--path");
                cmd.arg(r0_path);
            }
            (None, Some(branch)) => {
                cmd.arg("--branch");
                cmd.arg(branch);
            }
        };

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
    fn customize_guest(&self, profile: &CrateProfile, working_dir: &Path) -> Result<()> {
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
        let risc0_build = if let Some(gh_branch) = &self.context.risc0_gh_branch {
            format!("git = \"https://github.com/risc0/risc0.git\", branch = \"{gh_branch}\"")
        } else if let Some(r0_path) = &self.context.risc0_path {
            format!("path = \"{r0_path}/risc0/build\"")
        } else {
            bail!("Unsupported, missing risc0_path or risc0_gh_branch");
        };

        vars.insert("risc0_build", risc0_build.as_str());

        Self::render_file(&methods_toml, CARGO_TOML_METHODS_TMP, vars)?;

        // Generate the methods/guest/Cargo.toml file

        let mut vars = BTreeMap::new();
        let risc0_feature_std = if profile.std {
            ", features = ['std']"
        } else {
            ""
        };

        let risc0_zkvm = if let Some(gh_branch) = &self.context.risc0_gh_branch {
            format!("git = \"https://github.com/risc0/risc0.git\", branch = \"{gh_branch}\"")
        } else if let Some(r0_path) = &self.context.risc0_path {
            format!("path = \"{r0_path}/risc0/zkvm\"")
        } else {
            bail!("Unsupported, missing risc0_path or risc0_gh_branch");
        };

        let mut crate_line = format!(
            "{} = {{ version = \"{}\" }}",
            profile.name,
            profile.version.as_ref().unwrap()
        );
        if profile.crossbeam_patch {
            crate_line += CROSSBEAM_PATCH;
        }

        vars.insert("risc0_feature_std", risc0_feature_std);
        vars.insert("crate_line", &crate_line);
        vars.insert("risc0_zkvm", &risc0_zkvm);

        Self::render_file(&cargo_toml_file, CARGO_TOML_TEMPLATE, vars)?;

        // Generate the main.rs file

        let mut vars = BTreeMap::new();
        vars.insert("no_std_line", if profile.std { "" } else { "#![no_std]" });
        vars.insert(
            "use_lines",
            if let Some(import_str) = &profile.import_str {
                import_str
            } else {
                ""
            },
        );
        vars.insert(
            "main_body",
            if let Some(main_body) = &profile.custom_main {
                main_body
            } else {
                ""
            },
        );

        Self::render_file(&main_file, MAIN_RS_TEMPLATE, vars)?;

        Ok(())
    }

    // Builds the template project
    fn build_project(&self, profile: &CrateProfile, working_dir: &Path) -> Result<(bool, String)> {
        debug!(
            "building {} - {}",
            profile.name,
            working_dir.to_string_lossy()
        );

        // NOTE:
        // if you invoke this tool via `cargo run ...` it sets the CARGO_* and
        // RUST_TOOLCHAIN env vars, here we strip out all the extra env vars so
        // the cargo subcommands will correctly dispatch to rustup to pick the
        // target project's rust-toolchain.toml.
        let mut filtered_env: std::collections::HashMap<String, String> = std::env::vars()
            .filter(|(k, _)| {
                k == "TERM" || k == "TZ" || k == "CC" || k == "CXX" || k == "LANG" || k == "PATH"
            })
            .collect();

        // TODO: support GCC
        if profile.inject_cc_flags {
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
        let res = if status.success() || (!status.success() && profile.should_fail) {
            info!("{} - build - SUCCESS", profile.name);
            (true, String::new())
        } else {
            // Write out the build log to stderr
            // TODO: Capture and analyze this log for common classes of errors?
            let reader = BufReader::new(guest_log_file);
            let mut build_log_trimmed = String::new();
            let mut count = 0;
            for line in reader.lines().flatten() {
                if count < MAX_ERROR_LINES {
                    build_log_trimmed += &line;
                    build_log_trimmed += "\n";
                    count += 1;
                }
                writeln!(std::io::stderr(), "{line}")?;
            }

            std::io::stdout().write_all(&output.stdout).unwrap();
            std::io::stderr().write_all(&output.stderr).unwrap();

            error!("{} - build - FAILED", profile.name);
            (false, build_log_trimmed)
        };

        Ok(res)
    }

    /// Run the prover a given [CrateProfile]
    ///
    /// Requires that the build step has been run before hand
    fn run_prover(&self, profile: &CrateProfile, working_dir: &Path) -> Result<bool> {
        let cmd = working_dir.join("target/debug/host");
        if !cmd.exists() {
            bail!("Could not find 'host' binary in working_dir build dir, did the build run?");
        }

        info!("running: {}", cmd.display());
        let mut cmd = Command::new(cmd);
        let mut cmd = cmd.current_dir(working_dir);
        if self.context.fast_mode {
            cmd = cmd.env("RISC0_EXPERIMENTAL_PREFLIGHT", "1")
        }

        let output = cmd.output()?;

        let status = output.status;
        let res = if (status.success() && !profile.should_fail)
            || (!status.success() && profile.should_fail)
        {
            info!("{} - run - SUCCESS", profile.name);
            true
        } else {
            std::io::stdout().write_all(&output.stdout).unwrap();
            std::io::stderr().write_all(&output.stderr).unwrap();

            error!("{} - run - FAILED", profile.name);
            false
        };

        Ok(res)
    }

    /// Run a given profile through the set of tests
    fn run(&self, profile: &mut CrateProfile) -> Result<()> {
        if profiles::SKIP_CRATES.contains(&profile.name.as_str()) {
            warn!("Skipping {} due to SKIP_CRATES", profile.name);
            profile.results = Some(ValidationResults::from(RunStatus::Skipped));
            return Ok(());
        }
        let working_dir = self.gen_initial_project(profile)?;
        self.customize_guest(profile, &working_dir)?;
        let (build_success, build_errors) = self.build_project(profile, &working_dir)?;
        if !build_success {
            profile.results = Some(ValidationResults {
                status: RunStatus::BuildFail,
                build_errors: Some(build_errors),
            });
            return Ok(());
        }
        if profile.run_prover && !self.run_prover(profile, &working_dir)? {
            profile.results = Some(ValidationResults::from(RunStatus::RunFail));
            return Ok(());
        }

        profile.results = Some(ValidationResults::from(RunStatus::Success));
        Ok(())
    }

    /// Run a single profile in the config by `name`
    pub fn run_single(&self, name: &str) -> Result<()> {
        for profile in self.context.profiles.borrow_mut().iter_mut() {
            if profile.name == name {
                self.run(profile)?;
                return Ok(());
            }
        }

        bail!("Failed to find crate profile: {}", name)
    }

    /// Run all profiles in config
    pub fn run_all(&self) -> Result<()> {
        for profile in self.context.profiles.borrow_mut().iter_mut() {
            self.run(profile)?;
        }

        Ok(())
    }
}

pub struct ValidatorBuilder {
    context: ProfileConfig,
    out_dir: Option<PathBuf>,
}

impl ValidatorBuilder {
    pub fn new(context: ProfileConfig) -> Self {
        Self {
            context,
            out_dir: None,
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
        let out_dir = if let Some(dir) = self.out_dir {
            dir
        } else {
            tempdir()?.path().to_path_buf()
        };

        Ok(Validator {
            context: self.context,
            proj_out_dir: out_dir,
        })
    }
}
