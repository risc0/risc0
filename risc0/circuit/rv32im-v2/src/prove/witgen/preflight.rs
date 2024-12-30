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

use anyhow::{anyhow, bail, Result};
use derive_more::Debug;
use num_traits::FromPrimitive as _;
use risc0_binfmt::ExitCode;
use risc0_circuit_rv32im_v2_sys::{RawMemoryTransaction, RawPreflightCycle};
use risc0_core::scope;
use risc0_zkp::core::digest::DIGEST_WORDS;

use crate::{
    execute::{
        addr::{ByteAddr, WordAddr},
        node_idx_to_addr,
        pager::PagedMemory,
        platform::*,
        poseidon2::{self, Checksum, Poseidon2State},
        r0vm::{Risc0Context, Risc0Machine},
        rv32im::{DecodedInstruction, Emulator, InsnKind, Instruction},
        segment::Segment,
        sha2::Sha2State,
    },
    zirgen::circuit::ExtVal,
};

use super::{node_addr_to_idx, paged_map::PagedMap};

#[derive(Clone, Debug, Default)]
pub(crate) enum Back {
    #[default]
    None,
    Ecall(u32, u32, u32),
    #[debug("Poseidon2")]
    Poseidon2(Poseidon2State),
    #[debug("Sha2")]
    Sha2(Sha2State),
}

#[derive(Clone, Debug, Default)]
pub(crate) struct PreflightTrace {
    #[debug("{}", cycles.len())]
    pub cycles: Vec<RawPreflightCycle>,
    #[debug("{}", txns.len())]
    pub txns: Vec<RawMemoryTransaction>,
    #[debug("{}", backs.len())]
    pub backs: Vec<Back>,
    pub table_split_cycle: u32,
    pub rand_z: ExtVal,
}

pub(crate) struct Preflight<'a> {
    pub trace: PreflightTrace,
    segment: &'a Segment,
    pager: PagedMemory,
    pc: ByteAddr,
    machine_mode: u32,
    cur_write: usize,
    cur_read: usize,
    user_cycle: u32,
    txn_idx: u32,
    phys_cycles: u32,
    orig_words: PagedMap,
    prev_cycle: PagedMap,
    page_memory: PagedMap,
}

impl Segment {
    pub(crate) fn preflight(&self, rand_z: ExtVal) -> Result<PreflightTrace> {
        scope!("preflight");
        tracing::debug!("preflight: {self:#?}");

        let mut preflight = Preflight::new(self, rand_z);
        preflight.read_pages()?;
        preflight.body()?;
        preflight.write_pages()?;
        preflight.generate_tables()?;
        preflight.padding()?;
        preflight.wrap_memory_txns()?;
        preflight.update_p2_zcheck()?;

        tracing::trace!("paging_cycles: {}", preflight.pager.cycles);

        Ok(preflight.trace)
    }
}

fn get_digest_addr(idx: u32) -> WordAddr {
    MERKLE_TREE_START_ADDR + DIGEST_WORDS as u32 * (2 * MEMORY_PAGES as u32 - idx)
}

impl<'a> Preflight<'a> {
    fn new(segment: &'a Segment, rand_z: ExtVal) -> Self {
        tracing::debug!("po2: {}", segment.po2);
        let total_cycles = 1 << segment.po2;

        let mut page_memory = PagedMap::default();
        for (&node_idx, digest) in segment.partial_image.digests.iter() {
            let node_addr = node_idx_to_addr(node_idx);
            for i in 0..DIGEST_WORDS {
                page_memory.insert(&(node_addr + i), digest.as_words()[i]);
            }
        }
        Self {
            trace: PreflightTrace {
                cycles: Vec::with_capacity(total_cycles),
                backs: Vec::with_capacity(total_cycles),
                rand_z,
                ..Default::default()
            },
            segment,
            pager: PagedMemory::new(segment.partial_image.clone()),
            pc: ByteAddr(0),
            machine_mode: 0,
            cur_write: 0,
            cur_read: 0,
            txn_idx: 0,
            user_cycle: 0,
            phys_cycles: 0,
            orig_words: Default::default(),
            prev_cycle: Default::default(),
            page_memory,
        }
    }

    // Do page in
    pub fn read_pages(&mut self) -> Result<()> {
        self.read_root()?;
        let activity = self.pager.loaded_pages();
        poseidon2::read_start(self)?;
        for node_idx in activity.nodes {
            poseidon2::read_node(self, node_idx)?;
        }
        self.machine_mode = 1;
        for page_idx in activity.pages {
            poseidon2::read_page(self, page_idx)?;
        }
        self.machine_mode = 2;
        poseidon2::read_done(self)?;
        self.phys_cycles = 0;
        Ok(())
    }

