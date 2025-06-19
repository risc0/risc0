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

#[cfg(test)]
use rand::{
    distr::{Distribution, StandardUniform},
    Rng,
};

/// TODO
pub type PovwLogId = U160;

/// TODO
#[derive(Copy, Clone, Debug, Default, Serialize, Deserialize, PartialEq, Eq)]
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

#[cfg(test)]
impl Distribution<PovwJobId> for StandardUniform {
    fn sample<R: Rng + ?Sized>(&self, rng: &mut R) -> PovwJobId {
        PovwJobId {
            log: rng.random(),
            job: rng.random(),
        }
    }
}

/// TODO
#[derive(Copy, Clone, Debug, Default, Serialize, Deserialize, PartialEq, Eq)]
pub struct PovwNonce {
    /// TODO
    pub log: PovwLogId,
    /// TODO
    pub job: u64,
    /// TODO
    pub segment: u32,
}

impl PovwNonce {
    /// TODO
    pub fn to_bytes(self) -> [u8; U256::BYTES] {
        <U256 as From<Self>>::from(self).to_le_bytes()
    }

    /// TODO
    pub fn from_bytes(bytes: [u8; U256::BYTES]) -> Self {
        U256::from_le_bytes::<{ U256::BYTES }>(bytes).into()
    }

    /// TODO
    pub fn to_u32s(self) -> [u32; 8] {
        let mut u32s = bytemuck::cast::<_, [u32; 8]>(self.to_bytes());
        // Bytes are little-endian, so on a big-endian machine, they need to be reversed.
        for x in u32s.iter_mut() {
            *x = u32::from_le(*x);
        }
        u32s
    }

    /// TODO
    pub fn to_u16s(self) -> [u16; 16] {
        let mut u16s = bytemuck::cast::<_, [u16; 16]>(self.to_bytes());
        // Bytes are little-endian, so on a big-endian machine, they need to be reversed.
        for x in u16s.iter_mut() {
            *x = u16::from_le(*x);
        }
        u16s
    }

    /// TODO
    pub fn from_u16s(mut u16s: [u16; 16]) -> Self {
        // Bytes need to be little-endian, so on a big-endian machine, they need to be reversed.
        for x in u16s.iter_mut() {
            *x = u16::from_le(*x);
        }
        Self::from_bytes(bytemuck::cast(u16s))
    }
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

#[cfg(test)]
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
