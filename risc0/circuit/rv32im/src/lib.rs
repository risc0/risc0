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
pub mod trace;
mod zirgen;

use core::num::TryFromIntError;

use anyhow::{anyhow, ensure, Context, Result};
use derive_more::Debug;
use risc0_binfmt::PovwNonce;
use risc0_zkp::{
    adapter::CircuitInfo as _,
    core::{digest::Digest, hash::poseidon2::Poseidon2HashSuite},
    layout::Tree,
    verify::VerificationError,
};
use serde::{Deserialize, Serialize};

use self::zirgen::circuit::{Val, LAYOUT_GLOBAL};

pub use self::zirgen::CircuitImpl;

// NOTE: Seal version two introduced with PoVW, changing the output size from 74 to 90.
pub const RV32IM_SEAL_VERSION: u32 = 2;

/// This number was picked by running `bigint2-analyze` on all the current bigint programs
pub const MAX_INSN_CYCLES: usize = 25_000;

/// This is a smaller number used by lower po2's < 15 which can't fit a large bigint program.
pub const MAX_INSN_CYCLES_LOWER_PO2: usize = 2_000;

pub fn verify(mut seal: &[u32]) -> Result<(), VerificationError> {
    tracing::debug!("verify");

    // We don't have a `code' buffer to verify.
    let check_code_fn = |_: u32, _: &Digest| Ok(());

    let Some([version]) = seal.split_off(..1) else {
        return Err(VerificationError::ReceiptFormatError);
    };
    if *version != RV32IM_SEAL_VERSION {
        return Err(VerificationError::ReceiptFormatError);
    }

    let hash_suite = Poseidon2HashSuite::new_suite();
    risc0_zkp::verify::verify(&CircuitImpl, &hash_suite, seal, check_code_fn)
}

#[derive(Clone, Copy, Debug, Default, Serialize, Deserialize, PartialEq)]
pub struct HighLowU16(pub u16, pub u16);

impl From<HighLowU16> for u32 {
    fn from(x: HighLowU16) -> Self {
        ((x.0 as u32) << 16) | (x.1 as u32)
    }
}

impl From<u32> for HighLowU16 {
    fn from(x: u32) -> Self {
        Self((x >> 16) as u16, (x & 0xffff) as u16)
    }
}

#[derive(Clone, Copy, Debug, Default, Serialize, Deserialize, PartialEq)]
pub struct TerminateState {
    pub a0: HighLowU16,
    pub a1: HighLowU16,
}

#[derive(Clone, Debug, Serialize, Deserialize, PartialEq)]
pub struct Rv32imV2Claim {
    pub pre_state: Digest,
    pub post_state: Digest,
    pub input: Digest,
    pub output: Option<Digest>,
    pub terminate_state: Option<TerminateState>,
    pub shutdown_cycle: Option<u32>,
}

impl Rv32imV2Claim {
    pub fn decode(mut segment_seal: &[u32]) -> Result<Rv32imV2Claim> {
        ensure!(
            segment_seal.split_off(..1) == Some(&[RV32IM_SEAL_VERSION]),
            "seal version mismatch"
        );

        let io: &[Val] = bytemuck::checked::try_cast_slice(
            segment_seal
                .split_off(..CircuitImpl::OUTPUT_SIZE)
                .context("Seal too short; failed to decode output")?,
        )
        .map_err(|_| anyhow!("Invalid values in seal output section"))?;
        let global = Tree::new(io, LAYOUT_GLOBAL);

        // NOTE: rng and povw are not read from the globals here. Neither need to be checked to
        // establish the integrity of the Rv32imV2Claim.
        let pre_state = global.map(|c| c.state_in).get_digest_from_shorts()?;
        let post_state = global.map(|c| c.state_out).get_digest_from_shorts()?;
        let input = global.map(|c| c.input).get_digest_from_shorts()?;
        let output = global.map(|c| c.output).get_digest_from_shorts()?;
        let is_terminate = global.map(|c| c.is_terminate).get_u32_from_elem()?;
        let term_a0_high = global.map(|c| c.term_a0high).get_u32_from_elem()?;
        let term_a0_low = global.map(|c| c.term_a0low).get_u32_from_elem()?;
        let term_a1_high = global.map(|c| c.term_a1high).get_u32_from_elem()?;
        let term_a1_low = global.map(|c| c.term_a1low).get_u32_from_elem()?;
        let shutdown_cycle = global.map(|c| c.shutdown_cycle).get_u32_from_elem()?;

        fn try_as_u16(x: u32) -> Result<u16> {
            x.try_into()
                .map_err(|err: TryFromIntError| anyhow!("{err}"))
        }

        let terminate_state = if is_terminate == 1 {
            Some(TerminateState {
                a0: HighLowU16(try_as_u16(term_a0_high)?, try_as_u16(term_a0_low)?),
                a1: HighLowU16(try_as_u16(term_a1_high)?, try_as_u16(term_a1_low)?),
            })
        } else {
            None
        };

        let output = if is_terminate == 1 {
            Some(output)
        } else {
            None
        };

        Ok(Rv32imV2Claim {
            pre_state,
            post_state,
            input,
            output,
            terminate_state,
            shutdown_cycle: Some(shutdown_cycle),
        })
    }
}

/// Decodes a PoVW nonce from a segment seal.
pub fn decode_povw_nonce(segment_seal: &[u32]) -> Result<PovwNonce> {
    ensure!(
        segment_seal[0] == RV32IM_SEAL_VERSION,
        "seal version mismatch"
    );
    let segment_seal = &segment_seal[1..];

    let io: &[Val] = bytemuck::checked::cast_slice(&segment_seal[..CircuitImpl::OUTPUT_SIZE]);
    let global = Tree::new(io, LAYOUT_GLOBAL);

    let povw_nonce_shorts_vec = global.map(|c| c.povw_nonce).get_shorts()?;
    let povw_nonce_shorts_arr = povw_nonce_shorts_vec
        .try_into()
        .map_err(|_| anyhow!("povw nonce global has unexpected length"))?;
    Ok(PovwNonce::from_u16s(povw_nonce_shorts_arr))
}
