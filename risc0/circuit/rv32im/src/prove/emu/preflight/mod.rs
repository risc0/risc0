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

use anyhow::{bail, Result};
use derive_debug::Dbg;
use risc0_zkp::core::digest::DIGEST_WORDS;
use risc0_zkvm_platform::{
    memory::SYSTEM,
    syscall::{
        ecall,
        reg_abi::{REG_A0, REG_A1, REG_T0},
    },
    WORD_SIZE,
};

use super::{
    pager::PagedMemory,
    rv32im::{DecodedInstruction, EmuConext, Emulator, InsnKind, TrapCause},
    Segment,
};

const SYSTEM_START: usize = SYSTEM.start() / WORD_SIZE;

#[derive(Copy, Clone, Debug, PartialEq)]
pub enum Major {
    Compute0,
    Compute1,
    Compute2,
    MemIo,
    Multiply,
    Divide,
    VerifyAnd,
    VerifyDivide,
    ECall,
    ShaInit,
    ShaLoad,
    ShaMain,
    PageFault,
    MuxSize,
}

#[derive(Clone, Dbg, PartialEq)]
pub struct PreflightCycle {
    #[dbg(fmt = "0x{:08x}")]
    pc: u32,
    is_valid: bool,
    mem_idx: usize,
    extra_idx: usize,
    pub major: Major,
    pub minor: u32,
}

#[derive(Clone, Dbg, PartialEq)]
pub struct MemoryTransaction {
    pub cycle: usize,
    #[dbg(fmt = "0x{:08x}")]
    pub addr: u32,
    #[dbg(fmt = "0x{:08x}")]
    pub data: u32,
}

#[derive(Default)]
pub struct PreflightTrace {
    pub cycles: Vec<PreflightCycle>,
    pub txns: Vec<MemoryTransaction>,
    extras: Vec<u32>,
}

struct Preflight {
    pager: PagedMemory,
    pc: u32,
    cycles: usize,
    pub trace: PreflightTrace,
    mem_idx: usize,
    extra_idx: usize,
    output_ptr: u32,
}

impl Major {
    pub fn as_u32(&self) -> u32 {
        *self as u32
    }
}

fn into_major_minor(kind: InsnKind) -> (Major, u32) {
    match kind {
        InsnKind::ADD => (Major::Compute0, 0),
        InsnKind::SUB => (Major::Compute0, 1),
        InsnKind::XOR => (Major::Compute0, 2),
        InsnKind::OR => (Major::Compute0, 3),
        InsnKind::AND => (Major::Compute0, 4),
        InsnKind::SLT => (Major::Compute0, 5),
        InsnKind::SLTU => (Major::Compute0, 6),
        InsnKind::ADDI => (Major::Compute0, 7),

        InsnKind::XORI => (Major::Compute1, 0),
        InsnKind::ORI => (Major::Compute1, 1),
        InsnKind::ANDI => (Major::Compute1, 2),
        InsnKind::SLTI => (Major::Compute1, 3),
        InsnKind::SLTIU => (Major::Compute1, 4),
        InsnKind::BEQ => (Major::Compute1, 5),
        InsnKind::BNE => (Major::Compute1, 6),
        InsnKind::BLT => (Major::Compute1, 7),

        InsnKind::BGE => (Major::Compute2, 0),
        InsnKind::BLTU => (Major::Compute2, 1),
        InsnKind::BGEU => (Major::Compute2, 2),
        InsnKind::JAL => (Major::Compute2, 3),
        InsnKind::JALR => (Major::Compute2, 4),
        InsnKind::LUI => (Major::Compute2, 5),
        InsnKind::AUIPC => (Major::Compute2, 6),

        InsnKind::LB => (Major::MemIo, 0),
        InsnKind::LH => (Major::MemIo, 1),
        InsnKind::LW => (Major::MemIo, 2),
        InsnKind::LBU => (Major::MemIo, 3),
        InsnKind::LHU => (Major::MemIo, 4),
        InsnKind::SB => (Major::MemIo, 5),
        InsnKind::SH => (Major::MemIo, 6),
        InsnKind::SW => (Major::MemIo, 7),

        InsnKind::MUL => (Major::Multiply, 0),
        InsnKind::MULH => (Major::Multiply, 1),
        InsnKind::MULHSU => (Major::Multiply, 2),
        InsnKind::MULHU => (Major::Multiply, 3),
        InsnKind::SLL => (Major::Multiply, 4),
        InsnKind::SLLI => (Major::Multiply, 5),

        InsnKind::DIV => (Major::Divide, 0),
        InsnKind::DIVU => (Major::Divide, 1),
        InsnKind::REM => (Major::Divide, 2),
        InsnKind::REMU => (Major::Divide, 3),
        InsnKind::SRL => (Major::Divide, 4),
        InsnKind::SRA => (Major::Divide, 5),
        InsnKind::SRLI => (Major::Divide, 6),
        InsnKind::SRAI => (Major::Divide, 7),

        // TODO: deal with ecall vs ebreak
        InsnKind::EANY => (Major::ECall, 0),

        InsnKind::MRET => unreachable!(),
        InsnKind::INVALID => unreachable!(),
    }
}

