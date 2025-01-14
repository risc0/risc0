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

use std::{cell::RefCell, rc::Rc};

use anyhow::{bail, Result};
use risc0_binfmt::{ByteAddr, MemoryImage2, WordAddr};
use risc0_zkp::core::{
    digest::{Digest, DIGEST_BYTES},
    log2_ceil,
};

use crate::{Rv32imV2Claim, TerminateState};

use super::{
    pager::PagedMemory,
    platform::*,
    poseidon2::Poseidon2State,
    r0vm::{Risc0Context, Risc0Machine},
    rv32im::{disasm, DecodedInstruction, Emulator, Instruction},
    segment::Segment,
    sha2::Sha2State,
    syscall::Syscall,
    trace::{TraceCallback, TraceEvent},
    SyscallContext,
};

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
    user: u64,
    total: u64,
}

pub struct SimpleSession {
    pub segments: Vec<Segment>,
    pub result: ExecutorResult,
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
            pager: PagedMemory::new(image),
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

    pub fn run<F: FnMut(Segment) -> Result<()>>(
        &mut self,
        segment_po2: usize,
        max_insn_cycles: usize,
        max_cycles: Option<u64>,
        mut callback: F,
    ) -> Result<ExecutorResult> {
        let segment_limit: u32 = 1 << segment_po2;
        assert!(max_insn_cycles < segment_limit as usize);
        let segment_threshold = segment_limit - max_insn_cycles as u32;
        let mut segment_counter = 0;

        self.reset();

        let mut emu = Emulator::new();
        Risc0Machine::resume(self)?;
        let initial_digest = self.pager.image.image_id();
        tracing::debug!("initial_digest: {initial_digest}");

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

                assert!(self.segment_cycles() < segment_limit);
                Risc0Machine::suspend(self)?;

                let (pre_digest, partial_image, post_digest) = self.pager.commit()?;
                callback(Segment {
                    partial_image,
                    claim: Rv32imV2Claim {
                        pre_state: pre_digest,
                        post_state: post_digest,
                        input: self.input_digest,
                        output: self.output_digest,
                        terminate_state: self.terminate_state,
                        shutdown_cycle: None,
                    },
                    read_record: std::mem::take(&mut self.read_record),
                    write_record: std::mem::take(&mut self.write_record),
                    user_cycles: self.user_cycles,
                    suspend_cycle: self.phys_cycles,
                    paging_cycles: self.pager.cycles,
                    po2: segment_po2 as u32,
                    index: segment_counter,
                    segment_threshold,
                })?;

                segment_counter += 1;
                self.cycles.total += 1 << segment_po2;
                self.user_cycles = 0;
                self.phys_cycles = 0;
                self.pager.reset();

                Risc0Machine::resume(self)?;
            }

            Risc0Machine::step(&mut emu, self)?;
        }

        Risc0Machine::suspend(self)?;

        let (pre_digest, partial_image, post_digest) = self.pager.commit()?;
        let last_cycles = self.segment_cycles().next_power_of_two();
        let last_po2 = log2_ceil(last_cycles as usize);

        let final_claim = Rv32imV2Claim {
            pre_state: pre_digest,
            post_state: post_digest,
            input: self.input_digest,
            output: self.output_digest,
            terminate_state: self.terminate_state,
            shutdown_cycle: None,
        };

        callback(Segment {
            partial_image,
            claim: final_claim,
            read_record: std::mem::take(&mut self.read_record),
            write_record: std::mem::take(&mut self.write_record),
            user_cycles: self.user_cycles,
            suspend_cycle: self.phys_cycles,
            paging_cycles: self.pager.cycles,
            po2: last_po2 as u32,
            index: segment_counter,
            segment_threshold,
        })?;

        self.cycles.total += 1 << last_po2;

        let session_claim = Rv32imV2Claim {
            pre_state: initial_digest,
            post_state: post_digest,
            input: self.input_digest,
            output: self.output_digest,
            terminate_state: self.terminate_state,
            shutdown_cycle: None,
        };

        Ok(ExecutorResult {
            segments: segment_counter + 1,
            post_image: self.pager.image.clone(),
            user_cycles: self.cycles.user,
            total_cycles: self.cycles.total,
            paging_cycles: 0,   // TODO(flaub)
            reserved_cycles: 0, // TODO(flaub)
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
        self.cycles.user = 0;
        self.cycles.total = 0;
        self.pc = ByteAddr(0);
    }

    fn segment_cycles(&self) -> u32 {
        self.phys_cycles + self.pager.cycles + LOOKUP_TABLE_CYCLES as u32
    }

    fn trace(&mut self, event: TraceEvent) -> Result<()> {
        for trace in self.trace.iter() {
            trace.borrow_mut().trace_callback(event.clone())?;
        }
        Ok(())
    }
}

