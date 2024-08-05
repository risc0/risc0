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

#[cfg(test)]
mod tests;

use std::{array, cell::RefCell, collections::BTreeSet, mem, rc::Rc};

use anyhow::{bail, ensure, Result};
use crypto_bigint::{CheckedMul as _, Encoding as _, NonZero, U256, U512};
use risc0_binfmt::{ExitCode, MemoryImage, Program, SystemState};
use risc0_zkp::{
    core::{
        digest::{Digest, DIGEST_BYTES, DIGEST_WORDS},
        hash::sha::{BLOCK_BYTES, BLOCK_WORDS},
        log2_ceil,
    },
    MAX_CYCLES_PO2, MIN_CYCLES_PO2, ZK_CYCLES,
};
use risc0_zkvm_platform::{
    align_up,
    memory::{is_guest_memory, GUEST_MAX_MEM},
    syscall::{
        bigint, ecall, halt,
        reg_abi::{REG_A0, REG_A1, REG_A2, REG_A3, REG_A4, REG_MAX, REG_T0},
        IO_CHUNK_WORDS,
    },
    PAGE_SIZE, WORD_SIZE,
};
use sha2::digest::generic_array::GenericArray;

use super::{
    addr::{ByteAddr, WordAddr},
    pager::PagedMemory,
    rv32im::{DecodedInstruction, EmuContext, Emulator, Instruction, TrapCause},
    BIGINT_CYCLES, SYSTEM_START,
};
use crate::{
    prove::{
        emu::sha_cycles,
        engine::loader::{FINI_CYCLES, INIT_CYCLES},
        segment::{Segment, SyscallRecord},
    },
    trace::{TraceCallback, TraceEvent},
};

pub const DEFAULT_SEGMENT_LIMIT_PO2: usize = 20;

/// A host-side implementation of a system call.
pub trait Syscall {
    /// Invokes the system call.
    fn syscall(
        &self,
        syscall: &str,
        ctx: &mut dyn SyscallContext,
        into_guest: &mut [u32],
    ) -> Result<(u32, u32)>;
}

/// Access to memory and machine state for syscalls.
pub trait SyscallContext {
    /// Loads the value of the given register, e.g. REG_A0.
    fn peek_register(&mut self, idx: usize) -> Result<u32>;

    /// Loads an individual word from memory.
    fn peek_u32(&mut self, addr: ByteAddr) -> Result<u32>;

    /// Loads an individual byte from memory.
    fn peek_u8(&mut self, addr: ByteAddr) -> Result<u8>;

    /// Loads bytes from the given region of memory.
    ///
    /// A region may span multiple pages.
    fn peek_region(&mut self, addr: ByteAddr, size: u32) -> Result<Vec<u8>> {
        let mut region = Vec::new();
        for i in 0..size {
            region.push(self.peek_u8(addr + i)?);
        }
        Ok(region)
    }

    /// Load a page from memory at the specified page index.
    ///
    /// This is used by sys_fork in order to build a copy-on-write page cache to
    /// inherit pages from the parent process.
    fn peek_page(&mut self, page_idx: u32) -> Result<Vec<u8>>;

    /// Returns the current cycle count.
    fn get_cycle(&self) -> u64;

    /// Returns the current program counter.
    fn get_pc(&self) -> u32;
}

pub struct ExecutorResult {
    pub segments: usize,
    pub exit_code: ExitCode,
    pub post_image: MemoryImage,
    pub user_cycles: u64,
    pub total_cycles: u64,
    pub pre_state: SystemState,
    pub post_state: SystemState,
    pub output_digest: Option<Digest>,
}

#[derive(Default)]
struct SessionCycles {
    user: usize,
    total: usize,
}

pub struct SimpleSession {
    pub segments: Vec<Segment>,
    pub result: ExecutorResult,
}

#[derive(Debug)]
struct PendingState {
    pc: ByteAddr,
    insn: u32,
    cycles: usize,
    syscall: Option<SyscallRecord>,
    output_digest: Option<Digest>,
    exit_code: Option<ExitCode>,
    events: BTreeSet<TraceEvent>,
}

