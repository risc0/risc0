// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use core::arch::asm;

#[inline(never)]
pub fn profile_test_func1() {
    // Two functions inlined one after the other to test we get the bounds correct.
    profile_test_func2();
    profile_test_func3();

    profile_test_func4();

    // Tail-call to non-inlined function can produce confusing jump
    profile_test_func5();
}

#[inline(always)]
fn profile_test_func2() {
    unsafe { asm!("nop") }
}

#[inline(always)]
fn profile_test_func3() {
    unsafe { asm!("nop") }
}

/// This contains a jump in the middle that shouldn't be interpreted as a "call" by the profiler.
#[inline(always)]
fn profile_test_func4() {
    unsafe { asm!("la a0, 1f", "jr a0", "1:", "nop") }
}

/// Inline the same function many times in different locations
#[inline(never)]
fn profile_test_func5() {
    profile_test_func3();
    profile_test_func3();
    profile_test_func3();
    profile_test_func3();
    profile_test_func3();
    profile_test_func3();
    profile_test_func3();
    profile_test_func3();
    profile_test_func3();
    profile_test_func3();
}
