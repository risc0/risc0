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

use crate::{sha::Digest, SystemState};
use risc0_binfmt::tagged_struct;
use serde::{Deserialize, Serialize};

/// Indicates how a Segment or Session's execution has terminated
#[derive(Clone, Copy, Debug, PartialEq, Serialize, Deserialize)]
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
}

impl ExitCode {
    pub(crate) fn into_pair(self) -> (u32, u32) {
        match self {
            ExitCode::Halted(user_exit) => (0, user_exit),
            ExitCode::Paused(user_exit) => (1, user_exit),
            ExitCode::SystemSplit => (2, 0),
            // DO NOT MERGE(victor): Confirm SessionLimit can have an associated exit code.
            ExitCode::SessionLimit => (3, 0),
        }
    }
}

/// Data associated with a receipt which is used for both input and
/// output of global state.
#[derive(Clone, Debug, Serialize, Deserialize, PartialEq)]
pub struct ReceiptMetadata {
    /// The [SystemState] of a segment just before execution has begun.
    pub pre: SystemState,

    /// The [SystemState] of a segment just after execution has completed.
    pub post: SystemState,

    /// The exit code for a segment
    pub exit_code: ExitCode,

    /// A [Digest] of the input, from the viewpoint of the guest.
    pub input: Digest,

    /// A [Digest] of the journal, from the viewpoint of the guest.
    pub output: Digest,
}

impl ReceiptMetadata {
    /// Hash the [crate::ReceiptMetadata] to get a digest of the struct.
    pub fn digest(&self) -> Digest {
        let (sys_exit, user_exit) = self.exit_code.into_pair();
        tagged_struct(
            "risc0.ReceiptMeta",
            &[
                self.input,
                self.pre.digest(),
                self.post.digest(),
                self.output,
            ],
            &[sys_exit, user_exit],
        )
    }
}
