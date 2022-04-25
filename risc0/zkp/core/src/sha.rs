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

use core::fmt::{Debug, Display, Formatter};
use std::slice;

use arrayref::array_ref;
use generic_array::GenericArray;
use sha2::{compress256, Digest as ShaDigest, Sha256};
use typenum::U64;

use crate::{fp::Fp, fp4::Fp4};

pub const DIGEST_WORDS: usize = 8;

#[derive(Clone, Copy, Default, Eq, Hash, Ord, PartialOrd, PartialEq)]
pub struct Digest(pub [u32; DIGEST_WORDS]);

static INIT_256: [u32; DIGEST_WORDS] = [
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19,
];

fn set_word(buf: &mut [u8], idx: usize, word: u32) {
    buf[(4 * idx)..(4 * idx + 4)].copy_from_slice(&word.to_be_bytes());
}

impl Digest {
    pub fn from_u32s(words: &[u32]) -> Self {
        Digest(words.try_into().expect("slice with incorrect length"))
    }

    // Digests a byte array in the bog-standard SHA-256 fashion, but returns
    // the resulting value as our digest type (8 words) rather than 32 bytes.
    pub fn hash_bytes(bytes: &[u8]) -> Self {
        let mut hasher = Sha256::new();
        hasher.update(bytes);
        let raw_ret = hasher.finalize();
        let mut ret = [0 as u32; DIGEST_WORDS];
        for i in 0..DIGEST_WORDS {
            ret[i] = u32::from_be_bytes(*array_ref![raw_ret, i * 4, 4]);
        }
        Digest(ret)
    }

    // Digest FPs a word at a time, without padding (and using le encoding)
    pub fn hash_fps(fps: &[Fp]) -> Self {
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
        Digest(state)
    }

    pub fn hash_fp4s(fp4s: &[Fp4]) -> Self {
        let mut flat: Vec<Fp> = vec![];
        for i in 0..fp4s.len() {
            for j in 0..4 {
                flat.push(fp4s[i].elems()[j]);
            }
        }
        return Self::hash_fps(&flat);
    }

    // Digest two digest into one
    pub fn hash_pair(a: &Digest, b: &Digest) -> Self {
        let mut state = INIT_256;
        let mut block: GenericArray<u8, U64> = GenericArray::default();
        for i in 0..8 {
            set_word(block.as_mut_slice(), i, a.0[i]);
            set_word(block.as_mut_slice(), 8 + i, b.0[i]);
        }
        compress256(&mut state, slice::from_ref(&block));
        Digest(state)
    }
}

impl Digest {
    /// Constructs a new `Digest` from a byte array.
    pub fn new(data: [u32; DIGEST_WORDS]) -> Self {
        Self(data)
    }

    pub fn as_slice(&self) -> &[u32] {
        &self.0
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
