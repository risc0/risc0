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

pub use risc0_zkp::core::sha::{
    Digest, Sha, BLOCK_SIZE, DIGEST_BYTES, DIGEST_WORDS, DIGEST_WORD_SIZE, SHA256_INIT,
};

// Pick the appropriate implementation of SHA-256 depending on whether we are
// in the zkVM guest.
cfg_if::cfg_if! {
    if #[cfg(target_os = "zkvm")] {
        pub use crate::guest::sha::Impl;
    } else {
        pub use risc0_zkp::core::sha_cpu::Impl;
    }
}

const IMPL: Impl = Impl {};

/// Get a Sha implementation for the platform that is being compiled to.
/// On the host, this will return a CPU implementation. In the zkVM guest this
/// will return the guest implementation, which uses the SHA2 coprocessor inside
/// the RISCV circuit.
pub const fn sha() -> &'static impl Sha {
    &IMPL
}
