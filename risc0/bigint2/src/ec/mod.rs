// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

mod secp256k1;
mod secp384r1;
#[cfg(test)]
mod tests;

use include_bytes_aligned::include_bytes_aligned;

use crate::ffi::{sys_bigint2_3, sys_bigint2_4};

pub use secp256k1::Secp256k1Curve;
pub use secp384r1::Secp384r1Curve;

pub const EC_256_WIDTH_WORDS: usize = 256 / 32;
pub const EC_384_WIDTH_WORDS: usize = 384 / 32;

const ADD_256_BLOB: &[u8] = include_bytes_aligned!(4, "ec_add_256.blob");
const DOUBLE_256_BLOB: &[u8] = include_bytes_aligned!(4, "ec_double_256.blob");
const ADD_384_BLOB: &[u8] = include_bytes_aligned!(4, "ec_add_384.blob");
const DOUBLE_384_BLOB: &[u8] = include_bytes_aligned!(4, "ec_double_384.blob");

/// Generic static curve configuration.
pub trait Curve<const WIDTH: usize> {
    const CURVE: &'static WeierstrassCurve<WIDTH>;
}

/// An elliptic curve over a prime field
///
/// The curve is given in short Weierstrass form y^2 = x^3 + ax + b. It supports a maximum `WIDTH`
/// of its prime (and hence all coefficients and coordinates) given as number of 32-bit words (so
/// the maximum bitwidth will be `32 * WIDTH`)
#[derive(Debug, Eq, PartialEq)]
pub struct WeierstrassCurve<const WIDTH: usize> {
    // buffer[0] is the prime, buffer[1] is a, buffer[2] is b
    buffer: [[u32; WIDTH]; 3],
}

impl<const WIDTH: usize> WeierstrassCurve<WIDTH> {
    // TODO this constructor is prone to misuse, ideal to have named fields
    pub const fn new(
        prime: [u32; WIDTH],
        a: [u32; WIDTH],
        b: [u32; WIDTH],
    ) -> WeierstrassCurve<WIDTH> {
        WeierstrassCurve {
            buffer: [prime, a, b],
        }
    }

    /// The curve as concatenated u32s
    ///
    /// Little-endian, prime then a then b
    pub(crate) fn as_u32s(&self) -> &[[u32; WIDTH]; 3] {
        &self.buffer
    }
}

/// An affine point on an elliptic curve.
#[derive(Debug, Eq, PartialEq)]
pub struct AffinePoint<const WIDTH: usize, C> {
    buffer: [[u32; WIDTH]; 2],
    identity: bool,
    _marker: std::marker::PhantomData<C>,
}

// Manual clone and copy implementations to not require C to be Copy/Clone
impl<const WIDTH: usize, C> Clone for AffinePoint<WIDTH, C> {
    fn clone(&self) -> Self {
        *self
    }
}
impl<const WIDTH: usize, C> Copy for AffinePoint<WIDTH, C> {}

impl<const WIDTH: usize, C> AffinePoint<WIDTH, C> {
    pub const IDENTITY: AffinePoint<WIDTH, C> = AffinePoint {
        buffer: [[0u32; WIDTH]; 2],
        identity: true,
        _marker: std::marker::PhantomData,
    };

    /// Constructs an affine point from x and y coordinates, without checking that it is on
    /// a specific curve.
    pub fn new_unchecked(x: [u32; WIDTH], y: [u32; WIDTH]) -> AffinePoint<WIDTH, C> {
        AffinePoint {
            buffer: [x, y],
            identity: false,
            _marker: std::marker::PhantomData,
        }
    }
    /// The point as concatenated u32s for x and y. This function returns `None` if the point is at
    /// zero/infinity and `Some` with the coordinates otherwise.
    ///
    /// Little-endian, x coordinate before y coordinate
    /// The result is returned as a [[u32; WIDTH]; 2], and the FFI with the guest expects a
    /// [u32; WIDTH * 2]. Per the [rust array layout] they will be laid out the same in memory and
    /// this is acceptable.
    ///
    /// [rust array layout]: https://doc.rust-lang.org/reference/type-layout.html#array-layout
    pub fn as_u32s(&self) -> Option<&[[u32; WIDTH]; 2]> {
        if self.identity {
            None
        } else {
            Some(&self.buffer)
        }
    }

    /// Returns true if the point is the identity element (point at zero/infinity).
    pub fn is_identity(&self) -> bool {
        self.identity
    }
}

