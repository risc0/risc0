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

#![deny(missing_docs)]
//! Core objects used by the zk-STARK prover
//! and verifier.
#![doc = include_str!("README.md")]

extern crate alloc;

use rand::Rng;

/// This transitional "fp" module will remain until ZKP has been genericized to
/// work with multiple fields. This module includes the field extension whose
/// base field is of order 15*2^27 + 1.
///
/// # Example
pub mod fp {
    pub use crate::field::baby_bear::Elem as Fp;
}
/// This transitional "fp4" module will remain until ZKP has been genericized to
/// work with multiple fields. This module includes the base field of order
/// 15*2^27 + 1).
pub mod fp4 {
    pub use crate::field::baby_bear::ExtElem as Fp4;
    use crate::field::ExtElem;

    /// This transitional re-export will remain until ZKP has been genericized
    /// to work with multiple fields.
    pub const EXT_SIZE: usize = Fp4::EXT_SIZE;
}
pub mod ntt;
pub mod poly;
pub mod rou;
pub mod sha;
pub mod sha_cpu;
pub mod sha_rng;

/// For x = (1 << po2), given x, find po2.
/// # Example
/// ```
/// # use risc0_zkp::core::to_po2;
/// #
/// assert_eq!(to_po2(7), 2);
/// assert_eq!(to_po2(10), 3);
/// ```
pub fn to_po2(x: usize) -> usize {
    (31 - (x as u32).leading_zeros()) as usize
}

/// Compute `ceil(log_2(value))`
///
/// Find the smallest `result` such that, for the provided value,
/// `2^result >= value`.
/// # Example
/// ```
/// # use risc0_zkp::core::log2_ceil;
/// #
/// assert_eq!(log2_ceil())
/// ```
#[inline]
pub const fn log2_ceil(value: usize) -> usize {
    let mut result = 0;
    while (1 << result) < value {
        result += 1;
    }
    result
}

/// Generic trait for generating random values.
pub trait Random {
    /// Generate a uniform random value.
    fn random<R: Rng>(rng: &mut R) -> Self;
}

impl Random for u32 {
    /// Return a random u32 value.
    fn random<R: Rng>(rng: &mut R) -> Self {
        rng.next_u32()
    }
}
