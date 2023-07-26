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

use anyhow::{bail, Context, Result};
use ethers_solc::{Project, ProjectPathsConfig};

fn main() -> Result<()> {
    if cfg!(feature = "solidity_compile") {
        // configure the project with all its paths, solc, cache etc.
        let project = Project::builder()
            .paths(
                ProjectPathsConfig::hardhat(env!("CARGO_MANIFEST_DIR"))
                    .context("failed to create hardhat config")?,
            )
            .build()
            .context("failed to build project")?;
        let output = project.compile().context("failed to compile project")?;

        if output.has_compiler_errors() {
            bail!("{}", format!("{:?}", output.output().errors));
        }

        // Tell Cargo that if a source file changes, to rerun this build script.
        project.rerun_if_sources_changed();
    }
    Ok(())
}