    // Run main execution
    pub fn body(&mut self) -> Result<()> {
        let mut emu = Emulator::new();
        Risc0Machine::resume(self)?;
        while self.phys_cycles < self.segment.suspend_cycle {
            Risc0Machine::step(&mut emu, self)?;
        }
        Risc0Machine::suspend(self)
    }

    // Do page out
    pub fn write_pages(&mut self) -> Result<()> {
        let activity = self.pager.dirty_pages();
        self.pager.commit()?;
        poseidon2::write_start(self)?;
        for &page_idx in activity.pages.iter().rev() {
            poseidon2::write_page(self, page_idx)?;
        }
        self.machine_mode = 4;
        for &node_idx in activity.nodes.iter().rev() {
            poseidon2::write_node(self, node_idx)?;
        }
        self.machine_mode = 5;
        poseidon2::write_done(self)?;
        self.machine_mode = 0;
        self.write_root()
    }

    // Do table reification
    pub fn generate_tables(&mut self) -> Result<()> {
        self.trace.table_split_cycle = self.trace.cycles.len() as u32;
        self.fini()
    }

    pub fn padding(&mut self) -> Result<()> {
        let last_cycle = 1 << self.segment.po2;
        for _ in self.trace.cycles.len()..last_cycle {
            self.add_cycle_special(
                CycleState::ControlDone,
                CycleState::ControlDone,
                0,
                0,
                Back::None,
            );
        }
        Ok(())
    }

    // Now, go back and update memory transactions to wrap around
    fn wrap_memory_txns(&mut self) -> Result<()> {
        for txn in self.trace.txns.iter_mut() {
            // tracing::trace!("{txn:?}");
            let addr = WordAddr(txn.addr);
            if txn.prev_cycle == u32::MAX {
                // If first cycle for a particular address, set 'prev_cycle' to final cycle
                txn.prev_cycle = self.prev_cycle.get(&addr).unwrap();
            } else {
                // Otherwise, compute cycle diff and another diff
                let diff = txn.cycle - txn.prev_cycle;
                self.trace.cycles[(diff / 2) as usize].diff_count[(diff % 2) as usize] += 1;
            }

            // If last cycle, set final value to original value
            if txn.cycle == self.prev_cycle.get(&addr).unwrap() {
                txn.word = self.orig_words.get(&addr).unwrap_or_default();
            }
        }
        Ok(())
    }

    fn update_p2_zcheck(&mut self) -> Result<()> {
        let mut checksum = Checksum::new(&self.trace.rand_z);
        for (row, back) in self.trace.backs.iter_mut().enumerate() {
            if let Back::Poseidon2(p2_state) = back {
                let cycle = &self.trace.cycles[row];
                let next_cycle = &self.trace.cycles[row + 1];
                let state = CycleState::from_u32((cycle.major as u32 - 7) * 8 + cycle.minor as u32)
                    .unwrap();
                if state == CycleState::PoseidonLoadIn {
                    checksum.start();
                    for (i, txn_idx) in (cycle.txn_idx..next_cycle.txn_idx).enumerate() {
                        let txn = &self.trace.txns[txn_idx as usize];
                        checksum.add(p2_state.load_tx_type, i, txn);
                    }
                }
                match state {
                    CycleState::PoseidonLoadIn
                    | CycleState::PoseidonExtRound
                    | CycleState::PoseidonIntRound => {
                        p2_state.zcheck = checksum.zcheck;
                    }
                    _ => {
                        checksum.clear();
                    }
                }
            }
        }

        Ok(())
    }

    fn fini(&mut self) -> Result<()> {
        for i in (16..256).step_by(16) {
            self.add_cycle_special(
                CycleState::ControlTable,
                CycleState::ControlTable,
                i,
                0,
                Back::None,
            );
        }
        self.machine_mode = 1;
        for i in (0..64 * 1024).step_by(16) {
            self.add_cycle_special(
                CycleState::ControlTable,
                CycleState::ControlTable,
                i,
                0,
                Back::None,
            );
        }
        self.machine_mode = 0;
        self.add_cycle_special(
            CycleState::ControlTable,
            CycleState::ControlDone,
            0,
            0,
            Back::None,
        );
        if !matches!(self.segment.exit_code, ExitCode::Halted(_)) {
            let segment_threshold = self.segment.segment_threshold as usize;
            if self.trace.cycles.len() < segment_threshold {
                bail!("Stopping segment too early");
            }
            let diff = self.trace.cycles.len() - segment_threshold;
            self.trace.cycles[diff / 2].diff_count[diff % 2] += 1;
        }
        self.machine_mode = 1;
        self.add_cycle_special(
            CycleState::ControlDone,
            CycleState::ControlDone,
            0,
            0,
            Back::None,
        );
        Ok(())
    }

