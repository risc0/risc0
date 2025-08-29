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

#![cfg_attr(not(feature = "std"), no_std)]

mod control_id;
#[cfg(feature = "prove")]
pub mod prove;
#[cfg(feature = "prove")]
pub(crate) mod zirgen;

use risc0_zkp::core::digest::Digest;

pub use self::control_id::{KECCAK_CONTROL_IDS, KECCAK_CONTROL_ROOT};

pub const KECCAK_DEFAULT_PO2: usize = 17;

pub const KECCAK_PO2_RANGE: core::ops::RangeInclusive<usize> = 14..=18;

pub const RECURSION_PO2: usize = 18;

pub const KECCAK_PERMUTE_CYCLES: usize = 200;

pub type KeccakState = [u64; 25];

pub fn get_control_id(po2: usize) -> &'static Digest {
    assert!(KECCAK_PO2_RANGE.contains(&po2), "po2 {po2} out of range");
    &KECCAK_CONTROL_IDS[po2 - KECCAK_PO2_RANGE.min().unwrap()]
}

pub fn max_keccak_inputs(po2: usize) -> usize {
    let max_keccak_cycles: usize = 1 << po2;
    max_keccak_cycles / KECCAK_PERMUTE_CYCLES
}

/// Given a slice of `KeccakState`, encoded as `[u8]`, produce the SHA-256 digest matching what is produced by the keccak circuit.
#[cfg(feature = "prove")]
pub fn compute_keccak_digest(input: &[u8]) -> Digest {
    use risc0_zkp::core::digest::{DIGEST_BYTES, Digest};
    use risc0_zkp::core::hash::{
        sha,
        sha::{SHA256_INIT, Sha256},
    };

    let mut transcript = vec![];

    let mut input: Vec<u8> = input.to_vec();
    let input_states: &mut [KeccakState] = bytemuck::cast_slice_mut(&mut input);
    for input in input_states.iter_mut() {
        let mut data = [0u64; 32];
        data[0..25].clone_from_slice(input);
        transcript.push(data);

        keccak::f1600(input);

        data[0..25].clone_from_slice(input);
        transcript.push(data);
    }

    let mut digest = SHA256_INIT;
    for halfs in bytemuck::cast_slice::<[u64; 32], [u64; 8]>(transcript.as_slice()) {
        let mut first_half = [0u8; DIGEST_BYTES];
        first_half.clone_from_slice(bytemuck::cast_slice(&halfs[0..4]));

        let mut second_half = [0u8; DIGEST_BYTES];
        second_half.clone_from_slice(bytemuck::cast_slice(&halfs[4..8]));

        digest = *sha::Impl::compress(
            &digest,
            &Digest::from_bytes(first_half),
            &Digest::from_bytes(second_half),
        );
    }

    // reorder to match the keccak accelerator
    for word in digest.as_mut_words() {
        *word = word.to_be();
    }
    digest
}
