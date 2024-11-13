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

use crate::ffi::sys_bigint2_3;

const WORD_SIZE: usize = 4;
pub const RSA_3072_WIDTH_WORDS: usize = 3072 / 32;
pub const RSA_3072_WIDTH_BYTES: usize = RSA_3072_WIDTH_WORDS * WORD_SIZE;

const BLOB: &[u8] = include_bytes_aligned!(4, "modpow_65537.blob");

#[cfg(feature = "num-bigint-dig")]
fn to_u32_digits(input: &BigUint) -> Vec<u32> {
    let mut digits = Vec::with_capacity(RSA_3072_WIDTH_WORDS);
    let bytes = input.to_bytes_le();
    let mut chunks = bytes.chunks_exact(WORD_SIZE);
    for chunk in chunks.by_ref() {
        let word = u32::from_le_bytes(chunk.try_into().unwrap());
        digits.push(word);
    }

    let remainder = chunks.remainder();
    if !remainder.is_empty() {
        let mut word = 0u32;
        for i in 0..remainder.len() {
            word |= (remainder[i] as u32) << (i * 8);
        }
        digits.push(word);
    }

    digits
}

#[cfg(not(feature = "num-bigint-dig"))]
fn to_u32_digits(input: &BigUint) -> Vec<u32> {
    input.to_u32_digits()
}

pub fn modpow_65537(base: &BigUint, modulus: &BigUint) -> BigUint {
    let base = to_u32_digits(base);
    let modulus = to_u32_digits(modulus);
    let mut result = [0u32; RSA_3072_WIDTH_WORDS];
    raw_modpow_65537(&base, &modulus, &mut result);
    BigUint::from_slice(&result)
}

pub fn raw_modpow_65537(base: &[u32], modulus: &[u32], result: &mut [u32]) {
    assert_eq!(base.len(), RSA_3072_WIDTH_WORDS);
    assert_eq!(modulus.len(), RSA_3072_WIDTH_WORDS);
    assert_eq!(result.len(), RSA_3072_WIDTH_WORDS);

    unsafe {
        sys_bigint2_3(
            BLOB.as_ptr(),
            base.as_ptr(),
            modulus.as_ptr(),
            result.as_mut_ptr(),
        );
    }
}
