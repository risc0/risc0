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
use bytemuck;
use core::{cell::UnsafeCell, mem};

use risc0_zkvm_core::Digest;
use risc0_zkvm_serde::to_vec_with_capacity;
use serde::Serialize;

use crate::{
    align_up,
    gpio::{SHADescriptor, GPIO_SHA},
    REGION_SHA_START, WORD_SIZE,
};

// Current sha descriptor index.
struct CurDesc(UnsafeCell<usize>);
// SAFETY: single threaded environment
unsafe impl Sync for CurDesc {}

static CUR_DESC: CurDesc = CurDesc(UnsafeCell::new(0));

const END_MARKER: u8 = 0x80;

// Chunk size in words for optimized SHA to operate on; all SHA
// requests must be a multiple of this size.
const CHUNK_SIZE: usize = 64 / WORD_SIZE;

fn alloc_desc() -> *mut SHADescriptor {
    // SAFETY: Single threaded and this is the only place we use CUR_DESC.
    unsafe {
        let cur_desc = CUR_DESC.0.get();
        let ptr = (REGION_SHA_START as *mut SHADescriptor).add(*cur_desc);
        *cur_desc += 1;
        ptr
    }
}

// Computes a raw digest of the given slice.  The data must already
// contain the end marker and the trailer.
pub fn raw_digest(data: &[u32]) -> &'static Digest {
    assert_eq!(data.len() % CHUNK_SIZE, 0);
    // Allocate fresh memory that's guaranteed to be uninitialized so
    // the host can write to it.
    unsafe {
        let alloced = Box::<mem::MaybeUninit<Digest>>::new(mem::MaybeUninit::<Digest>::uninit());
        let digest = (*Box::into_raw(alloced)).as_mut_ptr();
        raw_digest_to(data, digest);
        &*digest
    }
}

// Computes a raw digest of the given slice, and stores the digest in
// the given pointer.  The digest memory must be uninitilaized.
pub(crate) unsafe fn raw_digest_to(data: &[u32], digest: *mut Digest) {
    assert_eq!(data.len() % CHUNK_SIZE, 0);
    let type_count = data.len() / CHUNK_SIZE;
    assert_ne!(type_count, 0);

    let desc_ptr = alloc_desc();

    desc_ptr.write_volatile(SHADescriptor {
        type_count,
        idx: 0,
        source: data.as_ptr() as usize,
        digest: digest as usize,
    });

    GPIO_SHA.write_volatile(desc_ptr);
}

// Calculates the number of words of capacity needed, including end
// marker and trailer, to take the SHA hash of len_bytes bytes.
pub const fn compute_capacity_needed(len_bytes: usize) -> usize {
    // Add one for end marker, round up, then 2 words for the 64-bit size.
    let len_words = align_up(len_bytes + 1, WORD_SIZE) / WORD_SIZE + 2;
    align_up(len_words, CHUNK_SIZE)
}

pub(crate) enum MemoryType {
    Normal, // Normal memory that can be written to multiple times.
    WOM,    // Write-only memory where each word can only be written once.
}
// Add the SHA trailer.  The given slice must already be properly
// sized according to compute_capacity_needed.
pub(crate) fn add_trailer(data: &mut [u32], len_bytes: usize, memtype: MemoryType) {
    assert_eq!(compute_capacity_needed(len_bytes), data.len());
    let marker_word = len_bytes / WORD_SIZE;
    match memtype {
        MemoryType::WOM => {
            // With WOM memory, we require word alignment, and we have to
            // write each word in the trailer exactly once.
            assert_eq!(0, len_bytes % WORD_SIZE);

            data[marker_word] = (END_MARKER as u32).to_le();
        }
        MemoryType::Normal => {
            // In regular memory, the end may not be word aligned, so the
            // end marker might go in the middle of a word.
            let as_u8: &mut [u8] = bytemuck::cast_slice_mut(data);
            as_u8[len_bytes] = END_MARKER;
        }
    }
    // Fill in zeros until the lower 32 bits of size.
    let size_word = data.len() - 1;
    data[marker_word + 1..size_word].fill(0);

    let len_bits = len_bytes * 8;
    data[size_word] = (len_bits as u32).to_be();
}

// Computes the SHA256 digest of a serialized object.
pub fn digest<T: Serialize>(val: &T) -> &'static Digest {
    // If the object to be serialized is a plain old structure in memory, this
    // should be a good guess for the allocation needed.
    let cap = compute_capacity_needed(mem::size_of_val(val));
    let mut buf = to_vec_with_capacity(val, cap).unwrap();

    let len_bytes = buf.len() * WORD_SIZE;
    buf.resize(compute_capacity_needed(len_bytes), 0);
    add_trailer(buf.as_mut_slice(), len_bytes, MemoryType::Normal);
    raw_digest(buf.as_slice())
}

// Makes a digest for a slice of u8s.  We have no guarantees on
// alignment so we have to copy the whole thing to a new buffer.
pub fn digest_u8_slice(data: &[u8]) -> &'static Digest {
    let len_bytes = data.len();
    let cap = compute_capacity_needed(len_bytes);
    let mut data_u32 = Vec::<u32>::with_capacity(cap);

    let whole_words = len_bytes / WORD_SIZE;
    // First copy in all the words we can.
    let words_copied: usize;
    match bytemuck::try_cast_slice(&data[..whole_words * WORD_SIZE]) as Result<&[u32], _> {
        Ok(words) => {
            data_u32.extend_from_slice(words);
            words_copied = whole_words;
        }
        Err(_) => {
            words_copied = 0;
        }
    };

    data_u32.resize(cap, 0);
    // Now copy in any remaining bytes.
    let remaining_in = &data[words_copied * WORD_SIZE..];
    let remaining_out: &mut [u8] = bytemuck::cast_slice_mut(&mut data_u32[words_copied..]);
    remaining_out[..remaining_in.len()].clone_from_slice(remaining_in);

    add_trailer(data_u32.as_mut_slice(), len_bytes, MemoryType::Normal);
    raw_digest(data_u32.as_slice())
}

// Set a marker so that the VM knows when the last SHA descriptor is
// reached. We need to write to this memory location at least once so
// that it's not uninitialized, and the value of 0 is the marker that
// the VM looks for.
pub(crate) fn finalize() {
    unsafe {
        let ptr = alloc_desc();
        let type_field_ptr: *mut usize = core::ptr::addr_of_mut!((*ptr).type_count);
        type_field_ptr.write_volatile(0);
    }
}
