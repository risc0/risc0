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

use std::collections::BTreeSet;

use anyhow::{bail, Result};
use derive_debug::Dbg;
use risc0_zkp::core::{
    digest::{Digest, DIGEST_WORDS},
    hash::sha::{BLOCK_WORDS, SHA256_INIT},
};
use risc0_zkvm_platform::{
    syscall::{
        ecall,
        reg_abi::{REG_A0, REG_A1, REG_T0},
    },
    WORD_SIZE,
};

use super::{
    pager::{PagedMemory, PAGE_WORDS},
    rv32im::{DecodedInstruction, EmuConext, Emulator, InsnKind, TrapCause},
    ByteAddr, Segment, WordAddr, SYSTEM_START,
};
use crate::prove::engine::loader::{SHA_INIT_OFFSET, SHA_K, SHA_K_OFFSET, SHA_K_SIZE};

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
    pc: ByteAddr,
    is_valid: bool,
    mem_idx: usize,
    extra_idx: usize,
    pub major: Major,
    pub minor: u32,
}

#[derive(Clone, Dbg, PartialEq)]
pub struct MemoryTransaction {
    pub cycle: usize,
    pub addr: WordAddr,
    #[dbg(fmt = "0x{:08x}")]
    pub data: u32,
}

#[derive(Clone, Default, Debug)]
pub struct PageFaults {
    pub reads: BTreeSet<u32>,
    pub writes: BTreeSet<u32>,
}

#[derive(Default)]
pub struct PreflightStage {
    pub cycles: Vec<PreflightCycle>,
    pub txns: Vec<MemoryTransaction>,
    extras: Vec<u32>,
}

#[derive(Default)]
pub struct PreflightTrace {
    pub pre: PreflightStage,
    pub body: PreflightStage,
    pub post: PreflightStage,
    pub faults: PageFaults,
}

struct Preflight {
    pager: PagedMemory,
    pc: ByteAddr,
    cycles: usize,
    pub trace: PreflightTrace,
    mem_idx: usize,
    extra_idx: usize,
    output_ptr: ByteAddr,
    pre_merkle_root: Digest,
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
        pc: ByteAddr,
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
    fn new<A: Into<WordAddr>>(cycle: usize, addr: A, data: u32) -> Self {
        Self {
            cycle,
            addr: addr.into(),
            data,
        }
    }
}

impl Preflight {
    fn new(segment: &Segment) -> Self {
        let pc = ByteAddr(segment.partial_image.pc);

        Self {
            pager: PagedMemory::new(segment.partial_image.clone()),
            pc,
            cycles: 0,
            trace: PreflightTrace::default(),
            mem_idx: 0,
            extra_idx: 0,
            output_ptr: ByteAddr(0),
            pre_merkle_root: segment.pre_state.merkle_root,
        }
    }

    fn ecall_halt(&mut self) -> Result<bool> {
        self.output_ptr = ByteAddr(self.load_register(REG_A1)?);
        self.load_register(REG_A0)?;
        Ok(true)
    }

    fn ecall_software(&mut self) -> Result<bool> {
        self.pc += WORD_SIZE;
        Ok(true)
    }

    fn ecall_sha(&mut self) -> Result<bool> {
        self.pc += WORD_SIZE;
        todo!()
    }

    fn ecall_bigint(&mut self) -> Result<bool> {
        self.pc += WORD_SIZE;
        todo!()
    }

    fn load_u32(&mut self, addr: WordAddr) -> Result<u32> {
        let data = self.pager.load(addr)?;
        tracing::debug!("load_u32: {:?} => 0x{data:08x}", addr.baddr(),);
        self.trace
            .body
            .txns
            .push(MemoryTransaction::new(self.cycles, addr, data));
        Ok(data)
    }

    fn store_u32(&mut self, addr: WordAddr, data: u32) -> Result<()> {
        tracing::debug!("store_u32: {:?} <= 0x{data:08x}", addr.baddr());
        // self.trace
        //     .txns
        //     .push(MemoryTransaction::new(self.cycles, addr, data));
        self.pager.store(addr, data)
    }

    fn pre_steps(&mut self) {
        let info = &self.pager.image.info;
        let bytes = self.pre_merkle_root.as_bytes();
        self.pager.image.store_region_in_page(info.root_addr, bytes)
    }

