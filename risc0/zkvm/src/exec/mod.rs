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

//! TODO

mod io;
#[cfg(test)]
mod tests;

use std::{
    array,
    collections::{BTreeSet, HashMap},
};

use anyhow::{anyhow, bail, Result};
use builder_pattern::Builder;
use risc0_zkp::{
    core::{
        digest::{DIGEST_BYTES, DIGEST_WORDS},
        hash::sha::BLOCK_BYTES,
    },
    ZK_CYCLES,
};
use risc0_zkvm_platform::{
    memory::SYSTEM,
    syscall::{
        ecall, halt,
        reg_abi::{REG_A0, REG_A1, REG_A2, REG_A3, REG_A4, REG_T0},
    },
    PAGE_SIZE, WORD_SIZE,
};
use rrs_lib::{
    instruction_executor::InstructionExecutor,
    instruction_string_outputter::InstructionStringOutputter, process_instruction, HartState,
    MemAccessSize, Memory,
};

use self::io::{Syscall, SyscallContext};
use crate::{align_up, binfmt::image::PageTableInfo, Loader, Segment};
use crate::{
    opcode::{MajorType, OpCode},
    ExitCode, MemoryImage, Session,
};

const DEFAULT_SEGMENT_LIMIT_PO2: usize = 20; // 1M cycles

const DEFAULT_SESSION_LIMIT: usize = 64 * 1024 * 1024; // 64M cycles

// The number of cycles required to compress a SHA-256 block.
const SHA_CYCLES: usize = 72;

// The number of blocks that fit within a single page.
const BLOCKS_PER_PAGE: usize = PAGE_SIZE / BLOCK_BYTES;

// The number of cycles required to compute a SHA-256 digest of a page.
const CYCLES_PER_PAGE: usize = SHA_CYCLES * BLOCKS_PER_PAGE;

/// TODO
#[derive(Builder)]
pub struct ExecutorEnv {
    #[default(HashMap::new())]
    vars: HashMap<String, String>,

    #[default(DEFAULT_SEGMENT_LIMIT_PO2)]
    segment_limit_po2: usize,

    #[default(DEFAULT_SESSION_LIMIT)]
    session_limit: usize,

    #[default(HashMap::new())]
    syscall_handlers: HashMap<String, Box<dyn Syscall>>,
}

/// TODO
pub struct Executor {
    env: ExecutorEnv,
    pre_image: MemoryImage,
    monitor: MemoryMonitor,
    hart: HartState,
    init_cycles: usize,
    fini_cycles: usize,
    body_cycles: usize,
}

#[derive(Eq, Ord, PartialEq, PartialOrd)]
struct MemStore {
    addr: u32,
    data: u8,
}

struct MemoryMonitor {
    image: MemoryImage,
    faults: PageFaults,
    pending_faults: PageFaults,
    pending_writes: BTreeSet<MemStore>,
}

impl MemoryMonitor {
    fn new(image: MemoryImage) -> Self {
        Self {
            image,
            faults: PageFaults::new(),
            pending_faults: PageFaults::new(),
            pending_writes: BTreeSet::new(),
        }
    }

    fn load_u8(&mut self, addr: u32) -> u8 {
        let info = &self.image.info;
        self.pending_faults.include(info, addr, IncludeDir::Read);
        self.image.buf[addr as usize]
    }

    fn load_u16(&mut self, addr: u32) -> u16 {
        assert_eq!(addr % 2, 0, "unaligned load");
        u16::from_le_bytes(self.load_array(addr))
    }

    fn load_u32(&mut self, addr: u32) -> u32 {
        assert_eq!(addr % WORD_SIZE as u32, 0, "unaligned load");
        u32::from_le_bytes(self.load_array(addr))
    }

    fn load_array<const N: usize>(&mut self, addr: u32) -> [u8; N] {
        array::from_fn(|idx| self.load_u8(addr + idx as u32))
    }

    fn load_register(&mut self, idx: usize) -> u32 {
        self.load_u32(get_register_addr(idx))
    }

    fn load_registers<const N: usize>(&mut self, idxs: [usize; N]) -> [u32; N] {
        idxs.map(|idx| self.load_register(idx))
    }

    fn load_string(&mut self, mut addr: u32) -> Result<String> {
        let mut s: Vec<u8> = Vec::new();
        loop {
            let b = self.load_u8(addr);
            if b == 0 {
                break;
            }
            s.push(b);
            addr += 1;
        }
        String::from_utf8(s).map_err(anyhow::Error::msg)
    }

