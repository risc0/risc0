// Copyright 2025 RISC Zero, Inc.
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

#[cfg(feature = "prove")]
pub mod prove;
pub mod verify;
mod zirgen;

use anyhow::{Result, bail, ensure};
use risc0_binfmt::ExitCode;
use risc0_zkp::{
    core::digest::{DIGEST_BYTES, DIGEST_SHORTS, DIGEST_WORDS, Digest},
    field::baby_bear::Elem,
};
use risc0_zkvm_platform::syscall::halt;
use serde::{Deserialize, Serialize};

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
}

struct Decoder<'a> {
    seal: &'a [u32],
}

impl<'a> Decoder<'a> {
    fn new(seal: &'a [u32]) -> Self {
        Self { seal }
    }

    fn read(&mut self, len: usize) -> &'a [u32] {
        let (slice, remain) = self.seal.split_at(len);
        self.seal = remain;
        slice
    }

    fn read_u32(&mut self) -> u32 {
        let slice = self.read(1);
        slice[0]
    }

    fn read_u32_from_elem(&mut self) -> u32 {
        Elem::new_raw(self.read_u32()).as_u32()
    }

    fn read_u32_from_shorts(&mut self) -> u32 {
        let slice = self.read(2);
        let (high, low) = (Elem::new(slice[0]), Elem::new(slice[1]));
        (high.as_u32() & 0xffff) << 16 | (low.as_u32() & 0xffff)
    }

    fn read_digest_from_words(&mut self) -> Result<Digest> {
        let slice = self.read(DIGEST_WORDS);
        let mut buf = slice.to_vec();
        for word in buf.iter_mut() {
            *word = Elem::new_raw(*word).as_u32();
        }
        Ok(Digest::try_from(buf.as_slice())?)
    }

    fn read_digest_from_shorts(&mut self) -> Result<Digest> {
        let slice = self.read(DIGEST_SHORTS);
        let mut digest_bytes = [0; DIGEST_BYTES];
        for i in 0..DIGEST_SHORTS {
            let elem = Elem::new_raw(slice[i]);
            let word = elem.as_u32();
            let short = u16::try_from(word)?;
            let short_bytes = short.to_le_bytes();
            digest_bytes[i * 2..i * 2 + 2].copy_from_slice(&short_bytes);
        }
        Ok(Digest::from_bytes(digest_bytes))
    }
}

impl Claim {
    pub fn decode(seal: &[u32]) -> Result<Self> {
        let mut decoder = Decoder::new(seal);

        let version = decoder.read_u32();
        ensure!(version == RV32IM_SEAL_VERSION, "seal version mismatch");

        let po2 = decoder.read_u32();

        let pre_state = decoder.read_digest_from_words()?;
        let post_state = decoder.read_digest_from_words()?;
        let is_terminate = decoder.read_u32_from_elem();
        let term_a0 = decoder.read_u32_from_shorts();
        let term_a1 = decoder.read_u32_from_shorts();
        let output = decoder.read_digest_from_shorts()?;

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
