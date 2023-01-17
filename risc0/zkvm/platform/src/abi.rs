// Copyright 2023 RISC Zero, Inc.
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

use crate::{io, memory, syscall};

// Number of words remaining in the heap that haven't yet been allocated.
static mut HEAP_WORDS_REMAINING: usize = memory::HEAP.len_words();

#[no_mangle]
pub fn zkvm_abi_alloc_words(nwords: usize) -> *mut u32 {
    // SAFETY: Single threaded, so nothing else can touch this while we're working.
    let heap_words_remaining: &mut usize = unsafe { &mut HEAP_WORDS_REMAINING };
    let new_words_remaining = heap_words_remaining
        .checked_sub(nwords)
        .expect("Out of memory!");
    // SAFETY: We've already checked to make sure we haven't
    // overflowed the heap, so the pointer arithmetic here should not
    // cause any undefined behavior.
    let ptr = unsafe { (memory::HEAP.end() as *mut u32).sub(*heap_words_remaining) };
    *heap_words_remaining = new_words_remaining;
    ptr
}

#[no_mangle]
pub fn zkvm_abi_write_stdout(buf: &[u8]) {
    unsafe {
        syscall::sys_io(io::SENDRECV_CHANNEL_STDOUT, buf.as_ptr(), buf.len());
    }
}

#[no_mangle]
pub fn zkvm_abi_write_stderr(buf: &[u8]) {
    unsafe {
        syscall::sys_io(io::SENDRECV_CHANNEL_STDERR, buf.as_ptr(), buf.len());
    }
}
