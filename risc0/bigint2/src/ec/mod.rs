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

use crate::ffi::{sys_bigint2_2, sys_bigint2_3};

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
    pub prime: BigUint,
    pub a: BigUint,
    pub b: BigUint,
}

#[derive(Clone, Debug, Eq, PartialEq)]
pub struct AffinePoint<const WIDTH: usize> {
    /// x coordinate
    pub x: BigUint,
    /// y coordinate
    pub y: BigUint,
    /// curve containing this point
    pub curve: Rc<WeierstrassCurve<WIDTH>>,
}

impl<const WIDTH: usize> AffinePoint<WIDTH> {
    /// The point as concatenated u32s for x and y
    ///
    /// Little-endian, x coordinate before y coordinate
    /// TODO: Where to doc this next bit
    /// The result is returned as a [[u32; WIDTH]; 2], and the FFI with the guest expects a [u32; WIDTH * 2]. Per https://doc.rust-lang.org/reference/type-layout.html#array-layout they will be laid out the same in memory and this is acceptable.
    #[cfg(not(feature = "num-bigint-dig"))]
    pub fn to_u32s(&self) -> [[u32; WIDTH]; 2] {
        // TODO: This feels duplicative with `to_u32_digits` from RSA, but I don't see a way to share code without doubling the `copy_from_slice` calls
        let mut result = [[0u32; WIDTH]; 2];
        let first = self.x.to_u32_digits();
        assert!(first.len() <= WIDTH);
        let last = self.y.to_u32_digits();
        assert!(last.len() <= WIDTH);
        result[0][..first.len()].copy_from_slice(&first);
        result[1][..first.len()].copy_from_slice(&last);
        result
    }

    /// The point as concatenated u32s for x and y
    ///
    /// Little-endian, x coordinate before y coordinate
    #[cfg(feature = "num-bigint-dig")]
    pub fn to_u32s(&self) -> [[u32; WIDTH]; 2] {
        todo!();
    }

    /// Read the point from concatenated u32s for x and y
    ///
    /// Input interpreted as little-endian with x coordinate before y coordinate
    pub fn from_u32s(data: &[[u32; WIDTH]; 2], curve: Rc<WeierstrassCurve<WIDTH>>) -> AffinePoint<WIDTH> {
        AffinePoint { 
            x: BigUint::from_slice(&data[0]),
            y: BigUint::from_slice(&data[1]),
            curve,
        }
    }
}

pub fn mul<const WIDTH: usize>(scalar: &BigUint, point: &AffinePoint<WIDTH>) -> AffinePoint<WIDTH> {
    // This assumes `pt` is actually on the curve
    // This assumption isn't checked here, so other code must ensure it's met
    // This algorithm doesn't work if `scalar` is a multiple of `pt`'s order
    // TODO: Need a different algorithm in num-bigint-dig because no `bit`

    // `result` will always be overridden, but the compiler doesn't know that so initialize
    let mut result = AffinePoint {
        x: BigUint::ZERO,
        y: BigUint::ZERO,
        curve: Rc::clone(&point.curve),
    };
    let mut first_write = true;
    let mut doubled_pt = point.clone();
    for pos in 0..scalar.bits() {
        if scalar.bit(pos) {
            if first_write {
                result = doubled_pt.clone();
                first_write = false;
            } else {
                result = add(&result, &doubled_pt);
            }
        }
        doubled_pt = double(&doubled_pt);
    }
    if first_write {
        panic!("Multiplication by zero forbidden as affine coordinates can't represent the point at infinity");
    }
    result
}

pub fn double<const WIDTH: usize>(point: &AffinePoint<WIDTH>) -> AffinePoint<WIDTH> {
    let mut result = [[0u32; WIDTH]; 2];
    double_raw(&point.to_u32s(), &mut result);
    AffinePoint::from_u32s(&result,Rc::clone(&point.curve))
}

fn double_raw<const WIDTH: usize>(point: &[[u32; WIDTH]; 2], result: &mut [[u32; WIDTH]; 2]) {
    unsafe {
        // Because [[u32; WIDTH]; 2] and [u32; WIDTH * 2] are laid out the same way, this `as` is safe
        // See https://doc.rust-lang.org/reference/type-layout.html#array-layout
        sys_bigint2_2(DOUBLE_BLOB.as_ptr(), point.as_ptr() as *const u32, result.as_mut_ptr() as *mut u32);
    }
}

pub fn add<const WIDTH: usize>(lhs: &AffinePoint<WIDTH>, rhs: &AffinePoint<WIDTH>) -> AffinePoint<WIDTH> {
    // TODO: Do we want to check for P + P, P - P? It isn't necessary for soundness -- it will fail
    // an EQZ if you try -- but maybe a pretty error here would be good DevEx?
    assert_eq!(lhs.curve, rhs.curve);
    let mut result = [[0u32; WIDTH]; 2];
    add_raw(&lhs.to_u32s(), &rhs.to_u32s(), &mut result);
    AffinePoint::from_u32s(&result, Rc::clone(&lhs.curve))
}

fn add_raw<const WIDTH: usize>(
    lhs: &[[u32; WIDTH]; 2],
    rhs: &[[u32; WIDTH]; 2],
    result: &mut [[u32; WIDTH]; 2],
) {
    unsafe {
        // Because [[u32; WIDTH]; 2] and [u32; WIDTH * 2] are laid out the same way, this `as` is safe
        // See https://doc.rust-lang.org/reference/type-layout.html#array-layout
        sys_bigint2_3(
            ADD_BLOB.as_ptr(),
            lhs.as_ptr() as *const u32,
            rhs.as_ptr() as *const u32,
            result.as_mut_ptr() as *mut u32,
        );
    }
}
