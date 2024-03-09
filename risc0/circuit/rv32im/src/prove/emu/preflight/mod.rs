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

use anyhow::{bail, Result};
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
        ecall, halt,
        reg_abi::{REG_A0, REG_A1, REG_T0},
    },
    WORD_SIZE,
};
use sha2::digest::generic_array::GenericArray;

use super::{
    mux::{Major, TopMux},
    pager::{PagedMemory, PAGE_WORDS},
    rv32im::{DecodedInstruction, EmuContext, Emulator, InsnKind, Instruction, TrapCause},
    ByteAddr, WordAddr, SYSTEM_START,
};
use crate::prove::{
    engine::loader::{
        ram_load_cycles, FINI_TAILROOM, SETUP_CYCLES, SHA_INIT_OFFSET, SHA_K, SHA_K_OFFSET,
        ZEROS_OFFSET,
    },
    segment::Segment,
};

#[derive(Clone, Debug, PartialEq)]
pub enum Back {
    Null,
    Body {
        pc: ByteAddr,
    },
    Halt {
        pc: ByteAddr,
        sys_exit_code: u8,
        user_exit_code: u8,
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
    start_pc: ByteAddr,
    prev_pc: ByteAddr,
    pc: ByteAddr,
    pub trace: PreflightTrace,
    output_ptr: ByteAddr,
    pre_merkle_root: Digest,
    halted: Option<u32>,
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
            start_pc: pc,
            prev_pc: pc,
            pc,
            trace: PreflightTrace::default(),
            output_ptr: ByteAddr(ZEROS_OFFSET as u32),
            pre_merkle_root: segment.pre_state.merkle_root,
            halted: None,
        }
    }

    #[allow(unused)]
    fn cur_cycle(&self) -> usize {
        self.trace.pre.cycles.len() + self.trace.body.cycles.len()
    }

    fn load_u32(&mut self, addr: WordAddr) -> Result<u32> {
        let data = self.pager.load(addr)?;
        // tracing::trace!("[{}] load_u32: {addr:?} => 0x{data:08x}", self.cur_cycle());
        self.add_txn(false, addr, data);
        Ok(data)
    }

    fn store_u32(&mut self, addr: WordAddr, data: u32) -> Result<()> {
        // tracing::trace!("[{}] store_u32: {addr:?} <= 0x{data:08x}", self.cur_cycle());
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

        for (i, word) in SHA_K.iter().enumerate() {
            self.pager
                .image
                .store_region_in_page((SHA_K_OFFSET + i * WORD_SIZE) as u32, &word.to_le_bytes());
        }

        for (i, word) in SHA256_INIT.as_words().iter().enumerate() {
            self.pager.image.store_region_in_page(
                (SHA_INIT_OFFSET + i * WORD_SIZE) as u32,
                &word.to_le_bytes(),
            );
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
            self.page_fault(true, /*is_read=*/ 1, *page_idx, /*is_done=*/ 0)?;
        }

        let max_cycles = self.steps;
        let pre_cycles = self.trace.pre.cycles.len();

        if let Some(exit_code) = self.halted {
            let body_cycles = self.trace.body.cycles.len();
            let body_padding = max_cycles - pre_cycles - body_cycles - FINI_TAILROOM - ZK_CYCLES;
            tracing::debug!("halt padding: {body_padding}, pre: {pre_cycles}, body: {body_cycles}");

            let exit_code_bytes = exit_code.to_le_bytes();
            let (sys_exit_code, user_exit_code) = (exit_code_bytes[0], exit_code_bytes[1]);
            if body_padding > 1 {
                self.add_cycle(false, TopMux::Body(Major::Halt, 0));
            }
            for _ in 1..body_padding {
                self.add_par_cycle(
                    false,
                    TopMux::Body(Major::Halt, 0),
                    Back::Halt {
                        pc: self.pc,
                        sys_exit_code,
                        user_exit_code,
                        write_addr: self.output_ptr.waddr(),
                    },
                );
            }
        } else {
            // Emulate the page fault writes before a system split.
            for page_idx in faults.writes.iter() {
                //.take(faults.writes.len() - 1) {
                self.page_fault(false, /*is_read=*/ 0, *page_idx, /*is_done=*/ 0)?;
            }
            let last_page_idx = faults.writes.last().unwrap();
            self.page_fault(
                false,
                /*is_read=*/ 0,
                *last_page_idx,
                /*is_done=*/ 1,
            )?;

            // let body_cycles = self.cycles;
            let body_cycles = self.trace.body.cycles.len();
            let body_padding = max_cycles - pre_cycles - body_cycles - FINI_TAILROOM - ZK_CYCLES;
            tracing::debug!(
                "fault padding: {body_padding}, pre: {pre_cycles}, body: {body_cycles}"
            );
            if body_padding > 1 {
                self.add_cycle(false, TopMux::Body(Major::Halt, 0));
            }
            for _ in 1..body_padding {
                self.add_par_cycle(
                    false,
                    TopMux::Body(Major::Halt, 0),
                    Back::Halt {
                        pc: self.pc,
                        sys_exit_code: halt::SPLIT as u8,
                        user_exit_code: 0,
                        write_addr: self.output_ptr.waddr(),
                    },
                );
            }
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
        let pc = if pre { self.start_pc } else { self.prev_pc };
        self.add_extra(pre, is_read);
        self.add_extra(pre, page_idx);
        self.add_extra(pre, is_done);
        self.add_par_cycle(pre, TopMux::Body(Major::PageFault, 0), Back::Body { pc });
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
            is_read == 1,
        )
    }

    fn sha_buffer(
        &mut self,
        buf_addr: WordAddr,
        sin_addr: WordAddr,
        sout_addr: WordAddr,
        count: usize,
        pre: bool,
        is_read: bool,
    ) -> Result<()> {
        const SHA_INIT: usize = 4;
        const SHA_LOAD: usize = 8;
        const SHA_MAIN_MIX: usize = 48;
        const SHA_MAIN_FINI: usize = 4;
        const SHA_K_ADDR: WordAddr = ByteAddr(SHA_K_OFFSET as u32).waddr();

        let repeat = count / BLOCK_WORDS;

        let mut state: [u32; DIGEST_WORDS] =
            std::array::from_fn(|i| self.pager.peek(sin_addr + i).unwrap().to_be());

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
            if !is_read {
                let block: [u32; BLOCK_WORDS] = std::array::from_fn(|j| {
                    self.pager.peek(buf_addr + i * BLOCK_WORDS + j).unwrap()
                });

                sha2::compress256(
                    &mut state,
                    &[*GenericArray::from_slice(bytemuck::cast_slice(&block))],
                );
            }

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
                    let offset = SHA_MAIN_FINI - j - 1;
                    if is_read {
                        self.record_load(pre, sout_addr + offset)?;
                        self.record_load(pre, sout_addr + offset + SHA_MAIN_FINI)?;
                    } else {
                        self.store_u32(sout_addr + offset, state[offset].to_be())?;
                        self.store_u32(
                            sout_addr + offset + SHA_MAIN_FINI,
                            state[offset + SHA_MAIN_FINI].to_be(),
                        )?;
                    }
                }
                self.add_cycle(pre, TopMux::Body(Major::ShaMain, 1));
            }
        }

        Ok(())
    }

    fn ecall_halt(&mut self) -> Result<bool> {
        self.output_ptr = ByteAddr(self.load_register(REG_A1)?);
        self.halted = Some(self.load_register(REG_A0)?);
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

    fn on_insn_decoded(&self, insn: &Instruction, _decoded: &DecodedInstruction) {
        tracing::trace!("{:?}> {:?}", self.pc, insn.kind);
    }

    fn on_normal_end(&mut self, insn: &Instruction, _decoded: &DecodedInstruction) {
        if insn.cycles == 2 {
            self.add_par_cycle(false, insn.kind.into(), Back::Body { pc: self.prev_pc });
            self.add_cycle(false, insn.kind.into());
        } else if insn.kind == InsnKind::EANY {
            self.add_cycle(false, insn.kind.into());
        } else {
            self.add_par_cycle(false, insn.kind.into(), Back::Body { pc: self.prev_pc });
        }
        self.prev_pc = self.pc
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

impl Segment {
    #[tracing::instrument(skip_all)]
    pub fn preflight(&self) -> Result<PreflightTrace> {
        tracing::debug!("preflight: {self:?}");
        let mut preflight = Preflight::new(self);
        let mut emu = Emulator::new();

        preflight.pre_steps();
        while preflight.trace.body.cycles.len() < self.insn_cycles {
            emu.step(&mut preflight)?;
        }
        preflight.post_steps()?;

        Ok(preflight.trace)
    }
}
