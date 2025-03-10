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

use std::{cell::RefCell, collections::BTreeSet, rc::Rc};

use anyhow::{bail, Result};
use risc0_binfmt::{ByteAddr, MemoryImage2, WordAddr};
use risc0_zkp::core::{
    digest::{Digest, DIGEST_BYTES},
    log2_ceil,
};

use crate::{
    trace::{TraceCallback, TraceEvent},
    Rv32imV2Claim, TerminateState,
};

use super::{
    bigint::BigIntState,
    pager::{compute_partial_image, PageTraceEvent, PagedMemory},
    platform::*,
    poseidon2::Poseidon2State,
    r0vm::{LoadOp, Risc0Context, Risc0Machine},
    rv32im::{disasm, DecodedInstruction, Emulator, Instruction},
    segment::Segment,
    sha2::Sha2State,
    syscall::Syscall,
    SyscallContext,
};

#[derive(Clone, Debug, Default)]
pub struct EcallMetric {
    pub count: u64,
    pub cycles: u64,
}

pub struct Executor<'a, 'b, S: Syscall> {
    pc: ByteAddr,
    user_pc: ByteAddr,
    machine_mode: u32,
    user_cycles: u32,
    phys_cycles: u32,
    pager: PagedMemory,
    terminate_state: Option<TerminateState>,
    read_record: Vec<Vec<u8>>,
    write_record: Vec<u32>,
    syscall_handler: &'a S,
    input_digest: Digest,
    output_digest: Option<Digest>,
    trace: Vec<Rc<RefCell<dyn TraceCallback + 'b>>>,
    cycles: SessionCycles,
}

pub struct ExecutorResult {
    pub segments: u64,
    pub post_image: MemoryImage2,
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

pub struct SimpleSession {
    pub segments: Vec<Segment>,
    pub result: ExecutorResult,
}

struct ComputePartialImageRequest {
    image: MemoryImage2,
    page_indexes: BTreeSet<u32>,

    input_digest: Digest,
    output_digest: Option<Digest>,
    read_record: Vec<Vec<u8>>,
    write_record: Vec<u32>,
    user_cycles: u32,
    phys_cycles: u32,
    pager_cycles: u32,
    terminate_state: Option<TerminateState>,
    segment_threshold: u32,
    pre_digest: Digest,
    post_digest: Digest,
    po2: u32,
}

/// Maximum number of segments we can queue up before we block execution
const MAX_OUTSTANDING_SEGMENTS: usize = 5;

fn compute_partial_images(
    recv: std::sync::mpsc::Receiver<ComputePartialImageRequest>,
    mut callback: impl FnMut(Segment) -> Result<()>,
) -> Result<u64> {
    let mut segment_counter = 0;
    while let Ok(req) = recv.recv() {
        let partial_image = compute_partial_image(req.image, req.page_indexes);
        callback(Segment {
            partial_image,
            claim: Rv32imV2Claim {
                pre_state: req.pre_digest,
                post_state: req.post_digest,
                input: req.input_digest,
                output: req.output_digest,
                terminate_state: req.terminate_state,
                shutdown_cycle: None,
            },
            read_record: req.read_record,
            write_record: req.write_record,
            user_cycles: req.user_cycles,
            suspend_cycle: req.phys_cycles,
            paging_cycles: req.pager_cycles,
            po2: req.po2,
            index: segment_counter,
            segment_threshold: req.segment_threshold,
        })?;
        segment_counter += 1;
    }
    Ok(segment_counter)
}

impl<'a, 'b, S: Syscall> Executor<'a, 'b, S> {
    pub fn new(
        image: MemoryImage2,
        syscall_handler: &'a S,
        input_digest: Option<Digest>,
        trace: Vec<Rc<RefCell<dyn TraceCallback + 'b>>>,
    ) -> Self {
        Self {
            pc: ByteAddr(0),
            user_pc: ByteAddr(0),
            machine_mode: 0,
            user_cycles: 0,
            phys_cycles: 0,
            pager: PagedMemory::new(image, !trace.is_empty() /* tracing_enabled */),
            terminate_state: None,
            read_record: Vec::new(),
            write_record: Vec::new(),
            syscall_handler,
            input_digest: input_digest.unwrap_or_default(),
            output_digest: None,
            trace,
            cycles: SessionCycles::default(),
        }
    }