impl<'a, 'b, S: Syscall> Risc0Context for Executor<'a, 'b, S> {
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

    fn on_insn_start(&mut self, insn: &Instruction, decoded: &DecodedInstruction) -> Result<()> {
        let cycle = self.cycles.user;
        self.cycles.user += 1;
        tracing::trace!(
            "[{}:{}:{cycle}] {:?}> {:#010x}  {}",
            self.user_cycles + 1,
            self.segment_cycles() + 1,
            self.pc,
            decoded.insn,
            disasm(insn, decoded)
        );
        self.trace(TraceEvent::InstructionStart {
            cycle,
            pc: self.pc.0,
            insn: decoded.insn,
        })
    }

    fn on_insn_end(&mut self, _insn: &Instruction, _decoded: &DecodedInstruction) -> Result<()> {
        self.user_cycles += 1;
        self.phys_cycles += 1;
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
        Ok(())
    }

    fn peek_u32(&mut self, addr: WordAddr) -> Result<u32> {
        self.pager.peek(addr)
    }

    fn load_u32(&mut self, addr: WordAddr) -> Result<u32> {
        let word = self.pager.load(addr)?;
        // tracing::trace!("load_mem({:?}) -> {word:#010x}", addr.baddr());
        Ok(word)
    }

    fn store_u32(&mut self, addr: WordAddr, word: u32) -> Result<()> {
        // tracing::trace!("store_mem({:?}, {word:#010x})", addr.baddr());
        self.trace(TraceEvent::MemorySet {
            addr: addr.baddr().0,
            region: word.to_be_bytes().to_vec(),
        })?;
        self.pager.store(addr, word)
    }

    fn on_terminate(&mut self, a0: u32, a1: u32) -> Result<()> {
        self.user_cycles += 1;

        self.terminate_state = Some(TerminateState {
            a0: a0.into(),
            a1: a1.into(),
        });
        tracing::debug!("{:?}", self.terminate_state);

        let output: Digest = self
            .peek_region(GLOBAL_OUTPUT_ADDR, DIGEST_BYTES)?
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

    fn on_poseidon2_cycle(&mut self, cur_state: CycleState, _p2: &Poseidon2State) {
        tracing::trace!("on_poseidon2_cycle: {cur_state:?}");
        self.phys_cycles += 1;
    }
}

impl<'a, 'b, S: Syscall> SyscallContext for Executor<'a, 'b, S> {
    fn peek_register(&mut self, idx: usize) -> Result<u32> {
        if idx >= REG_MAX {
            bail!("invalid register: x{idx}");
        }
        Risc0Context::peek_u32(self, USER_REGS_ADDR.waddr() + idx)
    }

    fn peek_u32(&mut self, addr: ByteAddr) -> Result<u32> {
        // let addr = Self::check_guest_addr(addr)?;
        Risc0Context::peek_u32(self, addr.waddr())
    }

    fn peek_u8(&mut self, addr: ByteAddr) -> Result<u8> {
        // let addr = Self::check_guest_addr(addr)?;
        let word = Risc0Context::peek_u32(self, addr.waddr())?;
        let bytes = word.to_le_bytes();
        Ok(bytes[addr.subaddr() as usize])
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
