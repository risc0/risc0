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

//! This module defines [Session] and [Segment] which provides a way to share
//! execution traces between the execution phase and the proving phase.

use alloc::collections::BTreeSet;

use risc0_zkp::core::digest::Digest;
use serde::{Deserialize, Serialize};

use crate::{exec::SyscallRecord, MemoryImage};

/// TODO
#[derive(Clone, Copy, Debug, PartialEq, Serialize, Deserialize)]
pub enum ExitCode {
    /// This indicates when a system-initiated split has occured due to the
    /// segment limit being exceeded.
    SystemSplit,

    /// This indicates that the session limit has been reached.
    SessionLimit,

    /// A user may manually pause a session so that it can be resumed at a later
    /// time.
    Paused,

    /// This indicates normal termination of a program with an interior exit
    /// code returned from the guest.
    Halted(u32),
}

#[derive(Clone, Default, Serialize, Deserialize)]
pub struct PageFaults {
    pub(crate) reads: BTreeSet<u32>,
    pub(crate) writes: BTreeSet<u32>,
}

/// TODO
#[derive(Serialize, Deserialize)]
pub struct Session {
    /// TODO
    pub segments: Vec<Segment>,

    /// TODO
    pub journal: Vec<u8>,
}

/// TODO
#[derive(Serialize, Deserialize)]
pub struct Segment {
    pub(crate) pre_image: MemoryImage,
    pub(crate) post_image_id: Digest,
    pub(crate) pc: u32,
    pub(crate) faults: PageFaults,
    pub(crate) syscalls: Vec<SyscallRecord>,
    pub(crate) exit_code: ExitCode,
}

impl Session {
    /// TODO
    pub fn new(segments: Vec<Segment>, journal: Vec<u8>) -> Self {
        Self { segments, journal }
    }
}

impl Segment {
    pub(crate) fn new(
        pre_image: MemoryImage,
        post_image_id: Digest,
        pc: u32,
        faults: PageFaults,
        syscalls: Vec<SyscallRecord>,
        exit_code: ExitCode,
    ) -> Self {
        Self {
            pre_image,
            post_image_id,
            pc,
            faults,
            syscalls,
            exit_code,
        }
    }
}
