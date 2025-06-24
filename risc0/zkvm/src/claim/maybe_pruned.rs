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

use alloc::vec::Vec;
use core::fmt;

use borsh::{BorshDeserialize, BorshSerialize};
use derive_more::Debug;
use risc0_binfmt::Digestible;
use risc0_zkp::core::digest::Digest;
use serde::{Deserialize, Serialize};

use crate::{
    claim::receipt::{Assumption, Assumptions, Input, Output, ReceiptClaim},
    sha::{self, Sha256},
    SystemState,
};

/// Either a source value or a hash [Digest] of the source value.
///
/// This type supports creating "Merkle-ized structs". Each field of a Merkle-ized struct can have
/// either the full value, or it can be "pruned" and replaced with a digest committing to that
/// value. One way to think of this is as a special Merkle tree of a predefined shape. Each field
/// is a child node. Any field/node in the tree can be opened by providing the Merkle inclusion
/// proof. When a subtree is pruned, the digest commits to the value of all contained fields.
/// [ReceiptClaim] is the motivating example of this type of Merkle-ized struct.
#[derive(Clone, Deserialize, Serialize, BorshSerialize, BorshDeserialize)]
pub enum MaybePruned<T>
where
    T: Clone + Serialize,
{
    /// Unpruned value.
    Value(T),

    /// Pruned value, which is a hash [Digest] of the value.
    Pruned(Digest),
}

impl<T> MaybePruned<T>
where
    T: Clone + Serialize,
{
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
            MaybePruned::Value(ref value) => Ok(value),
            MaybePruned::Pruned(ref digest) => Err(PrunedValueError(*digest)),
        }
    }

    /// Unwrap the value as a mutable reference, or return an error.
    pub fn as_value_mut(&mut self) -> Result<&mut T, PrunedValueError> {
        match self {
            MaybePruned::Value(ref mut value) => Ok(value),
            MaybePruned::Pruned(ref digest) => Err(PrunedValueError(*digest)),
        }
    }
}

impl<T> From<T> for MaybePruned<T>
where
    T: Clone + Serialize,
{
    fn from(value: T) -> Self {
        Self::Value(value)
    }
}

impl<T> Digestible for MaybePruned<T>
where
    T: Digestible + Clone + Serialize,
{
    fn digest<S: Sha256>(&self) -> Digest {
        match self {
            MaybePruned::Value(ref val) => val.digest::<S>(),
            MaybePruned::Pruned(digest) => *digest,
        }
    }
}

impl<T> Default for MaybePruned<T>
where
    T: Digestible + Default + Clone + Serialize,
{
    fn default() -> Self {
        MaybePruned::Value(Default::default())
    }
}

impl<T> MaybePruned<Option<T>>
where
    T: Clone + Serialize,
{
    /// Returns true is the value is None, or the value is pruned as the zero
    /// digest.
    pub fn is_none(&self) -> bool {
        match self {
            MaybePruned::Value(Some(_)) => false,
            MaybePruned::Value(None) => true,
            MaybePruned::Pruned(digest) => digest == &Digest::ZERO,
        }
    }

    /// Returns true is the value is Some(_), or the value is pruned as a
    /// non-zero digest.
    pub fn is_some(&self) -> bool {
        !self.is_none()
    }
}

#[cfg(test)]
impl<T> PartialEq for MaybePruned<T>
where
    T: Clone + Serialize + PartialEq,
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
    T: Clone + Serialize + Digestible + fmt::Debug,
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

/// Merge two structures containing [MaybePruned] fields to produce a resulting structure with
/// populated fields equal to the union of the two.
///
/// Viewing the two structs as Merkle trees, in which subtrees may be pruned, the result of this
/// operation is a tree with a set of nodes equal to the union of the set of nodes for each input.
#[cfg(feature = "prove")]
pub(crate) trait Merge: Digestible + Sized {
    /// Merge two structs to produce an output with a union of the fields populated in the inputs.
    fn merge(&self, other: &Self) -> Result<Self, MergeInequalityError>;

    /// Merge two structs to assigning self as the union of the fields populated in the two inputs.
    fn merge_with(&mut self, other: &Self) -> Result<(), MergeInequalityError> {
        // Not a very efficient implementation.
        *self = self.merge(other)?;
        Ok(())
    }
}

