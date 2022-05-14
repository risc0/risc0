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

use crate::sha::Digest;

#[derive(Clone, Debug)]
pub struct ShaRng {
    pool0: Digest,
    pool1: Digest,
    pool_used: usize,
}

impl ShaRng {
    pub fn mix(&mut self, val: &Digest) {
        for i in 0..8 {
            self.pool0.0[i] ^= val.0[i];
        }
        self.step();
    }

    fn step(&mut self) {
        self.pool0 = Digest::hash_pair(&self.pool0, &self.pool1);
        self.pool1 = Digest::hash_pair(&self.pool0, &self.pool1);
        self.pool_used = 0;
    }
}

impl Default for ShaRng {
    fn default() -> Self {
        ShaRng {
            pool0: Digest::hash_bytes(b"Hello"),
            pool1: Digest::hash_bytes(b"World"),
            pool_used: 0,
        }
    }
}

impl RngCore for ShaRng {
    fn next_u32(&mut self) -> u32 {
        if self.pool_used == 8 {
            self.step();
        }
        let out = self.pool0.0[self.pool_used];
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
mod tests {
    use super::Digest;
    use super::ShaRng;
    use rand::RngCore;

    #[test]
    fn match_cpp() {
        let mut x = ShaRng::default();
        for _ in 0..10 {
            x.next_u32();
        }
        assert_eq!(x.next_u32(), 1826198275);
        x.mix(&Digest::hash_bytes(b"foo"));
        assert_eq!(x.next_u32(), 1753965479);
    }
}
