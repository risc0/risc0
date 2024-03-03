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

use std::sync::atomic::{AtomicUsize, Ordering};

use anyhow::{anyhow, bail, Result};
use derive_debug::Dbg;
use risc0_zkp::{
    core::{
        digest::{Digest, DIGEST_WORDS},
        hash::sha::{BLOCK_WORDS, SHA256_INIT},
    },
    ZK_CYCLES,
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
    rv32im::{DecodedInstruction, EmuContext, Emulator, InsnKind, TrapCause},
    ByteAddr, Segment, WordAddr, SYSTEM_START,
};
use crate::prove::engine::loader::{
    ram_load_cycles, FINI_TAILROOM, SETUP_CYCLES, SHA_INIT_OFFSET, SHA_K, SHA_K_OFFSET,
};

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
    ECallCopyIn,
    BigInt,
    Halt,
    MuxSize,
}

#[derive(Clone, Debug, PartialEq)]
pub enum TopMux {
    BytesInit,
    BytesSetup,
    RamInit,
    RamLoad,
    Reset,
    Body(Major, u32),
    RamFini,
    BytesFini,
}

#[derive(Clone, Debug, PartialEq)]
pub enum Back {
    Null,
    Body {
        pc: ByteAddr,
    },
    Halt {
        pc: ByteAddr,
        exit_code: u32,
        write_addr: WordAddr,
    },
}

#[derive(Debug)]
pub struct PreflightCycle {
    pub mux: TopMux,
    pub back: Option<Back>,
    pub mem_idx: AtomicUsize,
    pub extra_idx: usize,
}

#[derive(Clone, Dbg, PartialEq)]
pub struct MemoryTransaction {
    pub cycle: usize,
    pub addr: WordAddr,
    #[dbg(fmt = "0x{:08x}")]
    pub data: u32,
}

#[derive(Clone, Default)]
pub struct PreflightStage {
    pub cycles: Vec<PreflightCycle>,
    pub txns: Vec<MemoryTransaction>,
    pub extras: Vec<u32>,
    pub mem_idx: usize,
    pub extra_idx: usize,
}

#[derive(Clone, Default)]
pub struct PreflightTrace {
    pub pre: PreflightStage,
    pub body: PreflightStage,
}

struct Preflight {
    steps: usize,
    pager: PagedMemory,
    pre_pc: ByteAddr,
    pc: ByteAddr,
    cycles: usize,
    pub trace: PreflightTrace,
    output_ptr: ByteAddr,
    pre_merkle_root: Digest,
}

impl Clone for PreflightCycle {
    fn clone(&self) -> Self {
        Self {
            mux: self.mux.clone(),
            back: self.back.clone(),
            mem_idx: AtomicUsize::new(self.mem_idx.load(Ordering::Relaxed)),
            extra_idx: self.extra_idx,
        }
    }
}

impl PartialEq for PreflightCycle {
    fn eq(&self, other: &Self) -> bool {
        self.mux == other.mux
            && self.back == other.back
            && self.mem_idx.load(Ordering::Relaxed) == other.mem_idx.load(Ordering::Relaxed)
            && self.extra_idx == other.extra_idx
    }
}

impl Major {
    pub fn as_u32(&self) -> u32 {
        *self as u32
    }
}

impl TopMux {
    pub fn as_body(&self) -> Result<(Major, u32)> {
        match self {
            TopMux::Body(major, minor) => Ok((*major, *minor)),
            _ => Err(anyhow!("TopMux::as_body invalid mux")),
        }
    }
}

impl InsnKind {
    fn major_minor(&self) -> (Major, u32) {
        match self {
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
            InsnKind::INVALID => (Major::MuxSize, 0),
        }
    }
}

impl From<InsnKind> for TopMux {
    fn from(kind: InsnKind) -> Self {
        let (major, minor) = kind.major_minor();
        TopMux::Body(major, minor)
    }
}

