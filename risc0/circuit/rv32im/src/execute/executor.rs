// Copyright 2025 RISC Zero, Inc.
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

use std::{
    cell::RefCell,
    collections::BTreeSet,
    rc::Rc,
    sync::mpsc::{sync_channel, SyncSender},
    thread::{self, ScopedJoinHandle},
};

use anyhow::{bail, Context, Result};
use enum_map::EnumMap;
use ringbuffer::{AllocRingBuffer, RingBuffer};
use risc0_binfmt::{ByteAddr, MemoryImage, PovwJobId, PovwNonce, WordAddr};
use risc0_zkp::core::{
    digest::{Digest, DIGEST_BYTES},
    log2_ceil,
};

use crate::{
    execute::rv32im::disasm,
    trace::{TraceCallback, TraceEvent},
    Rv32imV2Claim, TerminateState,
};

use super::{
    bigint,
    pager::{compute_partial_image, PageTraceEvent, PagedMemory, WorkingImage},
    platform::*,
    poseidon2::Poseidon2State,
    r0vm::{EcallKind, LoadOp, Risc0Context, Risc0Machine},
    rv32im::{DecodedInstruction, Emulator, InsnKind},
    segment::Segment,
    sha2::Sha2State,
    syscall::Syscall,
    unlikely, SyscallContext,
};

#[derive(Clone, Debug, Default)]
#[non_exhaustive]
pub struct EcallMetric {
    pub count: u64,
    pub cycles: u64,
}

#[derive(Default)]
pub struct EcallMetrics(EnumMap<EcallKind, EcallMetric>);

pub struct Executor<'a, 'b, S: Syscall> {
    pc: ByteAddr,
    user_pc: ByteAddr,
    machine_mode: u32,
    user_cycles: u32,
    initial_image: MemoryImage,
    pager: PagedMemory,
    terminate_state: Option<TerminateState>,
    read_record: Vec<Vec<u8>>,
    write_record: Vec<u32>,
    syscall_handler: &'a S,
    input_digest: Digest,
    output_digest: Option<Digest>,
    trace: Vec<Rc<RefCell<dyn TraceCallback + 'b>>>,
    cycles: SessionCycles,
    ecall_metrics: EcallMetrics,
    ring: AllocRingBuffer<(ByteAddr, InsnKind, DecodedInstruction)>,
    povw_job_id: Option<PovwJobId>,
    segment_counter: u32,
}

#[non_exhaustive]
pub struct ExecutorResult {
    pub segments: u64,
    pub post_image: MemoryImage,
    pub user_cycles: u64,
    pub total_cycles: u64,
    pub paging_cycles: u64,
    pub reserved_cycles: u64,
    pub claim: Rv32imV2Claim,
}

#[derive(Default)]
struct SessionCycles {
    total: u64,
    user: u64,
    paging: u64,
    reserved: u64,
}

#[non_exhaustive]
pub struct SimpleSession {
    pub segments: Vec<Segment>,
    pub result: ExecutorResult,
}

pub enum CycleLimit {
    Hard(u64), // it is an error to exceed this limit
    Soft(u64), // stop execution after this cycle count
    None,
}

struct CreateSegmentRequest {
    // Partial image containing pages that were written to in the segment.
    update_partial_image: WorkingImage,
    // Indices of all pages that were accessed in the segment.
    access_page_indexes: BTreeSet<u32>,

    input_digest: Digest,
    output_digest: Option<Digest>,
    read_record: Vec<Vec<u8>>,
    write_record: Vec<u32>,
    user_cycles: u32,
    pager_cycles: u32,
    terminate_state: Option<TerminateState>,
    segment_threshold: u32,
    po2: u32,
    index: u64,
    povw_nonce: Option<PovwNonce>,

    dump_path: Option<std::ffi::OsString>,
}

/// Maximum number of segments we can queue up before we block execution
const MAX_OUTSTANDING_SEGMENTS: usize = 5;

