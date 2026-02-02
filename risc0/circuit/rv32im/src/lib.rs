// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#![cfg_attr(not(feature = "std"), no_std)]

extern crate alloc;

use alloc::vec::Vec;

#[cfg(feature = "execute")]
pub mod execute;
#[cfg(feature = "prove")]
pub mod prove;
pub mod trace;
mod verify;
mod zirgen;

use anyhow::{Result, anyhow, bail, ensure};
use derive_more::Debug;
use risc0_binfmt::ExitCode;
use risc0_binfmt::PovwNonce;
use risc0_zkp::core::digest::{DIGEST_BYTES, DIGEST_SHORTS, DIGEST_WORDS, Digest};
use risc0_zkp::field::baby_bear::Elem;
use risc0_zkvm_platform::syscall::halt;
use serde::{Deserialize, Serialize};

#[cfg(feature = "execute")]
pub use risc0_circuit_rv32im_sys::BlockType;

pub use self::zirgen::CircuitImpl;
pub use verify::verify;

/// This number was picked by running `bigint2-analyze` on all the current bigint programs
pub const MAX_INSN_ROWS: usize = 25_000;

/// This is a smaller number used by lower po2's < 15 which can't fit a large bigint program.
pub const MAX_INSN_ROWS_LOWER_PO2: usize = 2_000;

#[cfg(not(target_os = "zkvm"))]
#[derive(Clone, Copy, Debug, enum_map::Enum, Serialize, Deserialize)]
#[non_exhaustive]
pub enum EcallKind {
    BigInt,
    Poseidon2,
    Read,
    Sha2,
    Terminate,
    User,
    Write,
}

#[cfg(not(target_os = "zkvm"))]
#[derive(Clone, Debug, Default, Serialize, Deserialize)]
#[non_exhaustive]
pub struct EcallMetric {
    pub count: u64,
}

#[cfg(not(target_os = "zkvm"))]
impl EcallMetric {
    pub fn new(count: u64) -> Self {
        Self { count }
    }
}

/// Version of the seal for the m3-variant of the rv32im circuit.
pub const RV32IM_SEAL_VERSION: u32 = 3;

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
pub struct Claim {
    pub po2: u32,
    pub pre_state: Digest,
    pub post_state: Digest,
    pub output: Option<Digest>,
    pub terminate_state: Option<TerminateState>,
    pub povw_nonce: PovwNonce,
}

struct Decoder<'a> {
    seal: &'a [u32],
}

impl<'a> Decoder<'a> {
    fn new(seal: &'a [u32]) -> Self {
        Self { seal }
    }

    fn read(&mut self, len: usize) -> Result<&'a [u32]> {
        ensure!(len <= self.seal.len(), "Unexpected end of seal");
        let (slice, remain) = self.seal.split_at(len);
        self.seal = remain;
        Ok(slice)
    }

    fn read_u32(&mut self) -> Result<u32> {
        let slice = self.read(1)?;
        Ok(slice[0])
    }

    fn read_u32_from_elem(&mut self) -> Result<u32> {
        Ok(bytemuck::checked::cast::<_, Elem>(self.read_u32()?).as_u32())
    }

    fn read_u32_from_shorts(&mut self) -> Result<u32> {
        let slice = bytemuck::checked::cast_slice::<_, Elem>(self.read(2)?);
        let (high, low) = (slice[1], slice[0]);
        let val = (high.as_u32() & 0xffff) << 16 | (low.as_u32() & 0xffff);
        Ok(val)
    }

    fn read_digest_from_words(&mut self) -> Result<Digest> {
        let slice = bytemuck::checked::cast_slice::<_, Elem>(self.read(DIGEST_WORDS)?);
        let buf = slice.iter().map(|x| x.as_u32()).collect::<Vec<u32>>();
        Ok(Digest::try_from(buf).unwrap())
    }

    fn read_digest_from_shorts(&mut self) -> Result<Digest> {
        let slice = self.read(DIGEST_SHORTS)?;
        let mut digest_bytes = [0; DIGEST_BYTES];
        for i in 0..DIGEST_SHORTS {
            let elem: Elem = bytemuck::checked::cast(slice[i]);
            let word = elem.as_u32();
            let short =
                u16::try_from(word).map_err(|e| anyhow!("failed to convert u32 to u16: {e}"))?;
            let short_bytes = short.to_le_bytes();
            digest_bytes[i * 2..i * 2 + 2].copy_from_slice(&short_bytes);
        }
        Ok(Digest::from_bytes(digest_bytes))
    }
}

impl Claim {
    pub fn decode(seal: &[u32]) -> Result<Self> {
        let mut decoder = Decoder::new(seal);

        let seal_version = decoder.read_u32()?;
        ensure!(
            seal_version == RV32IM_SEAL_VERSION,
            "seal version mismatch: actual={seal_version} expected={RV32IM_SEAL_VERSION}"
        );

        let po2 = decoder.read_u32()?;

        let pre_state = decoder.read_digest_from_words()?;
        let post_state = decoder.read_digest_from_words()?;
        let is_terminate = decoder.read_u32_from_elem()?;
        let term_a0 = decoder.read_u32_from_shorts()?;
        let term_a1 = decoder.read_u32_from_shorts()?;
        let output = decoder.read_digest_from_shorts()?;
        let mut povw_nonce = [0u32; 8];
        for v in &mut povw_nonce {
            *v = decoder.read_u32_from_shorts()?;
        }

        let (terminate_state, output) = if is_terminate == 1 {
            (
                Some(TerminateState {
                    a0: term_a0.into(),
                    a1: term_a1.into(),
                }),
                Some(output),
            )
        } else {
            (None, None)
        };

        Ok(Self {
            po2,
            pre_state,
            post_state,
            output,
            terminate_state,
            povw_nonce: PovwNonce::from_u32s(povw_nonce),
        })
    }

    pub fn exit_code(&self) -> Result<ExitCode> {
        let exit_code = if let Some(term) = self.terminate_state {
            let HighLowU16(user_exit, halt_type) = term.a0;
            match halt_type as u32 {
                halt::TERMINATE => ExitCode::Halted(user_exit as u32),
                halt::PAUSE => ExitCode::Paused(user_exit as u32),
                _ => bail!("Illegal halt type: {halt_type}"),
            }
        } else {
            ExitCode::SystemSplit
        };
        Ok(exit_code)
    }
}

/// Decodes a PoVW nonce from a segment seal.
pub fn decode_povw_nonce(segment_seal: &[u32]) -> Result<PovwNonce> {
    let claim = Claim::decode(segment_seal)?;
    Ok(claim.povw_nonce)
}
