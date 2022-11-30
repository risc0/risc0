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

use alloc::{string::String, vec::Vec};
use core::{
    fmt::{Debug, Display, Formatter},
    mem,
    ops::Deref,
};

use anyhow::{Error, Result};
use bytemuck::{Pod, Zeroable};
use risc0_zeroio::{Deserialize as ZeroioDeserialize, Serialize as ZeroioSerialize};
use serde::{Deserialize, Serialize};

/// The number of words represented by a [Digest].
// We represent a SHA-256 digest as 8 32-bit words instead of the
// traditional 32 8-bit bytes.
pub const DIGEST_WORDS: usize = 8;

/// The size of a word within a [Digest] (32-bits = 4 bytes).
pub const DIGEST_WORD_SIZE: usize = mem::size_of::<u32>();

/// Standard SHA initialization vector .
pub static SHA256_INIT: Digest = Digest::new([
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19,
]);

/// The result of a SHA-256 hashing function.
// TODO(nils): Remove 'Copy' trait on Digest; these are not small and
// we don't want to copy them around accidentally.
#[derive(
    Eq, PartialEq, Copy, Zeroable, Pod, Serialize, Deserialize, ZeroioSerialize, ZeroioDeserialize,
)]
#[repr(transparent)]
pub struct Digest([u32; DIGEST_WORDS]);

