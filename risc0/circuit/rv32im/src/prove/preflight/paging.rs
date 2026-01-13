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

use std::collections::BTreeSet;

use anyhow::{Result, bail};
use enum_map::EnumMap;
use risc0_binfmt::{MemoryImage, Page, WordAddr};
use risc0_circuit_rv32im_sys::{
    BlockType, FpDigest, PageInNodeWitness, PageInPageWitness, PageInPartWitness,
    PageOutNodeWitness, PageOutPageWitness, PageOutPartWitness, PageUncleWitness, fp::Fp,
};
use risc0_zkp::{
    core::{
        digest::{DIGEST_WORDS, Digest},
        hash::poseidon2::CELLS_RATE,
    },
    field::baby_bear::Elem,
};

use crate::prove::preflight::{
    constants::{MEMORY_SIZE_MPAGES, MPAGE_PART_SIZE, MPAGE_SIZE_WORDS},
    poseidon2::Poseidon2Witgen,
    trace::Trace,
};

#[derive(Default, Copy, Clone)]
pub struct MemoryInfo {
    pub cycle: u32,
    pub value: u32,
}

fn to_fp_digest(digest: &Digest) -> FpDigest {
    let mut out = FpDigest::default();

    for (out_cell, &word) in out.iter_mut().zip(digest.as_words().iter()) {
        *out_cell = Fp::new_raw(word);
    }
    out
}

#[derive(Clone)]
pub struct PageDetails(Box<[MemoryInfo; MPAGE_SIZE_WORDS as usize]>);

impl PageDetails {
    pub fn info(&self) -> &[MemoryInfo; MPAGE_SIZE_WORDS as usize] {
        &*self.0
    }

    pub fn info_mut(&mut self) -> &mut [MemoryInfo; MPAGE_SIZE_WORDS as usize] {
        &mut *self.0
    }
}

impl Default for PageDetails {
    fn default() -> Self {
        Self(Box::new([MemoryInfo::default(); MPAGE_SIZE_WORDS as usize]))
    }
}

pub struct PagedMemory {
    image: MemoryImage,
    p2: Poseidon2Witgen,

    /// Tracking for # of rows
    paging_cost: usize,

    counts: EnumMap<BlockType, usize>,

    /// List of paged in page + merkle nodes
    loaded: BTreeSet<u32>,
}

impl PagedMemory {
    pub fn new(image: MemoryImage) -> Self {
        Self {
            image,
            p2: Poseidon2Witgen::new(),
            paging_cost: 0,
            counts: Default::default(),
            loaded: Default::default(),
        }
    }

    pub fn page_in(&mut self, page_id: u32) -> Result<PageDetails> {
        let page_src = self.image.get_page(page_id)?;
        let mut page = PageDetails::default();
        for (i, entry) in page.info_mut().iter_mut().enumerate() {
            entry.value = page_src.load(WordAddr(i as u32));
        }
        self.add_cost_page();
        let mut idx = page_id + MEMORY_SIZE_MPAGES as u32;
        self.loaded.insert(idx);

        idx /= 2;
        while idx != 0 {
            if self.loaded.contains(&idx) {
                break;
            }

            self.add_cost_node();
            self.loaded.insert(idx);
            idx /= 2;
        }
        self.recompute_cost();
        Ok(page)
    }

    pub fn paging_cost(&self) -> usize {
        self.paging_cost
    }

    pub fn p2(&self) -> &Poseidon2Witgen {
        &self.p2
    }

    pub fn p2_mut(&mut self) -> &mut Poseidon2Witgen {
        &mut self.p2
    }

    pub fn commit(&mut self, trace: &mut Trace, pages: &[Option<PageDetails>]) -> Result<()> {
        if pages.len() != MEMORY_SIZE_MPAGES as usize {
            bail!("Too few provided pages");
        }

        self.image.update_digests();

        // Set initial root
        trace.globals_mut().rootIn = to_fp_digest(self.image.get_digest(1)?);

        let loaded = std::mem::take(&mut self.loaded);

        // Page in all the pages that were read
        for &page_idx in loaded.range(MEMORY_SIZE_MPAGES as u32..) {
            let page_idx = page_idx - MEMORY_SIZE_MPAGES as u32;
            tracing::trace!("Paging in: {page_idx}");
            self.page_in_page(trace, page_idx)?;
        }

        // Page in all nodes that were read
        for &node_idx in loaded.range(..MEMORY_SIZE_MPAGES as u32) {
            self.page_in_node(trace, node_idx)?;
        }

        // Page out all the new pages, update image
        for &page_idx in loaded.range(MEMORY_SIZE_MPAGES as u32..) {
            let page_idx = page_idx - MEMORY_SIZE_MPAGES as u32;
            tracing::trace!("Paging out: {page_idx}");
            let Some(page) = pages[page_idx as usize].as_ref() else {
                bail!("Loaded page {page_idx} not provided to commit");
            };
            self.page_out_page(trace, page_idx, page)?;
        }
        self.image.update_digests();

        // Page out all nodes
        for &node_idx in loaded.range(..MEMORY_SIZE_MPAGES as u32) {
            self.page_out_node(trace, node_idx)?;

            if !loaded.contains(&(node_idx * 2)) {
                self.page_uncle(trace, node_idx * 2)?;
            }

            if !loaded.contains(&(node_idx * 2 + 1)) {
                self.page_uncle(trace, node_idx * 2 + 1)?;
            }
        }

        self.loaded = loaded;

        trace.globals_mut().rootOut = to_fp_digest(self.image.get_digest(1)?);

        Ok(())
    }

