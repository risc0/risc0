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

use crate::field::*;

#[no_mangle]
pub extern "C" fn risc0_bigint_modadd_256_unchecked(
    lhs: &[u32; FIELD_256_WIDTH_WORDS],
    rhs: &[u32; FIELD_256_WIDTH_WORDS],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    unchecked::modadd_256(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_modadd_384_unchecked(
    lhs: &[u32; FIELD_384_WIDTH_WORDS],
    rhs: &[u32; FIELD_384_WIDTH_WORDS],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [u32; FIELD_384_WIDTH_WORDS],
) {
    unchecked::modadd_384(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_modinv_256_unchecked(
    inp: &[u32; FIELD_256_WIDTH_WORDS],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    unchecked::modinv_256(inp, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_modinv_384_unchecked(
    inp: &[u32; FIELD_384_WIDTH_WORDS],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [u32; FIELD_384_WIDTH_WORDS],
) {
    unchecked::modinv_384(inp, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_modmul_256_unchecked(
    lhs: &[u32; FIELD_256_WIDTH_WORDS],
    rhs: &[u32; FIELD_256_WIDTH_WORDS],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    unchecked::modmul_256(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_modmul_384_unchecked(
    lhs: &[u32; FIELD_384_WIDTH_WORDS],
    rhs: &[u32; FIELD_384_WIDTH_WORDS],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [u32; FIELD_384_WIDTH_WORDS],
) {
    unchecked::modmul_384(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_modsub_256_unchecked(
    lhs: &[u32; FIELD_256_WIDTH_WORDS],
    rhs: &[u32; FIELD_256_WIDTH_WORDS],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    unchecked::modsub_256(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_modsub_384_unchecked(
    lhs: &[u32; FIELD_384_WIDTH_WORDS],
    rhs: &[u32; FIELD_384_WIDTH_WORDS],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [u32; FIELD_384_WIDTH_WORDS],
) {
    unchecked::modsub_384(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_extfield_deg2_add_256_unchecked(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unchecked::extfield_deg2_add_256(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_extfield_deg2_add_384_unchecked(
    lhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unchecked::extfield_deg2_add_384(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_extfield_deg2_sub_256_unchecked(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unchecked::extfield_deg2_sub_256(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_extfield_deg2_sub_384_unchecked(
    lhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unchecked::extfield_deg2_sub_384(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_extfield_xxone_mul_256_unchecked(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    modsqr: &[u32; 2 * FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unchecked::extfield_xxone_mul_256(lhs, rhs, modulus, modsqr, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_extfield_xxone_mul_384_unchecked(
    lhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    modsqr: &[u32; 2 * FIELD_384_WIDTH_WORDS],
    result: &mut [[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    unchecked::extfield_xxone_mul_384(lhs, rhs, modulus, modsqr, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_modadd_256(
    lhs: &[u32; FIELD_256_WIDTH_WORDS],
    rhs: &[u32; FIELD_256_WIDTH_WORDS],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    modadd_256(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_modadd_384(
    lhs: &[u32; FIELD_384_WIDTH_WORDS],
    rhs: &[u32; FIELD_384_WIDTH_WORDS],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [u32; FIELD_384_WIDTH_WORDS],
) {
    modadd_384(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_modinv_256(
    inp: &[u32; FIELD_256_WIDTH_WORDS],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    modinv_256(inp, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_modinv_384(
    inp: &[u32; FIELD_384_WIDTH_WORDS],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [u32; FIELD_384_WIDTH_WORDS],
) {
    modinv_384(inp, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_modmul_256(
    lhs: &[u32; FIELD_256_WIDTH_WORDS],
    rhs: &[u32; FIELD_256_WIDTH_WORDS],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    modmul_256(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_modmul_384(
    lhs: &[u32; FIELD_384_WIDTH_WORDS],
    rhs: &[u32; FIELD_384_WIDTH_WORDS],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [u32; FIELD_384_WIDTH_WORDS],
) {
    modmul_384(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_modsub_256(
    lhs: &[u32; FIELD_256_WIDTH_WORDS],
    rhs: &[u32; FIELD_256_WIDTH_WORDS],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [u32; FIELD_256_WIDTH_WORDS],
) {
    modsub_256(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_modsub_384(
    lhs: &[u32; FIELD_384_WIDTH_WORDS],
    rhs: &[u32; FIELD_384_WIDTH_WORDS],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [u32; FIELD_384_WIDTH_WORDS],
) {
    modsub_384(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_extfield_deg2_add_256(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    extfield_deg2_add_256(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_extfield_deg2_add_384(
    lhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    extfield_deg2_add_384(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_extfield_deg2_sub_256(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    extfield_deg2_sub_256(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_extfield_deg2_sub_384(
    lhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    result: &mut [[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    extfield_deg2_sub_384(lhs, rhs, modulus, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_extfield_xxone_mul_256(
    lhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_256_WIDTH_WORDS],
    modsqr: &[u32; 2 * FIELD_256_WIDTH_WORDS],
    result: &mut [[u32; FIELD_256_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    extfield_xxone_mul_256(lhs, rhs, modulus, modsqr, result);
}

#[no_mangle]
pub extern "C" fn risc0_bigint_extfield_xxone_mul_384(
    lhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    rhs: &[[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
    modulus: &[u32; FIELD_384_WIDTH_WORDS],
    modsqr: &[u32; 2 * FIELD_384_WIDTH_WORDS],
    result: &mut [[u32; FIELD_384_WIDTH_WORDS]; EXT_DEGREE_2],
) {
    extfield_xxone_mul_384(lhs, rhs, modulus, modsqr, result);
}
