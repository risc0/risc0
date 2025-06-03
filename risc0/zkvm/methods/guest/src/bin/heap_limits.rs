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

#![no_std]
#![no_main]

extern crate alloc;

use alloc::{
    alloc::{alloc, Layout},
    string::String,
};

use risc0_zkvm::guest::env;

risc0_zkvm::entry!(main);

/// Show that we crash if we try to allocate too much memory instead of something else like re-use
/// old addresses or some other potentially bad behavior.
fn heap_overflow_via_alloc() {
    let ptr1 = unsafe { alloc(Layout::from_size_align(isize::MAX as usize, 1).unwrap()) };

    // Use the pointer in some way to defeat optimizer

    let ptr2 = unsafe { alloc(Layout::from_size_align(isize::MAX as usize, 1).unwrap()) };

    // Use the pointer in some way to defeat optimizer
    core::hint::black_box(ptr2);
    core::hint::black_box(ptr1);

    unreachable!("expected a crash in the memory allocator")
}

unsafe extern "C" {
    fn sys_alloc_aligned(bytes: usize, align: usize) -> *mut u8;
}

/// Show that we crash if we try to allocate too much memory instead of something else like re-use
/// old addresses or some other potentially bad behavior.
fn heap_overflow_via_sys_alloc_aligned() {
    for size in [10usize, usize::MAX] {
        let ptr = unsafe { sys_alloc_aligned(size, 1) };

        // Use the pointer in some way to defeat optimizer
        core::hint::black_box(ptr);
    }

    unreachable!("expected a crash in the memory allocator")
}

fn main() {
    match &env::read::<String>()[..] {
        "heap_overflow_via_alloc" => heap_overflow_via_alloc(),
        "heap_overflow_via_sys_alloc_aligned" => heap_overflow_via_sys_alloc_aligned(),
        unknown => panic!("unknown test {unknown}"),
    }
}