fn create_segments(
    initial_image: MemoryImage,
    recv: std::sync::mpsc::Receiver<CreateSegmentRequest>,
    mut callback: impl FnMut(Segment) -> Result<()>,
) -> Result<(Digest, Digest, MemoryImage)> {
    let mut existing_image = initial_image;
    let initial_digest = existing_image.image_id();

    while let Ok(req) = recv.recv() {
        // Compute the partial image that from the initial memory state that will be sent to
        // preflight for re-execution of the segment.
        let pre_digest = existing_image.image_id();
        let partial_image = compute_partial_image(&mut existing_image, req.access_page_indexes);

        // Update the image held locally to the state after segment execution.
        for (idx, page) in req.update_partial_image.pages {
            existing_image.set_page(idx, page);
        }
        existing_image.update_digests();
        let post_digest = existing_image.image_id();

        let segment = Segment {
            // TODO(victor/perf): Can we get away with sending a WorkingImage (i.e. without the
            // hashes) here instead? Without the uncles, it would not be possible to reconstruct
            // the claim. But maybe it would be cheaper if we could compute _just_ the uncles, and
            // avoid hashing pages that are included in the message. We'd also need to drop the
            // claim field from Segment, as it includes the root digests. It would no longer be
            // possible to compute the claim without re-executing the segment, to get the final
            // memory state and hash it.
            partial_image,
            claim: Rv32imV2Claim {
                pre_state: pre_digest,
                post_state: post_digest,
                input: req.input_digest,
                output: req.output_digest,
                terminate_state: req.terminate_state,
                shutdown_cycle: None,
            },
            read_record: req.read_record,
            write_record: req.write_record,
            suspend_cycle: req.user_cycles,
            paging_cycles: req.pager_cycles,
            po2: req.po2,
            index: req.index,
            segment_threshold: req.segment_threshold,
            povw_nonce: req.povw_nonce,
        };

        if let Some(dump_path) = req.dump_path {
            tracing::error!("{segment:?}");

            let bytes = segment.encode()?;
            tracing::error!("serialized {} bytes", bytes.len());

            std::fs::write(dump_path, bytes)?;
            break;
        }

        callback(segment)?;
    }
    Ok((initial_digest, existing_image.image_id(), existing_image))
}

impl<'a, 'b, S: Syscall> Executor<'a, 'b, S> {
    pub fn new(
        image: MemoryImage,
        syscall_handler: &'a S,
        input_digest: Option<Digest>,
        trace: Vec<Rc<RefCell<dyn TraceCallback + 'b>>>,
        povw_job_id: Option<PovwJobId>,
    ) -> Self {
        Self {
            pc: ByteAddr(0),
            user_pc: ByteAddr(0),
            machine_mode: 0,
            user_cycles: 0,
            pager: PagedMemory::new(image.clone(), /*tracing_enabled=*/ !trace.is_empty()),
            initial_image: image,
            terminate_state: None,
            read_record: Vec::new(),
            write_record: Vec::new(),
            syscall_handler,
            input_digest: input_digest.unwrap_or_default(),
            output_digest: None,
            trace,
            cycles: SessionCycles::default(),
            ecall_metrics: EcallMetrics::default(),
            ring: AllocRingBuffer::new(10),
            povw_job_id,
            segment_counter: 0,
        }
    }