    fn store_u8(&mut self, addr: u32, data: u8) {
        let info = &self.image.info;
        self.pending_faults.include(info, addr, IncludeDir::Write);
        self.pending_writes.insert(MemStore { addr, data });
    }

    fn store_u16(&mut self, addr: u32, data: u16) {
        assert_eq!(addr % 2, 0, "unaligned store");
        self.store_region(addr, &data.to_le_bytes());
    }

    fn store_u32(&mut self, addr: u32, data: u32) {
        assert_eq!(addr % WORD_SIZE as u32, 0, "unaligned store");
        self.store_region(addr, &data.to_le_bytes());
    }

    fn store_region(&mut self, addr: u32, slice: &[u8]) {
        for i in 0..slice.len() {
            self.store_u8(addr + i as u32, slice[i]);
        }
    }

    fn store_register(&mut self, idx: usize, data: u32) {
        self.store_u32(get_register_addr(idx), data);
    }

    // commit all pending activity
    fn commit(&mut self) {
        while let Some(op) = self.pending_writes.pop_first() {
            self.image.buf[op.addr as usize] = op.data;
        }
        self.faults.append(&mut self.pending_faults);
    }

    // drop all pending activity
    fn rollback(&mut self) {
        self.pending_writes.clear();
        self.pending_faults.clear();
    }

    fn total_faults(&self) -> usize {
        let reads = self.faults.reads.union(&self.pending_faults.reads).count();
        let writes = self
            .faults
            .writes
            .union(&self.pending_faults.writes)
            .count();
        reads + writes
    }

    fn clear(&mut self) {
        self.faults.clear();
        self.pending_writes.clear();
        self.pending_faults.clear();
    }
}

impl Memory for MemoryMonitor {
    fn read_mem(&mut self, addr: u32, size: MemAccessSize) -> Option<u32> {
        match size {
            MemAccessSize::Byte => Some(self.load_u8(addr) as u32),
            MemAccessSize::HalfWord => Some(self.load_u16(addr) as u32),
            MemAccessSize::Word => Some(self.load_u32(addr)),
        }
    }

    fn write_mem(&mut self, addr: u32, size: MemAccessSize, store_data: u32) -> bool {
        match size {
            MemAccessSize::Byte => self.store_u8(addr, store_data as u8),
            MemAccessSize::HalfWord => self.store_u16(addr, store_data as u16),
            MemAccessSize::Word => self.store_u32(addr, store_data),
        };
        true
    }
}

impl SyscallContext for MemoryMonitor {
    fn get_cycle(&self) -> usize {
        todo!()
    }

    fn load_u32(&mut self, addr: u32) -> u32 {
        MemoryMonitor::load_u32(self, addr)
    }

    fn load_u8(&mut self, addr: u32) -> u8 {
        MemoryMonitor::load_u8(self, addr)
    }
}

fn get_register_addr(idx: usize) -> u32 {
    (SYSTEM.start() + idx * WORD_SIZE) as u32
}

#[derive(Default)]
struct OpcodeResult {
    exit_code: Option<ExitCode>,
    extra_cycles: usize,
}

impl OpcodeResult {
    fn new(exit_code: Option<ExitCode>, extra_cycles: usize) -> Self {
        Self {
            exit_code,
            extra_cycles,
        }
    }
}

impl ExecutorEnv {}

impl Executor {
    /// TODO
    pub fn new(env: ExecutorEnv, image: MemoryImage, pc: u32) -> Self {
        let pre_image = image.clone();
        let loader = Loader::new();
        let init_cycles = loader.init_cycles();
        let fini_cycles = loader.fini_cycles();

        let registers = core::array::from_fn(|reg| {
            u32::from_le_bytes(
                image.buf[SYSTEM.start() + reg * WORD_SIZE..SYSTEM.start() + (reg + 1) * WORD_SIZE]
                    .try_into()
                    .unwrap(),
            )
        });

        let hart = HartState {
            registers,
            pc,
            last_register_write: None,
        };

        Self {
            env,
            pre_image,
            monitor: MemoryMonitor::new(image),
            hart,
            init_cycles,
            fini_cycles,
            body_cycles: 0,
        }
    }

