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

/// Montgomery constant: M0 = -P^{-1} mod 2^32 (standard REDC convention)
///
/// This is the standard REDC reduction constant. sppark calls this M0.
/// Verified: P * M0 ≡ -1 (mod 2^32), i.e., 0x78000001 * 0x77ffffff = 0xFFFFFFFF (mod 2^32).
pub const M0: u32 = 0x77ffffff;

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

/// Montgomery multiplication using mul_hi (u32-only arithmetic).
///
/// Computes (a * b * R^{-1}) mod P where R = 2^32, using REDC with
/// only 32-bit operations + mul_hi intrinsic (__umulhi on CUDA).
///
/// Standard REDC: product = a*b, red = lo(product) * M0 mod 2^32,
/// result = hi(product + red*P). Since lo(product + red*P) = 0 by
/// construction, carry = (product_lo != 0) ? 1 : 0.
#[cube]
pub fn bb_mul(a: u32, b: u32) -> u32 {
    let product_lo: u32 = a * b;
    let product_hi: u32 = a.mul_hi(b);
    let red: u32 = product_lo * M0;
    let q_hi: u32 = red.mul_hi(P);
    // Carry from REDC: lo(red*P) + product_lo = 0 mod 2^32,
    // so carry = 1 iff product_lo != 0
    let mut ret: u32 = product_hi + q_hi;
    if product_lo != 0u32 {
        ret = ret + 1u32;
    }
    // Final conditional reduction
    if ret >= P { ret - P } else { ret }
}
