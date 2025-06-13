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

//! Core types for function specific to proof of verifiable work (PoVW).

// TODO(povw): Rename these are just Nonce, LogId, etc and use them as `poww::Nonce`?

use ruint::aliases::{U160, U256, U64};
use serde::{Deserialize, Serialize};

/// TODO
pub type PovwLogId = U160;

/// TODO
#[derive(Copy, Clone, Debug, Serialize, Deserialize, PartialEq, Eq)]
pub struct PovwJobId {
    /// TODO
    pub log: PovwLogId,
    /// TODO
    pub job: u64,
}

impl PovwJobId {
    /// TODO
    pub fn nonce(self, segment_index: u32) -> PovwNonce {
        PovwNonce {
            log: self.log,
            job: self.job,
            segment: segment_index,
        }
    }

    /// TODO
    pub fn to_bytes(self) -> [u8; U160::BYTES + U64::BYTES] {
        [
            self.job.to_le_bytes().as_slice(),
            self.log.to_le_bytes::<{ U160::BYTES }>().as_slice(),
        ]
        .concat()
        .try_into()
        .unwrap()
    }

    /// TODO
    pub fn from_bytes(bytes: [u8; U160::BYTES + U64::BYTES]) -> Self {
        Self {
            job: u64::from_le_bytes(bytes[..U64::BYTES].try_into().unwrap()),
            log: U160::from_le_bytes::<{ U160::BYTES }>(bytes[U64::BYTES..].try_into().unwrap()),
        }
    }
}

impl From<(PovwLogId, u64)> for PovwJobId {
    fn from((log, job): (PovwLogId, u64)) -> Self {
        Self { log, job }
    }
}

impl TryFrom<&[u8]> for PovwJobId {
    type Error = core::array::TryFromSliceError;

    fn try_from(value: &[u8]) -> Result<Self, Self::Error> {
        Ok(Self::from_bytes(value.try_into()?))
    }
}

/// TODO
#[derive(Copy, Clone, Debug, Serialize, Deserialize, PartialEq, Eq)]
pub struct PovwNonce {
    /// TODO
    pub log: PovwLogId,
    /// TODO
    pub job: u64,
    /// TODO
    pub segment: u32,
}

impl From<PovwNonce> for U256 {
    /// Convert a [PovwNonce] to its [U256] representation.
    fn from(value: PovwNonce) -> Self {
        (value.log.to::<U256>() << 96) | (U256::from(value.job) << 32) | U256::from(value.segment)
    }
}

impl From<U256> for PovwNonce {
    /// Convert a [U256] to a [PovwNonce].
    ///
    /// All [U256] can be mapped to a unique PoVW nonce.
    fn from(value: U256) -> Self {
        Self {
            log: (value >> 96usize).to(),
            job: ((value >> 32usize) & U256::from(u64::MAX)).to(),
            segment: (value & U256::from(u32::MAX)).to(),
        }
    }
}
