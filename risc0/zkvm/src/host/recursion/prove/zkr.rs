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

use anyhow::{anyhow, bail, Result};
use risc0_circuit_recursion::control_id::{
    BN254_IDENTITY_CONTROL_ID, POSEIDON2_CONTROL_IDS, SHA256_CONTROL_IDS,
};
use risc0_circuit_recursion::prove::Program;
use risc0_zkp::{core::digest::Digest, MAX_CYCLES_PO2, MIN_CYCLES_PO2};

fn get_zkr(name: impl AsRef<str>, hashfn: &str, program_po2: usize) -> Result<(Program, Digest)> {
    let control_ids: &[(&str, Digest)] = match hashfn {
        "poseidon2" => &POSEIDON2_CONTROL_IDS,
        "sha-256" => &SHA256_CONTROL_IDS,
        "poseidon_254" => &[("identity.zkr", BN254_IDENTITY_CONTROL_ID)],
        _ => bail!("no control id found for {} with {hashfn}", name.as_ref()),
    };

    Ok((
        risc0_circuit_recursion::prove::zkr::get_zkr(name.as_ref(), program_po2)?,
        control_ids
            .iter()
            .copied()
            .find_map(|(n, id)| (n == name.as_ref()).then_some(id))
            .ok_or(anyhow!(
                "failed to find {} in the list of control IDs",
                name.as_ref()
            ))?,
    ))
}

pub fn test_recursion_circuit(hashfn: &str, program_po2: usize) -> Result<(Program, Digest)> {
    get_zkr("test_recursion_circuit.zkr", hashfn, program_po2)
}

// DO NOT MERGE: Consider this breaking change.
pub fn lift(rv32im_po2: usize, hashfn: &str, program_po2: usize) -> Result<(Program, Digest)> {
    if (MIN_CYCLES_PO2..MAX_CYCLES_PO2).contains(&rv32im_po2) {
        get_zkr(format!("lift_{rv32im_po2}.zkr"), hashfn, program_po2)
    } else {
        bail!("No rv32im verifier available for po2={rv32im_po2}")
    }
}

pub fn join(hashfn: &str, program_po2: usize) -> Result<(Program, Digest)> {
    // Assume join width of 2 and verify po2 equal to the program po2.
    get_zkr(format!("join2_{program_po2}.zkr"), hashfn, program_po2)
}

pub fn join_n(hashfn: &str, program_po2: usize, width: usize) -> Result<(Program, Digest)> {
    // Assume verify po2 equal to the program po2.
    get_zkr(
        format!("join{width}_{program_po2}.zkr"),
        hashfn,
        program_po2,
    )
}

pub fn lift_join_n(
    rv32im_po2: usize,
    hashfn: &str,
    program_po2: usize,
    width: usize,
) -> Result<(Program, Digest)> {
    get_zkr(
        format!("lift_join{width}_{rv32im_po2}.zkr"),
        hashfn,
        program_po2,
    )
}

pub fn resolve(hashfn: &str, program_po2: usize) -> Result<(Program, Digest)> {
    // Assume verify po2 equal to the program po2.
    get_zkr(format!("resolve_{program_po2}.zkr"), hashfn, program_po2)
}

pub fn identity(hashfn: &str, program_po2: usize) -> Result<(Program, Digest)> {
    // Assume verify po2 equal to the program po2.
    get_zkr(format!("identity_{program_po2}.zkr"), hashfn, program_po2)
}
