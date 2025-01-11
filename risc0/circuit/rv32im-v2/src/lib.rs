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

#[cfg(feature = "execute")]
pub mod execute;
#[cfg(feature = "prove")]
pub mod prove;
mod zirgen;

use anyhow::Result;
use derive_more::Debug;
use risc0_zkp::{
    adapter::CircuitInfo as _,
    core::{digest::Digest, hash::poseidon2::Poseidon2HashSuite},
    layout::Tree,
    verify::VerificationError,
};

use self::zirgen::circuit::{Val, LAYOUT_GLOBAL};

pub use self::zirgen::CircuitImpl;

pub fn verify(seal: &[u32]) -> Result<(), VerificationError> {
    let hash_suite = Poseidon2HashSuite::new_suite();

    // We don't have a `code' buffer to verify.
    let check_code_fn = |_: u32, _: &Digest| Ok(());

    risc0_zkp::verify::verify(&CircuitImpl, &hash_suite, seal, check_code_fn)
}

#[derive(Debug)]
pub struct Claim {
    pub pre_state: Digest,
    pub post_state: Digest,
    pub input: Digest,
    pub output: Digest,
    pub is_terminate: bool,
    #[debug("{term_a0:#010x}")]
    pub term_a0: u32,
    #[debug("{term_a1:#010x}")]
    pub term_a1: u32,
}

impl Claim {
    pub fn decode(seal: &[u32]) -> Result<Claim> {
        let io: &[Val] = bytemuck::checked::cast_slice(&seal[..CircuitImpl::OUTPUT_SIZE]);
        let global = Tree::new(io, LAYOUT_GLOBAL);

        let pre_state = global.map(|c| c.state_in).get_digest_from_shorts()?;
        let post_state = global.map(|c| c.state_out).get_digest_from_shorts()?;
        let input = global.map(|c| c.input).get_digest_from_shorts()?;
        let output = global.map(|c| c.output).get_digest_from_shorts()?;
        let is_terminate = global.map(|c| c.is_terminate).get_u32_from_elem()?;
        let term_a0_high = global.map(|c| c.term_a0high).get_u32_from_elem()?;
        let term_a0_low = global.map(|c| c.term_a0low).get_u32_from_elem()?;
        let term_a0 = term_a0_high << 16 | term_a0_low;
        let term_a1_high = global.map(|c| c.term_a1high).get_u32_from_elem()?;
        let term_a1_low = global.map(|c| c.term_a1low).get_u32_from_elem()?;
        let term_a1 = term_a1_high << 16 | term_a1_low;

        Ok(Claim {
            pre_state,
            post_state,
            input,
            output,
            is_terminate: is_terminate != 0,
            term_a0,
            term_a1,
        })
    }
}