    pub fn run(
        &mut self,
        segment_po2: usize,
        max_insn_cycles: usize,
        max_cycles: Option<u64>,
        callback: impl FnMut(Segment) -> Result<()> + Send,
    ) -> Result<ExecutorResult> {
        let segment_limit: u32 = 1 << segment_po2;
        assert!(max_insn_cycles < segment_limit as usize);
        let segment_threshold = segment_limit - max_insn_cycles as u32;

        self.reset();

        let mut emu = Emulator::new();
        Risc0Machine::resume(self)?;
        let initial_digest = self.pager.image.image_id();
        tracing::debug!("initial_digest: {initial_digest}");

        let (commit_sender, commit_recv) =
            std::sync::mpsc::sync_channel(MAX_OUTSTANDING_SEGMENTS - 1);

        let (post_digest, total_num_segments) = std::thread::scope(|scope| {
            let partial_images_thread =
                scope.spawn(move || compute_partial_images(commit_recv, callback));

            while self.terminate_state.is_none() {
                if let Some(max_cycles) = max_cycles {
                    if self.cycles.user >= max_cycles {
                        bail!(
                            "Session limit exceeded: {} >= {max_cycles}",
                            self.cycles.user
                        );
                    }
                }

                if self.segment_cycles() >= segment_threshold {
                    tracing::debug!(
                        "split(phys: {} + pager: {} + reserved: {LOOKUP_TABLE_CYCLES}) = {} >= {segment_threshold}",
                        self.phys_cycles,
                        self.pager.cycles,
                        self.segment_cycles()
                    );

                    assert!(
                        self.segment_cycles() < segment_limit,
                        "segment limit ({segment_limit}) too small for instruction at pc: {:?}",
                        self.pc
                    );
                    Risc0Machine::suspend(self)?;

                    let (pre_image, pre_digest, post_digest) = self.pager.commit();

                    let req = ComputePartialImageRequest {
                        image: pre_image,
                        page_indexes: self.pager.page_indexes(),
                        input_digest: self.input_digest,
                        output_digest: self.output_digest,
                        read_record: std::mem::take(&mut self.read_record),
                        write_record: std::mem::take(&mut self.write_record),
                        user_cycles: self.user_cycles,
                        phys_cycles: self.phys_cycles,
                        pager_cycles: self.pager.cycles,
                        terminate_state: self.terminate_state,
                        segment_threshold,
                        pre_digest,
                        post_digest,
                        po2: segment_po2 as u32,
                    };
                    if commit_sender.send(req).is_err() {
                        return Err(partial_images_thread.join().unwrap().unwrap_err());
                    }

                    let total_cycles = 1 << segment_po2;
                    let pager_cycles = self.pager.cycles as u64;
                    let user_cycles = self.user_cycles as u64;
                    self.cycles.total += total_cycles;
                    self.cycles.paging += pager_cycles;
                    self.cycles.reserved += total_cycles - pager_cycles - user_cycles;
                    self.user_cycles = 0;
                    self.phys_cycles = 0;
                    self.pager.reset();

                    Risc0Machine::resume(self)?;
                }

                Risc0Machine::step(&mut emu, self)?;
            }

            Risc0Machine::suspend(self)?;

            let final_cycles = self.segment_cycles().next_power_of_two();
            let final_po2 = log2_ceil(final_cycles as usize);
            let segment_threshold = (1 << final_po2) - max_insn_cycles as u32;
            let (pre_image, pre_digest, post_digest) = self.pager.commit();
            let req = ComputePartialImageRequest {
                image: pre_image,
                page_indexes: self.pager.page_indexes(),
                input_digest: self.input_digest,
                output_digest: self.output_digest,
                read_record: std::mem::take(&mut self.read_record),
                write_record: std::mem::take(&mut self.write_record),
                user_cycles: self.user_cycles,
                phys_cycles: self.phys_cycles,
                pager_cycles: self.pager.cycles,
                terminate_state: self.terminate_state,
                segment_threshold,
                pre_digest,
                post_digest,
                po2: final_po2 as u32,
            };
            if commit_sender.send(req).is_err() {
                return Err(partial_images_thread.join().unwrap().unwrap_err());
            }

            let final_cycles = final_cycles as u64;
            let user_cycles = self.user_cycles as u64;
            let pager_cycles = self.pager.cycles as u64;
            self.cycles.total += final_cycles;
            self.cycles.paging += pager_cycles;
            self.cycles.reserved += final_cycles - pager_cycles - user_cycles;

            drop(commit_sender);
            Ok((post_digest, partial_images_thread.join().unwrap()?))
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
            segments: total_num_segments,
            post_image: self.pager.image.clone(),
            user_cycles: self.cycles.user,
            total_cycles: self.cycles.total,
            paging_cycles: self.cycles.paging,
            reserved_cycles: self.cycles.reserved,
            claim: session_claim,
        })
    }

