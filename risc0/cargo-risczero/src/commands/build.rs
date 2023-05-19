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

use cargo_metadata::{Artifact, ArtifactProfile, Message};
use clap::Parser;
use risc0_zkvm::{Executor, ExecutorEnv};
use tempfile::{tempdir, TempDir};

#[derive(Parser)]
/// `cargo risczero build`
pub struct BuildCommand {
    /// Manifest directory path.
    #[clap(long, default_value = ".")]
    pub manifest_dir: PathBuf,

    /// Output directory for build artifacts.
    /// Determined from package metadata if not supplied.
    #[clap(long)]
    pub target_dir: Option<PathBuf>,

    /// Additional arguments to pass to "cargo build" on the guest
    pub args: Vec<String>,
}

static ZIP_CONTENTS: &[u8] = include_bytes!(concat!(env!("OUT_DIR"), "/cargo-risczero.zip"));

fn get_zip_file(dir: &TempDir, filename: &str) -> PathBuf {
    let mut zip = zip::ZipArchive::new(io::Cursor::new(ZIP_CONTENTS)).unwrap();
    let mut file = zip.by_name(filename).unwrap();
    let dest_path = dir.path().join(filename);
    let mut dest_file = fs::File::create(&dest_path).unwrap();
    io::copy(&mut file, &mut dest_file).unwrap();
    dest_path
}

impl BuildCommand {
    /// Execute this command
    pub fn run(&self, subcommand: &str) {
        let manifest_dir = match fs::canonicalize(&self.manifest_dir) {
            Ok(path) => path,
            Err(ref err) => panic!(
                "failed to resolve manifest directory `{}`: {}",
                &self.manifest_dir.display(),
                err
            ),
        };

        let tmpdir = tempdir().unwrap();

        let rust_runtime = get_zip_file(&tmpdir, "rust-runtime.a");
        eprintln!("Runtime: {rust_runtime:?}");

        let target_dir = &self
            .target_dir
            .clone()
            .unwrap_or_else(|| risc0_build::get_target_dir(&manifest_dir));

        println!("target_dir: {}", target_dir.display());
        fs::create_dir_all(&target_dir).expect("failed to ensure target directory exists");

        let guest_build_env = risc0_build::setup_guest_build_env(&target_dir);
        println!("guest_build_env: {guest_build_env:?}");

        let mut cmd = guest_build_env.cargo_command(
            subcommand,
            true,
            &[
                "-C",
                &format!("link_arg={}", rust_runtime.to_str().unwrap()),
            ],
        );
        cmd.arg("--message-format=json");

        // Strip out --no-run if specified, since we always pass --no-run.
        let mut no_run_flag = false;
        if subcommand == "test" {
            for arg in &self.args {
                if arg == "--no-run" {
                    no_run_flag = true;
                } else {
                    cmd.arg(&arg);
                }
            }
            cmd.arg("--no-run");
        } else {
            cmd.args(&self.args);
        }

        println!("running {cmd:?}");
        let mut child = cmd.stdout(Stdio::piped()).spawn().unwrap();
        let reader = std::io::BufReader::new(child.stdout.take().unwrap());
        let mut tests: Vec<String> = Vec::new();
        for message in Message::parse_stream(reader) {
            match message.unwrap() {
                Message::CompilerArtifact(Artifact {
                    executable: Some(exec_path),
                    profile: ArtifactProfile { test: true, .. },
                    ..
                }) => {
                    tests.push(exec_path.to_string());
                }
                Message::CompilerMessage(msg) => {
                    write!(io::stderr(), "{}", msg).unwrap();
                }
                _ => (),
            }
        }

        let output = child.wait().expect("Couldn't get cargo's exit status");
        if !output.success() {
            panic!("Unable to build static library")
        }

        if subcommand == "test" && !no_run_flag {
            eprintln!("Tests: {tests:?}");

            for t in &tests {
                eprintln!("Running test {t}");
                let mut env_builder = ExecutorEnv::builder();

                env_builder
                    .session_limit(usize::MAX)
                    .env_var("RUST_TEST_NOCAPTURE", "1")
                    .env_var("ARGC", &(self.args.len() + 1).to_string())
                    .env_var("ARGV_0", &t);

                for (i, arg) in self.args.iter().enumerate() {
                    env_builder.env_var(&format!("ARGV_{}", i + 1), &arg);
                }

                let env = env_builder.build();
                let mut exec = Executor::from_elf(env, &fs::read(t).unwrap()).unwrap();
                exec.run().unwrap();
            }
        }
    }
}
