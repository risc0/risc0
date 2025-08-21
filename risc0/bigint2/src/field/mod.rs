// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! Accelerated finite field arithmetic operations
//!
//! Provides acceleration for certain finite field arithmetic operations. The operations in the root
//! of this module include verification that the result is less than the modulus (for prime fields),
//! or that the result's coefficients are less than the characteristic (for extension fields). In
//! cases where it is known that these restrictions aren't necessary for security, there are
//! versions that omit this check in the [unchecked] submodule.

#[cfg(test)]
mod tests;

mod ffi;
pub mod unchecked;

use crate::WORD_SIZE;

pub const FIELD_256_WIDTH_WORDS: usize = 256 / (WORD_SIZE * 8);
pub const FIELD_384_WIDTH_WORDS: usize = 384 / (WORD_SIZE * 8);
pub const FIELD_4096_WIDTH_WORDS: usize = 4096 / (WORD_SIZE * 8);
pub const EXT_DEGREE_2: usize = 2;
pub const EXT_DEGREE_4: usize = 4;

pub fn modadd_256(
    lhs: &[u32; FIELD_256_WIDTH_WORDS],
    rhs: &[u32; FIELD_256_WIDTH_WORDS],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    unchecked::modadd_256(lhs, rhs, modulus, result);

    // An honest host will always return a result less than the modulus. A dishonest prover can
    // sometimes return a result greater than the modulus, so enforce that we're in the honest case.
    assert!(crate::is_less(result, modulus));
}

pub fn modadd_384(
    lhs: &[u32; FIELD_384_WIDTH_WORDS],
    rhs: &[u32; FIELD_384_WIDTH_WORDS],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [u32; FIELD_384_WIDTH_WORDS],
) {
    unchecked::modadd_384(lhs, rhs, modulus, result);

    // An honest host will always return a result less than the modulus. A dishonest prover can
    // sometimes return a result greater than the modulus, so enforce that we're in the honest case.
    assert!(crate::is_less(result, modulus));
}

/// Compute the multiplicative inverse of `inp` mod `modulus`
///
/// The result is returned in `result`. Note that this can only compute the inverse if a
/// multiplicative inverse actually exists. Otherwise, no proof can be generated (and the executor
/// will panic).
///
/// Most notably, this means `inp` cannot be zero ("no division by zero"), but the full rule is that
/// `inp` and `modulus` must be relatively prime. When `modulus` is prime, this just means that
/// `inp` must not be a multiple of `modulus`, but when `modulus` is composite there are more cases
/// with no solution, e.g. `8` does not have an inverse mod `12`.
pub fn modinv_256(
    inp: &[u32; FIELD_256_WIDTH_WORDS],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    unchecked::modinv_256(inp, modulus, result);

    // An honest host will always return a result less than the modulus. A dishonest prover can
    // sometimes return a result greater than the modulus, so enforce that we're in the honest case.
    assert!(crate::is_less(result, modulus));
}

pub fn modinv_384(
    inp: &[u32; FIELD_384_WIDTH_WORDS],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [u32; FIELD_384_WIDTH_WORDS],
) {
    unchecked::modinv_384(inp, modulus, result);

    // An honest host will always return a result less than the modulus. A dishonest prover can
    // sometimes return a result greater than the modulus, so enforce that we're in the honest case.
    assert!(crate::is_less(result, modulus));
}

pub fn modmul_256(
    lhs: &[u32; FIELD_256_WIDTH_WORDS],
    rhs: &[u32; FIELD_256_WIDTH_WORDS],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    unchecked::modmul_256(lhs, rhs, modulus, result);

    // An honest host will always return a result less than the modulus. A dishonest prover can
    // sometimes return a result greater than the modulus, so enforce that we're in the honest case.
    assert!(crate::is_less(result, modulus));
}

pub fn modmul_384(
    lhs: &[u32; FIELD_384_WIDTH_WORDS],
    rhs: &[u32; FIELD_384_WIDTH_WORDS],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [u32; FIELD_384_WIDTH_WORDS],
) {
    unchecked::modmul_384(lhs, rhs, modulus, result);

    // An honest host will always return a result less than the modulus. A dishonest prover can
    // sometimes return a result greater than the modulus, so enforce that we're in the honest case.
    assert!(crate::is_less(result, modulus));
}

pub fn modmul_4096(
    lhs: &[u32; FIELD_4096_WIDTH_WORDS],
    rhs: &[u32; FIELD_4096_WIDTH_WORDS],
    modulus: &[u32; FIELD_4096_WIDTH_WORDS],
    result: &mut [u32; FIELD_4096_WIDTH_WORDS],
) {
    unchecked::modmul_4096(lhs, rhs, modulus, result);

    // An honest host will always return a result less than the modulus. A dishonest prover can
    // sometimes return a result greater than the modulus, so enforce that we're in the honest case.
    assert!(crate::is_less(result, modulus));
}

