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

//! Very basic utilities to help implement NTT, used only in the verifier.

use crate::{fp4::Fp4, rou::ROU_REV};

/// Reverses the bits in a 32 bit number
/// For example 1011...0100 becomes 0010...1101
fn bit_rev_32(mut x: u32) -> u32 {
    x = ((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1);
    x = ((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2);
    x = ((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4);
    x = ((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8);
    (x >> 16) | (x << 16)
}

/// Bit reverse an array of (1 << n) numbers.
pub fn bit_reverse(io: &mut [Fp4], n: usize) {
    let size: usize = 1 << n;
    for i in 0..size {
        let rev_idx: usize = (bit_rev_32(i.try_into().unwrap()) >> (32 - n))
            .try_into()
            .unwrap();
        if i < rev_idx {
            let tmp = io[i];
            io[i] = io[rev_idx];
            io[rev_idx] = tmp;
        }
    }
}

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
/// And after the second round of recursive calls, we have
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
pub fn rev_butterfly(io: &mut [Fp4], n: usize) {
    assert!(io.len() == (1 << n));
    if n == 0 {
        return;
    }
    let half = 1 << (n - 1);
    let step = Fp4::from_u32(ROU_REV[n]);
    let mut cur = Fp4::one();
    for i in 0..half {
        let a = io[i];
        let b = io[i + half];
        io[i] = a + b;
        io[i + half] = (a - b) * cur;
        cur *= step;
    }
    rev_butterfly(&mut io[..half], n - 1);
    rev_butterfly(&mut io[half..], n - 1);
}
