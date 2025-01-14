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

use anyhow::{bail, Result};
use risc0_binfmt::{MemoryImage2, Program};
use risc0_core::scope;
use risc0_zkp::{
    core::{digest::Digest, log2_ceil},
    MAX_CYCLES_PO2,
};

use super::{
    pager::RESERVED_PAGING_CYCLES, platform::*, syscall::Syscall, Executor, SimpleSession,
    SyscallContext,
};

pub const DEFAULT_SESSION_LIMIT: Option<u64> = Some(1 << 24);
pub const MIN_CYCLES_PO2: usize = log2_ceil(LOOKUP_TABLE_CYCLES + RESERVED_PAGING_CYCLES as usize);

#[derive(Default)]
pub struct NullSyscall;

impl Syscall for NullSyscall {
    fn host_read(&self, _ctx: &mut dyn SyscallContext, _fd: u32, _buf: &mut [u8]) -> Result<u32> {
        unimplemented!()
    }

    fn host_write(&self, _ctx: &mut dyn SyscallContext, _fd: u32, _buf: &[u8]) -> Result<u32> {
        unimplemented!()
    }
}

pub fn execute<S: Syscall>(
    image: MemoryImage2,
    segment_limit_po2: usize,
    max_insn_cycles: usize,
    max_cycles: Option<u64>,
    syscall_handler: &S,
    input_digest: Option<Digest>,
) -> Result<SimpleSession> {
    scope!("execute");

    if !(MIN_CYCLES_PO2..=MAX_CYCLES_PO2).contains(&segment_limit_po2) {
        bail!("Invalid segment_limit_po2: {segment_limit_po2}");
    }

    let mut segments = Vec::new();
    let trace = Vec::new();
    let result = Executor::new(image, syscall_handler, input_digest, trace).run(
        segment_limit_po2,
        max_insn_cycles,
        max_cycles,
        |segment| {
            tracing::trace!("{segment:#?}");
            segments.push(segment);
            Ok(())
        },
    )?;

    Ok(SimpleSession { segments, result })
}

/// Constructs a program from an iterator of instructions starting from an entrypoint.
fn program_from_instructions(instructions: impl IntoIterator<Item = u32>) -> Program {
    let entry = USER_START_ADDR + WORD_SIZE;
    let entry = entry.0;
    let mut pc = entry;

    Program {
        entry,
        image: instructions
            .into_iter()
            .map(|instr| {
                let result = (pc, instr);
                pc += WORD_SIZE as u32;
                result
            })
            .collect(),
    }
}

pub fn basic() -> Program {
    program_from_instructions([
        lui(REG_T1, 0x1234b),
        lui(REG_T2, 0xf387e),
        add(REG_T0, REG_T1, REG_T2),
        lui(REG_A1, 0x4),
        ecall(),
    ])
}

pub fn simple_loop(count: u32) -> Program {
    // loop.asm:
    //
    // .global _boot
    // .text
    //
    // _boot:
    //     li      a4,0
    //     li      a5,100
    // loop:
    //     addi    a4,a4,1
    //     blt     a4,a5,loop
    //     lui     a1,0x1000
    //     ecall
    //
    // riscv32-unknown-elf-as loop.asm -o loop; riscv32-unknown-elf-objdump -d loop

    // sign extend low 12 bits
    let low = ((count as i32) << 20) >> 20;
    // upper 20 bits
    let high = (count as i32 - low) >> 12;
    tracing::debug!("{count:#010x}: ({high:#010x}, {low:#010x})");

    program_from_instructions([
        addi(REG_A4, REG_ZERO, 0),
        lui(REG_A5, high as u32),
        addi(REG_A5, REG_A5, low as u32),
        // loop:
        addi(REG_A4, REG_A4, 1),
        blt(REG_A4, REG_A5, -4 /*loop: */),
        lui(REG_A1, 0x1000),
        ecall(),
    ])
}

// 31        25 | 24  20 | 19  15 | 14  12 | 11        7 | 6    0 |
//    funct7    |   rs2  |   rs1  | funct3 |      rd     | opcode |
fn insn_r(funct7: u32, rs2: u32, rs1: u32, funct3: u32, rd: u32, opcode: u32) -> u32 {
    (funct7 << 25) | (rs2 << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode
}

// 31                 20 | 19  15 | 14  12 | 11        7 | 6    0 |
//     imm[11:0]         |   rs1  | funct3 |      rd     | opcode |
fn insn_i(imm: u32, rs1: u32, funct3: u32, rd: u32, opcode: u32) -> u32 {
    (imm << 20) | (rs1 << 15) | (funct3 << 12) | (rd << 7) | opcode
}

// 31        25 | 24  20 | 19  15 | 14  12 | 11        7 | 6    0 |
// imm[12|10:5] |   rs2  |   rs1  | funct3 | imm[4:1|11] | opcode |
fn insn_b(imm: u32, rs2: u32, rs1: u32, funct3: u32, opcode: u32) -> u32 {
    let imm_12 = (imm >> 12) & 0b1;
    let imm_10_5 = (imm >> 5) & 0b111111;
    let imm_11 = (imm >> 11) & 0b1;
    let imm_4_1 = (imm >> 1) & 0b1111;
    ((imm_12 << 6 | imm_10_5) << 25)
        | (rs2 << 20)
        | (rs1 << 15)
        | (funct3 << 12)
        | ((imm_4_1 << 1 | imm_11) << 7)
        | opcode
}

// 31                                   12 | 11        7 | 6    0 |
//    imm[31:12]                           |      rd     | opcode |
fn insn_u(imm: u32, rd: u32, opcode: u32) -> u32 {
    (imm << 12) | rd << 7 | opcode
}

fn add(rd: usize, rs1: usize, rs2: usize) -> u32 {
    insn_r(0x00, rs2 as u32, rs1 as u32, 0x0, rd as u32, 0b0110011)
}

fn addi(rd: usize, rs1: usize, imm: u32) -> u32 {
    insn_i(imm, rs1 as u32, 0x0, rd as u32, 0b0010011)
}

fn blt(rs1: usize, rs2: usize, offset: i32) -> u32 {
    insn_b(offset as u32, rs2 as u32, rs1 as u32, 0x4, 0b1100011)
}

fn ecall() -> u32 {
    insn_i(0x0, 0x0, 0x0, 0x0, 0b1110011)
}

fn lui(rd: usize, imm: u32) -> u32 {
    insn_u(imm, rd as u32, 0b0110111)
}
