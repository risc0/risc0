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

#![doc = include_str!("../README.md")]
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
pub use risc0_zkvm_platform::WORD_SIZE;
pub use serialize::{serialize, Alloc, AllocBuf, Serialize};
use util::as_words_padded;

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
