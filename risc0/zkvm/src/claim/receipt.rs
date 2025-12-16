// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

//! [ReceiptClaim] and associated types and functions.
//!
//! A [ReceiptClaim] struct contains the public claims (i.e. public outputs) of a zkVM guest
//! execution, such as the journal committed to by the guest. It also includes important
//! information such as the exit code and the starting and ending system state (i.e. the state of
//! memory).

use alloc::{collections::VecDeque, vec::Vec};
use core::{fmt, ops::Deref};

#[cfg(feature = "std")]
use anyhow::Context;
use anyhow::{anyhow, ensure};
use borsh::{BorshDeserialize, BorshSerialize};
use derive_more::Debug;
use risc0_binfmt::{
    Digestible, ExitCode, InvalidExitCodeError, read_sha_halfs, tagged_list, tagged_list_cons,
    tagged_struct, write_sha_halfs,
};
use risc0_zkp::core::digest::Digest;
use serde::{Deserialize, Serialize};

use super::{
    Unknown,
    maybe_pruned::{MaybePruned, PrunedValueError},
    work::WorkClaimError,
};
use crate::{
    SystemState, WorkClaim,
    sha::{self, Sha256},
};

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
    /// Construct a [ReceiptClaim] representing a zkVM execution that ended normally (i.e.
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

    /// Construct a [ReceiptClaim] representing a zkVM execution that ended in a normal paused
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

    pub(crate) fn decode_from_seal_m3(seal: &[u32]) -> anyhow::Result<ReceiptClaim> {
        let claim = risc0_circuit_rv32im_m3::Claim::decode(seal)?;
        tracing::debug!("claim: {claim:#?}");

        let exit_code = claim.exit_code()?;
        let post_state = match exit_code {
            ExitCode::Halted(_) => Digest::ZERO,
            _ => claim.post_state,
        };

        let output = claim.output.map(MaybePruned::Pruned).unwrap_or_default();

        Ok(ReceiptClaim {
            pre: MaybePruned::Value(SystemState {
                pc: 0,
                merkle_root: claim.pre_state,
            }),
            post: MaybePruned::Value(SystemState {
                pc: 0,
                merkle_root: post_state,
            }),
            exit_code,
            input: MaybePruned::Pruned(Digest::ZERO),
            output,
        })
    }

    #[cfg(feature = "prove")]
    pub(crate) fn decode_m3_with_output(
        seal: &[u32],
        output: MaybePruned<Option<Output>>,
    ) -> anyhow::Result<ReceiptClaim> {
        use crate::claim::merge::Merge;

        let mut claim = Self::decode_from_seal_m3(seal)?;
        claim
            .output
            .merge_with(&output)
            .context("Provided output does not match decoded output")?;
        Ok(claim)
    }

    /// Produce the claim for joining two claims of execution in a continuation, asserting the
    /// reachability of the post state of other from the pre state of self.
    pub fn join(&self, other: &Self) -> Self {
        ReceiptClaim {
            pre: self.pre.clone(),
            post: other.post.clone(),
            exit_code: other.exit_code,
            input: self.input.clone(),
            output: other.output.clone(),
        }
    }

    /// Produce the claim for resolving an assumption from the conditional claim (self). The
    /// conditional claim must have a full (unpruned) assumptions list and the given claim must be
    /// the head of the list.
    #[cfg(feature = "std")]
    pub fn resolve<Claim: risc0_binfmt::Digestible + ?Sized>(
        &self,
        assumption: &Claim,
    ) -> anyhow::Result<Self> {
        let mut resolved_claim = self.clone();

        // Open the assumptions on the output of the claim.
        let assumptions: &mut Assumptions = resolved_claim
            .output
            .as_value_mut()
            .context("conditional receipt output is pruned")?
            .as_mut()
            .ok_or_else(|| anyhow!("conditional receipt has empty output and no assumptions"))?
            .assumptions
            .as_value_mut()
            .context("conditional receipt has pruned assumptions")?;

        // Use the control root from the head of the assumptions list to form an Assumption from
        // the given claim. This is a simplifying assumption but cannot guarantee that the claim
        // actually resolves the assumption if it was produced with an incompatible control root.
        let head_control_root = assumptions
            .first()
            .context("assumptions list is empty")?
            .as_value()?
            .control_root;

        // Remove the head assumption.
        assumptions.resolve(
            &Assumption {
                control_root: head_control_root,
                claim: assumption.digest::<sha::Impl>(),
            }
            .digest::<sha::Impl>(),
        )?;

        Ok(resolved_claim)
    }
}

