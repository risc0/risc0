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

//! SHA-256 hashing services

pub use risc0_zkp::core::sha::{
    Digest, Sha256, BLOCK_BYTES, DIGEST_BYTES, DIGEST_WORDS, SHA256_INIT, WORD_SIZE,
};

// Pick the appropriate implementation of SHA-256 depending on whether we are
// in the zkVM guest.
// TODO(victor): Should I rename this to something other than Impl?
cfg_if::cfg_if! {
    if #[cfg(target_os = "zkvm")] {
        pub use crate::guest::sha::Impl;
    } else {
        pub use risc0_zkp::core::sha_cpu::Impl;
    }
}

pub mod rust_crypto {
    use risc0_zkp::core::sha::rust_crypto;
    pub use rust_crypto::Digest;

    pub type Sha256 = rust_crypto::Sha256<super::Impl>;
}