    /// TODO
    pub fn run(&mut self) -> Result<Session> {
        let mut segments = Vec::new();

        loop {
            let result = self.step()?;
            if let Some(exit_code) = result {
                let pre_image = self.pre_image.clone();
                self.monitor.image.hash_pages();
                let post_image_id = self.monitor.image.get_root();
                let segment = Segment::new(pre_image, post_image_id, exit_code);
                segments.push(segment);
                match exit_code {
                    ExitCode::SystemSplit => self.split(),
                    ExitCode::SessionLimit => bail!("Session limit exceeded"),
                    ExitCode::Paused | ExitCode::Halted(_) => {
                        break;
                    }
                };
            };
        }

        Ok(Session::new(segments))
    }

    fn split(&mut self) {
        log::debug!("SystemSplit");
        self.pre_image = self.monitor.image.clone();
        self.body_cycles = 0;
        self.monitor.clear();
    }

    /// TODO
    pub fn step(&mut self) -> Result<Option<ExitCode>> {
        let insn_pc = self.hart.pc;
        let insn = self.monitor.load_u32(insn_pc);
        let opcode = OpCode::decode(insn);

        let mut outputter = InstructionStringOutputter { insn_pc };
        let desc = process_instruction(&mut outputter, insn);
        log::debug!(
            "pc: 0x{:08x}, insn: 0x{:08x}, {}",
            outputter.insn_pc,
            insn,
            desc.unwrap_or(opcode.mnemonic.into())
        );

        let mut hart = HartState {
            registers: self.hart.registers,
            pc: self.hart.pc,
            last_register_write: self.hart.last_register_write,
        };

        let op_result = if opcode.major == MajorType::ECall {
            self.ecall()?
        } else {
            InstructionExecutor {
                mem: &mut self.monitor,
                hart_state: &mut hart,
            }
            .step()
            .map_err(|err| anyhow!("{:?}", err))?;
            OpcodeResult::default()
        };

        if let Some(idx) = hart.last_register_write {
            self.monitor.store_register(idx, hart.registers[idx]);
        }

        // try to execute the next instruction
        // if the segment limit is exceeded:
        // * don't increment the PC
        // * don't record any activity
        // * return ExitCode::SystemSplit
        // otherwise, commit memory and hart

        let segment_limit = 1 << self.env.segment_limit_po2;
        let segment_cycles = self.segment_cycles(&opcode);
        let exit_code = if segment_cycles > segment_limit {
            self.monitor.rollback();
            Some(ExitCode::SystemSplit)
        } else {
            self.hart = hart;
            self.monitor.commit();
            self.body_cycles += opcode.cycles + op_result.extra_cycles;
            op_result.exit_code
        };
        Ok(exit_code)
    }

    fn segment_cycles(&self, opcode: &OpCode) -> usize {
        // How many cycles are required to execute the next instruction?
        // This sum is based on:
        // - ensure we don't split in the middle of a SHA compress
        // - each page fault requires 1 PageFault cycle + CYCLES_PER_PAGE cycles
        // - leave room for fini_cycles
        // - leave room for ZK cycles
        let fault_cycles = self.monitor.total_faults() * (1 + CYCLES_PER_PAGE);
        let total_cycles = self.init_cycles
            + opcode.cycles
            + self.body_cycles
            + fault_cycles
            + self.fini_cycles
            + SHA_CYCLES
            + ZK_CYCLES;

        log::debug!(
            "body_cycles: {}, fault_cycles: {fault_cycles}, opcode_cycles: {}, total: {total_cycles}",
            self.body_cycles,
            opcode.cycles,
        );

        total_cycles
    }

    fn ecall(&mut self) -> Result<OpcodeResult> {
        match self.monitor.load_register(REG_T0) {
            ecall::HALT => self.ecall_halt(),
            ecall::OUTPUT => Ok(OpcodeResult::default()),
            ecall::SOFTWARE => self.ecall_software(),
            ecall::SHA => self.ecall_sha(),
            ecall => bail!("Unknown ecall {ecall:?}"),
        }
    }

    fn ecall_halt(&mut self) -> Result<OpcodeResult> {
        let halt_type = self.monitor.load_register(REG_A0);
        let exit_code = match halt_type {
            halt::TERMINATE => ExitCode::Halted(0),
            halt::PAUSE => ExitCode::Paused,
            halt::SPLIT => ExitCode::SystemSplit,
            _ => bail!("Illegal halt type: {halt_type}"),
        };
        Ok(OpcodeResult::new(Some(exit_code), 0))
    }

