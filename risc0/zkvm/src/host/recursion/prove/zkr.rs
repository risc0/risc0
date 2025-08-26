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

use anyhow::{Result, anyhow, bail};
use risc0_circuit_recursion::{
    control_id::{BN254_IDENTITY_CONTROL_ID, POSEIDON2_CONTROL_IDS, SHA256_CONTROL_IDS},
    prove::Program,
};
use risc0_zkp::{MAX_CYCLES_PO2, MIN_CYCLES_PO2, core::digest::Digest};

use crate::RECURSION_PO2;

fn get_zkr(name: &str, hashfn: &str) -> Result<(Program, Digest)> {
    let control_ids: &[(&str, Digest)] = match hashfn {
        "poseidon2" => &POSEIDON2_CONTROL_IDS,
        "sha-256" => &SHA256_CONTROL_IDS,
        "poseidon_254" => &[("identity.zkr", BN254_IDENTITY_CONTROL_ID)],
        _ => bail!("no control id found for {name} with {hashfn}"),
    };

    Ok((
        risc0_circuit_recursion::prove::zkr::get_zkr(name, RECURSION_PO2)?,
        control_ids
            .iter()
            .copied()
            .find_map(|(n, id)| (n == name).then_some(id))
            .ok_or_else(|| anyhow!("failed to find {name} in the list of control IDs"))?,
    ))
}

pub fn test_recursion_circuit(hashfn: &str) -> Result<(Program, Digest)> {
    get_zkr("test_recursion_circuit.zkr", hashfn)
}

pub fn lift(po2: usize, hashfn: &str) -> Result<(Program, Digest)> {
    if (MIN_CYCLES_PO2..MAX_CYCLES_PO2).contains(&po2) {
        get_zkr(&format!("lift_rv32im_v2_{po2}.zkr"), hashfn)
    } else {
        bail!("No rv32im verifier available for po2={po2}")
    }
}

pub fn join(hashfn: &str) -> Result<(Program, Digest)> {
    get_zkr("join.zkr", hashfn)
}

pub fn resolve(hashfn: &str) -> Result<(Program, Digest)> {
    get_zkr("resolve.zkr", hashfn)
}

pub fn identity(hashfn: &str) -> Result<(Program, Digest)> {
    get_zkr("identity.zkr", hashfn)
}

pub fn union(hashfn: &str) -> Result<(Program, Digest)> {
    get_zkr("union.zkr", hashfn)
}

pub fn lift_povw(po2: usize, hashfn: &str) -> Result<(Program, Digest)> {
    if (MIN_CYCLES_PO2..MAX_CYCLES_PO2).contains(&po2) {
        get_zkr(&format!("lift_rv32im_v2_povw_{po2}.zkr"), hashfn)
    } else {
        bail!("No rv32im verifier available for po2={po2}")
    }
}

pub fn join_povw(hashfn: &str) -> Result<(Program, Digest)> {
    get_zkr("join_povw.zkr", hashfn)
}

pub fn join_unwrap_povw(hashfn: &str) -> Result<(Program, Digest)> {
    get_zkr("join_unwrap_povw.zkr", hashfn)
}

pub fn resolve_povw(hashfn: &str) -> Result<(Program, Digest)> {
    get_zkr("resolve_povw.zkr", hashfn)
}

pub fn resolve_unwrap_povw(hashfn: &str) -> Result<(Program, Digest)> {
    get_zkr("resolve_unwrap_povw.zkr", hashfn)
}

pub fn unwrap_povw(hashfn: &str) -> Result<(Program, Digest)> {
    get_zkr("unwrap_povw.zkr", hashfn)
}
