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

use std::{collections::BTreeSet, vec::Vec};

use anyhow::{anyhow, bail, Result};
use risc0_zkvm_platform::{
    memory::SYSTEM,
    syscall::{ecall, halt, reg_abi::*},
    WORD_SIZE,
};
use rrs_lib::{
    instruction_executor::InstructionExecutor,
    instruction_string_outputter::InstructionStringOutputter, process_instruction, HartState,
    MemAccessSize, Memory,
};

use super::{
    align_up,
    opcode::{MajorType, OpCode},
    segment::{Segment, Segmentize},
};
use crate::{
    prove::{io::SyscallContext, ProverOpts},
    sha::{DIGEST_BYTES, DIGEST_WORDS},
    MemoryImage,
};

const NUM_REGS: usize = 32;

#[derive(Debug, Clone)]
pub struct MemWrite {
    pub addr: u32,
    pub val: u32,
}

#[derive(Debug, Clone)]
pub struct SyscallResult {
    pub to_guest: Vec<u32>,
    pub regs: (u32, u32),
}

#[derive(Debug, Clone)]
pub enum OperationType {
    /// Normal execution; runs the rv32im instruction at the current program
    /// counter.
    Execute,

    /// Page in the given page
    PageIn(u32),

    /// Halt execution
    Terminate,

    /// Halt execution, for this sgment, but continue in the next one.
    Pause,
}

/// Information on a preflight operation.
#[derive(Debug, Clone)]
pub struct Operation {
    /// Number of circuit cycles used by this preflight operation.
    pub circuit_cycles: usize,

    /// Program counter for the next operation after this one
    pub new_pc: u32,

    /// Memory writes
    pub mem_writes: Vec<MemWrite>,

    /// Addresses of memory reads.
    pub mem_reads: Vec<u32>,

    /// Results from any system calls made.
    pub syscalls: Vec<SyscallResult>,

    /// Type of operation this Operation does.
    pub op_type: OperationType,
}

impl Operation {
    fn new() -> Self {
        Self {
            circuit_cycles: 0,
            new_pc: 0,
            mem_writes: Vec::new(),
            mem_reads: Vec::new(),
            op_type: OperationType::Execute,
            syscalls: Vec::new(),
        }
    }
}

struct OperationBuilder<'a, 'b> {
    exec: &'a ExecState<'b>,

    op: Operation,
}

impl<'a, 'b> SyscallContext for OperationBuilder<'a, 'b> {
    fn get_cycle(&self) -> usize {
        self.exec.cycles
    }

    fn load_u32(&self, addr: u32) -> u32 {
        u32::from_le_bytes(
            self.exec.mem.image[addr as usize..addr as usize + WORD_SIZE]
                .try_into()
                .unwrap(),
        )
    }

    fn load_u8(&self, addr: u32) -> u8 {
        self.exec.mem.image[addr as usize]
    }

    fn load_region(&self, addr: u32, len: u32) -> Vec<u8> {
        self.exec.mem.image[addr as usize..(addr + len) as usize].to_vec()
    }
}

// Expose our memory as memory to rrs_lib.
impl Memory for OperationBuilder<'static, 'static> {
    fn read_mem(&mut self, addr: u32, size: MemAccessSize) -> Option<u32> {
        self.op.mem_reads.push(addr & !(WORD_SIZE as u32 - 1));
        match size {
            MemAccessSize::Byte => Some(self.load_u8(addr) as u32),
            MemAccessSize::HalfWord => {
                Some((self.load_u8(addr) as u32) + ((self.load_u8(addr + 1) as u32) << 8))
            }
            MemAccessSize::Word => Some(self.load_u32(addr)),
        }
    }

    fn write_mem(&mut self, addr: u32, size: MemAccessSize, store_data: u32) -> bool {
        let addr_word = addr & !(WORD_SIZE as u32 - 1);
        let mut word = self.load_u32(addr_word);
        self.op.mem_reads.push(addr_word);
        match size {
            MemAccessSize::Byte => {
                let mut bytes = word.to_le_bytes();
                bytes[addr as usize & 0x3] = store_data as u8;
                word = u32::from_le_bytes(bytes);
            }
            MemAccessSize::HalfWord => match addr & 0x2 {
                0x0 => word = (word & !0xFFFF) | store_data,
                0x02 => word = (word & 0xFFFF) | (store_data << 16),
                _ => unreachable!(),
            },
            MemAccessSize::Word => word = store_data,
        };
        self.op.mem_writes.push(MemWrite {
            addr: addr_word,
            val: word,
        });
        true
    }
}

impl<'a, 'b> OperationBuilder<'a, 'b> {
    fn new(exec: &'a ExecState<'b>) -> Self {
        Self {
            exec: exec,
            op: Operation::new(),
        }
    }
    fn store_u32(&mut self, addr: u32, val: u32) {
        assert!(addr % WORD_SIZE as u32 == 0);
        self.op.mem_writes.push(MemWrite { addr, val });
    }

    fn store_register(&mut self, reg: usize, val: u32) {
        self.store_u32((SYSTEM.start() + reg * WORD_SIZE) as u32, val)
    }

