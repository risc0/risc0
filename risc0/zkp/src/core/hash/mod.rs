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

//! Traits to configure which cryptographic primitives the ZKP uses

pub mod blake2b;
pub mod poseidon;
#[cfg(feature = "prove")]
pub mod poseidon_254;
pub mod sha;

use alloc::{boxed::Box, rc::Rc, string::String};

use risc0_core::field::Field;

use super::digest::Digest;

/// A trait that sets the hashes and encodings used by the ZKP.
pub trait HashFn<F: Field>: Send + Sync {
    /// Generate a hash from a pair of [Digest].
    fn hash_pair(&self, a: &Digest, b: &Digest) -> Box<Digest>;

    /// Generate a hash from a slice of field elements.  This may be unpadded so
    /// this is only safe to used when the size is known.
    fn hash_elem_slice(&self, slice: &[F::Elem]) -> Box<Digest>;

    /// Generate a hash from a slice of extension field element.  This may be
    /// unpadded so this is only safe to used when the size is known.
    fn hash_ext_elem_slice(&self, slice: &[F::ExtElem]) -> Box<Digest>;
}

/// A trait that sets the PRNG used by Fiat-Shamir.  We allow specialization at
/// this level rather than at RngCore because some hashes such as Posidon have
/// elements distributed uniformly over the field natively.
pub trait Rng<F: Field> {
    /// Mix in randomness from a Fiat-Shamir commitment.
    fn mix(&mut self, val: &Digest);

    /// Get a cryptographically uniform set of bits, as the low order bits of a
    /// u32
    fn random_bits(&mut self, bits: usize) -> u32;

    /// Get a cryptographically uniform field element
    fn random_elem(&mut self) -> F::Elem;

    /// Get a cryptographically uniform extension field element
    fn random_ext_elem(&mut self) -> F::ExtElem;
}

/// Responsible for constructing new Rngs.
pub trait RngFactory<F: Field> {
    /// Construct a new Rng
    fn new_rng(&self) -> Box<dyn Rng<F>>;
}

/// Make it easy compute both hash related traits from a single source
pub struct HashSuite<F: Field> {
    /// The name of this HashSuite.
    pub name: String,

    /// Define the hash used by the HashSuite
    pub hashfn: Rc<dyn HashFn<F>>,

    /// Define an RNG factory
    pub rng: Rc<dyn RngFactory<F>>,
}

impl<F: Field> Clone for HashSuite<F> {
    fn clone(&self) -> Self {
        Self {
            name: self.name.clone(),
            hashfn: self.hashfn.clone(),
            rng: self.rng.clone(),
        }
    }
}
