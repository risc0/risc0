// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use anyhow::Result;
use risc0_circuit_rv32im_sys::RawMemoryTransaction;
use risc0_zkp::{
    core::digest::DIGEST_WORDS,
    field::{Elem as _, baby_bear},
};

use crate::{
    execute::{
        CycleState, MERKLE_TREE_END_ADDR, MERKLE_TREE_START_ADDR, WORD_SIZE, node_idx,
        pager::{PAGE_WORDS, POSEIDON_PAGE_ROUNDS},
        poseidon2::{Poseidon2, Poseidon2State},
        r0vm::Risc0Context,
        tx,
    },
    zirgen::circuit::{ExtVal, LAYOUT_TOP, PoseidonStateLayout},
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
        let zcheck = self.zcheck.elems();
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
            zcheck[0].into(),
            zcheck[1].into(),
            zcheck[2].into(),
            zcheck[3].into(),
        ]
    }
}

impl Poseidon2 {
    pub fn read_start(ctx: &mut impl Risc0Context) -> Result<()> {
        // tracing::trace!("read_start");
        let p2 = Poseidon2State::new_start(0);
        ctx.on_poseidon2_cycle(CycleState::PoseidonEntry, &p2);
        Ok(())
    }

    pub fn read_node(ctx: &mut impl Risc0Context, node_idx: u32) -> Result<()> {
        // tracing::trace!("read_node: {node_idx:#010x}");
        let mut p2 = Poseidon2State::new_node(node_idx, true);
        p2.run(ctx, CycleState::PoseidonPaging)
    }

    pub fn read_page(ctx: &mut impl Risc0Context, page_idx: u32) -> Result<()> {
        // tracing::trace!("read_page: {page_idx:#010x}");
        let mut p2 = Poseidon2State::new_page(page_idx, true);
        p2.run(ctx, CycleState::PoseidonPaging)
    }

    pub fn read_done(ctx: &mut impl Risc0Context) -> Result<()> {
        // tracing::trace!("read_done");
        let p2 = Poseidon2State::new_done(MERKLE_TREE_START_ADDR.0, CycleState::Resume, 2);
        ctx.on_poseidon2_cycle(CycleState::PoseidonPaging, &p2);
        Ok(())
    }

    pub fn write_start(ctx: &mut impl Risc0Context) -> Result<()> {
        // tracing::trace!("write_start");
        let p2 = Poseidon2State::new_start(3);
        ctx.on_poseidon2_cycle(CycleState::PoseidonEntry, &p2);
        Ok(())
    }

    pub fn write_node(ctx: &mut impl Risc0Context, node_idx: u32) -> Result<()> {
        // tracing::trace!("write_node: {node_idx:#010x}");
        let mut p2 = Poseidon2State::new_node(node_idx, false);
        p2.run(ctx, CycleState::PoseidonPaging)
    }

    pub fn write_page(ctx: &mut impl Risc0Context, page_idx: u32) -> Result<()> {
        // tracing::trace!("write_page: {page_idx:#010x}");
        let mut p2 = Poseidon2State::new_page(page_idx, false);
        p2.run(ctx, CycleState::PoseidonPaging)
    }

    pub fn write_done(ctx: &mut impl Risc0Context) -> Result<()> {
        // tracing::trace!("write_done");
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
        // tracing::trace!("powers: {powers:?}");

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
        let mut coeffs = match tx_kind {
            tx::READ => (0, 1),
            tx::PAGE_IN => (0, txn.cycle as i32 - txn.prev_cycle as i32),
            tx::PAGE_OUT => (
                (txn.word & 0xffff) as i32 - (txn.prev_word & 0xffff) as i32,
                (txn.word >> 16) as i32 - (txn.prev_word >> 16) as i32,
            ),
            _ => unreachable!(),
        };
        if coeffs.0 < 0 {
            coeffs.0 += baby_bear::P as i32;
        }
        if coeffs.1 < 0 {
            coeffs.1 += baby_bear::P as i32;
        }
        let coeffs = (coeffs.0 as u32, coeffs.1 as u32);
        self.zcheck += self.powers[2 * idx] * ExtVal::from_u32(coeffs.0);
        self.zcheck += self.powers[2 * idx + 1] * ExtVal::from_u32(coeffs.1);
    }
}
