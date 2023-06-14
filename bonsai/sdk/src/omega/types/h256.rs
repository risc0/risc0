// Copyright 2023 RISC Zero, Inc.
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

use core::{
    fmt::{self, Debug, Display, Formatter},
    str::FromStr,
};

use hex::{FromHex, FromHexError};
use risc0_zkvm::sha::Digest;
use serde::{Deserialize, Deserializer, Serialize, Serializer};

/// The number of bytes required to represent a full digest (32).
pub const HASH_256_BYTES: usize = 256 / 8;

/// A helper wrapper for a full 256-bit hash.
#[derive(Clone, Eq, Hash, Ord, PartialEq, PartialOrd)]
#[cfg_attr(feature = "sqlx", derive(sqlx::Type), sqlx(transparent))]
pub struct H256([u8; HASH_256_BYTES]);

impl H256 {
    /// Returns a byte slice of this [H256]'s contents.
    pub fn as_bytes(&self) -> &[u8] {
        &self.0
    }

    /// Instantiates a digest from a word representation
    pub fn from_full_digest_words(words: [u32; 8]) -> Self {
        Self(bytemuck::cast(words))
    }
}

impl Default for H256 {
    /// Returns 256 zero bits as the default digest.
    fn default() -> Self {
        Self([0u8; HASH_256_BYTES])
    }
}

impl From<Digest> for H256 {
    fn from(digest: Digest) -> Self {
        let bytes: [u8; HASH_256_BYTES] = digest.into();
        H256(bytes)
    }
}

impl From<&Digest> for H256 {
    fn from(digest: &Digest) -> Self {
        digest.to_owned().into()
    }
}

impl From<[u8; HASH_256_BYTES]> for H256 {
    fn from(data: [u8; HASH_256_BYTES]) -> Self {
        Self(data)
    }
}

impl TryFrom<&[u8]> for H256 {
    type Error = core::array::TryFromSliceError;

    fn try_from(data: &[u8]) -> Result<Self, Self::Error> {
        Ok(<[u8; HASH_256_BYTES]>::try_from(data)?.into())
    }
}

impl AsRef<[u8]> for H256 {
    fn as_ref(&self) -> &[u8] {
        self.as_bytes()
    }
}

/// Parses an [H256] instance from a hex encoded string.
impl FromStr for H256 {
    type Err = FromHexError;

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let bytes = <[u8; HASH_256_BYTES]>::from_hex(s)?;
        Ok(H256(bytes))
    }
}

impl From<H256> for [u8; HASH_256_BYTES] {
    fn from(digest: H256) -> Self {
        digest.0
    }
}

impl From<H256> for Digest {
    fn from(digest: H256) -> Self {
        Digest::from(digest.0)
    }
}

impl<'a> From<&'a H256> for &'a Digest {
    fn from(digest: &'a H256) -> Self {
        bytemuck::cast_ref(&digest.0)
    }
}

/// Formats [H256] as a hex encoded string.
impl Display for H256 {
    fn fmt(&self, f: &mut Formatter) -> core::fmt::Result {
        f.write_str(&hex::encode(self))
    }
}

impl Debug for H256 {
    fn fmt(&self, f: &mut Formatter) -> core::fmt::Result {
        write!(f, "H256({})", &hex::encode(self))
    }
}

/// Serialize the [struct@H256] using [`Display`] for text-based formats and as
/// raw byte data for binary formats.
impl Serialize for H256 {
    fn serialize<S: Serializer>(&self, serializer: S) -> Result<S::Ok, S::Error> {
        if serializer.is_human_readable() {
            serializer.collect_str(self)
        } else {
            self.0.serialize(serializer)
        }
    }
}

/// Deserialize a [struct@H256] using [`FromStr`] for text-based formats and
/// from raw byte data for binary formats.
impl<'de> Deserialize<'de> for H256 {
    fn deserialize<D: Deserializer<'de>>(deserializer: D) -> Result<Self, D::Error> {
        if deserializer.is_human_readable() {
            use serde::de::{Error, Visitor};

            struct StrParser();
            impl<'de> Visitor<'de> for StrParser {
                type Value = H256;
                fn expecting(&self, formatter: &mut Formatter<'_>) -> fmt::Result {
                    write!(formatter, "a string")
                }
                fn visit_str<E: Error>(self, s: &str) -> Result<Self::Value, E> {
                    s.parse().map_err(Error::custom)
                }
            }
            // parse the string using from_str
            deserializer.deserialize_str(StrParser())
        } else {
            let bytes: [u8; HASH_256_BYTES] = Deserialize::deserialize(deserializer)?;
            Ok(H256(bytes))
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    const HEX: &str = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";

    #[test]
    fn test_digest_conversion() {
        let digest = Digest::from_hex(HEX).unwrap();

        let h256: H256 = digest.into();
        assert_eq!(h256, H256::from_str(HEX).unwrap());
        assert_eq!(h256, H256::try_from(digest.as_bytes()).unwrap());
        assert_eq!(h256.as_bytes(), digest.as_bytes());
    }

    #[test]
    fn test_hex_roundtrip() {
        assert_eq!(H256::from_str(HEX).unwrap().to_string(), HEX);
    }

    #[test]
    fn test_serialize_human_readable() {
        let hash = H256::from_str(HEX).unwrap();
        // JSON serialization should match Display
        assert_eq!(
            serde_json::to_string(&hash).unwrap(),
            format!("\"{}\"", hash.to_string())
        );
        // binary serialization should match the raw bytes
        assert_eq!(bincode::serialize(&hash).unwrap(), hash.as_bytes());
    }

    #[test]
    fn test_serde_roundtrip() {
        let hash = H256::from_str(HEX).unwrap();

        let json = serde_json::to_value(&hash).unwrap();
        assert_eq!(hash, serde_json::from_value(json).unwrap());
        let bytes = bincode::serialize(&hash).unwrap();
        assert_eq!(hash, bincode::deserialize(&bytes).unwrap());
    }
}
