// Copyright 2022 Risc0, Inc.
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

//! Simple SHA-256 wrappers.

use alloc::{borrow::Cow, string::String, vec::Vec};
use core::{
    fmt::{Debug, Display, Formatter},
    mem,
};

use anyhow::{bail, Error, Result};
use bytemuck::{Pod, Zeroable};
use serde::{Deserialize, Serialize};

/// The number of words represented by a [Digest].  We represent a
/// SHA-256 digest as 8 32-bit words instead of the traditional 32
/// 8-bit bytes.
pub const DIGEST_WORDS: usize = 8;

/// The size of a word within a [Digest] (32-bits = 4 bytes).
pub const DIGEST_WORD_SIZE: usize = mem::size_of::<u32>();

/// The number of words in a SHA block.  When using hash_raw_words,
/// you can avoid a copy by making sure the number of words is a
/// multiple of BLOCK_WORDS.
pub const BLOCK_WORDS: usize = 16;

/// The result of a SHA-256 hashing function.
#[derive(Eq, PartialEq, Copy, Zeroable, Pod, Serialize, Deserialize)]
#[repr(transparent)]
pub struct Digest([u32; DIGEST_WORDS]);

impl Digest {
    /// Create a new [Digest] from an existing array of words.
    pub fn new(data: [u32; DIGEST_WORDS]) -> Digest {
        Digest(data)
    }

    /// Try to create a [Digest] from a slice of words.
    pub fn try_from_slice(words: &[u32]) -> Result<Self> {
        Ok(Digest(words.try_into().map_err(Error::msg)?))
    }

    /// Create a [Digest] from a slice of words.
    ///
    /// # Panics
    ///
    /// Panics if the number of words is not exactly [DIGEST_WORDS].
    pub fn from_slice(words: &[u32]) -> Self {
        Self::try_from_slice(words).unwrap()
    }

    /// Returns a slice of words.
    pub fn as_slice(&self) -> &[u32] {
        &self.0
    }

    /// Returns a mutable slice of words.
    pub fn as_mut_slice(&mut self) -> &mut [u32] {
        &mut self.0
    }

    /// Returns a slice of words.
    pub fn get(&self) -> &[u32; DIGEST_WORDS] {
        &self.0
    }

    /// Returns a mutable slice of words.
    pub fn get_mut(&mut self) -> &mut [u32; DIGEST_WORDS] {
        &mut self.0
    }

    /// Returns a hexadecimal string representation of the [Digest].
    pub fn to_hex(&self) -> String {
        fn hex(digit: u8) -> char {
            char::from_digit(digit as u32, 16).unwrap()
        }
        self.0
            .iter()
            .flat_map(|word| word.to_be_bytes())
            .flat_map(|byte| [hex(byte >> 4), hex(byte & 0xF)])
            .collect()
    }
}

/// Converts a hexadecimal string into a [Digest].
impl TryFrom<&str> for Digest {
    type Error = anyhow::Error;
    fn try_from(s: &str) -> Result<Digest> {
        if s.len() != DIGEST_WORDS * DIGEST_WORD_SIZE * 2 {
            bail!("Expected {DIGEST_WORDS} words in {s}");
        }
        let words: Result<Vec<u32>> = (0..DIGEST_WORDS)
            .into_iter()
            .map(|x| u32::from_str_radix(&s[x * 8..(x + 1) * 8], 16).map_err(Error::msg))
            .collect();
        Self::try_from_slice(words?.as_slice())
    }
}

impl Default for Digest {
    fn default() -> Digest {
        Digest([0; DIGEST_WORDS])
    }
}

impl Display for Digest {
    fn fmt(&self, f: &mut Formatter) -> core::fmt::Result {
        for word in self.0 {
            core::write!(f, "{:08x?}", word)?;
        }
        Ok(())
    }
}

impl Debug for Digest {
    fn fmt(&self, f: &mut Formatter) -> core::fmt::Result {
        for word in self.0 {
            core::write!(f, "{:08x?}", word)?;
        }
        Ok(())
    }
}

impl Clone for Digest {
    fn clone(&self) -> Digest {
        Digest(self.0)
    }
}

#[cfg(target_os = "zkvm")]
use super::sha_zkvm as sha_impl;

#[cfg(not(target_os = "zkvm"))]
use super::sha_cpu as sha_impl;

/// Generate a SHA from a slice of bytes.
pub fn hash_bytes(bytes: &[u8]) -> Cow<Digest> {
    sha_impl::hash_bytes(bytes)
}

/// Generate a SHA from a slice of words without adding the size at
/// the end.  If needed, zero padding is still added to pad the data
/// to a multiple of BLOCK_WORDS.
pub fn hash_raw_words(words: &[u32]) -> Cow<'static, Digest> {
    sha_impl::hash_raw_words(words)
}

/// Generate a SHA from a pair of [Digests](Digest).
pub fn hash_pair(a: &Digest, b: &Digest) -> Cow<'static, Digest> {
    sha_impl::hash_pair(a, b)
}

