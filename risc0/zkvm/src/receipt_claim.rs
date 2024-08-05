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

//! [ReceiptClaim] and associated types and functions.
//!
//! A [ReceiptClaim] struct contains the public claims (i.e. public outputs) of a zkVM guest
//! execution, such as the journal committed to by the guest. It also includes important
//! information such as the exit code and the starting and ending system state (i.e. the state of
//! memory).

use alloc::{collections::VecDeque, vec::Vec};
use core::{fmt, ops::Deref};

use anyhow::{anyhow, ensure};
use borsh::{BorshDeserialize, BorshSerialize};
use risc0_binfmt::{
    read_sha_halfs, tagged_list, tagged_list_cons, tagged_struct, write_sha_halfs, Digestible,
    ExitCode, InvalidExitCodeError,
};
use risc0_zkp::core::digest::Digest;
use serde::{Deserialize, Serialize};

use crate::{
    sha::{self, Sha256},
    SystemState,
};

// TODO(victor): Add functions to handle the `ReceiptClaim` transformations conducted as part of
// join, resolve, and eventually resume calls. This will allow these to be used for recursion, as
// well as dev mode recursion, and composite receipts.

/// Public claims about a zkVM guest execution, such as the journal committed to by the guest.
///
/// Also includes important information such as the exit code and the starting and ending system
/// state (i.e. the state of memory). [ReceiptClaim] is a "Merkle-ized struct" supporting
/// partial openings of the underlying fields from a hash commitment to the full structure. Also
/// see [MaybePruned].
#[derive(Clone, Debug, Serialize, Deserialize, BorshSerialize, BorshDeserialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct ReceiptClaim {
    /// The [SystemState] just before execution has begun.
    pub pre: MaybePruned<SystemState>,

    /// The [SystemState] just after execution has completed.
    pub post: MaybePruned<SystemState>,

    /// The exit code for the execution.
    pub exit_code: ExitCode,

    /// Input to the guest.
    pub input: MaybePruned<Option<Input>>,

    /// [Output] of the guest, including the journal and assumptions set during execution.
    pub output: MaybePruned<Option<Output>>,
}

impl ReceiptClaim {
    /// Construct a [ReceiptClaim] representing a zkVM execution that eneded normally (i.e.
    /// Halted(0)) with the given image ID and journal.
    pub fn ok(
        image_id: impl Into<Digest>,
        journal: impl Into<MaybePruned<Vec<u8>>>,
    ) -> ReceiptClaim {
        Self {
            pre: MaybePruned::Pruned(image_id.into()),
            post: MaybePruned::Value(SystemState {
                pc: 0,
                merkle_root: Digest::ZERO,
            }),
            exit_code: ExitCode::Halted(0),
            input: None.into(),
            output: Some(Output {
                journal: journal.into(),
                assumptions: MaybePruned::Pruned(Digest::ZERO),
            })
            .into(),
        }
    }

    /// Construct a [ReceiptClaim] representing a zkVM execution that eneded in a normal paused
    /// state (i.e. Paused(0)) with the given image ID and journal.
    pub fn paused(
        image_id: impl Into<Digest>,
        journal: impl Into<MaybePruned<Vec<u8>>>,
    ) -> ReceiptClaim {
        Self {
            pre: MaybePruned::Pruned(image_id.into()),
            post: MaybePruned::Value(SystemState {
                pc: 0,
                merkle_root: Digest::ZERO,
            }),
            exit_code: ExitCode::Paused(0),
            input: None.into(),
            output: Some(Output {
                journal: journal.into(),
                assumptions: MaybePruned::Pruned(Digest::ZERO),
            })
            .into(),
        }
    }

