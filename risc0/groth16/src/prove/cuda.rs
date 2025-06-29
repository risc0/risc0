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

use std::{
    convert::TryFrom,
    ffi::{CString, NulError},
    path::{Path, PathBuf},
};

use anyhow::Result;
use risc0_groth16_sys::{ffi_wrap, risc0_groth16_cuda_prove, RawProverParams};
use rzup::{Component, Rzup, Version};
use tempfile::tempdir;

use crate::{ProofJson, Seal};

use super::seal_to_json::to_json;

pub(crate) fn shrink_wrap(seal_bytes: &[u8]) -> Result<Seal> {
    tracing::debug!("shrink_wrap: {} seal bytes", seal_bytes.len());

    let root_dir =
        Rzup::new()?.get_version_dir(&Component::Risc0Groth16, &Version::new(0, 1, 0))?;

    let graph_path: RawPath = root_dir.join("parallel-graph").try_into()?;
    let pcoeffs_path: RawPath = root_dir.join("preprocessed_coeffs.bin").try_into()?;
    let fres_path: RawPath = root_dir.join("fuzzed_msm_results.bin").try_into()?;
    let srs_path: RawPath = root_dir.join("stark_verify_final.zkey").try_into()?;

    let tmp_dir = tempdir()?;
    let work_dir = std::env::var("RISC0_WORK_DIR");
    let work_dir = work_dir.as_ref().map(Path::new).unwrap_or(tmp_dir.path());
    let proof_path = work_dir.join("proof.json");
    let seal_path = work_dir.join("input.json");
    let public_path: RawPath = work_dir.join("public.json").try_into()?;

    let mut seal_json = Vec::new();
    to_json(seal_bytes, &mut seal_json)?;
    std::fs::write(&seal_path, seal_json)?;

    let inputs_path: RawPath = seal_path.try_into()?;
    let raw_proof_path: RawPath = proof_path.as_path().try_into()?;

    let params = RawProverParams {
        graph_path: graph_path.c_str.as_ptr(),
        pcoeffs_path: pcoeffs_path.c_str.as_ptr(),
        fres_path: fres_path.c_str.as_ptr(),
        srs_path: srs_path.c_str.as_ptr(),
        inputs_path: inputs_path.c_str.as_ptr(),
        public_path: public_path.c_str.as_ptr(),
        proof_path: raw_proof_path.c_str.as_ptr(),
    };

    ffi_wrap(|| unsafe { risc0_groth16_cuda_prove(&params) })?;

    let contents = std::fs::read_to_string(proof_path)?;
    let proof_json: ProofJson = serde_json::from_str(&contents)?;
    proof_json.try_into()
}

struct RawPath {
    c_str: CString,
}

impl TryFrom<&Path> for RawPath {
    type Error = NulError;

    fn try_from(value: &Path) -> Result<Self, Self::Error> {
        Ok(RawPath {
            c_str: CString::new(value.as_os_str().as_encoded_bytes())?,
        })
    }
}

impl TryFrom<PathBuf> for RawPath {
    type Error = NulError;

    fn try_from(value: PathBuf) -> Result<Self, Self::Error> {
        RawPath::try_from(value.as_path())
    }
}
