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
    cmp::max,
    mem::size_of,
};

use crate::mem_layout::{REGION_HEAP_END, REGION_HEAP_START};
use crate::mutex::Mutex;
use crate::sha::ShaBuf;
use crate::{_fault, align_up, WORD_SIZE};
use risc0_zkvm_serde::{Result as SerdeResult, StreamWriter};

// Bump pointer allocator for *single* core systems.  Returns items of type T.
pub struct BumpPointerAlloc<T> {
    name: &'static str,
    start: *mut T,
    len: Mutex<usize>,
    cap: usize,
}

// This contains a raw pointer so we have to explicitly mark it as Sync.
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
            len: Mutex::new(0),
            cap: (end_bytes - start_bytes) / size_of::<T>(),
        }
    }

    pub fn ptr(&self) -> *mut T {
        self.start
    }

    pub unsafe fn alloc(&self, nitems: usize) -> *mut T {
        let mut len = self.len.lock().unwrap();

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
        let mut len = self.len.lock().unwrap();
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

            new_ptr.copy_from_nonoverlapping(old_ptr, old_nitems);
            return new_ptr;
        }
    }

    pub fn len(&self) -> usize {
        *self.len.lock().unwrap()
    }

    pub fn as_slice(&self) -> &[T] {
        unsafe { &*core::slice::from_raw_parts(self.start, *self.len.lock().unwrap()) }
    }

    pub fn as_mut_slice(&self) -> &mut [T] {
        unsafe { &mut *core::slice::from_raw_parts_mut(self.start, *self.len.lock().unwrap()) }
    }

    // Returns the slice of new values to be initialized, if any.
    pub fn resize(&self, new_size: usize) -> &mut [T] {
        assert!(new_size <= self.cap);
        let mut len = self.len.lock().unwrap();
        let init_range_start = *len;
        let init_range_end = max(*len, new_size);
        *len = new_size;

        // Return values to be initialized.
        unsafe {
            &mut *core::slice::from_raw_parts_mut(
                self.start.add(init_range_start),
                init_range_end - init_range_start,
            )
        }
    }

    pub fn as_buf<'a>(&'a self) -> BumpBuf<T>
    where
        'a: 'static,
    {
        BumpBuf::<T>::new(self)
    }
}

// Allow BumpPointerAlloc to be treated as SHA and serde buffers.
//
// TODO(nils):  This should lock the BumpPointerAlloc length mutex
// and hold it while the BumpBuf is in scope.  That will let us avoid doing
// quite so many checks while writing to it.
pub struct BumpBuf<T>
where
    T: 'static,
{
    zone: &'static BumpPointerAlloc<T>,
    // Original length before we started writing to this buffer.
    orig_len: usize,
}

impl<T> BumpBuf<T> {
    fn new(zone: &'static BumpPointerAlloc<T>) -> Self {
        Self {
            zone,
            orig_len: zone.len(),
        }
    }
}

impl<T> Extend<T> for BumpBuf<T> {
    fn extend<U>(&mut self, iter: U)
    where
        U: IntoIterator<Item = T>,
    {
        for val in iter {
            unsafe { *self.zone.alloc(1) = val };
        }
    }
}

impl ShaBuf for BumpBuf<u32> {
    fn len(&self) -> usize {
        self.zone.len()
    }

    fn push(&mut self, val: u32) {
        unsafe { *self.zone.alloc(1) = val };
    }

    fn as_slice(&self) -> &[u32] {
        self.zone.as_slice()
    }

    fn as_mut_slice(&mut self) -> &mut [u32] {
        self.zone.as_mut_slice()
    }

    fn extend_from_slice(&mut self, data: &[u32]) {
        unsafe {
            self.zone
                .alloc(data.len())
                .copy_from_nonoverlapping(data.as_ptr(), data.len());
        }
    }

    fn resize(&mut self, new_size: usize) {
        let new_elems = self.zone.resize(new_size);
        new_elems.fill(0);
    }
}

impl StreamWriter for BumpBuf<u32> {
    // A bump buf's allocation is all static, so we can return the slice that's been written.
    type Output = &'static [u32];

    fn try_push_word(&mut self, data: u32) -> SerdeResult<()> {
        self.push(data);
        SerdeResult::Ok(())
    }

    fn try_push_dword(&mut self, data: u64) -> SerdeResult<()> {
        self.extend_from_slice(&[(data & 0xffffffff) as u32, (data >> 32) as u32]);
        SerdeResult::Ok(())
    }

    fn try_extend(&mut self, data: &[u8]) -> SerdeResult<()> {
        unsafe {
            let ptr = self.zone.alloc(align_up(data.len(), WORD_SIZE));
            (ptr as *mut u8).copy_from_nonoverlapping(data.as_ptr(), data.len());
        }
        SerdeResult::Ok(())
    }

    fn release(&mut self) -> SerdeResult<Self::Output> {
        let start = unsafe { self.zone.ptr().add(self.orig_len) };
        let len = self.zone.len() - self.orig_len;
        SerdeResult::Ok(unsafe { &*core::slice::from_raw_parts(start, len) })
    }
}

unsafe impl GlobalAlloc for BumpPointerAlloc<u8> {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        let size: usize = layout.align_to(WORD_SIZE).unwrap().pad_to_align().size();
        self.alloc(size)
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