    /// Decode a [ReceiptClaim] from a list of [u32]'s
    pub fn decode(flat: &mut VecDeque<u32>) -> Result<Self, DecodeError> {
        let input = read_sha_halfs(flat)?;
        let pre = SystemState::decode(flat)?;
        let post = SystemState::decode(flat)?;
        let sys_exit = flat
            .pop_front()
            .ok_or(risc0_binfmt::DecodeError::EndOfStream)?;
        let user_exit = flat
            .pop_front()
            .ok_or(risc0_binfmt::DecodeError::EndOfStream)?;
        let exit_code = ExitCode::from_pair(sys_exit, user_exit)?;
        let output = read_sha_halfs(flat)?;

        Ok(Self {
            input: MaybePruned::Pruned(input),
            pre: pre.into(),
            post: post.into(),
            exit_code,
            output: MaybePruned::Pruned(output),
        })
    }

    /// Encode a [ReceiptClaim] to a list of [u32]'s
    pub fn encode(&self, flat: &mut Vec<u32>) -> Result<(), PrunedValueError> {
        write_sha_halfs(flat, &self.input.digest::<sha::Impl>());
        self.pre.as_value()?.encode(flat);
        self.post.as_value()?.encode(flat);
        let (sys_exit, user_exit) = self.exit_code.into_pair();
        flat.push(sys_exit);
        flat.push(user_exit);
        write_sha_halfs(flat, &self.output.digest::<sha::Impl>());
        Ok(())
    }
}

impl Digestible for ReceiptClaim {
    /// Hash the [ReceiptClaim] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        let (sys_exit, user_exit) = self.exit_code.into_pair();
        tagged_struct::<S>(
            "risc0.ReceiptClaim",
            &[
                self.input.digest::<S>(),
                self.pre.digest::<S>(),
                self.post.digest::<S>(),
                self.output.digest::<S>(),
            ],
            &[sys_exit, user_exit],
        )
    }
}

/// Error returned when decoding [ReceiptClaim] fails.
#[derive(Debug, Copy, Clone)]
pub enum DecodeError {
    /// Decoding failure due to an invalid exit code.
    InvalidExitCode(InvalidExitCodeError),
    /// Decoding failure due to an inner decoding failure.
    Decode(risc0_binfmt::DecodeError),
}

impl fmt::Display for DecodeError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Self::InvalidExitCode(e) => write!(f, "failed to decode receipt claim: {e}"),
            Self::Decode(e) => write!(f, "failed to decode receipt claim: {e}"),
        }
    }
}

impl From<risc0_binfmt::DecodeError> for DecodeError {
    fn from(e: risc0_binfmt::DecodeError) -> Self {
        Self::Decode(e)
    }
}

impl From<InvalidExitCodeError> for DecodeError {
    fn from(e: InvalidExitCodeError) -> Self {
        Self::InvalidExitCode(e)
    }
}

#[cfg(feature = "std")]
impl std::error::Error for DecodeError {}

/// A type representing an unknown claim type.
///
/// A receipt (e.g. [SuccinctReceipt][crate::SuccinctReceipt]) may have an unknown claim type when
/// only the digest of the claim is needed, and the full claim value cannot be determined by the
/// compiler. This allows for a collection of receipts to be created even when the underlying
/// claims are of heterogeneous types (e.g. Vec<SuccinctReceipt<Unknown>>).
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
        unreachable!("unreachable")
    }
}

impl BorshDeserialize for Unknown {
    fn deserialize_reader<R>(_: &mut R) -> core::result::Result<Self, borsh::io::Error> {
        unreachable!("unreachable")
    }
}

/// Input field in the [ReceiptClaim], committing to a public value accessible to the guest.
///
/// NOTE: This type is currently uninhabited (i.e. it cannot be constructed), and only its digest
/// is accessible. It may become inhabited in a future release.
#[derive(Clone, Debug, Serialize, Deserialize, BorshSerialize, BorshDeserialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct Input {
    // Private field to ensure this type cannot be constructed.
    // By making this type uninhabited, it can be populated later without breaking backwards
    // compatibility.
    pub(crate) x: Unknown,
}

