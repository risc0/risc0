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

use std::{io::Cursor, path::Path};

use anyhow::{Context as _, Result, anyhow};
use risc0_groth16_sys::{ProverParams, SetupParams, WitnessParams};
use rzup::{Component, Rzup, Version};
use tempfile::tempdir;

use crate::{ProofJson, Seal};

use super::seal_to_json::to_json;

pub(crate) fn shrink_wrap(seal_bytes: &[u8]) -> Result<Seal> {
    tracing::info!("shrink_wrap: {} seal bytes", seal_bytes.len());

    let root_dir = Rzup::new()
        .context("failed to initialize rzup")?
        .get_version_dir(&Component::Risc0Groth16, &Version::new(0, 1, 0))
        .context(
            "Missing required `risc0-groth16` rzup component. \
            To install it, ensure that your `rzup` version is >= 0.5.0, \
            and then run `rzup install risc0-groth16`.",
        )?;
    let tmp_dir = tempdir().context("failed to create temporary directory")?;
    let work_dir = std::env::var("RISC0_WORK_DIR");
    let work_dir = work_dir.as_ref().map(Path::new).unwrap_or(tmp_dir.path());
    let setup_params =
        SetupParams::new(&root_dir).context("failed to create groth16 work directories")?;

    let inputs = to_json(seal_bytes)?;

    let witness_params = WitnessParams::new(&root_dir);
    let witness = calc_witness(&witness_params.graph_path, &inputs)
        .context("failed to calculate groth16 witness")?;

    {
        let _lock = risc0_zkp::hal::cuda::singleton().lock();

        let prover_params = ProverParams::new(work_dir, witness.as_ptr())
            .context("failed to create groth16 prover parameters")?;
        risc0_groth16_sys::prove(&prover_params, &setup_params)
            .context("failed to run groth16 prove operation")?;

        let contents = std::fs::read_to_string(prover_params.proof_path.as_path())
            .context("failed to read groth16 prove output file")?;
        let proof_json: ProofJson = serde_json::from_str(&contents)
            .context("failed to decode groth16 prove output file JSON")?;
        proof_json.try_into()
    }
}

struct CalcWitness {
    witness: Vec<wtns_file::FieldElement<32>>,
}

impl CalcWitness {
    fn as_ptr(&self) -> *const u8 {
        self.witness.as_ptr() as *const u8
    }
}

fn calc_witness(graph_path: &Path, inputs: &str) -> Result<CalcWitness> {
    let graph = std::fs::read(graph_path)?;
    let witness_encoded = circom_witnesscalc::calc_witness(inputs, &graph)
        .map_err(|err| anyhow!("witness failure: {err}"))?;
    let wtns_f = wtns_file::WtnsFile::read(Cursor::new(witness_encoded))?;
    Ok(CalcWitness {
        witness: wtns_f.witness.0,
    })
}
