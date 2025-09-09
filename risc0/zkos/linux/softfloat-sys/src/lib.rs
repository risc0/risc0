// SPDX-License-Identifier: BSD-3-Clause
// See Notices.txt for copyright information
#![cfg_attr(not(test), no_std)]
#![allow(non_snake_case, non_camel_case_types, non_upper_case_globals)]

// Define C99 integer types directly for no_std compatibility
pub type int_fast8_t = i8;
pub type int_fast16_t = i16;
pub type int_fast32_t = i32;
pub type int_fast64_t = i64;
pub type uint_fast8_t = u8;
pub type uint_fast16_t = u16;
pub type uint_fast32_t = u32;
pub type uint_fast64_t = u64;

extern "C" {
    pub fn softfloat_detectTininess_read_helper() -> uint_fast8_t;
    pub fn softfloat_detectTininess_write_helper(v: uint_fast8_t);
    pub fn softfloat_roundingMode_read_helper() -> uint_fast8_t;
    pub fn softfloat_roundingMode_write_helper(v: uint_fast8_t);
    pub fn softfloat_exceptionFlags_read_helper() -> uint_fast8_t;
    pub fn softfloat_exceptionFlags_write_helper(v: uint_fast8_t);
    pub fn extF80_roundingPrecision_read_helper() -> uint_fast8_t;
    pub fn extF80_roundingPrecision_write_helper(v: uint_fast8_t);
}

#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct bfloat16_t {
    pub v: u16,
}

#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct float16_t {
    pub v: u16,
}

#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct float32_t {
    pub v: u32,
}

#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct float64_t {
    pub v: u64,
}

#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct float128_t {
    pub v: [u64; 2],
}

#[cfg(target_endian = "little")]
#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct extFloat80M {
    pub signif: u64,
    pub signExp: u16,
}

#[cfg(target_endian = "big")]
#[derive(Copy, Clone, Debug)]
#[repr(C)]
pub struct extFloat80M {
    pub signExp: u16,
    pub signif: u64,
}

pub type extFloat80_t = extFloat80M;

pub const softfloat_tininess_beforeRounding: u8 = 0;
pub const softfloat_tininess_afterRounding: u8 = 1;

pub const softfloat_round_near_even: u8 = 0;
pub const softfloat_round_minMag: u8 = 1;
pub const softfloat_round_min: u8 = 2;
pub const softfloat_round_max: u8 = 3;
pub const softfloat_round_near_maxMag: u8 = 4;
pub const softfloat_round_odd: u8 = 6;

pub const softfloat_flag_inexact: u8 = 1;
pub const softfloat_flag_underflow: u8 = 2;
pub const softfloat_flag_overflow: u8 = 4;
pub const softfloat_flag_infinite: u8 = 8;
pub const softfloat_flag_invalid: u8 = 16;

