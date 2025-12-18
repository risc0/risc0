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

#![allow(unused)]

use risc0_circuit_rv32im_m3_sys::BlockType;

use crate::rv32im::{RvOp, WORD_SIZE};

// use super::pager::NUM_PAGES;
// use super::platform::{PAGE_BYTES, WORD_SIZE};
// use super::rv32im::InsnKind;

/// This value can be almost anything, but I chose lcm(count_per_row..) to mitigate rounding errors.
pub const POINTS_PER_ROW: u64 = 5040;

const PART_SIZE: u64 = 8;
const PAGE_BYTES: usize = 1024;
const NUM_PARTS: u64 = (PAGE_BYTES as u64 / WORD_SIZE as u64) / PART_SIZE;
const NUM_PAGES: usize = 4 * 1024 * 1024;

const fn row_points(block: BlockType) -> u64 {
    POINTS_PER_ROW / block.count_per_row() as u64
}

/// Which block types the given instruction ends up being implemented with.
fn add_blocks_for_insn(blocks: &mut BlockCollection, i: &RvOp) {
    use BlockType::*;

    macro_rules! blocks {
        ($($value:expr),+) => {
            { $(blocks.add_block($value);)+ }
        }
    }

    match i {
        RvOp::Add => blocks!(InstReg, UnitAddSub),
        RvOp::Sub => blocks!(InstReg, UnitAddSub),
        RvOp::Xor => blocks!(InstReg, UnitBit),
        RvOp::Or => blocks!(InstReg, UnitBit),
        RvOp::And => blocks!(InstReg, UnitBit),
        RvOp::Sll => blocks!(InstReg, UnitShift, UnitMul),
        RvOp::Srl => blocks!(InstReg, UnitShift, UnitDiv, UnitMul),
        RvOp::Sra => blocks!(InstReg, UnitShift, UnitDiv, UnitMul),
        RvOp::Slt => blocks!(InstReg, UnitLt),
        RvOp::SltU => blocks!(InstReg, UnitLt),
        RvOp::AddI => blocks!(InstImm, UnitAddSub),
        RvOp::XorI => blocks!(InstImm, UnitBit),
        RvOp::OrI => blocks!(InstImm, UnitBit),
        RvOp::AndI => blocks!(InstImm, UnitBit),
        RvOp::SllI => blocks!(InstImm, UnitShift, UnitMul),
        RvOp::SrlI => blocks!(InstImm, UnitShift, UnitDiv, UnitMul),
        RvOp::SraI => blocks!(InstImm, UnitShift, UnitDiv, UnitMul),
        RvOp::SltI => blocks!(InstImm, UnitLt),
        RvOp::SltIU => blocks!(InstImm, UnitLt),
        RvOp::Lb => blocks!(InstLoad),
        RvOp::Lh => blocks!(InstLoad),
        RvOp::Lw => blocks!(InstLoad),
        RvOp::LbU => blocks!(InstLoad),
        RvOp::LhU => blocks!(InstLoad),
        RvOp::Sb => blocks!(InstStore),
        RvOp::Sh => blocks!(InstStore),
        RvOp::Sw => blocks!(InstStore),
        RvOp::Beq => blocks!(InstBranch, UnitAddSub),
        RvOp::Bne => blocks!(InstBranch, UnitAddSub),
        RvOp::Blt => blocks!(InstBranch, UnitLt),
        RvOp::Bge => blocks!(InstBranch, UnitLt),
        RvOp::BltU => blocks!(InstBranch, UnitLt),
        RvOp::BgeU => blocks!(InstBranch, UnitLt),
        RvOp::Jal => blocks!(InstJal),
        RvOp::JalR => blocks!(InstJalr),
        RvOp::Lui => blocks!(InstLui),
        RvOp::Auipc => blocks!(InstAuipc),
        RvOp::Mul => blocks!(InstReg, UnitMul),
        RvOp::MulH => blocks!(InstReg, UnitMul),
        RvOp::MulHSU => blocks!(InstReg, UnitMul),
        RvOp::MulHU => blocks!(InstReg, UnitMul),
        RvOp::Div => blocks!(InstReg, UnitDiv, UnitMul),
        RvOp::DivU => blocks!(InstReg, UnitDiv, UnitMul),
        RvOp::Rem => blocks!(InstReg, UnitDiv, UnitMul),
        RvOp::RemU => blocks!(InstReg, UnitDiv, UnitMul),
        RvOp::Mret => blocks!(InstMret),
        RvOp::Eany | RvOp::Fence | RvOp::Invalid => {}
    }
}

#[derive(Clone, Debug)]
pub struct BlockCollection {
    #[cfg(feature = "block_tracker_debug")]
    blocks: enum_map::EnumMap<BlockType, u64>,
    row_points: u64,
}

impl Default for BlockCollection {
    fn default() -> Self {
        Self {
            #[cfg(feature = "block_tracker_debug")]
            blocks: Default::default(),
            row_points: BlockType::COUNT as u64 * POINTS_PER_ROW,
        }
    }
}