pub struct Executor<'a, 'b, S: Syscall> {
    pc: ByteAddr,
    insn_cycles: usize,
    pager: PagedMemory,
    exit_code: Option<ExitCode>,
    syscalls: Vec<SyscallRecord>,
    syscall_handler: &'a S,
    input_digest: Digest,
    output_digest: Option<Digest>,
    pending: PendingState,
    trace: Vec<Rc<RefCell<dyn TraceCallback + 'b>>>,
    cycles: SessionCycles,
}

impl PendingState {
    fn reset(&mut self, pc: ByteAddr) {
        self.pc = pc;
        self.cycles = 0;
        self.syscall = None;
        self.output_digest = None;
        self.exit_code = None;
    }
}

impl<'a, 'b, S: Syscall> Executor<'a, 'b, S> {
    pub fn new(
        image: MemoryImage,
        syscall_handler: &'a S,
        input_digest: Option<Digest>,
        trace: Vec<Rc<RefCell<dyn TraceCallback + 'b>>>,
    ) -> Self {
        let pc = ByteAddr(image.pc);
        Self {
            pc,
            insn_cycles: 0,
            pager: PagedMemory::new(image),
            exit_code: None,
            syscalls: Vec::new(),
            syscall_handler,
            input_digest: input_digest.unwrap_or_default(),
            output_digest: None,
            pending: PendingState {
                pc,
                insn: 0,
                cycles: 0,
                syscall: None,
                output_digest: None,
                exit_code: None,
                events: BTreeSet::new(),
            },
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
        // at least one HaltCycle needs to appear in the body
        const MIN_HALT_CYCLES: usize = 1;
        // a final "is_done" PageFault cycle is required when a split occurs
        const PAGE_FINI_CYCLES: usize = 1;
        // leave room for reserved cycles
        const RESERVED_CYCLES: usize =
            INIT_CYCLES + MIN_HALT_CYCLES + PAGE_FINI_CYCLES + FINI_CYCLES + ZK_CYCLES;
        let segment_limit = (1 << segment_po2) - RESERVED_CYCLES;

        self.reset();

        let mut emu = Emulator::new();
        let mut segments = 0;
        let initial_state = self.pager.image.get_system_state();

        loop {
            if self.exit_code.is_some() {
                break;
            }

            if let Some(max_cycles) = max_cycles {
                if self.cycles.user >= max_cycles as usize {
                    bail!("Session limit exceeded");
                }
            }

            emu.step(self)?;

            let segment_cycles = self.insn_cycles + self.pager.cycles + self.pending.cycles;
            if segment_cycles < segment_limit {
                self.advance()?;
            } else if self.insn_cycles == 0 {
                bail!(
                    "segment limit ({segment_limit}) too small for instruction at pc: {:?}",
                    self.pc
                );
            } else {
                self.pager.undo();
                let used_cycles = self.insn_cycles + self.pager.cycles + RESERVED_CYCLES;
                let waste = (1 << segment_po2) - used_cycles;
                tracing::debug!(
                    "split: {} + {} + {RESERVED_CYCLES} = {used_cycles}, waste: {waste}, pending: {:?}",
                    self.insn_cycles,
                    self.pager.cycles,
                    self.pending
                );

                // split
                let (pre_state, partial_image, post_state) = self.pager.commit(self.pc);
                callback(Segment {
                    partial_image,
                    pre_state,
                    post_state,
                    syscalls: mem::take(&mut self.syscalls),
                    insn_cycles: self.insn_cycles,
                    po2: segment_po2,
                    exit_code: ExitCode::SystemSplit,
                    index: segments,
                    input_digest: self.input_digest,
                    output_digest: self.output_digest,
                })?;
                segments += 1;
                self.cycles.total += 1 << segment_po2;
                self.pager.clear();
                self.insn_cycles = 0;

                // replay the current instruction in a new segment
                self.pending.pc = self.pc;
                self.pending.cycles = 0;
            }
        }

        let (pre_state, partial_image, post_state) = self.pager.commit(self.pc);
        let segment_cycles = self.insn_cycles + self.pager.cycles + RESERVED_CYCLES;
        let po2 = log2_ceil(segment_cycles.next_power_of_two());
        let exit_code = self.exit_code.unwrap();

        callback(Segment {
            partial_image,
            pre_state: pre_state.clone(),
            post_state: post_state.clone(),
            syscalls: mem::take(&mut self.syscalls),
            insn_cycles: self.insn_cycles,
            po2,
            exit_code,
            index: segments,
            input_digest: self.input_digest,
            output_digest: self.output_digest,
        })?;
        segments += 1;
        self.cycles.total += 1 << po2;

        // NOTE: When a segment ends in a Halted(_) state, the post_state will be null.
        let post_state = match exit_code {
            ExitCode::Halted(_) => SystemState {
                pc: 0,
                merkle_root: Digest::ZERO,
            },
            _ => post_state,
        };

        Ok(ExecutorResult {
            segments,
            exit_code,
            post_image: self.pager.image.clone(),
            user_cycles: self.cycles.user.try_into()?,
            total_cycles: self.cycles.total.try_into()?,
            pre_state: initial_state,
            post_state,
            output_digest: self.output_digest,
        })
    }

    fn advance(&mut self) -> Result<()> {
        for trace in &self.trace {
            trace
                .borrow_mut()
                .trace_callback(TraceEvent::InstructionStart {
                    cycle: self.cycles.user.try_into()?,
                    pc: self.pc.0,
                    insn: self.pending.insn,
                })?;

            for event in &self.pending.events {
                trace.borrow_mut().trace_callback(event.clone()).unwrap();
            }
        }

        self.pc = self.pending.pc;
        self.insn_cycles += self.pending.cycles;
        self.cycles.user += self.pending.cycles;
        self.pending.cycles = 0;
        self.pending.events.clear();
        if let Some(syscall) = self.pending.syscall.take() {
            self.syscalls.push(syscall);
        }
        self.output_digest = self.pending.output_digest.take();
        self.exit_code = self.pending.exit_code.take();
        self.pager.commit_step();

        Ok(())
    }

    fn reset(&mut self) {
        self.pager.clear();
        self.exit_code = None;
        self.syscalls.clear();
        self.output_digest = None;
        self.pending.reset(self.pc);
        self.cycles.user = 0;
        self.cycles.total = 0;
    }
}

impl<'a, 'b, S: Syscall> Executor<'a, 'b, S> {
    fn ecall_halt(&mut self) -> Result<bool> {
        let a0 = self.load_register(REG_A0)?;
        let output_ptr = self.load_guest_addr_from_register(REG_A1)?;
        let output: [u8; DIGEST_BYTES] = self.load_array_from_guest(output_ptr)?;

        let halt_type = a0 & 0xff;
        let user_exit = (a0 >> 8) & 0xff;

        tracing::debug!("ecall_halt({halt_type}, {user_exit})");

        self.pending.exit_code = match halt_type {
            halt::TERMINATE => Some(ExitCode::Halted(user_exit)),
            halt::PAUSE => Some(ExitCode::Paused(user_exit)),
            _ => bail!("Illegal halt type: {halt_type}"),
        };
        self.pending.output_digest = Some(output.into());
        self.pending.pc = self.pc + WORD_SIZE;

        Ok(true)
    }

