// Copyright 2025 RISC Zero, Inc.
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

//! This module contains functions for running a Groth16 prover without Docker.
//!
//! [gnark]: https://github.com/Consensys/gnark

use std::{
    path::Path,
    process::{Command, Stdio},
};

use anyhow::{bail, Result};
use tempfile::tempdir;

use crate::{to_json, ProofJson, Seal, stark_verify};

/// Groth16 a given seal of an `identity_p254` receipt into a Groth16 `Seal`.
pub fn stark_to_snark(identity_p254_seal_bytes: &[u8]) -> Result<Seal> {
    let tmp_dir = tempdir()?;
    let work_dir = std::env::var("RISC0_WORK_DIR");
    let work_dir = work_dir.as_ref().map(Path::new).unwrap_or(tmp_dir.path());

    // Write the seal out in json format as input for the witness generator.
    tracing::debug!("seal-to-json");
    std::fs::write(work_dir.join("seal.r0"), identity_p254_seal_bytes)?;
    let seal_path = work_dir.join("input.json");
    let mut seal_json = Vec::new();
    to_json(identity_p254_seal_bytes, &mut seal_json)?;
    std::fs::write(&seal_path, seal_json)?;

    // Run the witness generator and read in the witness data.
    let wtns_path = work_dir.join("output.wtns");
    let ret = stark_verify::calc_witness(&seal_path, &wtns_path);
    assert!(0 == ret);

    let proof_path = work_dir.join("proof.json");
    let output = Command::new("prover")
        .arg("stark_verify.cs")
        .arg("stark_verify_final.pk.dmp")
        .arg(wtns_path)
        .arg(&proof_path)
        .stdout(Stdio::piped())
        .stderr(Stdio::piped())
        .output()?;
    if !output.status.success() {
        bail!(
            "prover returned failure exit code: {:?}",
            output.status.code()
        );
    }

    tracing::debug!("Parsing proof");
    let contents = std::fs::read_to_string(proof_path)?;
    let proof_json: ProofJson = serde_json::from_str(&contents)?;
    proof_json.try_into()
}
