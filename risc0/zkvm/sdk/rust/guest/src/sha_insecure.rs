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

use alloc_crate::vec::Vec;

use risc0_zkp::core::sha::{Digest, DIGEST_WORDS};
use risc0_zkvm_platform::{
    io::InsecureShaDescriptor,
    io::{SHADescriptor, GPIO_INSECURESHA256COMPRESS, GPIO_SHA},
    memory,
    rt::host_io::host_recv,
    WORD_SIZE,
};

use crate::sha::{add_trailer, compute_capacity_needed, with_sha_trailer, MemoryType};

/// Makes a digest for a slice of bytes.
fn digest_u8_slice(data: &[u8]) -> &'static Digest {
    with_sha_trailer(data, |slice| raw_digest(slice))
}

static SHA256_INIT: Digest = Digest::new([
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19,
]);

fn raw_digest(words: &[u32]) -> &'static Digest {
    let mut state = &SHA256_INIT;
    let mut blocks = words.chunks_exact(DIGEST_WORDS * 2);
    for block in blocks.by_ref() {
        state = compress256(
            bytemuck::cast_ref(state),
            bytemuck::cast_slice(&block[0..DIGEST_WORDS])
                .try_into()
                .unwrap(),
            bytemuck::cast_slice(&block[DIGEST_WORDS..])
                .try_into()
                .unwrap(),
        );
    }

    assert!(blocks.remainder().is_empty());
    state
}

// Normally we use u32s for everything, but the host doesn't mind
// unaligned reads, so we can send it u8s.
fn compress256(
    state: &Digest,
    block_half1: &[u8; DIGEST_WORDS * WORD_SIZE],
    block_half2: &[u8; DIGEST_WORDS * WORD_SIZE],
) -> &'static Digest {
    let desc = &InsecureShaDescriptor {
        state: state as *const Digest as u32,
        block_half1: block_half1.as_ptr() as u32,
        block_half2: block_half2.as_ptr() as u32,
    };
    crate::memory_barrier(desc);
    unsafe { GPIO_INSECURESHA256COMPRESS.as_ptr().write_volatile(desc) }
    let digest: &[u32; DIGEST_WORDS] = host_recv(DIGEST_WORDS).try_into().unwrap();
    bytemuck::cast_ref(digest)
}

/// A guest-side [Sha] implementation.
///
/// [Sha]: risc0_zkp::core::sha::Sha
#[derive(Debug, Clone)]
pub struct Impl {}

impl risc0_zkp::core::sha::Sha for Impl {
    type DigestPtr = &'static Digest;

    fn hash_bytes(&self, bytes: &[u8]) -> Self::DigestPtr {
        digest_u8_slice(bytes)
    }

    fn hash_pair(&self, a: &Digest, b: &Digest) -> Self::DigestPtr {
        compress256(&SHA256_INIT, bytemuck::cast_ref(a), bytemuck::cast_ref(b))
    }

    fn hash_raw_words(&self, words: &[u32]) -> Self::DigestPtr {
        raw_digest(words)
    }

    fn hash_raw_pod_slice<T: bytemuck::Pod>(&self, pod: &[T]) -> Self::DigestPtr {
        let u8s: &[u8] = bytemuck::cast_slice(pod);

        let mut state = &SHA256_INIT;
        let mut maybe_half_block1: Option<&[u8; DIGEST_WORDS * WORD_SIZE]> = None;

        let half_blocks = u8s.chunks_exact(DIGEST_WORDS * WORD_SIZE);
        let mut padded: [u8; DIGEST_WORDS * WORD_SIZE] = [0; DIGEST_WORDS * WORD_SIZE];
        let mut padded = match half_blocks.remainder() {
            [] => half_blocks.chain(None),
            rem @ &[..] => {
                padded[0..rem.len()].clone_from_slice(rem);
                half_blocks.chain(Some(padded.as_slice()))
            }
        };
        loop {
            let half_block1 = match padded.next() {
                Some(half_block1) => half_block1,
                None => break,
            };

            let half_block2 = match padded.next() {
                Some(half_block2) => half_block2,
                None => &[0; DIGEST_WORDS * WORD_SIZE],
            };

            state = compress256(
                state,
                half_block1.try_into().unwrap(),
                half_block2.try_into().unwrap(),
            );
        }

        state
    }

    // Generate a new digest by mixing two digests together via XOR,
    // and storing into the first digest.
    fn mix(&self, pool: &mut Self::DigestPtr, val: &Digest) {
        crate::sha::Impl {}.mix(pool, val)
    }
}