    fn ecall_input(&mut self) -> Result<bool> {
        tracing::debug!("[{}] ecall_input", self.insn_cycles);
        let a0 = self.load_register(REG_A0)? as usize;
        ensure!(a0 < DIGEST_WORDS, "sys_input index out of range");
        let word = self.input_digest.as_words()[a0];
        self.store_register(REG_A0, word)?;

        self.pending.cycles += 1;
        self.pending.pc = self.pc + WORD_SIZE;

        Ok(true)
    }

    fn ecall_software(&mut self) -> Result<bool> {
        tracing::debug!("[{}] ecall_software", self.insn_cycles);
        let into_guest_ptr = ByteAddr(self.load_register(REG_A0)?);
        let into_guest_len = self.load_register(REG_A1)? as usize;
        if into_guest_len > 0 && !is_guest_memory(into_guest_ptr.0) {
            bail!("{into_guest_ptr:?} is an invalid guest address");
        }
        let name_ptr = self.load_guest_addr_from_register(REG_A2)?;
        let syscall_name = self.peek_string(name_ptr)?;
        let name_end = name_ptr + syscall_name.len();
        Self::check_guest_addr(name_end)?;
        tracing::trace!("ecall_software({syscall_name}, into_guest: {into_guest_len})");

        let chunks = align_up(into_guest_len, IO_CHUNK_WORDS) / IO_CHUNK_WORDS;

        let syscall = if let Some(syscall) = &self.pending.syscall {
            tracing::debug!("Replay syscall: {syscall:?}");
            syscall.clone()
        } else {
            let mut to_guest = vec![0u32; into_guest_len];

            let (a0, a1) = self
                .syscall_handler
                .syscall(&syscall_name, self, &mut to_guest)?;

            let syscall = SyscallRecord {
                to_guest,
                regs: (a0, a1),
            };
            self.pending.syscall = Some(syscall.clone());
            syscall
        };

        // The guest uses a null pointer to indicate that a transfer from host
        // to guest is not needed.
        if into_guest_len > 0 && !into_guest_ptr.is_null() {
            Self::check_guest_addr(into_guest_ptr + into_guest_len)?;
            self.store_region(into_guest_ptr, bytemuck::cast_slice(&syscall.to_guest))?
        }

        let (a0, a1) = syscall.regs;
        self.store_register(REG_A0, a0)?;
        self.store_register(REG_A1, a1)?;

        tracing::trace!("{syscall:08x?}");

        self.pending.cycles += chunks + 1; // syscallBody + syscallFini
        self.pending.pc = self.pc + WORD_SIZE;

        Ok(true)
    }

