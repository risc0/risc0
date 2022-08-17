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

use crate::core::sha::{Digest, BLOCK_WORDS};
use alloc::{borrow::Cow, vec::Vec};
use risc0_zkvm_platform::abi::{sha_digest_u8_slice, sha_raw_digest};

use bytemuck;

// TODO: Figure out a better way to resolve this circular dependency.
// Perhaps risc0_zkvm_guest should not have a dependency on zkp?  Or
// maybe risc0_zkvm_guest::sha should move to risc0_zkvm_platform?

pub fn hash_bytes(bytes: &[u8]) -> Cow<'static, Digest> {
    Cow::Borrowed(bytemuck::cast_ref(sha_digest_u8_slice(bytes)))
}

pub fn hash_raw_words(words: &[u32]) -> Cow<'static, Digest> {
    let mut wordbuf: Vec<u32>;
    // Add padding if necessary.
    let words = if words.len() % 16 != 0 {
        let padded_len = ((words.len() + BLOCK_WORDS - 1) / BLOCK_WORDS) * BLOCK_WORDS;
        wordbuf = Vec::with_capacity(padded_len);
        wordbuf.extend(words);
        wordbuf.resize(padded_len, 0);
        wordbuf.as_slice()
    } else {
        words
    };

    Cow::Borrowed(bytemuck::cast_ref(sha_raw_digest(words)))
}

pub fn hash_pair(a: &Digest, b: &Digest) -> Cow<'static, Digest> {
    let block: [Digest; 2] = [*a, *b];
    Cow::Borrowed(bytemuck::cast_ref(sha_raw_digest(bytemuck::cast_slice(
        &block,
    ))))
}