    fn add_cost_node(&mut self) {
        self.counts[BlockType::P2Block] += 2;
        self.counts[BlockType::P2ExtRound] += 2 * 8;
        self.counts[BlockType::P2IntRounds] += 2;
        self.counts[BlockType::PageInNode] += 1;
        self.counts[BlockType::PageOutNode] += 1;
        self.counts[BlockType::PageUncle] += 1; // Technically we don't always need this
    }

    fn add_cost_page(&mut self) {
        const NUM_PARTS: usize = MPAGE_SIZE_WORDS as usize / MPAGE_PART_SIZE as usize;
        self.counts[BlockType::P2Block] += 2 * NUM_PARTS;
        self.counts[BlockType::P2ExtRound] += 2 * 8 * NUM_PARTS;
        self.counts[BlockType::P2IntRounds] += 2 * NUM_PARTS;
        self.counts[BlockType::PageInPart] += NUM_PARTS;
        self.counts[BlockType::PageOutPart] += NUM_PARTS;
        self.counts[BlockType::PageInPage] += 1;
        self.counts[BlockType::PageOutPage] += 1;
    }

    fn recompute_cost(&mut self) {
        self.paging_cost = BlockType::iter()
            .filter(|&bt| bt != BlockType::Empty)
            .map(|bt| self.counts[bt].div_ceil(bt.count_per_row() as usize))
            .sum()
    }

    fn page_in_page(&mut self, trace: &mut Trace, page_idx: u32) -> Result<()> {
        let page = self.image.get_page(page_idx)?;

        let mut cur = Digest::ZERO;
        const NUM_PARTS: u32 = MPAGE_SIZE_WORDS as u32 / MPAGE_PART_SIZE;

        for i in 0..NUM_PARTS {
            let mut data = [Elem::new(0); CELLS_RATE];
            let addr = page_idx * MPAGE_SIZE_WORDS as u32 + i * MPAGE_PART_SIZE;

            let mut pip_data = [0u32; 8];
            for j in 0..MPAGE_PART_SIZE {
                let word = page.load(WordAddr(i * MPAGE_PART_SIZE + j));
                pip_data[j as usize] = word;
                data[(2 * j) as usize] = Elem::new(word & 0xFFFF);
                data[(2 * j + 1) as usize] = Elem::new(word >> 16);
            }
            let in_ = to_fp_digest(&cur);
            cur = self.p2.do_block(trace, cur, &data, i == NUM_PARTS - 1);
            let out = to_fp_digest(&cur);

            trace.add_block(PageInPartWitness {
                in_,
                out,
                addr,
                data: pip_data,
            });
        }

        trace.add_block(PageInPageWitness {
            addr: page_idx * MPAGE_SIZE_WORDS as u32,
            node: to_fp_digest(&cur),
        });

        Ok(())
    }

    fn page_in_node(&mut self, trace: &mut Trace, node_idx: u32) -> Result<()> {
        let node = to_fp_digest(self.image.get_digest(node_idx)?);
        let left = to_fp_digest(self.image.get_digest(node_idx * 2)?);
        let right = to_fp_digest(self.image.get_digest(node_idx * 2 + 1)?);

        let mut data = [Elem::new(0); CELLS_RATE];
        for i in 0..DIGEST_WORDS {
            data[i] = right[i].to_elem();
            data[DIGEST_WORDS + 1] = left[i].to_elem();
        }

        trace.add_block(PageInNodeWitness {
            index: node_idx,
            node,
            left,
            right,
        });

        self.p2.do_block(trace, Digest::ZERO, &data, true);

        Ok(())
    }

