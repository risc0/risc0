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

use std::collections::BTreeSet;

use anyhow::{anyhow, bail, Result};
use derive_more::Debug;
use num_traits::FromPrimitive as _;
use risc0_binfmt::{ByteAddr, WordAddr};
use risc0_circuit_rv32im_sys::{RawMemoryTransaction, RawPreflightCycle};
use risc0_core::scope;
use risc0_zkp::core::digest::DIGEST_WORDS;

use crate::{
    execute::{
        bigint::BigIntBytes,
        node_idx,
        pager::{page_idx, PageState, PagedMemory},
        platform::*,
        poseidon2::{Poseidon2, Poseidon2State},
        r0vm::{EcallKind, LoadOp, Risc0Context, Risc0Machine},
        rv32im::{disasm, Emulator, InsnKind},
        segment::Segment,
        sha2::Sha2State,
    },
    zirgen::circuit::ExtVal,
};

use super::{
    bigint::BigIntState, node_addr_to_idx, node_idx_to_addr, paged_map::PagedMap,
    poseidon2::Checksum,
};

#[derive(Clone, Debug, Default)]
pub(crate) enum Back {
    #[default]
    None,
    Ecall(u32, u32, u32),
    #[debug("Poseidon2")]
    Poseidon2(Poseidon2State),
    #[debug("Sha2")]
    Sha2(Sha2State),
    #[debug("BigInt")]
    BigInt(BigIntState),
}

