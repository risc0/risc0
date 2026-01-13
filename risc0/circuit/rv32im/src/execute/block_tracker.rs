// Copyright 2026 RISC Zero, Inc.
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
use serde::{Deserialize, Serialize};

use risc0_circuit_rv32im_sys::BlockType;

use super::pager::NUM_PAGES;
use super::platform::{PAGE_BYTES, WORD_SIZE};
use super::rv32im::InsnKind;

/// This value can be almost anything, but I chose lcm(count_per_row..) to mitigate rounding errors.
pub const POINTS_PER_ROW: u64 = 5040;

const PART_SIZE: u64 = 8;
const NUM_PARTS: u64 = (PAGE_BYTES as u64 / WORD_SIZE as u64) / PART_SIZE;

const fn row_points(block: BlockType) -> u64 {
    POINTS_PER_ROW / block.count_per_row() as u64
}

/// Which block types the given instruction ends up being implemented with.
fn add_blocks_for_insn(blocks: &mut BlockCollection, i: &InsnKind) {
    use BlockType::*;

    macro_rules! blocks {
        ($($value:expr),+) => {
            { $(blocks.add_block($value);)+ }
        }
    }

    match i {
        InsnKind::Add => blocks!(InstReg, UnitAddSub),
        InsnKind::Sub => blocks!(InstReg, UnitAddSub),
        InsnKind::Xor => blocks!(InstReg, UnitBit),
        InsnKind::Or => blocks!(InstReg, UnitBit),
        InsnKind::And => blocks!(InstReg, UnitBit),
        InsnKind::Sll => blocks!(InstReg, UnitShift, UnitMul),
        InsnKind::Srl => blocks!(InstReg, UnitShift, UnitDiv, UnitMul),
        InsnKind::Sra => blocks!(InstReg, UnitShift, UnitDiv, UnitMul),
        InsnKind::Slt => blocks!(InstReg, UnitLt),
        InsnKind::SltU => blocks!(InstReg, UnitLt),
        InsnKind::AddI => blocks!(InstImm, UnitAddSub),
        InsnKind::XorI => blocks!(InstImm, UnitBit),
        InsnKind::OrI => blocks!(InstImm, UnitBit),
        InsnKind::AndI => blocks!(InstImm, UnitBit),
        InsnKind::SllI => blocks!(InstImm, UnitShift, UnitMul),
        InsnKind::SrlI => blocks!(InstImm, UnitShift, UnitDiv, UnitMul),
        InsnKind::SraI => blocks!(InstImm, UnitShift, UnitDiv, UnitMul),
        InsnKind::SltI => blocks!(InstImm, UnitLt),
        InsnKind::SltIU => blocks!(InstImm, UnitLt),
        InsnKind::Lb => blocks!(InstLoad),
        InsnKind::Lh => blocks!(InstLoad),
        InsnKind::Lw => blocks!(InstLoad),
        InsnKind::LbU => blocks!(InstLoad),
        InsnKind::LhU => blocks!(InstLoad),
        InsnKind::Sb => blocks!(InstStore),
        InsnKind::Sh => blocks!(InstStore),
        InsnKind::Sw => blocks!(InstStore),
        InsnKind::Beq => blocks!(InstBranch, UnitAddSub),
        InsnKind::Bne => blocks!(InstBranch, UnitAddSub),
        InsnKind::Blt => blocks!(InstBranch, UnitLt),
        InsnKind::Bge => blocks!(InstBranch, UnitLt),
        InsnKind::BltU => blocks!(InstBranch, UnitLt),
        InsnKind::BgeU => blocks!(InstBranch, UnitLt),
        InsnKind::Jal => blocks!(InstJal),
        InsnKind::JalR => blocks!(InstJalr),
        InsnKind::Lui => blocks!(InstLui),
        InsnKind::Auipc => blocks!(InstAuipc),
        InsnKind::Mul => blocks!(InstReg, UnitMul),
        InsnKind::MulH => blocks!(InstReg, UnitMul),
        InsnKind::MulHSU => blocks!(InstReg, UnitMul),
        InsnKind::MulHU => blocks!(InstReg, UnitMul),
        InsnKind::Div => blocks!(InstReg, UnitDiv, UnitMul),
        InsnKind::DivU => blocks!(InstReg, UnitDiv, UnitMul),
        InsnKind::Rem => blocks!(InstReg, UnitDiv, UnitMul),
        InsnKind::RemU => blocks!(InstReg, UnitDiv, UnitMul),
        InsnKind::Mret => blocks!(InstMret),
        InsnKind::Eany | InsnKind::Invalid => {}
    }
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct BlockCollection {
    #[cfg(any(test, feature = "block_tracker_debug"))]
    blocks: enum_map::EnumMap<BlockType, u32>,
    row_points: u64,
}

impl Default for BlockCollection {
    fn default() -> Self {
        Self {
            #[cfg(any(test, feature = "block_tracker_debug"))]
            blocks: {
                let mut blocks = enum_map::EnumMap::default();
                blocks[BlockType::Globals] += 1;
                blocks[BlockType::InstResume] += 1;
                blocks[BlockType::InstSuspend] += 1;
                blocks
            },
            row_points: BlockType::COUNT as u64 * POINTS_PER_ROW,
        }
    }
}

impl BlockCollection {
    fn add_block(&mut self, block: BlockType) {
        self.row_points += row_points(block);

        #[cfg(any(test, feature = "block_tracker_debug"))]
        {
            self.blocks[block] += 1;
        }
    }

    fn add_blocks(&mut self, block: BlockType, amount: u64) {
        self.row_points += row_points(block) * amount;

        #[cfg(any(test, feature = "block_tracker_debug"))]
        {
            self.blocks[block] += u32::try_from(amount).unwrap();
        }
    }

    pub fn row_points(&self) -> u64 {
        self.row_points
    }

    pub fn assert_preflight_counts(&self, _preflight: enum_map::EnumMap<BlockType, u32>) {
        #[cfg(any(test, feature = "block_tracker_debug"))]
        {
            // These blocks are estimates only, assert they are over-estimates.
            let estimate_blocks = [
                BlockType::InstSuspend,
                BlockType::MakeTable,
                BlockType::P2Block,
                BlockType::P2ExtRound,
                BlockType::P2IntRounds,
                BlockType::PageInNode,
                BlockType::PageOutNode,
                BlockType::PageUncle,
            ];

            for &b in estimate_blocks.iter() {
                assert!(
                    _preflight[b] <= self.blocks[b],
                    "block_tracker count was too low: {b:?} {} > {}\n\
                     executor = {:#?}\n\
                     preflight = {:#?}",
                    _preflight[b],
                    self.blocks[b],
                    &self.blocks,
                    &_preflight,
                );
            }

            for b in BlockType::iter().filter(|b| !estimate_blocks.contains(b)) {
                assert!(
                    _preflight[b] == self.blocks[b],
                    "block_tracker count was off: {b:?} {} != {}\n\
                     executor = {:#?}\n\
                     preflight = {:#?}",
                    _preflight[b],
                    self.blocks[b],
                    &self.blocks,
                    &_preflight,
                );
            }
        }
    }
}

pub struct BlockTracker {
    pc_cache: std::collections::BTreeSet<u32>,
    blocks: BlockCollection,
}

impl Default for BlockTracker {
    fn default() -> Self {
        let mut blocks = BlockCollection::default();

        blocks.add_blocks(BlockType::MakeTable, (256u64 + 65536u64) / 16);

        Self {
            pc_cache: Default::default(),
            blocks,
        }
    }
}

impl BlockTracker {
    pub fn track_instr(&mut self, kind: InsnKind) {
        add_blocks_for_insn(&mut self.blocks, &kind);
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

        self.blocks
            .add_blocks(BlockType::MakeTable, (bytes + words + 1).div_ceil(8));
    }

    pub fn track_ecall_bigint(&mut self, verify_program_size: u64) {
        self.blocks.add_block(BlockType::EcallBigInt);
        self.blocks
            .add_blocks(BlockType::BigInt, verify_program_size);
        self.blocks
            .add_blocks(BlockType::MakeTable, (verify_program_size + 1).div_ceil(8));
    }

    pub fn track_user_ecall(&mut self) {
        self.blocks.add_block(BlockType::InstEcall);
    }

    pub fn track_trap(&mut self) {
        self.blocks.add_block(BlockType::InstTrap);
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

        self.blocks
            .add_blocks(BlockType::MakeTable, (block_count + 1).div_ceil(8));
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
        blocks.add_blocks(BlockType::MakeTable, cycles.div_ceil(8) as u64);
    }

    pub fn get_blocks(&self, cycles: u32, page_touches: u64) -> BlockCollection {
        let mut blocks = self.blocks.clone();
        Self::add_page_in_blocks(&mut blocks, page_touches);
        Self::add_page_out_blocks(&mut blocks, page_touches);
        Self::add_page_uncle_blocks(&mut blocks, page_touches);

        // add 2 cycles for suspend / resume, 1 cycle is starting value
        Self::add_table_blocks(&mut blocks, cycles + 2 + 1);

        blocks
    }
}
