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

//! A generic (cross hash) digest, which is always 256 bits and composed of 8
//! words

use alloc::{format, vec::Vec};
use core::fmt::{Debug, Display, Formatter};

use borsh::{BorshDeserialize, BorshSerialize};
use bytemuck::{Pod, PodCastError, Zeroable};
use hex::{FromHex, FromHexError};
use serde::{Deserialize, Serialize};

pub use crate::digest;
pub use hex_literal::hex;
pub use risc0_zkvm_platform::WORD_SIZE;

/// The number of words in the representation of a [Digest].
pub const DIGEST_WORDS: usize = 8;

/// The number of shorts in the representation of a [Digest].
pub const DIGEST_SHORTS: usize = DIGEST_WORDS * 2;

/// Size of the [Digest] representation in bytes.
///
/// Note that digests are stored in memory as words instead of bytes.
pub const DIGEST_BYTES: usize = DIGEST_WORDS * WORD_SIZE;

/// Digest represents the results of a hashing function.  It is always 256 bits
/// of storage although depending on the hash it may have additional structure
/// (for example Poseidon's output is actually composed of field elements).  The
/// storage is in u32's in part to simplify alignment requirements, especially
/// in the zkVM.
#[derive(
    Copy,
    Clone,
    Eq,
    Ord,
    PartialOrd,
    PartialEq,
    Hash,
    Pod,
    Zeroable,
    Serialize,
    Deserialize,
    BorshSerialize,
    BorshDeserialize,
)]
#[repr(transparent)]
pub struct Digest([u32; DIGEST_WORDS]);

impl Digest {
    /// Digest of all zeroes.
    pub const ZERO: Self = Self::new([0u32; DIGEST_WORDS]);

    /// Constant constructor
    pub const fn new(data: [u32; DIGEST_WORDS]) -> Self {
        Self(data)
    }

    /// Construct a digest from a array of bytes in a const context.
    /// Outside of const context, `Digest::from` is recommended.
    pub const fn from_bytes(bytes: [u8; DIGEST_BYTES]) -> Self {
        let mut digest: Digest = Digest::ZERO;
        let mut i: usize = 0;
        while i < DIGEST_WORDS {
            let mut j = 0;
            let mut word = 0u32;
            while j < WORD_SIZE {
                word <<= 8;
                word |= bytes[i * WORD_SIZE + j] as u32;
                j += 1;
            }
            word = u32::from_be(word);
            digest.0[i] = word;
            i += 1;
        }
        digest
    }

    /// Returns a reference to the [Digest] as a slice of words.
    pub fn as_words(&self) -> &[u32] {
        &self.0
    }

    /// Returns a reference to the [Digest] as a slice of bytes.
    pub fn as_bytes(&self) -> &[u8] {
        bytemuck::cast_slice(&self.0)
    }

    /// Returns a mutable slice of words.
    pub fn as_mut_words(&mut self) -> &mut [u32] {
        &mut self.0
    }

    /// Returns a mutable slice of bytes.
    pub fn as_mut_bytes(&mut self) -> &mut [u8] {
        bytemuck::cast_slice_mut(&mut self.0)
    }
}

impl Default for Digest {
    fn default() -> Digest {
        Digest([0; DIGEST_WORDS])
    }
}

/// Create a new [Digest] from an array of words.
impl From<[u32; DIGEST_WORDS]> for Digest {
    fn from(data: [u32; DIGEST_WORDS]) -> Self {
        Self(data)
    }
}

/// Create a new [Digest] from an array of bytes.
impl From<[u8; DIGEST_BYTES]> for Digest {
    fn from(data: [u8; DIGEST_BYTES]) -> Self {
        match bytemuck::try_cast(data) {
            Ok(digest) => digest,
            Err(PodCastError::TargetAlignmentGreaterAndInputNotAligned) => {
                // Bytes are not aligned. Copy the byte array into a new digest.
                bytemuck::pod_read_unaligned(&data)
            }
            Err(e) => unreachable!("failed to cast [u8; DIGEST_BYTES] to Digest: {}", e),
        }
    }
}

impl<'a> From<&'a [u32; DIGEST_WORDS]> for &'a Digest {
    fn from(data: &'a [u32; DIGEST_WORDS]) -> Self {
        bytemuck::cast_ref(data)
    }
}

impl FromHex for Digest {
    type Error = FromHexError;

    fn from_hex<T: AsRef<[u8]>>(hex: T) -> Result<Self, Self::Error> {
        Ok(<[u8; DIGEST_BYTES]>::from_hex(hex)?.into())
    }
}