impl<const WIDTH: usize, C: Curve<WIDTH>> AffinePoint<WIDTH, C> {
    /// Elliptic curve multiplication of the point by a scalar.
    pub fn mul(&self, scalar: &[u32; WIDTH], result: &mut AffinePoint<WIDTH, C>) {
        // This assumes `pt` is actually on the curve
        // This assumption isn't checked here, so other code must ensure it's met
        // This algorithm doesn't work if `scalar` is a multiple of `pt`'s order

        // Initialize two values to alternate writes to avoid unnecessary copies.
        let mut result_buffer1 = AffinePoint::IDENTITY;
        let mut result_buffer2 = AffinePoint::IDENTITY;

        let mut result_ptr = &mut result_buffer1;
        let mut result_scratch = &mut result_buffer2;

        // Note: the first value can be an uninitialized value.
        let mut doubled_pt_buffer1 = *self;
        let mut doubled_pt_buffer2 = *self;

        let mut doubled_point = &mut doubled_pt_buffer1;
        let mut doubled_point_scratch = &mut doubled_pt_buffer2;

        let mut first_write = true;
        for pos in 0..bits(scalar) {
            if bit(scalar, pos) {
                if first_write {
                    first_write = false;
                    *result_ptr = *doubled_point;
                } else {
                    result_ptr.add_internal(doubled_point, result_scratch);
                    // Swap references to result buffers to update the result.
                    core::mem::swap(&mut result_ptr, &mut result_scratch);
                }
            }

            doubled_point.double_internal(doubled_point_scratch);
            // Swap references to doubled point buffers to update the current doubled value.
            core::mem::swap(&mut doubled_point, &mut doubled_point_scratch);
        }

        if first_write {
            // Multiplied by zero, which is the identity point.
            *result = AffinePoint::IDENTITY;
        } else {
            // Copy the value from the buffer most recently written to.
            *result = *result_ptr;
        }

        // Check that the final result is less than the curve's prime.
        let prime = C::CURVE.buffer[0];
        assert!(crate::is_less(&result_ptr.buffer[0], &prime));
        assert!(crate::is_less(&result_ptr.buffer[1], &prime));
    }

    /// Elliptic curve doubling of the affine point.
    pub fn double(&self, result: &mut Self) {
        self.double_internal(result);

        // An honest host will always return a result less than the curve's prime in each coordinate.
        // A dishonest prover can sometimes return a result greater than the prime, so enforce that
        // we're in the honest case.
        let prime = C::CURVE.buffer[0];
        assert!(crate::is_less(&result.buffer[0], &prime));
        assert!(crate::is_less(&result.buffer[1], &prime));
    }

    /// [double] without checking the result is less than the curve's prime.
    #[inline]
    fn double_internal(&self, result: &mut Self) {
        let curve = C::CURVE;
        // If the point is zero, can short-circuit and return the identity point.
        if let Some(point) = self.as_u32s() {
            if self.buffer[1] != [0u32; WIDTH] {
                double_raw(point, curve.as_u32s(), &mut result.buffer);
                // DO NOT REMOVE: the result is unchecked, and only the buffer is updated above
                result.identity = false;
            } else {
                // DO NOT REMOVE: in this case a zero has been computed and the buffer is ignored
                result.identity = true;
            }
        } else {
            *result = *self;
        }
    }

    /// Elliptic curve addition of the affine point.
    pub fn add(&self, rhs: &AffinePoint<WIDTH, C>, result: &mut AffinePoint<WIDTH, C>) {
        self.add_internal(rhs, result);

        // An honest host will always return a result less than the curve's prime in each coordinate.
        // A dishonest prover can sometimes return a result greater than the prime, so enforce that
        // we're in the honest case.
        let prime = C::CURVE.buffer[0];
        assert!(crate::is_less(&result.buffer[0], &prime));
        assert!(crate::is_less(&result.buffer[1], &prime));
    }

    #[inline]
    fn add_internal(&self, rhs: &AffinePoint<WIDTH, C>, result: &mut AffinePoint<WIDTH, C>) {
        let curve = C::CURVE;

        // If the left or right value is zero, can return the other value.
        let Some(lhs) = self.as_u32s() else {
            *result = *rhs;
            return;
        };
        let Some(rhs) = rhs.as_u32s() else {
            *result = *self;
            return;
        };

        if lhs[0] == rhs[0] {
            // X coordinates are the same, so either we double the value if it's the same point,
            // or return the identity if it's different (and so lhs = -rhs).
            if self.buffer[1] != rhs[1] {
                // x == x, y == -y, so the result is the identity point
                result.identity = true;
            } else {
                // P + P, which can be done with a double call.
                double_raw(lhs, curve.as_u32s(), &mut result.buffer);
                // DO NOT REMOVE: the result is unchecked, and only the buffer is updated above
                result.identity = false;
            }
        } else {
            // X coordinates are different, so we can add the points as normal.
            add_raw(lhs, rhs, curve.as_u32s(), &mut result.buffer);
            // DO NOT REMOVE: the result is unchecked, and only the buffer is updated above
            result.identity = false;
        }
    }
}