    pub fn run(
        &mut self,
        segment_po2: usize,
        max_insn_cycles: usize,
        max_cycles: CycleLimit,
        callback: impl FnMut(Segment) -> Result<()> + Send,
    ) -> Result<ExecutorResult> {
        let segment_limit: u32 = 1 << segment_po2;
        assert!(max_insn_cycles < segment_limit as usize);
        let segment_threshold = segment_limit - max_insn_cycles as u32;

        self.reset();

        let mut emu = Emulator::new();
        Risc0Machine::resume(self)?;

        let (commit_sender, commit_recv) = sync_channel(MAX_OUTSTANDING_SEGMENTS - 1);

        let initial_image = self.initial_image.clone();
        let (initial_digest, post_digest, post_image) = thread::scope(|scope| {
            let segment_callback_thread =
                scope.spawn(move || create_segments(initial_image, commit_recv, callback));

            while self.terminate_state.is_none() {
                match max_cycles {
                    CycleLimit::Hard(max_cycles) => {
                        if self.cycles.user >= max_cycles {
                            bail!(
                                "Session limit exceeded: {} >= {max_cycles}",
                                self.cycles.user
                            );
                        }
                    }
                    CycleLimit::Soft(max_cycles) => {
                        if self.cycles.user >= max_cycles {
                            break;
                        }
                    }
                    CycleLimit::None => {}
                }

                if self.segment_cycles() > segment_threshold {
                    assert!(
                        self.segment_cycles() < segment_limit,
                        "segment limit ({segment_limit}) too small for instruction at pc: {:?}",
                        self.pc
                    );

                    Risc0Machine::suspend(self)?;
                    self.split_segment(&commit_sender, segment_po2, segment_threshold)?;
                    Risc0Machine::resume(self)?;
                }

                let result = Risc0Machine::step(&mut emu, self);

                if let Err(err) = result {
                    self.dump();
                    let result = self.dump_segment(
                        commit_sender,
                        segment_callback_thread,
                        segment_po2,
                        segment_threshold,
                        self.segment_counter,
                    );
                    return Err(if let Err(inner) = result {
                        err.context(inner)
                    } else {
                        err
                    });
                }
            }

            Risc0Machine::suspend(self)?;

            let final_cycles = self.segment_cycles().next_power_of_two();
            let final_po2 = log2_ceil(final_cycles as usize);
            self.split_segment(
                &commit_sender,
                final_po2,
                0, // theshold is meaningless for final segment
            )?;

            drop(commit_sender);

            segment_callback_thread.join().unwrap()
        })?;

        let session_claim = Rv32imV2Claim {
            pre_state: initial_digest,
            post_state: post_digest,
            input: self.input_digest,
            output: self.output_digest,
            terminate_state: self.terminate_state,
            shutdown_cycle: None,
        };

        Ok(ExecutorResult {
            segments: self.segment_counter as u64 + 1,
            post_image,
            user_cycles: self.cycles.user,
            total_cycles: self.cycles.total,
            paging_cycles: self.cycles.paging,
            reserved_cycles: self.cycles.reserved,
            claim: session_claim,
        })
    }

    fn split_segment(
        &mut self,
        commit_sender: &SyncSender<CreateSegmentRequest>,
        segment_po2: usize,
        segment_threshold: u32,
    ) -> Result<()> {
        tracing::debug!(
            "split(phys: {} + pager: {} + reserved: {RESERVED_CYCLES}) = {} >= {segment_threshold}",
            self.user_cycles,
            self.pager.cycles,
            self.segment_cycles()
        );

        let partial_image = self.pager.commit();

        let req = CreateSegmentRequest {
            update_partial_image: partial_image,
            access_page_indexes: self.pager.page_indexes(),
            input_digest: self.input_digest,
            output_digest: self.output_digest,
            read_record: std::mem::take(&mut self.read_record),
            write_record: std::mem::take(&mut self.write_record),
            user_cycles: self.user_cycles,
            pager_cycles: self.pager.cycles,
            terminate_state: self.terminate_state,
            segment_threshold,
            po2: segment_po2 as u32,
            index: self.segment_counter as u64,
            dump_path: None,
            povw_nonce: self.povw_nonce(self.segment_counter),
        };
        if commit_sender.send(req).is_err() {
            //return Err(segment_callback_thread.join().unwrap().unwrap_err());
            bail!("DO NOT MERGE")
        }

        // NOTE: There is no reasonable scenario where a session will have more than 4B
        // segments, but its possible.
        self.segment_counter = self
            .segment_counter
            .checked_add(1)
            .context("segment_counter overflow")?;

        let total_cycles = 1 << segment_po2;
        let pager_cycles = self.pager.cycles as u64;
        let user_cycles = self.user_cycles as u64;
        self.cycles.total += total_cycles;
        self.cycles.paging += pager_cycles;
        self.cycles.reserved += total_cycles - pager_cycles - user_cycles;
        self.user_cycles = 0;
        self.pager.reset();

        Ok(())
    }

