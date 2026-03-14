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

//! Baby Bear extension field (F_p^4) arithmetic for cubecl GPU kernels.
//!
//! Extension field elements are represented as 4 u32 values in Montgomery form,
//! using the irreducible polynomial x^4 - 11.

use cubecl::prelude::*;

use crate::hal::cubecl::field::{bb_add, bb_mul, bb_sub};

/// NBETA = encode(P - 11) in Montgomery form.
///
/// The extension field F_p^4 uses irreducible polynomial x^4 - 11.
/// Multiplication reduces powers >= 4 by multiplying by -BETA = -(P-11) = NBETA.
/// NBETA = P - 11 in the base field, encoded in Montgomery form.
pub const NBETA: u32 = 0x40000018;

/// Extension field addition: (a0 + a1*x + a2*x^2 + a3*x^3) + (b0 + b1*x + b2*x^2 + b3*x^3)
///
/// Component-wise addition in the base field.
#[cube]
pub fn bb4_add(
    r0: &mut u32,
    r1: &mut u32,
    r2: &mut u32,
    r3: &mut u32,
    b0: u32,
    b1: u32,
    b2: u32,
    b3: u32,
) {
    *r0 = bb_add(*r0, b0);
    *r1 = bb_add(*r1, b1);
    *r2 = bb_add(*r2, b2);
    *r3 = bb_add(*r3, b3);
}

/// Extension field subtraction: (a0..a3) - (b0..b3)
///
/// Component-wise subtraction in the base field.
#[cube]
pub fn bb4_sub(
    r0: &mut u32,
    r1: &mut u32,
    r2: &mut u32,
    r3: &mut u32,
    b0: u32,
    b1: u32,
    b2: u32,
    b3: u32,
) {
    *r0 = bb_sub(*r0, b0);
    *r1 = bb_sub(*r1, b1);
    *r2 = bb_sub(*r2, b2);
    *r3 = bb_sub(*r3, b3);
}

/// Extension field multiplication: (a0..a3) * (b0..b3) mod (x^4 - 11)
///
/// From fpext.h: multiply out polynomial representations, reduce mod x^4 - 11.
/// Uses NBETA = -(P-11) mod P for the reduction of high-degree terms.
#[cube]
pub fn bb4_mul(
    r0: &mut u32,
    r1: &mut u32,
    r2: &mut u32,
    r3: &mut u32,
    b0: u32,
    b1: u32,
    b2: u32,
    b3: u32,
) {
    let a0 = *r0;
    let a1 = *r1;
    let a2 = *r2;
    let a3 = *r3;
    // Compute all results into locals before writing back.
    // cubecl treats `let a0 = *r0` as an alias, so writing *r0
    // would corrupt a0 for subsequent uses. All writes must be deferred.
    // o0 = a0*b0 + NBETA*(a1*b3 + a2*b2 + a3*b1)
    let nb0 = bb_add(bb_add(bb_mul(a1, b3), bb_mul(a2, b2)), bb_mul(a3, b1));
    let o0 = bb_add(bb_mul(a0, b0), bb_mul(NBETA, nb0));
    // o1 = a0*b1 + a1*b0 + NBETA*(a2*b3 + a3*b2)
    let nb1 = bb_add(bb_mul(a2, b3), bb_mul(a3, b2));
    let o1 = bb_add(bb_add(bb_mul(a0, b1), bb_mul(a1, b0)), bb_mul(NBETA, nb1));
    // o2 = a0*b2 + a1*b1 + a2*b0 + NBETA*(a3*b3)
    let o2 = bb_add(
        bb_add(bb_add(bb_mul(a0, b2), bb_mul(a1, b1)), bb_mul(a2, b0)),
        bb_mul(NBETA, bb_mul(a3, b3)),
    );
    // o3 = a0*b3 + a1*b2 + a2*b1 + a3*b0
    let o3 = bb_add(
        bb_add(bb_mul(a0, b3), bb_mul(a1, b2)),
        bb_add(bb_mul(a2, b1), bb_mul(a3, b0)),
    );
    // Write all results at once
    *r0 = o0;
    *r1 = o1;
    *r2 = o2;
    *r3 = o3;
}

/// Multiply extension field element by a base field scalar: (a0..a3) * s
///
/// Each component is independently multiplied by the scalar.
#[cube]
pub fn bb4_mul_scalar(r0: &mut u32, r1: &mut u32, r2: &mut u32, r3: &mut u32, s: u32) {
    *r0 = bb_mul(*r0, s);
    *r1 = bb_mul(*r1, s);
    *r2 = bb_mul(*r2, s);
    *r3 = bb_mul(*r3, s);
}

/// Raise base field element to a power (repeated squaring).
///
/// Computes base^exp mod P in Montgomery form.
#[cube]
pub fn bb_pow(base: u32, exp: u32) -> u32 {
    // Montgomery form of 1 = R mod P = 2^32 mod 0x78000001 = 0x0ffffffe
    let mut tot: u32 = 0x0ffffffeu32;
    let mut cur: u32 = base;
    let mut n: u32 = exp;
    // Repeated squaring
    while n != 0u32 {
        if n & 1u32 != 0u32 {
            tot = bb_mul(tot, cur);
        }
        n = n >> 1u32;
        cur = bb_mul(cur, cur);
    }
    tot
}

/// Raise extension field element to a power (repeated squaring).
///
/// Computes (r0..r3)^exp in the extension field.
#[cube]
pub fn bb4_pow(r0: &mut u32, r1: &mut u32, r2: &mut u32, r3: &mut u32, exp: u32) {
    let mut c0: u32 = *r0;
    let mut c1: u32 = *r1;
    let mut c2: u32 = *r2;
    let mut c3: u32 = *r3;
    // Start with identity (1, 0, 0, 0) in Montgomery form
    *r0 = 0x0ffffffeu32;
    *r1 = 0u32;
    *r2 = 0u32;
    *r3 = 0u32;
    let mut n: u32 = exp;
    while n != 0u32 {
        if n & 1u32 != 0u32 {
            bb4_mul(r0, r1, r2, r3, c0, c1, c2, c3);
        }
        n = n >> 1u32;
        // Square cur
        let t0 = c0;
        let t1 = c1;
        let t2 = c2;
        let t3 = c3;
        bb4_mul(&mut c0, &mut c1, &mut c2, &mut c3, t0, t1, t2, t3);
    }
}
