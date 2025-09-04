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

use core::alloc::{GlobalAlloc, Layout};
use core::ptr::NonNull;
use core::sync::atomic::{AtomicBool, Ordering};
use rlsf::Tlsf;

use crate::constants::{KERNEL_HEAP_SIZE, KERNEL_HEAP_START_ADDR};

// Type alias for the heap allocator
type Heap = Tlsf<'static, usize, usize, { usize::BITS as usize }, { usize::BITS as usize }>;

// Static TLSF allocator instance
static mut TLSF: Heap = Tlsf::new();
static INITIALIZED: AtomicBool = AtomicBool::new(false);

// Helper function to get raw pointer to TLSF
unsafe fn get_tlsf_ptr() -> *mut Heap {
    &raw mut TLSF
}

/// Global kernel heap allocator using RLSF (Real-time Lock-free Slab)
pub struct KernelAllocator;

unsafe impl GlobalAlloc for KernelAllocator {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        // Ensure the allocator is initialized
        if !INITIALIZED.load(Ordering::Acquire) {
            unsafe {
                init_kernel_allocator();
            }
        }

        unsafe {
            (*get_tlsf_ptr())
                .allocate(layout)
                .map(|ptr| ptr.as_ptr())
                .unwrap_or(core::ptr::null_mut())
        }
    }

    unsafe fn dealloc(&self, ptr: *mut u8, layout: Layout) {
        if !ptr.is_null() {
            unsafe {
                (*get_tlsf_ptr()).deallocate(NonNull::new_unchecked(ptr), layout.align());
            }
        }
    }
}

impl KernelAllocator {
    /// Get heap statistics
    pub fn get_heap_stats(&self) -> (usize, usize, usize) {
        // This is a simplified version - RLSF doesn't provide direct stats
        // In a real implementation, you'd track these values
        let total = KERNEL_HEAP_SIZE;
        let used = 0; // Would need to track this
        let remaining = total - used;
        (used, remaining, total)
    }
}

/// Initialize the kernel allocator
///
/// # Safety
/// This function is unsafe because it modifies global state and assumes
/// the kernel heap memory region is available.
pub unsafe fn init_kernel_allocator() {
    if INITIALIZED.load(Ordering::Acquire) {
        return; // Already initialized
    }

    // Initialize the heap memory region
    let heap_start = KERNEL_HEAP_START_ADDR as *mut u8;
    let heap_size = KERNEL_HEAP_SIZE;

    /* Not needed?
       Zero out the heap memory
    unsafe {
        core::ptr::write_bytes(heap_start, 0, heap_size);
    } */

    // Add the heap memory to the allocator
    let heap_slice = unsafe { core::slice::from_raw_parts_mut(heap_start, heap_size) };
    let heap_maybe_uninit =
        unsafe { core::mem::transmute::<&mut [u8], &mut [core::mem::MaybeUninit<u8>]>(heap_slice) };
    unsafe {
        (*get_tlsf_ptr()).insert_free_block(heap_maybe_uninit);
    }

    // Mark as initialized
    INITIALIZED.store(true, Ordering::Release);
}

/// Get heap statistics
pub fn get_heap_stats() -> (usize, usize, usize) {
    let allocator = KernelAllocator;
    allocator.get_heap_stats()
}

// Note: Tests for the allocator are not included here because they require
// the RISC-V target environment where the alloc crate is available.
// The allocator will be tested in the actual zkVM environment.
