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

mod env;
mod io;
mod monitor;
#[cfg(test)]
mod tests;

use std::array;

use anyhow::{anyhow, bail, Result};
use risc0_zkp::{
    core::{
        digest::{DIGEST_BYTES, DIGEST_WORDS},
        hash::sha::BLOCK_BYTES,
    },
    ZK_CYCLES,
};
use risc0_zkvm_platform::{
    memory::MEM_SIZE,
    syscall::{
        ecall, halt,
        reg_abi::{REG_A0, REG_A1, REG_A2, REG_A3, REG_A4, REG_MAX, REG_T0},
    },
    PAGE_SIZE, WORD_SIZE,
};
use rrs_lib::{
    instruction_executor::InstructionExecutor,
    instruction_string_outputter::InstructionStringOutputter, process_instruction, HartState,
};

pub use self::env::{ExecutorEnv, ExecutorEnvBuilder};
use self::monitor::MemoryMonitor;
use crate::{
    align_up,
    opcode::{MajorType, OpCode},
    ExitCode, Loader, MemoryImage, Program, Segment, Session,
};

// The number of cycles required to compress a SHA-256 block.
const SHA_CYCLES: usize = 72;

// The number of blocks that fit within a single page.
const BLOCKS_PER_PAGE: usize = PAGE_SIZE / BLOCK_BYTES;

// The number of cycles required to compute a SHA-256 digest of a page.
const CYCLES_PER_PAGE: usize = SHA_CYCLES * BLOCKS_PER_PAGE;

/// TODO
pub struct Executor {
    env: ExecutorEnv,
    pre_image: MemoryImage,
    monitor: MemoryMonitor,
    hart: HartState,
    init_cycles: usize,
    fini_cycles: usize,
    body_cycles: usize,
    segment_cycle: usize,
    session_cycle: usize,
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

impl Executor {
    /// TODO
    pub fn new(env: ExecutorEnv, image: MemoryImage, pc: u32) -> Self {
        let pre_image = image.clone();
        let loader = Loader::new();
        let init_cycles = loader.init_cycles();
        let fini_cycles = loader.fini_cycles();

        let mut monitor = MemoryMonitor::new(image);
        let all_regs: [usize; REG_MAX] = array::from_fn(|idx| idx);
        let registers = monitor.load_registers(all_regs);
        monitor.clear();

        let hart = HartState {
            registers,
            pc,
            last_register_write: None,
        };

        Self {
            env,
            pre_image,
            monitor,
            hart,
            init_cycles,
            fini_cycles,
            body_cycles: 0,
            segment_cycle: init_cycles,
            session_cycle: init_cycles,
        }
    }

    /// TODO
    pub fn from_elf(env: ExecutorEnv, elf: &[u8]) -> Result<Self> {
        let program = Program::load_elf(&elf, MEM_SIZE as u32)?;
        let image = MemoryImage::new(&program, PAGE_SIZE as u32);
        Ok(Self::new(env, image, program.entry))
    }

    /// TODO
    pub fn run(&mut self) -> Result<Session> {
        let mut segments = Vec::new();

        loop {
            let result = self.step()?;
            if let Some(exit_code) = result {
                let pre_image = self.pre_image.clone();
                self.monitor.image.hash_pages(); // TODO: hash only the dirty pages
                let post_image_id = self.monitor.image.get_root();
                let segment = Segment::new(pre_image, post_image_id, exit_code);
                segments.push(segment);
                match exit_code {
                    ExitCode::SystemSplit => self.split(),
                    ExitCode::SessionLimit => bail!("Session limit exceeded"),
                    ExitCode::Paused => {
                        log::debug!("Paused: {}", self.segment_cycle);
                        break;
                    }
                    ExitCode::Halted(exit_code) => {
                        log::debug!("Halted({exit_code}): {}", self.segment_cycle);
                        break;
                    }
                };
            };
        }

        Ok(Session::new(segments))
    }

    fn split(&mut self) {
        log::debug!("SystemSplit: {}", self.segment_cycle);
        self.pre_image = self.monitor.image.clone();
        self.body_cycles = 0;
        self.segment_cycle = self.init_cycles;
        self.monitor.clear();
    }

    /// TODO
    pub fn step(&mut self) -> Result<Option<ExitCode>> {
        let insn_pc = self.hart.pc;
        let insn = self.monitor.load_u32(insn_pc);
        let opcode = OpCode::decode(insn);

        if log::log_enabled!(log::Level::Debug) {
            let mut outputter = InstructionStringOutputter { insn_pc };
            let desc = process_instruction(&mut outputter, insn);
            log::debug!(
                "[{}] pc: 0x{:08x}, insn: 0x{:08x} => {}",
                self.segment_cycle,
                outputter.insn_pc,
                insn,
                desc.unwrap_or(opcode.mnemonic.into())
            );
        }

        let mut hart = HartState {
            registers: self.hart.registers,
            pc: self.hart.pc,
            last_register_write: self.hart.last_register_write,
        };

        let op_result = if opcode.major == MajorType::ECall {
            self.ecall(&mut hart)?
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
            self.segment_cycle = segment_cycles;
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

        log::trace!(
            "body_cycles: {}\
            , fault_cycles: {fault_cycles}\
            , opcode_cycles: {}\
            , total: {total_cycles}",
            self.body_cycles,
            opcode.cycles,
        );

        total_cycles
    }

    fn ecall(&mut self, hart: &mut HartState) -> Result<OpcodeResult> {
        match self.monitor.load_register(REG_T0) {
            ecall::HALT => self.ecall_halt(),
            ecall::OUTPUT => Ok(OpcodeResult::default()),
            ecall::SOFTWARE => self.ecall_software(hart),
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

    fn ecall_software(&mut self, hart: &mut HartState) -> Result<OpcodeResult> {
        let [to_guest_ptr, to_guest_words, name_ptr] =
            self.monitor.load_registers([REG_A0, REG_A1, REG_A2]);
        let syscall_name = self.monitor.load_string(name_ptr)?;
        log::debug!("Guest called syscall {syscall_name:?} requesting {to_guest_words} words back");

        let chunks = align_up(to_guest_words as usize, WORD_SIZE);
        let mut to_guest = vec![0; to_guest_words as usize];

        let handler = self
            .env
            .syscalls
            .inner
            .get(&syscall_name)
            .ok_or(anyhow!("Unknown syscall: {syscall_name:?}"))?;
        let (a0, a1) =
            handler
                .borrow_mut()
                .syscall(&syscall_name, &mut self.monitor, &mut to_guest)?;

        self.monitor
            .store_region(to_guest_ptr, bytemuck::cast_slice(&to_guest));
        self.monitor.store_register(REG_A0, a0);
        self.monitor.store_register(REG_A1, a1);

        log::debug!("Syscall returned a0: {a0:#X}, a1: {a1:#X}");

        // Record the syscall
        // c.op.syscalls.push(SyscallResult {
        //     to_guest,
        //     regs: (a0, a1),
        // });

        hart.pc += WORD_SIZE as u32;

        // One cycle for the ecall cycle, then one for each chunk or
        // portion thereof then one to save output (a0, a1)
        Ok(OpcodeResult::new(None, 1 + chunks + 1))
    }
}
