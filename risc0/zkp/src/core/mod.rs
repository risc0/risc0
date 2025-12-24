// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! Core module used to implement a zk-STARK prover and verifier.

#![deny(missing_docs)]

extern crate alloc;

pub mod digest;
pub mod hash;
pub mod ntt;
pub mod poly;

use rand_core::RngCore;

/// Compute `floor(log_2(x))`.
///
/// Returns the position of the highest set bit (0-indexed).
/// Equivalent to finding the largest `po2` such that `(1 << po2) <= x`.
/// # Example
/// ```rust
/// # use risc0_zkp::core::to_po2;
/// #
/// assert_eq!(to_po2(7), 2);  // floor(log2(7)) = 2
/// assert_eq!(to_po2(10), 3); // floor(log2(10)) = 3
/// ```
pub fn to_po2(x: usize) -> usize {
    (31 - (x as u32).leading_zeros()) as usize
}

/// Compute `ceil(log_2(value))`
///
/// Find the smallest `result` such that, for the provided value,
/// `2^result >= value`.
/// # Example
/// ```rust
/// # use risc0_zkp::core::log2_ceil;
/// #
/// assert_eq!(log2_ceil(8), 3); // 2^3 = 8
/// assert_eq!(log2_ceil(32), 5); // 2^5 = 32
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
    fn random<R: RngCore>(rng: &mut R) -> Self;
}

impl Random for u32 {
    /// Return a random u32 value.
    fn random<R: RngCore>(rng: &mut R) -> Self {
        rng.next_u32()
    }
}
