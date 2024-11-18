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

use crate::ffi::{sys_bigint2_2, sys_bigint2_3};
#[cfg(not(feature = "num-bigint-dig"))]
use num_bigint::BigUint;
#[cfg(feature = "num-bigint-dig")]
use num_bigint_dig::BigUint;

const ADD_BLOB: &[u8] = include_bytes_aligned!(4, "add.blob");
const DOUBLE_BLOB: &[u8] = include_bytes_aligned!(4, "double.blob");

pub const EC_256_WIDTH_WORDS: usize = 256 / 32;

#[derive(Clone, Debug, Eq, PartialEq)]
pub struct AffinePoint {
    /// x coordinate
    pub x: BigUint,
    /// y coordinate
    pub y: BigUint,
}

impl AffinePoint {
    /// The point as concatenated u32s for x and y
    ///
    /// Little-endian, x coordinate before y coordinate
    #[cfg(not(feature = "num-bigint-dig"))]
    pub fn to_u32s(&self) -> [u32; 2 * EC_256_WIDTH_WORDS] {
        // TODO: This feels duplicative with `to_u32_digits` from RSA, but I don't see a way to share code without doubling the `copy_from_slice` calls
        let mut result = [0u32; 2 * EC_256_WIDTH_WORDS];
        let mut first = self.x.to_u32_digits();
        assert!(first.len() <= EC_256_WIDTH_WORDS);
        if first.len() < EC_256_WIDTH_WORDS {
            first.resize(EC_256_WIDTH_WORDS, 0);
        }
        let mut last = self.y.to_u32_digits();
        assert!(last.len() <= EC_256_WIDTH_WORDS);
        if last.len() < EC_256_WIDTH_WORDS {
            last.resize(EC_256_WIDTH_WORDS, 0);
        }
        result[..EC_256_WIDTH_WORDS].copy_from_slice(&first);
        result[EC_256_WIDTH_WORDS..].copy_from_slice(&last);
        result
    }

    /// The point as concatenated u32s for x and y
    ///
    /// Little-endian, x coordinate before y coordinate
    #[cfg(feature = "num-bigint-dig")]
    pub fn to_u32s(&self) -> [u32; 2 * EC_256_WIDTH_WORDS] {
        todo!();
    }

    pub fn from_u32s(data: &[u32; 2 * EC_256_WIDTH_WORDS]) -> AffinePoint {
        let mut iter = data.chunks(EC_256_WIDTH_WORDS);
        // We know the exact length of `data` so these unwraps are always successful
        let x = BigUint::from_slice(iter.next().unwrap());
        let y = BigUint::from_slice(iter.next().unwrap());
        AffinePoint { x, y }
    }
}

pub fn mul(scalar: &BigUint, point: &AffinePoint) -> AffinePoint {
    // This assumes `pt` is actually on the curve
    // This assumption isn't checked here, so other code must ensure it's met
    // This algorithm doesn't work if `scalar` is a multiple of `pt`'s order
    // TODO: Need a different algorithm in num-bigint-dig because no `bit`

    // `result` will always be overridden, but the compiler doesn't know that so initialize
    let mut result = AffinePoint {
        x: BigUint::ZERO,
        y: BigUint::ZERO,
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

pub fn double(point: &AffinePoint) -> AffinePoint {
    let mut result = [0u32; 2 * EC_256_WIDTH_WORDS];
    double_raw(&point.to_u32s(), &mut result);
    AffinePoint::from_u32s(&result)
}

fn double_raw(point: &[u32; 2 * EC_256_WIDTH_WORDS], result: &mut [u32; 2 * EC_256_WIDTH_WORDS]) {
    unsafe {
        sys_bigint2_2(DOUBLE_BLOB.as_ptr(), point.as_ptr(), result.as_mut_ptr());
    }
}

pub fn add(lhs: &AffinePoint, rhs: &AffinePoint) -> AffinePoint {
    // TODO: Do we want to check for P + P, P - P? It isn't necessary for soundness -- it will fail
    // an EQZ if you try -- but maybe a pretty error here would be good DevEx?
    let mut result = [0u32; 2 * EC_256_WIDTH_WORDS];
    add_raw(&lhs.to_u32s(), &rhs.to_u32s(), &mut result);
    AffinePoint::from_u32s(&result)
}

fn add_raw(
    lhs: &[u32; 2 * EC_256_WIDTH_WORDS],
    rhs: &[u32; 2 * EC_256_WIDTH_WORDS],
    result: &mut [u32; 2 * EC_256_WIDTH_WORDS],
) {
    unsafe {
        sys_bigint2_3(
            ADD_BLOB.as_ptr(),
            lhs.as_ptr(),
            rhs.as_ptr(),
            result.as_mut_ptr(),
        );
    }
}
