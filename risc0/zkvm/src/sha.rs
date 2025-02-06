// Copyright 2024 RISC Zero, Inc.
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
//!
//! Support for SHA-256 hashing compatible with the on-circuit SHA acceleration
//! available in the guest. This module can be used from both the host and the
//! guest -- it will detect the build environment and select the appropriate
//! implementation.
//!
//! # Usage
//!
//! We provide two interfaces for SHA hashing. The first interface is based on
//! [Rust Crypto](https://github.com/RustCrypto) wrappers and can be found in
//! the [rust_crypto] module, along with documentation and usage notes.
//!
//! The other interface is to directly use an implementation of the [Sha256]
//! trait defined in this module:
//! ```rust
//! use risc0_zkvm::sha::{Impl, Sha256};
//!
//! // Hash a u8 array
//! let data = [1_u8, 2, 5, 14];
//! let hash = Impl::hash_bytes(&data);
//!
//! // Hash a String
//! let abc = String::from("abc");
//! let abc_hash = Impl::hash_bytes(&abc.as_bytes());
//!
//! // Hash a Digest
//! let hash_hash = Impl::hash_bytes(&hash.as_bytes());
//! // Hashing can also be done with 32-bit words (matching the zkVM word size)
//! let hash_hash_words = Impl::hash_words(&hash.as_words());
//! // Hashing with bytes or words should not change the result
//! assert_eq!(hash_hash, hash_hash_words);
//! ```

pub use risc0_zkp::core::{
    digest::{Digest, DIGEST_BYTES, DIGEST_SHORTS, DIGEST_WORDS},
    hash::sha::{Block, Sha256, BLOCK_BYTES, BLOCK_WORDS, SHA256_INIT, WORD_SIZE},
};

// This Impl selects the appropriate implementation of SHA-256 depending on whether we are
// in the zkVM guest. Users can simply `use risc0_zkvm::sha::Impl`.
pub use risc0_zkp::core::hash::sha::Impl;

/// Defines a collision resistant hash for the typed and structured data.
pub trait Digestible {
    /// Calculate a collision resistant hash for the typed and structured data.
    fn digest(&self) -> Digest;
}

impl<D: ?Sized + risc0_binfmt::Digestible> Digestible for D {
    /// Calculate a collision resistant hash for the typed and structured data.
    fn digest(&self) -> Digest {
        self.digest::<Impl>()
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

    use risc0_zkp::core::hash::sha::rust_crypto;
    pub use rust_crypto::{Digest, Output};

    /// Sha256 is a [Rust Crypto] wrapper on the RISC Zero SHA-256
    /// implementations. This type will automatically select the correct
    /// implementation for usage in the zkVM guest and on the host.
    pub type Sha256 = rust_crypto::Sha256<super::Impl>;
}