extern "C" {
    pub fn softfloat_raiseFlags(_: uint_fast8_t);

    pub fn ui32_to_f16(_: u32) -> float16_t;
    pub fn ui32_to_f32(_: u32) -> float32_t;
    pub fn ui32_to_f64(_: u32) -> float64_t;
    pub fn ui32_to_extF80(_: u32) -> extFloat80_t;
    pub fn ui32_to_f128(_: u32) -> float128_t;
    pub fn ui32_to_extF80M(_: u32, _: *mut extFloat80_t);
    pub fn ui32_to_f128M(_: u32, _: *mut float128_t);
    pub fn ui64_to_f16(_: u64) -> float16_t;
    pub fn ui64_to_f32(_: u64) -> float32_t;
    pub fn ui64_to_f64(_: u64) -> float64_t;
    pub fn ui64_to_extF80(_: u64) -> extFloat80_t;
    pub fn ui64_to_f128(_: u64) -> float128_t;

    pub fn ui64_to_extF80M(_: u64, _: *mut extFloat80_t);
    pub fn ui64_to_f128M(_: u64, _: *mut float128_t);
    pub fn i32_to_f16(_: i32) -> float16_t;
    pub fn i32_to_f32(_: i32) -> float32_t;
    pub fn i32_to_f64(_: i32) -> float64_t;
    pub fn i32_to_extF80(_: i32) -> extFloat80_t;
    pub fn i32_to_f128(_: i32) -> float128_t;

    pub fn i32_to_extF80M(_: i32, _: *mut extFloat80_t);
    pub fn i32_to_f128M(_: i32, _: *mut float128_t);
    pub fn i64_to_f16(_: i64) -> float16_t;
    pub fn i64_to_f32(_: i64) -> float32_t;
    pub fn i64_to_f64(_: i64) -> float64_t;
    pub fn i64_to_extF80(_: i64) -> extFloat80_t;
    pub fn i64_to_f128(_: i64) -> float128_t;

    pub fn i64_to_extF80M(_: i64, _: *mut extFloat80_t);
    pub fn i64_to_f128M(_: i64, _: *mut float128_t);

    pub fn bf16_to_f32(_: bfloat16_t) -> float32_t;
    pub fn bf16_isSignalingNaN(_: bfloat16_t) -> bool;

    pub fn f16_to_ui32(_: float16_t, _: uint_fast8_t, _: bool) -> uint_fast32_t;
    pub fn f16_to_ui64(_: float16_t, _: uint_fast8_t, _: bool) -> uint_fast64_t;
    pub fn f16_to_i32(_: float16_t, _: uint_fast8_t, _: bool) -> int_fast32_t;
    pub fn f16_to_i64(_: float16_t, _: uint_fast8_t, _: bool) -> int_fast64_t;
    pub fn f16_to_ui32_r_minMag(_: float16_t, _: bool) -> uint_fast32_t;
    pub fn f16_to_ui64_r_minMag(_: float16_t, _: bool) -> uint_fast64_t;
    pub fn f16_to_i32_r_minMag(_: float16_t, _: bool) -> int_fast32_t;
    pub fn f16_to_i64_r_minMag(_: float16_t, _: bool) -> int_fast64_t;
    pub fn f16_to_f32(_: float16_t) -> float32_t;
    pub fn f16_to_f64(_: float16_t) -> float64_t;
    pub fn f16_to_extF80(_: float16_t) -> extFloat80_t;
    pub fn f16_to_f128(_: float16_t) -> float128_t;

    pub fn f16_to_extF80M(_: float16_t, _: *mut extFloat80_t);
    pub fn f16_to_f128M(_: float16_t, _: *mut float128_t);
    pub fn f16_roundToInt(_: float16_t, _: uint_fast8_t, _: bool) -> float16_t;
    pub fn f16_add(_: float16_t, _: float16_t) -> float16_t;
    pub fn f16_sub(_: float16_t, _: float16_t) -> float16_t;
    pub fn f16_mul(_: float16_t, _: float16_t) -> float16_t;
    pub fn f16_mulAdd(_: float16_t, _: float16_t, _: float16_t) -> float16_t;
    pub fn f16_div(_: float16_t, _: float16_t) -> float16_t;
    pub fn f16_rem(_: float16_t, _: float16_t) -> float16_t;
    pub fn f16_sqrt(_: float16_t) -> float16_t;
    pub fn f16_eq(_: float16_t, _: float16_t) -> bool;
    pub fn f16_le(_: float16_t, _: float16_t) -> bool;
    pub fn f16_lt(_: float16_t, _: float16_t) -> bool;
    pub fn f16_eq_signaling(_: float16_t, _: float16_t) -> bool;
    pub fn f16_le_quiet(_: float16_t, _: float16_t) -> bool;
    pub fn f16_lt_quiet(_: float16_t, _: float16_t) -> bool;
    pub fn f16_isSignalingNaN(_: float16_t) -> bool;

    pub fn f32_to_ui32(_: float32_t, _: uint_fast8_t, _: bool) -> uint_fast32_t;
    pub fn f32_to_ui64(_: float32_t, _: uint_fast8_t, _: bool) -> uint_fast64_t;
    pub fn f32_to_i32(_: float32_t, _: uint_fast8_t, _: bool) -> int_fast32_t;
    pub fn f32_to_i64(_: float32_t, _: uint_fast8_t, _: bool) -> int_fast64_t;
    pub fn f32_to_ui32_r_minMag(_: float32_t, _: bool) -> uint_fast32_t;
    pub fn f32_to_ui64_r_minMag(_: float32_t, _: bool) -> uint_fast64_t;
    pub fn f32_to_i32_r_minMag(_: float32_t, _: bool) -> int_fast32_t;
    pub fn f32_to_i64_r_minMag(_: float32_t, _: bool) -> int_fast64_t;
    pub fn f32_to_bf16(_: float32_t) -> bfloat16_t;
    pub fn f32_to_f16(_: float32_t) -> float16_t;
    pub fn f32_to_f64(_: float32_t) -> float64_t;
    pub fn f32_to_extF80(_: float32_t) -> extFloat80_t;
    pub fn f32_to_f128(_: float32_t) -> float128_t;

    pub fn f32_to_extF80M(_: float32_t, _: *mut extFloat80_t);
    pub fn f32_to_f128M(_: float32_t, _: *mut float128_t);
    pub fn f32_roundToInt(_: float32_t, _: uint_fast8_t, _: bool) -> float32_t;
    pub fn f32_add(_: float32_t, _: float32_t) -> float32_t;
    pub fn f32_sub(_: float32_t, _: float32_t) -> float32_t;
    pub fn f32_mul(_: float32_t, _: float32_t) -> float32_t;
    pub fn f32_mulAdd(_: float32_t, _: float32_t, _: float32_t) -> float32_t;
    pub fn f32_div(_: float32_t, _: float32_t) -> float32_t;
    pub fn f32_rem(_: float32_t, _: float32_t) -> float32_t;
    pub fn f32_sqrt(_: float32_t) -> float32_t;
    pub fn f32_eq(_: float32_t, _: float32_t) -> bool;
    pub fn f32_le(_: float32_t, _: float32_t) -> bool;
    pub fn f32_lt(_: float32_t, _: float32_t) -> bool;
    pub fn f32_eq_signaling(_: float32_t, _: float32_t) -> bool;
    pub fn f32_le_quiet(_: float32_t, _: float32_t) -> bool;
    pub fn f32_lt_quiet(_: float32_t, _: float32_t) -> bool;
    pub fn f32_isSignalingNaN(_: float32_t) -> bool;

    pub fn f64_to_ui32(_: float64_t, _: uint_fast8_t, _: bool) -> uint_fast32_t;
    pub fn f64_to_ui64(_: float64_t, _: uint_fast8_t, _: bool) -> uint_fast64_t;
    pub fn f64_to_i32(_: float64_t, _: uint_fast8_t, _: bool) -> int_fast32_t;
    pub fn f64_to_i64(_: float64_t, _: uint_fast8_t, _: bool) -> int_fast64_t;
    pub fn f64_to_ui32_r_minMag(_: float64_t, _: bool) -> uint_fast32_t;
    pub fn f64_to_ui64_r_minMag(_: float64_t, _: bool) -> uint_fast64_t;
    pub fn f64_to_i32_r_minMag(_: float64_t, _: bool) -> int_fast32_t;
    pub fn f64_to_i64_r_minMag(_: float64_t, _: bool) -> int_fast64_t;
    pub fn f64_to_f16(_: float64_t) -> float16_t;
    pub fn f64_to_f32(_: float64_t) -> float32_t;
    pub fn f64_to_extF80(_: float64_t) -> extFloat80_t;
    pub fn f64_to_f128(_: float64_t) -> float128_t;

    pub fn f64_to_extF80M(_: float64_t, _: *mut extFloat80_t);
    pub fn f64_to_f128M(_: float64_t, _: *mut float128_t);
    pub fn f64_roundToInt(_: float64_t, _: uint_fast8_t, _: bool) -> float64_t;
    pub fn f64_add(_: float64_t, _: float64_t) -> float64_t;
    pub fn f64_sub(_: float64_t, _: float64_t) -> float64_t;
    pub fn f64_mul(_: float64_t, _: float64_t) -> float64_t;
    pub fn f64_mulAdd(_: float64_t, _: float64_t, _: float64_t) -> float64_t;
    pub fn f64_div(_: float64_t, _: float64_t) -> float64_t;
    pub fn f64_rem(_: float64_t, _: float64_t) -> float64_t;
    pub fn f64_sqrt(_: float64_t) -> float64_t;
    pub fn f64_eq(_: float64_t, _: float64_t) -> bool;
    pub fn f64_le(_: float64_t, _: float64_t) -> bool;
    pub fn f64_lt(_: float64_t, _: float64_t) -> bool;
    pub fn f64_eq_signaling(_: float64_t, _: float64_t) -> bool;
    pub fn f64_le_quiet(_: float64_t, _: float64_t) -> bool;
    pub fn f64_lt_quiet(_: float64_t, _: float64_t) -> bool;
    pub fn f64_isSignalingNaN(_: float64_t) -> bool;

    pub fn extF80_to_ui32(_: extFloat80_t, _: uint_fast8_t, _: bool) -> uint_fast32_t;
    pub fn extF80_to_ui64(_: extFloat80_t, _: uint_fast8_t, _: bool) -> uint_fast64_t;
    pub fn extF80_to_i32(_: extFloat80_t, _: uint_fast8_t, _: bool) -> int_fast32_t;
    pub fn extF80_to_i64(_: extFloat80_t, _: uint_fast8_t, _: bool) -> int_fast64_t;
    pub fn extF80_to_ui32_r_minMag(_: extFloat80_t, _: bool) -> uint_fast32_t;
    pub fn extF80_to_ui64_r_minMag(_: extFloat80_t, _: bool) -> uint_fast64_t;
    pub fn extF80_to_i32_r_minMag(_: extFloat80_t, _: bool) -> int_fast32_t;
    pub fn extF80_to_i64_r_minMag(_: extFloat80_t, _: bool) -> int_fast64_t;
    pub fn extF80_to_f16(_: extFloat80_t) -> float16_t;
    pub fn extF80_to_f32(_: extFloat80_t) -> float32_t;
    pub fn extF80_to_f64(_: extFloat80_t) -> float64_t;
    pub fn extF80_to_f128(_: extFloat80_t) -> float128_t;
    pub fn extF80_roundToInt(_: extFloat80_t, _: uint_fast8_t, _: bool) -> extFloat80_t;
    pub fn extF80_add(_: extFloat80_t, _: extFloat80_t) -> extFloat80_t;
    pub fn extF80_sub(_: extFloat80_t, _: extFloat80_t) -> extFloat80_t;
    pub fn extF80_mul(_: extFloat80_t, _: extFloat80_t) -> extFloat80_t;
    pub fn extF80_div(_: extFloat80_t, _: extFloat80_t) -> extFloat80_t;
    pub fn extF80_rem(_: extFloat80_t, _: extFloat80_t) -> extFloat80_t;
    pub fn extF80_sqrt(_: extFloat80_t) -> extFloat80_t;
    pub fn extF80_eq(_: extFloat80_t, _: extFloat80_t) -> bool;
    pub fn extF80_le(_: extFloat80_t, _: extFloat80_t) -> bool;
    pub fn extF80_lt(_: extFloat80_t, _: extFloat80_t) -> bool;
    pub fn extF80_eq_signaling(_: extFloat80_t, _: extFloat80_t) -> bool;
    pub fn extF80_le_quiet(_: extFloat80_t, _: extFloat80_t) -> bool;
    pub fn extF80_lt_quiet(_: extFloat80_t, _: extFloat80_t) -> bool;
    pub fn extF80_isSignalingNaN(_: extFloat80_t) -> bool;

    pub fn extF80M_to_ui32(_: *const extFloat80_t, _: uint_fast8_t, _: bool) -> uint_fast32_t;
    pub fn extF80M_to_ui64(_: *const extFloat80_t, _: uint_fast8_t, _: bool) -> uint_fast64_t;
    pub fn extF80M_to_i32(_: *const extFloat80_t, _: uint_fast8_t, _: bool) -> int_fast32_t;
    pub fn extF80M_to_i64(_: *const extFloat80_t, _: uint_fast8_t, _: bool) -> int_fast64_t;
    pub fn extF80M_to_ui32_r_minMag(_: *const extFloat80_t, _: bool) -> uint_fast32_t;
    pub fn extF80M_to_ui64_r_minMag(_: *const extFloat80_t, _: bool) -> uint_fast64_t;
    pub fn extF80M_to_i32_r_minMag(_: *const extFloat80_t, _: bool) -> int_fast32_t;
    pub fn extF80M_to_i64_r_minMag(_: *const extFloat80_t, _: bool) -> int_fast64_t;
    pub fn extF80M_to_f16(_: *const extFloat80_t) -> float16_t;
    pub fn extF80M_to_f32(_: *const extFloat80_t) -> float32_t;
    pub fn extF80M_to_f64(_: *const extFloat80_t) -> float64_t;
    pub fn extF80M_to_f128M(_: *const extFloat80_t, _: *mut float128_t);
    pub fn extF80M_roundToInt(
        _: *const extFloat80_t,
        _: uint_fast8_t,
        _: bool,
        _: *mut extFloat80_t,
    );
    pub fn extF80M_add(_: *const extFloat80_t, _: *const extFloat80_t, _: *mut extFloat80_t);
    pub fn extF80M_sub(_: *const extFloat80_t, _: *const extFloat80_t, _: *mut extFloat80_t);
    pub fn extF80M_mul(_: *const extFloat80_t, _: *const extFloat80_t, _: *mut extFloat80_t);
    pub fn extF80M_div(_: *const extFloat80_t, _: *const extFloat80_t, _: *mut extFloat80_t);
    pub fn extF80M_rem(_: *const extFloat80_t, _: *const extFloat80_t, _: *mut extFloat80_t);
    pub fn extF80M_sqrt(_: *const extFloat80_t, _: *mut extFloat80_t);
    pub fn extF80M_eq(_: *const extFloat80_t, _: *const extFloat80_t) -> bool;
    pub fn extF80M_le(_: *const extFloat80_t, _: *const extFloat80_t) -> bool;
    pub fn extF80M_lt(_: *const extFloat80_t, _: *const extFloat80_t) -> bool;
    pub fn extF80M_eq_signaling(_: *const extFloat80_t, _: *const extFloat80_t) -> bool;
    pub fn extF80M_le_quiet(_: *const extFloat80_t, _: *const extFloat80_t) -> bool;
    pub fn extF80M_lt_quiet(_: *const extFloat80_t, _: *const extFloat80_t) -> bool;
    pub fn extF80M_isSignalingNaN(_: *const extFloat80_t) -> bool;

    pub fn f128_to_ui32(_: float128_t, _: uint_fast8_t, _: bool) -> uint_fast32_t;
    pub fn f128_to_ui64(_: float128_t, _: uint_fast8_t, _: bool) -> uint_fast64_t;
    pub fn f128_to_i32(_: float128_t, _: uint_fast8_t, _: bool) -> int_fast32_t;
    pub fn f128_to_i64(_: float128_t, _: uint_fast8_t, _: bool) -> int_fast64_t;
    pub fn f128_to_ui32_r_minMag(_: float128_t, _: bool) -> uint_fast32_t;
    pub fn f128_to_ui64_r_minMag(_: float128_t, _: bool) -> uint_fast64_t;
    pub fn f128_to_i32_r_minMag(_: float128_t, _: bool) -> int_fast32_t;
    pub fn f128_to_i64_r_minMag(_: float128_t, _: bool) -> int_fast64_t;
    pub fn f128_to_f16(_: float128_t) -> float16_t;
    pub fn f128_to_f32(_: float128_t) -> float32_t;
    pub fn f128_to_f64(_: float128_t) -> float64_t;
    pub fn f128_to_extF80(_: float128_t) -> extFloat80_t;
    pub fn f128_roundToInt(_: float128_t, _: uint_fast8_t, _: bool) -> float128_t;
    pub fn f128_add(_: float128_t, _: float128_t) -> float128_t;
    pub fn f128_sub(_: float128_t, _: float128_t) -> float128_t;
    pub fn f128_mul(_: float128_t, _: float128_t) -> float128_t;
    pub fn f128_mulAdd(_: float128_t, _: float128_t, _: float128_t) -> float128_t;
    pub fn f128_div(_: float128_t, _: float128_t) -> float128_t;
    pub fn f128_rem(_: float128_t, _: float128_t) -> float128_t;
    pub fn f128_sqrt(_: float128_t) -> float128_t;
    pub fn f128_eq(_: float128_t, _: float128_t) -> bool;
    pub fn f128_le(_: float128_t, _: float128_t) -> bool;
    pub fn f128_lt(_: float128_t, _: float128_t) -> bool;
    pub fn f128_eq_signaling(_: float128_t, _: float128_t) -> bool;
    pub fn f128_le_quiet(_: float128_t, _: float128_t) -> bool;
    pub fn f128_lt_quiet(_: float128_t, _: float128_t) -> bool;
    pub fn f128_isSignalingNaN(_: float128_t) -> bool;

    pub fn f128M_to_ui32(_: *const float128_t, _: uint_fast8_t, _: bool) -> uint_fast32_t;
    pub fn f128M_to_ui64(_: *const float128_t, _: uint_fast8_t, _: bool) -> uint_fast64_t;
    pub fn f128M_to_i32(_: *const float128_t, _: uint_fast8_t, _: bool) -> int_fast32_t;
    pub fn f128M_to_i64(_: *const float128_t, _: uint_fast8_t, _: bool) -> int_fast64_t;
    pub fn f128M_to_ui32_r_minMag(_: *const float128_t, _: bool) -> uint_fast32_t;
    pub fn f128M_to_ui64_r_minMag(_: *const float128_t, _: bool) -> uint_fast64_t;
    pub fn f128M_to_i32_r_minMag(_: *const float128_t, _: bool) -> int_fast32_t;
    pub fn f128M_to_i64_r_minMag(_: *const float128_t, _: bool) -> int_fast64_t;
    pub fn f128M_to_f16(_: *const float128_t) -> float16_t;
    pub fn f128M_to_f32(_: *const float128_t) -> float32_t;
    pub fn f128M_to_f64(_: *const float128_t) -> float64_t;
    pub fn f128M_to_extF80M(_: *const float128_t, _: *mut extFloat80_t);
    pub fn f128M_roundToInt(_: *const float128_t, _: uint_fast8_t, _: bool, _: *mut float128_t);
    pub fn f128M_add(_: *const float128_t, _: *const float128_t, _: *mut float128_t);
    pub fn f128M_sub(_: *const float128_t, _: *const float128_t, _: *mut float128_t);
    pub fn f128M_mul(_: *const float128_t, _: *const float128_t, _: *mut float128_t);
    pub fn f128M_mulAdd(
        _: *const float128_t,
        _: *const float128_t,
        _: *const float128_t,
        _: *mut float128_t,
    );
    pub fn f128M_div(_: *const float128_t, _: *const float128_t, _: *mut float128_t);
    pub fn f128M_rem(_: *const float128_t, _: *const float128_t, _: *mut float128_t);
    pub fn f128M_sqrt(_: *const float128_t, _: *mut float128_t);
    pub fn f128M_eq(_: *const float128_t, _: *const float128_t) -> bool;
    pub fn f128M_le(_: *const float128_t, _: *const float128_t) -> bool;
    pub fn f128M_lt(_: *const float128_t, _: *const float128_t) -> bool;
    pub fn f128M_eq_signaling(_: *const float128_t, _: *const float128_t) -> bool;
    pub fn f128M_le_quiet(_: *const float128_t, _: *const float128_t) -> bool;
    pub fn f128M_lt_quiet(_: *const float128_t, _: *const float128_t) -> bool;
    pub fn f128M_isSignalingNaN(_: *const float128_t) -> bool;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_linking() {
        macro_rules! link_functions {
            ($($name:ident,)*) => {
                $(println!(concat!(stringify!($name), ": {:#X}"), $name as usize);)*
            };
        }
        link_functions!(
            softfloat_detectTininess_read_helper,
            softfloat_detectTininess_write_helper,
            softfloat_roundingMode_read_helper,
            softfloat_roundingMode_write_helper,
            softfloat_exceptionFlags_read_helper,
            softfloat_exceptionFlags_write_helper,
            extF80_roundingPrecision_read_helper,
            extF80_roundingPrecision_write_helper,
            softfloat_raiseFlags,
            ui32_to_f16,
            ui32_to_f32,
            ui32_to_f64,
            ui32_to_extF80,
            ui32_to_f128,
            ui32_to_extF80M,
            ui32_to_f128M,
            ui64_to_f16,
            ui64_to_f32,
            ui64_to_f64,
            ui64_to_extF80,
            ui64_to_f128,
            ui64_to_extF80M,
            ui64_to_f128M,
            i32_to_f16,
            i32_to_f32,
            i32_to_f64,
            i32_to_extF80,
            i32_to_f128,
            i32_to_extF80M,
            i32_to_f128M,
            i64_to_f16,
            i64_to_f32,
            i64_to_f64,
            i64_to_extF80,
            i64_to_f128,
            i64_to_extF80M,
            i64_to_f128M,
            bf16_to_f32,
            bf16_isSignalingNaN,
            f16_to_ui32,
            f16_to_ui64,
            f16_to_i32,
            f16_to_i64,
            f16_to_ui32_r_minMag,
            f16_to_ui64_r_minMag,
            f16_to_i32_r_minMag,
            f16_to_i64_r_minMag,
            f16_to_f32,
            f16_to_f64,
            f16_to_extF80,
            f16_to_f128,
            f16_to_extF80M,
            f16_to_f128M,
            f16_roundToInt,
            f16_add,
            f16_sub,
            f16_mul,
            f16_mulAdd,
            f16_div,
            f16_rem,
            f16_sqrt,
            f16_eq,
            f16_le,
            f16_lt,
            f16_eq_signaling,
            f16_le_quiet,
            f16_lt_quiet,
            f16_isSignalingNaN,
            f32_to_ui32,
            f32_to_ui64,
            f32_to_i32,
            f32_to_i64,
            f32_to_ui32_r_minMag,
            f32_to_ui64_r_minMag,
            f32_to_i32_r_minMag,
            f32_to_i64_r_minMag,
            f32_to_bf16,
            f32_to_f16,
            f32_to_f64,
            f32_to_extF80,
            f32_to_f128,
            f32_to_extF80M,
            f32_to_f128M,
            f32_roundToInt,
            f32_add,
            f32_sub,
            f32_mul,
            f32_mulAdd,
            f32_div,
            f32_rem,
            f32_sqrt,
            f32_eq,
            f32_le,
            f32_lt,
            f32_eq_signaling,
            f32_le_quiet,
            f32_lt_quiet,
            f32_isSignalingNaN,
            f64_to_ui32,
            f64_to_ui64,
            f64_to_i32,
            f64_to_i64,
            f64_to_ui32_r_minMag,
            f64_to_ui64_r_minMag,
            f64_to_i32_r_minMag,
            f64_to_i64_r_minMag,
            f64_to_f16,
            f64_to_f32,
            f64_to_extF80,
            f64_to_f128,
            f64_to_extF80M,
            f64_to_f128M,
            f64_roundToInt,
            f64_add,
            f64_sub,
            f64_mul,
            f64_mulAdd,
            f64_div,
            f64_rem,
            f64_sqrt,
            f64_eq,
            f64_le,
            f64_lt,
            f64_eq_signaling,
            f64_le_quiet,
            f64_lt_quiet,
            f64_isSignalingNaN,
            extF80_to_ui32,
            extF80_to_ui64,
            extF80_to_i32,
            extF80_to_i64,
            extF80_to_ui32_r_minMag,
            extF80_to_ui64_r_minMag,
            extF80_to_i32_r_minMag,
            extF80_to_i64_r_minMag,
            extF80_to_f16,
            extF80_to_f32,
            extF80_to_f64,
            extF80_to_f128,
            extF80_roundToInt,
            extF80_add,
            extF80_sub,
            extF80_mul,
            extF80_div,
            extF80_rem,
            extF80_sqrt,
            extF80_eq,
            extF80_le,
            extF80_lt,
            extF80_eq_signaling,
            extF80_le_quiet,
            extF80_lt_quiet,
            extF80_isSignalingNaN,
            extF80M_to_ui32,
            extF80M_to_ui64,
            extF80M_to_i32,
            extF80M_to_i64,
            extF80M_to_ui32_r_minMag,
            extF80M_to_ui64_r_minMag,
            extF80M_to_i32_r_minMag,
            extF80M_to_i64_r_minMag,
            extF80M_to_f16,
            extF80M_to_f32,
            extF80M_to_f64,
            extF80M_to_f128M,
            extF80M_roundToInt,
            extF80M_add,
            extF80M_sub,
            extF80M_mul,
            extF80M_div,
            extF80M_rem,
            extF80M_sqrt,
            extF80M_eq,
            extF80M_le,
            extF80M_lt,
            extF80M_eq_signaling,
            extF80M_le_quiet,
            extF80M_lt_quiet,
            extF80M_isSignalingNaN,
            f128_to_ui32,
            f128_to_ui64,
            f128_to_i32,
            f128_to_i64,
            f128_to_ui32_r_minMag,
            f128_to_ui64_r_minMag,
            f128_to_i32_r_minMag,
            f128_to_i64_r_minMag,
            f128_to_f16,
            f128_to_f32,
            f128_to_f64,
            f128_to_extF80,
            f128_roundToInt,
            f128_add,
            f128_sub,
            f128_mul,
            f128_mulAdd,
            f128_div,
            f128_rem,
            f128_sqrt,
            f128_eq,
            f128_le,
            f128_lt,
            f128_eq_signaling,
            f128_le_quiet,
            f128_lt_quiet,
            f128_isSignalingNaN,
            f128M_to_ui32,
            f128M_to_ui64,
            f128M_to_i32,
            f128M_to_i64,
            f128M_to_ui32_r_minMag,
            f128M_to_ui64_r_minMag,
            f128M_to_i32_r_minMag,
            f128M_to_i64_r_minMag,
            f128M_to_f16,
            f128M_to_f32,
            f128M_to_f64,
            f128M_to_extF80M,
            f128M_roundToInt,
            f128M_add,
            f128M_sub,
            f128M_mul,
            f128M_mulAdd,
            f128M_div,
            f128M_rem,
            f128M_sqrt,
            f128M_eq,
            f128M_le,
            f128M_lt,
            f128M_eq_signaling,
            f128M_le_quiet,
            f128M_lt_quiet,
            f128M_isSignalingNaN,
        );
    }
}
