// Copyright 2024 RISC Zero, Inc.
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

use crate::{
    extension::install::InstallExtension,
    toolchain::install::InstallToolchain,
    utils::{get_updatable_items, RepoType},
};

pub fn handle_update() {
    let updatable_items = get_updatable_items().expect("Error getting updates");

    for item in updatable_items {
        match item.repo {
            RepoType::Toolchain(repo) => {
                let installer = InstallToolchain {
                    toolchain: Some(item.latest_version.clone()),
                    repo,
                };
                installer.run().expect("Error during toolchain update")
            }
            RepoType::Extension(repo) => {
                let installer = InstallExtension {
                    repo,
                    version: Some(format!("v{}", item.latest_version.clone())),
                };
                installer.run().expect("Error during extension update")
            }
        }
    }
}