    fn ecall_sha(&mut self) -> Result<bool> {
        tracing::debug!("[{}] ecall_sha", self.insn_cycles);
        let state_out_ptr = self.load_guest_addr_from_register(REG_A0)?;
        let state_in_ptr = self.load_guest_addr_from_register(REG_A1)?;
        let count = self.load_register(REG_A4)?;

        let state_in: [u8; DIGEST_BYTES] = self.load_array_from_guest(state_in_ptr)?;
        let mut state: [u32; DIGEST_WORDS] = bytemuck::cast_slice(&state_in).try_into().unwrap();
        for word in &mut state {
            *word = word.to_be();
        }

        if count > 0 {
            let mut block1_ptr = self.load_guest_addr_from_register(REG_A2)?;
            let mut block2_ptr = self.load_guest_addr_from_register(REG_A3)?;

            // tracing::debug!("ecall_sha: start state: {state:08x?}");
            let mut block = [0u32; BLOCK_WORDS];

            for _ in 0..count {
                let (digest1, digest2) = block.split_at_mut(DIGEST_WORDS);
                for (i, word) in digest1.iter_mut().enumerate() {
                    *word = self.load_u32_from_guest(block1_ptr + (i * WORD_SIZE))?;
                }
                for (i, word) in digest2.iter_mut().enumerate() {
                    *word = self.load_u32_from_guest(block2_ptr + (i * WORD_SIZE))?;
                }
                // tracing::debug!("Compressing block {block:02x?}");
                sha2::compress256(
                    &mut state,
                    &[*GenericArray::from_slice(bytemuck::cast_slice(&block))],
                );

                block1_ptr += BLOCK_BYTES;
                block2_ptr += BLOCK_BYTES;
            }
        }

        // tracing::debug!("ecall_sha: final state: {state:08x?}");
        for word in &mut state {
            *word = u32::from_be(*word);
        }

        self.store_region_into_guest(state_out_ptr, bytemuck::cast_slice(&state))?;

        self.pending.cycles += sha_cycles(count as usize);
        self.pending.pc = self.pc + WORD_SIZE;

        Ok(true)
    }

