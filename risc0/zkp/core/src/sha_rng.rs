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

use rand::{Error, RngCore};
use rand_core::impls;

use crate::sha::{Digest, Sha, DIGEST_WORDS};

#[derive(Clone, Debug)]
pub struct ShaRng<S: Sha> {
    sha: S,
    pool0: S::DigestPtr,
    pool1: S::DigestPtr,
    pool_used: usize,
}

impl<S: Sha> ShaRng<S> {
    pub fn new(sha: &S) -> ShaRng<S> {
        ShaRng {
            sha: sha.clone(),
            pool0: sha.hash_bytes(b"Hello"),
            pool1: sha.hash_bytes(b"World"),
            pool_used: 0,
        }
    }

    pub fn mix(&mut self, val: &Digest) {
        self.sha.mix(&mut self.pool0, val);
        self.step();
    }

    fn step(&mut self) {
        self.pool0 = self.sha.hash_pair(&self.pool0, &self.pool1);
        self.pool1 = self.sha.hash_pair(&self.pool0, &self.pool1);
        self.pool_used = 0;
    }
}

impl<S: Sha> RngCore for ShaRng<S> {
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

#[cfg(test)]
pub mod tests {
    use super::ShaRng;
    use crate::sha::Sha;
    use rand::RngCore;

    // Runs conformance test on a SHA implementation to make sure it
    // properly behaves for generating pseudo-random numbers.
    pub fn test_sha_rng_impl<S: Sha>(sha: &S) {
        let mut x = ShaRng::new(sha);
        for _ in 0..10 {
            x.next_u32();
        }
        assert_eq!(x.next_u32(), 1826198275);
        x.mix(&*sha.hash_bytes(b"foo"));
        assert_eq!(x.next_u32(), 1753965479);
    }
}
