// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

extern crate alloc;

use alloc::vec::Vec;
use core::{borrow::Borrow, mem::size_of};

use risc0_zkp::core::{
    digest::{DIGEST_BYTES, Digest},
    hash::sha::Sha256,
};

/// Defines a collision resistant hash for the typed and structured data.
pub trait Digestible {
    /// Calculate a collision resistant hash for the typed and structured data.
    fn digest<S: Sha256>(&self) -> Digest;
}

impl Digestible for [u8] {
    fn digest<S: Sha256>(&self) -> Digest {
        *S::hash_bytes(self)
    }
}

impl Digestible for Vec<u8> {
    fn digest<S: Sha256>(&self) -> Digest {
        *S::hash_bytes(self)
    }
}

impl<D: Digestible> Digestible for [D] {
    /// A default incremental hashing algorithm for a slice of Digestible elements.
    ///
    /// This hashing routine may not be appropriate for add use cases. In particular, it is not a
    /// PRF and cannot be used as a MAC. Given a digest of a list, anyone can compute the digest of
    /// that list with additional elements appended to the front of the list. It also does not
    /// domain separate typed data, and the digest of an empty slice is the zero digest.
    fn digest<S: Sha256>(&self) -> Digest {
        self.iter().rfold(Digest::ZERO, |accum, item| {
            *S::hash_bytes(&[accum.as_bytes(), item.digest::<S>().as_bytes()].concat())
        })
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

/// A struct hashing routine, permitting tree-like opening of fields.
///
/// Used for hashing of the receipt claim, and in the recursion predicates.
pub fn tagged_struct<S: Sha256>(tag: &str, down: &[impl Borrow<Digest>], data: &[u32]) -> Digest {
    let tag_digest: Digest = *S::hash_bytes(tag.as_bytes());
    #[allow(clippy::manual_slice_size_calculation)]
    let mut all = Vec::<u8>::with_capacity(
        DIGEST_BYTES * (down.len() + 1) + size_of::<u32>() * data.len() + size_of::<u16>(),
    );
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

/// A list hashing routine, permitting iterative opening over elements.
///
/// Used for hashing of the receipt claim assumptions list, and in the recursion
/// predicates.
pub fn tagged_iter<S: Sha256>(
    tag: &str,
    iter: impl DoubleEndedIterator<Item = impl Borrow<Digest>>,
) -> Digest {
    iter.rfold(Digest::ZERO, |list_digest, elem| {
        tagged_list_cons::<S>(tag, elem.borrow(), &list_digest)
    })
}

/// A list hashing routine, permitting iterative opening over elements.
///
/// Used for hashing of the receipt claim assumptions list, and in the recursion
/// predicates.
pub fn tagged_list<S: Sha256>(tag: &str, list: &[impl Borrow<Digest>]) -> Digest {
    tagged_iter::<S>(tag, list.iter().map(|x| x.borrow()))
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
pub fn tagged_list_cons<S: Sha256>(tag: &str, head: &Digest, tail: &Digest) -> Digest {
    tagged_struct::<S>(tag, &[head, tail], &[])
}

#[cfg(test)]
mod tests {
    use risc0_zkp::core::hash::sha::cpu;

    use super::{Digest, tagged_struct};

    #[test]
    fn test_tagged_struct() {
        let digest1 = tagged_struct::<cpu::Impl>("foo", &Vec::<Digest>::new(), &[1, 2013265920, 3]);
        let digest2 = tagged_struct::<cpu::Impl>("bar", &[digest1, digest1], &[2013265920, 5]);
        let digest3 = tagged_struct::<cpu::Impl>(
            "baz",
            &[digest1, digest2, digest1],
            &[6, 7, 2013265920, 9, 10],
        );

        println!("digest = {digest3:?}");
        assert_eq!(
            digest3.to_string(),
            "9ff20cc6d365efa2af09181772f49013d05cdee6da896851614cae23aa5dd442"
        );
    }
}