    fn ecall_bigint(&mut self) -> Result<bool> {
        let op = self.load_register(REG_A1)?;
        let z_ptr = self.load_guest_addr_from_register(REG_A0)?;
        let x_ptr = self.load_guest_addr_from_register(REG_A2)?;
        let y_ptr = self.load_guest_addr_from_register(REG_A3)?;
        let n_ptr = self.load_guest_addr_from_register(REG_A4)?;

        let mut load_bigint_le_bytes = |ptr: ByteAddr| -> Result<[u8; bigint::WIDTH_BYTES]> {
            let mut arr = [0u32; bigint::WIDTH_WORDS];
            for (i, word) in arr.iter_mut().enumerate() {
                *word = self
                    .load_u32_from_guest(ptr + (i * WORD_SIZE) as u32)?
                    .to_le();
            }
            Ok(bytemuck::cast(arr))
        };

        if op != 0 {
            bail!("ecall_bigint: op must be set to 0");
        }

        // Load inputs.
        let x = U256::from_le_bytes(load_bigint_le_bytes(x_ptr)?);
        let y = U256::from_le_bytes(load_bigint_le_bytes(y_ptr)?);
        let n = U256::from_le_bytes(load_bigint_le_bytes(n_ptr)?);

        // Compute modular multiplication, or simply multiplication if n == 0.
        let z: U256 = if n == U256::ZERO {
            x.checked_mul(&y).unwrap()
        } else {
            let (w_lo, w_hi) = x.mul_wide(&y);
            let w = w_hi.concat(&w_lo);
            let z = w.rem(&NonZero::<U512>::from_uint(n.resize()));
            z.resize()
        };

        // Store result.
        for (i, word) in bytemuck::cast::<_, [u32; bigint::WIDTH_WORDS]>(z.to_le_bytes())
            .into_iter()
            .enumerate()
        {
            self.store_u32_into_guest(z_ptr + (i * WORD_SIZE) as u32, word.to_le())?;
        }

        self.pending.cycles += BIGINT_CYCLES;
        self.pending.pc = self.pc + WORD_SIZE;

        Ok(true)
    }

    fn check_guest_addr(addr: ByteAddr) -> Result<ByteAddr> {
        if !is_guest_memory(addr.0) {
            bail!("{addr:?} is an invalid guest address");
        }
        Ok(addr)
    }

    fn load_guest_addr_from_register(&mut self, idx: usize) -> Result<ByteAddr> {
        let addr = ByteAddr(self.load_register(idx)?);
        Self::check_guest_addr(addr)
    }

    fn load_u32_from_guest(&mut self, addr: ByteAddr) -> Result<u32> {
        Self::check_guest_addr(addr)?;
        self.load_memory(addr.waddr())
    }

    fn load_array_from_guest<const N: usize>(&mut self, addr: ByteAddr) -> Result<[u8; N]> {
        // Self::check_guest_addr_range(addr, addr + u32::try_from(N)?)?;
        Self::check_guest_addr(addr)?;
        Self::check_guest_addr(addr + N)?;
        self.load_array(addr)
    }

    fn load_array<const N: usize>(&mut self, addr: ByteAddr) -> Result<[u8; N]> {
        let mut bytes = Vec::new();
        for i in 0..N {
            bytes.push(self.load_u8(addr + i)?);
        }
        let ret = array::from_fn(|i| bytes[i]);
        // tracing::trace!("load_array({addr:?}) -> {ret:02x?}");
        Ok(ret)
    }

    fn load_u8(&mut self, addr: ByteAddr) -> Result<u8> {
        let word = self.pager.load(addr.waddr());
        let bytes = word.to_le_bytes();
        let byte_offset = addr.0 as usize % WORD_SIZE;
        Ok(bytes[byte_offset])
    }