    fn store_region(&mut self, start: u32, data: &[u32]) {
        for (addr, word) in (start..start + (data.len() * WORD_SIZE) as u32)
            .step_by(WORD_SIZE)
            .zip(data.iter().copied())
        {
            self.store_u32(addr, word)
        }
    }

    fn build(self) -> Result<Operation> {
        Ok(self.op)
    }
}

pub struct ExecState<'a> {
    // Current RAM state
    pub(super) mem: MemoryImage,

    // Current rrs_lib register state
    registers: [u32; NUM_REGS],

    // Current program counter
    pub(super) pc: u32,

    // Current cycle count
    cycles: usize,

    // Prover options
    pub(super) opts: ProverOpts<'a>,

    // True if the guest requested a halt to this session.
    terminated: bool,

    // Currently paged in pages.
    pages: BTreeSet<u32>,
}

impl<'a> ExecState<'a> {
    pub fn new(entry: u32, mem_init: MemoryImage, opts: ProverOpts<'a>) -> Self {
        let registers = core::array::from_fn(|reg| {
            u32::from_le_bytes(
                mem_init.image
                    [SYSTEM.start() + reg * WORD_SIZE..SYSTEM.start() + (reg + 1) * WORD_SIZE]
                    .try_into()
                    .unwrap(),
            )
        });
        Self {
            mem: mem_init,
            cycles: 0,
            registers,
            terminated: false,
            opts,
            pc: entry,
            pages: BTreeSet::new(),
        }
    }

    pub fn compute(&self) -> Result<Operation> {
        if self.terminated {
            bail!("Terminated");
        }
        let mut c = OperationBuilder::new(self);
        let inst = c.load_u32(self.pc);
        let opcode = OpCode::decode(inst);

        if opcode.major == MajorType::ECall {
            return self.do_ecall();
        }

        if log::log_enabled!(log::Level::Trace) {
            let mut outputter = InstructionStringOutputter { insn_pc: self.pc };
            let desc = process_instruction(&mut outputter, inst);
            log::trace!(
                "pc=0x{:08x}: inst=0x{:08x} {}",
                outputter.insn_pc,
                inst,
                desc.as_ref().map(String::as_str).unwrap_or("(unknown)")
            );
        }
        let mut hart_state = HartState {
            registers: self.registers,
            pc: self.pc,
            last_register_write: None,
        };

        {
            // Ugh, rrs_lib requires that its memory handler has a static
            // lifetime.  Safety: We don't let this escape.
            // TODO: Submit upstream patch maybe?
            let c_static: &mut OperationBuilder<'static, 'static> = unsafe {
                &mut *((&mut c as *mut OperationBuilder).cast()
                    as *mut OperationBuilder<'static, 'static>)
            };
            InstructionExecutor {
                hart_state: &mut hart_state,
                mem: c_static,
            }
            .step()
            .map_err(|err| anyhow!("{:?}", err))?;
        }

        c.op.new_pc = hart_state.pc;
        c.op.circuit_cycles = match opcode.mnemonic {
            "XORI" | "ORI" | "ANDI" | "SRLI" | "SRAI" | "XOR" | "OR" | "AND" | "DIV" | "DIVU"
            | "REM" | "REMU" | "SRL" | "SRA" => 2,
            _ => 1,
        };

        if let Some(reg) = hart_state.last_register_write {
            // This instruction updated a register; save it to the register section of our
            // RAM
            c.store_register(reg, hart_state.registers[reg]);
        }

        c.build()
    }

