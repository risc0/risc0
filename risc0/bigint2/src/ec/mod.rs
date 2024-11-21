// Copyright 2024 RISC Zero, Inc.
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

#[cfg(test)]
mod tests;

use include_bytes_aligned::include_bytes_aligned;
use num_bigint::BigUint;
use std::rc::Rc;

use crate::ffi::{sys_bigint2_3, sys_bigint2_4};

const ADD_BLOB: &[u8] = include_bytes_aligned!(4, "add.blob");
const DOUBLE_BLOB: &[u8] = include_bytes_aligned!(4, "double.blob");

/// The secp256k1 curve's prime as u32 digits, least significant digit first
/// TODO: public?
pub const SECP256K1_PRIME: [u32; 8] = [
    0xFFFFFC2F, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
];

pub const EC_256_WIDTH_WORDS: usize = 256 / 32;

/// An elliptic curve over a prime field
///
/// The curve is given in short Weierstrass form y^2 = x^3 + ax + b. It supports a maximum `WIDTH` of its prime (and hence all coefficients and coordinates) given as number of 32-bit words (so the maximum bitwidth will be `32 * WIDTH`)
#[derive(Debug, Eq, PartialEq)]
pub struct WeierstrassCurve<const WIDTH: usize> {
    // buffer[0] is the prime, buffer[1] is a, buffer[2] is b
    buffer: [[u32; WIDTH]; 3],
}

impl<const WIDTH: usize> WeierstrassCurve<WIDTH> {
    // TODO this constructor is prone to misuse, ideal to have named fields
    pub fn new(prime: BigUint, a: BigUint, b: BigUint) -> WeierstrassCurve<WIDTH> {
        // TODO: This feels duplicative with `to_u32_digits` from RSA, but I don't see a way to share code without doubling the `copy_from_slice` calls
        let mut buffer = [[0u32; WIDTH]; 3];
        let first = prime.to_u32_digits();
        assert!(first.len() <= WIDTH);
        let middle = a.to_u32_digits();
        assert!(middle.len() <= WIDTH);
        let last = b.to_u32_digits();
        assert!(last.len() <= WIDTH);
        buffer[0][..first.len()].copy_from_slice(&first);
        buffer[1][..middle.len()].copy_from_slice(&middle);
        buffer[2][..last.len()].copy_from_slice(&last);
        WeierstrassCurve { buffer }
    }

    /// The curve as concatenated u32s
    ///
    /// Little-endian, prime then a then b
    pub fn as_u32s(&self) -> &[[u32; WIDTH]; 3] {
        &self.buffer
    }
    pub fn to_u32s(&self) -> &[[u32; WIDTH]; 3] {
        todo!();
    }
}

#[derive(Clone, Debug, Eq, PartialEq)]
pub struct AffinePoint<const WIDTH: usize> {
    buffer: [[u32; WIDTH]; 2],
    /// curve containing this point
    curve: Rc<WeierstrassCurve<WIDTH>>,
}

impl<const WIDTH: usize> AffinePoint<WIDTH> {
    pub fn new(x: BigUint, y: BigUint, curve: Rc<WeierstrassCurve<WIDTH>>) -> AffinePoint<WIDTH> {
        // TODO: This feels duplicative with `to_u32_digits` from RSA, but I don't see a way to share code without doubling the `copy_from_slice` calls
        let mut buffer = [[0u32; WIDTH]; 2];
        let first = x.to_u32_digits();
        assert!(first.len() <= WIDTH);
        let last = y.to_u32_digits();
        assert!(last.len() <= WIDTH);
        buffer[0][..first.len()].copy_from_slice(&first);
        buffer[1][..last.len()].copy_from_slice(&last);
        AffinePoint { buffer, curve }
    }
    /// The point as concatenated u32s for x and y
    ///
    /// Little-endian, x coordinate before y coordinate
    /// TODO: Where to doc this next bit
    /// The result is returned as a [[u32; WIDTH]; 2], and the FFI with the guest expects a [u32; WIDTH * 2]. Per https://doc.rust-lang.org/reference/type-layout.html#array-layout they will be laid out the same in memory and this is acceptable.
    pub fn as_u32s(&self) -> &[[u32; WIDTH]; 2] {
        &self.buffer
    }

    /// The point as concatenated u32s for x and y
    ///
    /// Little-endian, x coordinate before y coordinate
    #[cfg(feature = "num-bigint-dig")]
    pub fn to_u32s(&self) -> &[[u32; WIDTH]; 2] {
        todo!();
    }