#[derive(Clone, Debug, Default)]
pub(crate) struct PreflightTrace {
    #[debug("{}", cycles.len())]
    pub cycles: Vec<RawPreflightCycle>,
    #[debug("{}", txns.len())]
    pub txns: Vec<RawMemoryTransaction>,
    #[debug("{}", bigint_bytes.len())]
    pub bigint_bytes: Vec<u8>,
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
    bigint_idx: u32,
    user_cycles: u32,
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
        for (&node_idx, digest) in segment.partial_image.digests() {
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
            pager: PagedMemory::new(
                segment.partial_image.clone(),
                false, /* tracing_enabled */
            ),
            pc: ByteAddr(0),
            machine_mode: 0,
            cur_write: 0,
            cur_read: 0,
            txn_idx: 0,
            bigint_idx: 0,
            user_cycle: 0,
            user_cycles: 0,
            orig_words: Default::default(),
            prev_cycle: Default::default(),
            page_memory,
        }
    }

    // Do page in
    pub fn read_pages(&mut self) -> Result<()> {
        self.read_root()?;
        let activity = self.pager.loaded_pages();
        Poseidon2::read_start(self)?;
        for node_idx in activity.nodes {
            Poseidon2::read_node(self, node_idx)?;
        }
        self.machine_mode = 1;
        for page_idx in activity.pages {
            Poseidon2::read_page(self, page_idx)?;
        }
        self.machine_mode = 2;
        Poseidon2::read_done(self)?;
        self.user_cycles = 0;
        Ok(())
    }

    // Run main execution
    pub fn body(&mut self) -> Result<()> {
        let mut emu = Emulator::new();
        Risc0Machine::resume(self)?;
        while self.user_cycles < self.segment.suspend_cycle {
            Risc0Machine::step(&mut emu, self)?;
        }
        tracing::debug!(
            "suspend(cycle: {}:{}, pc: {:?}, mode: {})",
            self.trace.cycles.len(),
            self.user_cycles,
            self.pc,
            self.machine_mode
        );
        Risc0Machine::suspend(self)
    }

    // Do page out
    pub fn write_pages(&mut self) -> Result<()> {
        let activity = self.pager.dirty_pages();
        self.pager.commit();
        Poseidon2::write_start(self)?;
        for &page_idx in activity.pages.iter().rev() {
            Poseidon2::write_page(self, page_idx)?;
        }
        self.machine_mode = 4;
        for &node_idx in activity.nodes.iter().rev() {
            Poseidon2::write_node(self, node_idx)?;
        }
        self.machine_mode = 5;
        Poseidon2::write_done(self)?;
        self.machine_mode = 0;
        self.write_root()
    }

    // Do table reification
    pub fn generate_tables(&mut self) -> Result<()> {
        self.trace.table_split_cycle = self.trace.cycles.len() as u32;
        self.fini()
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
        let start_cycles = self.trace.cycles.len();

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

        if self.segment.claim.terminate_state.is_none() {
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
        assert_eq!(self.trace.cycles.len() - start_cycles, RESERVED_CYCLES);

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

    fn read_root(&mut self) -> Result<()> {
        let addr = get_digest_addr(1);
        for i in 0..DIGEST_WORDS {
            self.load_u32(LoadOp::Record, addr + i)?;
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
            self.load_u32(LoadOp::Record, addr + i)?;
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
            bigint_idx: self.bigint_idx,
            diff_count: [0, 0],
        };
        // tracing::trace!("[{}]: {cycle:?}", self.trace.cycles.len());
        self.trace.cycles.push(cycle);
        self.trace.backs.push(back);
        self.txn_idx = self.trace.txns.len() as u32;
        self.bigint_idx = self.trace.bigint_bytes.len() as u32;
    }

    fn add_witness(&mut self, bytes: &BigIntBytes) {
        self.trace.bigint_bytes.extend_from_slice(bytes);
    }

    fn add_cycle_insn(&mut self, state: CycleState, pc: u32, insn: InsnKind) {
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
        let raw_cur_state = cur_state as u32;
        let major = (7 + raw_cur_state / 8) as u8;
        let minor = (raw_cur_state % 8) as u8;
        // tracing::trace!("add_cycle_special(cur_state: {cur_state:?}, next_state: {next_state:?}, major: {major}, minor: {minor})");
        self.add_cycle(next_state, pc, major, minor, paging_idx, back);
    }

    pub(crate) fn on_bigint_cycle(&mut self, cur_state: CycleState, bigint: &BigIntState) {
        self.add_witness(&bigint.bytes);
        self.add_cycle_special(
            cur_state,
            bigint.next_state,
            self.pc.0,
            0, //paging_idx
            Back::BigInt(bigint.clone()),
        );
        self.user_cycles += 1;
    }
}

impl Risc0Context for Preflight<'_> {
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
        tracing::trace!("[{}] set_machine_mode({mode})", self.trace.cycles.len());
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
        let input_words = self.segment.claim.input.as_words();
        for (i, word) in input_words.iter().enumerate() {
            self.store_u32(GLOBAL_INPUT_ADDR.waddr() + i, *word)?;
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
            self.load_u32(LoadOp::Record, GLOBAL_OUTPUT_ADDR.waddr() + i)?;
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

    fn on_insn_start(
        &mut self,
        kind: InsnKind,
        decoded: &crate::execute::rv32im::DecodedInstruction,
    ) -> Result<()> {
        tracing::trace!(
            "[{}]: {:?}> {}",
            self.trace.cycles.len(),
            self.pc,
            disasm(kind, decoded)
        );
        Ok(())
    }

    fn on_insn_end(&mut self, kind: InsnKind) -> Result<()> {
        self.add_cycle_insn(CycleState::Decode, self.pc.0, kind);
        self.user_cycle += 1;
        self.user_cycles += 1;
        Ok(())
    }

    fn trap_rewind(&mut self) {
        self.trace.txns.truncate(self.txn_idx as usize);
    }

    // Pass memory ops to pager + record
    fn load_u32(&mut self, op: LoadOp, addr: WordAddr) -> Result<u32> {
        if op == LoadOp::Peek {
            return self.pager.peek(addr);
        }

        // tracing::trace!("load_u32: {addr:?}");
        let cycle = (2 * self.trace.cycles.len()) as u32;
        let word = if addr >= MERKLE_TREE_START_ADDR {
            self.page_memory
                .get(&addr)
                .ok_or_else(|| anyhow!("Invalid load from page memory"))?
        } else {
            self.pager.load(addr)?
        };
        if op == LoadOp::Record {
            self.orig_words.get_mut(&addr).get_or_insert(word);
            let prev_cycle = self.prev_cycle.insert_default(&addr, cycle, u32::MAX);
            let txn = RawMemoryTransaction {
                addr: addr.0,
                cycle,
                word,
                prev_cycle,
                prev_word: word,
            };
            // tracing::trace!("txn: {txn:?}");
            self.trace.txns.push(txn);
        }
        Ok(word)
    }

    fn store_u32(&mut self, addr: WordAddr, word: u32) -> Result<()> {
        let cycle = (2 * self.trace.cycles.len() + 1) as u32;
        let prev_word = if addr >= MEMORY_END_ADDR {
            self.page_memory
                .insert(&addr, word)
                .ok_or_else(|| anyhow!("Invalid store to page memory"))?
        } else {
            let prev_word = self.pager.load(addr)?;
            self.pager.store(addr, word)?;
            prev_word
        };
        let prev_cycle = self.prev_cycle.insert_default(&addr, cycle, u32::MAX);
        let txn = RawMemoryTransaction {
            addr: addr.0,
            cycle,
            word,
            prev_cycle,
            prev_word,
        };
        // tracing::trace!("txn: {txn:?}");
        self.trace.txns.push(txn);
        Ok(())
    }

    fn on_ecall_cycle(
        &mut self,
        cur_state: CycleState,
        next_state: CycleState,
        s0: u32,
        s1: u32,
        s2: u32,
        _kind: EcallKind,
    ) -> Result<()> {
        self.add_cycle_special(cur_state, next_state, self.pc.0, 0, Back::Ecall(s0, s1, s2));
        self.user_cycles += 1;
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
        self.cur_read += 1;
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
        self.user_cycles += 1;
    }

    fn on_poseidon2_cycle(&mut self, cur_state: CycleState, p2: &Poseidon2State) {
        self.add_cycle_special(
            cur_state,
            p2.next_state,
            self.pc.0,
            node_addr_to_idx(WordAddr(p2.buf_out_addr)),
            Back::Poseidon2(p2.clone()),
        );
        self.user_cycles += 1;
    }

    fn ecall_bigint(&mut self) -> Result<()> {
        super::bigint::ecall_preflight(self)
    }
}

impl InsnKind {
    pub fn major(&self) -> u8 {
        (*self as u32 / 8) as u8
    }

    pub fn minor(&self) -> u8 {
        (*self as u32 % 8) as u8
    }
}

#[derive(Clone, Default, Debug)]
pub(crate) struct PagingActivity {
    pub pages: BTreeSet<u32>,
    pub nodes: BTreeSet<u32>,
}

impl PagingActivity {
    fn new(pages: BTreeSet<u32>) -> Self {
        let mut nodes = BTreeSet::new();
        for &page_idx in pages.iter() {
            let mut node_idx = node_idx(page_idx);
            while node_idx != 1 {
                let parent_idx = node_idx / 2;
                // tracing::trace!("add node: {node_idx:#010x}, parent_idx: {parent_idx:#010x}");
                if !nodes.insert(parent_idx) {
                    break;
                }
                node_idx = parent_idx;
            }
        }
        Self { pages, nodes }
    }
}

impl PagedMemory {
    pub(crate) fn loaded_pages(&self) -> PagingActivity {
        tracing::trace!("loaded_pages: {:#010x?}", self.image.get_page_indexes());
        PagingActivity::new(self.image.get_page_indexes())
    }

    pub(crate) fn dirty_pages(&self) -> PagingActivity {
        let pages = self
            .page_states
            .iter()
            .filter(|(node_idx, state)| {
                *node_idx >= MEMORY_PAGES as u32 && *state == PageState::Dirty
            })
            .map(|(node_idx, _)| page_idx(node_idx))
            .collect();
        PagingActivity::new(pages)
    }
}
