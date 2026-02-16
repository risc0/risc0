// Copyright 2026 RISC Zero, Inc.
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

//! Baby Bear field arithmetic for cubecl GPU kernels.
//!
//! All values are stored in Montgomery form. The prime modulus is
//! P = 15 * 2^27 + 1 = 2013265921.

use cubecl::prelude::*;

/// The Baby Bear prime: P = 15 * 2^27 + 1
pub const P: u32 = 0x78000001;

/// Montgomery constant: M = -P^{-1} mod 2^32
///
/// Note: The CUDA implementation (mont32_t) uses M0 = 0x77ffffff which is
/// P^{-1} mod 2^32 (not negated), but the Rust CPU implementation uses
/// M = 0x88000001 which is -P^{-1} mod 2^32. We match the Rust CPU code.
pub const M: u32 = 0x88000001;

/// Modular addition in Montgomery form.
///
/// Computes (a + b) mod P where a, b are in Montgomery form.
#[cube]
pub fn bb_add(a: u32, b: u32) -> u32 {
    let x = a + b;
    let corr = x - P;
    // If x >= P, use corrected value. Since P < 2^31, x < 2^32,
    // and (x - P) won't underflow to a value >= P when x >= P.
    // When x < P, the subtraction wraps to a large value > P.
    if corr < P { corr } else { x }
}

/// Modular subtraction in Montgomery form.
///
/// Computes (a - b) mod P where a, b are in Montgomery form.
#[cube]
pub fn bb_sub(a: u32, b: u32) -> u32 {
    let x = a - b;
    // If a >= b, x is the correct result (and x < P since both inputs < P).
    // If a < b, x wraps around and we need to add P back.
    // Wrapped value will be > P since it's a large u32.
    if x > P { x + P } else { x }
}

/// Montgomery multiplication.
///
/// Computes (a * b * R^{-1}) mod P where R = 2^32, using the REDC algorithm.
/// This matches the Rust CPU implementation in baby_bear.rs.
#[cube]
pub fn bb_mul(a: u32, b: u32) -> u32 {
    // Widening multiply: o64 = a * b
    let o64: u64 = (a as u64) * (b as u64);
    // low = -o64 mod 2^32 (i.e., negate the low 32 bits)
    let low: u32 = 0u32 - (o64 as u32);
    // red = M * low mod 2^32
    let red: u32 = M * low;
    // o64 += red * P (this makes the low 32 bits zero)
    let o64 = o64 + (red as u64) * (P as u64);
    // Result is the high 32 bits
    let ret: u32 = (o64 >> 32) as u32;
    // Final reduction
    if ret >= P { ret - P } else { ret }
}
