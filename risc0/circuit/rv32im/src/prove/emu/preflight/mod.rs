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

use std::collections::VecDeque;

use anyhow::{anyhow, bail, ensure, Result};
use crypto_bigint::{CheckedMul as _, Encoding as _, NonZero, U256, U512};
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
        bigint, ecall, halt,
        reg_abi::{REG_A0, REG_A1, REG_A2, REG_A3, REG_A4, REG_T0},
        IO_CHUNK_WORDS,
    },
    WORD_SIZE,
};
use sha2::digest::generic_array::GenericArray;

use super::{
    mux::{Major, TopMux},
    pager::{PagedMemory, PAGE_WORDS},
    rv32im::{DecodedInstruction, EmuContext, Emulator, InsnKind, Instruction, TrapCause},
    ByteAddr, WordAddr, SHA_INIT, SHA_MAIN_FINI, SHA_MAIN_MIX, SYSTEM_START,
};
use crate::prove::{
    engine::loader::{
        FINI_CYCLES, RAM_LOAD_CYCLES, SETUP_CYCLES, SHA_INIT_OFFSET, SHA_K, SHA_K_OFFSET,
        ZEROS_OFFSET,
    },
    segment::{Segment, SyscallRecord},
};

const SHA_K_ADDR: WordAddr = ByteAddr(SHA_K_OFFSET as u32).waddr();

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

#[derive(Clone, Debug, PartialEq)]
pub struct PreflightCycle {
    pub mux: TopMux,
    pub back: Option<Back>,
    pub mem_idx: usize,
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
    syscalls: VecDeque<SyscallRecord>,
    input_digest: Digest,
}

impl PreflightCycle {
    fn new(mux: TopMux, back: Option<Back>, mem_idx: usize, extra_idx: usize) -> Self {
        Self {
            mux,
            back,
            mem_idx,
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
            syscalls: segment.syscalls.clone().into(),
            input_digest: segment.input_digest,
        }
    }

    fn load_u32(&mut self, addr: WordAddr) -> Result<u32> {
        let data = self.pager.load(addr);
        // tracing::trace!("load_u32({addr:?}) -> 0x{data:08x}");
        self.add_txn(false, addr, data);
        Ok(data)
    }

