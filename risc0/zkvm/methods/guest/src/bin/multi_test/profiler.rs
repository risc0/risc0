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