/// Doubles a point on the curve.
///
/// Note: this function assumes that identity point cases are handled before calling, otherwise
/// this function will panic in the host.
fn double_raw<const WIDTH: usize>(
    point: &[[u32; WIDTH]; 2],
    curve: &[[u32; WIDTH]; 3],
    result: &mut [[u32; WIDTH]; 2],
) {
    // Because [[u32; WIDTH]; 2] and [u32; WIDTH * 2] are laid out the same way, this `as` is safe
    // (and similarly with [[u32; WIDTH]; 3] and [u32; WIDTH * 3])
    // See https://doc.rust-lang.org/reference/type-layout.html#array-layout
    if WIDTH <= EC_256_WIDTH_WORDS {
        unsafe {
            sys_bigint2_3(
                DOUBLE_256_BLOB.as_ptr(),
                point.as_ptr() as *const u32,
                curve.as_ptr() as *const u32,
                result.as_mut_ptr() as *mut u32,
            );
        }
    } else if WIDTH <= EC_384_WIDTH_WORDS {
        unsafe {
            sys_bigint2_3(
                DOUBLE_384_BLOB.as_ptr(),
                point.as_ptr() as *const u32,
                curve.as_ptr() as *const u32,
                result.as_mut_ptr() as *mut u32,
            );
        }
    } else {
        unimplemented!(
            "Bitwidths above 384 bits not currently supported for elliptic curve precompiles"
        );
    }
}

/// Adds two points on the curve.
///
/// Note: this function assumes that identity point cases are handled before calling, otherwise
/// this function will panic in the host.
fn add_raw<const WIDTH: usize>(
    lhs: &[[u32; WIDTH]; 2],
    rhs: &[[u32; WIDTH]; 2],
    curve: &[[u32; WIDTH]; 3],
    result: &mut [[u32; WIDTH]; 2],
) {
    // Because [[u32; WIDTH]; 2] and [u32; WIDTH * 2] are laid out the same way, this `as` is safe
    // (and similarly with [[u32; WIDTH]; 3] and [u32; WIDTH * 3])
    // See https://doc.rust-lang.org/reference/type-layout.html#array-layout
    if WIDTH <= EC_256_WIDTH_WORDS {
        unsafe {
            sys_bigint2_4(
                ADD_256_BLOB.as_ptr(),
                lhs.as_ptr() as *const u32,
                rhs.as_ptr() as *const u32,
                curve.as_ptr() as *const u32,
                result.as_mut_ptr() as *mut u32,
            );
        }
    } else if WIDTH <= EC_384_WIDTH_WORDS {
        unsafe {
            sys_bigint2_4(
                ADD_384_BLOB.as_ptr(),
                lhs.as_ptr() as *const u32,
                rhs.as_ptr() as *const u32,
                curve.as_ptr() as *const u32,
                result.as_mut_ptr() as *mut u32,
            );
        }
    } else {
        unimplemented!(
            "Bitwidths above 384 bits not currently supported for elliptic curve precompiles"
        );
    }
}

/// Checks if the bit at the position is set.
fn bit<const WIDTH: usize>(scalar: &[u32; WIDTH], bit: u32) -> bool {
    let bits_per_digit = 32u32;
    if let Ok(digit_index) = usize::try_from(bit / bits_per_digit)
        && let Some(digit) = scalar.get(digit_index)
    {
        let bit_mask = (1u32) << (bit % bits_per_digit);
        return (digit & bit_mask) != 0;
    }
    false
}

/// Returns the minimum number of bits required to represent the scalar
fn bits<const WIDTH: usize>(scalar: &[u32; WIDTH]) -> u32 {
    // Find the highest set bit by scanning from most significant word
    for (i, &word) in scalar.iter().rev().enumerate() {
        if word != 0 {
            // Found highest non-zero word
            // Calculate total bits based on zero words and leading zeros of non-zero word
            return (WIDTH - 1 - i) as u32 * 32 + (32 - word.leading_zeros());
        }
    }
    0
}

#[cfg(test)]
mod bit_tests {
    use super::*;

    #[test]
    fn bit_test() {
        let test = [0b00001001, 0b11110010];
        assert_eq!(bits(&test), 40);
        assert!(bit(&test, 0));
        assert!(!bit(&test, 1));
        assert!(!bit(&test, 2));
        assert!(bit(&test, 3));
        assert!(bit(&test, 33));
        assert!(bit(&test, 36));
        assert!(!bit(&test, 35));
    }
}