impl PreflightCycle {
    fn new(mux: TopMux, back: Option<Back>, mem_idx: usize, extra_idx: usize) -> Self {
        Self {
            mux,
            back,
            mem_idx: AtomicUsize::new(mem_idx),
            extra_idx,
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

impl PreflightStage {
    fn add_cycle(&mut self, mux: TopMux, back: Option<Back>) {
        self.cycles
            .push(PreflightCycle::new(mux, back, self.mem_idx, self.extra_idx));
        self.mem_idx = self.txns.len();
        self.extra_idx = self.extras.len();
    }

    fn add_txn(&mut self, addr: WordAddr, data: u32) {
        self.txns
            .push(MemoryTransaction::new(self.cycles.len(), addr, data));
    }

    fn add_extra(&mut self, value: u32) {
        self.extras.push(value);
    }
}

impl Preflight {
    fn new(segment: &Segment) -> Self {
        tracing::debug!("po2: {}", segment.po2);
        let pc = ByteAddr(segment.partial_image.pc);
        Self {
            steps: 1 << segment.po2,
            pager: PagedMemory::new(segment.partial_image.clone()),
            pre_pc: pc,
            pc,
            cycles: 0,
            trace: PreflightTrace::default(),
            output_ptr: ByteAddr(0),
            pre_merkle_root: segment.pre_state.merkle_root,
        }
    }

    fn load_u32(&mut self, addr: WordAddr) -> Result<u32> {
        let data = self.pager.load(addr)?;
        // tracing::trace!("load_u32: {:?} => 0x{data:08x}", addr.baddr(),);
        self.add_txn(false, addr, data);
        Ok(data)
    }

    fn store_u32(&mut self, addr: WordAddr, data: u32) -> Result<()> {
        // tracing::trace!("store_u32: {:?} <= 0x{data:08x}", addr.baddr());
        self.pager.store(addr, data)
    }

    fn add_cycle(&mut self, pre: bool, mux: TopMux) {
        let stage = if pre {
            &mut self.trace.pre
        } else {
            &mut self.trace.body
        };
        stage.add_cycle(mux, None);
    }

    fn add_par_cycle(&mut self, pre: bool, mux: TopMux, back: Back) {
        let stage = if pre {
            &mut self.trace.pre
        } else {
            &mut self.trace.body
        };
        stage.add_cycle(mux, Some(back));
    }

    fn add_txn(&mut self, pre: bool, addr: WordAddr, data: u32) {
        let stage = if pre {
            &mut self.trace.pre
        } else {
            &mut self.trace.body
        };
        stage.add_txn(addr, data);
    }

    fn add_extra(&mut self, pre: bool, value: u32) {
        let stage = if pre {
            &mut self.trace.pre
        } else {
            &mut self.trace.body
        };
        stage.add_extra(value);
    }

    fn pre_steps(&mut self) {
        // bytes_init
        self.add_par_cycle(true, TopMux::BytesInit, Back::Null);

        // bytes_setup+
        for _ in 0..SETUP_CYCLES {
            self.add_cycle(true, TopMux::BytesSetup);
        }

        // ram_init
        self.add_par_cycle(true, TopMux::RamInit, Back::Null);

        // ram_load+
        for _ in 0..ram_load_cycles().len() {
            self.add_par_cycle(true, TopMux::RamLoad, Back::Null);
        }

        // reset(0)
        self.add_cycle(true, TopMux::Reset);
        self.add_cycle(true, TopMux::Reset);
        let info = &self.pager.image.info;
        let bytes = self.pre_merkle_root.as_bytes();
        self.pager.image.store_region_in_page(info.root_addr, bytes)
    }

    fn post_steps(&mut self) -> Result<()> {
        let faults = self.pager.get_faults();

        // Emulate the page fault reads occuring before the body starts.
        for page_idx in faults.reads.iter().rev() {
            self.page_fault(true, /*is_read=*/ 1, *page_idx, /*isdone=*/ 0)?;
        }

        // Emulate the page fault writes occuring after a halt/pause.
        // let faults: Vec<u32> = self.trace.faults.reads.iter().rev().cloned().collect();
        // for page_idx in faults {
        //     self.page_fault(true, page_idx)?;
        // }

        let max_cycles = self.steps;
        let pre_cycles = self.trace.pre.cycles.len();
        let body_cycles = self.cycles;
        let body_padding = max_cycles - pre_cycles - body_cycles - FINI_TAILROOM - ZK_CYCLES;
        tracing::debug!("body_padding: {body_padding}, pre: {pre_cycles}, body: {body_cycles}");
        if body_padding > 1 {
            self.add_cycle(false, TopMux::Body(Major::Halt, 0));
        }
        for _ in 1..body_padding {
            self.add_par_cycle(
                false,
                TopMux::Body(Major::Halt, 0),
                Back::Halt {
                    pc: self.pc + 4u32,
                    exit_code: 0,
                    write_addr: self.output_ptr.waddr(),
                },
            );
        }

        // reset(1)
        self.reset_cycle(self.output_ptr.waddr())?;

        // reset(2)
        self.reset_cycle(ByteAddr(self.pager.image.info.root_addr).waddr())?;

        // ram_fini
        self.add_par_cycle(false, TopMux::RamFini, Back::Null);

        // bytes_fini
        self.add_par_cycle(false, TopMux::BytesFini, Back::Null);

        Ok(())
    }

    fn pre_peek(&mut self, addr: WordAddr) -> Result<()> {
        let data = self.pager.pre_peek(addr)?;
        self.trace.pre.add_txn(addr, data);
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

    fn reset_cycle(&mut self, addr: WordAddr) -> Result<()> {
        const HALF_DIGEST_WORDS: usize = DIGEST_WORDS / 2;
        for i in 0..2usize {
            for j in 0..HALF_DIGEST_WORDS {
                self.load_u32(addr + i * HALF_DIGEST_WORDS + j)?;
            }
            self.add_cycle(false, TopMux::Reset);
        }
        Ok(())
    }
}

// emulation of specific cycle types
impl Preflight {
    fn page_fault(&mut self, pre: bool, is_read: u32, page_idx: u32, is_done: u32) -> Result<()> {
        self.add_extra(pre, is_read);
        self.add_extra(pre, page_idx);
        self.add_extra(pre, is_done);
        self.add_par_cycle(
            pre,
            TopMux::Body(Major::PageFault, 0),
            Back::Body {
                pc: self.pre_pc + 4u32,
            },
        );
        if is_done == 1 {
            return Ok(());
        }

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
            pre,
        )
    }

    fn sha_buffer(
        &mut self,
        buf_addr: WordAddr,
        sin_addr: WordAddr,
        sout_addr: WordAddr,
        count: usize,
        pre: bool,
    ) -> Result<()> {
        const SHA_INIT: usize = 4;
        const SHA_LOAD: usize = 8;
        const SHA_MAIN_MIX: usize = 48;
        const SHA_MAIN_FINI: usize = 4;
        const SHA_K_ADDR: WordAddr = ByteAddr(SHA_K_OFFSET as u32).waddr();

        let repeat = count / BLOCK_WORDS;

        // SHA_INIT
        self.add_cycle(pre, TopMux::Body(Major::ShaInit, 0));
        for i in 0..SHA_INIT {
            let idx = SHA_INIT - i - 1;
            let data = SHA256_INIT.as_words()[idx];
            self.add_txn(pre, sin_addr + idx, data);

            let idx = DIGEST_WORDS - i - 1;
            let data = SHA256_INIT.as_words()[idx];
            self.add_txn(pre, sin_addr + idx, data);
            self.add_cycle(pre, TopMux::Body(Major::ShaInit, 0));
        }

        for i in 0..repeat {
            // SHA_LOAD
            for j in 0..2 {
                let offset = SHA_LOAD * j;
                for k in 0..SHA_LOAD {
                    self.record_load(pre, buf_addr + i * SHA_LOAD * 2 + offset + k)?;
                    self.add_txn(pre, SHA_K_ADDR + offset + k, SHA_K[offset + k]);
                    self.add_cycle(pre, TopMux::Body(Major::ShaLoad, j as u32));
                }
            }

            // SHA_MAIN(mix)
            for j in 0..SHA_MAIN_MIX {
                self.add_txn(pre, SHA_K_ADDR + SHA_LOAD * 2 + j, SHA_K[SHA_LOAD * 2 + j]);
                self.add_cycle(pre, TopMux::Body(Major::ShaMain, 0));
            }

            // SHA_MAIN(fini)
            for j in 0..SHA_MAIN_FINI {
                if i == repeat - 1 {
                    self.record_load(pre, sout_addr + (SHA_MAIN_FINI - j - 1))?;
                    self.record_load(pre, sout_addr + (SHA_MAIN_FINI - j - 1) + SHA_MAIN_FINI)?;
                    self.add_cycle(pre, TopMux::Body(Major::ShaMain, 1));
                } else {
                    self.add_cycle(pre, TopMux::Body(Major::ShaMain, 1));
                }
            }
        }

        Ok(())
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
}

impl EmuContext for Preflight {
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
        tracing::trace!("{:?}> {kind:?}", self.pc);
    }

    fn on_normal_end(&mut self, kind: InsnKind, _decoded: &DecodedInstruction) {
        if kind == InsnKind::EANY {
            self.add_cycle(false, kind.into());
        } else {
            self.add_par_cycle(false, kind.into(), Back::Body { pc: self.pc });
        }
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
            // tracing::trace!("store_reg: x{idx} <= 0x{data:08x}");
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

#[tracing::instrument(skip_all)]
pub fn preflight_segment(segment: &Segment) -> Result<PreflightTrace> {
    tracing::debug!("preflight_segment: {segment:?}");
    let mut preflight = Preflight::new(segment);
    let mut emu = Emulator::new();

    preflight.pre_steps();
    while preflight.cycles < segment.insn_cycles {
        emu.step(&mut preflight)?;
    }
    preflight.post_steps()?;

    Ok(preflight.trace)
}