impl MaybePruned<ReceiptClaim> {
    /// Produce the claim for joining two claims of execution in a continuation, asserting the
    /// reachability of the post state of other from the pre state of self.
    pub fn join(&self, other: &Self) -> Result<Self, PrunedValueError> {
        Ok(self.as_value()?.join(other.as_value()?).into())
    }

    /// Produce the claim for resolving an assumption from the conditional claim (self). The
    /// conditional claim must have a full (unpruned) assumptions list and the given claim must be
    /// the head of the list.
    #[cfg(feature = "std")]
    pub fn resolve<Claim: risc0_binfmt::Digestible + ?Sized>(
        &self,
        assumption: &Claim,
    ) -> anyhow::Result<Self> {
        Ok(self
            .as_value()
            .context("conditional claim is pruned")?
            .resolve(assumption)?
            .into())
    }
}

impl WorkClaim<ReceiptClaim> {
    /// Joins two work claims by combining their receipt claims and work values while ensuring
    /// the consumed nonce ranges are disjoint.
    pub fn join(&self, other: &Self) -> Result<Self, WorkClaimError> {
        Ok(Self {
            claim: self.claim.join(&other.claim)?,
            work: self.work.join(&other.work)?,
        })
    }

    /// Resolves assumptions in the receipt claim while preserving the work value.
    #[cfg(feature = "std")]
    pub fn resolve<Claim: risc0_binfmt::Digestible + ?Sized>(
        &self,
        assumption: &Claim,
    ) -> anyhow::Result<Self> {
        Ok(Self {
            claim: self.claim.resolve(assumption)?,
            work: self.work.clone(),
        })
    }
}

impl MaybePruned<WorkClaim<ReceiptClaim>> {
    /// Joins two possibly pruned work claims by combining their receipt claims and work values
    /// while ensuring the consumed nonce ranges are disjoint.
    pub fn join(&self, other: &Self) -> Result<Self, WorkClaimError> {
        Ok(self.as_value()?.join(other.as_value()?)?.into())
    }

    /// Resolves assumptions in a possibly pruned work claim while preserving the work value.
    #[cfg(feature = "std")]
    pub fn resolve<Claim: risc0_binfmt::Digestible + ?Sized>(
        &self,
        assumption: &Claim,
    ) -> anyhow::Result<Self> {
        Ok(self
            .as_value()
            .context("conditional povw claim is pruned")?
            .resolve(assumption)?
            .into())
    }
}

#[cfg(feature = "prove")]
pub(crate) fn exit_code_from_terminate_state(
    terminate_state: &Option<risc0_circuit_rv32im::TerminateState>,
) -> anyhow::Result<ExitCode> {
    use anyhow::bail;
    use risc0_circuit_rv32im::HighLowU16;
    use risc0_zkvm_platform::syscall::halt;

    let exit_code = if let Some(term) = terminate_state {
        let HighLowU16(user_exit, halt_type) = term.a0;
        match halt_type as u32 {
            halt::TERMINATE => ExitCode::Halted(user_exit as u32),
            halt::PAUSE => ExitCode::Paused(user_exit as u32),
            _ => bail!("Illegal halt type: {halt_type}"),
        }
    } else {
        ExitCode::SystemSplit
    };
    Ok(exit_code)
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

/// Each UnionClaim can be used as an inner node in a Merkle mountain
/// accumulator, the root of which commits to a set of claims.
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct UnionClaim {
    /// Digest of the "left" Assumption struct.
    ///
    /// The left should always be lesser of the two when interpreting the digest as a big-endian number.
    pub left: Digest,
    /// Digest of the "right" Assumption struct.
    pub right: Digest,
}

impl Digestible for UnionClaim {
    fn digest<S: Sha256>(&self) -> Digest {
        tagged_struct::<S>("risc0.UnionClaim", &[self.left, self.right], &[])
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
    #[debug("{}", fmt_debug_journal(journal))]
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

#[allow(dead_code)]
fn fmt_debug_journal(journal: &MaybePruned<Vec<u8>>) -> alloc::string::String {
    match journal {
        MaybePruned::Value(bytes) => alloc::format!("{} bytes", bytes.len()),
        MaybePruned::Pruned(_) => alloc::format!("{journal:?}"),
    }
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
#[derive(
    Clone, Debug, Serialize, Deserialize, Eq, Hash, PartialEq, BorshSerialize, BorshDeserialize,
)]
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
