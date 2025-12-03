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

use borsh::{BorshDeserialize, BorshSerialize};
use derive_builder::Builder;
use risc0_binfmt::PovwLogId;
use risc0_zkvm::{Digest, Unknown, WorkClaim};
use ruint::aliases::U160;
use serde::{Deserialize, Serialize};

use crate::{Job, SubtreeOpening, WorkLog, error::Error};

/// Guest program for the Log Builder.
#[cfg(feature = "prover")]
pub const RISC0_POVW_LOG_BUILDER_ELF: &[u8] = include_bytes!("../elfs/risc0-povw-log-builder.bin");

/// Guest program identifier, known as the image ID, for the Log Builder guest.
pub const RISC0_POVW_LOG_BUILDER_ID: [u8; 32] =
    *include_bytes!("../elfs/risc0-povw-log-builder.iid");

/// State of the PoVW guest program execution.
///
/// Represents either the initial state with a work log ID or a continuation
/// state with a journal from previous execution.
#[derive(Clone, Debug, Serialize, Deserialize, BorshSerialize, BorshDeserialize)]
pub enum State {
    /// Initial execution state with the work log ID to process.
    Initial {
        /// ID of the work log being processed.
        work_log_id: U160,
    },
    /// Continuation state with journal from previous execution.
    Continuation {
        /// Journal containing the accumulated state from previous execution.
        journal: Journal,
    },
}

impl State {
    /// Creates an initial state with the given work log ID.
    pub const fn initial(work_log_id: U160) -> Self {
        Self::Initial { work_log_id }
    }
}

impl From<Journal> for State {
    fn from(journal: Journal) -> Self {
        Self::Continuation { journal }
    }
}

/// Input to the PoVW guest program.
///
/// Contains the execution state, work log updates to apply, and the self image ID
/// for recursive verification.
#[derive(Clone, Builder, Debug, Serialize, Deserialize, BorshSerialize, BorshDeserialize)]
#[non_exhaustive]
pub struct Input {
    /// Execution state for the Log Builder guest.
    ///
    /// Use `State::Initial { work_log_id }` to start from an empty work log
    /// (the empty work log root is used as the initial commit).
    /// Use `State::Continuation { journal }` to resume from a prior execution
    /// (the journal's `updated_commit` is used as the initial commit for this update).
    #[builder(setter(into))]
    pub state: State,
    /// Series of work log updates to apply.
    #[builder(setter(into), default)]
    pub updates: Vec<WorkLogUpdate>,
    /// Image ID of the work log builder guest, provided to enable recursive verification.
    #[builder(setter(into))]
    pub self_image_id: Digest,
}

impl Input {
    /// Create an [InputBuilder] to construct an [Input].
    pub fn builder() -> InputBuilder {
        Default::default()
    }

    /// Serialize the input to a vector of bytes.
    pub fn encode(&self) -> Result<Vec<u8>, Error> {
        borsh::to_vec(self).map_err(Into::into)
    }

    /// Deserialize the input from a slice of bytes.
    pub fn decode(buffer: impl AsRef<[u8]>) -> Result<Self, Error> {
        borsh::from_slice(buffer.as_ref()).map_err(Into::into)
    }
}

/// A single work log update containing a work claim and its non-inclusion proof.
///
/// Used to prove that nonces consumed in this update are unused in the work log
/// to which the update is applied.
#[derive(Clone, Debug, Serialize, Deserialize, BorshSerialize, BorshDeserialize)]
#[non_exhaustive]
pub struct WorkLogUpdate {
    /// Work claim to be added to the log.
    pub claim: WorkClaim<Unknown>,
    /// Proof that the nonces consumed in this update are unused in the work log.
    pub noninclusion_proof: SubtreeOpening<WorkLog, { Job::TREE_HEIGHT }>,
}

impl WorkLogUpdate {
    /// Create a new [WorkLogUpdate] from the given claim and noninclusion proof for the job in its
    /// respective log.
    pub fn new(
        claim: impl Into<WorkClaim<Unknown>>,
        noninclusion_proof: SubtreeOpening<WorkLog, { Job::TREE_HEIGHT }>,
    ) -> Self {
        Self {
            claim: claim.into(),
            noninclusion_proof,
        }
    }
}

/// Journal output from PoVW guest program execution.
///
/// Contains the work log commitment updates and accumulated work value.
#[derive(
    Clone, Builder, Debug, Serialize, Deserialize, BorshSerialize, BorshDeserialize, PartialEq, Eq,
)]
#[non_exhaustive]
pub struct Journal {
    /// Work log ID that this journal corresponds to.
    #[builder(setter(into))]
    pub work_log_id: PovwLogId,
    /// Initial work log commitment.
    ///
    /// If the log is initially empty, the empty work log root constant is used.
    #[builder(setter(into))]
    pub initial_commit: Digest,
    /// Commitment to the work log after accumulating all work claims.
    #[builder(setter(into))]
    pub updated_commit: Digest,
    /// Sum of the values from the work claims included in this update.
    pub update_value: u64,
    /// Image ID of the work log builder guest, included to enable recursive verification.
    ///
    /// The verifier must ensure this digest is equal to the expected work log builder image ID.
    #[builder(setter(into))]
    pub self_image_id: Digest,
}

impl Journal {
    /// Create a [JournalBuilder] to construct a [Journal].
    pub fn builder() -> JournalBuilder {
        Default::default()
    }

    /// Serialize the journal to a vector of bytes.
    pub fn encode(&self) -> Result<Vec<u8>, Error> {
        borsh::to_vec(self).map_err(Into::into)
    }

    /// Deserialize the journal from a slice of bytes.
    pub fn decode(buffer: impl AsRef<[u8]>) -> Result<Self, Error> {
        borsh::from_slice(buffer.as_ref()).map_err(Into::into)
    }
}
