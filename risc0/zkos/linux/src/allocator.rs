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

use alloc::format;
use core::alloc::{GlobalAlloc, Layout};
use core::ptr::NonNull;
use core::sync::atomic::{AtomicBool, AtomicUsize, Ordering};
use rlsf::Tlsf;

use crate::constants::{KERNEL_HEAP_SIZE, KERNEL_HEAP_START_ADDR};

// Type alias for the heap allocator
type Heap = Tlsf<'static, usize, usize, { usize::BITS as usize }, { usize::BITS as usize }>;

// Static TLSF allocator instance
static mut TLSF: Heap = Tlsf::new();
static INITIALIZED: AtomicBool = AtomicBool::new(false);

// Heap statistics tracking
static HEAP_USED: AtomicUsize = AtomicUsize::new(0);
static HEAP_ALLOC_COUNT: AtomicUsize = AtomicUsize::new(0);
static HEAP_DEALLOC_COUNT: AtomicUsize = AtomicUsize::new(0);

// Helper function to get raw pointer to TLSF
unsafe fn get_tlsf_ptr() -> *mut Heap {
    &raw mut TLSF
}

/// Global kernel heap allocator using RLSF (Real-time Lock-free Slab)
pub struct KernelAllocator;

unsafe impl GlobalAlloc for KernelAllocator {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        // Ensure the allocator is initialized
        // CRITICAL: Check heap usage before initializing to detect if init happens after allocations
        if !INITIALIZED.load(Ordering::Acquire) {
            let (used, _, _) = get_heap_stats();
            if used > 0 {
                crate::kernel::print(&format!(
                    "CRITICAL: alloc() calling init_kernel_allocator() when heap already has {} bytes!",
                    used
                ));
                crate::kernel::print(
                    "  This suggests init_kernel_allocator() was NOT called at startup!",
                );
            }
            unsafe {
                init_kernel_allocator();
            }
        }

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

        // Track allocation
        let size = layout.size();
        HEAP_USED.fetch_add(size, Ordering::Relaxed);
        HEAP_ALLOC_COUNT.fetch_add(1, Ordering::Relaxed);

        ret
    }

    unsafe fn dealloc(&self, ptr: *mut u8, layout: Layout) {
        if !ptr.is_null() {
            // Track deallocation (approximate - we don't know exact size freed)
            // TLSF may have internal overhead, so this is an approximation
            let size = layout.size();
            let old_used = HEAP_USED.fetch_sub(size, Ordering::Relaxed);
            let new_used = old_used.saturating_sub(size);
            HEAP_DEALLOC_COUNT.fetch_add(1, Ordering::Relaxed);

            // Log large deallocations that might indicate path_index being freed
            if size > 100_000 {
                crate::kernel::print(&format!(
                    "LARGE DEALLOC: {} bytes ({} KB), heap used: {} -> {} bytes",
                    size,
                    size / 1024,
                    old_used,
                    new_used
                ));
            }

            unsafe {
                (*get_tlsf_ptr()).deallocate(NonNull::new_unchecked(ptr), layout.align());
            }
        }
    }
}

impl KernelAllocator {
    /// Get heap statistics
    /// Returns (used_bytes, free_bytes, total_bytes)
    /// Note: Used bytes is approximate due to allocator overhead
    pub fn get_heap_stats(&self) -> (usize, usize, usize) {
        let total = KERNEL_HEAP_SIZE;
        let used = HEAP_USED.load(Ordering::Relaxed);
        // Free is approximate - actual free may be less due to fragmentation
        let free = total.saturating_sub(used);
        (used, free, total)
    }

    /// Get detailed heap statistics including allocation counts
    pub fn get_detailed_heap_stats(&self) -> (usize, usize, usize, usize, usize) {
        let (used, free, total) = self.get_heap_stats();
        let allocs = HEAP_ALLOC_COUNT.load(Ordering::Relaxed);
        let deallocs = HEAP_DEALLOC_COUNT.load(Ordering::Relaxed);
        (used, free, total, allocs, deallocs)
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
    // Check if already initialized
    if INITIALIZED.load(Ordering::Acquire) {
        // Check if heap has allocations - if so, re-initializing would CORRUPT them!
        let (heap_used, _, _) = get_heap_stats();
        if heap_used > 0 {
            crate::kernel::print(&format!(
                "CRITICAL: init_kernel_allocator called when heap has {} bytes allocated!",
                heap_used
            ));
            crate::kernel::print(
                "  This would ZERO the heap and corrupt all existing allocations!",
            );
            crate::kernel::print("  Returning early to prevent corruption.");
        } else {
            crate::kernel::print("init_kernel_allocator: Already initialized (heap empty, safe)");
        }
        return; // Already initialized
    }

    // Track heap state before initialization
    let (heap_before, _, _) = get_heap_stats();
    if heap_before > 0 {
        crate::kernel::print(&format!(
            "WARNING: init_kernel_allocator: Heap already has {} bytes before init!",
            heap_before
        ));
    }

    // Initialize the heap memory region (fixed 16MB below stack)
    let heap_start = KERNEL_HEAP_START_ADDR as *mut u8;
    let heap_size = KERNEL_HEAP_SIZE;

    crate::kernel::print("Zeroing heap memory");

    unsafe {
        // This writes the byte value 0 to every address from `heap_start` up to `heap_start + heap_size`,
        // that is, it zeroes out the entire kernel heap memory region from the starting pointer
        // (`heap_start`) to (`heap_start + heap_size`).
        core::ptr::write_bytes(heap_start, 0, heap_size);
    }
    crate::kernel::print("Done zeroing heap memory");

    // Add the heap memory to the allocator
    let heap_slice = unsafe { core::slice::from_raw_parts_mut(heap_start, heap_size) };
    let heap_maybe_uninit =
        unsafe { core::mem::transmute::<&mut [u8], &mut [core::mem::MaybeUninit<u8>]>(heap_slice) };
    unsafe {
        (*get_tlsf_ptr()).insert_free_block(heap_maybe_uninit);
    }

    // CRITICAL: Reset heap tracking counters when zeroing the heap
    // This ensures stats are accurate after initialization
    HEAP_USED.store(0, Ordering::Release);
    HEAP_ALLOC_COUNT.store(0, Ordering::Release);
    HEAP_DEALLOC_COUNT.store(0, Ordering::Release);

    // Mark as initialized
    INITIALIZED.store(true, Ordering::Release);

    // Verify heap is empty after initialization
    let (heap_after, _, _) = get_heap_stats();
    crate::kernel::print(&format!(
        "init_kernel_allocator: Complete - heap before: {} bytes, after: {} bytes",
        heap_before, heap_after
    ));
    if heap_after != 0 {
        crate::kernel::print("WARNING: Heap stats show non-zero usage after initialization!");
    }
}

/// Get heap statistics
pub fn get_heap_stats() -> (usize, usize, usize) {
    let allocator = KernelAllocator;
    allocator.get_heap_stats()
}

// Note: Tests for the allocator are not included here because they require
// the RISC-V target environment where the alloc crate is available.
// The allocator will be tested in the actual zkVM environment.