    fn ecall_sha(&mut self) -> Result<OpcodeResult> {
        let [out_state_ptr, in_state_ptr, mut block1_ptr, mut block2_ptr, count] = self
            .monitor
            .load_registers([REG_A0, REG_A1, REG_A2, REG_A3, REG_A4]);

        let in_state: [u8; DIGEST_BYTES] = self.monitor.load_array(in_state_ptr);
        let mut state: [u32; DIGEST_WORDS] = bytemuck::cast_slice(&in_state).try_into().unwrap();
        for word in &mut state {
            *word = word.to_be();
        }

        log::debug!("Initial sha state: {state:08x?}");
        for _ in 0..count {
            let mut block = [0u32; DIGEST_WORDS * 2];
            for i in 0..DIGEST_WORDS {
                block[i] = self.monitor.load_u32(block1_ptr + (i * WORD_SIZE) as u32);
            }
            for i in 0..DIGEST_WORDS {
                block[DIGEST_WORDS + i] =
                    self.monitor.load_u32(block2_ptr + (i * WORD_SIZE) as u32);
            }
            log::debug!("Compressing block {block:02x?}");
            sha2::compress256(
                &mut state,
                &[*generic_array::GenericArray::from_slice(
                    bytemuck::cast_slice(&block),
                )],
            );

            block1_ptr += BLOCK_BYTES as u32;
            block2_ptr += BLOCK_BYTES as u32;
        }
        log::debug!("Final sha state: {state:08x?}");

        for word in &mut state {
            *word = u32::from_be(*word);
        }

        self.monitor
            .store_region(out_state_ptr, bytemuck::cast_slice(&state));

        Ok(OpcodeResult::new(None, SHA_CYCLES * count as usize))
    }

    fn ecall_software(&mut self) -> Result<OpcodeResult> {
        let [to_guest_ptr, to_guest_words, name_ptr] =
            self.monitor.load_registers([REG_A0, REG_A1, REG_A2]);
        let syscall_name = self.monitor.load_string(name_ptr)?;
        log::debug!("Guest called syscall {syscall_name} requesting {to_guest_words} words back");

        let chunks = align_up(to_guest_words as usize, WORD_SIZE);
        let mut to_guest = vec![0u32; to_guest_words as usize];

        let (a0, a1): (u32, u32);
        if let Some(cb) = self.env.syscall_handlers.get(&syscall_name) {
            (a0, a1) = cb.syscall(&syscall_name, &mut self.monitor, &mut to_guest)?;
            self.monitor
                .store_region(to_guest_ptr, bytemuck::cast_slice(&to_guest));
        } else {
            bail!("Unknown syscall {syscall_name}");
        }

        self.monitor.store_register(REG_A0, a0);
        self.monitor.store_register(REG_A1, a1);

        log::debug!("Syscall returned a0: {a0:#X}, a1: {a1:#X}");

        // Record the syscall
        // c.op.syscalls.push(SyscallResult {
        //     to_guest,
        //     regs: (a0, a1),
        // });

        // One cycle for the ecall cycle, then one for each chunk or
        // portion thereof then one to save output (a0, a1)
        Ok(OpcodeResult::new(None, 1 + chunks + 1))
    }
}

struct PageFaults {
    reads: BTreeSet<u32>,
    writes: BTreeSet<u32>,
}

enum IncludeDir {
    Read,
    Write,
}

impl PageFaults {
    pub fn new() -> Self {
        Self {
            reads: BTreeSet::new(),
            writes: BTreeSet::new(),
        }
    }

    fn include(&mut self, info: &PageTableInfo, addr: u32, dir: IncludeDir) {
        let mut addr = addr;
        loop {
            let page_idx = info.get_page_index(addr);
            let entry_addr = info.get_page_entry_addr(page_idx);
            match dir {
                IncludeDir::Read => self.reads.insert(page_idx),
                IncludeDir::Write => self.writes.insert(page_idx),
            };
            if page_idx == info.root_idx {
                break;
            }
            addr = entry_addr;
        }
    }

    fn clear(&mut self) {
        self.reads.clear();
        self.writes.clear();
    }

    fn append(&mut self, rhs: &mut Self) {
        self.reads.append(&mut rhs.reads);
        self.writes.append(&mut rhs.writes);
    }

    #[allow(dead_code)]
    fn dump(&self) {
        log::debug!("PageFaultInfo");
        log::debug!("  reads>");
        for idx in self.reads.iter().rev() {
            log::debug!("  0x{:08X}", idx);
        }
        log::debug!("  writes>");
        for idx in self.writes.iter().rev() {
            log::debug!("  0x{:08X}", idx);
        }
    }
}
