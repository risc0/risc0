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

#[cfg(feature = "execute")]
pub mod execute;
#[cfg(feature = "prove")]
pub mod prove;
mod zirgen;

use risc0_zkp::{
    core::{digest::Digest, hash::poseidon2::Poseidon2HashSuite},
    verify::VerificationError,
};

use self::zirgen::CircuitImpl;

pub fn verify(seal: &[u32]) -> Result<(), VerificationError> {
    let hash_suite = Poseidon2HashSuite::new_suite();

    // We don't have a `code' buffer to verify.
    let check_code_fn = |_: u32, _: &Digest| Ok(());

    risc0_zkp::verify::verify(&CircuitImpl, &hash_suite, seal, check_code_fn)
}
