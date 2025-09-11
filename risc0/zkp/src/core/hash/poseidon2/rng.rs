// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! A Poseidon2 based CRNG used in Fiat-Shamir.

use risc0_core::field::{
    ExtElem,
    baby_bear::{BabyBear, BabyBearExtElem, Elem},
};

use super::{CELLS_OUT, CELLS_RATE, consts::CELLS, poseidon2_mix};
use crate::core::{digest::Digest, hash::Rng};

/// A random number generator driven by Poseidon2
#[derive(Clone, Debug)]
pub struct Poseidon2Rng {
    // The cells of the sponge
    cells: [Elem; CELLS],
    // How many cells have used so far
    pool_used: usize,
}

impl Default for Poseidon2Rng {
    fn default() -> Self {
        Self::new()
    }
}

impl Poseidon2Rng {
    /// Construct a new Poseidon2Rng
    pub fn new() -> Self {
        Self {
            cells: [Elem::new(0); CELLS],
            pool_used: 0,
        }
    }
}

impl Rng<BabyBear> for Poseidon2Rng {
    fn mix(&mut self, val: &Digest) {
        // if switching from squeezing, do a mix
        if self.pool_used != 0 {
            poseidon2_mix(&mut self.cells);
            self.pool_used = 0;
        }
        // Add in CELLS_OUT elements (also # of digest words)
        for i in 0..CELLS_OUT {
            self.cells[i] += Elem::new_raw(val.as_words()[i]);
        }
        // Mix
        poseidon2_mix(&mut self.cells);
    }

    fn random_bits(&mut self, bits: usize) -> u32 {
        let mut val = self.random_elem().as_u32();
        for _ in 0..3 {
            let new_val = self.random_elem().as_u32();
            if val == 0 {
                val = new_val;
            }
        }
        ((1 << bits) - 1) & val
    }

    fn random_elem(&mut self) -> Elem {
        if self.pool_used == CELLS_RATE {
            poseidon2_mix(&mut self.cells);
            self.pool_used = 0;
        }
        let out = self.cells[self.pool_used];
        self.pool_used += 1;
        out
    }

    fn random_ext_elem(&mut self) -> BabyBearExtElem {
        ExtElem::from_subelems((0..4).map(|_| self.random_elem()))
    }
}
