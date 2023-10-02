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

//! [ReceiptMetadata] and associated types and functions.
//!
//! A [ReceiptMetadata] struct contains the public claims about a zkVM guest
//! execution, such as the journal committed to by the guest. It also includes
//! important information such as the exit code and the starting and ending
//! system state (i.e. the state of memory).

use alloc::{collections::VecDeque, vec::Vec};
use core::{fmt, ops::Deref};

use anyhow::{anyhow, ensure};
use risc0_binfmt::{read_sha_halfs, tagged_list, tagged_struct, write_sha_halfs};
use serde::{Deserialize, Serialize};

use crate::{
    sha::{Digest, Digestable, Sha256, DIGEST_WORDS},
    SystemState,
};

/// A value that may either be the source value directly, or a hash digest of
/// the value.
#[derive(Clone, Debug, Deserialize, Serialize)]
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

    /// Unwrap the value as a reference, or return an error.k
    pub fn as_value(&self) -> Result<&T, PrunedValueError> {
        match self {
            MaybePruned::Value(ref value) => Ok(value),
            MaybePruned::Pruned(ref digest) => Err(PrunedValueError(digest.clone())),
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

impl<T> Digestable for MaybePruned<T>
where
    T: Digestable + Clone + Serialize,
{
    fn digest(&self) -> Digest {
        match self {
            MaybePruned::Value(ref val) => val.digest(),
            MaybePruned::Pruned(digest) => digest.clone(),
        }
    }
}

impl<T> MaybePruned<Option<T>>
where
    T: Clone + Serialize,
{
    /// Returns true is the value is None, or the value is pruned as the zero digest.
    pub fn is_none(&self) -> bool {
        match self {
            MaybePruned::Value(Some(_)) => false,
            MaybePruned::Value(None) => true,
            MaybePruned::Pruned(digest) => digest == &Digest::new([0u32; DIGEST_WORDS]),
        }
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

/// Error returned when the source value was pruned, and is not available.
#[derive(Debug, Clone)]
pub struct PrunedValueError(Digest);

impl fmt::Display for PrunedValueError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "value is pruned: {}", &self.0)
    }
}

#[cfg(feature = "std")]
impl std::error::Error for PrunedValueError {}

/// Data associated with a receipt which is used for both input and
/// output of global state.
#[derive(Clone, Debug, Serialize, Deserialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct ReceiptMetadata {
    /// The [SystemState] of a segment just before execution has begun.
    pub pre: MaybePruned<SystemState>,

    /// The [SystemState] of a segment just after execution has completed.
    pub post: MaybePruned<SystemState>,

    /// The exit code for a segment
    pub exit_code: ExitCode,

    /// A [Digest] of the input, from the viewpoint of the guest.
    pub input: Digest,

    /// A [Output] of the guest, including the journal and assumptions set
    /// during execution.
    pub output: MaybePruned<Option<Output>>,
}

impl ReceiptMetadata {
    /// Decode a [crate::ReceiptMetadata] from a list of [u32]'s
    pub fn decode(flat: &mut VecDeque<u32>) -> Result<Self, InvalidExitCodeError> {
        let input = read_sha_halfs(flat);
        let pre = SystemState::decode(flat);
        let post = SystemState::decode(flat);
        let sys_exit = flat.pop_front().unwrap();
        let user_exit = flat.pop_front().unwrap();
        let exit_code = ExitCode::from_pair(sys_exit, user_exit)?;
        let output = read_sha_halfs(flat);

        Ok(Self {
            input,
            pre: pre.into(),
            post: post.into(),
            exit_code,
            output: MaybePruned::Pruned(output),
        })
    }

    /// Encode a [crate::ReceiptMetadata] to a list of [u32]'s
    pub fn encode(&self, flat: &mut Vec<u32>) -> Result<(), PrunedValueError> {
        write_sha_halfs(flat, &self.input);
        self.pre.as_value()?.encode(flat);
        self.post.as_value()?.encode(flat);
        let (sys_exit, user_exit) = self.exit_code.into_pair();
        flat.push(sys_exit);
        flat.push(user_exit);
        write_sha_halfs(flat, &self.output.digest());
        Ok(())
    }
}

impl risc0_binfmt::Digestable for ReceiptMetadata {
    /// Hash the [crate::ReceiptMetadata] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        let (sys_exit, user_exit) = self.exit_code.into_pair();
        tagged_struct::<S>(
            "risc0.ReceiptMeta",
            &[
                self.input,
                self.pre.digest(),
                self.post.digest(),
                self.output.digest(),
            ],
            &[sys_exit, user_exit],
        )
    }
}

/// Indicates how a Segment or Session's execution has terminated
#[derive(Clone, Copy, Debug, Serialize, Deserialize, PartialEq)]
pub enum ExitCode {
    /// This indicates when a system-initiated split has occured due to the
    /// segment limit being exceeded.
    SystemSplit,

    /// This indicates that the session limit has been reached.
    SessionLimit,

    /// A user may manually pause a session so that it can be resumed at a later
    /// time, along with the user returned code.
    Paused(u32),

    /// This indicates normal termination of a program with an interior exit
    /// code returned from the guest.
    Halted(u32),

    /// This indicates termination of a program where the next instruction will
    /// fail.
    Fault,
}