/// Error returned when a merge it attempted with two values with unequal digests.
#[cfg(feature = "prove")]
#[derive(Debug, Clone)]
pub(crate) struct MergeInequalityError(pub Digest, pub Digest);

#[cfg(feature = "prove")]
impl fmt::Display for MergeInequalityError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(
            f,
            "cannot merge values; left and right are not digest equal: left {}, right {}",
            hex::encode(self.0),
            hex::encode(self.1)
        )
    }
}

#[cfg(all(feature = "std", feature = "prove"))]
impl std::error::Error for MergeInequalityError {}

/// Private marker trait providing an implementation of merge to values which implement PartialEq and clone and do not contain Merge fields.
#[cfg(feature = "prove")]
trait MergeLeaf: Digestible + PartialEq + Clone + Sized {}

#[cfg(feature = "prove")]
impl MergeLeaf for SystemState {}
#[cfg(feature = "prove")]
impl MergeLeaf for Assumption {}
#[cfg(feature = "prove")]
impl MergeLeaf for Vec<u8> {}

#[cfg(feature = "prove")]
impl<T: MergeLeaf> Merge for T {
    fn merge(&self, other: &Self) -> Result<Self, MergeInequalityError> {
        if self != other {
            return Err(MergeInequalityError(
                self.digest::<sha::Impl>(),
                other.digest::<sha::Impl>(),
            ));
        }

        Ok(self.clone())
    }
}

#[cfg(feature = "prove")]
impl<T> Merge for MaybePruned<T>
where
    T: Merge + Serialize + Clone,
{
    fn merge(&self, other: &Self) -> Result<Self, MergeInequalityError> {
        let check_eq = || {
            if self.digest::<sha::Impl>() != other.digest::<sha::Impl>() {
                Err(MergeInequalityError(
                    self.digest::<sha::Impl>(),
                    other.digest::<sha::Impl>(),
                ))
            } else {
                Ok(())
            }
        };

        Ok(match (self, other) {
            (MaybePruned::Value(left), MaybePruned::Value(right)) => {
                MaybePruned::Value(left.merge(right)?)
            }
            (MaybePruned::Value(_), MaybePruned::Pruned(_)) => {
                check_eq()?;
                self.clone()
            }
            (MaybePruned::Pruned(_), MaybePruned::Value(_)) => {
                check_eq()?;
                other.clone()
            }
            (MaybePruned::Pruned(_), MaybePruned::Pruned(_)) => {
                check_eq()?;
                self.clone()
            }
        })
    }
}

#[cfg(feature = "prove")]
impl<T: Merge> Merge for Option<T> {
    fn merge(&self, other: &Self) -> Result<Self, MergeInequalityError> {
        match (self, other) {
            (Some(left), Some(right)) => Some(left.merge(right)).transpose(),
            (None, None) => Ok(None),
            _ => Err(MergeInequalityError(
                self.digest::<sha::Impl>(),
                other.digest::<sha::Impl>(),
            )),
        }
    }
}

#[cfg(feature = "prove")]
impl Merge for Assumptions {
    fn merge(&self, other: &Self) -> Result<Self, MergeInequalityError> {
        if self.0.len() != other.0.len() {
            return Err(MergeInequalityError(
                self.digest::<sha::Impl>(),
                other.digest::<sha::Impl>(),
            ));
        }
        Ok(Assumptions(
            self.0
                .iter()
                .zip(other.0.iter())
                .map(|(left, right)| left.merge(right))
                .collect::<Result<Vec<_>, _>>()?,
        ))
    }
}

#[cfg(feature = "prove")]
impl Merge for Input {
    fn merge(&self, _other: &Self) -> Result<Self, MergeInequalityError> {
        match self.x { /* unreachable  */ }
    }
}

#[cfg(feature = "prove")]
impl Merge for Output {
    fn merge(&self, other: &Self) -> Result<Self, MergeInequalityError> {
        Ok(Self {
            journal: self.journal.merge(&other.journal)?,
            assumptions: self.assumptions.merge(&other.assumptions)?,
        })
    }
}

#[cfg(feature = "prove")]
impl Merge for ReceiptClaim {
    fn merge(&self, other: &Self) -> Result<Self, MergeInequalityError> {
        if self.exit_code != other.exit_code {
            return Err(MergeInequalityError(
                self.digest::<sha::Impl>(),
                other.digest::<sha::Impl>(),
            ));
        }
        Ok(Self {
            pre: self.pre.merge(&other.pre)?,
            post: self.post.merge(&other.post)?,
            exit_code: self.exit_code,
            input: self.input.merge(&other.input)?,
            output: self.output.merge(&other.output)?,
        })
    }
}