impl TryFrom<&[u8]> for Digest {
    type Error = core::array::TryFromSliceError;

    fn try_from(data: &[u8]) -> Result<Self, Self::Error> {
        Ok(<[u8; DIGEST_BYTES]>::try_from(data)?.into())
    }
}

impl TryFrom<&[u32]> for Digest {
    type Error = core::array::TryFromSliceError;

    fn try_from(data: &[u32]) -> Result<Self, Self::Error> {
        Ok(<[u32; DIGEST_WORDS]>::try_from(data)?.into())
    }
}

impl<'a> TryFrom<&'a [u32]> for &'a Digest {
    type Error = PodCastError;

    fn try_from(data: &'a [u32]) -> Result<Self, Self::Error> {
        match bytemuck::try_cast_slice(data) {
            Ok([digest]) => Ok(digest),
            Ok(_) => Err(PodCastError::SizeMismatch),
            Err(e) => Err(e),
        }
    }
}

impl TryFrom<Vec<u8>> for Digest {
    type Error = Vec<u8>;

    fn try_from(data: Vec<u8>) -> Result<Self, Self::Error> {
        Ok(<[u8; DIGEST_BYTES]>::try_from(data)?.into())
    }
}

impl TryFrom<Vec<u32>> for Digest {
    type Error = Vec<u32>;

    fn try_from(data: Vec<u32>) -> Result<Self, Self::Error> {
        Ok(<[u32; DIGEST_WORDS]>::try_from(data)?.into())
    }
}

impl From<Digest> for [u8; DIGEST_BYTES] {
    fn from(digest: Digest) -> Self {
        bytemuck::cast(digest)
    }
}

impl From<Digest> for [u32; DIGEST_WORDS] {
    fn from(digest: Digest) -> Self {
        digest.0
    }
}

impl AsRef<[u8; DIGEST_BYTES]> for Digest {
    fn as_ref(&self) -> &[u8; DIGEST_BYTES] {
        bytemuck::cast_ref(&self.0)
    }
}

impl AsMut<[u8; DIGEST_BYTES]> for Digest {
    fn as_mut(&mut self) -> &mut [u8; DIGEST_BYTES] {
        bytemuck::cast_mut(&mut self.0)
    }
}

impl AsRef<[u32; DIGEST_WORDS]> for Digest {
    fn as_ref(&self) -> &[u32; DIGEST_WORDS] {
        &self.0
    }
}

impl AsMut<[u32; DIGEST_WORDS]> for Digest {
    fn as_mut(&mut self) -> &mut [u32; DIGEST_WORDS] {
        &mut self.0
    }
}

impl AsRef<[u8]> for Digest {
    fn as_ref(&self) -> &[u8] {
        self.as_bytes()
    }
}

impl AsMut<[u8]> for Digest {
    fn as_mut(&mut self) -> &mut [u8] {
        self.as_mut_bytes()
    }
}

impl AsRef<[u32]> for Digest {
    fn as_ref(&self) -> &[u32] {
        self.as_words()
    }
}

impl AsMut<[u32]> for Digest {
    fn as_mut(&mut self) -> &mut [u32] {
        self.as_mut_words()
    }
}

impl Display for Digest {
    fn fmt(&self, f: &mut Formatter) -> core::fmt::Result {
        f.write_str(&hex::encode(self))
    }
}

impl Debug for Digest {
    fn fmt(&self, f: &mut Formatter) -> core::fmt::Result {
        f.write_str(&format!("Digest({})", &hex::encode(self)))
    }
}

/// Macro for constructing a Digest from a hex string.
#[macro_export]
macro_rules! digest {
    ($s:literal) => {{
        const BYTES: [u8; $crate::core::digest::DIGEST_BYTES] = $crate::core::digest::hex!($s);
        $crate::core::digest::Digest::from_bytes(BYTES)
    }};
}

#[cfg(test)]
mod tests {
    use hex::FromHex;

    use super::Digest;

    #[test]
    fn test_from_hex() {
        assert_eq!(
            Digest::from_hex("00000077000000AA0000001200000034000000560000007a000000a900000009")
                .unwrap(),
            Digest::from([
                0x77_u32.to_be(),
                0xaa_u32.to_be(),
                0x12_u32.to_be(),
                0x34_u32.to_be(),
                0x56_u32.to_be(),
                0x7a_u32.to_be(),
                0xa9_u32.to_be(),
                0x09_u32.to_be(),
            ])
        );
    }

    #[test]
    fn test_roundtrip() {
        const HEX: &str = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";
        assert_eq!(hex::encode(Digest::from_hex(HEX).unwrap()), HEX);
    }
}
