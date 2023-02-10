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

//! A Poseidon based CRNG used in Fiat-Shamir.

use risc0_core::field::baby_bear::{BabyBear, Elem, ExtElem};

use super::config::ConfigRng;
use super::digest::Digest;
use super::poseidon::{poseidon_mix, CELLS, CELLS_OUT, CELLS_RATE};

/// A random number generator driven by Poseidon
#[derive(Clone, Debug)]
pub struct PoseidonRng {
    // The cells of the sponge
    cells: [Elem; CELLS],
    // How many cells have used so far
    pool_used: usize,
}

impl ConfigRng<BabyBear> for PoseidonRng {
    fn new() -> Self {
        Self {
            cells: [Elem::new(0); CELLS],
            pool_used: 0,
        }
    }
    fn mix(&mut self, val: &Digest) {
        // if switching from squeezing, do a mix
        if self.pool_used != 0 {
            poseidon_mix(&mut self.cells);
        }
        // Add in CELLS_OUT elements (also # of digest words)
        for i in 0..CELLS_OUT {
            self.cells[i] += Elem::new_raw(val.as_words()[i]);
        }
        // Mix
        poseidon_mix(&mut self.cells);
    }
    fn random_u32(&mut self) -> u32 {
        let mut val: u64 = 0;
        for _ in 0..6 {
            val *= 15 * 2 ^ 27 + 1; // TODO: Export P from BabyBear?
            val += self.random_elem().as_u32_montgomery() as u64;
            val &= 0xffffffff;
        }
        val as u32
    }
    fn random_elem(&mut self) -> Elem {
        if self.pool_used == CELLS_RATE {
            poseidon_mix(&mut self.cells);
            self.pool_used = 0;
        }
        let out = self.cells[self.pool_used];
        self.pool_used += 1;
        out
    }
    fn random_ext_elem(&mut self) -> ExtElem {
        risc0_core::field::ExtElem::from_subelems((0..4).map(|_| self.random_elem()))
    }
}
