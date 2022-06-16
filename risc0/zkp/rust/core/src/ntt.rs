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

//! An implementation of a Numeric Theoretic Transform (NTT).

use core::ops::{Add, Sub};

use paste::paste;

use crate::{
    fp::{Fp, FpMul},
    log2_ceil,
    rou::{ROU_FWD, ROU_REV},
};

/// Reverses the bits in a 32 bit number
/// For example 1011...0100 becomes 0010...1101
fn bit_rev_32(mut x: u32) -> u32 {
    x = ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1);
    x = ((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2);
    x = ((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4);
    x = ((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8);
    (x >> 16) | (x << 16)
}

/// Bit reverses the indices in an array of (1 << n) numbers.
/// This permutes the values in the array so that a value which is previously
/// in index i, will now go in the index i' given by reversing the bits of i.
/// For example, with n=4, the value at index 3=0011 will go to index 12=1100.
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
fn fwd_butterfly_0<T>(_: &mut [T], _: usize) {
    // no-op base case
}

#[inline]
fn rev_butterfly_0<T>(_: &mut [T]) {
    // no-op base case
}

macro_rules! butterfly {
    ($n:literal, $x:literal) => {
        paste! {
            #[inline]
            fn [<fwd_butterfly_ $n>]<T>(io: &mut [T], expand_bits: usize)
            where
                T: Copy + FpMul + Add<Output = T> + Sub<Output = T>,
            {
                if $n == expand_bits {
                    return;
                }
                let half = 1 << ($n - 1);
                [<fwd_butterfly_ $x>](&mut io[..half], expand_bits);
                [<fwd_butterfly_ $x>](&mut io[half..], expand_bits);
                let step = Fp::new(ROU_FWD[$n]);
                let mut cur = Fp::new(1);
                for i in 0..half {
                    let a = io[i];
                    let b = io[i + half].fp_mul(cur);
                    io[i] = a + b;
                    io[i + half] = a - b;
                    cur *= step;
                }
            }

            #[inline]
            fn [<rev_butterfly_ $n>]<T>(io: &mut [T])
            where
                T: Copy + FpMul + Add<Output = T> + Sub<Output = T>,
            {
                let half = 1 << ($n - 1);
                let step = Fp::new(ROU_REV[$n]);
                let mut cur = Fp::new(1);
                for i in 0..half {
                    let a = io[i];
                    let b = io[i + half];
                    io[i] = a + b;
                    io[i + half] = (a - b).fp_mul(cur);
                    cur *= step;
                }
                [<rev_butterfly_ $x>](&mut io[..half]);
                [<rev_butterfly_ $x>](&mut io[half..]);
            }
        }
    };
}

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
/// changed indices. This is described [here](https://en.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm#Data_reordering,_bit_reversal,_and_in-place_algorithms)
/// The output of rev_butterfly(io, n) at index i is the sum over k from 0 to
/// 2^n-1 of io[k] * ROU_REV[n]^(k*i'), where i' is i bit-reversed as an n-bit
/// number.
///
/// As an example, we'll work through a trace of the rev_butterfly algorithm
/// with n = 3 on a list of length 8. Let w = ROU_REV[3] be the eighth root of
/// unity. We start with
///   [a0, a1, a2, a3, a4, a5, a6, a7]
/// After the loop, before the first round of recursive calls, we have
///   [a0+a4, a1+a5,     a2+a6,         a3+a7,
///    a0-a4, a1*w-a5*w, a2*w^2-a6*w^2, a3*w^3-a7*w^3]
/// After first round of recursive calls, we have
///   [a0+a4+a2+a6,         a1+a5+a3+a7,
///    a0+a4-a2-a6,         a1*w^2+a5*w^2-a3*w^2-a7*w^2,
///    a0-a4+a2*w^2-a6*w^2, a1*w-a5*w+a3*w^3-a7*w^3,
///    a0-a4-a2*w^2+a6*w^2, a1*w^3-a5*w^3-a3*w^5+a7*w^5]
/// And after the second round of recursive calls, we have
///   [a0+a4+a2+a6+a1+a5+a3+a7,
///    a0+a4+a2+a6-a1-a5-a3-a7,
///    a0+a4-a2-a6+a1*w^2+a5*w^2-a3*w^2-a7*w^2,
///    a0+a4-a2-a6-a1*w^2-a5*w^2+a3*w^2+a7*w^2,
///    a0-a4+a2*w^2-a6*w^2+a1*w-a5*w+a3*w^3-a7*w^3,
///    a0-a4+a2*w^2-a6*w^2-a1*w+a5*w-a3*w^3+a7*w^3,
///    a0-a4-a2*w^2+a6*w^2+a1*w^3-a5*w^3+a3*w^5-a7*w^5,
///    a0-a4-a2*w^2+a6*w^2-a1*w^3+a5*w^3-a3*w^5+a7*w^5]
/// Rewriting this, we get
///   [sum_k ak w^0,
///    sum_k ak w^4k,
///    sum_k ak w^2k,
///    sum_k ak w^6k,
///    sum_k ak w^1k,
///    sum_k ak w^5k,
///    sum_k ak w^3k,
///    sum_k ak w^7k]
/// The exponent multiplicands in the sum arise from reversing the indices as
/// three-bit numbers. For example, 3 is 011 in binary, which reversed is 110,
/// which is 6. So i' in the exponent of the index-3 value is 6.
pub fn interpolate_ntt<T>(io: &mut [T])
where
    T: Copy + FpMul + Add<Output = T> + Sub<Output = T>,
{
    let size = io.len();
    let n = log2_ceil(size);
    assert_eq!(1 << n, size);
    match n {
        0 => rev_butterfly_0(io),
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
        _ => unreachable!(),
    }
    let norm = Fp::new(size as u32).inv();
    for i in 0..size {
        io[i] = io[i].fp_mul(norm);
    }
}

/// Perform a forward butterfly transform of a buffer of (1 << n) numbers.
pub fn evaluate_ntt<T>(io: &mut [T], expand_bits: usize)
where
    T: Copy + FpMul + Add<Output = T> + Sub<Output = T>,
{
    // do_ntt::<T, false>(io, expand_bits);
    let size = io.len();
    let n = log2_ceil(size);
    assert_eq!(1 << n, size);
    match n {
        0 => fwd_butterfly_0(io, expand_bits),
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
        _ => unreachable!(),
    }
}

/// Expand the `input` into `output` to support polynomial evaluation on `expand_bits` points.
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
    use rand::thread_rng;

    use crate::{
        fp::Fp,
        ntt::{bit_reverse, evaluate_ntt, interpolate_ntt},
        rou::ROU_FWD,
        Random,
    };

    // Compare the complex version to the naive version
    #[test]
    fn cmp_evaluate() {
        const N: usize = 6;
        const SIZE: usize = 1 << N;
        let mut rng = thread_rng();
        // Randomly fill input
        let mut buf = [Fp::random(&mut rng); SIZE];
        // Compute the hard way
        let mut goal = [Fp::default(); SIZE];
        // Compute polynomial at each ROU power (starting at 0, i.e. x = 1)
        let mut x = Fp::new(1);
        for i in 0..SIZE {
            // Compute the polynomial
            let mut tot = Fp::new(0);
            let mut xn = Fp::new(1);
            for j in 0..SIZE {
                tot += buf[j] * xn;
                xn *= x;
            }
            goal[i] = tot;
            x *= Fp::new(ROU_FWD[N]);
        }
        // Now compute multiEvaluate in place
        bit_reverse(&mut buf);
        evaluate_ntt(&mut buf, 0);
        // Compare
        assert_eq!(goal, buf);
    }

    // Make sure fwd + rev is identity
    #[test]
    fn roundtrip() {
        const N: usize = 10;
        const SIZE: usize = 1 << N;
        // Randomly fill buffer
        let mut rng = thread_rng();
        let mut buf = [Fp::random(&mut rng); SIZE];
        // Copy it
        let orig = buf.clone();
        // Now go backwords
        interpolate_ntt(&mut buf);
        // Make sure something changed
        assert_ne!(orig, buf);
        // Now go forward
        evaluate_ntt(&mut buf, 0);
        // It should be back to identical
        assert_eq!(orig, buf);
    }

    #[test]
    fn expand() {
        const N: usize = 6;
        const L: usize = 2;
        const SIZE_IN: usize = 1 << (N - L);
        const SIZE_OUT: usize = 1 << N;
        let mut rng = thread_rng();
        let mut cmp = [Fp::random(&mut rng); SIZE_IN];
        let mut buf = [Fp::default(); SIZE_OUT];
        // Do plain interpolate on cmp
        interpolate_ntt(&mut cmp);
        // Expand to buf
        super::expand(&mut buf, &cmp, L);
        // Evaluate over the larger space
        evaluate_ntt(&mut buf, L);
        // Order cmp nicely for the check
        bit_reverse(&mut cmp);
        // Now verify by comparing with the slow way
        let mut goal = [Fp::default(); SIZE_OUT];
        // Compute polynomial at each ROU power (starting at 0, i.e. x = 1)
        let mut x = Fp::new(1);
        for i in 0..SIZE_OUT {
            // Compute the polynomial
            let mut tot = Fp::new(0);
            let mut xn = Fp::new(1);
            for j in 0..SIZE_IN {
                tot += cmp[j] * xn;
                xn *= x;
            }
            goal[i] = tot;
            x *= Fp::new(ROU_FWD[N]);
        }
        assert_eq!(goal, buf);
    }
}
