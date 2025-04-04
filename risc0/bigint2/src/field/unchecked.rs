// Copyright 2025 RISC Zero, Inc.
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

//! Operations that don't constrain `result < modulus`
//!
//! These finite field arithmetic acceleration operations are "unchecked" in the sense that they
//! provide no guarantee that `result < modulus` (or, in the case of extension field operations,
//! provide no guarantee for any coefficient that `result < characteristic`). This can be acceptable
//! when computing internal results during a series of finite field operations, provided the other
//! finite field operations expect that inputs may violate this constraint, but using these
//! functions can create security holes in certain other use cases (e.g. comparing to a hash value).
//!
//! There are checking wrappers available in [crate::field] for use cases where `result < modulus`
//! checking is necessary; you should also avoid these functions and prefer the checked versions in
//! [crate::field] if you are uncertain about the security implications of this choice.

use crate::{
    ffi::{sys_bigint2_3, sys_bigint2_4, sys_bigint2_5},
    field::{EXT_DEGREE_2, EXT_DEGREE_4, FIELD_256_WIDTH_WORDS, FIELD_384_WIDTH_WORDS, FIELD_4096_WIDTH_WORDS},
};

use include_bytes_aligned::include_bytes_aligned;

const MODADD_256_BLOB: &[u8] = include_bytes_aligned!(4, "modadd_256.blob");
const MODADD_384_BLOB: &[u8] = include_bytes_aligned!(4, "modadd_384.blob");
const MODINV_256_BLOB: &[u8] = include_bytes_aligned!(4, "modinv_256.blob");
const MODINV_384_BLOB: &[u8] = include_bytes_aligned!(4, "modinv_384.blob");
const MODMUL_256_BLOB: &[u8] = include_bytes_aligned!(4, "modmul_256.blob");
const MODMUL_384_BLOB: &[u8] = include_bytes_aligned!(4, "modmul_384.blob");
const MODMUL_4096_BLOB: &[u8] = include_bytes_aligned!(4, "modmul_4096.blob");
const MODSUB_256_BLOB: &[u8] = include_bytes_aligned!(4, "modsub_256.blob");
const MODSUB_384_BLOB: &[u8] = include_bytes_aligned!(4, "modsub_384.blob");
const EXTFIELD_DEG2_ADD_256_BLOB: &[u8] = include_bytes_aligned!(4, "extfield_deg2_add_256.blob");
const EXTFIELD_DEG2_ADD_384_BLOB: &[u8] = include_bytes_aligned!(4, "extfield_deg2_add_384.blob");
const EXTFIELD_DEG2_MUL_256_BLOB: &[u8] = include_bytes_aligned!(4, "extfield_deg2_mul_256.blob");
const EXTFIELD_DEG4_MUL_256_BLOB: &[u8] = include_bytes_aligned!(4, "extfield_deg4_mul_256.blob");
const EXTFIELD_DEG2_SUB_256_BLOB: &[u8] = include_bytes_aligned!(4, "extfield_deg2_sub_256.blob");
const EXTFIELD_DEG2_SUB_384_BLOB: &[u8] = include_bytes_aligned!(4, "extfield_deg2_sub_384.blob");
const EXTFIELD_XXONE_MUL_256_BLOB: &[u8] = include_bytes_aligned!(4, "extfield_xxone_mul_256.blob");
const EXTFIELD_XXONE_MUL_384_BLOB: &[u8] = include_bytes_aligned!(4, "extfield_xxone_mul_384.blob");

pub fn modadd_256(
    lhs: &[u32; FIELD_256_WIDTH_WORDS],
    rhs: &[u32; FIELD_256_WIDTH_WORDS],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    unsafe {
        sys_bigint2_4(
            MODADD_256_BLOB.as_ptr(),
            lhs.as_ptr(),
            rhs.as_ptr(),
            modulus.as_ptr(),
            result.as_mut_ptr(),
        );
    }
}

pub fn modadd_384(
    lhs: &[u32; FIELD_384_WIDTH_WORDS],
    rhs: &[u32; FIELD_384_WIDTH_WORDS],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [u32; FIELD_384_WIDTH_WORDS],
) {
    unsafe {
        sys_bigint2_4(
            MODADD_384_BLOB.as_ptr(),
            lhs.as_ptr(),
            rhs.as_ptr(),
            modulus.as_ptr(),
            result.as_mut_ptr(),
        );
    }
}

pub fn modinv_256(
    inp: &[u32; FIELD_256_WIDTH_WORDS],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    unsafe {
        sys_bigint2_3(
            MODINV_256_BLOB.as_ptr(),
            inp.as_ptr(),
            modulus.as_ptr(),
            result.as_mut_ptr(),
        );
    }
}

pub fn modinv_384(
    inp: &[u32; FIELD_384_WIDTH_WORDS],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [u32; FIELD_384_WIDTH_WORDS],
) {
    unsafe {
        sys_bigint2_3(
            MODINV_384_BLOB.as_ptr(),
            inp.as_ptr(),
            modulus.as_ptr(),
            result.as_mut_ptr(),
        );
    }
}

pub fn modmul_256(
    lhs: &[u32; FIELD_256_WIDTH_WORDS],
    rhs: &[u32; FIELD_256_WIDTH_WORDS],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    unsafe {
        sys_bigint2_4(
            MODMUL_256_BLOB.as_ptr(),
            lhs.as_ptr(),
            rhs.as_ptr(),
            modulus.as_ptr(),
            result.as_mut_ptr(),
        );
    }
}

