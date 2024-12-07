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
#[cfg(test)]
mod tests;
#[cfg(feature = "prove")]
pub(crate) mod zirgen;

#[cfg(feature = "prove")]
use anyhow::Result;
#[cfg(feature = "prove")]
use risc0_zkp::core::{digest::Digest, hash::poseidon2::Poseidon2HashSuite};

#[cfg(feature = "prove")]
use self::zirgen::CircuitImpl;

pub const KECCAK_PO2: usize = 16;

pub const RECURSION_PO2: usize = 18;

pub use self::control_id::{KECCAK_CONTROL_ID, KECCAK_CONTROL_ROOT};

pub type Seal = Vec<u32>;

#[cfg(feature = "prove")]
pub fn verify(seal: &Seal) -> Result<()> {
    let hash_suite = Poseidon2HashSuite::new_suite();

    // We don't have a `code' buffer to verify.
    let check_code_fn = |_: u32, _: &Digest| Ok(());

    Ok(risc0_zkp::verify::verify(
        &CircuitImpl,
        &hash_suite,
        seal,
        check_code_fn,
    )?)
}
