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

//! Build Solidity contracts with Foundry when `cargo build` is invoked.

#![feature(is_terminal)]

use clap::Parser;
use file_lock::{FileLock, FileOptions};
use foundry_cli::cmd::{forge, Cmd};

/// .forge.lock in the repo root. CWD in a build script is the crate dir.
const FILE_LOCK_PATH: &'static str = "../../.forge.lock";

fn main() -> anyhow::Result<()> {
    // It is globally unsafe to run two forge processes at the same time -_-
    // This is because the two (or more) forge instances may try to install solc to
    // a glabally shared directory, and if they race, one of the them may panic.
    let options = FileOptions::new().write(true).create(true);
    let _ = match FileLock::lock(FILE_LOCK_PATH, true, options) {
        Ok(lock) => lock,
        Err(err) => panic!("Error getting write lock: {}", err),
    };

    let cmd = forge::build::BuildArgs::try_parse_from(["--"].into_iter())?;
    let _ = cmd
        .run()
        .map_err(|e| anyhow::anyhow!("{}", e.to_string()))?;
    Ok(())
}