    /// Read the point from concatenated u32s for x and y
    ///
    /// Input interpreted as little-endian with x coordinate before y coordinate
    pub fn from_u32s(
        data: [[u32; WIDTH]; 2],
        curve: Rc<WeierstrassCurve<WIDTH>>,
    ) -> AffinePoint<WIDTH> {
        AffinePoint {
            buffer: data,
            curve,
        }
    }
}

pub fn mul<const WIDTH: usize>(scalar: &BigUint, point: &AffinePoint<WIDTH>) -> AffinePoint<WIDTH> {
    // This assumes `pt` is actually on the curve
    // This assumption isn't checked here, so other code must ensure it's met
    // This algorithm doesn't work if `scalar` is a multiple of `pt`'s order
    // TODO: Need a different algorithm in num-bigint-dig because no `bit`

    // Initialize two values to alternate writes to avoid unnecessary copies.
    let mut result_flip = false;
    let mut result1 = AffinePoint::new(BigUint::ZERO, BigUint::ZERO, Rc::clone(&point.curve));
    let mut result2 = result1.clone();

    // Note: the first value can be an uninitialized value.
    let mut doubled_pt1 = point.clone();
    let mut doubled_pt2 = point.clone();

    let mut first_write = true;
    for pos in 0..scalar.bits() {
        // Alternate between the doubled value. Immutable reference is to the current value,
        // mutable reference is to the other that can be written to.
        // Note: This is not using a boolean flag because `pos%2` is less cycles.
        let (current_doubled, next_doubled) = if pos % 2 == 0 {
            (&doubled_pt2, &mut doubled_pt1)
        } else {
            (&doubled_pt1, &mut doubled_pt2)
        };

        if scalar.bit(pos) {
            // Alternate buffers to write to and use as current value.
            let (current_result, next_result) = if result_flip {
                (&result2, &mut result1)
            } else {
                (&result1, &mut result2)
            };

            if first_write {
                first_write = false;
                *next_result = current_doubled.clone();
            } else {
                add(current_result, current_doubled, next_result);
            }
            result_flip = !result_flip;
        }

        double(current_doubled, next_doubled);
    }

    // Assert that some value was written to the result.
    if first_write {
        panic!("Multiplication by zero forbidden as affine coordinates can't represent the point at infinity");
    }

    // Return the result, based on which buffer was written to last.
    if result_flip {
        result2
    } else {
        result1
    }
}

pub fn double<const WIDTH: usize>(point: &AffinePoint<WIDTH>, result: &mut AffinePoint<WIDTH>) {
    double_raw(point.as_u32s(), point.curve.as_u32s(), &mut result.buffer);
}

fn double_raw<const WIDTH: usize>(
    point: &[[u32; WIDTH]; 2],
    curve: &[[u32; WIDTH]; 3],
    result: &mut [[u32; WIDTH]; 2],
) {
    unsafe {
        // Because [[u32; WIDTH]; 2] and [u32; WIDTH * 2] are laid out the same way, this `as` is safe
        // (and similarly with [[u32; WIDTH]; 3] and [u32; WIDTH * 3])
        // See https://doc.rust-lang.org/reference/type-layout.html#array-layout
        sys_bigint2_3(
            DOUBLE_BLOB.as_ptr(),
            point.as_ptr() as *const u32,
            curve.as_ptr() as *const u32,
            result.as_mut_ptr() as *mut u32,
        );
    }
}

pub fn add<const WIDTH: usize>(
    lhs: &AffinePoint<WIDTH>,
    rhs: &AffinePoint<WIDTH>,
    result: &mut AffinePoint<WIDTH>,
) {
    // TODO: Do we want to check for P + P, P - P? It isn't necessary for soundness -- it will fail
    // an EQZ if you try -- but maybe a pretty error here would be good DevEx?
    assert_eq!(lhs.curve, rhs.curve);
    add_raw(
        lhs.as_u32s(),
        rhs.as_u32s(),
        lhs.curve.as_u32s(),
        &mut result.buffer,
    );
}

fn add_raw<const WIDTH: usize>(
    lhs: &[[u32; WIDTH]; 2],
    rhs: &[[u32; WIDTH]; 2],
    curve: &[[u32; WIDTH]; 3],
    result: &mut [[u32; WIDTH]; 2],
) {
    unsafe {
        // Because [[u32; WIDTH]; 2] and [u32; WIDTH * 2] are laid out the same way, this `as` is safe
        // (and similarly with [[u32; WIDTH]; 3] and [u32; WIDTH * 3])
        // See https://doc.rust-lang.org/reference/type-layout.html#array-layout
        sys_bigint2_4(
            ADD_BLOB.as_ptr(),
            lhs.as_ptr() as *const u32,
            rhs.as_ptr() as *const u32,
            curve.as_ptr() as *const u32,
            result.as_mut_ptr() as *mut u32,
        );
    }
}
