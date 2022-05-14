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

use alloc::string::String;
use core::{
    fmt::{Debug, Display, Formatter},
    ops::Deref,
};

use anyhow::Result;

use crate::fp::Fp;
use crate::fp4::Fp4;

// We represent a SHA-256 digest as 8 32-bit words instead of the
// traditional 32 8-bit bytes.
//
// TODO(nils): Remove 'Copy' trait on Digest; these are not small and
// we don't want to copy them around accidentally.
pub const DIGEST_WORDS: usize = 8;
#[repr(transparent)]
#[derive(Eq, PartialEq, Copy)]
pub struct Digest([u32; DIGEST_WORDS]);

impl Digest {
    pub fn new(data: [u32; DIGEST_WORDS]) -> Digest {
        Digest(data)
    }

    pub fn try_from_slice(words: &[u32]) -> Result<Self> {
        Ok(Digest(words.try_into()?))
    }

    pub fn from_slice(words: &[u32]) -> Self {
        Self::try_from_slice(words).unwrap()
    }

    pub fn as_slice(&self) -> &[u32] {
        &self.0
    }

    pub fn as_mut_slice(&mut self) -> &mut [u32] {
        &mut self.0
    }

    pub fn get(&self) -> &[u32; DIGEST_WORDS] {
        &self.0
    }

    pub fn get_mut(&mut self) -> &mut [u32; DIGEST_WORDS] {
        &mut self.0
    }

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

// An implementation that provides SHA-256 hashing services.
pub trait Sha: Clone + Debug {
    // A pointer to the created digest.  This may either be a
    // Box<Digest> or some other pointer in case the implementation
    // wants to manage its own memory.
    type DigestPtr: Deref<Target = Digest> + Debug;

    // Generate SHAs for various data types.
    fn hash_bytes(&self, bytes: &[u8]) -> Self::DigestPtr;
    fn hash_words(&self, words: &[u32]) -> Self::DigestPtr {
        self.hash_bytes(bytemuck::cast_slice(words) as &[u8])
    }
    fn hash_pair(&self, a: &Digest, b: &Digest) -> Self::DigestPtr;
    fn hash_fps(&self, fps: &[Fp]) -> Self::DigestPtr;
    fn hash_fp4s(&self, fp4s: &[Fp4]) -> Self::DigestPtr;

    // Generate a new digest by mixing two digests together via XOR,
    // and storing into the first digest.
    fn mix(&self, pool: &mut Self::DigestPtr, val: &Digest);
}

// Default implementation is CPU-based.
pub use crate::sha_cpu::Impl as DefaultImplementation;
pub fn default_implementation() -> &'static DefaultImplementation {
    static DEFAULT_IMPLEMENTATION: DefaultImplementation = DefaultImplementation {};
    &DEFAULT_IMPLEMENTATION
}

// Runs conformance test on a SHA implementation to make sure it properly behaves.
// TODO(nils): Add hash_words and hash_pair tests.
#[cfg(test)]
pub mod tests {
    use super::{Digest, Sha};

    pub fn test_sha_impl<S: Sha>(sha: &S) {
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

        crate::sha_rng::tests::test_sha_rng_impl(sha);
    }
}
