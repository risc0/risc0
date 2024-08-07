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

use core::fmt;

use borsh::{BorshDeserialize, BorshSerialize};
use serde::{Deserialize, Serialize};

/// Exit condition indicated by the zkVM at the end of the guest execution.
///
/// Exit codes have a "system" part and a "user" part. Semantically, the system
/// part is set to indicate the type of exit (e.g. halt, pause, or system split)
/// and is directly controlled by the zkVM. The user part is an exit code,
/// similar to exit codes used in Linux, chosen by the guest program to indicate
/// additional information (e.g. 0 to indicate success or 1 to indicate an
/// error).
#[derive(
    Clone, Copy, Debug, Serialize, Deserialize, PartialEq, BorshSerialize, BorshDeserialize,
)]
pub enum ExitCode {
    /// This indicates normal termination of a program with an interior exit
    /// code returned from the guest program. A halted program cannot be
    /// resumed.
    Halted(u32),

    /// This indicates the execution ended in a paused state with an interior
    /// exit code set by the guest program. A paused program can be resumed such
    /// that execution picks up where it left of, with the same memory state.
    Paused(u32),

    /// This indicates the execution ended on a host-initiated system split.
    ///
    /// System split is mechanism by which the host can temporarily stop
    /// execution of the guest. Execution ended in a system split has no output
    /// and no conclusions can be drawn about whether the program will
    /// eventually halt. System split is used in [continuations] to split
    /// execution into individually provable [segments].
    ///
    /// [continuations]: https://dev.risczero.com/terminology#continuations
    /// [segments]: https://dev.risczero.com/terminology#segment
    SystemSplit,

    /// This indicates that the guest exited upon reaching the session limit set by the host.
    ///
    /// NOTE: The current version of the RISC Zero zkVM will never exit with an exit code of SessionLimit.
    /// This is because the system cannot currently prove that the session limit as been reached.
    SessionLimit,
}

impl ExitCode {
    /// Convert this [ExitCode] into a pair representation, where the first number is the "system"
    /// part, and the second is the "user" part. E.g. Halted(255) -> (0, 255)
    pub fn into_pair(self) -> (u32, u32) {
        match self {
            ExitCode::Halted(user_exit) => (0, user_exit),
            ExitCode::Paused(user_exit) => (1, user_exit),
            ExitCode::SystemSplit => (2, 0),
            ExitCode::SessionLimit => (2, 2),
        }
    }

    /// Convert this [ExitCode] from its pair representation, where the first number is the "system"
    /// part, and the second is the "user" part. E.g. (0, 255) -> Halted(255)
    pub fn from_pair(sys_exit: u32, user_exit: u32) -> Result<ExitCode, InvalidExitCodeError> {
        match sys_exit {
            0 => Ok(ExitCode::Halted(user_exit)),
            1 => Ok(ExitCode::Paused(user_exit)),
            2 => Ok(ExitCode::SystemSplit),
            _ => Err(InvalidExitCodeError(sys_exit, user_exit)),
        }
    }

    /// Whether the verifier should expect a non-empty output field. Exit codes Halted and Paused
    /// produce can produce a non-empty outputs, whereas system initiated exits like SystemSplit do
    /// not.
    pub fn expects_output(&self) -> bool {
        match self {
            ExitCode::Halted(_) | ExitCode::Paused(_) => true,
            ExitCode::SystemSplit | ExitCode::SessionLimit => false,
        }
    }

    /// True if the exit code is Halted(0), indicating the program guest exited with an ok status.
    pub fn is_ok(&self) -> bool {
        matches!(self, ExitCode::Halted(0))
    }
}

impl Eq for ExitCode {}

/// Error returned when a `(system, user)` exit code pair is an invalid
/// representation.
#[derive(Debug, Copy, Clone)]
pub struct InvalidExitCodeError(pub u32, pub u32);

impl fmt::Display for InvalidExitCodeError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "invalid exit code pair ({}, {})", self.0, self.1)
    }
}

#[cfg(feature = "std")]
impl std::error::Error for InvalidExitCodeError {}
