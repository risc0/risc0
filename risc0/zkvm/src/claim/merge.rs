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

//! The [Merge] trait supporting merging of claims and Merklized structures.

use alloc::vec::Vec;
use core::fmt;

use derive_more::Debug;
use risc0_binfmt::Digestible;
use risc0_zkp::core::digest::Digest;
use serde::Serialize;

use crate::{
    claim::{
        maybe_pruned::MaybePruned,
        receipt::{Assumption, Assumptions, Input, Output, ReceiptClaim},
    },
    sha, SystemState, Work, WorkClaim,
};

/// Merge two structures containing [MaybePruned] fields to produce a resulting structure with
/// populated fields equal to the union of the two.
///
/// Viewing the two structs as Merkle trees, in which subtrees may be pruned, the result of this
/// operation is a tree with a set of nodes equal to the union of the set of nodes for each input.
pub(crate) trait Merge: Digestible + Sized {
    /// Merge two structs to produce an output with a union of the fields populated in the inputs.
    fn merge(&self, other: &Self) -> Result<Self, MergeInequalityError>;

    /// Merge two structs to assigning self as the union of the fields populated in the two inputs.
    fn merge_with(&mut self, other: &Self) -> Result<&mut Self, MergeInequalityError> {
        // Not a very efficient implementation.
        *self = self.merge(other)?;
        Ok(self)
    }
}

/// Error returned when a merge it attempted with two values with unequal digests.
#[derive(Debug, Clone)]
pub(crate) struct MergeInequalityError(pub Digest, pub Digest);

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

#[cfg(feature = "std")]
impl std::error::Error for MergeInequalityError {}

/// Private marker trait providing an implementation of merge to values which implement PartialEq and clone and do not contain Merge fields.
trait MergeLeaf: Digestible + PartialEq + Clone + Sized {}

impl MergeLeaf for SystemState {}
impl MergeLeaf for Assumption {}
impl MergeLeaf for Work {}
impl MergeLeaf for Vec<u8> {}

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

impl Merge for Input {
    fn merge(&self, _other: &Self) -> Result<Self, MergeInequalityError> {
        match self.x { /* unreachable  */ }
    }
}

impl Merge for Output {
    fn merge(&self, other: &Self) -> Result<Self, MergeInequalityError> {
        Ok(Self {
            journal: self.journal.merge(&other.journal)?,
            assumptions: self.assumptions.merge(&other.assumptions)?,
        })
    }
}

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

impl<Claim: Merge + Clone + Serialize> Merge for WorkClaim<Claim> {
    fn merge(&self, other: &Self) -> Result<Self, MergeInequalityError> {
        Ok(Self {
            claim: self.claim.merge(&other.claim)?,
            work: self.work.merge(&other.work)?,
        })
    }
}

#[cfg(test)]
mod tests {
    use hex::FromHex;

    use super::{Assumptions, MaybePruned, Merge, Output, ReceiptClaim, SystemState};
    use crate::sha::{Digest, Digestible};
    use crate::ExitCode;

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
