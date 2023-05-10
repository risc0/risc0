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

use std::{fs, path::PathBuf};

use clap::Parser;

#[derive(Parser)]
/// `cargo risczero build`
pub struct BuildCommand {
    // TODO(victor): Determine most or all of these automatically.
    /// Manifest directory path
    #[clap(long, default_value = ".")]
    pub manifest_dir: PathBuf,

    /// Output directory for build artifacts.
    #[clap(long)]
    pub target_dir: Option<PathBuf>,
}

impl BuildCommand {
    /// Execute this command
    pub fn run(&self) {
        let manifest_dir = match fs::canonicalize(&self.manifest_dir) {
            Ok(path) => path,
            Err(ref err) => panic!(
                "failed to resolve manifest directory `{}`: {}",
                &self.manifest_dir.display(),
                err
            ),
        };

        let target_dir = &self
            .target_dir
            .clone()
            .unwrap_or_else(|| risc0_build::get_target_dir(&manifest_dir));

        println!("target_dir: {}", target_dir.display());
        fs::create_dir_all(&target_dir).expect("failed to ensure target directory exists");

        let pkg = risc0_build::get_package(&manifest_dir);
        let guest_build_env = risc0_build::setup_guest_build_env(&target_dir);

        println!("pkg.name: {}", &pkg.name);
        println!("guest_build_env: {guest_build_env:?}");
        println!("running build_guest_package");

        risc0_build::build_guest_package(&pkg, &target_dir, &guest_build_env, vec![], true);
    }
}