    fn post_steps(&mut self) -> Result<()> {
        // RESET(1)
        let addr = self.output_ptr.waddr();
        for i in 0..DIGEST_WORDS {
            self.load_u32(addr + i)?;
        }

        // RESET(2)
        let root_addr = ByteAddr(self.pager.image.info.root_addr).waddr();
        for i in 0..DIGEST_WORDS {
            self.load_u32(root_addr + i)?;
        }

        self.trace.faults = self.pager.get_faults();

        // Emulate the page fault reads occuring before the body starts.
        let faults: Vec<u32> = self.trace.faults.reads.iter().rev().cloned().collect();
        for page_idx in faults {
            let info = &self.pager.image.info;
            let addr = ByteAddr(info.get_page_addr(page_idx)).waddr();
            let page_words = if page_idx == info.root_idx {
                info.num_root_entries as usize * DIGEST_WORDS
            } else {
                PAGE_WORDS
            };
            let entry_addr = ByteAddr(info.get_page_entry_addr(page_idx)).waddr();
            self.sha_buffer(
                addr,
                ByteAddr(SHA_INIT_OFFSET as u32).waddr(),
                entry_addr,
                page_words,
                true,
            )?;
        }

        Ok(())
    }

    fn pre_peek(&mut self, addr: WordAddr) -> Result<()> {
        let data = self.pager.pre_peek(addr)?;
        self.trace
            .pre
            .txns
            .push(MemoryTransaction::new(0, addr, data));
        Ok(())
    }

    fn record_load(&mut self, pre: bool, addr: WordAddr) -> Result<()> {
        if pre {
            self.pre_peek(addr)
        } else {
            self.load_u32(addr)?;
            Ok(())
        }
    }

    fn record_load_imm(&mut self, pre: bool, addr: WordAddr, data: u32) {
        if pre {
            self.trace
                .pre
                .txns
                .push(MemoryTransaction::new(0, addr, data));
        } else {
            self.trace
                .body
                .txns
                .push(MemoryTransaction::new(0, addr, data));
        }
    }

    fn sha_buffer(
        &mut self,
        buf_addr: WordAddr,
        sin_addr: WordAddr,
        sout_addr: WordAddr,
        count: usize,
        pre: bool,
    ) -> Result<()> {
        const HALF_DIGEST_WORDS: usize = DIGEST_WORDS / 2;
        const SHA_INIT: usize = 4;
        const SHA_LOAD: usize = 16;
        const SHA_MIX: usize = SHA_K_SIZE - SHA_LOAD;
        const SHA_K_ADDR: WordAddr = ByteAddr(SHA_K_OFFSET as u32).waddr();

        let repeat = count / BLOCK_WORDS;

        // SHA_INIT
        for i in 0..SHA_INIT {
            let idx = SHA_INIT - i - 1;
            let data = SHA256_INIT.as_words()[idx];
            self.record_load_imm(pre, sin_addr + idx, data);

            let idx = DIGEST_WORDS - i - 1;
            let data = SHA256_INIT.as_words()[idx];
            self.record_load_imm(pre, sin_addr + idx, data);
        }

        for i in 0..repeat {
            // SHA_LOAD
            for j in 0..SHA_LOAD {
                self.record_load(pre, buf_addr + i * SHA_LOAD + j)?;
                self.record_load_imm(pre, SHA_K_ADDR + j, SHA_K[j]);
            }

            // SHA_MAIN(mix)
            for j in 0..SHA_MIX {
                self.record_load_imm(pre, SHA_K_ADDR + SHA_LOAD + j, SHA_K[SHA_LOAD + j]);
            }
        }

        // SHA_MAIN(fini)
        for i in 0..HALF_DIGEST_WORDS {
            self.record_load(pre, sout_addr + (HALF_DIGEST_WORDS - i - 1))?;
            self.record_load(pre, sout_addr + (DIGEST_WORDS - i - 1))?;
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
        tracing::debug!("{:?}> {kind:?}", self.pc);
    }

    fn on_normal_end(&mut self, kind: InsnKind, _decoded: &DecodedInstruction) {
        let (major, minor) = into_major_minor(kind);
        self.trace.body.cycles.push(PreflightCycle::new(
            self.pc,
            true,
            self.mem_idx,
            self.extra_idx,
            major,
            minor,
        ));
        self.mem_idx = self.trace.body.txns.len();
        self.extra_idx = self.trace.body.extras.len();
        self.cycles += 1;
    }

    fn get_pc(&self) -> ByteAddr {
        self.pc
    }

    fn set_pc(&mut self, addr: ByteAddr) {
        self.pc = addr;
    }

    fn load_register(&mut self, idx: usize) -> Result<u32> {
        self.load_u32(SYSTEM_START + idx)
    }

    fn store_register(&mut self, idx: usize, data: u32) -> Result<()> {
        if idx != 0 {
            tracing::trace!("store_reg: x{idx} <= 0x{data:08x}");
            self.store_u32(SYSTEM_START + idx, data)?;
        }
        Ok(())
    }

    fn load_memory(&mut self, addr: WordAddr) -> Result<u32> {
        self.load_u32(addr)
    }

    fn store_memory(&mut self, addr: WordAddr, data: u32) -> Result<()> {
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
