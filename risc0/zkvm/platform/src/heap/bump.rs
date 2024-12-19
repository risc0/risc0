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

use crate::syscall::sys_alloc_aligned;
use core::alloc::{GlobalAlloc, Layout};

#[global_allocator]
pub static HEAP: BumpPointerAlloc = BumpPointerAlloc;

extern "C" {
    // This symbol is defined by the loader and marks the end
    // of all elf sections, so this is where we start our
    // heap.
    //
    // This is generated automatically by the linker; see
    // https://lld.llvm.org/ELF/linker_script.html#sections-command
    static _end: u8;
}

static HEAP_START: usize = unsafe { (&_end) as *const u8 as usize };

/// Pointer to next heap address to use, initialized as the address of the _end symbol.
///
/// The heap grows into higher addresses from it's starting position. Since this is a bump
/// allocator and memory is never freed, this address strictly increases over time.
pub(crate) static mut HEAP_POS: usize = HEAP_START;

pub struct BumpPointerAlloc;

unsafe impl GlobalAlloc for BumpPointerAlloc {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        sys_alloc_aligned(layout.size(), layout.align())
    }

    unsafe fn dealloc(&self, _: *mut u8, _: Layout) {
        // this allocator never deallocates memory
    }

    unsafe fn alloc_zeroed(&self, layout: Layout) -> *mut u8 {
        // NOTE: This is safe to avoid zeroing allocated bytes, as the bump allocator does not
        //       re-use memory and the zkVM memory is zero-initialized.
        self.alloc(layout)
    }
}

impl BumpPointerAlloc {
    /// Used memory on the heap, in bytes. Note that the bump allocator never frees memory.
    pub fn used(&self) -> usize {
        // SAFETY: Single threaded, and non-premptive so access is safe.
        unsafe { HEAP_POS - HEAP_START }
    }

    /// Free memory on the heap, in bytes.
    pub fn free(&self) -> usize {
        // SAFETY: Single threaded, and non-premptive so access is safe. HEAP_POS will always be
        // less than the start of system memory.
        crate::memory::SYSTEM.start() - unsafe { HEAP_POS }
    }
}