    fn page_out_page(
        &mut self,
        trace: &mut Trace,
        page_idx: u32,
        page_data: &PageDetails,
    ) -> Result<()> {
        let mut new_page = Page::default();
        let mut cur = Digest::ZERO;

        const NUM_PARTS: u32 = MPAGE_SIZE_WORDS as u32 / MPAGE_PART_SIZE;

        let mut pop_data = [0u32; 8];
        let mut pop_cycle = [0u32; 8];
        for i in 0..NUM_PARTS {
            let mut data = [Elem::new(0); CELLS_RATE];
            let addr = page_idx * MPAGE_SIZE_WORDS as u32 + i * MPAGE_PART_SIZE;

            for j in 0..MPAGE_PART_SIZE {
                let page_data_j = page_data.info()[(i * MPAGE_PART_SIZE + j) as usize];
                let word = page_data_j.value;
                new_page.store(WordAddr(i * MPAGE_PART_SIZE + j), word);
                pop_data[j as usize] = word;
                pop_cycle[j as usize] = page_data_j.cycle;
                data[(2 * j) as usize] = Elem::new(word & 0xFFFF);
                data[(2 * j + 1) as usize] = Elem::new(word >> 16);
            }
            let in_ = to_fp_digest(&cur);
            cur = self.p2.do_block(trace, cur, &data, i == NUM_PARTS - 1);
            let out = to_fp_digest(&cur);

            trace.add_block(PageOutPartWitness {
                in_,
                out,
                addr,
                data: pop_data,
                cycle: pop_cycle,
            });
        }
        trace.add_block(PageOutPageWitness {
            addr: page_idx * MPAGE_SIZE_WORDS as u32,
            node: to_fp_digest(&cur),
        });

        self.image.set_page(page_idx, new_page);

        Ok(())
    }

    fn page_out_node(&mut self, trace: &mut Trace, node_idx: u32) -> Result<()> {
        let wit_node = to_fp_digest(self.image.get_digest(node_idx)?);
        let wit_left = to_fp_digest(self.image.get_digest(node_idx * 2)?);
        let wit_right = to_fp_digest(self.image.get_digest(node_idx * 2 + 1)?);

        let mut data = [Elem::new(0); CELLS_RATE];
        for i in 0..DIGEST_WORDS {
            data[i] = wit_right[i].to_elem();
            data[DIGEST_WORDS + i] = wit_left[i].to_elem();
        }

        trace.add_block(PageOutNodeWitness {
            index: node_idx,
            node: wit_node,
            left: wit_left,
            right: wit_right,
        });

        self.p2.do_block(trace, Digest::ZERO, &data, true);
        Ok(())
    }

    fn page_uncle(&mut self, trace: &mut Trace, page_idx: u32) -> Result<()> {
        trace.add_block(PageUncleWitness {
            index: page_idx,
            node: to_fp_digest(self.image.get_digest(page_idx)?),
        });
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::prove::preflight::trace::tests::decode_trace;

    use bytemuck::Zeroable as _;
    use enum_map::{EnumMap, enum_map};

    use risc0_circuit_rv32im_sys::{BlockType, RowInfo};

    #[test]
    fn test_it() {
        let image = MemoryImage::default();
        let mut paging = PagedMemory::new(image);
        let mut rows = vec![RowInfo::zeroed(); 1024];
        let mut aux = vec![0u32; 4096 * 100];
        let mut trace = Trace::new(&mut rows, &mut aux);

        paging.page_in(0).unwrap();
        paging.page_in(1).unwrap();

        let mut page_details = vec![None; MEMORY_SIZE_MPAGES as usize];
        page_details[0] = Some(PageDetails::default());
        page_details[1] = Some(PageDetails::default());
        paging.commit(&mut trace, &page_details).unwrap();

        let mut block_counts: EnumMap<BlockType, u64> = Default::default();
        for block in decode_trace(&rows, &aux) {
            block_counts[block.block_type()] += 1;
        }
        const NUM_PARTS: u64 = MPAGE_SIZE_WORDS / MPAGE_PART_SIZE as u64;
        let page_touches = 2;
        let tree_height = MEMORY_SIZE_MPAGES.ilog2() as u64;
        let p2_blocks = 2 * (page_touches * NUM_PARTS + tree_height);
        assert_eq!(
            block_counts,
            enum_map! {
                BlockType::P2ExtRound => p2_blocks * 8,
                BlockType::P2Block => p2_blocks,
                BlockType::P2IntRounds => p2_blocks,
                BlockType::PageInNode => tree_height,
                BlockType::PageInPage => page_touches,
                BlockType::PageInPart => page_touches * NUM_PARTS,
                BlockType::PageOutNode => tree_height,
                BlockType::PageOutPage => page_touches,
                BlockType::PageOutPart => page_touches * NUM_PARTS,
                BlockType::PageUncle => tree_height - 1,
                _ => 0
            }
        );
    }
}