pub fn modsub_256(
    lhs: &[u32; FIELD_256_WIDTH_WORDS],
    rhs: &[u32; FIELD_256_WIDTH_WORDS],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    unchecked::modsub_256(lhs, rhs, modulus, result);

    // An honest host will always return a result less than the modulus. A dishonest prover can
    // sometimes return a result greater than the modulus, so enforce that we're in the honest case.
    assert!(crate::is_less(result, modulus));
}

pub fn modsub_384(
    lhs: &[u32; FIELD_384_WIDTH_WORDS],
    rhs: &[u32; FIELD_384_WIDTH_WORDS],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [u32; FIELD_384_WIDTH_WORDS],
) {
    unchecked::modsub_384(lhs, rhs, modulus, result);

    // An honest host will always return a result less than the modulus. A dishonest prover can
    // sometimes return a result greater than the modulus, so enforce that we're in the honest case.
    assert!(crate::is_less(result, modulus));
}

pub fn extfield_deg2_add_256(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unchecked::extfield_deg2_add_256(lhs, rhs, modulus, result);

    // An honest host will always return a result less than the modulus. A dishonest prover can
    // sometimes return a result greater than the modulus, so enforce that we're in the honest case.
    assert!(crate::is_less(&result[0], modulus));
    assert!(crate::is_less(&result[1], modulus));
}

pub fn extfield_deg2_add_384(
    lhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unchecked::extfield_deg2_add_384(lhs, rhs, modulus, result);

    // An honest host will always return a result less than the modulus. A dishonest prover can
    // sometimes return a result greater than the modulus, so enforce that we're in the honest case.
    assert!(crate::is_less(&result[0], modulus));
    assert!(crate::is_less(&result[1], modulus));
}

pub fn extfield_deg2_mul_256(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    monic_irr: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unchecked::extfield_deg2_mul_256(lhs, rhs, monic_irr, modulus, result);

    // An honest host will always return a result less than the modulus. A dishonest prover can
    // sometimes return a result greater than the modulus, so enforce that we're in the honest case.
    assert!(crate::is_less(&result[0], modulus));
    assert!(crate::is_less(&result[1], modulus));
}

pub fn extfield_deg4_mul_256(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_4],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_4],
    monic_irr: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_4],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_4],
) {
    unchecked::extfield_deg4_mul_256(lhs, rhs, monic_irr, modulus, result);

    // An honest host will always return a result less than the modulus. A dishonest prover can
    // sometimes return a result greater than the modulus, so enforce that we're in the honest case.
    assert!(crate::is_less(&result[0], modulus));
    assert!(crate::is_less(&result[1], modulus));
    assert!(crate::is_less(&result[2], modulus));
    assert!(crate::is_less(&result[3], modulus));
}

pub fn extfield_deg2_sub_256(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unchecked::extfield_deg2_sub_256(lhs, rhs, modulus, result);

    // An honest host will always return a result less than the modulus. A dishonest prover can
    // sometimes return a result greater than the modulus, so enforce that we're in the honest case.
    assert!(crate::is_less(&result[0], modulus));
    assert!(crate::is_less(&result[1], modulus));
}

pub fn extfield_deg2_sub_384(
    lhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unchecked::extfield_deg2_sub_384(lhs, rhs, modulus, result);

    // An honest host will always return a result less than the modulus. A dishonest prover can
    // sometimes return a result greater than the modulus, so enforce that we're in the honest case.
    assert!(crate::is_less(&result[0], modulus));
    assert!(crate::is_less(&result[1], modulus));
}

pub fn extfield_xxone_mul_256(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    modsqr: &[u32; 2 * FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unchecked::extfield_xxone_mul_256(lhs, rhs, modulus, modsqr, result);

    // An honest host will always return a result less than the modulus. A dishonest prover can
    // sometimes return a result greater than the modulus, so enforce that we're in the honest case.
    assert!(crate::is_less(&result[0], modulus));
    assert!(crate::is_less(&result[1], modulus));
}

pub fn extfield_xxone_mul_384(
    lhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    modsqr: &[u32; 2 * FIELD_384_WIDTH_WORDS],
    result: &mut [[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unchecked::extfield_xxone_mul_384(lhs, rhs, modulus, modsqr, result);

    // An honest host will always return a result less than the modulus. A dishonest prover can
    // sometimes return a result greater than the modulus, so enforce that we're in the honest case.
    assert!(crate::is_less(&result[0], modulus));
    assert!(crate::is_less(&result[1], modulus));
}
