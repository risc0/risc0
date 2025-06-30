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

use std::path::Path;

use anyhow::Result;
use risc0_groth16_sys::{ProverParams, SetupParams};
use rzup::{Component, Rzup, Version};
use tempfile::tempdir;

use crate::{ProofJson, Seal};

use super::seal_to_json::to_json;

pub(crate) fn shrink_wrap(seal_bytes: &[u8]) -> Result<Seal> {
    tracing::debug!("shrink_wrap: {} seal bytes", seal_bytes.len());

    let root_dir =
        Rzup::new()?.get_version_dir(&Component::Risc0Groth16, &Version::new(0, 1, 0))?;
    let tmp_dir = tempdir()?;
    let work_dir = std::env::var("RISC0_WORK_DIR");
    let work_dir = work_dir.as_ref().map(Path::new).unwrap_or(tmp_dir.path());

    let setup_params = SetupParams::new(&root_dir)?;
    let prover_params = ProverParams::new(work_dir)?;

    let mut seal_json = Vec::new();
    to_json(seal_bytes, &mut seal_json)?;
    std::fs::write(prover_params.inputs_path.as_path(), seal_json)?;

    risc0_groth16_sys::prove(&prover_params, &setup_params)?;

    let contents = std::fs::read_to_string(prover_params.proof_path.as_path())?;
    let proof_json: ProofJson = serde_json::from_str(&contents)?;
    proof_json.try_into()
}
