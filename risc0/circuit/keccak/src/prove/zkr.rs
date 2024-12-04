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

use std::io::{Cursor, Read as _};

use anyhow::{Context as _, Result};
use risc0_circuit_recursion::prove::Program;
use zip::ZipArchive;

use crate::{KECCAK_PO2, RECURSION_PO2};

const ZKR_ZIP: &[u8] = include_bytes!("keccak_zkr.zip");

pub fn get_zkr_u32s(name: &str) -> Result<Vec<u32>> {
    let mut zip = ZipArchive::new(Cursor::new(ZKR_ZIP))?;
    let mut entry = zip
        .by_name(name)
        .with_context(|| format!("Failed to read {name}"))?;

    let mut bytes = Vec::new();
    entry.read_to_end(&mut bytes)?;

    Ok(Vec::from(bytemuck::cast_slice(bytes.as_slice())))
}

pub fn get_zkr() -> Result<Program> {
    let name = format!("keccak_lift_{KECCAK_PO2}.zkr");
    let u32s = get_zkr_u32s(&name)?;
    Ok(Program::from_encoded(&u32s, RECURSION_PO2))
}

#[cfg(test)]
mod tests {
    use anyhow::Result;
    use risc0_zkp::core::{digest::Digest, hash::poseidon2::Poseidon2HashSuite};
    use risc0_zkvm::recursion::MerkleGroup;

    use crate::control_id::{KECCAK_CONTROL_ID, KECCAK_CONTROL_ROOT};

    use super::get_zkr;

    fn compute_control_id() -> Result<Digest> {
        let program = get_zkr()?;
        let hash_suite = Poseidon2HashSuite::new_suite();
        Ok(program.compute_control_id(hash_suite))
    }

    fn compute_control_root() -> Result<Digest> {
        let control_id = compute_control_id()?;
        let hash_suite = Poseidon2HashSuite::new_suite();
        let hashfn = hash_suite.hashfn.as_ref();
        let group = MerkleGroup::new(vec![control_id])?;
        Ok(group.calc_root(hashfn))
    }

    // Makes sure our included control IDs are what we expect
    #[test]
    fn control_ids() {
        assert_eq!(KECCAK_CONTROL_ID, compute_control_id().unwrap());
    }

    #[test]
    fn control_roots() {
        assert_eq!(KECCAK_CONTROL_ROOT, compute_control_root().unwrap());
    }
}