impl Digest {
    /// Create a new [Digest] from an existing array of words.
    pub const fn new(data: [u32; DIGEST_WORDS]) -> Digest {
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

    /// Converts a hexadecimal string into a [Digest].
    pub fn from_str(s: &str) -> Digest {
        s.into()
    }
}

impl From<&str> for Digest {
    fn from(s: &str) -> Digest {
        let words: Vec<u32> = (0..DIGEST_WORDS)
            .into_iter()
            .map(|x| u32::from_str_radix(&s[x * 8..(x + 1) * 8], 16).unwrap())
            .collect();
        Digest::new(words.try_into().unwrap())
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

/// An implementation that provides SHA-256 hashing services.
pub trait Sha: Clone + Debug {
    /// A pointer to the created digest.
    ///
    /// This may either be a Box<Digest> or some other pointer in case the
    /// implementation wants to manage its own memory.
    type DigestPtr: Deref<Target = Digest> + Debug;

    /// Generate a SHA from a slice of bytes, padding to block size
    /// and adding the SHA trailer.
    fn hash_bytes(&self, bytes: &[u8]) -> Self::DigestPtr;

    /// Generate a SHA from a slice of words, padding to block size
    /// and adding the SHA trailer.
    fn hash_words(&self, words: &[u32]) -> Self::DigestPtr {
        self.hash_bytes(bytemuck::cast_slice(words) as &[u8])
    }

    /// Generate a SHA from a slice of words without adding padding or
    /// length.
    fn hash_raw_words(&self, words: &[u32]) -> Self::DigestPtr;

    /// Generate a SHA from a pair of [Digests](Digest).
    fn hash_pair(&self, a: &Digest, b: &Digest) -> Self::DigestPtr {
        self.compress(&SHA256_INIT, a, b)
    }

    /// Execute the sha256 "compress" operation.  The block is
    /// specified as two half-blocks.  Not all implementations provide
    /// this.
    fn compress(
        &self,
        state: &Digest,
        block_half1: &Digest,
        block_half2: &Digest,
    ) -> Self::DigestPtr;

    /// Generate a SHA from a slice of anything that can be
    /// represented as plain old data.  Pads up to the Sha block
    /// boundry, but does not add the standard SHA trailer.
    fn hash_raw_pod_slice<T: bytemuck::Pod>(&self, slice: &[T]) -> Self::DigestPtr;

    /// Generate a new digest by mixing two digests together via XOR,
    /// and storing into the first digest.
    fn mix(&self, pool: &mut Self::DigestPtr, val: &Digest);
}

#[cfg(test)]
mod tests {
    use super::Digest;

    #[test]
    fn test_from_str() {
        assert_eq!(
            Digest::from_str("00000077000000AA0000001200000034000000560000007a000000a900000009"),
            Digest::new([119, 170, 18, 52, 86, 122, 169, 9])
        );
    }
}

#[allow(missing_docs)]
pub mod testutil {
    use alloc::vec::Vec;

    use super::{Digest, Sha};
    use crate::field::baby_bear::{BabyBearElem, BabyBearExtElem};

    // Runs conformance test on a SHA implementation to make sure it properly
    // behaves.
    pub fn test_sha_impl<S: Sha>(sha: &S) {
        test_hash_pair(sha);
        test_hash_raw_pod_slice(sha);
        test_sha_basics(sha);
        test_elems(sha);
        test_extelems(sha);

        crate::core::sha_rng::testutil::test_sha_rng_impl(sha);
    }

    fn test_sha_basics<S: Sha>(sha: &S) {
        // Standard test vectors
        assert_eq!(
            *sha.hash_bytes("abc".as_bytes()),
            Digest::new([
                0xba7816bf, 0x8f01cfea, 0x414140de, 0x5dae2223, 0xb00361a3, 0x96177a9c, 0xb410ff61,
                0xf20015ad
            ])
        );
        assert_eq!(
            *sha.hash_bytes("".as_bytes()),
            Digest::new([
                0xe3b0c442, 0x98fc1c14, 0x9afbf4c8, 0x996fb924, 0x27ae41e4, 0x649b934c, 0xa495991b,
                0x7852b855
            ])
        );
        assert_eq!(
            *sha.hash_bytes("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq".as_bytes()),
            Digest::new([
                0x248d6a61, 0xd20638b8, 0xe5c02693, 0x0c3e6039, 0xa33ce459, 0x64ff2167, 0xf6ecedd4,
                0x19db06c1
            ])
        );
        assert_eq!(*sha.hash_bytes(
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
            sha.hash_bytes(&"Byzantium".as_bytes()).to_hex(),
            "f75c763b4a52709ac294fc7bd7cf14dd45718c3d50b36f4732b05b8c6017492a"
        );
    }

    fn hash_elems<S: Sha>(sha: &S, len: usize) -> Digest {
        let items: Vec<BabyBearElem> = (0..len as u32)
            .into_iter()
            .map(|x| BabyBearElem::new(x))
            .collect();
        *sha.hash_raw_pod_slice(items.as_slice())
    }

    fn hash_extelems<S: Sha>(sha: &S, len: usize) -> Digest {
        let items: Vec<BabyBearExtElem> = (0..len as u32)
            .into_iter()
            .map(|x| {
                BabyBearExtElem::new(
                    BabyBearElem::new(x * 4),
                    BabyBearElem::new(x * 4 + 1),
                    BabyBearElem::new(x * 4 + 2),
                    BabyBearElem::new(x * 4 + 3),
                )
            })
            .collect();
        *sha.hash_raw_pod_slice(items.as_slice())
    }

    fn test_elems<S: Sha>(sha: &S) {
        const LENS: &[usize] = &[0, 1, 7, 8, 9];
        // It doesn't matter what elems hash to, as long as they're consistent.
        const EXPECTED_STRS: &[&str] = &[
            "6a09e667bb67ae853c6ef372a54ff53a510e527f9b05688c1f83d9ab5be0cd19",
            "da5698be17b9b46962335799779fbeca8ce5d491c0d26243bafef9ea1837a9d8",
            "643f71dab15c4f6a6e8820dee5f59cc07818b9c4473b47bba9516cc3be992f1c",
            "3dae53575097f63d0a461048813cc9ab870f0ddbcf9e4aea8dcddecc0aea736d",
            "903fe671a0971f6dea6e8a1180dcd1ce87b56d0b42ee3861212e86428a983a5b",
        ];

        let expected: Vec<Digest> = EXPECTED_STRS.iter().map(|x| Digest::from_str(x)).collect();
        let actual: Vec<Digest> = LENS.iter().map(|x| hash_elems(sha, *x)).collect();
        assert_eq!(expected, actual);
    }

    fn test_extelems<S: Sha>(sha: &S) {
        const LENS: &[usize] = &[0, 1, 7, 8, 9];
        // It doesn't matter what extelems hash to, as long as they're consistent.
        const EXPECTED_STRS: &[&str] = &[
            "6a09e667bb67ae853c6ef372a54ff53a510e527f9b05688c1f83d9ab5be0cd19",
            "6343c9ca9260f2d6cf190c2d2bbff0bf928789e4d2c1a24654137a5d48f254bc",
            "07d3bfa65009530790a51cca21b83dd492c60ade96ee1d2c5b25c4c5cfe257b0",
            "60a53ad42dfe03c7c0d1d46790a832356d09b52c6812eada27622476d6180392",
            "5af62d0303208f4573656ac707d7447f0303fd76a134a775f329104d03c37985",
        ];

        let expected: Vec<Digest> = EXPECTED_STRS.iter().map(|x| Digest::from_str(x)).collect();
        let actual: Vec<Digest> = LENS.iter().map(|x| hash_extelems(sha, *x)).collect();
        assert_eq!(expected, actual);
    }

    fn test_hash_raw_pod_slice<S: Sha>(sha: &S) {
        {
            let items: &[u32] = &[1];
            assert_eq!(
                *sha.hash_raw_pod_slice(items),
                Digest::from_str(
                    "e3050856aac389661ae490656ad0ea57df6aff0ff6eef306f8cc2eed4f240249"
                )
            );
        }
        {
            let items: &[u32] = &[1, 2];
            assert_eq!(
                *sha.hash_raw_pod_slice(items),
                Digest::from_str(
                    "4138ebae12299733cc677d1150c2a0139454662fc76ec95da75d2bf9efddc57a"
                )
            );
        }
        {
            let items: &[u32] = &[0xffffffff];
            assert_eq!(
                *sha.hash_raw_pod_slice(items),
                Digest::from_str(
                    "a3dba037d56175209dfd4191f727e91c5feb67e65a6ab5ed4daf0893c89598c8"
                )
            );
        }
    }

    fn test_hash_pair<S: Sha>(sha: &S) {
        assert_eq!(
            *sha.hash_pair(
                &Digest::from_str(
                    "6a09e667bb67ae853c6ef372a54ff53a510e527f9b05688c1f83d9ab5be0cd19"
                ),
                &Digest::from_str(
                    "ed375cadc653bb9078cee904acee6f7ff2bf7476c92dc92911bae27c41ebc015"
                )
            ),
            Digest::from_str("3aa2c47c47cd9e5c5259fd1c3428c30b9608201f5e163061deea8d2d7c65f2c3")
        );
    }
}
