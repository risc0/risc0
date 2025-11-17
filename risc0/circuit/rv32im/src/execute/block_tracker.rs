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

use risc0_circuit_rv32im_m3_sys::BlockType;

use super::pager::NUM_PAGES;
use super::platform::{PAGE_BYTES, WORD_SIZE};
use super::rv32im::InsnKind;

const POINTS_PER_ROW: u32 = 5040;

const PART_SIZE: u32 = 8;
const NUM_PARTS: u32 = (PAGE_BYTES as u32 / WORD_SIZE as u32) / PART_SIZE;

const fn row_points(block: BlockType) -> u32 {
    POINTS_PER_ROW / block.count_per_row() as u32
}

/// Which block types the given instruction ends up being implemented with.
const fn row_points_for_insn(i: &InsnKind) -> u32 {
    use BlockType::*;

    macro_rules! rp {
        ($($value:expr),+) => {
            0 $(+ row_points($value))+
        }
    }

    match i {
        InsnKind::Add => rp!(InstReg, UnitAddSub),
        InsnKind::Sub => rp!(InstReg, UnitAddSub),
        InsnKind::Xor => rp!(InstReg, UnitBit),
        InsnKind::Or => rp!(InstReg, UnitBit),
        InsnKind::And => rp!(InstReg, UnitBit),
        InsnKind::Sll => rp!(InstReg, UnitShift, UnitMul),
        InsnKind::Srl => rp!(InstReg, UnitShift, UnitDiv, UnitMul),
        InsnKind::Sra => rp!(InstReg, UnitShift, UnitDiv, UnitMul),
        InsnKind::Slt => rp!(InstReg, UnitLt),
        InsnKind::SltU => rp!(InstReg, UnitLt),
        InsnKind::AddI => rp!(InstImm, UnitAddSub),
        InsnKind::XorI => rp!(InstImm, UnitBit),
        InsnKind::OrI => rp!(InstImm, UnitBit),
        InsnKind::AndI => rp!(InstImm, UnitBit),
        InsnKind::SllI => rp!(InstImm, UnitShift, UnitMul),
        InsnKind::SrlI => rp!(InstImm, UnitShift, UnitDiv, UnitMul),
        InsnKind::SraI => rp!(InstImm, UnitShift, UnitDiv, UnitMul),
        InsnKind::SltI => rp!(InstImm, UnitLt),
        InsnKind::SltIU => rp!(InstImm, UnitLt),
        InsnKind::Lb => rp!(InstLoad),
        InsnKind::Lh => rp!(InstLoad),
        InsnKind::Lw => rp!(InstLoad),
        InsnKind::LbU => rp!(InstLoad),
        InsnKind::LhU => rp!(InstLoad),
        InsnKind::Sb => rp!(InstStore),
        InsnKind::Sh => rp!(InstStore),
        InsnKind::Sw => rp!(InstStore),
        InsnKind::Beq => rp!(InstBranch, UnitAddSub),
        InsnKind::Bne => rp!(InstBranch, UnitAddSub),
        InsnKind::Blt => rp!(InstBranch, UnitLt),
        InsnKind::Bge => rp!(InstBranch, UnitLt),
        InsnKind::BltU => rp!(InstBranch, UnitLt),
        InsnKind::BgeU => rp!(InstBranch, UnitLt),
        InsnKind::Jal => rp!(InstJal),
        InsnKind::JalR => rp!(InstJalr),
        InsnKind::Lui => rp!(InstLui),
        InsnKind::Auipc => rp!(InstAuipc),
        InsnKind::Mul => rp!(InstReg, UnitMul),
        InsnKind::MulH => rp!(InstReg, UnitMul),
        InsnKind::MulHSU => rp!(InstReg, UnitMul),
        InsnKind::MulHU => rp!(InstReg, UnitMul),
        InsnKind::Div => rp!(InstReg, UnitDiv, UnitMul),
        InsnKind::DivU => rp!(InstReg, UnitDiv, UnitMul),
        InsnKind::Rem => rp!(InstReg, UnitDiv, UnitMul),
        InsnKind::RemU => rp!(InstReg, UnitDiv, UnitMul),
        InsnKind::Mret => rp!(InstMret),
        InsnKind::Eany | InsnKind::Fence | InsnKind::Invalid => 0,
    }
}

pub struct BlockTracker {
    pc_cache: std::collections::BTreeSet<u32>,
    row_points: u32,
}

impl Default for BlockTracker {
    fn default() -> Self {
        Self {
            pc_cache: Default::default(),
            row_points: BlockType::COUNT as u32 * POINTS_PER_ROW,
        }
    }
}

impl BlockTracker {
    pub fn track_instr(&mut self, kind: InsnKind) {
        self.row_points += row_points_for_insn(&kind);
    }

    pub fn track_pc(&mut self, pc: u32) {
        if self.pc_cache.insert(pc) {
            self.row_points += row_points(BlockType::Decode);
        }
    }

    pub fn track_ecall_write(&mut self) {
        self.row_points += row_points(BlockType::EcallWrite);
    }

    pub fn track_ecall_terminate(&mut self) {
        self.row_points += row_points(BlockType::EcallTerminate);
    }

    pub fn track_ecall_read(&mut self, bytes: u32, words: u32) {
        self.row_points += row_points(BlockType::EcallRead)
            + row_points(BlockType::ReadByte) * bytes
            + row_points(BlockType::ReadWord) * words;
    }

    pub fn track_ecall_bigint(&mut self, verify_program_size: u32) {
        self.row_points += row_points(BlockType::EcallBigInt)
            + row_points(BlockType::BigInt) * verify_program_size;
    }

    const fn p2_points() -> u32 {
        row_points(BlockType::P2Block)
            + row_points(BlockType::P2IntRounds)
            + 8 * row_points(BlockType::P2ExtRound)
    }

    pub fn track_ecall_poseidon2(&mut self, block_count: u32) {
        self.row_points += row_points(BlockType::EcallP2)
            + block_count * (row_points(BlockType::P2Step) + Self::p2_points());
    }

    const fn page_in_points() -> u32 {
        let tree_height = NUM_PAGES.ilog2() as u32;
        row_points(BlockType::PageInPage)
            + (row_points(BlockType::PageInPart) + Self::p2_points()) * NUM_PARTS
            + (row_points(BlockType::PageInNode) + Self::p2_points()) * (tree_height - 1)
    }

    const fn page_out_points() -> u32 {
        let tree_height = NUM_PAGES.ilog2() as u32;
        row_points(BlockType::PageOutPage)
            + (row_points(BlockType::PageOutPart) + Self::p2_points()) * NUM_PARTS
            + (row_points(BlockType::PageOutNode) + Self::p2_points()) * (tree_height - 1)
    }

    pub fn row_count(&self, page_touches: u32) -> u32 {
        let page_points = page_touches * (Self::page_in_points() + Self::page_out_points());
        (self.row_points + page_points).div_ceil(POINTS_PER_ROW)
    }
}
