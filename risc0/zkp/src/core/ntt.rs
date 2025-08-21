// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! An implementation of a number-theoretic transform (NTT).

use core::ops::{Add, Mul, Sub};

use paste::paste;
use risc0_core::field::{Elem, RootsOfUnity};

use super::log2_ceil;

/// Reverses the bits in a 32-bit number.
/// # Example
/// ```rust
/// # use risc0_zkp::core::ntt::bit_rev_32;
/// #
/// let a: u32 = 2^8 + 2^4 + 1;
///
/// assert_eq!(format!("{:b}", a), "1101");
/// assert_eq!(format!("{:b}", bit_rev_32(a)), "10110000000000000000000000000000");
/// ```
pub fn bit_rev_32(mut x: u32) -> u32 {
    // The values used here are, in binary:
    // 10101010101010101010101010101010, 01010101010101010101010101010101
    x = ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1);
    // 110011001100110011001100, 001100110011001100110011
    x = ((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2);
    // 111100001111000011110000, 000011110000111100001111
    x = ((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4);
    // 11111111000000001111111100000000, 00000000111111110000000011111111
    x = ((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8);
    x.rotate_left(16)
}

/// Bit-reverses the indices in an array of (1 << n) numbers.
/// This permutes the values in the array so that a value which is previously
/// in index i will now go in the index i', given by reversing the bits of i.
///
/// # Example
/// For example, with the array given below of size n=4,
/// the indices are `0, 1, 2, 3`; bitwise, they're `0, 01, 10, 11`.
///
/// Reversed, these give `0, 10, 01, 11`, permuting the second and third
/// values.
/// ```rust
/// # use risc0_zkp::core::ntt::bit_reverse;
/// #
/// let mut some_values = [1, 2, 3, 4];
/// bit_reverse(&mut some_values);
/// assert_eq!(some_values, [1, 3, 2, 4]);
/// ```
pub fn bit_reverse<T: Copy>(io: &mut [T]) {
    let n = log2_ceil(io.len());
    assert_eq!(1 << n, io.len());
    for i in 0..io.len() {
        let rev_idx = (bit_rev_32(i as u32) >> (32 - n)) as usize;
        if i < rev_idx {
            io.swap(i, rev_idx);
        }
    }
}

#[inline]
fn fwd_butterfly_0<B, T>(_: &mut [T], _: usize) {
    // no-op base case
}

#[inline]
fn rev_butterfly_0<B, T>(_: &mut [T]) {
    // no-op base case
}

// TODO: This generates butterfly functions up to $n = 32, but will panic if $n
// is bigger than <F as RootsOfUnity>::MAX_ROU_PO2 -- is this the best approach?
macro_rules! butterfly {
    ($n:literal, $x:literal) => {
        paste! {
            #[inline]
            fn [<fwd_butterfly_ $n>]<B, T>(io: &mut [T], expand_bits: usize)
            where
                // B is a base field element, T may be either base or extension
                B: Elem + RootsOfUnity,
                T: Copy + Mul<B, Output = T> + Add<Output = T> + Sub<Output = T>,
            {
                if $n == expand_bits {
                    return;
                }
                let half = 1 << ($n - 1);
                [<fwd_butterfly_ $x>]::<B, T>(&mut io[..half], expand_bits);
                [<fwd_butterfly_ $x>]::<B, T>(&mut io[half..], expand_bits);
                let step = <B as RootsOfUnity>::ROU_FWD[$n];
                let mut cur = B::ONE;
                for i in 0..half {
                    let a = io[i];
                    let b = io[i + half] * cur;
                    io[i] = a + b;
                    io[i + half] = a - b;
                    cur *= step;
                }
            }

            #[inline]
            fn [<rev_butterfly_ $n>]<B, T>(io: &mut [T])
            where
                // B is a base field element, T may be either base or extension
                B: Elem + RootsOfUnity,
                T: Copy + Mul<B, Output = T> + Add<Output = T> + Sub<Output = T>,
            {
                let half = 1 << ($n - 1);
                let step = <B as RootsOfUnity>::ROU_REV[$n];
                let mut cur = B::ONE;
                for i in 0..half {
                    let a = io[i];
                    let b = io[i + half];
                    io[i] = a + b;
                    io[i + half] = (a - b) * cur;
                    cur *= step;
                }
                [<rev_butterfly_ $x>]::<B, T>(&mut io[..half]);
                [<rev_butterfly_ $x>]::<B, T>(&mut io[half..]);
            }
        }
    };
}

butterfly!(32, 31);
butterfly!(31, 30);
butterfly!(30, 29);
butterfly!(29, 28);
butterfly!(28, 27);
butterfly!(27, 26);
butterfly!(26, 25);
butterfly!(25, 24);
butterfly!(24, 23);
butterfly!(23, 22);
butterfly!(22, 21);
butterfly!(21, 20);
butterfly!(20, 19);
butterfly!(19, 18);
butterfly!(18, 17);
butterfly!(17, 16);
butterfly!(16, 15);
butterfly!(15, 14);
butterfly!(14, 13);
butterfly!(13, 12);
butterfly!(12, 11);
butterfly!(11, 10);
butterfly!(10, 9);
butterfly!(9, 8);
butterfly!(8, 7);
butterfly!(7, 6);
butterfly!(6, 5);
butterfly!(5, 4);
butterfly!(4, 3);
butterfly!(3, 2);
butterfly!(2, 1);
butterfly!(1, 0);

/// Perform a reverse butterfly transform of a buffer of (1 << n) numbers.
/// The result of this computation is a discrete Fourier transform, but with
/// changed indices. This is described [here](https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm#Data_reordering,_bit_reversal,_and_in-place_algorithms).
/// The output of `rev_butterfly(io, n)` at index i is the sum over k from 0 to
/// 2^n-1 of io\[k\] ROU_REV\[n\]^(k i'), where i' is i bit-reversed as an
/// n-bit number and ROU_REV are the 'reverse' roots of unity.
///
/// As an example, we'll work through a trace of the rev_butterfly algorithm
/// with n = 3 on a list of length 8. Let w = ROU_REV\[3\] be the eighth root of
/// unity. We start with
///
///   \[a0, a1, a2, a3, a4, a5, a6, a7\]
///
/// After the loop, before the first round of recursive calls, we have
///
///   [a0+a4, a1+a5,     a2+a6,         a3+a7,
///
///    a0-a4, a1w-a5w, a2w^2-a6w^2, a3w^3-a7w^3]
///
/// After first round of recursive calls, we have
///
///   [a0+a4+a2+a6,         a1+a5+a3+a7,
///
///    a0+a4-a2-a6,         a1w^2+a5w^2-a3w^2-a7w^2,
///
///    a0-a4+a2w^2-a6w^2, a1w-a5w+a3w^3-a7w^3,
///
///    a0-a4-a2w^2+a6w^2, a1w^3-a5w^3-a3w^5+a7w^5]
///
/// And after the second round of recursive calls, we have
///
///   [a0+a4+a2+a6+a1+a5+a3+a7,
///
///    a0+a4+a2+a6-a1-a5-a3-a7,
///
///    a0+a4-a2-a6+a1w^2+a5w^2-a3w^2-a7w^2,
///
///    a0+a4-a2-a6-a1w^2-a5w^2+a3w^2+a7w^2,
///
///    a0-a4+a2w^2-a6w^2+a1w-a5w+a3w^3-a7w^3,
///
///    a0-a4+a2w^2-a6w^2-a1w+a5w-a3w^3+a7w^3,
///
///    a0-a4-a2w^2+a6w^2+a1w^3-a5w^3+a3w^5-a7w^5,
///
///    a0-a4-a2w^2+a6w^2-a1w^3+a5w^3-a3w^5+a7w^5]
///
/// Rewriting this, we get
///
///   \[sum_k ak w^0,
///    sum_k ak w^4k,
///    sum_k ak w^2k,
///    sum_k ak w^6k,
///    sum_k ak w^1k,
///    sum_k ak w^5k,
///    sum_k ak w^3k,
///    sum_k ak w^7k\]
///
/// The exponent multiplicands in the sum arise from reversing the indices as
/// three-bit numbers. For example, 3 is 011 in binary, which reversed is 110,
/// which is 6. So i' in the exponent of the index-3 value is 6.
pub fn interpolate_ntt<B, T>(io: &mut [T])
where
    // B is a base field element, T may be either base or extension
    B: Elem + RootsOfUnity,
    T: Copy + Mul<B, Output = T> + Add<Output = T> + Sub<Output = T>,
{
    let size = io.len();
    let n = log2_ceil(size);
    assert_eq!(1 << n, size);
    match n {
        0 => rev_butterfly_0::<B, T>(io),
        1 => rev_butterfly_1(io),
        2 => rev_butterfly_2(io),
        3 => rev_butterfly_3(io),
        4 => rev_butterfly_4(io),
        5 => rev_butterfly_5(io),
        6 => rev_butterfly_6(io),
        7 => rev_butterfly_7(io),
        8 => rev_butterfly_8(io),
        9 => rev_butterfly_9(io),
        10 => rev_butterfly_10(io),
        11 => rev_butterfly_11(io),
        12 => rev_butterfly_12(io),
        13 => rev_butterfly_13(io),
        14 => rev_butterfly_14(io),
        15 => rev_butterfly_15(io),
        16 => rev_butterfly_16(io),
        17 => rev_butterfly_17(io),
        18 => rev_butterfly_18(io),
        19 => rev_butterfly_19(io),
        20 => rev_butterfly_20(io),
        21 => rev_butterfly_21(io),
        22 => rev_butterfly_22(io),
        23 => rev_butterfly_23(io),
        24 => rev_butterfly_24(io),
        25 => rev_butterfly_25(io),
        26 => rev_butterfly_26(io),
        27 => rev_butterfly_27(io),
        28 => rev_butterfly_28(io),
        29 => rev_butterfly_29(io),
        30 => rev_butterfly_30(io),
        31 => rev_butterfly_31(io),
        32 => rev_butterfly_32(io),
        _ => unreachable!(),
    }
    let norm = B::from_u64(size as u64).inv();
    for x in io.iter_mut().take(size) {
        *x = *x * norm;
    }
}

/// Perform a forward butterfly transform of a buffer of (1 << n) numbers.
pub fn evaluate_ntt<B, T>(io: &mut [T], expand_bits: usize)
where
    // B is a base field element, T may be either base or extension
    B: Elem + RootsOfUnity,
    T: Copy + Mul<B, Output = T> + Add<Output = T> + Sub<Output = T>,
{
    // do_ntt::<T, false>(io, expand_bits);
    let size = io.len();
    let n = log2_ceil(size);
    assert_eq!(1 << n, size);
    match n {
        0 => fwd_butterfly_0::<B, T>(io, expand_bits),
        1 => fwd_butterfly_1(io, expand_bits),
        2 => fwd_butterfly_2(io, expand_bits),
        3 => fwd_butterfly_3(io, expand_bits),
        4 => fwd_butterfly_4(io, expand_bits),
        5 => fwd_butterfly_5(io, expand_bits),
        6 => fwd_butterfly_6(io, expand_bits),
        7 => fwd_butterfly_7(io, expand_bits),
        8 => fwd_butterfly_8(io, expand_bits),
        9 => fwd_butterfly_9(io, expand_bits),
        10 => fwd_butterfly_10(io, expand_bits),
        11 => fwd_butterfly_11(io, expand_bits),
        12 => fwd_butterfly_12(io, expand_bits),
        13 => fwd_butterfly_13(io, expand_bits),
        14 => fwd_butterfly_14(io, expand_bits),
        15 => fwd_butterfly_15(io, expand_bits),
        16 => fwd_butterfly_16(io, expand_bits),
        17 => fwd_butterfly_17(io, expand_bits),
        18 => fwd_butterfly_18(io, expand_bits),
        19 => fwd_butterfly_19(io, expand_bits),
        20 => fwd_butterfly_20(io, expand_bits),
        21 => fwd_butterfly_21(io, expand_bits),
        22 => fwd_butterfly_22(io, expand_bits),
        23 => fwd_butterfly_23(io, expand_bits),
        24 => fwd_butterfly_24(io, expand_bits),
        25 => fwd_butterfly_25(io, expand_bits),
        26 => fwd_butterfly_26(io, expand_bits),
        27 => fwd_butterfly_27(io, expand_bits),
        28 => fwd_butterfly_28(io, expand_bits),
        29 => fwd_butterfly_29(io, expand_bits),
        30 => fwd_butterfly_30(io, expand_bits),
        31 => fwd_butterfly_31(io, expand_bits),
        32 => fwd_butterfly_32(io, expand_bits),
        _ => unreachable!(),
    }
}

/// Expand the `input` into `output` to support polynomial evaluation on
/// `input.len() * (1 << expand_bits)` points.
pub fn expand<T>(output: &mut [T], input: &[T], expand_bits: usize)
where
    T: Copy,
{
    let size_out = input.len() * (1 << expand_bits);
    for i in 0..size_out {
        output[i] = input[i >> expand_bits];
    }
}

#[cfg(test)]
mod tests {
    use risc0_core::field::{Elem, RootsOfUnity, baby_bear::BabyBearElem};

    use crate::core::ntt::{bit_reverse, evaluate_ntt, interpolate_ntt};

    // Compare the complex version to the naive version
    #[test]
    fn cmp_evaluate() {
        const N: usize = 6;
        const SIZE: usize = 1 << N;
        let mut rng = rand::rng();
        // Randomly fill input
        let mut buf = [BabyBearElem::random(&mut rng); SIZE];
        // Compute the hard way
        let mut goal = [BabyBearElem::ZERO; SIZE];
        // Compute polynomial at each ROU power (starting at 0, i.e. x = 1)
        let mut x = BabyBearElem::ONE;
        for goal in goal.iter_mut() {
            // Compute the polynomial
            let mut tot = BabyBearElem::ZERO;
            let mut xn = BabyBearElem::ONE;
            for buf in buf.iter() {
                tot += *buf * xn;
                xn *= x;
            }
            *goal = tot;
            x *= BabyBearElem::ROU_FWD[N];
        }
        // Now compute multiEvaluate in place
        bit_reverse(&mut buf);
        evaluate_ntt::<BabyBearElem, BabyBearElem>(&mut buf, 0);
        // Compare
        assert_eq!(goal, buf);
    }

    // Make sure fwd + rev is identity
    #[test]
    fn roundtrip() {
        const N: usize = 10;
        const SIZE: usize = 1 << N;
        // Randomly fill buffer
        let mut rng = rand::rng();
        let mut buf = [BabyBearElem::random(&mut rng); SIZE];
        // Copy it
        let orig = buf;
        // Now go backwards
        interpolate_ntt::<BabyBearElem, BabyBearElem>(&mut buf);
        // Make sure something changed
        assert_ne!(orig, buf);
        // Now go forward
        evaluate_ntt::<BabyBearElem, BabyBearElem>(&mut buf, 0);
        // It should be back to identical
        assert_eq!(orig, buf);
    }

    #[test]
    fn expand() {
        const N: usize = 6;
        const L: usize = 2;
        const SIZE_IN: usize = 1 << (N - L);
        const SIZE_OUT: usize = 1 << N;
        let mut rng = rand::rng();
        let mut cmp = [BabyBearElem::random(&mut rng); SIZE_IN];
        let mut buf = [BabyBearElem::ZERO; SIZE_OUT];
        // Do plain interpolate on cmp
        interpolate_ntt::<BabyBearElem, BabyBearElem>(&mut cmp);
        // Expand to buf
        super::expand(&mut buf, &cmp, L);
        // Evaluate over the larger space
        evaluate_ntt::<BabyBearElem, BabyBearElem>(&mut buf, L);
        // Order cmp nicely for the check
        bit_reverse(&mut cmp);
        // Now verify by comparing with the slow way
        let mut goal = [BabyBearElem::ZERO; SIZE_OUT];
        // Compute polynomial at each ROU power (starting at 0, i.e. x = 1)
        let mut x = BabyBearElem::ONE;
        for goal in goal.iter_mut() {
            // Compute the polynomial
            let mut tot = BabyBearElem::ZERO;
            let mut xn = BabyBearElem::ONE;
            for cmp in cmp.iter() {
                tot += *cmp * xn;
                xn *= x;
            }
            *goal = tot;
            x *= BabyBearElem::ROU_FWD[N];
        }
        assert_eq!(goal, buf);
    }
}
