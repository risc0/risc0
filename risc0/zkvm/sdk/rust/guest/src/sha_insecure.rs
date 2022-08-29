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

use risc0_zkp::core::sha::{Digest, DIGEST_WORDS, SHA256_INIT};
use risc0_zkvm_platform::{
    io::{
        InsecureShaCompressDescriptor, InsecureShaHashDescriptor, SHADescriptor,
        GPIO_INSECURESHACOMPRESS, GPIO_INSECURESHAHASH, GPIO_SHA,
    },
    memory,
    rt::host_io::host_recv,
    WORD_SIZE,
};

use crate::sha::{add_trailer, compute_capacity_needed, with_sha_trailer, MemoryType};

/// A guest-side [Sha] implementation.
///
/// [Sha]: risc0_zkp::core::sha::Sha
#[derive(Debug, Clone)]
pub struct Impl {}

impl risc0_zkp::core::sha::Sha for Impl {
    type DigestPtr = &'static Digest;

    fn hash_bytes(&self, bytes: &[u8]) -> Self::DigestPtr {
        with_sha_trailer(bytes, |words| {
            self.update(&SHA256_INIT, bytemuck::cast_slice(words))
        })
    }

    fn update(&self, state: &Digest, bytes: &[u8]) -> Self::DigestPtr {
        let desc = &InsecureShaHashDescriptor {
            state: state as *const Digest as u32,
            start: bytes.as_ptr() as u32,
            len: bytes.len() as u32,
        };
        crate::memory_barrier(desc);
        unsafe { GPIO_INSECURESHAHASH.as_ptr().write_volatile(desc) }
        let digest: &[u32; DIGEST_WORDS] = host_recv(DIGEST_WORDS).try_into().unwrap();
        bytemuck::cast_ref(digest)
    }

    fn compress(
        &self,
        state: &Digest,
        block_half1: &Digest,
        block_half2: &Digest,
    ) -> &'static Digest {
        let desc = &InsecureShaCompressDescriptor {
            state: state as *const Digest as u32,
            block_half1: block_half1 as *const Digest as u32,
            block_half2: block_half2 as *const Digest as u32,
        };
        crate::memory_barrier(desc);
        unsafe { GPIO_INSECURESHACOMPRESS.as_ptr().write_volatile(desc) }
        let digest: &[u32; DIGEST_WORDS] = host_recv(DIGEST_WORDS).try_into().unwrap();

        // We expect to take 72 cycles to do this operation in an
        // accelerated circuit.  With optimization, asking the host
        // takes 63 cycles as of this writing.  So, do a little bit of
        // extra work here.
        crate::memory_barrier(&desc.block_half1);

        bytemuck::cast_ref(digest)
    }

    fn hash_raw_words(&self, words: &[u32]) -> Self::DigestPtr {
        self.update(&SHA256_INIT, bytemuck::cast_slice(words))
    }

    fn hash_raw_pod_slice<T: bytemuck::Pod>(&self, pod: &[T]) -> Self::DigestPtr {
        let u8s: &[u8] = bytemuck::cast_slice(pod);
        self.update(&SHA256_INIT, u8s)
    }

    // Generate a new digest by mixing two digests together via XOR,
    // and storing into the first digest.
    fn mix(&self, pool: &mut Self::DigestPtr, val: &Digest) {
        crate::sha::Impl {}.mix(pool, val)
    }
}
