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

use std::alloc::{self, Layout};

use include_bytes_aligned::include_bytes_aligned;
use num_bigint::BigUint;

use crate::ffi::sys_bigint2_3;

const WORD_SIZE: usize = 4;
pub const RSA_3072_WIDTH_WORDS: usize = 3072 / 32;
pub const RSA_3072_WIDTH_BYTES: usize = RSA_3072_WIDTH_WORDS * WORD_SIZE;

const BLOB: &[u8] = include_bytes_aligned!(4, "modpow_65537.blob");

fn init_rsa_buffer() -> Box<[u32; RSA_3072_WIDTH_WORDS]> {
    let layout = Layout::array::<u32>(RSA_3072_WIDTH_WORDS).unwrap();
    let ptr = unsafe { alloc::alloc_zeroed(layout) };
    unsafe { Box::from_raw(ptr as *mut [u32; RSA_3072_WIDTH_WORDS]) }
}

#[cfg(feature = "num-bigint-dig")]
fn to_u32_digits(input: &BigUint) -> Box<[u32; RSA_3072_WIDTH_WORDS]> {
    let mut result = init_rsa_buffer();
    let bytes = input.to_bytes_le();
    assert!(
        bytes.len() <= RSA_3072_WIDTH_BYTES,
        "Input too large: {} bytes exceeds RSA width of {} bytes",
        bytes.len(),
        RSA_3072_WIDTH_BYTES
    );

    let mut chunks = bytes.chunks_exact(WORD_SIZE);
    for (i, chunk) in chunks.by_ref().enumerate() {
        result[i] = u32::from_le_bytes(chunk.try_into().unwrap());
    }

    let remainder = chunks.remainder();
    if !remainder.is_empty() {
        let idx = bytes.len() / WORD_SIZE;
        let mut word = 0u32;
        for (i, &byte) in remainder.iter().enumerate() {
            word |= (byte as u32) << (i * 8);
        }
        result[idx] = word;
    }

    result
}

#[cfg(not(feature = "num-bigint-dig"))]
fn to_u32_digits(input: &BigUint) -> Box<[u32; RSA_3072_WIDTH_WORDS]> {
    let digits = input.to_u32_digits();
    assert!(
        digits.len() <= RSA_3072_WIDTH_WORDS,
        "Input too large: {} words exceeds RSA width of {} words",
        digits.len(),
        RSA_3072_WIDTH_WORDS
    );

    let mut result = init_rsa_buffer();
    result[..digits.len()].copy_from_slice(&digits);
    result
}

pub fn modpow_65537(base: &BigUint, modulus: &BigUint) -> BigUint {
    let base = to_u32_digits(base);
    let modulus = to_u32_digits(modulus);
    let mut result = [0u32; RSA_3072_WIDTH_WORDS];
    raw_modpow_65537(&base, &modulus, &mut result);
    BigUint::from_slice(&result)
}

pub fn raw_modpow_65537(
    base: &[u32; RSA_3072_WIDTH_WORDS],
    modulus: &[u32; RSA_3072_WIDTH_WORDS],
    result: &mut [u32; RSA_3072_WIDTH_WORDS],
) {
    unsafe {
        sys_bigint2_3(
            BLOB.as_ptr(),
            base.as_ptr(),
            modulus.as_ptr(),
            result.as_mut_ptr(),
        );
    }
}
