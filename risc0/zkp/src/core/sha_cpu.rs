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

//! Simple wrappers for a CPU-based SHA-256 implementation.

use alloc::{boxed::Box, vec::Vec};
use core::slice;

use sha2::{
    digest::generic_array::{typenum::U64, GenericArray},
    Digest as _,
};

use super::sha::{Block, Digest, Sha256, DIGEST_WORDS, SHA256_INIT};

/// A CPU-based [Sha256] implementation.
#[derive(Default, Clone)]
pub struct Impl {}

fn set_word(buf: &mut [u8], idx: usize, word: u32) {
    buf[(4 * idx)..(4 * idx + 4)].copy_from_slice(&word.to_ne_bytes());
}

impl Impl {
    /// Compute the hash of a slice of plain-old-data using the
    /// specified offset and stride. 'size' specifies the number of
    /// elements to hash.
    pub fn hash_pod_stride<T: bytemuck::Pod>(
        pods: &[T],
        offset: usize,
        size: usize,
        stride: usize,
    ) -> Box<Digest> {
        // Because bytes in our digests are in big-endian order, regardless of host
        // architecture, and the `sha2::compress256` function takes words in native
        // byte order, the bytes of the IV need to be flipped on little-endian
        // machines (e.g. x86).
        let mut state: [u32; DIGEST_WORDS] = SHA256_INIT.into();
        for word in state.iter_mut() {
            *word = word.to_be();
        }

        let mut block: GenericArray<u8, U64> = GenericArray::default();

        // Construct an Iterator<u8> with the given, offset, stride, and size in items.
        let mut bytes = pods
            .iter()
            .skip(offset)
            .step_by(stride)
            .take(size)
            .flat_map(|pod| bytemuck::cast_slice(slice::from_ref(pod)) as &[u8])
            .copied()
            .fuse();

        let mut off = 0;
        while let Some(b1) = bytes.next() {
            let b2 = bytes.next().unwrap_or(0);
            let b3 = bytes.next().unwrap_or(0);
            let b4 = bytes.next().unwrap_or(0);
            set_word(
                block.as_mut_slice(),
                off,
                u32::from_ne_bytes([b1, b2, b3, b4]),
            );
            off += 1;
            if off == 16 {
                sha2::compress256(&mut state, slice::from_ref(&block));
                off = 0;
            }
        }
        if off != 0 {
            block[off * 4..].fill(0);
            sha2::compress256(&mut state, slice::from_ref(&block));
        }

        // Flip the bytes back to big-endian order from native order.
        for word in state.iter_mut() {
            *word = word.to_be();
        }
        Box::new(Digest::from(state))
    }
}

impl Sha256 for Impl {
    type DigestPtr = Box<Digest>;

    fn hash_bytes(bytes: &[u8]) -> Self::DigestPtr {
        let digest = sha2::Sha256::digest(bytes);
        let words: Vec<u32> = digest
            .as_slice()
            .chunks(4)
            .map(|chunk| u32::from_ne_bytes(chunk.try_into().unwrap()))
            .collect();
        Box::new(Digest::from(
            <[u32; DIGEST_WORDS]>::try_from(words).unwrap(),
        ))
    }

    fn hash_words(words: &[u32]) -> Self::DigestPtr {
        Self::hash_bytes(bytemuck::cast_slice(words) as &[u8])
    }

    #[inline]
    fn hash_raw_pod_slice<T: bytemuck::Pod>(pod: &[T]) -> Self::DigestPtr {
        let u8s: &[u8] = bytemuck::cast_slice(pod);
        let mut state: [u32; DIGEST_WORDS] = SHA256_INIT.into();
        for word in state.iter_mut() {
            *word = word.to_be();
        }
        let mut blocks = u8s.chunks_exact(64);
        for block in blocks.by_ref() {
            sha2::compress256(&mut state, slice::from_ref(GenericArray::from_slice(block)));
        }
        let remainder = blocks.remainder();
        if remainder.len() > 0 {
            let mut last_block: GenericArray<u8, U64> = GenericArray::default();
            bytemuck::cast_slice_mut(last_block.as_mut_slice())[..remainder.len()]
                .clone_from_slice(remainder);
            sha2::compress256(&mut state, slice::from_ref(&last_block));
        }
        for word in state.iter_mut() {
            *word = word.to_be();
        }
        Box::new(Digest::from(state))
    }

    // Digest two digest into one
    #[inline]
    fn compress(
        orig_state: &Digest,
        block_half1: &Digest,
        block_half2: &Digest,
    ) -> Self::DigestPtr {
        // Convert the state from big-endian to native byte order.
        let mut state: [u32; DIGEST_WORDS] = *orig_state.as_ref();
        for word in state.iter_mut() {
            *word = word.to_be();
        }

        // Half-blocks may not be contiguous so they must be copied here.
        let mut block: GenericArray<u8, U64> = GenericArray::default();
        for i in 0..8 {
            set_word(block.as_mut_slice(), i, block_half1.as_words()[i]);
            set_word(block.as_mut_slice(), 8 + i, block_half2.as_words()[i]);
        }
        sha2::compress256(&mut state, slice::from_ref(&block));

        // Convert the state from big-endian to native byte order.
        for word in state.iter_mut() {
            *word = word.to_be();
        }
        Box::new(Digest::from(state))
    }

    #[inline]
    fn compress_slice(orig_state: &Digest, blocks: &[Block]) -> Self::DigestPtr {
        // Convert the state from big-endian to native byte order.
        let mut state: [u32; DIGEST_WORDS] = *orig_state.as_ref();
        for word in state.iter_mut() {
            *word = word.to_be();
        }

        // Reinterpret the RISC0 blocks as GenericArray<u8, U64>.
        // SAFETY: We know that the two types have the same memory layout, so this
        // conversion is known to be safe.
        match unsafe { blocks.align_to::<GenericArray<u8, U64>>() } {
            (&[], aligned_blocks, &[]) => sha2::compress256(&mut state, &aligned_blocks),
            _ => unreachable!("alignment will always be satisfied for block conversion"),
        };

        // Convert the native byte order result to big-endian.
        for word in state.iter_mut() {
            *word = word.to_be();
        }
        Box::new(Digest::from(state))
    }
}

#[cfg(test)]
mod tests {
    use super::Impl;

    #[test]
    fn test_impl() {
        crate::core::sha::testutil::test_sha_impl::<Impl>();
    }
}