    fn reset(&mut self) {
        self.pager.reset();
        self.terminate_state = None;
        self.read_record.clear();
        self.write_record.clear();
        self.output_digest = None;
        self.machine_mode = 0;
        self.user_cycles = 0;
        self.phys_cycles = 0;
        self.cycles = SessionCycles::default();
        self.pc = ByteAddr(0);
    }

    fn segment_cycles(&self) -> u32 {
        self.phys_cycles + self.pager.cycles + LOOKUP_TABLE_CYCLES as u32
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

    #[cold]
    fn trace_instruction(&self, cycle: u64, insn: &Instruction, decoded: &DecodedInstruction) {
        tracing::trace!(
            "[{}:{}:{cycle}] {:?}> {:#010x}  {}",
            self.user_cycles + 1,
            self.segment_cycles() + 1,
            self.pc,
            decoded.insn,
            disasm(insn, decoded)
        );
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

    fn on_insn_start(&mut self, insn: &Instruction, decoded: &DecodedInstruction) -> Result<()> {
        let cycle = self.cycles.user;
        self.cycles.user += 1;
        if tracing::enabled!(tracing::Level::TRACE) {
            self.trace_instruction(cycle, insn, decoded);
        }
        if !self.trace.is_empty() {
            self.trace(TraceEvent::InstructionStart {
                cycle,
                pc: self.pc.0,
                insn: decoded.insn,
            })
        } else {
            Ok(())
        }
    }

    fn on_insn_end(&mut self, _insn: &Instruction, _decoded: &DecodedInstruction) -> Result<()> {
        self.user_cycles += 1;
        self.phys_cycles += 1;
        if !self.trace.is_empty() {
            self.trace_pager()?;
        }
        Ok(())
    }

    fn on_ecall_cycle(
        &mut self,
        _cur: CycleState,
        _next: CycleState,
        _s0: u32,
        _s1: u32,
        _s2: u32,
    ) -> Result<()> {
        self.phys_cycles += 1;
        if !self.trace.is_empty() {
            self.trace_pager()?;
        }
        Ok(())
    }

    fn load_u32(&mut self, op: LoadOp, addr: WordAddr) -> Result<u32> {
        let word = match op {
            LoadOp::Peek => self.pager.peek(addr)?,
            LoadOp::Load | LoadOp::Record => self.pager.load(addr)?,
        };
        // tracing::trace!("load_mem({:?}) -> {word:#010x}", addr.baddr());
        Ok(word)
    }

    fn load_register(&mut self, _op: LoadOp, base: WordAddr, idx: usize) -> Result<u32> {
        let word = self.pager.load_register(base, idx);
        // tracing::trace!("load_register({:?}) -> {word:#010x}", addr.baddr());
        Ok(word)
    }

    fn store_u32(&mut self, addr: WordAddr, word: u32) -> Result<()> {
        // tracing::trace!("store_mem({:?}, {word:#010x})", addr.baddr());
        if !self.trace.is_empty() {
            self.trace(TraceEvent::MemorySet {
                addr: addr.baddr().0,
                region: word.to_be_bytes().to_vec(),
            })?;
        }
        self.pager.store(addr, word)
    }

    fn store_register(&mut self, base: WordAddr, idx: usize, word: u32) -> Result<()> {
        // tracing::trace!("store_mem({:?}, {word:#010x})", addr.baddr());
        if !self.trace.is_empty() {
            self.trace(TraceEvent::MemorySet {
                addr: (base + idx).baddr().0,
                region: word.to_be_bytes().to_vec(),
            })?;
        }
        self.pager.store_register(base, idx, word);
        Ok(())
    }

    fn on_terminate(&mut self, a0: u32, a1: u32) -> Result<()> {
        self.user_cycles += 1;

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
        self.phys_cycles += 1;
    }

    fn on_poseidon2_cycle(&mut self, _cur_state: CycleState, _p2: &Poseidon2State) {
        self.phys_cycles += 1;
    }

    fn on_bigint_cycle(&mut self, _cur_state: CycleState, _bigint: &BigIntState) {
        self.phys_cycles += 1;
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

    fn peek_page(&mut self, page_idx: u32) -> Result<Vec<u8>> {
        self.pager.peek_page(page_idx)
    }

    fn get_cycle(&self) -> u64 {
        self.cycles.user
    }

    fn get_pc(&self) -> u32 {
        self.user_pc.0
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
