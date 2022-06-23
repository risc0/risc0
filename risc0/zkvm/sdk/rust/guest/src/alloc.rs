// Copyright 2022 Risc0, Inc.
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

use crate::{_fault, align_up, mem_layout, WORD_SIZE};

// Bump pointer allocator for *single* core systems
struct BumpPointerAlloc {
    head: UnsafeCell<usize>,
    end: usize,
}

// SAFETY: single threaded environment
unsafe impl Sync for BumpPointerAlloc {}

#[cfg(target_arch = "riscv32")]
unsafe impl GlobalAlloc for BumpPointerAlloc {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        let head = self.head.get();

        // move start up to the next alignment boundary
        let alloc_start = align_up(*head, WORD_SIZE);
        let alloc_end = alloc_start.checked_add(layout.size()).unwrap();
        if alloc_end > self.end {
            _fault();
        } else {
            *head = alloc_end;
            alloc_start as *mut u8
        }
    }

    unsafe fn dealloc(&self, _: *mut u8, _: Layout) {
        // this allocator never deallocates memory
    }
}

#[cfg(target_arch = "riscv32")]
#[global_allocator]
static HEAP: BumpPointerAlloc = BumpPointerAlloc {
    head: UnsafeCell::new(mem_layout::HEAP.start()),
    end: mem_layout::HEAP.end(),
};

#[cfg(target_arch = "riscv32")]
#[alloc_error_handler]
unsafe fn alloc_fault(_layout: Layout) -> ! {
    _fault()
}
