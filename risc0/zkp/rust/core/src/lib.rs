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

#![no_std]
// #![deny(missing_docs)]
#![doc = include_str!("../README.md")]

extern crate alloc;

use rand::Rng;

pub mod fp;
pub mod fp4;
pub mod ntt;
pub mod poly;
pub mod rou;
pub mod sha;
pub mod sha_cpu;
pub mod sha_rng;

/// For x = (1 << po2), given x, find po2.
pub fn to_po2(x: usize) -> usize {
    (31 - (x as u32).leading_zeros()) as usize
}

/// Compute `ceil(log_2(value))`
///
/// Find the smallest value `result` such that `2^result >= value`.
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
    fn random<R: Rng>(rng: &mut R) -> Self {
        rng.next_u32()
    }
}
