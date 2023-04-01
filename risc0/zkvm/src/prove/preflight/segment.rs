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

use alloc::rc::Rc;
use core::cell::RefCell;

use anyhow::{anyhow, Result};
use risc0_zkp::{
    core::config::HashSuite,
    field::baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
    hal::Hal,
};

use crate::{
    prove::{
        default_hal,
        preflight::exec::{ExecState, OperationType, SyscallResult},
        EvalCheck, Syscall, SyscallContext,
    },
    ControlIdLocator, MemoryImage, Prover, ProverOpts, Receipt,
};

// TODO: Get this from ProverOpts::segment_limit_po2 once that option is
// available, and once we have cycle-accurate segmentation so we don't go over
// this limit.
const SEGMENT_LIMIT: usize = 1 << 22;

/// A Segment is a minimal execution trace of a segment of execution.
pub struct Segment {
    mem_init: MemoryImage,
    entry: u32,

    /// Number of cycles used in this segment
    cycles: usize,

    /// Results from all syscalls called.
    syscalls: Vec<SyscallResult>,
}

struct ReplaySyscalls<'a, I: Iterator<Item = &'a SyscallResult>> {
    iter: RefCell<I>,
}

impl<'a, I: Iterator<Item = &'a SyscallResult>> Syscall for ReplaySyscalls<'a, I> {
    fn syscall(
        &self,
        syscall: &str,
        _ctx: &dyn SyscallContext,
        to_guest: &mut [u32],
    ) -> Result<(u32, u32)> {
        let mut iter = self.iter.borrow_mut();
        let ret = iter
            .next()
            .ok_or_else(|| anyhow!("Extraneous syscall {syscall} in replay"))?;
        log::debug!(
            "Replaying syscall {syscall}, to_guest: {to_guest:?} regs {:?}",
            ret.regs
        );
        to_guest.clone_from_slice(ret.to_guest.as_slice());
        Ok(ret.regs)
    }
}

impl<'a, I: Iterator<Item = &'a SyscallResult>> ReplaySyscalls<'a, I> {
    pub fn new(iter: I) -> Self {
        Self {
            iter: RefCell::new(iter),
        }
    }
}

impl Segment {
    fn new(exec: &ExecState) -> Segment {
        // TODO: Once we integrate pageouts, we shouldn't need to
        // rehash all the memory for each segment.
        let mut mem_init = exec.mem.clone();
        mem_init.hash_pages();
        Segment {
            mem_init: mem_init,
            entry: exec.pc,

            cycles: 0,
            syscalls: Vec::new(),
        }
    }

    fn is_empty(&self) -> bool {
        self.cycles == 0
    }

    pub fn prove(&self) -> Result<Receipt> {
        let (hal, eval) = default_hal();
        self.prove_with_hal(hal.as_ref(), &eval)
    }

    pub fn prove_with_hal<H, E>(&self, hal: &H, eval: &E) -> Result<Receipt>
    where
        H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
        <<H as Hal>::HashSuite as HashSuite<BabyBear>>::Hash: ControlIdLocator,
        E: EvalCheck<H>,
    {
        log::debug!(
            "Running prover on segment, entry = {}, {} cycles, {} syscalls",
            self.entry,
            self.cycles,
            self.syscalls.len()
        );
        // TODO: Prover::run havs a lot of overhead, like expanding
        // and such, that we don't need to do here.  We should optimize.
        let mut opts = ProverOpts::without_defaults()
            .with_unknown_syscall_handler(ReplaySyscalls::new(self.syscalls.iter()))
            .with_skip_verify(true);
        opts.finalized = true;
        let mut p = Prover::from_image(
            Rc::new(RefCell::new(self.mem_init.clone())),
            self.entry,
            opts,
        )?;

        p.run_with_hal(hal, eval)
    }
}

pub struct Segmentize<'a> {
    exec: ExecState<'a>,

    // Current segment so far
    segment: Segment,
}
impl<'a> Iterator for Segmentize<'a> {
    type Item = Result<Segment>;

    fn next(&mut self) -> Option<Result<Segment>> {
        self.try_next().transpose()
    }
}

impl<'a> Segmentize<'a> {
    pub fn new(exec: ExecState<'a>) -> Self {
        let segment = Segment::new(&exec);
        Self { exec, segment }
    }

    fn try_next(&mut self) -> Result<Option<Segment>> {
        log::debug!("Trying to get next segment");
        while !self.exec.is_terminated() {
            let op = self.exec.compute()?;
            if op.circuit_cycles + self.segment.cycles > SEGMENT_LIMIT {
                // If this would overflow, discard the results of this
                // cycle and return a segment.
                // TODO: Make this cycle accurate instead of just an estimation.
                assert!(!self.segment.is_empty());

                log::debug!("Segmentize making a new segment at {}", self.segment.cycles);

                return Ok(Some(core::mem::replace(
                    &mut self.segment,
                    Segment::new(&self.exec),
                )));
            }

            self.exec.apply(&op)?;
            self.segment.cycles += op.circuit_cycles;
            self.segment.syscalls.extend(op.syscalls);

            if let OperationType::Pause = op.op_type {
                return Ok(Some(core::mem::replace(
                    &mut self.segment,
                    Segment::new(&self.exec),
                )));
            }
        }

        if self.segment.is_empty() {
            log::debug!("Last segment is empty");
            Ok(None)
        } else {
            let last = core::mem::replace(&mut self.segment, Segment::new(&self.exec));
            assert!(self.segment.is_empty());

            log::debug!("Segmentize returning last segment at {}", last.cycles);

            Ok(Some(last))
        }
    }
}
