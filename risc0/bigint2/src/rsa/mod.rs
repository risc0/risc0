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

use crate::ffi::sys_bigint2_3;

#[stability::unstable]
pub const RSA_3072_WIDTH_WORDS: usize = 3072 / 32;
#[stability::unstable]
pub const RSA_4096_WIDTH_WORDS: usize = 4096 / 32;

const BLOB: &[u8] = include_bytes_aligned!(4, "modpow_65537.blob");

#[stability::unstable]
pub fn modpow_65537_3072(
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

#[stability::unstable]
pub fn modpow_65537_4096(
    base: &[u32; RSA_4096_WIDTH_WORDS],
    modulus: &[u32; RSA_4096_WIDTH_WORDS],
    result: &mut [u32; RSA_4096_WIDTH_WORDS],
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
