use core::{
    alloc::{GlobalAlloc, Layout},
    cell::UnsafeCell,
    mem,
};

use crate::{_fault, align_up, REGION_HEAP_END, REGION_HEAP_START};

// Bump pointer allocator for *single* core systems
struct BumpPointerAlloc {
    head: UnsafeCell<usize>,
    end: usize,
}
unsafe impl Sync for BumpPointerAlloc {}

unsafe impl GlobalAlloc for BumpPointerAlloc {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        let head = self.head.get();

        // move start up to the next alignment boundary
        let alloc_start = align_up(*head, mem::size_of::<usize>());
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

#[global_allocator]
static HEAP: BumpPointerAlloc = BumpPointerAlloc {
    head: UnsafeCell::new(REGION_HEAP_START),
    end: REGION_HEAP_END,
};

#[alloc_error_handler]
unsafe fn alloc_fault(_layout: Layout) -> ! {
    _fault()
}
