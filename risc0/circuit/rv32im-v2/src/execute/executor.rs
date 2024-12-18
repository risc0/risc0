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

use std::{cell::RefCell, rc::Rc};

use anyhow::{bail, Result};
use risc0_binfmt::ExitCode;
use risc0_zkp::core::{digest::Digest, log2_ceil};

use super::{
    addr::{ByteAddr, WordAddr},
    image::MemoryImage2,
    pager::PagedMemory,
    platform::{CycleState, LOOKUP_TABLE_CYCLES},
    r0vm::{Risc0Context, Risc0Machine},
    rv32im::{disasm, DecodedInstruction, Emulator, Instruction},
    segment::Segment,
    syscall::Syscall,
    trace::{TraceCallback, TraceEvent},
};

pub struct Executor<'a, 'b, S: Syscall> {
    pc: ByteAddr,
    machine_mode: u32,
    user_cycles: u32,
    phys_cycles: u32,
    pager: PagedMemory,
    exit_code: Option<ExitCode>,
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
    pub exit_code: ExitCode,
    pub post_image: MemoryImage2,
    pub user_cycles: u64,
    pub total_cycles: u64,
    pub pre_digest: Digest,
    pub post_digest: Digest,
    pub output_digest: Option<Digest>,
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
            machine_mode: 0,
            user_cycles: 0,
            phys_cycles: 0,
            pager: PagedMemory::new(image),
            exit_code: None,
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
        max_cycles: Option<u64>,
        mut callback: F,
    ) -> Result<ExecutorResult> {
        let segment_limit = 1 << segment_po2;
        let mut segment_counter = 0u64;

        self.reset();

        let mut emu = Emulator::new();
        Risc0Machine::resume(self)?;
        let initial_digest = *self.pager.image.image_id();

        while self.exit_code.is_none() {
            if let Some(max_cycles) = max_cycles {
                if self.cycles.user >= max_cycles {
                    bail!("Session limit exceeded");
                }
            }

            if self.segment_cycles() >= segment_limit {
                Risc0Machine::suspend(self)?;

                let (pre_digest, partial_image, post_digest) = self.pager.commit()?;
                callback(Segment {
                    partial_image,
                    pre_digest,
                    post_digest,
                    read_record: std::mem::take(&mut self.read_record),
                    write_record: std::mem::take(&mut self.write_record),
                    user_cycles: self.user_cycles,
                    suspend_cycle: self.phys_cycles,
                    paging_cycles: self.pager.cycles,
                    po2: segment_po2 as u32,
                    exit_code: ExitCode::SystemSplit,
                    index: segment_counter,
                    input_digest: self.input_digest,
                    output_digest: self.output_digest,
                    segment_threshold: 4000,
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
        let last_po2 = log2_ceil(self.segment_cycles().next_power_of_two() as usize);
        let exit_code = self.exit_code.unwrap();

        callback(Segment {
            partial_image,
            pre_digest,
            post_digest,
            read_record: std::mem::take(&mut self.read_record),
            write_record: std::mem::take(&mut self.write_record),
            user_cycles: self.user_cycles,
            suspend_cycle: self.phys_cycles,
            paging_cycles: self.pager.cycles,
            po2: last_po2 as u32,
            exit_code,
            index: segment_counter,
            input_digest: self.input_digest,
            output_digest: self.output_digest,
            segment_threshold: 4000,
        })?;

        self.cycles.total += 1 << last_po2;

        Ok(ExecutorResult {
            segments: segment_counter + 1,
            exit_code,
            post_image: self.pager.image.clone(),
            user_cycles: self.cycles.user,
            total_cycles: self.cycles.total,
            pre_digest: initial_digest,
            post_digest,
            output_digest: self.output_digest,
        })
    }

    fn reset(&mut self) {
        self.pager.reset();
        self.exit_code = None;
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

    fn on_terminate(&mut self, a0: u32, _a1: u32) {
        self.user_cycles += 1;
        self.exit_code = Some(ExitCode::Halted(a0));
    }

    fn host_read(&mut self, fd: u32, buf: &mut [u8]) -> Result<u32> {
        let rlen = self.syscall_handler.host_read(fd, buf)?;
        let slice = &buf[..rlen as usize];
        self.read_record.push(slice.to_vec());
        Ok(rlen)
    }

    fn host_write(&mut self, fd: u32, buf: &[u8]) -> Result<u32> {
        let rlen = self.syscall_handler.host_write(fd, buf)?;
        self.write_record.push(rlen);
        Ok(rlen)
    }
}
