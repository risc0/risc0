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

//! Functions for computing SHA-256 hashes.

use alloc::format;
use alloc::{boxed::Box, vec::Vec};
use core::{
    cell::UnsafeCell,
    mem::{self, MaybeUninit},
};

use risc0_zkp::core::sha::{Digest, DIGEST_WORDS, SHA256_INIT};
use risc0_zkvm_platform::{
    syscall::{sys_sha_buffer, sys_sha_compress},
    WORD_SIZE,
};
use serde::Serialize;

use crate::guest::align_up;
use crate::serde::to_vec_with_capacity;

const END_MARKER: u8 = 0x80;

// Chunk size in words for optimized SHA to operate on; all SHA
// requests must be a multiple of this size.
const BLOCK_WORDS: usize = 16;
const HALFBLOCK_WORDS: usize = BLOCK_WORDS / 2;
type HalfBlock = [u32; HALFBLOCK_WORDS];
type Block = [HalfBlock; 2];

fn alloc_uninit_digest() -> *mut Digest {
    extern crate alloc;
    use core::alloc::Layout;
    unsafe { alloc::alloc::alloc(Layout::from_size_align(64, 4).unwrap()).cast() }
}

fn compress(
    out_state: *mut Digest,
    in_state: *const Digest,
    block_half1: &HalfBlock,
    block_half2: &HalfBlock,
) {
    // SAFETY: This is only called from this crate.  It's perfectly fine
    // for in_state and out_state to point at the same place, and for
    // out_state to be uninitialized memory, and those preclude us
    // from using references.
    unsafe {
        sys_sha_compress(out_state.cast(), in_state.cast(), block_half1, block_half2);
    }
}

#[derive(PartialEq, Eq, Debug, Copy, Clone)]
pub(crate) enum Trailer {
    /// Add a SHA-standard trailer with an end marker and the given number of
    /// bits
    WithTrailer { total_bits: usize },
    /// Only zero-pad; don't add markers or length.
    WithoutTrailer,
}
pub(crate) use Trailer::*;

const fn compute_u32s_needed(len_bytes: usize, trailer: Trailer) -> usize {
    match trailer {
        WithoutTrailer => align_up(len_bytes, WORD_SIZE * BLOCK_WORDS) / WORD_SIZE,
        WithTrailer { total_bits: _ } => {
            // Add one byte for end marker
            let nwords = align_up(len_bytes + 1, WORD_SIZE) / WORD_SIZE;
            // Add two words for length at end (even though we only
            // use one of them, being a 32-bit architecture)
            let nwords = nwords + 2;

            align_up(nwords, BLOCK_WORDS)
        }
    }
}

// Slow path for when we need padding and/or alignment.
fn copy_and_update(
    out_state: *mut Digest,
    mut in_state: *const Digest,
    bytes: &[u8],
    trailer: Trailer,
) {
    let padlen = compute_u32s_needed(bytes.len(), trailer);
    let mut padbuf: Vec<u32> = Vec::with_capacity(padlen);
    assert!(bytes.len() <= padlen * WORD_SIZE);
    // SAFETY: u32 is more stringently aligned than bytes, and we've
    // already checked to make sure the buffer is big enough.
    unsafe {
        let padbuf_u8: *mut u8 = padbuf.as_mut_ptr().cast();
        padbuf_u8.copy_from_nonoverlapping(bytes.as_ptr(), bytes.len());

        match trailer {
            WithTrailer { total_bits: _ } => {
                padbuf_u8.add(bytes.len()).write(END_MARKER);
                padbuf_u8
                    .add(bytes.len() + 1)
                    .write_bytes(0, padlen * WORD_SIZE - bytes.len() - 1)
            }
            WithoutTrailer => {
                padbuf_u8
                    .add(bytes.len())
                    .write_bytes(0, padlen * WORD_SIZE - bytes.len());
            }
        }
        padbuf.set_len(padlen);
    }

    if let WithTrailer { total_bits } = trailer {
        assert_eq!(padbuf[padlen - 1], 0);
        padbuf[padlen - 1] = (total_bits as u32).to_be();
    }

    match bytemuck::pod_align_to::<u32, Block>(padbuf.as_slice()) {
        (&[], blocks @ &[..], &[]) => {
            // SAFETY: This is only called from this crate.  It's perfectly fine
            // for in_state and out_state to point at the same place, and for
            // out_state to be uninitialized memory, and those preclude us
            // from using references.
            if blocks.len() > 0 {
                unsafe {
                    sys_sha_buffer(
                        out_state.cast(),
                        in_state.cast(),
                        bytemuck::cast_slice(blocks).as_ptr(),
                        blocks.len() as u32,
                    );
                }
                in_state = out_state;
            }
        }
        _ => panic!("padbuf should already be aligned and padded"),
    }

    if in_state != out_state {
        unsafe { out_state.write(*in_state) }
    }
}

