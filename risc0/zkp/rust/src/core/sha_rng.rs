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

//! A SHA-256 based CRNG used in Fiat-Shamir
use alloc::borrow::Cow;
use rand::{Error, RngCore};
use rand_core::impls;

use super::sha::{digest_mix, hash_bytes, hash_pair, Digest, DIGEST_WORDS};

/// A random number generator driven by a [Sha].
#[derive(Clone, Debug)]
pub struct ShaRng<'a> {
    pool0: Cow<'a, Digest>,
    pool1: Cow<'a, Digest>,
    pool_used: usize,
}

impl<'a> ShaRng<'a> {
    /// Create a new [ShaRng].
    pub fn new() -> ShaRng<'a> {
        ShaRng {
            pool0: hash_bytes(b"Hello"),
            pool1: hash_bytes(b"World"),
            pool_used: 0,
        }
    }

    /// Mix the pool with a specified [Digest].
    pub fn mix(&mut self, val: &Digest) {
        digest_mix(self.pool0.to_mut(), val);
        self.step();
    }

    fn step(&mut self) {
        self.pool0 = hash_pair(&self.pool0, &self.pool1);
        self.pool1 = hash_pair(&self.pool0, &self.pool1);
        self.pool_used = 0;
    }
}

impl<'a> RngCore for ShaRng<'a> {
    fn next_u32(&mut self) -> u32 {
        if self.pool_used == DIGEST_WORDS {
            self.step();
        }
        let out = self.pool0.get()[self.pool_used];
        // Mark this word as used.
        self.pool_used += 1;
        out
    }

    fn next_u64(&mut self) -> u64 {
        ((self.next_u32() as u64) << 32) | (self.next_u32() as u64)
    }

    fn fill_bytes(&mut self, dest: &mut [u8]) {
        impls::fill_bytes_via_next(self, dest);
    }

    fn try_fill_bytes(&mut self, dest: &mut [u8]) -> Result<(), Error> {
        Ok(self.fill_bytes(dest))
    }
}

#[allow(missing_docs)]
pub mod testutil {
    use super::ShaRng;
    use rand::RngCore;

    // Runs conformance test on a SHA implementation to make sure it
    // properly behaves for generating pseudo-random numbers.  This is
    //  purposefully not behind #[cfg(test)] so that it can be run in
    //  a zkvm guest.
    pub fn test_sha_rng_impl() {
        let mut x = ShaRng::new();
        for _ in 0..10 {
            x.next_u32();
        }
        assert_eq!(x.next_u32(), 1826198275);
        x.mix(&crate::core::sha::hash_bytes(b"foo"));
        assert_eq!(x.next_u32(), 1753965479);
    }
}
