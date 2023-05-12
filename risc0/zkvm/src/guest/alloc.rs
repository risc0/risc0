// Copyright 2023 RISC Zero, Inc.
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

use core::{
    alloc::{GlobalAlloc, Layout},
    cell::UnsafeCell,
};

use risc0_zkvm_platform::{memory, syscall, WORD_SIZE};

struct BumpPointerAlloc;

#[cfg(target_os = "zkvm")]
unsafe impl GlobalAlloc for BumpPointerAlloc {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        let nwords = layout
            .align_to(WORD_SIZE)
            .expect("Unable to align allocation to word size")
            .pad_to_align()
            .size()
            / WORD_SIZE;
        syscall::sys_alloc_words(nwords) as *mut u8
    }

    unsafe fn dealloc(&self, _: *mut u8, _: Layout) {
        // this allocator never deallocates memory
    }
}

#[cfg(target_os = "zkvm")]
#[global_allocator]
static HEAP: BumpPointerAlloc = BumpPointerAlloc;