    fn peek_string(&mut self, mut addr: ByteAddr) -> Result<String> {
        // tracing::trace!("load_string: 0x{addr:08x}");
        let mut buf = Vec::new();
        loop {
            let bytes = self.peek_u8(addr)?;
            if bytes == 0 {
                break;
            }
            buf.push(bytes);
            addr += 1u32;
        }
        Ok(String::from_utf8(buf)?)
    }

    fn store_u32_into_guest(&mut self, addr: ByteAddr, data: u32) -> Result<()> {
        Self::check_guest_addr(addr)?;
        self.store_memory(addr.waddr(), data)
    }

    fn store_region_into_guest(&mut self, addr: ByteAddr, slice: &[u8]) -> Result<()> {
        Self::check_guest_addr(addr)?;
        Self::check_guest_addr(addr + slice.len())?;
        self.store_region(addr, slice)
    }

    fn raw_store_u8(&mut self, addr: ByteAddr, byte: u8) -> Result<()> {
        let byte_offset = addr.0 as usize % WORD_SIZE;
        let word = self.peek_u32(addr)?;
        let mut bytes = word.to_le_bytes();
        bytes[byte_offset] = byte;
        let word = u32::from_le_bytes(bytes);
        self.raw_store_memory(addr.waddr(), word)
    }

    fn store_region(&mut self, addr: ByteAddr, slice: &[u8]) -> Result<()> {
        // tracing::trace!("store_region({addr:?}, {slice:02x?})");
        if !self.trace.is_empty() {
            self.pending.events.insert(TraceEvent::MemorySet {
                addr: addr.0,
                region: slice.into(),
            });
        }

        slice
            .iter()
            .enumerate()
            .try_for_each(|(i, x)| self.raw_store_u8(addr + i, *x))?;

        Ok(())
    }

    fn raw_store_memory(&mut self, addr: WordAddr, data: u32) -> Result<()> {
        // tracing::trace!("store_mem({:?}, 0x{data:08x})", addr.baddr());
        self.pager.store(addr, data)
    }
}

impl<'a, 'b, S: Syscall> EmuContext for Executor<'a, 'b, S> {
    fn ecall(&mut self) -> Result<bool> {
        match self.load_register(REG_T0)? {
            ecall::HALT => self.ecall_halt(),
            ecall::INPUT => self.ecall_input(),
            ecall::SOFTWARE => self.ecall_software(),
            ecall::SHA => self.ecall_sha(),
            ecall::BIGINT => self.ecall_bigint(),
            ecall => bail!("Unknown ecall {ecall:?}"),
        }
    }

    fn mret(&self) -> Result<bool> {
        unimplemented!()
    }

    fn trap(&self, cause: TrapCause) -> Result<bool> {
        let msg = format!("Trap: {cause:08x?}, pc: {:?}", self.pc);
        tracing::info!("{msg}");
        bail!("{msg}");
    }

    fn check_data_load(&self, addr: ByteAddr) -> bool {
        is_guest_memory(addr.0)
    }

    fn check_data_store(&self, addr: ByteAddr) -> bool {
        is_guest_memory(addr.0)
    }

    fn check_insn_load(&self, addr: ByteAddr) -> bool {
        is_guest_memory(addr.0)
    }

    fn on_insn_decoded(&self, insn: &Instruction, _decoded: &DecodedInstruction) {
        tracing::trace!("{:?}> {:?}", self.pc, insn.kind);
    }

    fn on_normal_end(&mut self, insn: &Instruction, decoded: &DecodedInstruction) {
        self.pending.insn = decoded.insn;
        self.pending.cycles += insn.cycles;
    }

    fn get_pc(&self) -> ByteAddr {
        self.pending.pc
    }

    fn set_pc(&mut self, pc: ByteAddr) {
        self.pending.pc = pc;
    }

