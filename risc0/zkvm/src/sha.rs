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
// in the zkVM guest. Users can simply `use risc0_zkvm::sha::Impl`.
cfg_if::cfg_if! {
    if #[cfg(target_os = "zkvm")] {
        pub use crate::guest::sha::Impl;
    } else {
        pub use risc0_zkp::core::sha_cpu::Impl;
    }
}

pub mod rust_crypto {
    //! [Rust Crypto] wrappers for the RISC0 Sha256 trait.
    //!
    //! [Rust Crypto]: https://github.com/RustCrypto
    //!
    //! # Usage
    //!
    //! ```rust
    //! use risc0_zkvm::sha::rust_crypto::{Sha256, Digest as _};
    //!
    //! // create a Sha256 object
    //! let mut hasher = Sha256::new();
    //!
    //! // write input message
    //! hasher.update(b"hello world");
    //!
    //! // read hash digest and consume hasher
    //! let result = hasher.finalize();
    //!
    //! assert_eq!(hex::encode(result), "b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9");
    //!
    //! // more concise version of the code above.
    //! assert_eq!(hex::encode(Sha256::digest(b"hello world")),
    //!     "b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9"
    //! );
    //! ```
    // NOTE: When used on the host, these functions are strictly less efficient,
    // with the primary loss being passing blocks received through the
    // RustCrypto interface as [u8] into blocks compatible with the RISC0
    // interface of [u32] which has stricter alignment and therefore may require
    // a copy. When on the host, this gets pass _back_ to the RustCrypto [sha2]
    // crate meaning that copy was wasted. This is the result of prioritizing code
    // factoring and guest performance over host performance.

    use risc0_zkp::core::sha::rust_crypto;
    pub use rust_crypto::Digest;

    /// Sha256 is a [Rust Crypto] wrapper on the RISC Zero SHA-256
    /// implementations. This type will automatically select the correct
    /// implementation for usage in the zkVM guest and on the host.
    pub type Sha256 = rust_crypto::Sha256<super::Impl>;
}