/// Generate a new digest by mixing two digests together via XOR,
/// and stores it back in the pool.
pub fn digest_mix(pool: &mut Digest, val: &Digest) {
    for (pool_word, val_word) in pool.get_mut().iter_mut().zip(val.get()) {
        *pool_word ^= *val_word;
    }
}

#[cfg(test)]
mod tests {
    use super::Digest;

    #[test]
    fn test_from_str() {
        assert_eq!(
            Digest::try_from("00000077000000AA0000001200000034000000560000007a000000a900000009")
                .unwrap(),
            Digest::new([119, 170, 18, 52, 86, 122, 169, 9])
        );
    }
}

#[allow(missing_docs)]
pub mod testutil {
    use alloc::{borrow::Cow, vec::Vec};

    use super::{hash_bytes, hash_pair, hash_raw_words, Digest};

    // Runs conformance test on a SHA implementation to make sure it
    // properly behaves.  This is purposefully not behind #[cfg(test)]
    // so that it can be run in a zkvm guest.
    pub fn test_sha_impl() {
        test_hash_pair();
        test_sha_basics();
        test_raw_words();

        crate::core::sha_rng::testutil::test_sha_rng_impl();
    }

    fn test_sha_basics() {
        // Standard test vectors
        assert_eq!(
            *hash_bytes("abc".as_bytes()),
            Digest::new([
                0xba7816bf, 0x8f01cfea, 0x414140de, 0x5dae2223, 0xb00361a3, 0x96177a9c, 0xb410ff61,
                0xf20015ad
            ])
        );
        assert_eq!(
            *hash_bytes("".as_bytes()),
            Digest::new([
                0xe3b0c442, 0x98fc1c14, 0x9afbf4c8, 0x996fb924, 0x27ae41e4, 0x649b934c, 0xa495991b,
                0x7852b855
            ])
        );
        assert_eq!(
            *hash_bytes("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq".as_bytes()),
            Digest::new([
                0x248d6a61, 0xd20638b8, 0xe5c02693, 0x0c3e6039, 0xa33ce459, 0x64ff2167, 0xf6ecedd4,
                0x19db06c1
            ])
        );
        assert_eq!(*hash_bytes(
            "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu" .as_bytes()),
            Digest::new([0xcf5b16a7,
                       0x78af8380,
                       0x036ce59e,
                       0x7b049237,
                       0x0b249b11,
                       0xe8f07a51,
                       0xafac4503,
                       0x7afee9d1]));
        // Test also the 'hexDigest' bit.
        // Python says:
        // >>> hashlib.sha256("Byzantium").hexdigest()
        // 'f75c763b4a52709ac294fc7bd7cf14dd45718c3d50b36f4732b05b8c6017492a'
        assert_eq!(
            hash_bytes(&"Byzantium".as_bytes()).to_hex(),
            "f75c763b4a52709ac294fc7bd7cf14dd45718c3d50b36f4732b05b8c6017492a"
        );
    }

    fn hash_rawvec(len: usize) -> Cow<'static, Digest> {
        let items: Vec<u32> = (0..len as u32).into_iter().collect();
        hash_raw_words(items.as_slice())
    }

    fn test_raw_words() {
        const LENS: &[usize] = &[0, 1, 7, 8, 9];
        const EXPECTED_STRS: &[&str] = &[
            "6a09e667bb67ae853c6ef372a54ff53a510e527f9b05688c1f83d9ab5be0cd19",
            "da5698be17b9b46962335799779fbeca8ce5d491c0d26243bafef9ea1837a9d8",
            "f5291d65176f19d6c22b9377df2ed418e0f4ea044e9dee9fa2f8dbf863f1c615",
            "8a5f075fdf7d09b8103c0e88c30a906f13a962e0c4562c09d2c95b928d9cee46",
            "ab57060d5b4b27718986483158dcf069e87ba7a52f6bf960d49f6d305b733281",
        ];

        let expected: Vec<Digest> = EXPECTED_STRS
            .iter()
            .map(|&x| Digest::try_from(x).unwrap())
            .collect();
        let actual: Vec<Digest> = LENS.iter().map(|x| *hash_rawvec(*x)).collect();
        assert_eq!(expected, actual);
    }

    fn test_hash_pair() {
        assert_eq!(
            *hash_pair(
                &Digest::try_from(
                    "6a09e667bb67ae853c6ef372a54ff53a510e527f9b05688c1f83d9ab5be0cd19"
                )
                .unwrap(),
                &Digest::try_from(
                    "ed375cadc653bb9078cee904acee6f7ff2bf7476c92dc92911bae27c41ebc015"
                )
                .unwrap()
            ),
            Digest::try_from("3aa2c47c47cd9e5c5259fd1c3428c30b9608201f5e163061deea8d2d7c65f2c3")
                .unwrap()
        );
    }
}
