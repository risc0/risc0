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

pub type KeccakState = [u64; 25];

pub fn get_control_id(po2: usize) -> &'static Digest {
    assert!(KECCAK_PO2_RANGE.contains(&po2), "po2 {po2} out of range");
    &KECCAK_CONTROL_IDS[po2 - KECCAK_PO2_RANGE.min().unwrap()]
}
