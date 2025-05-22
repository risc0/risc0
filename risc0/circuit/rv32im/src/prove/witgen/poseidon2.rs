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

use anyhow::Result;
use risc0_circuit_rv32im_sys::RawMemoryTransaction;
use risc0_zkp::{
    core::digest::DIGEST_WORDS,
    field::{Elem as _},
};

use crate::{
    execute::{
        node_idx,
        pager::{PAGE_WORDS, POSEIDON_PAGE_ROUNDS},
        poseidon2::{Poseidon2, Poseidon2State},
        r0vm::Risc0Context,
        tx, CycleState, MERKLE_TREE_END_ADDR, MERKLE_TREE_START_ADDR, WORD_SIZE,
    },
    zirgen::circuit::{ExtVal, PoseidonStateLayout, LAYOUT_TOP},
};

use super::node_idx_to_addr;

const P2_STATE_LAYOUT: &PoseidonStateLayout = LAYOUT_TOP.inst_result.arm9.state;
const P2_STATE_SIZE: usize = std::mem::size_of::<Poseidon2State>() / WORD_SIZE;

impl Poseidon2State {
    fn new_start(mode: u32) -> Self {
        Self {
            buf_out_addr: if mode == 0 {
                MERKLE_TREE_END_ADDR.0
            } else {
                MERKLE_TREE_START_ADDR.0
            },
            is_elem: 1,
            check_out: 1,
            load_tx_type: tx::PAGE_IN,
            next_state: CycleState::PoseidonPaging,
            mode,
            ..Default::default()
        }
    }

    fn new_done(buf_out_addr: u32, next_state: CycleState, mode: u32) -> Self {
        Self {
            buf_out_addr,
            next_state,
            mode,
            ..Default::default()
        }
    }

    fn new_node(node_idx: u32, is_read: bool) -> Self {
        Self {
            buf_out_addr: node_idx_to_addr(node_idx).0,
            is_elem: 1,
            check_out: if is_read { 1 } else { 0 },
            load_tx_type: if is_read { tx::PAGE_IN } else { tx::PAGE_OUT },
            next_state: CycleState::PoseidonPaging,
            buf_in_addr: node_idx_to_addr(2 * node_idx + 1).0,
            count: 1,
            mode: if is_read { 0 } else { 4 },
            ..Default::default()
        }
    }

    fn new_page(page_idx: u32, is_read: bool) -> Self {
        let node_idx = node_idx(page_idx);
        Self {
            buf_out_addr: node_idx_to_addr(node_idx).0,
            check_out: if is_read { 1 } else { 0 },
            load_tx_type: if is_read { tx::PAGE_IN } else { tx::PAGE_OUT },
            next_state: CycleState::PoseidonPaging,
            buf_in_addr: page_idx * PAGE_WORDS as u32,
            count: POSEIDON_PAGE_ROUNDS,
            mode: if is_read { 1 } else { 3 },
            ..Default::default()
        }
    }

    pub(crate) const fn offsets() -> [usize; P2_STATE_SIZE] {
        [
            P2_STATE_LAYOUT.has_state._super.offset,
            P2_STATE_LAYOUT.state_addr._super.offset,
            P2_STATE_LAYOUT.buf_out_addr._super.offset,
            P2_STATE_LAYOUT.is_elem._super.offset,
            P2_STATE_LAYOUT.check_out._super.offset,
            P2_STATE_LAYOUT.load_tx_type._super.offset,
            P2_STATE_LAYOUT.next_state._super.offset,
            P2_STATE_LAYOUT.sub_state._super.offset,
            P2_STATE_LAYOUT.buf_in_addr._super.offset,
            P2_STATE_LAYOUT.count._super.offset,
            P2_STATE_LAYOUT.mode._super.offset,
            P2_STATE_LAYOUT.inner[0]._super.offset,
            P2_STATE_LAYOUT.inner[1]._super.offset,
            P2_STATE_LAYOUT.inner[2]._super.offset,
            P2_STATE_LAYOUT.inner[3]._super.offset,
            P2_STATE_LAYOUT.inner[4]._super.offset,
            P2_STATE_LAYOUT.inner[5]._super.offset,
            P2_STATE_LAYOUT.inner[6]._super.offset,
            P2_STATE_LAYOUT.inner[7]._super.offset,
            P2_STATE_LAYOUT.inner[8]._super.offset,
            P2_STATE_LAYOUT.inner[9]._super.offset,
            P2_STATE_LAYOUT.inner[10]._super.offset,
            P2_STATE_LAYOUT.inner[11]._super.offset,
            P2_STATE_LAYOUT.inner[12]._super.offset,
            P2_STATE_LAYOUT.inner[13]._super.offset,
            P2_STATE_LAYOUT.inner[14]._super.offset,
            P2_STATE_LAYOUT.inner[15]._super.offset,
            P2_STATE_LAYOUT.inner[16]._super.offset,
            P2_STATE_LAYOUT.inner[17]._super.offset,
            P2_STATE_LAYOUT.inner[18]._super.offset,
            P2_STATE_LAYOUT.inner[19]._super.offset,
            P2_STATE_LAYOUT.inner[20]._super.offset,
            P2_STATE_LAYOUT.inner[21]._super.offset,
            P2_STATE_LAYOUT.inner[22]._super.offset,
            P2_STATE_LAYOUT.inner[23]._super.offset,
            P2_STATE_LAYOUT.zcheck._super.offset,
            P2_STATE_LAYOUT.zcheck._super.offset + 1,
            P2_STATE_LAYOUT.zcheck._super.offset + 2,
            P2_STATE_LAYOUT.zcheck._super.offset + 3,
        ]
    }

