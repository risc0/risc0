// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! Functions for computing SHA-256 hashes.

use alloc::vec::Vec;

use crate::core::{
    digest::Digest,
    hash::sha::{BLOCK_WORDS, Block, SHA256_INIT},
};
use risc0_zkvm_platform::{
    WORD_SIZE, align_up,
    syscall::{sys_sha_buffer, sys_sha_compress},
};

// FIP 180-4 specifies that the bit-string being hashed should have a `1`
// appended to it before padding.
const END_MARKER: u8 = 0x80;

fn alloc_uninit_digest() -> *mut Digest {
    extern crate alloc;
    use core::alloc::Layout;
    unsafe { alloc::alloc::alloc(Layout::from_size_align(64, 4).unwrap()).cast() }
}

fn compress(
    out_state: *mut Digest,
    in_state: *const Digest,
    block_half1: &Digest,
    block_half2: &Digest,
) {
    // SAFETY: This is only called from this crate.  It's perfectly fine
    // for in_state and out_state to point at the same place, and for
    // out_state to be uninitialized memory, and those preclude us
    // from using references.
    unsafe {
        sys_sha_compress(
            out_state.cast(),
            in_state.cast(),
            block_half1.as_ref(),
            block_half2.as_ref(),
        );
    }
}

fn compress_slice(out_state: *mut Digest, in_state: *const Digest, blocks: &[Block]) {
    // SAFETY: This is only called from this crate. It's perfectly fine
    // for in_state and out_state to point at the same place, and for
    // out_state to be uninitialized memory, and those preclude us
    // from using references.
    unsafe {
        sys_sha_buffer(
            out_state.cast(),
            in_state.cast(),
            bytemuck::cast_slice(blocks).as_ptr(),
            blocks.len() as u32,
        );
    }
}

#[derive(PartialEq, Eq, Debug, Copy, Clone)]
pub(crate) enum Trailer {
    /// Add a SHA-standard trailer with an end marker and the given number of
    /// bits
    WithTrailer { total_bits: u32 },
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
        padbuf[padlen - 1] = total_bits.to_be();
    }

    match bytemuck::pod_align_to::<u32, Block>(padbuf.as_slice()) {
        (&[], blocks @ &[..], &[]) => {
            // SAFETY: This is only called from this crate.  It's perfectly fine
            // for in_state and out_state to point at the same place, and for
            // out_state to be uninitialized memory, and those preclude us
            // from using references.
            if !blocks.is_empty() {
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
            if !blocks.is_empty() {
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
            if !blocks.is_empty() {
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

/// A guest-side [Sha256] implementation.
///
/// [Sha256]: crate::core::hash::sha::Sha256
#[derive(Debug, Clone, Default)]
pub struct Impl {}

impl crate::core::hash::sha::Sha256 for Impl {
    type DigestPtr = &'static mut Digest;

    fn hash_bytes(bytes: &[u8]) -> Self::DigestPtr {
        let digest = alloc_uninit_digest();
        update_u8(
            digest,
            &SHA256_INIT,
            bytes,
            WithTrailer {
                total_bits: bytes.len() as u32 * 8,
            },
        );
        // Now that digest is initialized, we can convert it to a reference.
        unsafe { &mut *digest }
    }

    fn hash_words(words: &[u32]) -> Self::DigestPtr {
        let digest = alloc_uninit_digest();
        update_u32(
            digest,
            &SHA256_INIT,
            words,
            WithTrailer {
                total_bits: words.len() as u32 * 32,
            },
        );
        // Now that digest is initialized, we can convert it to a reference.
        unsafe { &mut *digest }
    }

    fn hash_raw_data_slice<T: bytemuck::NoUninit>(data: &[T]) -> Self::DigestPtr {
        let digest = alloc_uninit_digest();
        let words: &[u32] = bytemuck::cast_slice(data);
        update_u32(digest, &SHA256_INIT, words, WithoutTrailer);
        // Now that digest is initialized, we can convert it to a reference.
        unsafe { &mut *digest }
    }

    fn compress(state: &Digest, block_half1: &Digest, block_half2: &Digest) -> Self::DigestPtr {
        let digest = alloc_uninit_digest();
        compress(digest, state, block_half1, block_half2);
        // Now that digest is initialized, we can convert it to a reference.
        unsafe { &mut *digest }
    }

    fn compress_slice(state: &Digest, blocks: &[Block]) -> Self::DigestPtr {
        let digest = alloc_uninit_digest();
        compress_slice(digest, state, blocks);
        // Now that digest is initialized, we can convert it to a reference.
        unsafe { &mut *digest }
    }
}
