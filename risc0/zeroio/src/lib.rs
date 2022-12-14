// Copyright 2022 RISC Zero, Inc.
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

//! Zeroio provides utilities to communicate efficiently with the guest.
//!
//! This is similar to serde's "Serialize" and "Deserialize", but has
//! different design targets:
//!
//! * Guest runtime performance is paramount.
//! * It's a significant performance degradation for the guest to have to read a
//!   value that's not aligned on a 32-bit boundary.
//! * Space efficiency is nice, but less important than guest runtime
//!   performance.
//! * We want to conveniently be able to take cryptographic hashes of a
//!   structure.
//!
//! In response, zeroio does these things differently than serde:
//!
//! * There is only one on-wire format; zeroio does not try to be as featureful
//!   as serde.
//! * Datatypes available are much more limited
//! * We don't want to spend any cycles deserializing or copying, so we store
//!   the data in a format that's easy to access without copying, similarly to
//!   the `rkyv' crate.
//! * In contrast to rkyv, we use slices instead of pointers to refer to
//!   available serialized data.  This allows us to avoid unsafe code.
//! * We store all data buffers as [u32] (as opposed to the more common [u8]).
//! * There is one canonical format; any serialization of the same data will
//!   construct the same structure.  To take a cryptographic hash, we simply
//!   hash the [u32] slice.
//! * We null-pad all data buffers up to the size of the hash block (with one
//!   word remaining) to avoid copying when computing a hash.
//!
//! Note that for deserializing, while we guarantee sha(a) == sha(b)
//! implies deserialize_from(a) == deserialize_from(b), we do not
//! guarantee the converse, that deserialize_from(a) ==
//! deserialize_from(b) implies a == b.

#![cfg_attr(not(feature = "std"), no_std)]

extern crate alloc;

pub mod deserialize;
pub mod serialize;
#[cfg(test)]
mod serialize_test;
#[cfg(test)]
pub mod tests;
mod util;

pub use deserialize::{Deserialize, DeserializeOwned};
pub use risc0_zeroio_derive::{Deserialize, Serialize};
pub use serialize::{serialize, Alloc, AllocBuf, Serialize};
use util::as_words_padded;

pub const WORD_SIZE: usize = 4;
pub const PAD_WORDS: usize = 8;

pub type Result<T> = core::result::Result<T, ZeroioError>;

#[derive(Debug)]
pub enum ZeroioError {
    AllocationSizeMismatch,
    FillOverrun,
}

impl core::fmt::Display for ZeroioError {
    fn fmt(&self, f: &mut core::fmt::Formatter) -> core::fmt::Result {
        match self {
            ZeroioError::AllocationSizeMismatch => {
                write!(f, "Allocation mismatch during serialization")
            }
            ZeroioError::FillOverrun => write!(f, "Structure filled up more than it allocated"),
        }
    }
}

pub const fn align_bytes_to_words(bytes: usize) -> usize {
    (bytes + WORD_SIZE - 1) / WORD_SIZE
}

pub(crate) fn pad_words(words: usize) -> usize {
    ((words + PAD_WORDS - 1) / PAD_WORDS) * PAD_WORDS
}

pub fn to_vec<T: Serialize>(val: &T) -> Result<alloc::vec::Vec<u32>> {
    serialize::serialize(val)
}

pub fn from_slice<'a, T: Deserialize<'a>>(words: &'a [u32]) -> Result<T::RefType> {
    Ok(T::deserialize_from(words))
}
