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

use _alloc::{boxed::Box, vec::Vec};
use core::mem;

use zkvm_core::Digest;

use crate::{
    align_up,
    gpio::{SHADescriptor, GPIO_SHA},
    REGION_SHA_START, WORD_SIZE,
};

pub struct SHA256 {
    pub(crate) storage: Vec<u8>,
}

static mut CUR_DESC: usize = 0;

// Compute the padded size for data of size 'len' which is equal to:
// len + 1 (terminating byte) + sizeof(uint64_t),
// rounded up to nearest multiple of 64.
fn padded_size(size: usize) -> usize {
    align_up(size + 1 + mem::size_of::<u64>(), 64)
}

fn get_cur_desc() -> *mut SHADescriptor {
    unsafe { (REGION_SHA_START as *mut SHADescriptor).add(CUR_DESC) }
}

impl SHA256 {
    pub fn new() -> Self {
        SHA256 {
            storage: Vec::with_capacity(padded_size(0)),
        }
    }

    pub fn with_capacity(capacity: usize) -> Self {
        SHA256 {
            storage: Vec::with_capacity(padded_size(capacity)),
        }
    }

    pub fn update<T>(&mut self, data: &T) {
        let ptr: *const T = data;
        let len_bytes = mem::size_of::<T>();
        self.storage.reserve(len_bytes);
        unsafe {
            let end = self.storage.as_mut_ptr().add(self.storage.len());
            end.copy_from_nonoverlapping(ptr.cast(), len_bytes);
            self.storage.set_len(self.storage.len() + len_bytes);
        }
    }

    pub fn update_slice<T>(&mut self, data: &[T]) {
        let ptr = data.as_ptr();
        let len_bytes = data.len() * mem::size_of::<T>();
        self.storage.reserve(len_bytes);
        unsafe {
            let end = self.storage.as_mut_ptr().add(self.storage.len());
            end.copy_from_nonoverlapping(ptr.cast(), len_bytes);
            self.storage.set_len(self.storage.len() + len_bytes);
        }
    }

    pub fn finalize(&mut self) -> Box<Digest> {
        let len = self.storage.len();
        let total = padded_size(len);
        self.storage.resize(total, 0);
        self.storage[len] = 0x80;
        let mut digest: Box<mem::MaybeUninit<Digest>> = Box::new_uninit();
        finalize_into(
            len,
            total,
            self.storage.as_mut_ptr(),
            digest.as_mut_ptr().cast(),
        );
        unsafe { digest.assume_init() }
    }
}

fn finalize_into(len: usize, total: usize, ptr: *mut u8, result: *mut usize) {
    let bits = len * 8;
    unsafe {
        // Write size in bits as big endian.
        let trailer: *mut usize = ptr.add(total - WORD_SIZE).cast();
        trailer.write_volatile(bits.to_be());

        // Set up the next descriptor.
        let desc = get_cur_desc();
        desc.write_volatile(SHADescriptor {
            type_count: total / 64,
            idx: 0,
            source: ptr as usize,
            digest: result as usize,
        });

        // Write the descriptor to the oracle for processing.
        GPIO_SHA.write_volatile(desc);

        // Jump to the next descriptor.
        CUR_DESC += 1;
    }
}

pub(crate) fn digest_commit_into(len: usize, slice: &mut [u32], result: *mut usize) {
    let total = padded_size(len);
    let len_words = len / WORD_SIZE;
    slice[len_words] = 0x00000080;
    for i in len_words + 1..total / WORD_SIZE - 1 {
        slice[i] = 0;
    }
    finalize_into(len, total, slice.as_mut_ptr().cast(), result);
}

pub fn digest<T>(data: T) -> Box<Digest> {
    let mut sha = SHA256::with_capacity(mem::size_of::<T>());
    sha.update(&data);
    sha.finalize()
}

pub fn digest_slice<T>(data: &[T]) -> Box<Digest> {
    let mut sha = SHA256::with_capacity(data.len());
    sha.update_slice(data);
    sha.finalize()
}

pub(crate) fn finalize() {
    let ptr = get_cur_desc() as *mut usize;
    unsafe { ptr.write_volatile(0) };
}
