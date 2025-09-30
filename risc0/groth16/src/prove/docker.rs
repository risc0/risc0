// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! This module contains functions for running a Groth16 prover using Docker.
//!
//! Docker is used here as a way to provide [gnark] and the required prover key in a single package.
//! Proving with Groth16 is currently only supported using Docker.
//!
//! [gnark]: https://github.com/Consensys/gnark

use std::{
    path::Path,
    process::{Command, Stdio},
};

use anyhow::{Result, bail};
use tempfile::tempdir;

use super::seal_to_json::to_json;
use crate::{ProofJson, Seal};

/// Groth16 a given seal of an `identity_p254` receipt into a Groth16 `Seal`.
/// Requires running Docker on an x86 architecture.
pub(crate) fn shrink_wrap(identity_p254_seal_bytes: &[u8]) -> Result<Seal> {
    if !is_docker_installed() {
        bail!("Please install docker first.")
    }

    let tmp_dir = tempdir()?;
    let work_dir = std::env::var("RISC0_WORK_DIR");
    let work_dir = work_dir.as_ref().map(Path::new).unwrap_or(tmp_dir.path());

    tracing::debug!("seal-to-json");
    std::fs::write(work_dir.join("seal.r0"), identity_p254_seal_bytes)?;
    let seal_path = work_dir.join("input.json");
    let proof_path = work_dir.join("proof.json");
    let seal_json = to_json(identity_p254_seal_bytes)?;
    std::fs::write(seal_path, seal_json)?;

    tracing::debug!("risc0-groth16-prover");
    let output = Command::new("docker")
        .arg("run")
        .arg("--rm")
        .arg("-v")
        .arg(format!("{}:/mnt", work_dir.to_string_lossy()))
        .arg("risczero/risc0-groth16-prover:v2025-04-03.1")
        .stdout(Stdio::piped())
        .stderr(Stdio::piped())
        .output()?;
    if !output.status.success() {
        let hint = match output.status.code() {
            Some(126) => "\nThis process may not have permission to run containers.",
            _ => "",
        };
        bail!(
            "docker returned failure exit code: {:?}{hint}",
            output.status.code()
        );
    }

    tracing::debug!("Parsing proof");
    let contents = std::fs::read_to_string(proof_path)?;
    let proof_json: ProofJson = serde_json::from_str(&contents)?;
    proof_json.try_into()
}

fn is_docker_installed() -> bool {
    Command::new("docker")
        .arg("--version")
        .output()
        .map(|output| output.status.success())
        .unwrap_or(false)
}
