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

use std::io::{Cursor, Read};

use anyhow::{ensure, Context, Result};
use risc0_circuit_recursion::{prove::Program, CIRCUIT, REGISTER_GROUP_CODE};
use risc0_core::field::baby_bear::BabyBearElem;
use risc0_zkp::adapter::TapsProvider;
use zip::ZipArchive;

use crate::BIGINT_PO2;

pub(crate) const ZKR_ZIP: &[u8] = include_bytes!("bigint_zkr.zip");

fn get_zkr_u32s(name: &str) -> Result<Vec<u32>> {
    let mut zip = ZipArchive::new(Cursor::new(ZKR_ZIP))?;
    let mut entry = zip
        .by_name(name)
        .with_context(|| format!("Failed to read {name}"))?;

    let mut bytes = Vec::new();
    entry.read_to_end(&mut bytes)?;

    Ok(Vec::from(bytemuck::cast_slice(bytes.as_slice())))
}

pub fn get_zkr(name: &str, po2: usize) -> Result<Program> {
    let code_size = CIRCUIT.get_taps().group_size(REGISTER_GROUP_CODE);

    let u32s = get_zkr_u32s(name)?;
    ensure!(u32s.len() % code_size == 0);
    ensure!(u32s.len() / code_size < (1 << po2));
    let rows = u32s.len() / code_size;
    let steps = 1 << po2;
    let pct = (rows as f64 * 100.) / ((1 << po2) as f64);

    tracing::debug!("Got {rows}/{steps} ({pct:.2}%) rows of program for {name} with po2={po2}",);

    Ok(Program {
        code: u32s.iter().cloned().map(BabyBearElem::from).collect(),
        code_size,
        po2,
    })
}

static REGISTER_ZKRS: std::sync::Once = std::sync::Once::new();

pub fn register_zkrs() {
    REGISTER_ZKRS.call_once(|| {
        for prog in crate::generated::PROGRAMS {
            let name = prog.name.to_string();
            risc0_zkvm::register_zkr(&prog.control_id, move || {
                crate::zkr::get_zkr(&format!("{}.zkr", name), BIGINT_PO2)
            });
        }
    });
}

#[cfg(test)]
mod tests {
    use anyhow::{Context, Result};
    use risc0_zkp::core::digest::Digest;
    use risc0_zkp::core::hash::poseidon2::Poseidon2HashSuite;
    use risc0_zkvm::recursion::MerkleGroup;

    use crate::{BigIntProgram, BIGINT_PO2};

    fn compute_control_id(prog: &BigIntProgram) -> Result<Digest> {
        let program = crate::zkr::get_zkr(&format!("{}.zkr", prog.name), BIGINT_PO2)?;
        let hash_suite = Poseidon2HashSuite::new_suite();
        Ok(program.compute_control_id(hash_suite))
    }

    fn compute_control_root(prog: &BigIntProgram) -> Result<Digest> {
        let control_id = compute_control_id(prog)?;
        let hash_suite = Poseidon2HashSuite::new_suite();
        let hashfn = hash_suite.hashfn.as_ref();
        let group = MerkleGroup::new(vec![control_id])?;
        Ok(group.calc_root(hashfn))
    }

    fn verify_control_id(prog: &BigIntProgram) -> Result<()> {
        assert_eq!(
            prog.control_id,
            compute_control_id(prog)?,
            "Control id mismatch on {}",
            prog.name
        );
        Ok(())
    }

    fn verify_control_root(prog: &BigIntProgram) -> Result<()> {
        assert_eq!(
            prog.control_root,
            compute_control_root(prog)?,
            "Control root mismatch on {}",
            prog.name
        );
        Ok(())
    }

    // Makes sure our included control IDs are what we expect
    #[test]
    fn control_ids() -> Result<()> {
        for prog in crate::generated::PROGRAMS {
            verify_control_id(prog).context(prog.name)?;
        }
        Ok(())
    }

    #[test]
    fn control_roots() -> Result<()> {
        for prog in crate::generated::PROGRAMS {
            verify_control_root(prog).context(prog.name)?;
        }
        Ok(())
    }
}
