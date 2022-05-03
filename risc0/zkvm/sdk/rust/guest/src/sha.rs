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

use core::alloc::Layout;

use crate::{
    alloc::HEAP_ZONE,
    gpio::{SHADescriptor, GPIO_SHA},
    mem_layout::SHA_DESC_ZONE,
    WORD_SIZE,
};
use _alloc::vec::Vec;
use risc0_zkvm_core::DIGEST_WORDS;
use risc0_zkvm_serde::to_vec;
use serde::Serialize;

pub const END_MARKER: u8 = 0x80;

// Chunk size for optimized SHA to operate on; all SHA requests must
// be a multiple of this size.
const CHUNK_SIZE: usize = 64 / WORD_SIZE;

// Computes a raw digest of the given slice.  The data must already contain the end marker and the trailer.
pub fn raw_digest(data: &[u32]) -> &'static [u32; DIGEST_WORDS] {
    assert_eq!(data.len() % CHUNK_SIZE, 0);
    // Allocate fresh memory that's guaranteed to be uninitialized so the host can write to it:
    unsafe {
        let digest: *mut [u32; DIGEST_WORDS] =
            HEAP_ZONE.alloc(Layout::new::<[u32; DIGEST_WORDS]>().size()) as _;
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
    fn extend_from_slice(&mut self, data: &[u32]);
}

pub fn add_end_marker<T: ShaBuf>(data: &mut T) {
    data.push((END_MARKER as u32).to_le());
}

pub fn add_trailer<T: ShaBuf>(data: &mut T, bits: usize) {
    // The last word needs to be the size, the second to last word needs to be 0,
    // and the total words needs to be a multiple of CHUNK_SIZE.  Pad the data so there's two
    // words remaining before a CHUNK_SIZE boundry that we can fill with (0, bits).
    let padding = CHUNK_SIZE - 1 - ((data.len() + 1) % CHUNK_SIZE);
    const PADDING: [u32; CHUNK_SIZE] = [0; CHUNK_SIZE];
    data.extend_from_slice(&PADDING[..padding + 1]);
    data.push((bits as u32).to_be());

    assert_eq!(0, data.len() % CHUNK_SIZE);
}

pub fn digest<T: ShaBuf>(mut data: T) -> &'static [u32; DIGEST_WORDS] {
    let bits = data.len() * WORD_SIZE * 8;
    add_end_marker(&mut data);
    add_trailer(&mut data, bits);
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
    fn extend_from_slice(&mut self, data: &[u32]) {
        self.extend_from_slice(data)
    }
}

pub fn digest_serialized<T: Serialize>(val: &T) -> &'static [u32; DIGEST_WORDS] {
    let buf = to_vec(val).unwrap();
    digest(buf)
}

// Make a digest for u8s, which are not aligned on a word boundary.
pub fn digest_u8_slice(data: &[u8]) -> &'static [u32; DIGEST_WORDS] {
    digest_u8_vec(data.iter().cloned().collect::<Vec<u8>>())
}

pub fn digest_u8_vec(mut data: Vec<u8>) -> &'static [u32; DIGEST_WORDS] {
    let bits = data.len() * 8;
    data.push(END_MARKER);
    while data.len() % WORD_SIZE != 0 {
        data.push(0);
    }
    // Unsafe in general, but our allocator always aligns on WORD_SIZE,
    // and our deallocator does nothing.  This means we can reinterpret
    // our u8 vec as a u32 vec.
    let mut data: Vec<u32> = unsafe {
        let ptr = data.as_mut_ptr() as *mut u32;
        let len = data.len() / WORD_SIZE;
        let cap = data.capacity() / WORD_SIZE;
        Vec::from_raw_parts(ptr, len, cap)
    };

    add_trailer(&mut data, bits);
    raw_digest(data.as_slice())
}

pub(crate) fn finalize() {
    unsafe {
        let ptr = SHA_DESC_ZONE.alloc(1);
        let type_field_ptr: *mut usize = core::ptr::addr_of_mut!((*ptr).type_count);
        type_field_ptr.write_volatile(0);
    }
}
