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

#![doc = include_str!("../README.md")]
#![cfg_attr(not(feature = "std"), no_std)]

pub mod control_id;
mod info;
pub mod layout;
pub mod poly_ext;
#[cfg(feature = "prove")]
pub mod prove;
mod taps;
pub mod trace;

use risc0_zkp::{
    adapter::{CircuitCoreDef, TapsProvider},
    core::digest::Digest,
    field::baby_bear::BabyBear,
    taps::TapSet,
};

use control_id::{BLAKE2B_CONTROL_IDS, POSEIDON2_CONTROL_IDS, SHA256_CONTROL_IDS};

pub struct CircuitImpl;

pub const REGISTER_GROUP_ACCUM: usize = 0;
pub const REGISTER_GROUP_CODE: usize = 1;
pub const REGISTER_GROUP_CTRL: usize = 1;
pub const REGISTER_GROUP_DATA: usize = 2;

pub const GLOBAL_MIX: usize = 0;
pub const GLOBAL_OUT: usize = 1;
pub const CIRCUIT: CircuitImpl = CircuitImpl::new();

impl CircuitImpl {
    const fn new() -> Self {
        CircuitImpl
    }
}

impl TapsProvider for CircuitImpl {
    fn get_taps(&self) -> &'static TapSet<'static> {
        taps::TAPSET
    }
}

impl CircuitCoreDef<BabyBear> for CircuitImpl {}

/// Fetch a control ID with the given hash, by name, and cycle limit as a power of two (po2) from
/// the precomputed table. If the hash function is not precomputed, or the po2 is out of range,
/// this function will return `None`.
///
/// Supported values for hash_name are "sha-256", "poseidon2", and "blake2b".
#[inline]
pub fn control_id(hash_name: impl AsRef<str>, po2: usize) -> Option<Digest> {
    if !(risc0_zkp::MIN_CYCLES_PO2..=risc0_zkp::MAX_CYCLES_PO2).contains(&po2) {
        return None;
    }
    let idx = po2 - risc0_zkp::MIN_CYCLES_PO2;
    match hash_name.as_ref() {
        "sha-256" => Some(SHA256_CONTROL_IDS[idx]),
        "poseidon2" => Some(POSEIDON2_CONTROL_IDS[idx]),
        "blake2b" => Some(BLAKE2B_CONTROL_IDS[idx]),
        _ => None,
    }
}

/// Fetch all precomputed control IDs using the given hash, by name, and up to the cycle limit as a
/// power of two (po2). If po2 is larger than the max supported, only supported po2s will be
/// returned.
pub fn control_ids(
    hash_name: impl AsRef<str> + 'static,
    po2_max: usize,
) -> impl Iterator<Item = Digest> {
    // Using `take_while` here ensures termination when po2_max is much greater than the highest po2.
    (risc0_zkp::MIN_CYCLES_PO2..=po2_max)
        .map(move |po2| control_id(hash_name.as_ref(), po2))
        .take_while(Option::is_some)
        .map(Option::unwrap)
}