    fn read_root(&mut self) -> Result<()> {
        let addr = get_digest_addr(1);
        for i in 0..DIGEST_WORDS {
            self.load_u32(addr + i)?;
        }
        self.add_cycle_special(
            CycleState::LoadRoot,
            CycleState::PoseidonEntry,
            0,
            0,
            Back::None,
        );
        Ok(())
    }

    fn write_root(&mut self) -> Result<()> {
        let addr = get_digest_addr(1);
        for i in 0..DIGEST_WORDS {
            self.load_u32(addr + i)?;
        }
        self.add_cycle_special(
            CycleState::StoreRoot,
            CycleState::ControlTable,
            0,
            0,
            Back::None,
        );
        Ok(())
    }

    fn add_cycle(
        &mut self,
        state: CycleState,
        pc: u32,
        major: u8,
        minor: u8,
        paging_idx: u32,
        back: Back,
    ) {
        let cycle = RawPreflightCycle {
            state: state as u32,
            pc,
            major,
            minor,
            machine_mode: self.machine_mode as u8,
            padding: 0,
            user_cycle: self.user_cycle,
            txn_idx: self.txn_idx,
            paging_idx,
            diff_count: [0, 0],
        };
        // tracing::trace!("[{}]: {cycle:?}", self.trace.cycles.len());
        self.trace.cycles.push(cycle);
        self.trace.backs.push(back);
        self.txn_idx = self.trace.txns.len() as u32;
    }

    fn add_cycle_insn(&mut self, state: CycleState, pc: u32, insn: InsnKind) {
        tracing::trace!("[{}]: {pc:#010x}> {insn:?}", self.trace.cycles.len());
        match insn {
            InsnKind::Eany => {
                // Technically we need to switch on the machine mode *entering* the EANY
                if self.trace.cycles.last().unwrap().machine_mode != 0 {
                    self.add_cycle(
                        state,
                        pc,
                        major::ECALL0,
                        ecall_minor::MACHINE_ECALL,
                        0,
                        Back::None,
                    );
                } else {
                    self.add_cycle(
                        state,
                        pc,
                        major::CONTROL0,
                        control_minor::USER_ECALL,
                        0,
                        Back::None,
                    );
                }
            }
            InsnKind::Mret => {
                self.add_cycle(
                    state,
                    pc,
                    major::CONTROL0,
                    control_minor::MRET,
                    0,
                    Back::None,
                );
            }
            _ => {
                self.add_cycle(state, pc, insn.major(), insn.minor(), 0, Back::None);
            }
        }
    }

    fn add_cycle_special(
        &mut self,
        cur_state: CycleState,
        next_state: CycleState,
        pc: u32,
        paging_idx: u32,
        back: Back,
    ) {
        let cur_state = cur_state as u32;
        let major = (7 + cur_state / 8) as u8;
        let minor = (cur_state % 8) as u8;
        // tracing::trace!("add_cycle_special(cur_state: {cur_state}, next_state: {next_state}, major: {major}, minor: {minor})");
        self.add_cycle(next_state, pc, major, minor, paging_idx, back);
    }
}

impl<'a> Risc0Context for Preflight<'a> {
    fn get_pc(&self) -> ByteAddr {
        self.pc
    }

    fn set_pc(&mut self, addr: ByteAddr) {
        self.pc = addr;
    }

    fn set_user_pc(&mut self, _addr: ByteAddr) {
        // no-op
    }

    fn get_machine_mode(&self) -> u32 {
        self.machine_mode
    }

    fn set_machine_mode(&mut self, mode: u32) {
        self.machine_mode = mode;
    }

    fn resume(&mut self) -> Result<()> {
        self.add_cycle_special(
            CycleState::Resume,
            CycleState::Resume,
            self.pc.0,
            0,
            Back::None,
        );
        for i in 0..DIGEST_WORDS {
            self.store_u32(GLOBAL_INPUT_ADDR.waddr() + i, 0)?; // FIXME!
        }
        self.add_cycle_special(
            CycleState::Resume,
            CycleState::Decode,
            self.pc.0,
            0,
            Back::None,
        );
        Ok(())
    }

    fn suspend(&mut self) -> Result<()> {
        self.pc = ByteAddr(0);
        self.add_cycle_special(CycleState::Suspend, CycleState::Suspend, 0, 0, Back::None);
        for i in 0..DIGEST_WORDS {
            self.load_u32(GLOBAL_OUTPUT_ADDR.waddr() + i)?;
        }
        self.machine_mode = 3;
        self.add_cycle_special(
            CycleState::Suspend,
            CycleState::PoseidonEntry,
            0,
            0,
            Back::None,
        );
        Ok(())
    }

