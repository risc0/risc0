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

use std::{fs, io, io::Write, path::PathBuf, process::Stdio};

use anyhow::{Context, Result, anyhow, bail, ensure};
use cargo_metadata::{Artifact, ArtifactProfile, Message};
use clap::{Args, Subcommand};
use risc0_build::cargo_command;
use risc0_zkvm::{ExecutorEnv, ExitCode, default_executor};
use tempfile::{TempDir, tempdir};

const ZIP_CONTENTS: &[u8] = include_bytes!(concat!(env!("OUT_DIR"), "/cargo-risczero.zip"));

/// `cargo risczero guest`
#[derive(Debug, Args)]
pub struct GuestCommand {
    #[command(subcommand)]
    command: GuestSubCommands,
}

/// Subcommands of cargo that are supported by this cargo risczero command.
#[derive(Debug, Subcommand)]
pub enum GuestSubCommands {
    /// Invocation of `cargo risczero build` which calls `cargo build`.
    Build(CommonArgs),

    /// Invocation of `cargo risczero build` which calls `cargo test --no-run`.
    Test(CommonArgs),
}

/// Common arguments for guest commands.
#[derive(Debug, Args)]
pub struct CommonArgs {
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

fn get_zip_file(dir: &TempDir, filename: &str) -> Result<PathBuf> {
    let mut zip = zip::ZipArchive::new(io::Cursor::new(ZIP_CONTENTS))?;
    let mut file = zip.by_name(filename)?;
    let dest_path = dir.path().join(filename);
    let mut dest_file = fs::File::create(&dest_path)?;
    io::copy(&mut file, &mut dest_file)?;
    Ok(dest_path)
}

impl GuestCommand {
    /// Execute this command.
    ///
    /// subcommand specifies which cargo subcommand to run, e.g. "build" or
    /// "test". If "test", this function will apply extra steps to approximate
    /// the behavior of cargo test, running tests with the RISC Zero
    /// executor.
    pub fn run(&self) -> Result<()> {
        let args = match &self.command {
            GuestSubCommands::Build(args) => args,
            GuestSubCommands::Test(args) => args,
        };

        // Determine the manifest directory and get it's canonical path.
        let manifest_path = match fs::canonicalize(&args.manifest_path) {
            Ok(path) => path,
            Err(ref err) => bail!(
                "failed to resolve manifest path `{}`: {}",
                &args.manifest_path.display(),
                err
            ),
        };

        // Unpack the risc0-zkvm-platform.a file that is included in this binary.
        let tmpdir = tempdir()?;
        let rust_runtime = get_zip_file(&tmpdir, "risc0-zkvm-platform.a")?;

        // Determine the target directory where the build artifacts should be placed.
        let target_dir = &args
            .target_dir
            .clone()
            .unwrap_or_else(|| risc0_build::get_target_dir(&manifest_path));

        fs::create_dir_all(&target_dir)
            .with_context(|| "failed to ensure target directory exists")?;

        let subcmd = match &self.command {
            GuestSubCommands::Build(_) => "build",
            GuestSubCommands::Test(_) => "test",
        };

        // Build the cargo build/test command for building the crate.
        let mut cmd = cargo_command(
            subcmd,
            &[
                "-C".to_string(),
                format!(
                    "link_arg={}",
                    rust_runtime
                        .to_str()
                        .ok_or_else(|| anyhow!("invalid path string for rust_runtime"))?
                ),
            ],
        );

        cmd.arg("--message-format=json");

        cmd.args(&[
            "--manifest-path",
            manifest_path
                .to_str()
                .ok_or_else(|| anyhow!("invalid path string for manifest_path"))?,
            "--target-dir",
            target_dir
                .to_str()
                .ok_or_else(|| anyhow!("invalid path string for target_dir"))?,
        ]);

        // TODO: Give the user a way to request a release build.
        // if !is_debug() {
        //    cmd.args(&["--release"]);
        //}

        // Strip out --no-run if specified, since we always pass --no-run.
        let mut no_run_flag = false;
        let mut test_args = vec![];
        match &self.command {
            GuestSubCommands::Test(args) => {
                let mut test_args_delimiter_seen = false;
                cmd.arg("--no-run");
                for arg in &args.args {
                    if test_args_delimiter_seen {
                        test_args.push(arg.clone());
                    } else if arg == "--no-run" {
                        no_run_flag = true;
                    } else if arg == "--" {
                        test_args_delimiter_seen = true;
                    } else {
                        cmd.arg(&arg);
                    }
                }
            }
            GuestSubCommands::Build(args) => {
                cmd.args(&args.args);
            }
        }

        println!("Running command: {:?}", &cmd);

        // Start the cargo command as a subprocess.
        let mut child = cmd.stdout(Stdio::piped()).spawn()?;

        // Parse stdout from the command and record any test binaries that get compiled.
        let reader = std::io::BufReader::new(
            child
                .stdout
                .take()
                .ok_or_else(|| anyhow!("failed to read from cmd stdout"))?,
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
        if matches!(self.command, GuestSubCommands::Test(_)) && !no_run_flag {
            eprintln!("Running tests: {tests:?}");

            for test in tests {
                eprintln!("Running test in guest: {test} {test_args:?}");
                let mut builder = ExecutorEnv::builder();
                builder
                    // Add the test elf path as arg 0, the POSIX program name
                    .args(&[test.clone()])
                    .args(&test_args)
                    .env_var("RUST_TEST_NOCAPTURE", "1");

                // Forward all environment variables set on this process.
                for (key, val) in std::env::vars().into_iter() {
                    builder.env_var(&key, &val);
                }

                let env = builder.build()?;

                let exec = default_executor();
                let session = exec.execute(env, &fs::read(test)?)?;
                ensure!(
                    session.exit_code == ExitCode::Halted(0),
                    "test exited with code {:?}",
                    session.exit_code
                );
            }
        };
        Ok(())
    }
}