pub fn modmul_384(
    lhs: &[u32; FIELD_384_WIDTH_WORDS],
    rhs: &[u32; FIELD_384_WIDTH_WORDS],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [u32; FIELD_384_WIDTH_WORDS],
) {
    unsafe {
        sys_bigint2_4(
            MODMUL_384_BLOB.as_ptr(),
            lhs.as_ptr(),
            rhs.as_ptr(),
            modulus.as_ptr(),
            result.as_mut_ptr(),
        );
    }
}

pub fn modmul_4096(
    lhs: &[u32; FIELD_4096_WIDTH_WORDS],
    rhs: &[u32; FIELD_4096_WIDTH_WORDS],
    modulus: &[u32; FIELD_4096_WIDTH_WORDS],
    result: &mut [u32; FIELD_4096_WIDTH_WORDS],
) {
    unsafe {
        sys_bigint2_4(
            MODMUL_4096_BLOB.as_ptr(),
            lhs.as_ptr(),
            rhs.as_ptr(),
            modulus.as_ptr(),
            result.as_mut_ptr(),
        );
    }
}

pub fn modsub_256(
    lhs: &[u32; FIELD_256_WIDTH_WORDS],
    rhs: &[u32; FIELD_256_WIDTH_WORDS],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    unsafe {
        sys_bigint2_4(
            MODSUB_256_BLOB.as_ptr(),
            lhs.as_ptr(),
            rhs.as_ptr(),
            modulus.as_ptr(),
            result.as_mut_ptr(),
        );
    }
}

pub fn modsub_384(
    lhs: &[u32; FIELD_384_WIDTH_WORDS],
    rhs: &[u32; FIELD_384_WIDTH_WORDS],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [u32; FIELD_384_WIDTH_WORDS],
) {
    unsafe {
        sys_bigint2_4(
            MODSUB_384_BLOB.as_ptr(),
            lhs.as_ptr(),
            rhs.as_ptr(),
            modulus.as_ptr(),
            result.as_mut_ptr(),
        );
    }
}

pub fn extfield_deg2_add_256(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unsafe {
        sys_bigint2_4(
            EXTFIELD_DEG2_ADD_256_BLOB.as_ptr(),
            lhs.as_ptr() as *const u32,
            rhs.as_ptr() as *const u32,
            modulus.as_ptr(),
            result.as_mut_ptr() as *mut u32,
        );
    }
}

pub fn extfield_deg2_add_384(
    lhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unsafe {
        sys_bigint2_4(
            EXTFIELD_DEG2_ADD_384_BLOB.as_ptr(),
            lhs.as_ptr() as *const u32,
            rhs.as_ptr() as *const u32,
            modulus.as_ptr(),
            result.as_mut_ptr() as *mut u32,
        );
    }
}

pub fn extfield_deg2_mul_256(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    monic_irr: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unsafe {
        sys_bigint2_5(
            EXTFIELD_DEG2_MUL_256_BLOB.as_ptr(),
            lhs.as_ptr() as *const u32,
            rhs.as_ptr() as *const u32,
            monic_irr.as_ptr() as *const u32,
            modulus.as_ptr(),
            result.as_mut_ptr() as *mut u32,
        );
    }
}

pub fn extfield_deg4_mul_256(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_4],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_4],
    monic_irr: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_4],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_4],
) {
    unsafe {
        sys_bigint2_5(
            EXTFIELD_DEG4_MUL_256_BLOB.as_ptr(),
            lhs.as_ptr() as *const u32,
            rhs.as_ptr() as *const u32,
            monic_irr.as_ptr() as *const u32,
            modulus.as_ptr(),
            result.as_mut_ptr() as *mut u32,
        );
    }
}

pub fn extfield_deg2_sub_256(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unsafe {
        sys_bigint2_4(
            EXTFIELD_DEG2_SUB_256_BLOB.as_ptr(),
            lhs.as_ptr() as *const u32,
            rhs.as_ptr() as *const u32,
            modulus.as_ptr(),
            result.as_mut_ptr() as *mut u32,
        );
    }
}

pub fn extfield_deg2_sub_384(
    lhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unsafe {
        sys_bigint2_4(
            EXTFIELD_DEG2_SUB_384_BLOB.as_ptr(),
            lhs.as_ptr() as *const u32,
            rhs.as_ptr() as *const u32,
            modulus.as_ptr(),
            result.as_mut_ptr() as *mut u32,
        );
    }
}

pub fn extfield_xxone_mul_256(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    modsqr: &[u32; 2 * FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unsafe {
        sys_bigint2_5(
            EXTFIELD_XXONE_MUL_256_BLOB.as_ptr(),
            lhs.as_ptr() as *const u32,
            rhs.as_ptr() as *const u32,
            modulus.as_ptr(),
            modsqr.as_ptr(),
            result.as_mut_ptr() as *mut u32,
        );
    }
}

pub fn extfield_xxone_mul_384(
    lhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    modsqr: &[u32; 2 * FIELD_384_WIDTH_WORDS],
    result: &mut [[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unsafe {
        sys_bigint2_5(
            EXTFIELD_XXONE_MUL_384_BLOB.as_ptr(),
            lhs.as_ptr() as *const u32,
            rhs.as_ptr() as *const u32,
            modulus.as_ptr(),
            modsqr.as_ptr(),
            result.as_mut_ptr() as *mut u32,
        );
    }
}