    pub(crate) fn as_array(&self) -> [u32; P2_STATE_SIZE] {
        let zcheck_elems = self.zcheck.elems();
        let [z0, z1, z2, z3] = [
            zcheck_elems[0].into(),
            zcheck_elems[1].into(),
            zcheck_elems[2].into(),
            zcheck_elems[3].into(),
        ];

        [
            self.has_state,
            self.state_addr,
            self.buf_out_addr,
            self.is_elem,
            self.check_out,
            self.load_tx_type,
            self.next_state as u32,
            self.sub_state,
            self.buf_in_addr,
            self.count,
            self.mode,
            self.inner[0],
            self.inner[1],
            self.inner[2],
            self.inner[3],
            self.inner[4],
            self.inner[5],
            self.inner[6],
            self.inner[7],
            self.inner[8],
            self.inner[9],
            self.inner[10],
            self.inner[11],
            self.inner[12],
            self.inner[13],
            self.inner[14],
            self.inner[15],
            self.inner[16],
            self.inner[17],
            self.inner[18],
            self.inner[19],
            self.inner[20],
            self.inner[21],
            self.inner[22],
            self.inner[23],
            z0, z1, z2, z3,
        ]
    }
}

impl Poseidon2 {
    pub fn read_start(ctx: &mut dyn Risc0Context) -> Result<()> {
        let p2 = Poseidon2State::new_start(0);
        ctx.on_poseidon2_cycle(CycleState::PoseidonEntry, &p2);
        Ok(())
    }

    pub fn read_node(ctx: &mut dyn Risc0Context, node_idx: u32) -> Result<()> {
        let mut p2 = Poseidon2State::new_node(node_idx, true);
        p2.rest(ctx, CycleState::PoseidonPaging)
    }

    pub fn read_page(ctx: &mut dyn Risc0Context, page_idx: u32) -> Result<()> {
        let mut p2 = Poseidon2State::new_page(page_idx, true);
        p2.rest(ctx, CycleState::PoseidonPaging)
    }

    pub fn read_done(ctx: &mut dyn Risc0Context) -> Result<()> {
        let p2 = Poseidon2State::new_done(MERKLE_TREE_START_ADDR.0, CycleState::Resume, 2);
        ctx.on_poseidon2_cycle(CycleState::PoseidonPaging, &p2);
        Ok(())
    }

    pub fn write_start(ctx: &mut dyn Risc0Context) -> Result<()> {
        let p2 = Poseidon2State::new_start(3);
        ctx.on_poseidon2_cycle(CycleState::PoseidonEntry, &p2);
        Ok(())
    }

    pub fn write_node(ctx: &mut dyn Risc0Context, node_idx: u32) -> Result<()> {
        let mut p2 = Poseidon2State::new_node(node_idx, false);
        p2.rest(ctx, CycleState::PoseidonPaging)
    }

    pub fn write_page(ctx: &mut dyn Risc0Context, page_idx: u32) -> Result<()> {
        let mut p2 = Poseidon2State::new_page(page_idx, false);
        p2.rest(ctx, CycleState::PoseidonPaging)
    }

    pub fn write_done(ctx: &mut dyn Risc0Context) -> Result<()> {
        let p2 = Poseidon2State::new_done(MERKLE_TREE_END_ADDR.0, CycleState::StoreRoot, 5);
        ctx.on_poseidon2_cycle(CycleState::PoseidonPaging, &p2);
        Ok(())
    }
}

pub(crate) struct Checksum {
    powers: [ExtVal; DIGEST_WORDS * 2 + 1],
    pub zcheck: ExtVal,
}

impl Checksum {
    pub(crate) fn new(rand_z: &ExtVal) -> Self {
        let mut cur = ExtVal::ONE;
        let mut powers = [ExtVal::ZERO; DIGEST_WORDS * 2 + 1];
        for power in powers.iter_mut() {
            *power = cur;
            cur *= *rand_z;
        }


        Self {
            powers,
            zcheck: ExtVal::ZERO,
        }
    }

    pub(crate) fn start(&mut self) {
        self.zcheck *= self.powers[16];
    }

    pub(crate) fn clear(&mut self) {
        self.zcheck = ExtVal::ZERO;
    }

    pub(crate) fn add(&mut self, tx_kind: u32, idx: usize, txn: &RawMemoryTransaction) {
        let coeffs = match tx_kind {
            tx::READ => (0u32, 1u32),
            tx::PAGE_IN => {
                let diff = txn.cycle.wrapping_sub(txn.prev_cycle);
                (0u32, diff)
            },
            tx::PAGE_OUT => {
                // Use wrapping arithmetic to avoid branches
                let word_low = txn.word & 0xffff;
                let prev_word_low = txn.prev_word & 0xffff;
                let word_high = txn.word >> 16;
                let prev_word_high = txn.prev_word >> 16;

                let diff_low = word_low.wrapping_sub(prev_word_low);
                let diff_high = word_high.wrapping_sub(prev_word_high);

                (diff_low, diff_high)
            },
            _ => unreachable!(),
        };

        // Combine the two multiplications for better instruction-level parallelism
        let idx2 = 2 * idx;
        self.zcheck += self.powers[idx2] * ExtVal::from_u32(coeffs.0)
                    + self.powers[idx2 + 1] * ExtVal::from_u32(coeffs.1);
    }
}
