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
