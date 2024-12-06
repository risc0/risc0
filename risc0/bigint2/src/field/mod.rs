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

use crate::ffi::{sys_bigint2_3, sys_bigint2_4};
use crate::WORD_SIZE;

pub const FIELD_256_WIDTH_WORDS: usize = 256 / (WORD_SIZE * 8);
pub const EXT_DEGREE_2: usize = 2;  // TODO

const MODADD_256_BLOB: &[u8] = include_bytes_aligned!(4, "modadd_256.blob");
const MODINV_256_BLOB: &[u8] = include_bytes_aligned!(4, "modinv_256.blob");
const MODMUL_256_BLOB: &[u8] = include_bytes_aligned!(4, "modmul_256.blob");
const MODSUB_256_BLOB: &[u8] = include_bytes_aligned!(4, "modsub_256.blob");
const EXTFIELDADD_256_BLOB: &[u8] = include_bytes_aligned!(4, "extfieldadd_256.blob");
const EXTFIELDMUL_256_BLOB: &[u8] = include_bytes_aligned!(4, "extfieldmul_256.blob");
const EXTFIELDSUB_256_BLOB: &[u8] = include_bytes_aligned!(4, "extfieldsub_256.blob");

pub fn modadd_256(
    lhs: &[u32; FIELD_256_WIDTH_WORDS],
    rhs: &[u32; FIELD_256_WIDTH_WORDS],
    prime: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    unsafe {
        sys_bigint2_4(
            MODADD_256_BLOB.as_ptr(),
            lhs.as_ptr() as *const u32,
            rhs.as_ptr() as *const u32,
            prime.as_ptr() as *const u32,
            result.as_mut_ptr() as *mut u32,
        );
    }
}

pub fn modinv_256(
    inp: &[u32; FIELD_256_WIDTH_WORDS],
    prime: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    unsafe {
        sys_bigint2_3(
            MODINV_256_BLOB.as_ptr(),
            inp.as_ptr() as *const u32,
            prime.as_ptr() as *const u32,
            result.as_mut_ptr() as *mut u32,
        );
    }
}

pub fn modmul_256(
    lhs: &[u32; FIELD_256_WIDTH_WORDS],
    rhs: &[u32; FIELD_256_WIDTH_WORDS],
    prime: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    unsafe {
        sys_bigint2_4(
            MODMUL_256_BLOB.as_ptr(),
            lhs.as_ptr() as *const u32,
            rhs.as_ptr() as *const u32,
            prime.as_ptr() as *const u32,
            result.as_mut_ptr() as *mut u32,
        );
    }
}

pub fn modsub_256(
    lhs: &[u32; FIELD_256_WIDTH_WORDS],
    rhs: &[u32; FIELD_256_WIDTH_WORDS],
    prime: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    unsafe {
        sys_bigint2_4(
            MODSUB_256_BLOB.as_ptr(),
            lhs.as_ptr() as *const u32,
            rhs.as_ptr() as *const u32,
            prime.as_ptr() as *const u32,
            result.as_mut_ptr() as *mut u32,
        );
    }
}

pub fn extfieldadd_256(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    prime: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unsafe {
        sys_bigint2_4(
            EXTFIELDADD_256_BLOB.as_ptr(),
            lhs.as_ptr() as *const u32,
            rhs.as_ptr() as *const u32,
            prime.as_ptr() as *const u32,
            result.as_mut_ptr() as *mut u32,
        );
    }
}

pub fn extfieldmul_256(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    prime: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unsafe {
        sys_bigint2_4(
            EXTFIELDMUL_256_BLOB.as_ptr(),
            lhs.as_ptr() as *const u32,
            rhs.as_ptr() as *const u32,
            prime.as_ptr() as *const u32,
            result.as_mut_ptr() as *mut u32,
        );
    }
}

pub fn extfieldsub_256(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    prime: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unsafe {
        sys_bigint2_4(
            EXTFIELDSUB_256_BLOB.as_ptr(),
            lhs.as_ptr() as *const u32,
            rhs.as_ptr() as *const u32,
            prime.as_ptr() as *const u32,
            result.as_mut_ptr() as *mut u32,
        );
    }
}
