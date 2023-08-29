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
use std::{
    fs::File,
    io::{Read, Write},
    path::{Path, PathBuf},
};

use anyhow::Result;
use risc0_binfmt::MemoryImage;
use risc0_zkp::core::digest::Digest;
use serde::{Deserialize, Serialize};

use crate::host::{receipt::ExitCode, server::exec::executor::SyscallRecord};

#[derive(Clone, Default, Serialize, Deserialize, Debug)]
pub struct PageFaults {
    pub(crate) reads: BTreeSet<u32>,
    pub(crate) writes: BTreeSet<u32>,
}

/// The execution trace of a program.
///
/// The record of memory transactions of an execution that starts from an
/// initial memory image (which includes the starting PC) and proceeds until
/// either a sys_halt or a sys_pause syscall is encountered. This record is
/// stored as a vector of [Segment]s.
#[derive(Serialize, Deserialize)]
pub struct Session {
    /// The constituent [Segment]s of the Session. The final [Segment] will have
    /// an [ExitCode] of [Halted](ExitCode::Halted), [Paused](ExitCode::Paused),
    /// or [SessionLimit](ExitCode::SessionLimit), and all other [Segment]s (if
    /// any) will have [ExitCode::SystemSplit].
    pub segments: Vec<Box<dyn SegmentRef>>,

    /// The data publicly committed by the guest program.
    pub journal: Vec<u8>,

    /// The [ExitCode] of the session.
    pub exit_code: ExitCode,

    /// The hooks to be called during the proving phase.
    #[serde(skip)]
    pub hooks: Vec<Box<dyn SessionEvents>>,
}

/// A reference to a [Segment].
///
/// This allows implementors to determine the best way to represent this in an
/// pluggable manner. See the [SimpleSegmentRef] for a very basic
/// implmentation.
#[typetag::serde(tag = "type")]
pub trait SegmentRef: Send {
    /// Resolve this reference into an actual [Segment].
    fn resolve(&self) -> Result<Segment>;
}

/// The execution trace of a portion of a program.
///
/// The record of memory transactions of an execution that starts from an
/// initial memory image, and proceeds until terminated by the system or user.
/// This represents a chunk of execution work that will be proven in a single
/// call to the ZKP system. It does not necessarily represent an entire program;
/// see [Session] for tracking memory transactions until a user-requested
/// termination.
#[derive(Clone, Serialize, Deserialize)]
pub struct Segment {
    pub(crate) pre_image: MemoryImage,
    pub(crate) post_image_id: Digest,
    pub(crate) faults: PageFaults,
    pub(crate) syscalls: Vec<SyscallRecord>,
    pub(crate) split_insn: Option<u32>,
    pub(crate) exit_code: ExitCode,

    /// The number of cycles in powers of 2.
    pub po2: usize,

    /// The index of this [Segment] within the [Session]
    pub index: u32,

    /// The number of cycles used to execute instructions.
    pub insn_cycles: usize,
}

/// The Events of [Session]
pub trait SessionEvents {
    /// Fired before the proving of a segment starts.
    #[allow(unused)]
    fn on_pre_prove_segment(&self, segment: &Segment) {}

    /// Fired after the proving of a segment ends.
    #[allow(unused)]
    fn on_post_prove_segment(&self, segment: &Segment) {}
}

impl Session {
    /// Construct a new [Session] from its constituent components.
    pub fn new(segments: Vec<Box<dyn SegmentRef>>, journal: Vec<u8>, exit_code: ExitCode) -> Self {
        Self {
            segments,
            journal,
            exit_code,
            hooks: Vec::new(),
        }
    }

    /// A convenience method that resolves all [SegmentRef]s and returns the
    /// associated [Segment]s.
    pub fn resolve(&self) -> Result<Vec<Segment>> {
        self.segments
            .iter()
            .map(|segment_ref| segment_ref.resolve())
            .collect()
    }

    /// Add a hook to be called during the proving phase.
    pub fn add_hook<E: SessionEvents + 'static>(&mut self, hook: E) {
        self.hooks.push(Box::new(hook));
    }
}

impl Segment {
    /// Create a new [Segment] from its constituent components.
    #[allow(clippy::too_many_arguments)]
    pub(crate) fn new(
        pre_image: MemoryImage,
        post_image_id: Digest,
        faults: PageFaults,
        syscalls: Vec<SyscallRecord>,
        exit_code: ExitCode,
        split_insn: Option<u32>,
        po2: usize,
        index: u32,
        insn_cycles: usize,
    ) -> Self {
        log::info!("segment[{index}]> reads: {}, writes: {}, exit_code: {exit_code:?}, split_insn: {split_insn:?}, po2: {po2}, insn_cycles: {insn_cycles}",
            faults.reads.len(),
            faults.writes.len(),
        );
        Self {
            pre_image,
            post_image_id,
            faults,
            syscalls,
            exit_code,
            split_insn,
            po2,
            index,
            insn_cycles,
        }
    }
}

/// A very basic implementation of a [SegmentRef].
///
/// The [Segment] itself is stored in this implementation.
#[derive(Clone, Serialize, Deserialize)]
pub struct SimpleSegmentRef {
    segment: Segment,
}

#[typetag::serde]
impl SegmentRef for SimpleSegmentRef {
    fn resolve(&self) -> Result<Segment> {
        Ok(self.segment.clone())
    }
}

impl SimpleSegmentRef {
    /// Construct a [SimpleSegmentRef] with the specified [Segment].
    pub fn new(segment: Segment) -> Self {
        Self { segment }
    }
}

/// A basic implementation of a [SegmentRef] that saves the segment to a file
///
/// The [Segment] is stored in a user-specified file in this implementation,
/// and the SegmentRef holds the filename.
///
/// There is an example of using [FileSegmentRef] in [our EVM example]
/// (<https://github.com/risc0/risc0/blob/main/examples/zkevm-demo/src/main.rs>).
#[derive(Clone, Serialize, Deserialize)]
pub struct FileSegmentRef {
    path: PathBuf,
}

#[typetag::serde]
impl SegmentRef for FileSegmentRef {
    fn resolve(&self) -> Result<Segment> {
        let mut contents = Vec::new();
        let mut file = File::open(&self.path)?;
        file.read_to_end(&mut contents)?;
        let segment: Segment = bincode::deserialize(&contents)?;
        Ok(segment)
    }
}

impl FileSegmentRef {
    /// Construct a [FileSegmentRef]
    ///
    /// This builds a FileSegmentRef that stores `segment` in a file at `path`.
    pub fn new(segment: &Segment, path: &Path) -> Result<Self> {
        let path = path.join(format!("{}.bincode", segment.index));
        let mut file = File::create(&path)?;
        let contents = bincode::serialize(&segment)?;
        file.write_all(&contents)?;
        Ok(Self { path })
    }
}
