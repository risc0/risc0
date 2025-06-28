// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use risc0_zkvm::{Digest, Unknown, WorkClaim};
use ruint::aliases::U160;
use serde::{Deserialize, Serialize};

use crate::{Job, SubtreeOpening, WorkLog};

#[derive(Clone, Debug, Serialize, Deserialize, PartialEq, Eq)]
pub struct WorkLogCommit {
    pub log_id: U160,
    pub log_root: Digest,
}

impl WorkLogCommit {
    pub fn empty(work_log_id: U160) -> Self {
        Self {
            log_id: work_log_id,
            log_root: WorkLog::EMPTY.commit(),
        }
    }
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub enum State {
    Initial { work_log_id: U160 },
    Continuation { journal: Journal },
}

impl State {
    pub const fn initial(work_log_id: U160) -> Self {
        Self::Initial { work_log_id }
    }
}

impl From<Journal> for State {
    fn from(journal: Journal) -> Self {
        Self::Continuation { journal }
    }
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct Input {
    /// Optional journal from the previous execution of this guest.
    ///
    /// If provided, the updated root of the journal will be used as the initial root for this
    /// update. If not provided, an empty work log root constant is used.
    pub state: State,
    /// Series of work log updates to apply.
    pub updates: Vec<WorkLogUpdate>,
    /// Image ID of the work log builder guest, provided to enable recursive verification.
    pub self_image_id: Digest,
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct WorkLogUpdate {
    pub claim: WorkClaim<Unknown>,
    // TODO: Add a type-alias or something to make this less ugly.
    pub noninclusion_proof: SubtreeOpening<WorkLog, { Job::TREE_HEIGHT }>,
}

#[derive(Clone, Debug, Serialize, Deserialize, PartialEq, Eq)]
pub struct Journal {
    /// Optional initial work log commitment.
    ///
    /// If the log is initially empty, the empty work log root constant is used.
    pub initial_commit: WorkLogCommit,
    /// Commitment to the work log after accumulating all work claims.
    pub updated_commit: WorkLogCommit,
    /// Sum of the values from the work claims included in this update.
    pub update_value: u64,
    /// Image ID of the work log builder guest, included to enable recursive verification.
    ///
    /// The verifier must ensure this digest is equal to the expected work log builder image ID.
    pub self_image_id: Digest,
}
