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

use alloc::{collections::VecDeque, vec::Vec};
use core::{convert::Infallible, fmt};

use crate::{
    sha::{tagged_struct, Digest},
    SystemState,
};
use risc0_binfmt::{read_sha_halfs, write_sha_halfs};
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

    pub(crate) fn from_pair(
        sys_exit: u32,
        user_exit: u32,
    ) -> Result<ExitCode, InvalidExitCodeError> {
        match sys_exit {
            0 => Ok(ExitCode::Halted(user_exit)),
            1 => Ok(ExitCode::Paused(user_exit)),
            2 => Ok(ExitCode::SystemSplit),
            3 => Ok(ExitCode::SessionLimit),
            _ => Err(InvalidExitCodeError(sys_exit, user_exit)),
        }
    }
}

#[derive(Debug, Copy, Clone)]
pub struct InvalidExitCodeError(u32, u32);

impl fmt::Display for InvalidExitCodeError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "invalid exit code pair ({}, {})", self.0, self.1)
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
                self.pre.digest::<crate::sha::Impl>(),
                self.post.digest::<crate::sha::Impl>(),
                self.output,
            ],
            &[sys_exit, user_exit],
        )
    }

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
            pre,
            post,
            exit_code,
            output,
        })
    }

    // TODO(victor): Consider returning () instead of Result<(), Infallible>
    /// Encode a [crate::ReceiptMetadata] to a list of [u32]'s
    pub fn encode(&self, flat: &mut Vec<u32>) -> Result<(), Infallible> {
        write_sha_halfs(flat, &self.input);
        self.pre.encode(flat);
        self.post.encode(flat);
        let (sys_exit, user_exit) = self.exit_code.into_pair();
        flat.push(sys_exit);
        flat.push(user_exit);
        write_sha_halfs(flat, &self.output);
        Ok(())
    }
}