#[cfg(feature = "prove")]
#[cfg(test)]
mod tests {
    use hex::FromHex;

    use super::{Assumptions, MaybePruned, Merge, Output, ReceiptClaim, SystemState};
    use crate::ExitCode;
    use crate::sha::{Digest, Digestible};

    /// Testing utility for randomly pruning structs.
    trait RandPrune {
        fn rand_prune(&self) -> Self;
    }

    impl RandPrune for MaybePruned<ReceiptClaim> {
        fn rand_prune(&self) -> Self {
            match (self, rand::random::<bool>()) {
                (Self::Value(x), true) => Self::Pruned(x.digest()),
                (Self::Value(x), false) => ReceiptClaim {
                    pre: x.pre.rand_prune(),
                    post: x.post.rand_prune(),
                    exit_code: x.exit_code,
                    input: x.input.clone(),
                    output: x.output.rand_prune(),
                }
                .into(),
                (Self::Pruned(x), _) => Self::Pruned(*x),
            }
        }
    }

    impl RandPrune for MaybePruned<SystemState> {
        fn rand_prune(&self) -> Self {
            match (self, rand::random::<bool>()) {
                (Self::Value(x), true) => Self::Pruned(x.digest()),
                (Self::Value(x), false) => SystemState {
                    pc: x.pc,
                    merkle_root: x.merkle_root,
                }
                .into(),
                (Self::Pruned(x), _) => Self::Pruned(*x),
            }
        }
    }

    impl RandPrune for MaybePruned<Option<Output>> {
        fn rand_prune(&self) -> Self {
            match (self, rand::random::<bool>()) {
                (Self::Value(x), true) => Self::Pruned(x.digest()),
                (Self::Value(x), false) => x
                    .as_ref()
                    .map(|o| Output {
                        journal: o.journal.rand_prune(),
                        assumptions: o.assumptions.rand_prune(),
                    })
                    .into(),
                (Self::Pruned(x), _) => Self::Pruned(*x),
            }
        }
    }

    impl RandPrune for MaybePruned<Vec<u8>> {
        fn rand_prune(&self) -> Self {
            match (self, rand::random::<bool>()) {
                (Self::Value(x), true) => Self::Pruned(x.digest()),
                (Self::Value(x), false) => x.clone().into(),
                (Self::Pruned(x), _) => Self::Pruned(*x),
            }
        }
    }

    impl RandPrune for MaybePruned<Assumptions> {
        fn rand_prune(&self) -> Self {
            match (self, rand::random::<bool>()) {
                (Self::Value(x), true) => Self::Pruned(x.digest()),
                (Self::Value(x), false) => x.clone().into(),
                (Self::Pruned(x), _) => Self::Pruned(*x),
            }
        }
    }

    #[test]
    fn merge_receipt_claim() {
        let claim = MaybePruned::Value(ReceiptClaim {
            pre: SystemState {
                pc: 2100484,
                merkle_root: Digest::from_hex(
                    "9095da07d84ccc170c5113e3dafdf0531700f0b3f0c627acc9f0329440d984fa",
                )
                .unwrap(),
            }
            .into(),
            post: SystemState {
                pc: 2297164,
                merkle_root: Digest::from_hex(
                    "223651656250c0cf2f1c3f8923ef3d2c8624a361830492ffec6450e1930fb07d",
                )
                .unwrap(),
            }
            .into(),
            exit_code: ExitCode::Halted(0),
            input: None.into(),
            output: MaybePruned::Value(Some(Output {
                journal: MaybePruned::Value(b"hello world".to_vec()),
                assumptions: MaybePruned::Value(Assumptions(vec![
                    MaybePruned::Pruned(Digest::ZERO),
                    MaybePruned::Pruned(Digest::ZERO),
                ])),
            })),
        });

        // Run the test to 10k times to reach every combination with high probability.
        for _ in 0..10000 {
            let left = claim.rand_prune();
            let right = claim.rand_prune();

            assert_eq!(left.merge(&right).unwrap().digest(), claim.digest());
        }
    }
}