    fn on_insn_start(&mut self, _insn: &Instruction, _decoded: &DecodedInstruction) -> Result<()> {
        Ok(())
    }

    fn on_insn_end(&mut self, insn: &Instruction, _decoded: &DecodedInstruction) -> Result<()> {
        self.add_cycle_insn(CycleState::Decode, self.pc.0, insn.kind);
        self.user_cycle += 1;
        self.phys_cycles += 1;
        Ok(())
    }

    fn trap_rewind(&mut self) {
        self.trace.txns.truncate(self.txn_idx as usize);
    }

    fn peek_u32(&mut self, _addr: WordAddr) -> Result<u32> {
        // no-op is OK
        Ok(0)
    }

    // Pass memory ops to pager + record
    fn load_u32(&mut self, addr: WordAddr) -> Result<u32> {
        // tracing::trace!("load_u32: {addr:?}");
        let cycle = (2 * self.trace.cycles.len()) as u32;
        let word = if addr >= MERKLE_TREE_START_ADDR {
            self.page_memory
                .get(&addr)
                .ok_or(anyhow!("Invalid load from page memory"))?
        } else {
            self.pager.load(addr)?
        };
        self.orig_words.get_mut(&addr).get_or_insert(word);
        let prev_cycle = self.prev_cycle.insert_default(&addr, cycle, u32::MAX);
        self.trace.txns.push(RawMemoryTransaction {
            addr: addr.0,
            cycle,
            word,
            prev_cycle,
            prev_word: word,
        });
        Ok(word)
    }

    fn store_u32(&mut self, addr: WordAddr, word: u32) -> Result<()> {
        let cycle = (2 * self.trace.cycles.len() + 1) as u32;
        let prev_word = if addr >= MEMORY_END_ADDR {
            self.page_memory
                .insert(&addr, word)
                .ok_or(anyhow!("Invalid store to page memory"))?
        } else {
            let prev_word = self.pager.load(addr)?;
            self.pager.store(addr, word)?;
            prev_word
        };
        let prev_cycle = self.prev_cycle.insert_default(&addr, cycle, u32::MAX);
        self.trace.txns.push(RawMemoryTransaction {
            addr: addr.0,
            cycle,
            word,
            prev_cycle,
            prev_word,
        });
        Ok(())
    }

    fn on_ecall_cycle(
        &mut self,
        cur_state: CycleState,
        next_state: CycleState,
        s0: u32,
        s1: u32,
        s2: u32,
    ) -> Result<()> {
        self.add_cycle_special(cur_state, next_state, self.pc.0, 0, Back::Ecall(s0, s1, s2));
        self.phys_cycles += 1;
        if next_state == CycleState::PoseidonEntry {
            poseidon2::ecall(self)?;
        }
        Ok(())
    }

    fn on_terminate(&mut self, _a0: u32, _a1: u32) -> Result<()> {
        // no-op
        Ok(())
    }

    fn host_read(&mut self, _fd: u32, buf: &mut [u8]) -> Result<u32> {
        if self.cur_read >= self.segment.read_record.len() {
            bail!("Invalid segment: unexpected read record");
        }
        let record = &self.segment.read_record[self.cur_read];
        let rlen = record.len();
        if rlen > buf.len() {
            bail!("Invalid segment: truncated read record");
        }
        buf[..rlen].copy_from_slice(record);
        Ok(rlen as u32)
    }

    fn host_write(&mut self, _fd: u32, _buf: &[u8]) -> Result<u32> {
        if self.cur_write >= self.segment.write_record.len() {
            bail!("Invalid segment: unexpected write record");
        }
        self.cur_write += 1;
        Ok(self.segment.write_record[self.cur_write])
    }

    fn on_sha2_cycle(&mut self, cur_state: CycleState, sha2: &Sha2State) {
        self.add_cycle_special(
            cur_state,
            sha2.next_state,
            self.pc.0,
            node_addr_to_idx(sha2.state_out_addr),
            Back::Sha2(sha2.clone()),
        );
        self.phys_cycles += 1;
    }

    fn on_poseidon2_cycle(&mut self, cur_state: CycleState, p2: &Poseidon2State) {
        self.add_cycle_special(
            cur_state,
            p2.next_state,
            self.pc.0,
            node_addr_to_idx(WordAddr(p2.buf_out_addr)),
            Back::Poseidon2(p2.clone()),
        );
        self.phys_cycles += 1;
    }
}
