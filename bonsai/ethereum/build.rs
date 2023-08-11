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

use clap::Parser;
use foundry_cli::cmd::{forge, Cmd};

fn main() -> anyhow::Result<()> {
    let cmd = forge::build::BuildArgs::try_parse_from(["--"].into_iter())?;
    let _ = cmd
        .run()
        .map_err(|e| anyhow::anyhow!("{}", e.to_string()))?;
    Ok(())
}
