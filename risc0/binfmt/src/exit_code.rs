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

use serde::{Deserialize, Serialize};

/// Exit condition indicated by the zkVM at the end of the guest execution.
///
/// Exit codes have a "system" part and a "user" part. Semantically, the system
/// part is set to indicate the type of exit (e.g. halt, pause, or system split)
/// and is directly controlled by the zkVM. The user part is an exit code,
/// similar to exit codes used in Linux, chosen by the guest program to indicate
/// additional information (e.g. 0 to indicate success or 1 to indicate an
/// error).
#[derive(Clone, Copy, Debug, Serialize, Deserialize, PartialEq)]
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

    /// This indicates that the guest exited upon reaching the session limit set
    /// by the host.
    SessionLimit,
}