impl Digestible for Input {
    /// Hash the [Input] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        match self.x { /* unreachable  */ }
    }
}

/// Output field in the [ReceiptClaim], committing to a claimed journal and assumptions list.
#[derive(Clone, Debug, Serialize, Deserialize, BorshSerialize, BorshDeserialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct Output {
    /// The journal committed to by the guest execution.
    pub journal: MaybePruned<Vec<u8>>,

    /// An ordered list of [ReceiptClaim] digests corresponding to the
    /// calls to `env::verify` and `env::verify_integrity`.
    ///
    /// Verifying the integrity of a [crate::Receipt] corresponding to a [ReceiptClaim] with a
    /// non-empty assumptions list does not guarantee unconditionally any of the claims over the
    /// guest execution (i.e. if the assumptions list is non-empty, then the journal digest cannot
    /// be trusted to correspond to a genuine execution). The claims can be checked by additional
    /// verifying a [crate::Receipt] for every digest in the assumptions list.
    pub assumptions: MaybePruned<Assumptions>,
}

impl Digestible for Output {
    /// Hash the [Output] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        tagged_struct::<S>(
            "risc0.Output",
            &[self.journal.digest::<S>(), self.assumptions.digest::<S>()],
            &[],
        )
    }
}

/// An [assumption] made in the course of proving program execution.
///
/// Assumptions are generated when the guest makes a recursive verification call. Each assumption
/// commits the statement, such that only a receipt proving that statement can be used to resolve
/// and remove the assumption.
///
/// [assumption]: https://dev.risczero.com/terminology#assumption
#[derive(Clone, Debug, Serialize, Deserialize, PartialEq, BorshSerialize, BorshDeserialize)]
pub struct Assumption {
    /// Commitment to the assumption claim. It may be the digest of a [ReceiptClaim], or it could
    /// be the digest of the claim for a different circuit such as an accelerator.
    pub claim: Digest,

    /// Commitment to the set of [recursion programs] that can be used to resolve this assumption.
    ///
    /// Binding the set of recursion programs also binds the circuits, and creates an assumption
    /// resolved by independent set of circuits (e.g. keccak or Groth16 verify). Proofs of these
    /// external claims are verified by a "lift" program implemented for the recursion VM which
    /// brings the claim into the recursion system. This lift program is committed to in the
    /// control root.
    ///
    /// A special value of all zeroes indicates "self-composition", where the control root used to
    /// verify this claim is also used to verify the assumption.
    ///
    /// [recursion programs]: https://dev.risczero.com/terminology#recursion-program
    pub control_root: Digest,
}

impl Digestible for Assumption {
    /// Hash the [Assumption] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        tagged_struct::<S>("risc0.Assumption", &[self.claim, self.control_root], &[])
    }
}

/// A list of assumptions, each a [Digest] or populated value of an [Assumption].
#[derive(Clone, Default, Debug, Serialize, Deserialize, BorshSerialize, BorshDeserialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct Assumptions(pub Vec<MaybePruned<Assumption>>);

impl Assumptions {
    /// Add an assumption to the head of the assumptions list.
    pub fn add(&mut self, assumption: MaybePruned<Assumption>) {
        self.0.insert(0, assumption);
    }

    /// Mark an assumption as resolved and remove it from the list.
    ///
    /// Assumptions can only be removed from the head of the list.
    pub fn resolve(&mut self, resolved: &Digest) -> anyhow::Result<()> {
        let head = self
            .0
            .first()
            .ok_or_else(|| anyhow!("cannot resolve assumption from empty list"))?;

        ensure!(
            &head.digest::<sha::Impl>() == resolved,
            "resolved assumption is not equal to the head of the list: {} != {}",
            resolved,
            head.digest::<sha::Impl>()
        );

        // Drop the head of the assumptions list.
        self.0 = self.0.split_off(1);
        Ok(())
    }
}

