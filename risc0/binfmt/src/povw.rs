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

//! Core types for function specific to proof of verifiable work (PoVW).

extern crate alloc;

use alloc::{collections::VecDeque, vec::Vec};

use borsh::{BorshDeserialize, BorshSerialize};
use ruint::aliases::{U64, U160, U256};
use serde::{Deserialize, Serialize};

#[cfg(feature = "rand")]
use rand::{
    Rng,
    distr::{Distribution, StandardUniform},
};

use crate::DecodeError;

/// A 160-bit identifier for a PoVW work log.
///
/// Each prover maintains one or more work logs, with each log having a unique identifier.
/// Each work log is guaranteed to have a distinct range of nonces, allowing the used nonces
/// from each log to be tracked separately.
pub type PovwLogId = U160;

/// Globally unique identifier for a proving job.
///
/// A proving job represents a single continuation (sequence of segments) being proven.
/// The job ID combines a work log identifier with a job number to create a globally
/// unique identifier that can generate nonces for each segment in the job.
#[derive(
    Copy,
    Clone,
    Debug,
    Default,
    Serialize,
    Deserialize,
    BorshSerialize,
    BorshDeserialize,
    PartialEq,
    Eq,
)]
pub struct PovwJobId {
    /// The work log that this job belongs to.
    pub log: PovwLogId,
    /// Job number within the work log.
    pub job: u64,
}

impl PovwJobId {
    /// Creates a nonce for a specific segment within this job.
    pub fn nonce(self, segment_index: u32) -> PovwNonce {
        PovwNonce {
            log: self.log,
            job: self.job,
            segment: segment_index,
        }
    }

    /// Serializes the job ID to a byte array in little-endian format.
    pub fn to_bytes(self) -> [u8; U160::BYTES + U64::BYTES] {
        let mut out = [0u8; U160::BYTES + U64::BYTES];
        out[..U64::BYTES].copy_from_slice(&self.job.to_le_bytes());
        out[U64::BYTES..U64::BYTES + U160::BYTES]
            .copy_from_slice(&self.log.to_le_bytes::<{ U160::BYTES }>());
        out
    }

    /// Deserializes a job ID from a byte array in little-endian format.
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

#[cfg(feature = "rand")]
impl Distribution<PovwJobId> for StandardUniform {
    fn sample<R: Rng + ?Sized>(&self, rng: &mut R) -> PovwJobId {
        PovwJobId {
            log: rng.random(),
            job: rng.random(),
        }
    }
}

/// A 256-bit unique nonce for Proof of Verifiable Work.
///
/// Each nonce uniquely identifies a single segment proof and prevents double-counting
/// of work. The nonce has a structured format combining a work log ID, job number,
/// and segment index.
#[derive(
    Copy,
    Clone,
    Debug,
    Default,
    Serialize,
    Deserialize,
    BorshSerialize,
    BorshDeserialize,
    PartialEq,
    Eq,
)]
pub struct PovwNonce {
    /// Work log identifier.
    pub log: PovwLogId,
    /// Job number within the work log.
    pub job: u64,
    /// Segment index within the job.
    pub segment: u32,
}

impl PovwNonce {
    /// A zero nonce constant.
    pub const ZERO: Self = Self {
        log: PovwLogId::ZERO,
        job: 0,
        segment: 0,
    };

    /// Converts the nonce to a 256-bit byte array in little-endian format.
    pub fn to_bytes(self) -> [u8; U256::BYTES] {
        <U256 as From<Self>>::from(self).to_le_bytes()
    }

    /// Creates a nonce from a 256-bit byte array in little-endian format.
    pub fn from_bytes(bytes: [u8; U256::BYTES]) -> Self {
        U256::from_le_bytes::<{ U256::BYTES }>(bytes).into()
    }

    /// Converts the nonce to its U256 representation.
    pub fn to_u256(self) -> U256 {
        (self.log.to::<U256>() << 96) | (U256::from(self.job) << 32) | U256::from(self.segment)
    }

