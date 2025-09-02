// Copyright 2025 RISC Zero, Inc.
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

//! The [MaybePruned] type and related traits, supporting Merkle-ized structs.

use core::fmt;

use borsh::{BorshDeserialize, BorshSerialize};
use derive_more::Debug;
use risc0_binfmt::Digestible;
use risc0_zkp::core::digest::Digest;
use serde::{Deserialize, Serialize};

use crate::sha::{self, Sha256};

/// Either a source value or a hash [Digest] of the source value.
///
/// This type supports creating "Merkle-ized structs". Each field of a Merkle-ized struct can have
/// either the full value, or it can be "pruned" and replaced with a digest committing to that
/// value. One way to think of this is as a special Merkle tree of a predefined shape. Each field
/// is a child node. Any field/node in the tree can be opened by providing the Merkle inclusion
/// proof. When a subtree is pruned, the digest commits to the value of all contained fields.
/// [ReceiptClaim][crate::ReceiptClaim] is the motivating example of this type of Merkle-ized struct.
#[derive(Clone, Deserialize, Serialize, BorshSerialize, BorshDeserialize)]
pub enum MaybePruned<T> {
    /// Unpruned value.
    Value(T),

    /// Pruned value, which is a hash [Digest] of the value.
    Pruned(Digest),
}

impl<T> MaybePruned<T> {
    /// Unwrap the value, or return an error.
    pub fn value(self) -> Result<T, PrunedValueError> {
        match self {
            MaybePruned::Value(value) => Ok(value),
            MaybePruned::Pruned(digest) => Err(PrunedValueError(digest)),
        }
    }

    /// Unwrap the value as a reference, or return an error.
    pub fn as_value(&self) -> Result<&T, PrunedValueError> {
        match self {
            MaybePruned::Value(value) => Ok(value),
            MaybePruned::Pruned(digest) => Err(PrunedValueError(*digest)),
        }
    }

    /// Unwrap the value as a mutable reference, or return an error.
    pub fn as_value_mut(&mut self) -> Result<&mut T, PrunedValueError> {
        match self {
            MaybePruned::Value(value) => Ok(value),
            MaybePruned::Pruned(digest) => Err(PrunedValueError(*digest)),
        }
    }
}

impl<T> From<T> for MaybePruned<T> {
    fn from(value: T) -> Self {
        Self::Value(value)
    }
}

impl<T> Digestible for MaybePruned<T>
where
    T: Digestible,
{
    fn digest<S: Sha256>(&self) -> Digest {
        match self {
            MaybePruned::Value(val) => val.digest::<S>(),
            MaybePruned::Pruned(digest) => *digest,
        }
    }
}

impl<T> Default for MaybePruned<T>
where
    T: Digestible + Default,
{
    fn default() -> Self {
        MaybePruned::Value(Default::default())
    }
}

impl<T> MaybePruned<Option<T>> {
    /// Returns true if the value is None, or the value is pruned as the zero
    /// digest.
    pub fn is_none(&self) -> bool {
        match self {
            MaybePruned::Value(Some(_)) => false,
            MaybePruned::Value(None) => true,
            MaybePruned::Pruned(digest) => digest == &Digest::ZERO,
        }
    }

    /// Returns true if the value is Some(_), or the value is pruned as a
    /// non-zero digest.
    pub fn is_some(&self) -> bool {
        !self.is_none()
    }
}

#[cfg(test)]
impl<T> PartialEq for MaybePruned<T>
where
    T: PartialEq,
{
    fn eq(&self, other: &Self) -> bool {
        match (self, other) {
            (Self::Value(a), Self::Value(b)) => a == b,
            (Self::Pruned(a), Self::Pruned(b)) => a == b,
            _ => false,
        }
    }
}

impl<T> fmt::Debug for MaybePruned<T>
where
    T: Digestible + fmt::Debug,
{
    /// Format [MaybePruned] values are if they were a struct with value and
    /// digest fields. Digest field is always provided so that divergent
    /// trees of [MaybePruned] values can be compared.
    fn fmt(&self, fmt: &mut fmt::Formatter<'_>) -> fmt::Result {
        let mut builder = fmt.debug_struct("MaybePruned");
        if let MaybePruned::Value(value) = self {
            builder.field("value", value);
        }
        builder
            .field("digest", &self.digest::<sha::Impl>())
            .finish()
    }
}

/// Error returned when the source value was pruned, and is not available.
#[derive(Debug, Clone)]
pub struct PrunedValueError(pub Digest);

impl fmt::Display for PrunedValueError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "value is pruned: {}", &self.0)
    }
}

#[cfg(feature = "std")]
impl std::error::Error for PrunedValueError {}
