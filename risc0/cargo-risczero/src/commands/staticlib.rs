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
    io::{stderr, Write},
    process::Stdio,
};

use cargo_metadata::{Message, MetadataCommand};
use clap::Parser;
use risc0_build::setup_guest_build_env;

#[derive(Parser)]
/// `cargo risczero staticlib' creates a static library using C calling
/// conventions for zkvm guest support.  It outputs the filename of the
/// built library file to standard output so it's easy to include
/// in scripts.
pub struct StaticlibCommand {}

impl StaticlibCommand {
    /// Execute this command
    pub fn run(&self) {
        let manifest_meta = MetadataCommand::new().exec().unwrap();
        let out_dir = manifest_meta.target_directory;

        let target_dir = out_dir.join("riscv-guest").into_string();
        let guest_build_env = setup_guest_build_env(out_dir.as_ref());
        let mut cmd = guest_build_env.cargo_command("rustc", /* std= */ false);
        eprintln!("Building for guest: {:?}", cmd);
        cmd.args(&[
            "--release",
            "--package",
            "risc0-zkvm-platform",
            "--target-dir",
            &target_dir,
            "--lib",
            "--message-format=json",
            "--crate-type=staticlib",
        ]);

        let mut child = cmd.stdout(Stdio::piped()).spawn().unwrap();
        let reader = std::io::BufReader::new(child.stdout.take().unwrap());
        let mut libs = Vec::new();
        for message in cargo_metadata::Message::parse_stream(reader) {
            match message.unwrap() {
                Message::CompilerArtifact(artifact) => {
                    for filename in artifact.filenames {
                        if let Some("a") = filename.extension() {
                            libs.push(filename.to_string());
                        }
                    }
                }
                Message::CompilerMessage(msg) => {
                    write!(stderr(), "{}", msg).unwrap();
                }
                _ => (),
            }
        }

        let output = child.wait().expect("Couldn't get cargo's exit status");
        if !output.success() {
            panic!("Unable to build static library")
        }

        match libs.as_slice() {
            [] => panic!("No static library was built"),
            [lib] => println!("{}", lib),
            _ => panic!("Multiple static libraries found: {:?}", libs.as_slice()),
        }
    }
}