impl ExitCode {
    pub(crate) fn into_pair(self) -> (u32, u32) {
        match self {
            ExitCode::Halted(user_exit) => (0, user_exit),
            ExitCode::Paused(user_exit) => (1, user_exit),
            ExitCode::SystemSplit => (2, 0),
            // DO NOT MERGE(victor): Confirm SessionLimit and Fault can have an associated exit
            // code.
            ExitCode::SessionLimit => (3, 0),
            ExitCode::Fault => (4, 0),
        }
    }

    pub(crate) fn from_pair(
        sys_exit: u32,
        user_exit: u32,
    ) -> Result<ExitCode, InvalidExitCodeError> {
        match sys_exit {
            0 => Ok(ExitCode::Halted(user_exit)),
            1 => Ok(ExitCode::Paused(user_exit)),
            2 => Ok(ExitCode::SystemSplit),
            3 => Ok(ExitCode::SessionLimit),
            4 => Ok(ExitCode::Fault),
            _ => Err(InvalidExitCodeError(sys_exit, user_exit)),
        }
    }

    pub(crate) fn expects_output(&self) -> bool {
        match self {
            ExitCode::Halted(_) | ExitCode::Paused(_) => true,
            ExitCode::SystemSplit | ExitCode::SessionLimit | ExitCode::Fault => false,
        }
    }
}

/// Error returned when a (system, user) exit code pair is an invalid
/// representation.
#[derive(Debug, Copy, Clone)]
pub struct InvalidExitCodeError(u32, u32);

impl fmt::Display for InvalidExitCodeError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "invalid exit code pair ({}, {})", self.0, self.1)
    }
}

#[cfg(feature = "std")]
impl std::error::Error for InvalidExitCodeError {}

/// Output field in the [crate::ReceiptMetadata], committing to a claimed
/// journal and assumptions list.
#[derive(Clone, Debug, Serialize, Deserialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct Output {
    // TODO(victor): Reconsider whether this Journal type should exist.
    /// A SHA-256 digest of the journal committed to by the guest execution.
    pub journal: MaybePruned<Vec<u8>>,

    /// An ordered list of [crate::ReceiptMetadata] digests corresponding to the
    /// calls to `env::verify`.
    ///
    /// Verifying a [crate::Receipt] corresponding to a [crate::ReceiptMetadata]
    /// with a non-empty assumptions list does not guarantee unconditionally
    /// any of the claims over the guest execution (i.e. if the assumptions
    /// list is non-empty, then the journal digest cannot be trusted to
    /// correspond to a genuine execution). The claims can be checked by
    /// additional verifying a [crate::Receipt] for every digest in the
    /// assumptions list.
    pub assumptions: MaybePruned<Assumptions>,
}

impl risc0_binfmt::Digestable for Output {
    /// Hash the [Output] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        tagged_struct::<S>(
            "risc0.Output",
            &[self.journal.digest(), self.assumptions.digest()],
            &[],
        )
    }
}

/// A list of assumptions, each a [Digest] of a [ReceiptMetadata].
#[derive(Clone, Debug, Serialize, Deserialize)]
#[cfg_attr(test, derive(PartialEq))]
pub struct Assumptions(pub Vec<MaybePruned<ReceiptMetadata>>);

impl Assumptions {
    /// Mark an assumption as resolved and return the assumption list with it
    /// removed.
    ///
    /// Assumptions can only be removed from the head of the list.
    #[allow(unused)] // DO NOT MERGE
    pub(crate) fn resolve(mut self, resolved: Digest) -> anyhow::Result<Self> {
        let head = self
            .0
            .first()
            .ok_or_else(|| anyhow!("cannot resolve assumption from empty list"))?;

        ensure!(
            head.digest() == resolved,
            "resolved assumption is not equal to the head of the list: {} != {}",
            resolved,
            head.digest()
        );

        // Drop the head of the assumptions list.
        self.0 = self.0.split_off(1);
        Ok(self)
    }
}

impl Deref for Assumptions {
    type Target = [MaybePruned<ReceiptMetadata>];

    fn deref(&self) -> &Self::Target {
        &self.0
    }
}

impl risc0_binfmt::Digestable for Assumptions {
    /// Hash the [Output] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        tagged_list::<S>(
            "risc0.Assumptions",
            &self.0.iter().map(|a| a.digest()).collect::<Vec<_>>(),
        )
    }
}

impl fmt::Display for InvalidAssumptionDigestError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(
            f,
            "resolved assumption is not the head of the assumption list: {:?}",
            &self
        )
    }
}

impl MaybePruned<Assumptions> {
    /// Check if the (possibly pruned) assumptions list is empty.
    pub fn is_empty(&self) -> bool {
        match self {
            MaybePruned::Value(list) => list.is_empty(),
            MaybePruned::Pruned(digest) => digest == &Digest::new([0u32; DIGEST_WORDS]),
        }
    }
}

/// Error for when the resolved assumption is not the head of the list.
#[derive(Debug, Clone)]
pub struct InvalidAssumptionDigestError {
    /// Digest of the [ReceiptMetadata] for the assumption marked as resolved.
    pub resolved: Digest,
}

#[cfg(feature = "std")]
impl std::error::Error for InvalidAssumptionDigestError {}

// TODO(victor): Add tests that show every combination of pruned struct returns
// the same digest. Check that the digest of an empty assumptions list is all
// zeroes.
