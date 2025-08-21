// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! Claim types and utilities for the zkVM.

use borsh::{BorshDeserialize, BorshSerialize};
use risc0_binfmt::Digestible;
use risc0_zkp::core::digest::Digest;
use serde::{Deserialize, Serialize};

use crate::sha::Sha256;

pub(crate) mod maybe_pruned;
#[cfg(feature = "prove")]
pub(crate) mod merge;
pub(crate) mod receipt;
pub(crate) mod work;

/// A receipt (e.g. [SuccinctReceipt][crate::SuccinctReceipt]) may have an unknown claim type when
/// only the digest of the claim is needed, and the full claim value cannot be determined by the
/// compiler. This allows for a collection of receipts to be created even when the underlying
/// claims are of heterogeneous types (e.g. `Vec<SuccinctReceipt<Unknown>>`).
///
/// Note that this is an uninhabited type, similar to the [never type].
///
/// [never type]: https://doc.rust-lang.org/std/primitive.never.html
#[derive(Clone, Debug, Serialize, Deserialize)]
#[cfg_attr(test, derive(PartialEq))]
pub enum Unknown {}

impl Digestible for Unknown {
    fn digest<S: Sha256>(&self) -> Digest {
        match *self { /* unreachable  */ }
    }
}

impl BorshSerialize for Unknown {
    fn serialize<W>(&self, _: &mut W) -> core::result::Result<(), borsh::io::Error> {
        match *self { /* unreachable  */ }
    }
}

impl BorshDeserialize for Unknown {
    fn deserialize_reader<R>(_: &mut R) -> core::result::Result<Self, borsh::io::Error> {
        Err(borsh::io::Error::new(
            borsh::io::ErrorKind::InvalidData,
            "BorshDeserialize attempted to deserialize Unknown; data is malformed",
        ))
    }
}
