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

use std::{fs, io, io::Write, path::PathBuf, process::Stdio};

use anyhow::{anyhow, bail, Context};
use cargo_metadata::{Artifact, ArtifactProfile, Message};
use clap::Parser;
use risc0_zkvm::{Executor, ExecutorEnv};
use tempfile::{tempdir, TempDir};

/// Subcommands of cargo that are supported by this cargo risczero command.
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub enum BuildSubcommand {
    /// Invocation of `cargo risczero build` which calls `cargo build`.
    Build,

    /// Invocation of `cargo risczero build` which calls `cargo test --no-run`.
    Test,
}

impl AsRef<str> for BuildSubcommand {
    fn as_ref(&self) -> &'static str {
        match &self {
            Self::Build => "build",
            Self::Test => "test",
        }
    }
}

#[derive(Parser)]
/// `cargo risczero build`
pub struct BuildCommand {
    /// Path to the Cargo.toml file for the crate to be built.
    #[clap(long, default_value = "./Cargo.toml")]
    pub manifest_path: PathBuf,

    /// Output directory for build artifacts.
    ///
    /// Determined from package metadata if not supplied.
    #[clap(long)]
    pub target_dir: Option<PathBuf>,

    /// Additional arguments to pass to "cargo build" on the guest
    pub args: Vec<String>,
}

static ZIP_CONTENTS: &[u8] = include_bytes!(concat!(env!("OUT_DIR"), "/cargo-risczero.zip"));

fn get_zip_file(dir: &TempDir, filename: &str) -> anyhow::Result<PathBuf> {
    let mut zip = zip::ZipArchive::new(io::Cursor::new(ZIP_CONTENTS))?;
    let mut file = zip.by_name(filename)?;
    let dest_path = dir.path().join(filename);
    let mut dest_file = fs::File::create(&dest_path)?;
    io::copy(&mut file, &mut dest_file)?;
    Ok(dest_path)
}

impl BuildCommand {
    /// Execute this command.
    ///
    /// subcommand specifies which cargo subcommand to run, e.g. "build" or
    /// "test". If "test", this function will apply extra steps to approximate
    /// the behavior of cargo test, running tests with the RISC Zero
    /// executor.
    pub fn run(&self, subcommand: BuildSubcommand) -> anyhow::Result<()> {
        // Determine the manifest directory and get it's canonical path.
        let manifest_path = match fs::canonicalize(&self.manifest_path) {
            Ok(path) => path,
            Err(ref err) => bail!(
                "failed to resolve manifest path `{}`: {}",
                &self.manifest_path.display(),
                err
            ),
        };

        // Unpack the rust-runtime.a file that is included in this binary.
        let tmpdir = tempdir()?;

        let rust_runtime = get_zip_file(&tmpdir, "rust-runtime.a")?;
        eprintln!("Runtime: {rust_runtime:?}");

        // Determine the target directory where the build artifacts should be placed.
        let target_dir = &self
            .target_dir
            .clone()
            .unwrap_or_else(|| risc0_build::get_target_dir(&manifest_path));

        fs::create_dir_all(&target_dir)
            .with_context(|| "failed to ensure target directory exists")?;

        let guest_build_env = risc0_build::setup_guest_build_env(&target_dir);

        // Build the cargo build/test command for building the crate.
        let mut cmd = guest_build_env.cargo_command(
            subcommand.as_ref(),
            true,
            &[
                "-C",
                &format!(
                    "link_arg={}",
                    rust_runtime
                        .to_str()
                        .expect("invalid path string for rust_runtime")
                ),
            ],
        );
        cmd.arg("--message-format=json");

        // Strip out --no-run if specified, since we always pass --no-run.
        let mut no_run_flag = false;
        if subcommand == BuildSubcommand::Test {
            cmd.arg("--no-run");
            for arg in &self.args {
                if arg == "--no-run" {
                    no_run_flag = true;
                } else {
                    cmd.arg(&arg);
                }
            }
        } else {
            cmd.args(&self.args);
        }

        eprintln!("running {cmd:?}");
        let mut child = cmd.stdout(Stdio::piped()).spawn()?;

        // Parse stdout from the command and record any test binaries that get compiled.
        let reader = std::io::BufReader::new(
            child
                .stdout
                .take()
                .ok_or(anyhow!("failed to read from cmd stdout"))?,
        );
        let mut tests: Vec<String> = Vec::new();
        for message in Message::parse_stream(reader) {
            match message? {
                Message::CompilerArtifact(Artifact {
                    executable: Some(exec_path),
                    profile: ArtifactProfile { test: true, .. },
                    ..
                }) => {
                    tests.push(exec_path.to_string());
                }
                Message::CompilerMessage(msg) => {
                    write!(io::stderr(), "{}", msg)?;
                }
                _ => (),
            }
        }

        let output = child
            .wait()
            .with_context(|| "couldn't get cargo's exit status")?;
        if !output.success() {
            bail!("failed to build crate")
        }

        // If we are running `cargo risczero test`, load each test binary into the
        // executor and run them.
        if subcommand == BuildSubcommand::Test && !no_run_flag {
            eprintln!("Running tests: {tests:?}");

            for t in &tests {
                eprintln!("Running test {t}");
                let mut env_builder = ExecutorEnv::builder();

                env_builder
                    .env_var("RUST_TEST_NOCAPTURE", "1")
                    .env_var("ARGC", &(self.args.len() + 1).to_string())
                    .env_var("ARGV_0", &t);

                for (i, arg) in self.args.iter().enumerate() {
                    env_builder.env_var(&format!("ARGV_{}", i + 1), &arg);
                }

                let env = env_builder.build()?;
                let mut exec = Executor::from_elf(env, &fs::read(t)?)?;
                exec.run()?;
            }
        };
        Ok(())
    }
}
