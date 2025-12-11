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

#![allow(dead_code)]

extern crate alloc;

use core::alloc::{GlobalAlloc, Layout};
use core::ptr::NonNull;
use rlsf::Tlsf;

use crate::constants::{KERNEL_HEAP_SIZE, KERNEL_HEAP_START_ADDR};

// Type alias for the heap allocator
type Heap = Tlsf<'static, usize, usize, { usize::BITS as usize }, { usize::BITS as usize }>;

// Static TLSF allocator instance
static mut TLSF: Heap = Tlsf::new();

// Helper function to get raw pointer to TLSF
unsafe fn get_tlsf_ptr() -> *mut Heap {
    &raw mut TLSF
}

/// Global kernel heap allocator using RLSF (Real-time Lock-free Slab)
pub struct KernelAllocator;

unsafe impl GlobalAlloc for KernelAllocator {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        let ret = unsafe {
            (*get_tlsf_ptr())
                .allocate(layout)
                .map(|ptr| ptr.as_ptr())
                .unwrap_or(core::ptr::null_mut())
        };
        if ret.is_null() {
            crate::kernel::print("Out of memory");
            #[allow(clippy::empty_loop)]
            loop {} // Halt on OOM
        }

        ret
    }

    unsafe fn dealloc(&self, ptr: *mut u8, layout: Layout) {
        if !ptr.is_null() {
            // Track deallocation (approximate - we don't know exact size freed)
            // TLSF may have internal overhead, so this is an approximation
            unsafe {
                (*get_tlsf_ptr()).deallocate(NonNull::new_unchecked(ptr), layout.align());
            }
        }
    }
}

/// Initialize the kernel allocator
///
/// # Safety
/// This function is unsafe because it modifies global state and assumes
/// the kernel heap memory region is available.
///
/// # WARNING
/// Calling this twice (even with the INITIALIZED check) could corrupt existing allocations
/// if there's a race condition. The heap is zeroed, which would destroy any existing data!
pub unsafe fn init_kernel_allocator() {
    // Initialize the heap memory region (fixed 16MB below stack)
    let heap_start = KERNEL_HEAP_START_ADDR as *mut u8;
    let heap_size = KERNEL_HEAP_SIZE;
    /* crate::kernel::print("Zeroing heap memory");

    unsafe {
        // This writes the byte value 0 to every address from `heap_start` up to `heap_start + heap_size`,
        // that is, it zeroes out the entire kernel heap memory region from the starting pointer
        // (`heap_start`) to (`heap_start + heap_size`).
        core::ptr::write_bytes(heap_start, 0, heap_size);
    }
    crate::kernel::print("Done zeroing heap memory"); */

    // Add the heap memory to the allocator
    let heap_slice = unsafe { core::slice::from_raw_parts_mut(heap_start, heap_size) };
    let heap_maybe_uninit =
        unsafe { core::mem::transmute::<&mut [u8], &mut [core::mem::MaybeUninit<u8>]>(heap_slice) };
    unsafe {
        (*get_tlsf_ptr()).insert_free_block(heap_maybe_uninit);
    }
}
