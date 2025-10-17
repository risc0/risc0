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
use risc0_zkp::core::digest::Digest;
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
pub struct Rv32imM3Claim {
    pub pre_state: Digest,
    pub post_state: Digest,
    pub input: Digest,
    pub output: Option<Digest>,
    pub terminate_state: Option<TerminateState>,
    pub shutdown_cycle: Option<u32>,
}

impl Rv32imM3Claim {
    pub fn decode(seal: &[u32]) -> Result<Self> {
        ensure!(seal[0] == RV32IM_SEAL_VERSION, "seal version mismatch");

        // TODO: fix this
        let pre_state = Digest::ZERO;
        let post_state = Digest::ZERO;
        let input = Digest::ZERO;
        let output = None;
        let terminate_state = None;
        let shutdown_cycle = 0;

        Ok(Self {
            pre_state,
            post_state,
            input,
            output,
            terminate_state,
            shutdown_cycle: Some(shutdown_cycle),
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