impl Deref for Assumptions {
    type Target = [MaybePruned<Assumption>];

    fn deref(&self) -> &Self::Target {
        &self.0
    }
}

impl Digestible for Assumptions {
    /// Hash the [Assumptions] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        tagged_list::<S>(
            "risc0.Assumptions",
            &self.0.iter().map(|a| a.digest::<S>()).collect::<Vec<_>>(),
        )
    }
}

impl MaybePruned<Assumptions> {
    /// Check if the (possibly pruned) assumptions list is empty.
    pub fn is_empty(&self) -> bool {
        match self {
            MaybePruned::Value(list) => list.is_empty(),
            MaybePruned::Pruned(digest) => digest == &Digest::ZERO,
        }
    }

    /// Add an assumption to the head of the assumptions list.
    ///
    /// If this value is pruned, then the result will also be a pruned value.
    pub fn add(&mut self, assumption: MaybePruned<Assumption>) {
        match self {
            MaybePruned::Value(list) => list.add(assumption),
            MaybePruned::Pruned(list_digest) => {
                *list_digest = tagged_list_cons::<sha::Impl>(
                    "risc0.Assumptions",
                    &assumption.digest::<sha::Impl>(),
                    &*list_digest,
                );
            }
        }
    }

    /// Mark an assumption as resolved and remove it from the list.
    ///
    /// Assumptions can only be removed from the head of the list. If this value
    /// is pruned, then the result will also be a pruned value. The `tail`
    /// parameter should be equal to the digest of the list after the
    /// resolved assumption is removed.
    pub fn resolve(&mut self, resolved: &Digest, tail: &Digest) -> anyhow::Result<()> {
        match self {
            MaybePruned::Value(list) => list.resolve(resolved),
            MaybePruned::Pruned(list_digest) => {
                let reconstructed =
                    tagged_list_cons::<sha::Impl>("risc0.Assumptions", resolved, tail);
                ensure!(
                    &reconstructed == list_digest,
                    "reconstructed list digest does not match; expected {}, reconstructed {}",
                    list_digest,
                    reconstructed
                );

                // Set the pruned digest value to be equal to the rest parameter.
                *list_digest = *tail;
                Ok(())
            }
        }
    }
}

impl From<Vec<MaybePruned<Assumption>>> for Assumptions {
    fn from(value: Vec<MaybePruned<Assumption>>) -> Self {
        Self(value)
    }
}

impl From<Vec<Assumption>> for Assumptions {
    fn from(value: Vec<Assumption>) -> Self {
        Self(value.into_iter().map(Into::into).collect())
    }
}

impl From<Vec<Assumption>> for MaybePruned<Assumptions> {
    fn from(value: Vec<Assumption>) -> Self {
        Self::Value(value.into())
    }
}

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
        // Not an very efficient implementation.
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

    use super::{Assumptions, ExitCode, MaybePruned, Merge, Output, ReceiptClaim, SystemState};
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
                (Self::Pruned(x), _) => Self::Pruned(x.clone()),
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
                (Self::Pruned(x), _) => Self::Pruned(x.clone()),
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
                (Self::Pruned(x), _) => Self::Pruned(x.clone()),
            }
        }
    }

    impl RandPrune for MaybePruned<Vec<u8>> {
        fn rand_prune(&self) -> Self {
            match (self, rand::random::<bool>()) {
                (Self::Value(x), true) => Self::Pruned(x.digest()),
                (Self::Value(x), false) => x.clone().into(),
                (Self::Pruned(x), _) => Self::Pruned(x.clone()),
            }
        }
    }

    impl RandPrune for MaybePruned<Assumptions> {
        fn rand_prune(&self) -> Self {
            match (self, rand::random::<bool>()) {
                (Self::Value(x), true) => Self::Pruned(x.digest()),
                (Self::Value(x), false) => x.clone().into(),
                (Self::Pruned(x), _) => Self::Pruned(x.clone()),
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
