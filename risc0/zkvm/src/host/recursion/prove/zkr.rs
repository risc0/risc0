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

use anyhow::{bail, Result};
use risc0_circuit_recursion::REGISTER_GROUP_CODE;
use risc0_zkp::{
    adapter::TapsProvider, core::digest::Digest, field::baby_bear::BabyBearElem, MAX_CYCLES_PO2,
    MIN_CYCLES_PO2,
};

use super::{Program, CIRCUIT, RECURSION_CODE_SIZE};

fn get_zkr(name: &str) -> Result<(Program, Digest)> {
    let u32s = risc0_circuit_recursion::zkr::get_zkr(name)?;
    let code_size = CIRCUIT.get_taps().group_size(REGISTER_GROUP_CODE);
    assert_eq!(code_size, RECURSION_CODE_SIZE);

    Ok((
        Program {
            code: u32s.iter().cloned().map(BabyBearElem::from).collect(),
            code_size,
        },
        risc0_circuit_recursion::zkr::get_control_id(name)?,
    ))
}

pub fn test_recursion_circuit() -> Result<(Program, Digest)> {
    get_zkr("test_recursion_circuit.zkr")
}

pub fn lift(po2: usize) -> Result<(Program, Digest)> {
    if po2 >= MIN_CYCLES_PO2 && po2 < MAX_CYCLES_PO2 {
        get_zkr(&format!("lift_{po2}.zkr"))
    } else {
        bail!("No rv32im verifier available for po2={po2}")
    }
}

pub fn join() -> Result<(Program, Digest)> {
    get_zkr("join.zkr")
}

pub fn identity() -> Result<(Program, Digest)> {
    get_zkr("identity.zkr")
}
