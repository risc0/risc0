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

use crate::{
    align_up,
    alloc::HEAP_ZONE,
    gpio::{SHADescriptor, GPIO_SHA},
    mem_layout::SHA_DESC_ZONE,
    WORD_SIZE,
};
use _alloc::vec::Vec;
use core::mem;
use risc0_zkvm_core::DIGEST_WORDS;
use risc0_zkvm_serde::to_vec_with_capacity;
use serde::Serialize;

const END_MARKER: u8 = 0x80;

// Chunk size in words for optimized SHA to operate on; all SHA
// requests must be a multiple of this size.
const CHUNK_SIZE: usize = 64 / WORD_SIZE;

// Computes a raw digest of the given slice.  The data must already contain the end marker and the trailer.
pub fn raw_digest(data: &[u32]) -> &'static [u32; DIGEST_WORDS] {
    assert_eq!(data.len() % CHUNK_SIZE, 0);
    // Allocate fresh memory that's guaranteed to be uninitialized so the host can write to it:
    unsafe {
        let digest: *mut [u32; DIGEST_WORDS] = HEAP_ZONE.alloc(DIGEST_WORDS * WORD_SIZE) as _;
        raw_digest_to(data, digest);
        let digest_ref: &'static [u32; DIGEST_WORDS] = &*digest;
        digest_ref
    }
}

// Computes a raw digest of the given slice, and stores the digest in the given pointer.  The digest memory must be uninitilaized.
pub unsafe fn raw_digest_to(data: &[u32], digest: *mut [u32; DIGEST_WORDS]) {
    assert_eq!(data.len() % CHUNK_SIZE, 0);
    let type_count = data.len() / CHUNK_SIZE;
    assert_ne!(type_count, 0);

    let desc_ptr = SHA_DESC_ZONE.alloc(1);

    desc_ptr.write_volatile(SHADescriptor {
        type_count,
        idx: 0,
        source: data.as_ptr() as usize,
        digest: digest as usize,
    });

    GPIO_SHA.write_volatile(desc_ptr);
}

pub trait ShaBuf: Extend<u32> {
    fn len(&self) -> usize;
    fn push(&mut self, val: u32);
    fn as_slice(&self) -> &[u32];
    fn as_mut_slice(&mut self) -> &mut [u32];
    fn extend_from_slice(&mut self, data: &[u32]);
    fn resize(&mut self, new_size: usize);
}

// Calculates the number of words of capacity needed, including end
// marker and trailer, to take the SHA hash of len_bytes bytes.
const fn compute_capacity_needed(len_bytes: usize) -> usize {
    // Add one for end marker
    let mut len_words = align_up(len_bytes + 1, WORD_SIZE) / WORD_SIZE;
    // Add two words for 64-bit size
    len_words += 2;

    align_up(len_words, CHUNK_SIZE)
}

// Slower version of add_trailer for use on write-only memory which
// writes each word exactly once.  LEngth must already be word aligned.
pub fn add_wom_trailer<T: ShaBuf>(data: &mut T, len_bytes: usize) {
    assert_eq!(0, len_bytes % WORD_SIZE);
    let len_words = len_bytes / WORD_SIZE;
    data.push((END_MARKER as u32).to_le());

    // Align to leave 2 words for length at the end.
    while (data.len() % CHUNK_SIZE) != (CHUNK_SIZE - 2) {
        data.push(0);
    }

    // 64-bit size
    data.push((0 as u32).to_be());
    let len_bits = len_words * WORD_SIZE * 8;
    data.push((len_bits as u32).to_be());
}

pub(crate) fn add_trailer<T: ShaBuf>(data: &mut T, len_bytes: usize) {
    assert!(len_bytes <= (data.len() * WORD_SIZE));
    //    let padded_size = align_up((bytes + 3 * WORD_SIZE) / WORD_SIZE, CHUNK_SIZE);
    // Allow space at the end for:
    //    * end marker (1 byte)
    //    * length (uint64_t, 8 bytes)
    let padded_len = compute_capacity_needed(len_bytes);
    assert_eq!(0, padded_len % CHUNK_SIZE);
    data.resize(padded_len);

    // Add end marker
    let slice = data.as_mut_slice();
    unsafe {
        let ptr = slice.as_mut_ptr();
        let u8ptr = ptr as *mut u8;
        assert!(len_bytes < slice.len() * WORD_SIZE);
        u8ptr.add(len_bytes).write_volatile(END_MARKER);
    }

    // Last word is size in bits.
    let len_bits = len_bytes * 8;
    slice[slice.len() - 1] = (len_bits as u32).to_be();
}

// Consumes the given buffer since it needs to modify it to add the trailer.
pub fn digest<T: ShaBuf>(mut data: T) -> &'static [u32; DIGEST_WORDS] {
    let len_bytes = data.len() * WORD_SIZE;
    add_trailer(&mut data, len_bytes);
    raw_digest(data.as_slice())
}

impl ShaBuf for Vec<u32> {
    fn len(&self) -> usize {
        self.len()
    }
    fn push(&mut self, val: u32) {
        self.push(val)
    }
    fn as_slice(&self) -> &[u32] {
        self.as_slice()
    }
    fn as_mut_slice(&mut self) -> &mut [u32] {
        self.as_mut_slice()
    }
    fn extend_from_slice(&mut self, data: &[u32]) {
        self.extend_from_slice(data)
    }
    fn resize(&mut self, new_size: usize) {
        self.resize(new_size, 0)
    }
}

pub fn digest_serialized<T: Serialize>(val: &T) -> &'static [u32; DIGEST_WORDS] {
    // If the object to be serialized is a plain old structure in memory, this should
    // be a good guess for the allocation needed.
    let cap = compute_capacity_needed(mem::size_of_val(val));
    let buf = to_vec_with_capacity(val, cap).unwrap();
    digest(buf)
}

// Make a digest for u8s.  We have no guarantees on alignment so we
// have to copy the whole thing.
pub fn digest_u8(data: &[u8]) -> &'static [u32; DIGEST_WORDS] {
    let len_bytes = data.len();
    let cap = compute_capacity_needed(len_bytes);
    let mut data_u32 = Vec::<u32>::with_capacity(cap);
    unsafe {
        (data_u32.as_mut_ptr() as *mut u8).copy_from_nonoverlapping(data.as_ptr(), len_bytes);
        data_u32.set_len(align_up(len_bytes, WORD_SIZE) / WORD_SIZE);
    }
    add_trailer(&mut data_u32, len_bytes);
    raw_digest(data_u32.as_slice())
}

pub(crate) fn finalize() {
    unsafe {
        let ptr = SHA_DESC_ZONE.alloc(1);
        let type_field_ptr: *mut usize = core::ptr::addr_of_mut!((*ptr).type_count);
        type_field_ptr.write_volatile(0);
    }
}
