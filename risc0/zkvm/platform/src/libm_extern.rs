// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! Export symbols for math functions from libm to the global namespace.

#![allow(dead_code)]

#[unsafe(no_mangle)]
pub extern "C" fn acosf(x: f32) -> f32 {
    libm::acosf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn acoshf(x: f32) -> f32 {
    libm::acoshf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn acosh(x: f64) -> f64 {
    libm::acosh(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn acos(x: f64) -> f64 {
    libm::acos(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn asinf(x: f32) -> f32 {
    libm::asinf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn asinhf(x: f32) -> f32 {
    libm::asinhf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn asinh(x: f64) -> f64 {
    libm::asinh(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn asin(x: f64) -> f64 {
    libm::asin(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn atan2f(y: f32, x: f32) -> f32 {
    libm::atan2f(y, x)
}

#[unsafe(no_mangle)]
pub extern "C" fn atan2(y: f64, x: f64) -> f64 {
    libm::atan2(y, x)
}

#[unsafe(no_mangle)]
pub extern "C" fn atanf(x: f32) -> f32 {
    libm::atanf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn atanhf(x: f32) -> f32 {
    libm::atanhf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn atanh(x: f64) -> f64 {
    libm::atanh(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn atan(x: f64) -> f64 {
    libm::atan(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn cbrtf(x: f32) -> f32 {
    libm::cbrtf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn cbrt(x: f64) -> f64 {
    libm::cbrt(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn ceilf(x: f32) -> f32 {
    libm::ceilf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn ceil(x: f64) -> f64 {
    libm::ceil(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn copysignf(x: f32, y: f32) -> f32 {
    libm::copysignf(x, y)
}

#[unsafe(no_mangle)]
pub extern "C" fn copysign(x: f64, y: f64) -> f64 {
    libm::copysign(x, y)
}

#[unsafe(no_mangle)]
pub extern "C" fn cosf(x: f32) -> f32 {
    libm::cosf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn coshf(x: f32) -> f32 {
    libm::coshf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn cosh(x: f64) -> f64 {
    libm::cosh(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn cos(x: f64) -> f64 {
    libm::cos(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn erfcf(x: f32) -> f32 {
    libm::erfcf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn erfc(x: f64) -> f64 {
    libm::erfc(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn erff(x: f32) -> f32 {
    libm::erff(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn erf(x: f64) -> f64 {
    libm::erf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn exp10f(x: f32) -> f32 {
    libm::exp10f(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn exp10(x: f64) -> f64 {
    libm::exp10(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn exp2f(x: f32) -> f32 {
    libm::exp2f(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn exp2(x: f64) -> f64 {
    libm::exp2(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn expf(x: f32) -> f32 {
    libm::expf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn expm1f(x: f32) -> f32 {
    libm::expm1f(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn expm1(x: f64) -> f64 {
    libm::expm1(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn exp(x: f64) -> f64 {
    libm::exp(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn fabsf(x: f32) -> f32 {
    libm::fabsf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn fabs(x: f64) -> f64 {
    libm::fabs(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn fdimf(x: f32, y: f32) -> f32 {
    libm::fdimf(x, y)
}

#[unsafe(no_mangle)]
pub extern "C" fn fdim(x: f64, y: f64) -> f64 {
    libm::fdim(x, y)
}

#[unsafe(no_mangle)]
pub extern "C" fn floorf(x: f32) -> f32 {
    libm::floorf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn floor(x: f64) -> f64 {
    libm::floor(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn fmaf(x: f32, y: f32, z: f32) -> f32 {
    libm::fmaf(x, y, z)
}

#[unsafe(no_mangle)]
pub extern "C" fn fma(x: f64, y: f64, z: f64) -> f64 {
    libm::fma(x, y, z)
}

#[unsafe(no_mangle)]
pub extern "C" fn fmaxf(x: f32, y: f32) -> f32 {
    libm::fmaxf(x, y)
}

#[unsafe(no_mangle)]
pub extern "C" fn fmax(x: f64, y: f64) -> f64 {
    libm::fmax(x, y)
}

#[unsafe(no_mangle)]
pub extern "C" fn fminf(x: f32, y: f32) -> f32 {
    libm::fminf(x, y)
}

#[unsafe(no_mangle)]
pub extern "C" fn fmin(x: f64, y: f64) -> f64 {
    libm::fmin(x, y)
}

#[unsafe(no_mangle)]
pub extern "C" fn fmodf(x: f32, y: f32) -> f32 {
    libm::fmodf(x, y)
}

#[unsafe(no_mangle)]
pub extern "C" fn fmod(x: f64, y: f64) -> f64 {
    libm::fmod(x, y)
}

#[unsafe(no_mangle)]
pub fn frexpf(x: f32) -> (f32, i32) {
    libm::frexpf(x)
}

#[unsafe(no_mangle)]
pub fn frexp(x: f64) -> (f64, i32) {
    libm::frexp(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn hypotf(x: f32, y: f32) -> f32 {
    libm::hypotf(x, y)
}

#[unsafe(no_mangle)]
pub extern "C" fn hypot(x: f64, y: f64) -> f64 {
    libm::hypot(x, y)
}

#[unsafe(no_mangle)]
pub extern "C" fn ilogbf(x: f32) -> i32 {
    libm::ilogbf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn ilogb(x: f64) -> i32 {
    libm::ilogb(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn j0f(x: f32) -> f32 {
    libm::j0f(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn j0(x: f64) -> f64 {
    libm::j0(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn j1f(x: f32) -> f32 {
    libm::j1f(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn j1(x: f64) -> f64 {
    libm::j1(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn jnf(n: i32, x: f32) -> f32 {
    libm::jnf(n, x)
}

#[unsafe(no_mangle)]
pub extern "C" fn jn(n: i32, x: f64) -> f64 {
    libm::jn(n, x)
}

#[unsafe(no_mangle)]
pub extern "C" fn ldexpf(x: f32, n: i32) -> f32 {
    libm::ldexpf(x, n)
}

#[unsafe(no_mangle)]
pub extern "C" fn ldexp(x: f64, n: i32) -> f64 {
    libm::ldexp(x, n)
}

#[unsafe(no_mangle)]
pub fn lgammaf_r(x: f32) -> (f32, i32) {
    libm::lgammaf_r(x)
}

#[unsafe(no_mangle)]
pub fn lgammf(x: f32) -> f32 {
    libm::lgammaf(x)
}

#[unsafe(no_mangle)]
pub fn lgamma_r(x: f64) -> (f64, i32) {
    libm::lgamma_r(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn lgamma(x: f64) -> f64 {
    libm::lgamma(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn log10f(x: f32) -> f32 {
    libm::log10f(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn log10(x: f64) -> f64 {
    libm::log10(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn log1pf(x: f32) -> f32 {
    libm::log1pf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn log1p(x: f64) -> f64 {
    libm::log1p(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn log2f(x: f32) -> f32 {
    libm::log2f(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn log2(x: f64) -> f64 {
    libm::log2(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn logf(x: f32) -> f32 {
    libm::logf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn log(x: f64) -> f64 {
    libm::log(x)
}

#[unsafe(no_mangle)]
pub fn modff(x: f32) -> (f32, f32) {
    libm::modff(x)
}

#[unsafe(no_mangle)]
pub fn modf(x: f64) -> (f64, f64) {
    libm::modf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn nextafterf(x: f32, y: f32) -> f32 {
    libm::nextafterf(x, y)
}

#[unsafe(no_mangle)]
pub extern "C" fn nextafter(x: f64, y: f64) -> f64 {
    libm::nextafter(x, y)
}

#[unsafe(no_mangle)]
pub extern "C" fn powf(x: f32, y: f32) -> f32 {
    libm::powf(x, y)
}

#[unsafe(no_mangle)]
pub extern "C" fn pow(x: f64, y: f64) -> f64 {
    libm::pow(x, y)
}

#[unsafe(no_mangle)]
pub extern "C" fn remainderf(x: f32, y: f32) -> f32 {
    libm::remainderf(x, y)
}

#[unsafe(no_mangle)]
pub extern "C" fn remainder(x: f64, y: f64) -> f64 {
    libm::remainder(x, y)
}

#[unsafe(no_mangle)]
pub fn remquof(x: f32, y: f32) -> (f32, i32) {
    libm::remquof(x, y)
}

#[unsafe(no_mangle)]
pub fn remquo(x: f64, y: f64) -> (f64, i32) {
    libm::remquo(x, y)
}

#[unsafe(no_mangle)]
pub extern "C" fn roundf(x: f32) -> f32 {
    libm::roundf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn round(x: f64) -> f64 {
    libm::round(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn scalbnf(x: f32, n: i32) -> f32 {
    libm::scalbnf(x, n)
}

#[unsafe(no_mangle)]
pub extern "C" fn scalbn(x: f64, n: i32) -> f64 {
    libm::scalbn(x, n)
}

#[unsafe(no_mangle)]
pub fn sincosf(x: f32) -> (f32, f32) {
    libm::sincosf(x)
}

#[unsafe(no_mangle)]
pub fn sincos(x: f64) -> (f64, f64) {
    libm::sincos(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn sinf(x: f32) -> f32 {
    libm::sinf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn sinhf(x: f32) -> f32 {
    libm::sinhf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn sinh(x: f64) -> f64 {
    libm::sinh(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn sin(x: f64) -> f64 {
    libm::sin(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn sqrtf(x: f32) -> f32 {
    libm::sqrtf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn sqrt(x: f64) -> f64 {
    libm::sqrt(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn tanf(x: f32) -> f32 {
    libm::tanf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn tanhf(x: f32) -> f32 {
    libm::tanhf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn tanh(x: f64) -> f64 {
    libm::tanh(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn tan(x: f64) -> f64 {
    libm::tan(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn tgammaf(x: f32) -> f32 {
    libm::tgammaf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn tgamma(x: f64) -> f64 {
    libm::tgamma(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn truncf(x: f32) -> f32 {
    libm::truncf(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn trunc(x: f64) -> f64 {
    libm::trunc(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn y0f(x: f32) -> f32 {
    libm::y0f(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn y0(x: f64) -> f64 {
    libm::y0(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn y1f(x: f32) -> f32 {
    libm::y1f(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn y1(x: f64) -> f64 {
    libm::y1(x)
}

#[unsafe(no_mangle)]
pub extern "C" fn ynf(n: i32, x: f32) -> f32 {
    libm::ynf(n, x)
}

#[unsafe(no_mangle)]
pub extern "C" fn yn(n: i32, x: f64) -> f64 {
    libm::yn(n, x)
}
