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

extern crate core;

use std::fs;
use std::io::Write;

use ethers_solc::{Project, ProjectPathsConfig};

fn main() {
    // Configure the project with all its paths, solc, cache etc.
    let project = Project::builder()
        .paths(ProjectPathsConfig::hardhat(env!("CARGO_MANIFEST_DIR")).unwrap())
        .build()
        .unwrap();
    let output = project.compile().unwrap();

    if output.has_compiler_errors() || output.has_compiler_warnings() {
        // HACK: Bypass the parent cargo output capture and send directly to the tty, if available.
        // This allows solc to forward errors and warnings to the user.
        let mut tty = fs::OpenOptions::new().write(true).open("/dev/tty").ok();

        if let Some(tty) = &mut tty {
            for error in output.clone().output().errors.iter() {
                write!(tty, "{}", error).unwrap();
            }
            if output.has_compiler_errors() {
                panic!("Failed to build Solidity contracts");
            }
        } else {
            panic!("{:?}", output.output().errors);
        }
    }

    // Tell Cargo that if a source file changes, to rerun this build script.
    project.rerun_if_sources_changed();
}
