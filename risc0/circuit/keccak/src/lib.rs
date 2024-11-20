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

#![cfg_attr(not(feature = "std"), no_std)]

use risc0_zkp::core::digest::Digest;

pub struct CircuitImpl;

#[cfg(not(feature = "make_control_ids"))]
pub mod control_id;
//#[cfg(feature = "make_control_ids")]
//pub mod zkr;
#[cfg(feature = "prove")]
mod zkr;

#[cfg(feature = "prove")]
mod info;
mod poly_ext;
#[cfg(feature = "prove")]
pub mod prove;
#[cfg(feature = "prove")]
mod taps;

//#[cfg(target_os = "zkvm")]
//mod guest;
//#[cfg(target_os = "zkvm")]
//pub use guest::*;

//#[cfg(test)]
//mod tests;
// TODO: Can we import this from somewhere other than ZKVM?
pub const RECURSION_PO2: usize = 18;

pub const KECCAK_PO2_RANGE: core::ops::Range<usize> = 14..25;

pub const CIRCUIT: CircuitImpl = CircuitImpl;

#[cfg(not(feature = "make_control_ids"))]
fn lookup_by_po2(po2: usize, arr: &'static [Digest]) -> &'static Digest {
    assert_eq!(arr.len(), KECCAK_PO2_RANGE.len());
    assert!(
        po2 <= KECCAK_PO2_RANGE.max().unwrap(),
        "po2 {po2} out of range"
    );
    &arr[po2 - KECCAK_PO2_RANGE.min().unwrap()]
}

#[cfg(not(feature = "make_control_ids"))]
pub fn get_control_id(po2: usize) -> &'static Digest {
    lookup_by_po2(po2, &control_id::KECCAK_CONTROL_IDS)
}

#[cfg(not(feature = "make_control_ids"))]
pub fn get_control_root(po2: usize) -> &'static Digest {
    lookup_by_po2(po2, &control_id::KECCAK_CONTROL_ROOTS)
}