    /// Converts the nonce to an array of 8 u32 values.
    pub fn to_u32s(self) -> [u32; 8] {
        let mut u32s = bytemuck::cast::<_, [u32; 8]>(self.to_bytes());
        // Bytes are little-endian, so on a big-endian machine, they need to be reversed.
        for x in u32s.iter_mut() {
            *x = u32::from_le(*x);
        }
        u32s
    }

    /// Converts the nonce to an array of 16 u16 values.
    pub fn to_u16s(self) -> [u16; 16] {
        let mut u16s = bytemuck::cast::<_, [u16; 16]>(self.to_bytes());
        // Bytes are little-endian, so on a big-endian machine, they need to be reversed.
        for x in u16s.iter_mut() {
            *x = u16::from_le(*x);
        }
        u16s
    }

    /// Creates a nonce from an array of 16 u16 values.
    pub fn from_u16s(mut u16s: [u16; 16]) -> Self {
        // Bytes need to be little-endian, so on a big-endian machine, they need to be reversed.
        for x in u16s.iter_mut() {
            *x = u16::from_le(*x);
        }
        Self::from_bytes(bytemuck::cast(u16s))
    }

    /// Encodes the nonce to a seal buffer.
    pub fn encode_to_seal(&self, buf: &mut Vec<u32>) {
        buf.extend(self.to_u16s().into_iter().map(u32::from));
    }

    /// Decodes a nonce from a seal buffer.
    pub fn decode_from_seal(buf: &mut VecDeque<u32>) -> Result<Self, DecodeError> {
        if buf.len() < 16 {
            return Err(DecodeError::EndOfStream);
        }
        fn u16_from_u32(x: u32) -> Result<u16, DecodeError> {
            x.try_into().map_err(|_| DecodeError::OutOfRange)
        }
        Ok(Self::from_u16s(
            buf.drain(..16)
                .map(u16_from_u32)
                .collect::<Result<Vec<_>, _>>()?
                .try_into()
                .unwrap(),
        ))
    }
}

impl From<PovwNonce> for U256 {
    /// Convert a [PovwNonce] to its [U256] representation.
    fn from(value: PovwNonce) -> Self {
        value.to_u256()
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

impl TryFrom<&[u8]> for PovwNonce {
    type Error = core::array::TryFromSliceError;

    fn try_from(value: &[u8]) -> Result<Self, Self::Error> {
        Ok(Self::from_bytes(value.try_into()?))
    }
}

impl TryFrom<Vec<u8>> for PovwNonce {
    type Error = core::array::TryFromSliceError;

    fn try_from(value: Vec<u8>) -> Result<Self, Self::Error> {
        value.as_slice().try_into()
    }
}

#[cfg(feature = "rand")]
impl Distribution<PovwNonce> for StandardUniform {
    fn sample<R: Rng + ?Sized>(&self, rng: &mut R) -> PovwNonce {
        PovwNonce {
            log: rng.random(),
            job: rng.random(),
            segment: rng.random(),
        }
    }
}

#[cfg(test)]
mod tests {
    use super::{PovwJobId, PovwNonce};

    #[test]
    fn test_povw_job_id_round_trip() {
        let original: PovwJobId = rand::random();
        let bytes = original.to_bytes();
        let reconstructed = PovwJobId::from_bytes(bytes);
        assert_eq!(original, reconstructed);
    }

    #[test]
    fn test_povw_nonce_bytes_round_trip() {
        let original: PovwNonce = rand::random();
        let bytes = original.to_bytes();
        let reconstructed = PovwNonce::from_bytes(bytes);
        assert_eq!(original, reconstructed);
    }

    #[test]
    fn test_povw_nonce_u16s_round_trip() {
        let original: PovwNonce = rand::random();
        let u16s = original.to_u16s();
        let reconstructed = PovwNonce::from_u16s(u16s);
        assert_eq!(original, reconstructed);
    }
}