    fn load_register(&mut self, idx: usize) -> Result<u32> {
        // tracing::trace!("load_reg: x{idx}");
        Ok(self.pager.load(SYSTEM_START + idx))
    }

    fn store_register(&mut self, idx: usize, data: u32) -> Result<()> {
        if idx != 0 {
            // tracing::trace!("store_reg: x{idx} <= 0x{data:08x}");
            self.pager.store(SYSTEM_START + idx, data)?;
            if !self.trace.is_empty() {
                self.pending
                    .events
                    .insert(TraceEvent::RegisterSet { idx, value: data });
            }
        }
        Ok(())
    }

    fn load_memory(&mut self, addr: WordAddr) -> Result<u32> {
        let data = self.pager.load(addr);
        // tracing::trace!("load_mem({:?}) -> 0x{data:08x}", addr.baddr());
        Ok(data)
    }

    fn store_memory(&mut self, addr: WordAddr, data: u32) -> Result<()> {
        // tracing::trace!("store_mem({:?}, 0x{data:08x})", addr.baddr());
        if !self.trace.is_empty() {
            self.pending.events.insert(TraceEvent::MemorySet {
                addr: addr.baddr().0,
                region: data.to_le_bytes().to_vec(),
            });
        }
        self.raw_store_memory(addr, data)
    }
}

impl<'a, 'b, S: Syscall> SyscallContext for Executor<'a, 'b, S> {
    fn get_cycle(&self) -> u64 {
        self.cycles.user as u64
    }

    fn peek_register(&mut self, idx: usize) -> Result<u32> {
        if idx >= REG_MAX {
            bail!("invalid register: x{idx}");
        }
        self.pager.peek(SYSTEM_START + idx)
    }

    fn peek_u32(&mut self, addr: ByteAddr) -> Result<u32> {
        let addr = Self::check_guest_addr(addr)?;
        self.pager.peek(addr.waddr())
    }

    fn peek_u8(&mut self, addr: ByteAddr) -> Result<u8> {
        let addr = Self::check_guest_addr(addr)?;
        let word = self.pager.peek(addr.waddr())?;
        let bytes = word.to_le_bytes();
        let byte_offset = addr.0 as usize % WORD_SIZE;
        Ok(bytes[byte_offset])
    }

    fn peek_page(&mut self, page_idx: u32) -> Result<Vec<u8>> {
        let addr = self.pager.image.info.get_page_addr(page_idx);
        if !is_guest_memory(addr) {
            bail!("{page_idx} is an invalid guest page_idx");
        }
        Ok(self.pager.peek_page(page_idx))
    }

    fn get_pc(&self) -> u32 {
        EmuContext::get_pc(self).0
    }
}

#[tracing::instrument(skip_all)]
pub fn execute<S: Syscall>(
    image: MemoryImage,
    segment_limit_po2: usize,
    max_cycles: Option<u64>,
    syscall_handler: &S,
    input_digest: Option<Digest>,
) -> Result<SimpleSession> {
    if !(MIN_CYCLES_PO2..=MAX_CYCLES_PO2).contains(&segment_limit_po2) {
        bail!("Invalid segment_limit_po2: {segment_limit_po2}");
    }

    let mut segments = Vec::new();
    let trace = Vec::new();
    let result = Executor::new(image, syscall_handler, input_digest, trace).run(
        segment_limit_po2,
        max_cycles,
        |segment| {
            segments.push(segment);
            Ok(())
        },
    )?;

    Ok(SimpleSession { segments, result })
}

pub fn execute_elf<S: Syscall>(
    elf: &[u8],
    segment_po2: usize,
    max_cycles: Option<u64>,
    syscall_handler: &S,
    input_digest: Option<Digest>,
) -> Result<SimpleSession> {
    let program = Program::load_elf(elf, GUEST_MAX_MEM as u32)?;
    let image = MemoryImage::new(&program, PAGE_SIZE as u32)?;
    execute(
        image,
        segment_po2,
        max_cycles,
        syscall_handler,
        input_digest,
    )
}
