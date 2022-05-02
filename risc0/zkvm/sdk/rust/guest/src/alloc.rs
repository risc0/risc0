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
    mem::size_of,
    ops::Deref,
};

use crate::mem_layout::{REGION_HEAP_END, REGION_HEAP_START};
use crate::{_fault, WORD_SIZE};

// Bump pointer allocator for *single* core systems.  Returns items of type T.
pub struct BumpPointerAlloc<T> {
    name: &'static str,
    start: *mut T,
    len: UnsafeCell<usize>,
    cap: usize,
}
// We have to declare this explicitly because the structure contains a raw pointer.
unsafe impl<T> Sync for BumpPointerAlloc<T> {}

impl<T> BumpPointerAlloc<T> {
    // Defines a new memory allocation zone; start end end are given in bytes.
    pub(crate) const fn new(name: &'static str, start_bytes: usize, end_bytes: usize) -> Self {
        // TODO(nils): Figure out a way to do these asserts in a const fn:
        // assert_eq!(start_bytes % size_of::<T>(), 0);
        // assert_eq!(end_bytes % size_of::<T>(), 0);
        // assert!(size_of::<T>() % align_of::<T>() == 0);
        BumpPointerAlloc {
            name,
            start: start_bytes as *mut T,
            len: UnsafeCell::new(0),
            cap: (end_bytes - start_bytes) / size_of::<T>(),
        }
    }

    pub unsafe fn alloc(&self, nitems: usize) -> *mut T {
        let len: &mut usize = &mut *self.len.get();
        let ptr = self.start.add(*len);
        let new_len = *len + nitems;

        if new_len > self.cap {
            panic!("Out of {} memory", self.name)
        }

        *len = new_len;
        ptr
    }

    // Changes the size of an allocation, ideally in place.
    unsafe fn realloc(&self, old_ptr: *mut T, old_nitems: usize, new_nitems: usize) -> *mut T {
        if new_nitems <= old_nitems {
            return old_ptr;
        }
        let len: &mut usize = &mut *self.len.get();
        let additional_items = new_nitems - old_nitems;
        if core::ptr::eq(
            self.start.add(*len + new_nitems),
            old_ptr.add(additional_items),
        ) {
            // Nothing has been allocate since; reallocate in place
            let new_len = *len + additional_items;
            if new_len > self.cap {
                panic!("Out of {} memory", self.name)
            }

            return old_ptr;
        } else {
            let new_ptr = self.start.add(*len);
            let new_len = *len + new_nitems;

            if new_len > self.cap {
                panic!("Out of {} memory", self.name)
            }

            *len = new_len;
            return new_ptr;
        }
    }
}

// Returns the part of this region written so far.
impl<T> Deref for BumpPointerAlloc<T> {
    type Target = [T];
    fn deref(&self) -> &[T] {
        unsafe { &*core::slice::from_raw_parts(self.start, *self.len.get()) }
    }
}

unsafe impl GlobalAlloc for BumpPointerAlloc<u8> {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        let size: usize = layout.align_to(WORD_SIZE).unwrap().pad_to_align().size();
        self.alloc(size)
    }

    // Uninitialized memory shows up already zeroed, so no need to zero it.
    unsafe fn alloc_zeroed(&self, layout: Layout) -> *mut u8 {
        self.alloc(layout.size())
    }

    unsafe fn dealloc(&self, _: *mut u8, _: Layout) {
        // this allocator never deallocates memory
    }

    unsafe fn realloc(&self, old_ptr: *mut u8, old_layout: Layout, new_size: usize) -> *mut u8 {
        let old_size = old_layout.size();
        // Copied from default implementation:
        let new_layout = Layout::from_size_align_unchecked(new_size, old_layout.align());
        let new_size: usize = new_layout.pad_to_align().size();

        self.realloc(old_ptr, old_size, new_size)
    }
}

#[global_allocator]
pub(crate) static HEAP_ZONE: BumpPointerAlloc<u8> =
    BumpPointerAlloc::<u8>::new("Heap", REGION_HEAP_START, REGION_HEAP_END);

#[alloc_error_handler]
unsafe fn alloc_fault(_layout: Layout) -> ! {
    _fault()
}