    pub(crate) fn terminate_state(&self) -> Option<&TerminateState> {
        self.terminate_state.as_ref()
    }

    fn dump(&self) {
        tracing::debug!("Dumping last {} instructions:", self.ring.len());
        for (pc, kind, decoded) in self.ring.iter() {
            tracing::debug!("{pc:?}> {:#010x}  {}", decoded.insn, disasm(*kind, decoded));
        }
    }

    fn dump_segment<RetT>(
        &mut self,
        commit_sender: SyncSender<CreateSegmentRequest>,
        segment_callback_thread: ScopedJoinHandle<'_, Result<RetT>>,
        po2: usize,
        segment_threshold: u32,
        index: u32,
    ) -> anyhow::Result<()> {
        if let Some(dump_path) = std::env::var_os("RISC0_DUMP_PATH") {
            tracing::error!(
                "Execution failure, saving segment to {}:",
                dump_path.to_string_lossy()
            );

            let partial_image = self.pager.commit();

            let req = CreateSegmentRequest {
                update_partial_image: partial_image,
                access_page_indexes: self.pager.page_indexes(),
                input_digest: self.input_digest,
                output_digest: self.output_digest,
                read_record: std::mem::take(&mut self.read_record),
                write_record: std::mem::take(&mut self.write_record),
                user_cycles: self.user_cycles,
                pager_cycles: self.pager.cycles,
                terminate_state: self.terminate_state,
                segment_threshold,
                po2: po2 as u32,
                index: index as u64,
                dump_path: Some(dump_path),
                povw_nonce: self.povw_nonce(index),
            };
            let _ = commit_sender.send(req);
            let _ = segment_callback_thread.join().unwrap()?;
        }
        Ok(())
    }

    pub fn take_ecall_metrics(&mut self) -> EcallMetrics {
        std::mem::take(&mut self.ecall_metrics)
    }

    fn reset(&mut self) {
        self.pager.reset();
        self.terminate_state = None;
        self.read_record.clear();
        self.write_record.clear();
        self.output_digest = None;
        self.machine_mode = 0;
        self.user_cycles = 0;
        self.cycles = SessionCycles::default();
        self.pc = ByteAddr(0);
        self.ecall_metrics = EcallMetrics::default();
        self.segment_counter = 0;
    }

    fn segment_cycles(&self) -> u32 {
        self.user_cycles + self.pager.cycles + RESERVED_CYCLES as u32
    }

    fn inc_user_cycles(&mut self, count: usize, ecall: Option<EcallKind>) {
        self.cycles.user += count as u64;
        self.user_cycles += count as u32;
        if let Some(kind) = ecall {
            self.ecall_metrics.0[kind].cycles += count as u64;
        }
    }

    fn povw_nonce(&self, segment_index: u32) -> Option<PovwNonce> {
        self.povw_job_id.map(|job| job.nonce(segment_index))
    }

    #[cold]
    fn trace(&mut self, event: TraceEvent) -> Result<()> {
        for trace in self.trace.iter() {
            trace.borrow_mut().trace_callback(event.clone())?;
        }
        Ok(())
    }

    #[cold]
    fn trace_pager(&mut self) -> Result<()> {
        for &event in self.pager.trace_events() {
            let event = TraceEvent::from(event);
            for trace in self.trace.iter() {
                trace.borrow_mut().trace_callback(event.clone())?;
            }
        }
        self.pager.clear_trace_events();
        Ok(())
    }

