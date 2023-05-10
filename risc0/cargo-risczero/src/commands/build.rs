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
    pub target_dir: PathBuf,
}

impl BuildCommand {
    /// Execute this command
    pub fn run(&self) {
        // TODO(victor): Call build_guest_package from here!
        // You don't actually have enough ars parsed yet to actually call it.
        let pkg = risc0_build::get_package(&self.manifest_dir);
        let guest_build_env = risc0_build::setup_guest_build_env(&self.target_dir);

        println!("pkg.name: {}", &pkg.name);
        println!("guest_build_env: {guest_build_env:?}");
        println!("running build_guest_package");

        risc0_build::build_guest_package(&pkg, &self.target_dir, &guest_build_env, vec![], true);
    }
}