impl BlockCollection {
    fn add_block(&mut self, block: BlockType) {
        self.row_points += row_points(block);

        #[cfg(feature = "block_tracker_debug")]
        {
            self.blocks[block] += 1;
        }
    }

    fn add_blocks(&mut self, block: BlockType, amount: u64) {
        self.row_points += row_points(block) * amount;

        #[cfg(feature = "block_tracker_debug")]
        {
            self.blocks[block] += amount;
        }
    }

    pub fn row_points(&self) -> u64 {
        self.row_points
    }
}

pub struct BlockTracker {
    pc_cache: std::collections::BTreeSet<u32>,
    blocks: BlockCollection,
}

impl Default for BlockTracker {
    fn default() -> Self {
        let mut blocks = BlockCollection::default();

        blocks.add_blocks(BlockType::MakeTable, (256 + 65536) / 16);

        Self {
            pc_cache: Default::default(),
            blocks,
        }
    }
}

impl BlockTracker {
    pub fn track_instr(&mut self, op: RvOp) {
        add_blocks_for_insn(&mut self.blocks, &op);
    }

    pub fn track_pc(&mut self, pc: u32) {
        if self.pc_cache.insert(pc) {
            self.blocks.add_block(BlockType::Decode);
        }
    }

    pub fn track_ecall_write(&mut self) {
        self.blocks.add_block(BlockType::EcallWrite);
    }

    pub fn track_ecall_terminate(&mut self) {
        self.blocks.add_block(BlockType::EcallTerminate);
    }

    pub fn track_ecall_read(&mut self, bytes: u64, words: u64) {
        self.blocks.add_block(BlockType::EcallRead);
        self.blocks.add_blocks(BlockType::ReadByte, bytes);
        self.blocks.add_blocks(BlockType::ReadWord, words);
    }

    pub fn track_ecall_bigint(&mut self, verify_program_size: u64) {
        self.blocks.add_block(BlockType::EcallBigInt);
        self.blocks
            .add_blocks(BlockType::BigInt, verify_program_size);
    }

    fn add_p2_blocks(blocks: &mut BlockCollection, num: u64) {
        blocks.add_blocks(BlockType::P2Block, num);
        blocks.add_blocks(BlockType::P2IntRounds, num);
        blocks.add_blocks(BlockType::P2ExtRound, 8 * num);
    }

    pub fn track_ecall_poseidon2(&mut self, block_count: u64) {
        self.blocks.add_block(BlockType::EcallP2);
        self.blocks.add_blocks(BlockType::P2Step, block_count);
        Self::add_p2_blocks(&mut self.blocks, block_count);
    }

    const fn page_tree_inner_levels() -> u64 {
        // tree_levels = tree_height + 1
        // tree_height = floor(log2(NUM_PAGES))
        // inner_block_levels = tree_levels - 1 = tree_height = floor(log2(NUM_PAGES))
        NUM_PAGES.ilog2() as u64
    }

    fn add_page_in_blocks(blocks: &mut BlockCollection, num: u64) {
        blocks.add_blocks(BlockType::PageInPage, num);
        blocks.add_blocks(BlockType::PageInPart, num * NUM_PARTS);
        Self::add_p2_blocks(blocks, num * NUM_PARTS);

        blocks.add_blocks(BlockType::PageInNode, Self::page_tree_inner_levels() * num);
        Self::add_p2_blocks(blocks, Self::page_tree_inner_levels() * num);
    }

    fn add_page_out_blocks(blocks: &mut BlockCollection, num: u64) {
        blocks.add_blocks(BlockType::PageOutPage, num);
        blocks.add_blocks(BlockType::PageOutPart, num * NUM_PARTS);
        Self::add_p2_blocks(blocks, num * NUM_PARTS);

        blocks.add_blocks(BlockType::PageOutNode, Self::page_tree_inner_levels() * num);
        Self::add_p2_blocks(blocks, Self::page_tree_inner_levels() * num);
    }

    fn add_page_uncle_blocks(blocks: &mut BlockCollection, num: u64) {
        blocks.add_blocks(BlockType::PageUncle, Self::page_tree_inner_levels() * num);
    }

    fn add_table_blocks(blocks: &mut BlockCollection, cycles: u32) {
        blocks.add_blocks(BlockType::MakeTable, (cycles / 8) as u64);
    }

    pub fn get_blocks(&self, cycles: u32, page_touches: u64) -> BlockCollection {
        let mut blocks = self.blocks.clone();
        Self::add_page_in_blocks(&mut blocks, page_touches);
        Self::add_page_out_blocks(&mut blocks, page_touches);
        Self::add_page_uncle_blocks(&mut blocks, page_touches);

        Self::add_table_blocks(&mut blocks, cycles);

        blocks
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test_log::test]
    fn basic() {
        let tracker = BlockTracker::default();

        let blocks = tracker.get_blocks(0, 10);
        let cycles = blocks.row_points().div_ceil(POINTS_PER_ROW) as u32;

        tracing::info!("points: {}, cycles: {cycles}", blocks.row_points());
    }
}