    fn do_ecall(&self) -> Result<Operation> {
        let mut c = OperationBuilder::new(self);
        c.op.new_pc = self.pc + WORD_SIZE as u32;
        match c.load_register(REG_T0) {
            ecall::HALT => {
                let halt_type = c.load_register(REG_A0);
                match halt_type {
                    halt::TERMINATE => {
                        c.op.op_type = OperationType::Terminate;
                        c.op.circuit_cycles = 1;
                    }
                    halt::PAUSE | halt::SPLIT => {
                        c.op.op_type = OperationType::Pause;
                        c.op.circuit_cycles = 1;
                    }
                    _ => {
                        panic!("Unknown halt type {halt_type}")
                    }
                }
            }
            ecall::OUTPUT => {
                // TODO
                c.op.circuit_cycles = 1;
            }
            ecall::SHA => {
                let [out_state, in_state, mut block1_ptr, mut block2_ptr, count] =
                    [REG_A0, REG_A1, REG_A2, REG_A3, REG_A4].map(|reg| c.load_register(reg));

                // Sha setup
                c.op.circuit_cycles = 1;

                let in_state_vec = c.load_region(in_state, DIGEST_BYTES as u32);
                let mut state: [u32; DIGEST_WORDS] =
                    bytemuck::cast_slice(&in_state_vec).try_into().unwrap();
                for word in &mut state {
                    *word = word.to_be();
                }

                log::debug!("Initial sha state: {state:08x?}");

                for _ in 0..count {
                    let mut block = [0u32; DIGEST_WORDS * 2];
                    for i in 0..DIGEST_WORDS {
                        block[i] = c.load_u32(block1_ptr + (i * WORD_SIZE) as u32);
                    }
                    for i in 0..DIGEST_WORDS {
                        block[DIGEST_WORDS + i] = c.load_u32(block2_ptr + (i * WORD_SIZE) as u32);
                    }
                    log::debug!("Compressing block {block:02x?}");
                    sha2::compress256(
                        &mut state,
                        &[*generic_array::GenericArray::from_slice(
                            bytemuck::cast_slice(&block),
                        )],
                    );

                    c.op.circuit_cycles += 72;
                    block1_ptr += DIGEST_BYTES as u32 * 2;
                    block2_ptr += DIGEST_BYTES as u32 * 2;
                }
                log::debug!("Final sha state: {state:08x?}");

                for word in &mut state {
                    *word = u32::from_be(*word);
                }

                c.store_region(out_state, bytemuck::cast_slice(&state));
            }
            ecall::SOFTWARE => {
                let to_guest_ptr = c.load_register(REG_A0);
                let to_guest_words = c.load_register(REG_A1);
                let name_ptr = c.load_register(REG_A2);
                let syscall_name = c.load_string(name_ptr)?;

                log::debug!(
                    "Guest called syscall {syscall_name} requesting {to_guest_words} words back"
                );

                // One cycle for the ecall cycle, then one for each chunk or
                // portion thereof then one to save output (a0, a1)
                let chunks = align_up(to_guest_words as usize, WORD_SIZE);
                c.op.circuit_cycles = 1 + chunks + 1;

                let mut to_guest = vec![0u32; to_guest_words as usize];

                let (a0, a1): (u32, u32);

                if let Some(cb) = self.opts.syscall_handlers.get(&syscall_name) {
                    (a0, a1) = cb.syscall(&syscall_name, &mut c, &mut to_guest)?;
                    c.store_region(to_guest_ptr, bytemuck::cast_slice(&to_guest));
                } else {
                    bail!("Unknown syscall {syscall_name}");
                }
                c.store_register(REG_A0, a0);
                c.store_register(REG_A1, a1);

                log::debug!("Syscall returned a0={a0:#X} a1={a1:#X}");

                // Record the syscall
                c.op.syscalls.push(SyscallResult {
                    to_guest,
                    regs: (a0, a1),
                });
            }
            ecall => bail!("Unknown ecall {ecall:?}"),
        }

        c.build()
    }

    /// If the given Operation requires a page-in, return a page-in
    /// operation that needs to be executed before this operation.
    pub fn get_page_in(&self, op: &Operation) -> Result<Option<Operation>> {
        // TODO: This is just a rough guess for now; we should make
        // crate::prove::exec::MachineContext::get_page_faults more
        // general and share code with it.
        for addr in op.mem_reads.iter() {
            if !self.pages.contains(addr) {
                let mut c = OperationBuilder::new(self);
                c.op.new_pc = self.pc;
                c.op.op_type = OperationType::PageIn(*addr);
                c.op.circuit_cycles = 2304;
                return Ok(Some(c.build()?));
            }
        }

        Ok(None)
    }

    pub fn apply(&mut self, op: &Operation) -> Result<()> {
        while let Some(page_in) = self.get_page_in(op)? {
            assert!(
                match op.op_type {
                    OperationType::PageIn(_) => false,
                    _ => true,
                },
                "Page-in ops should not generate more page-in ops."
            );
            self.apply(&page_in)?;
        }
        self.pc = op.new_pc;
        self.cycles += op.circuit_cycles;

        for wr in op.mem_writes.iter() {
            let addr = wr.addr as usize;
            if addr + WORD_SIZE > self.mem.image.len() {
                bail!("Out of bounds write: {wr:?}");
            }
            self.mem.image[addr..addr + WORD_SIZE].clone_from_slice(&wr.val.to_le_bytes());

            // Update rrs_lib's register structure
            if addr >= SYSTEM.start() {
                let reg = (addr - SYSTEM.start()) / 4;
                if reg < self.registers.len() {
                    self.registers[reg] = wr.val;
                }
            }
        }
        match op.op_type {
            OperationType::Execute | OperationType::Pause => (),
            OperationType::Terminate => self.terminated = true,
            OperationType::PageIn(page) => {
                self.pages.insert(page);
            }
        }
        Ok(())
    }

    pub fn is_terminated(&self) -> bool {
        self.terminated
    }

    fn try_next(&mut self) -> Result<Option<Operation>> {
        if self.terminated {
            Ok(None)
        } else {
            let op = self.compute()?;
            self.apply(&op)?;
            Ok(Some(op))
        }
    }

    pub fn segmentize(self) -> impl Iterator<Item = Result<Segment>> + 'a {
        Segmentize::new(self)
    }
}

impl<'a> Iterator for ExecState<'a> {
    type Item = Result<Operation>;

    fn next(&mut self) -> Option<Result<Operation>> {
        self.try_next().transpose()
    }
}
