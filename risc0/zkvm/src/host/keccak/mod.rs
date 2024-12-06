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

use alloc::collections::VecDeque;
use anyhow::Result;
use risc0_binfmt::read_sha_halfs;
use risc0_circuit_keccak::prove::keccak_prover;
use risc0_circuit_keccak::prove::KeccakState;
use risc0_circuit_keccak::{KECCAK_CONTROL_ID, KECCAK_CONTROL_ROOT};
use risc0_core::field::baby_bear::BabyBearElem;
use risc0_zkp::core::digest::{Digest, DIGEST_SHORTS};

use crate::{receipt::SuccinctReceipt, recursion, Unknown};

/// Generate a keccak proof that has been lifted.
pub fn prove_keccak(input: &[u8]) -> Result<SuccinctReceipt<Unknown>> {
    let input: &[KeccakState] = bytemuck::cast_slice(input);
    let prover = keccak_prover().unwrap();
    let seal = prover
        .prove(input, risc0_circuit_keccak::KECCAK_PO2)
        .unwrap();

    let claim_digest: Digest = read_sha_halfs(&mut VecDeque::from_iter(
        bytemuck::checked::cast_slice::<_, BabyBearElem>(&seal[0..DIGEST_SHORTS])
            .iter()
            .copied()
            .map(u32::from),
    ))?;

    // Make sure we have a valid seal so we can fail early if anything went wrong
    prover.verify(&seal).expect("Verification failed");

    let claim_sha_input = claim_digest
        .as_words()
        .iter()
        .copied()
        .flat_map(|x| [x & 0xffff, x >> 16])
        .map(BabyBearElem::new)
        .collect::<Vec<_>>();

    let mut zkr_input: Vec<u32> = Vec::new();
    zkr_input.extend(KECCAK_CONTROL_ROOT.as_words());
    zkr_input.extend(seal);
    zkr_input.extend(bytemuck::cast_slice(claim_sha_input.as_slice()));

    recursion::prove::prove_zkr(
        &KECCAK_CONTROL_ID,
        bytemuck::cast_slice(zkr_input.as_slice()),
    )
}
