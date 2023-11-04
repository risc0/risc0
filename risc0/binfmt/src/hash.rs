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

extern crate alloc;

use alloc::vec::Vec;
use core::borrow::Borrow;

use risc0_zkp::core::{digest::Digest, hash::sha::Sha256};

/// Defines a collision resistant hash for the typed and structured data.
pub trait Digestible {
    /// Calculate a collision resistant hash for the typed and structured data.
    fn digest<S: Sha256>(&self) -> Digest;
}

impl Digestible for [u8] {
    fn digest<S: Sha256>(&self) -> Digest {
        *S::hash_bytes(&self)
    }
}

impl Digestible for Vec<u8> {
    fn digest<S: Sha256>(&self) -> Digest {
        *S::hash_bytes(&self)
    }
}

impl<T: Digestible> Digestible for Option<T> {
    fn digest<S: Sha256>(&self) -> Digest {
        match self {
            Some(val) => val.digest::<S>(),
            None => Digest::ZERO,
        }
    }
}

/// A struct hashing routine, permiting tree-like opening of fields.
///
/// Used for hashing of receipt metadata, and in the recursion predicates.
pub fn tagged_struct<S: Sha256>(tag: &str, down: &[impl Borrow<Digest>], data: &[u32]) -> Digest {
    let tag_digest: Digest = *S::hash_bytes(tag.as_bytes());
    let mut all = Vec::<u8>::new();
    all.extend_from_slice(tag_digest.as_bytes());
    for digest in down {
        all.extend_from_slice(digest.borrow().as_ref());
    }
    for word in data.iter().copied() {
        all.extend_from_slice(&word.to_le_bytes());
    }
    let down_count: u16 = down
        .len()
        .try_into()
        .expect("struct defined with more than 2^16 fields");
    all.extend_from_slice(&down_count.to_le_bytes());
    *S::hash_bytes(&all)
}

/// A list hashing routine, permiting iterative opening over elements.
///
/// Used for hashing of receipt metadata assumptions list, and in the recursion
/// predicates.
pub fn tagged_list<S: Sha256>(tag: &str, list: &[impl Borrow<Digest>]) -> Digest {
    list.into_iter()
        .rev()
        .fold(Digest::ZERO, |list_digest, elem| {
            tagged_list_cons::<S>(tag, elem.borrow(), &list_digest)
        })
}

/// Calculate the hash resulting from adding one element to a [tagged_list]
/// digest.
///
/// This function logically pushes the element `head` onto the front of the
/// list.
///
/// ```rust
/// use risc0_zkp::core::hash::sha::{cpu::Impl, Sha256};
/// use risc0_binfmt::{tagged_list, tagged_list_cons};
///
/// let [a, b, c] = [
///     *Impl::hash_bytes(b"a".as_slice()),
///     *Impl::hash_bytes(b"b".as_slice()),
///     *Impl::hash_bytes(b"c".as_slice()),
/// ];
/// assert_eq!(
///     tagged_list::<Impl>("tag", &[a, b, c]),
///     tagged_list_cons::<Impl>("tag", &a, &tagged_list::<Impl>("tag", &[b, c])),
/// );
/// ```
pub fn tagged_list_cons<S: Sha256>(tag: &str, head: &Digest, rest: &Digest) -> Digest {
    tagged_struct::<S>(tag, &[head, rest], &[])
}

#[cfg(test)]
mod tests {
    use risc0_zkp::core::hash::sha::cpu;

    use super::{tagged_struct, Digest};

    #[test]
    fn test_tagged_struct() {
        let digest1 = tagged_struct::<cpu::Impl>("foo", &Vec::<Digest>::new(), &[1, 2013265920, 3]);
        let digest2 = tagged_struct::<cpu::Impl>("bar", &[digest1, digest1], &[2013265920, 5]);
        let digest3 = tagged_struct::<cpu::Impl>(
            "baz",
            &[digest1, digest2, digest1],
            &[6, 7, 2013265920, 9, 10],
        );

        println!("digest = {:?}", digest3);
        assert_eq!(
            digest3.to_string(),
            "9ff20cc6d365efa2af09181772f49013d05cdee6da896851614cae23aa5dd442"
        );
    }
}
