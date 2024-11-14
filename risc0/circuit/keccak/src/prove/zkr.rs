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

use crate::{control_id::KECCAK_CONTROL_IDS, KECCAK_PO2_RANGE, RECURSION_PO2};
use anyhow::{ensure, Result};
use risc0_circuit_recursion::prove::Program;
use risc0_core::field::baby_bear::BabyBearElem;

// TODO: publish this value from recursion crate or find some other way not to have this constant here.
const RECURSION_CODE_SIZE: usize = 23;

static REGISTER_ZKRS: std::sync::Once = std::sync::Once::new();

pub fn get_zkr(name: &str, po2: usize) -> Result<Program> {
    let code_size = RECURSION_CODE_SIZE;
    let u32s = crate::zkr::get_zkr_u32s(name)?;
    ensure!(u32s.len() % code_size == 0);
    ensure!(u32s.len() / code_size < (1 << po2));
    let rows = u32s.len() / code_size;
    let steps = 1 << po2;
    let pct = (rows as f64 * 100.) / ((1 << po2) as f64);

    tracing::debug!("Got {rows}/{steps} ({pct:.2}%) rows of program for {name} with po2={po2}");

    Ok(Program {
        code: u32s.iter().cloned().map(BabyBearElem::from).collect(),
        code_size,
        po2,
    })
}

pub fn register_zkrs() {
    REGISTER_ZKRS.call_once(|| {
        for (po2, control_id) in KECCAK_PO2_RANGE.zip(KECCAK_CONTROL_IDS) {
            let name = format!("keccak_lift_{}.zkr", po2);
            risc0_zkvm::register_zkr(&control_id, move || get_zkr(&name, RECURSION_PO2));
        }
    });
}

#[cfg(test)]
mod tests {
    use super::get_zkr;
    use crate::{get_control_id, get_control_root, KECCAK_PO2_RANGE, RECURSION_PO2};
    use anyhow::{ensure, Context, Result};
    use risc0_zkp::core::digest::Digest;
    use risc0_zkp::core::hash::poseidon2::Poseidon2HashSuite;
    use risc0_zkvm::recursion::MerkleGroup;

    fn compute_control_id(po2: usize) -> Result<Digest> {
        let program = get_zkr(&format!("keccak_lift_{}.zkr", po2), RECURSION_PO2)?;
        let hash_suite = Poseidon2HashSuite::new_suite();
        Ok(program.compute_control_id(hash_suite))
    }

    fn compute_control_root(po2: usize) -> Result<Digest> {
        let control_id = compute_control_id(po2)?;
        let hash_suite = Poseidon2HashSuite::new_suite();
        let hashfn = hash_suite.hashfn.as_ref();
        let group = MerkleGroup::new(vec![control_id])?;
        Ok(group.calc_root(hashfn))
    }

    fn verify_control_id(po2: usize) -> Result<()> {
        ensure!(
            *get_control_id(po2) == compute_control_id(po2)?,
            "Control id mismatch on po2={}",
            po2
        );
        Ok(())
    }

    fn verify_control_root(po2: usize) -> Result<()> {
        ensure!(
            *get_control_root(po2) == compute_control_root(po2)?,
            "Control root mismatch on po2={}",
            po2
        );
        Ok(())
    }

    // Makes sure our included control IDs are what we expect
    #[test]
    fn control_ids() -> Result<()> {
        for po2 in KECCAK_PO2_RANGE {
            verify_control_id(po2).context(format!("po2={po2}"))?;
        }
        Ok(())
    }

    #[test]
    fn control_roots() -> Result<()> {
        for po2 in KECCAK_PO2_RANGE {
            verify_control_root(po2).context(format!("po2={po2}"))?;
        }

        Ok(())
    }
}