    fn store_u32(&mut self, addr: WordAddr, data: u32) -> Result<()> {
        // tracing::trace!("store_u32({addr:?}, 0x{data:08x})");
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
        for _ in 0..RAM_LOAD_CYCLES {
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

        // Emulate the page fault reads occurring before the body starts.
        for page_idx in faults.reads.iter().rev() {
            self.page_fault(true, /*is_read=*/ 1, *page_idx, /*is_done=*/ 0)?;
        }

        let (sys_exit_code, user_exit_code) = self
            .halted
            .map(|exit_code| {
                let exit_code_bytes = exit_code.to_le_bytes();
                (exit_code_bytes[0], exit_code_bytes[1])
            })
            .unwrap_or((halt::SPLIT as u8, 0));

        if sys_exit_code != halt::TERMINATE as u8 {
            // Emulate the page fault writes before a system split or a pause.
            for page_idx in faults.writes.iter() {
                self.page_fault(false, /*is_read=*/ 0, *page_idx, /*is_done=*/ 0)?;
            }
            if sys_exit_code == halt::SPLIT as u8 {
                self.page_fault(
                    false, /*is_read=*/ 0, /*page_idx=*/ 0, /*is_done=*/ 1,
                )?;
            }
        }

        if sys_exit_code != halt::SPLIT as u8 {
            if sys_exit_code == halt::PAUSE as u8 {
                self.load_u32(self.pc.waddr())?;
            }
            self.add_txn(false, SYSTEM_START + REG_T0, ecall::HALT);
            self.add_txn(false, SYSTEM_START + REG_A1, self.output_ptr.0);
            self.add_txn(false, SYSTEM_START + REG_A0, self.halted.unwrap());
            self.add_cycle(false, TopMux::Body(Major::ECall, 0));
            self.pc += WORD_SIZE;
        }

        let max_cycles = self.steps;
        let pre_cycles = self.trace.pre.cycles.len();
        let body_cycles = self.trace.body.cycles.len();
        let err = || {
            anyhow::anyhow!("Invalid execution trace. max: {max_cycles}, pre: {pre_cycles}, body: {body_cycles}")
        };
        let body_padding = max_cycles
            .checked_sub(pre_cycles)
            .ok_or_else(err)?
            .checked_sub(body_cycles)
            .ok_or_else(err)?
            .checked_sub(FINI_CYCLES + ZK_CYCLES)
            .ok_or_else(err)?;
        tracing::debug!("padding: {body_padding}, pre: {pre_cycles}, body: {body_cycles}");

        if body_padding > 0 {
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
        // tracing::trace!("pre_peek({addr:?}) -> 0x{data:08x}");
        self.trace.pre.add_txn(addr, data);
        Ok(())
    }

    fn peek(&self, addr: WordAddr) -> Result<u32> {
        let data = self.pager.peek(addr)?;
        // tracing::trace!("peek({addr:?}) -> 0x{data:08x}");
        Ok(data)
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
        tracing::debug!(
            "page_fault(0x{page_idx:05x}, {is_read}, {is_done}, {:?})",
            addr.baddr()
        );
        let page_words = if page_idx == info.root_idx {
            info.num_root_entries as usize * DIGEST_WORDS
        } else {
            PAGE_WORDS
        };
        let entry_addr = ByteAddr(info.get_page_entry_addr(page_idx)).waddr();
        self.sha_cycles(
            addr,
            addr + DIGEST_WORDS,
            ByteAddr(SHA_INIT_OFFSET as u32).waddr(),
            entry_addr,
            page_words / BLOCK_WORDS,
            pre,
            is_read == 1,
        )
    }

    #[allow(clippy::too_many_arguments)]
    fn sha_cycles(
        &mut self,
        block1_addr: WordAddr,
        block2_addr: WordAddr,
        sin_addr: WordAddr,
        sout_addr: WordAddr,
        repeat: usize,
        pre: bool,
        is_read: bool,
    ) -> Result<()> {
        let mut state: [u32; DIGEST_WORDS] =
            std::array::from_fn(|i| self.peek(sin_addr + i).unwrap().to_be());

        // SHA_INIT
        self.add_cycle(pre, TopMux::Body(Major::ShaInit, 0));
        for i in 1..SHA_INIT {
            let idx = SHA_INIT - i - 1;
            // idx: [3, 2, 1, 0]
            self.record_load(pre, sin_addr + idx)?;
            // idx: [7, 6, 5, 4]
            self.record_load(pre, sin_addr + idx + 4u32)?;
            self.add_cycle(pre, TopMux::Body(Major::ShaInit, 0));
        }

        for i in 0..repeat {
            if !is_read {
                let mut block = [0u32; BLOCK_WORDS];
                let (digest1, digest2) = block.split_at_mut(DIGEST_WORDS);
                for (j, word) in digest1.iter_mut().enumerate() {
                    *word = self.peek(block1_addr + i * BLOCK_WORDS + j)?;
                }
                for (j, word) in digest2.iter_mut().enumerate() {
                    *word = self.peek(block2_addr + i * BLOCK_WORDS + j)?;
                }

                sha2::compress256(
                    &mut state,
                    &[*GenericArray::from_slice(bytemuck::cast_slice(&block))],
                );
            }

            // SHA_LOAD
            for j in 0..DIGEST_WORDS {
                self.sha_load(pre, block1_addr + i * BLOCK_WORDS, 0, j)?;
            }
            for j in 0..DIGEST_WORDS {
                self.sha_load(pre, block2_addr + i * BLOCK_WORDS, 1, j)?;
            }

            // SHA_MAIN(mix)
            for j in 0..SHA_MAIN_MIX {
                self.add_txn(pre, SHA_K_ADDR + BLOCK_WORDS + j, SHA_K[BLOCK_WORDS + j]);
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

    fn sha_load(&mut self, pre: bool, block_addr: WordAddr, minor: u32, i: usize) -> Result<()> {
        // tracing::trace!("sha_load({:?}, {minor}, {i})", block_addr + i);
        let k_idx = minor as usize * DIGEST_WORDS + i;
        self.record_load(pre, block_addr + i)?;
        self.add_txn(pre, SHA_K_ADDR + k_idx, SHA_K[k_idx]);
        self.add_cycle(pre, TopMux::Body(Major::ShaLoad, minor));
        Ok(())
    }

    fn syscall_body(&mut self, chunk: &[u32], ptr: &mut WordAddr) -> Result<()> {
        for word in chunk {
            self.add_extra(false, *word);
            self.store_u32(*ptr, *word)?;
            *ptr += 1u32;
        }
        self.add_cycle(false, TopMux::Body(Major::ECallCopyIn, 0));
        Ok(())
    }

    fn syscall_fini(&mut self, a0: u32, a1: u32) -> Result<()> {
        self.add_extra(false, a0);
        self.add_extra(false, a1);
        self.store_register(REG_A0, a0)?;
        self.store_register(REG_A1, a1)?;
        self.add_cycle(false, TopMux::Body(Major::ECallCopyIn, 1));
        Ok(())
    }

    fn ecall_halt(&mut self) -> Result<bool> {
        tracing::trace!("ecall_halt");
        self.output_ptr = ByteAddr(self.peek_register(REG_A1)?);
        let exit_code = self.peek_register(REG_A0)?;
        self.halted = Some(exit_code);
        Ok(true)
    }

    fn ecall_input(&mut self) -> Result<bool> {
        self.load_register(REG_T0)?;
        let a0 = self.load_register(REG_A0)? as usize;
        ensure!(a0 < DIGEST_WORDS, "sys_input index out of range");
        let word = self.input_digest.as_words()[a0];
        self.store_register(REG_A0, word)?;

        self.add_cycle(false, TopMux::Body(Major::ECall, 0));

        self.pc += WORD_SIZE;
        Ok(true)
    }

    fn peek_register(&mut self, idx: usize) -> Result<u32> {
        self.peek(SYSTEM_START + idx)
    }

    fn ecall_software(&mut self) -> Result<bool> {
        let cycle = self.trace.body.cycles.len();
        self.load_register(REG_T0)?;
        let mut into_guest_ptr = ByteAddr(self.load_register(REG_A0)?).waddr();
        let into_guest_len = self.load_register(REG_A1)? as usize;

        let syscall = self
            .syscalls
            .pop_front()
            .ok_or(anyhow!("Missing syscall record"))?;
        let (a0, a1) = syscall.regs;

        let stray_words = into_guest_len % IO_CHUNK_WORDS;
        let (head, body) = syscall.to_guest.split_at(stray_words);

        // syscallInit
        self.add_cycle(false, TopMux::Body(Major::ECall, 0));

        if !head.is_empty() {
            self.syscall_body(head, &mut into_guest_ptr)?;
        }

        for chunk in body.chunks_exact(IO_CHUNK_WORDS) {
            self.syscall_body(chunk, &mut into_guest_ptr)?;
        }

        self.syscall_fini(a0, a1)?;

        tracing::debug!(
            "[{cycle}] ecall_software: {}",
            self.trace.body.cycles.len() - cycle
        );

        self.pc += WORD_SIZE;
        Ok(true)
    }

    fn ecall_sha(&mut self) -> Result<bool> {
        let cycle = self.trace.body.cycles.len();
        self.load_register(REG_T0)?;
        let state_out_ptr = ByteAddr(self.load_register(REG_A0)?).waddr();
        let state_in_ptr = ByteAddr(self.load_register(REG_A1)?).waddr();
        let count = self.load_register(REG_A4)? as usize;
        self.add_cycle(false, TopMux::Body(Major::ECall, 0));

        let block1_ptr = ByteAddr(self.load_register(REG_A2)?).waddr();
        let block2_ptr = ByteAddr(self.load_register(REG_A3)?).waddr();
        self.sha_cycles(
            block1_ptr,
            block2_ptr,
            state_in_ptr,
            state_out_ptr,
            count,
            false,
            false,
        )?;

        tracing::debug!(
            "[{cycle}] ecall_sha: {}",
            self.trace.body.cycles.len() - cycle
        );

        self.pc += WORD_SIZE;
        Ok(true)
    }

    fn peek_bigint(&mut self, idx: usize) -> Result<()> {
        let ptr = ByteAddr(self.load_register(idx)?).waddr();
        for i in 0..bigint::WIDTH_WORDS {
            self.load_u32(ptr + i)?;
        }
        Ok(())
    }

    fn ecall_bigint(&mut self) -> Result<bool> {
        const BIGINT_IO_SIZE: usize = 4;

        let cycle = self.trace.body.cycles.len();
        tracing::debug!("[{cycle}] ecall_bigint");

        self.load_register(REG_T0)?;
        self.load_register(REG_A1)?;
        self.add_cycle(false, TopMux::Body(Major::ECall, 0));

        let z_ptr = ByteAddr(self.load_register(REG_A0)?).waddr();
        let x_ptr = ByteAddr(self.load_register(REG_A2)?).waddr();
        let y_ptr = ByteAddr(self.load_register(REG_A3)?).waddr();
        let n_ptr = ByteAddr(self.load_register(REG_A4)?).waddr();
        tracing::debug!("bigint(z: {z_ptr:?}, x: {x_ptr:?}, y: {y_ptr:?}, n {n_ptr:?}");
        self.peek_bigint(REG_A2)?;
        self.peek_bigint(REG_A3)?;
        self.peek_bigint(REG_A4)?;
        self.add_cycle(false, TopMux::Body(Major::BigInt, 0));

        let mut n = [0u32; bigint::WIDTH_WORDS];
        let mut x = [0u32; bigint::WIDTH_WORDS];
        let mut y = [0u32; bigint::WIDTH_WORDS];

        let ptrs = [(n_ptr, &mut n), (x_ptr, &mut x), (y_ptr, &mut y)];

        // Load inputs.
        for (ptr, arr) in ptrs {
            for i in 0..2 {
                let offset = i * BIGINT_IO_SIZE;
                for j in 0..BIGINT_IO_SIZE {
                    let word = self.load_u32(ptr + offset + j)?;
                    arr[offset + j] = word.to_le();
                }
                self.peek_bigint(REG_A2)?;
                self.peek_bigint(REG_A3)?;
                self.peek_bigint(REG_A4)?;
                self.add_cycle(false, TopMux::Body(Major::BigInt, 0));
            }
        }

        let n = U256::from_le_bytes(bytemuck::cast(n));
        let x = U256::from_le_bytes(bytemuck::cast(x));
        let y = U256::from_le_bytes(bytemuck::cast(y));

        // Compute modular multiplication, or simply multiplication if n == 0.
        let z: U256 = if n == U256::ZERO {
            x.checked_mul(&y).unwrap()
        } else {
            let (w_lo, w_hi) = x.mul_wide(&y);
            let w = w_hi.concat(&w_lo);
            let z = w.rem(&NonZero::<U512>::from_uint(n.resize()));
            z.resize()
        };

        tracing::debug!("n: {n:?}, x: {x:?}, y: {y:?}, z: {z:?}");

        // Store result.
        let z: [u32; bigint::WIDTH_WORDS] = bytemuck::cast(z.to_le_bytes());
        for i in 0..2 {
            self.peek_bigint(REG_A2)?;
            self.peek_bigint(REG_A3)?;
            self.peek_bigint(REG_A4)?;

            let offset = i * BIGINT_IO_SIZE;
            for j in 0..BIGINT_IO_SIZE {
                let word = z[offset + j].to_le();
                self.store_u32(z_ptr + offset + j, word)?;
            }

            self.add_cycle(false, TopMux::Body(Major::BigInt, 0));
        }

        self.pc += WORD_SIZE;
        Ok(true)
    }
}

impl EmuContext for Preflight {
    fn ecall(&mut self) -> Result<bool> {
        // we use the pager load directly here so that we don't induce a memory
        // transaction but still cause the page to marked as loaded.
        match self.pager.load(SYSTEM_START + REG_T0) {
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
        bail!("Trap: {cause:08x?}");
    }

    fn on_insn_decoded(&self, insn: &Instruction, _decoded: &DecodedInstruction) {
        tracing::trace!("{:?}> {:?}", self.pc, insn.kind);
    }

    fn on_normal_end(&mut self, insn: &Instruction, _decoded: &DecodedInstruction) {
        match insn.kind {
            InsnKind::AND
            | InsnKind::ANDI
            | InsnKind::XOR
            | InsnKind::XORI
            | InsnKind::OR
            | InsnKind::ORI => {
                let mux: TopMux = insn.kind.into();
                let (_, minor) = mux.as_body().unwrap();
                self.add_par_cycle(false, mux, Back::Body { pc: self.prev_pc });
                self.add_cycle(false, TopMux::Body(Major::VerifyAnd, minor));
            }
            InsnKind::DIV
            | InsnKind::DIVU
            | InsnKind::REM
            | InsnKind::REMU
            | InsnKind::SRL
            | InsnKind::SRA
            | InsnKind::SRLI
            | InsnKind::SRAI => {
                let mux: TopMux = insn.kind.into();
                let (_, minor) = mux.as_body().unwrap();
                self.add_par_cycle(false, mux, Back::Body { pc: self.prev_pc });
                self.add_cycle(false, TopMux::Body(Major::VerifyDivide, minor));
            }
            InsnKind::EANY => {
                // cycles are added during ecall handlers
            }
            _ => {
                self.add_par_cycle(false, insn.kind.into(), Back::Body { pc: self.prev_pc });
            }
        }
        self.prev_pc = self.pc;
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
        tracing::debug!("preflight: {self:#?}");
        let mut preflight = Preflight::new(self);
        let mut emu = Emulator::new();

        preflight.pre_steps();
        while preflight.trace.body.cycles.len() < self.insn_cycles && preflight.halted.is_none() {
            emu.step(&mut preflight)?;
            preflight.pager.commit_step();
        }
        preflight.post_steps()?;

        Ok(preflight.trace)
    }
}
