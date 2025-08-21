// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! A SHA-256 based CRNG used in Fiat-Shamir.

use alloc::boxed::Box;

use rand_core::{RngCore, impls};
use risc0_core::field::{Elem, Field};

use super::{DIGEST_WORDS, Digest, Impl, Sha256};
use crate::core::hash::Rng;

/// A random number generator driven by a [Sha256].
#[derive(Clone, Debug)]
pub struct ShaRng {
    // Pool 0 receives new entropy and is where values are drawn from.
    pool0: Box<Digest>,
    // Pool 1 provides secret state in the step function. It is never observable.
    pool1: Box<Digest>,
    pool_used: usize,
}

impl Default for ShaRng {
    fn default() -> Self {
        Self::new()
    }
}

impl ShaRng {
    /// Create a new [ShaRng] from a given [Sha256].
    pub fn new() -> Self {
        Self {
            pool0: (*Impl::hash_bytes(b"Hello")).into(),
            pool1: (*Impl::hash_bytes(b"World")).into(),
            pool_used: 0,
        }
    }

    /// Mix the pool with a specified [Digest].
    pub fn inner_mix(&mut self, val: &Digest) {
        for i in 0..DIGEST_WORDS {
            self.pool0.as_mut_words()[i] = self.pool0.as_words()[i] ^ val.as_words()[i];
        }
        self.step();
    }

    fn step(&mut self) {
        self.pool0 = (*Impl::hash_pair(&self.pool0, &self.pool1)).into();
        self.pool1 = (*Impl::hash_pair(&self.pool0, &self.pool1)).into();
        self.pool_used = 0;
    }
}

impl RngCore for ShaRng {
    fn next_u32(&mut self) -> u32 {
        if self.pool_used == DIGEST_WORDS {
            self.step();
        }
        let out = self.pool0.as_words()[self.pool_used];
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
}

impl<F: Field> Rng<F> for ShaRng {
    fn mix(&mut self, val: &Digest) {
        self.inner_mix(val);
    }

    fn random_bits(&mut self, bits: usize) -> u32 {
        ((1 << bits) - 1) & self.next_u32()
    }

    fn random_elem(&mut self) -> F::Elem {
        F::Elem::random(self)
    }

    fn random_ext_elem(&mut self) -> F::ExtElem {
        F::ExtElem::random(self)
    }
}

#[cfg(test)]
mod tests {
    use rand_core::RngCore;

    use super::ShaRng;
    use crate::core::hash::sha::{Sha256, cpu::Impl};

    // Runs conformance test on a SHA implementation to make sure it
    // properly behaves for generating pseudo-random numbers.
    #[test]
    fn test_sha_rng_impl() {
        let mut x = ShaRng::new();
        for _ in 0..10 {
            x.next_u32();
        }
        assert_eq!(x.next_u32(), 785921476);
        x.inner_mix(&Impl::hash_bytes(b"foo"));
        assert_eq!(x.next_u32(), 4167871101);
    }
}
