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

use crate::{memory::GUEST_MAX_MEM, syscall::sys_panic, WORD_SIZE};
use core::alloc::{GlobalAlloc, Layout};

#[global_allocator]
pub static HEAP: BumpPointerAlloc = BumpPointerAlloc;

unsafe extern "C" {
    // This symbol is defined by the loader and marks the end
    // of all elf sections, so this is where we start our
    // heap.
    //
    // This is generated automatically by the linker; see
    // https://lld.llvm.org/ELF/linker_script.html#sections-command
    static _end: u8;
}

static mut HEAP_START: usize = 0;

/// Pointer to next heap address to use, initialized by the [init] function to the _end symbol.
///
/// The heap grows into higher addresses from it's starting position. Since this is a bump
/// allocator and memory is never freed, this address strictly increases over time.
static mut HEAP_POS: usize = 0;

pub struct BumpPointerAlloc;

unsafe impl GlobalAlloc for BumpPointerAlloc {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        unsafe { alloc_aligned(layout.size(), layout.align()) }
    }

    unsafe fn dealloc(&self, _: *mut u8, _: Layout) {
        // this allocator never deallocates memory
    }

    unsafe fn alloc_zeroed(&self, layout: Layout) -> *mut u8 {
        // NOTE: This is safe to avoid zeroing allocated bytes, as the bump allocator does not
        //       re-use memory and the zkVM memory is zero-initialized.
        unsafe { self.alloc(layout) }
    }
}

/// Used memory on the heap, in bytes. Note that the bump allocator never frees memory.
pub fn used() -> usize {
    // SAFETY: Single threaded, and non-preemptive so access is safe.
    unsafe { HEAP_POS - HEAP_START }
}

/// Free memory on the heap, in bytes.
pub fn free() -> usize {
    // SAFETY: Single threaded, and non-preemptive so access is safe. HEAP_POS will always be
    // less than the start of system memory.
    GUEST_MAX_MEM - unsafe { HEAP_POS }
}

pub(crate) unsafe fn alloc_aligned(bytes: usize, align: usize) -> *mut u8 {
    // SAFETY: Single threaded, and non-preemptive so access is safe.
    let mut heap_pos = unsafe { HEAP_POS };

    // Honor requested alignment if larger than word size.
    // Note: align is typically a power of two.
    let align = usize::max(align, WORD_SIZE);

    let offset = heap_pos & (align - 1);
    if offset != 0 {
        heap_pos += align - offset;
    }

    // Check to make sure heap doesn't collide with SYSTEM memory.
    match heap_pos.checked_add(bytes) {
        Some(new_heap_pos) if new_heap_pos <= GUEST_MAX_MEM => {
            // SAFETY: Single threaded, and non-preemptive so modification is safe.
            unsafe { HEAP_POS = new_heap_pos };
        }
        _ => {
            const MSG: &[u8] = "Out of memory! You have been using the default bump allocator \
                which does not reclaim memory. Enable the `heap-embedded-alloc` feature to \
                reclaim memory. This will result in extra cycle cost."
                .as_bytes();
            unsafe { sys_panic(MSG.as_ptr(), MSG.len()) };
        }
    }

    heap_pos as *mut u8
}

/// Initialize the bump allocator with the memory allocations defined in the [memory][crate::memory] module.
///
/// # Safety
///
/// This function must be called exactly once.
pub unsafe fn init() {
    unsafe extern "C" {
        static _end: u8;
    }
    unsafe {
        HEAP_START = (&_end) as *const u8 as usize;
        HEAP_POS = HEAP_START;
    }
}