impl PreflightCycle {
    fn new(
        pc: u32,
        is_valid: bool,
        mem_idx: usize,
        extra_idx: usize,
        major: Major,
        minor: u32,
    ) -> Self {
        Self {
            pc,
            is_valid,
            mem_idx,
            extra_idx,
            major,
            minor,
        }
    }
}

impl MemoryTransaction {
    fn new(cycle: usize, addr: u32, data: u32) -> Self {
        Self { cycle, addr, data }
    }
}

impl Preflight {
    fn new(segment: &Segment) -> Self {
        let pc = segment.partial_image.pc;
        Self {
            pager: PagedMemory::new(segment.partial_image.clone()),
            pc,
            cycles: 0,
            trace: PreflightTrace::default(),
            mem_idx: 0,
            extra_idx: 0,
            output_ptr: 0,
        }
    }

    fn ecall_halt(&mut self) -> Result<bool> {
        self.output_ptr = self.load_register(REG_A1)?;
        self.load_register(REG_A0)?;
        Ok(true)
    }

    fn ecall_software(&mut self) -> Result<bool> {
        self.pc += WORD_SIZE as u32;
        Ok(true)
    }

    fn ecall_sha(&mut self) -> Result<bool> {
        self.pc += WORD_SIZE as u32;
        todo!()
    }

    fn ecall_bigint(&mut self) -> Result<bool> {
        self.pc += WORD_SIZE as u32;
        todo!()
    }

    fn load_u32(&mut self, addr: u32) -> Result<u32> {
        let data = self.pager.load(addr)?;
        tracing::debug!(
            "load_u32: 0x{:08x} => 0x{data:08x}",
            addr * WORD_SIZE as u32,
        );
        self.trace
            .txns
            .push(MemoryTransaction::new(self.cycles, addr, data));
        Ok(data)
    }

    fn store_u32(&mut self, addr: u32, data: u32) -> Result<()> {
        tracing::debug!(
            "store_u32: 0x{:08x} <= 0x{data:08x}",
            addr * WORD_SIZE as u32
        );
        // self.trace
        //     .txns
        //     .push(MemoryTransaction::new(self.cycles, addr, data));
        self.pager.store(addr, data)
    }

    fn pre_steps(&mut self) {
        //
    }

    fn post_steps(&mut self) -> Result<()> {
        // RESET(1)
        let addr = self.output_ptr / WORD_SIZE as u32;
        for i in 0..DIGEST_WORDS {
            self.load_u32(addr + i as u32)?;
        }

        // RESET(2)
        let root_addr = self.pager.image.info.root_addr / WORD_SIZE as u32;
        for i in 0..DIGEST_WORDS {
            self.load_u32(root_addr + i as u32)?;
        }

        Ok(())
    }
}

impl EmuConext for Preflight {
    fn ecall(&mut self) -> Result<bool> {
        match self.load_register(REG_T0)? {
            ecall::HALT => self.ecall_halt(),
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
        bail!("Trap: {cause:08x?}");
    }

    fn on_insn_decoded(&self, kind: InsnKind, _decoded: &DecodedInstruction) {
        tracing::debug!("0x{:08x}> {kind:?}", self.pc);
    }

    fn on_normal_end(&mut self, kind: InsnKind, _decoded: &DecodedInstruction) {
        let (major, minor) = into_major_minor(kind);
        self.trace.cycles.push(PreflightCycle::new(
            self.pc,
            true,
            self.mem_idx,
            self.extra_idx,
            major,
            minor,
        ));
        self.mem_idx = self.trace.txns.len();
        self.extra_idx = self.trace.extras.len();
        self.cycles += 1;
    }

    fn get_pc(&self) -> u32 {
        self.pc
    }

    fn set_pc(&mut self, addr: u32) {
        self.pc = addr;
    }

    fn load_register(&mut self, idx: usize) -> Result<u32> {
        self.load_u32((SYSTEM_START + idx) as u32)
    }

    fn store_register(&mut self, idx: usize, data: u32) -> Result<()> {
        if idx != 0 {
            tracing::trace!("store_reg: x{idx} <= 0x{data:08x}");
            self.store_u32((SYSTEM_START + idx) as u32, data)?;
        }
        Ok(())
    }

    fn load_memory(&mut self, addr: u32) -> Result<u32> {
        self.load_u32(addr)
    }

    fn store_memory(&mut self, addr: u32, data: u32) -> Result<()> {
        self.store_u32(addr, data)
    }
}

pub fn preflight_segment(segment: &Segment) -> Result<PreflightTrace> {
    let mut preflight = Preflight::new(segment);
    let mut emu = Emulator::new();

    preflight.pre_steps();
    while preflight.cycles < segment.insn_cycles {
        emu.step(&mut preflight)?;
    }
    preflight.post_steps()?;

    Ok(preflight.trace)
}
