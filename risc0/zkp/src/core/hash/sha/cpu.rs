// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! Simple wrappers for a CPU-based SHA-256 implementation.

use alloc::{boxed::Box, vec::Vec};
use core::slice;

use sha2::{
    Digest as _,
    digest::generic_array::{GenericArray, typenum::U64},
};

use super::{Block, SHA256_INIT, Sha256};
use crate::core::digest::{DIGEST_WORDS, Digest};

/// A CPU-based [Sha256] implementation.
#[derive(Default, Clone)]
pub struct Impl {}

fn set_word(buf: &mut [u8], idx: usize, word: u32) {
    buf[(4 * idx)..(4 * idx + 4)].copy_from_slice(&word.to_ne_bytes());
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
        Self::hash_bytes(bytemuck::cast_slice(words))
    }

    #[inline]
    fn hash_raw_data_slice<T: bytemuck::NoUninit>(data: &[T]) -> Self::DigestPtr {
        let u8s: &[u8] = bytemuck::cast_slice(data);
        let mut state: [u32; DIGEST_WORDS] = SHA256_INIT.into();
        for word in state.iter_mut() {
            *word = word.to_be();
        }
        let mut blocks = u8s.chunks_exact(64);
        for block in blocks.by_ref() {
            sha2::compress256(&mut state, slice::from_ref(GenericArray::from_slice(block)));
        }
        let remainder = blocks.remainder();
        if !remainder.is_empty() {
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

        // Reinterpret the RISC Zero blocks as GenericArray<u8, U64>.
        // SAFETY: We know that the two types have the same memory layout, so this
        // conversion is known to be safe.
        match unsafe { blocks.align_to::<GenericArray<u8, U64>>() } {
            (&[], aligned_blocks, &[]) => sha2::compress256(&mut state, aligned_blocks),
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
        crate::core::hash::sha::testutil::test_sha_impl::<Impl>();
    }
}