pub(crate) fn update_u32(
    out_state: *mut Digest,
    mut in_state: *const Digest,
    words: &[u32],
    trailer: Trailer,
) {
    match bytemuck::pod_align_to::<u32, Block>(words) {
        (&[], blocks @ &[..], rest @ &[..]) => {
            // SAFETY: This is only called from this crate.  It's perfectly fine
            // for in_state and out_state to point at the same place, and for
            // out_state to be uninitialized memory, and those preclude us
            // from using references.
            if blocks.len() > 0 {
                unsafe {
                    sys_sha_buffer(
                        out_state.cast(),
                        in_state.cast(),
                        bytemuck::cast_slice(blocks).as_ptr(),
                        blocks.len() as u32,
                    );
                }
                in_state = out_state;
            }

            copy_and_update(out_state, in_state, bytemuck::cast_slice(rest), trailer);
        }
        _ => unreachable!(
            "words should always have sufficient alignment to start on a block boundary"
        ),
    }
}

fn update_u8(out_state: *mut Digest, mut in_state: *const Digest, bytes: &[u8], trailer: Trailer) {
    match bytemuck::pod_align_to::<u8, Block>(bytes) {
        (&[], blocks @ &[..], rest @ &[..]) => {
            // Start is aligned on word boundary.
            // SAFETY: This is only called from this crate.  It's perfectly fine
            // for in_state and out_state to point at the same place, and for
            // out_state to be uninitialized memory, and those preclude us
            // from using references.
            if blocks.len() > 0 {
                unsafe {
                    sys_sha_buffer(
                        out_state.cast(),
                        in_state.cast(),
                        bytemuck::cast_slice(blocks).as_ptr(),
                        blocks.len() as u32,
                    );
                }
                in_state = out_state;
            }
            copy_and_update(out_state, in_state, rest, trailer);
        }
        _ => {
            // Unaligned; copy the whole thing.
            copy_and_update(out_state, in_state, bytes, trailer)
        }
    }
}

/// Computes the SHA256 digest of a serialized object.
pub fn digest<T: Serialize>(val: &T) -> &'static Digest {
    // If the object to be serialized is a plain old structure in memory, this
    // should be a good guess for the allocation needed.
    let approx_len = mem::size_of_val(val);
    let cap = compute_u32s_needed(
        approx_len,
        WithTrailer {
            total_bits: approx_len * 8,
        },
    );
    let buf = to_vec_with_capacity(val, cap).unwrap();

    let trailer = WithTrailer {
        total_bits: buf.len() * 8,
    };

    let digest = alloc_uninit_digest();
    update_u32(digest, &SHA256_INIT, buf.as_slice(), trailer);
    // Now that digest is initialized, we can convert it to a reference.
    unsafe { &*digest }
}

/// A guest-side [Sha] implementation.
///
/// [Sha]: risc0_zkp::core::sha::Sha
#[derive(Debug, Clone)]
pub struct Impl {}

impl risc0_zkp::core::sha::Sha for Impl {
    type DigestPtr = &'static Digest;

    fn hash_bytes(&self, bytes: &[u8]) -> Self::DigestPtr {
        let digest = alloc_uninit_digest();
        update_u8(
            digest,
            &SHA256_INIT,
            bytes,
            WithTrailer {
                total_bits: bytes.len() * 8,
            },
        );
        // Now that digest is initialized, we can convert it to a reference.
        unsafe { &*digest }
    }

    fn hash_raw_words(&self, words: &[u32]) -> Self::DigestPtr {
        let digest = alloc_uninit_digest();
        update_u32(digest, &SHA256_INIT, words, WithoutTrailer);
        // Now that digest is initialized, we can convert it to a reference.
        unsafe { &*digest }
    }

    fn hash_raw_pod_slice<T: bytemuck::Pod>(&self, pod: &[T]) -> Self::DigestPtr {
        let digest = alloc_uninit_digest();
        let words: &[u32] = bytemuck::cast_slice(pod);
        update_u32(digest, &SHA256_INIT, words, WithoutTrailer);
        // Now that digest is initialized, we can convert it to a reference.
        unsafe { &*digest }
    }

    // Generate a new digest by mixing two digests together via XOR,
    // and storing into the first digest.
    fn mix(&self, pool: &mut Self::DigestPtr, val: &Digest) {
        let mut digest = Box::<Digest>::new(Digest::default());
        for i in 0..DIGEST_WORDS {
            digest.get_mut()[i] = pool.get()[i] ^ val.get()[i];
        }
        unsafe {
            let ptr: *const Digest = &*digest;
            *pool = &*ptr
        }
    }

    fn compress(
        &self,
        state: &Digest,
        block_half1: &Digest,
        block_half2: &Digest,
    ) -> &'static Digest {
        let digest = alloc_uninit_digest();
        compress(digest, state, &block_half1.get(), &block_half2.get());
        // Now that digest is initialized, we can convert it to a reference.
        unsafe { &*digest }
    }
}