    #[inline(always)]
    fn trace_instruction(&mut self, cycle: u64, kind: InsnKind, decoded: &DecodedInstruction) {
        if cfg!(feature = "exec_debug") {
            if unlikely(tracing::enabled!(tracing::Level::TRACE)) {
                tracing::trace!(
                    "[{}:{}:{cycle}] {:?}> {:#010x}  {}",
                    self.user_cycles + 1,
                    self.segment_cycles() + 1,
                    self.pc,
                    decoded.insn,
                    super::rv32im::disasm(kind, decoded)
                );
            }
            if unlikely(tracing::enabled!(tracing::Level::DEBUG)) {
                self.ring.push((self.pc, kind, decoded.clone()));
            }
        }
    }
}

impl<S: Syscall> Risc0Context for Executor<'_, '_, S> {
    fn get_pc(&self) -> ByteAddr {
        self.pc
    }

    fn set_pc(&mut self, addr: ByteAddr) {
        self.pc = addr;
    }

    fn set_user_pc(&mut self, addr: ByteAddr) {
        self.user_pc = addr;
    }

    fn get_machine_mode(&self) -> u32 {
        self.machine_mode
    }

    fn set_machine_mode(&mut self, mode: u32) {
        self.machine_mode = mode;
    }

    fn resume(&mut self) -> Result<()> {
        let input_words = self.input_digest.as_words().to_vec();
        for (i, word) in input_words.iter().enumerate() {
            self.store_u32(GLOBAL_INPUT_ADDR.waddr() + i, *word)?;
        }
        Ok(())
    }

    #[inline(always)]
    fn on_insn_start(&mut self, kind: InsnKind, decoded: &DecodedInstruction) -> Result<()> {
        let cycle = self.cycles.user;
        self.trace_instruction(cycle, kind, decoded);
        if unlikely(!self.trace.is_empty()) {
            self.trace(TraceEvent::InstructionStart {
                cycle,
                pc: self.pc.0,
                insn: decoded.insn,
            })?;
        }
        Ok(())
    }

    #[inline(always)]
    fn on_insn_end(&mut self, _kind: InsnKind) -> Result<()> {
        self.inc_user_cycles(1, None);
        if unlikely(!self.trace.is_empty()) {
            self.trace_pager()?;
        }
        Ok(())
    }

    fn on_ecall_cycle(
        &mut self,
        cur: CycleState,
        _next: CycleState,
        _s0: u32,
        _s1: u32,
        _s2: u32,
        kind: EcallKind,
    ) -> Result<()> {
        if cur == CycleState::MachineEcall {
            self.ecall_metrics.0[kind].count += 1;
        }
        self.inc_user_cycles(1, Some(kind));
        if !self.trace.is_empty() {
            self.trace_pager()?;
        }
        Ok(())
    }

    #[inline(always)]
    fn load_u32(&mut self, op: LoadOp, addr: WordAddr) -> Result<u32> {
        let word = match op {
            LoadOp::Peek => self.pager.peek(addr)?,
            LoadOp::Load | LoadOp::Record => self.pager.load(addr)?,
        };
        // tracing::trace!("load_mem({:?}) -> {word:#010x}", addr.baddr());
        Ok(word)
    }

    #[inline(always)]
    fn load_register(&mut self, _op: LoadOp, base: WordAddr, idx: usize) -> Result<u32> {
        let word = self.pager.load_register(base, idx);
        // tracing::trace!("load_register({:?}) -> {word:#010x}", addr.baddr());
        Ok(word)
    }

    #[inline(always)]
    fn store_u32(&mut self, addr: WordAddr, word: u32) -> Result<()> {
        // tracing::trace!(
        //     "store_u32({:?}, {word:#010x}), pc: {:?}",
        //     addr.baddr(),
        //     self.pc
        // );
        if unlikely(!self.trace.is_empty()) {
            self.trace(TraceEvent::MemorySet {
                addr: addr.baddr().0,
                region: word.to_be_bytes().to_vec(),
            })?;
        }
        self.pager.store(addr, word)
    }

