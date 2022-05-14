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

use alloc::{boxed::Box, vec, vec::Vec};
use core::slice;

use sha2::digest::generic_array::{typenum::U64, GenericArray};
use sha2::{compress256, Digest as ShaDigest, Sha256};

use crate::{
    fp::Fp,
    fp4::Fp4,
    sha::{Digest, Sha, DIGEST_WORDS},
};

static INIT_256: [u32; DIGEST_WORDS] = [
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19,
];

#[derive(Clone)]
pub struct Impl {}

fn set_word(buf: &mut [u8], idx: usize, word: u32) {
    buf[(4 * idx)..(4 * idx + 4)].copy_from_slice(&word.to_le_bytes());
}

impl Sha for Impl {
    type DigestPtr = Box<Digest>;

    fn hash_bytes(&self, bytes: &[u8]) -> Self::DigestPtr {
        let mut hasher = Sha256::new();
        hasher.update(bytes);
        Box::new(Digest::new(
            hasher
                .finalize()
                .as_slice()
                .chunks(4)
                .map(|chunk| u32::from_be_bytes(chunk.try_into().unwrap()))
                .collect::<Vec<u32>>()
                .try_into()
                .unwrap(),
        ))
    }

    fn hash_words(&self, words: &[u32]) -> Self::DigestPtr {
        self.hash_bytes(bytemuck::cast_slice(words) as &[u8])
    }

    fn hash_fps(&self, fps: &[Fp]) -> Self::DigestPtr {
        let mut state = INIT_256;
        let mut block: GenericArray<u8, U64> = GenericArray::default();
        let mut off = 0;
        for i in 0..fps.len() {
            set_word(block.as_mut_slice(), off, u32::from(fps[i]));
            off += 1;
            if off == 16 {
                compress256(&mut state, slice::from_ref(&block));
                off = 0;
            }
        }
        if off != 0 {
            block[off * 4..].fill(0);
            compress256(&mut state, slice::from_ref(&block));
        }
        Box::new(Digest::new(state))
    }

    fn hash_fp4s(&self, fp4s: &[Fp4]) -> Self::DigestPtr {
        let mut flat: Vec<Fp> = vec![];
        for i in 0..fp4s.len() {
            for j in 0..4 {
                flat.push(fp4s[i].elems()[j]);
            }
        }
        return self.hash_fps(&flat);
    }

    // Digest two digest into one
    fn hash_pair(&self, a: &Digest, b: &Digest) -> Self::DigestPtr {
        let mut state = INIT_256;
        let mut block: GenericArray<u8, U64> = GenericArray::default();
        for i in 0..8 {
            set_word(block.as_mut_slice(), i, a.as_slice()[i]);
            set_word(block.as_mut_slice(), 8 + i, b.as_slice()[i]);
        }
        compress256(&mut state, slice::from_ref(&block));
        Box::new(Digest::new(state))
    }

    // Generate a new digest by mixing two digests together via XOR,
    // and stores it back in the pool.
    fn mix(&self, pool: &mut Self::DigestPtr, val: &Digest) {
        // CPU based sha can do this in place without generating another digest pointer.
        for (pool_word, val_word) in pool.get_mut().iter_mut().zip(val.get()) {
            *pool_word ^= *val_word;
        }
    }
}

impl core::fmt::Debug for Impl {
    fn fmt(&self, f: &mut core::fmt::Formatter) -> core::fmt::Result {
        core::write!(f, "CPU SHA256 implementation")
    }
}

#[cfg(test)]
mod tests {
    use super::Impl;

    #[test]
    fn test_impl() {
        crate::sha::tests::test_sha_impl(&Impl {})
    }
}
