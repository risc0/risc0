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

use core::{fmt::Debug, ops::DerefMut};

use risc0_core::field::Field;

use super::digest::Digest;

/// A trait that sets the hashes and encodings used by the ZKP.
pub trait HashFn<F: Field> {
    /// A pointer to the digest created as the result of a hashing operation.
    ///
    /// This may either be a `Box<Digest>` or some other pointer in case the
    /// implementation wants to manage its own memory. Semantically, holding the
    /// `DigestPtr` denotes ownership of the underlying value. (e.g. `DigestPtr`
    /// does not implement `Copy` and the owner of `DigestPtr` can create a
    /// mutable reference to the underlying digest).
    type DigestPtr: DerefMut<Target = Digest> + Debug;

    /// Generate a hash from a pair of [Digest].
    fn hash_pair(a: &Digest, b: &Digest) -> Self::DigestPtr;

    /// Generate a hash from a slice of field elements.  This may be unpadded so
    /// this is only safe to used when the size is known.
    fn hash_elem_slice(slice: &[F::Elem]) -> Self::DigestPtr;

    /// Generate a hash from a slice of extension field element.  This may be
    /// unpadded so this is only safe to used when the size is known.
    fn hash_ext_elem_slice(slice: &[F::ExtElem]) -> Self::DigestPtr;
}

/// A trait that sets the PRNG used by Fiat-Shamir.  We allow specialization at
/// this level rather than at RngCore because some hashes such as Posidon have
/// elements distributed uniformly over the field natively.
pub trait Rng<F: Field> {
    /// Create a new RNG is a standard state, mix before using!
    fn new() -> Self;

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

/// Make it easy compute both hash related traits from a single source
pub trait HashSuite<F: Field> {
    /// Define the hash used by the HashSuite
    type HashFn: HashFn<F>;

    /// Define the random mixer used by the HashSuite
    type Rng: Rng<F>;
}