    #[inline(always)]
    fn store_register(&mut self, base: WordAddr, idx: usize, word: u32) -> Result<()> {
        // tracing::trace!("store_register({:?}, {word:#010x})", addr.baddr());
        if unlikely(!self.trace.is_empty()) {
            self.trace(TraceEvent::MemorySet {
                addr: (base + idx).baddr().0,
                region: word.to_be_bytes().to_vec(),
            })?;
        }
        self.pager.store_register(base, idx, word);
        Ok(())
    }

    fn on_terminate(&mut self, a0: u32, a1: u32) -> Result<()> {
        self.terminate_state = Some(TerminateState {
            a0: a0.into(),
            a1: a1.into(),
        });
        tracing::debug!("{:?}", self.terminate_state);

        let output: Digest = self
            .load_region(LoadOp::Peek, GLOBAL_OUTPUT_ADDR, DIGEST_BYTES)?
            .as_slice()
            .try_into()?;
        self.output_digest = Some(output);

        Ok(())
    }

    fn host_read(&mut self, fd: u32, buf: &mut [u8]) -> Result<u32> {
        let rlen = self.syscall_handler.host_read(self, fd, buf)?;
        let slice = &buf[..rlen as usize];
        self.read_record.push(slice.to_vec());
        Ok(rlen)
    }

    fn host_write(&mut self, fd: u32, buf: &[u8]) -> Result<u32> {
        let rlen = self.syscall_handler.host_write(self, fd, buf)?;
        self.write_record.push(rlen);
        Ok(rlen)
    }

    fn on_sha2_cycle(&mut self, _cur_state: CycleState, _sha2: &Sha2State) {
        self.inc_user_cycles(1, Some(EcallKind::Sha2));
    }

    fn on_poseidon2_cycle(&mut self, _cur_state: CycleState, _p2: &Poseidon2State) {
        self.inc_user_cycles(1, Some(EcallKind::Poseidon2));
    }

    fn ecall_bigint(&mut self) -> Result<()> {
        let cycles = bigint::ecall_execute(self)?;
        self.inc_user_cycles(cycles, Some(EcallKind::BigInt));
        Ok(())
    }
}

impl<S: Syscall> SyscallContext for Executor<'_, '_, S> {
    fn peek_register(&mut self, idx: usize) -> Result<u32> {
        if idx >= REG_MAX {
            bail!("invalid register: x{idx}");
        }
        self.load_register(LoadOp::Peek, USER_REGS_ADDR.waddr(), idx)
    }

    fn peek_u32(&mut self, addr: ByteAddr) -> Result<u32> {
        // let addr = Self::check_guest_addr(addr)?;
        self.load_u32(LoadOp::Peek, addr.waddr())
    }

    fn peek_u8(&mut self, addr: ByteAddr) -> Result<u8> {
        // let addr = Self::check_guest_addr(addr)?;
        self.load_u8(LoadOp::Peek, addr)
    }

    fn peek_region(&mut self, addr: ByteAddr, size: usize) -> Result<Vec<u8>> {
        // let addr = Self::check_guest_addr(addr)?;
        self.load_region(LoadOp::Peek, addr, size)
    }

    fn get_cycle(&self) -> u64 {
        self.cycles.user
    }

    fn get_pc(&self) -> u32 {
        self.user_pc.0
    }
}

impl From<EcallMetrics> for Vec<(String, EcallMetric)> {
    fn from(metrics: EcallMetrics) -> Self {
        metrics
            .0
            .into_iter()
            .map(|(kind, metric)| (format!("{kind:?}"), metric))
            .collect()
    }
}

impl From<PageTraceEvent> for TraceEvent {
    fn from(event: PageTraceEvent) -> Self {
        match event {
            PageTraceEvent::PageIn { cycles } => TraceEvent::PageIn {
                cycles: cycles as u64,
            },
            PageTraceEvent::PageOut { cycles } => TraceEvent::PageOut {
                cycles: cycles as u64,
            },
        }
    }
}
