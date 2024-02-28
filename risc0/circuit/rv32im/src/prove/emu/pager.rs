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

use std::collections::{BTreeMap, BTreeSet, HashMap};

use anyhow::Result;
use risc0_binfmt::{MemoryImage, SystemState};
use risc0_zkp::core::hash::sha::BLOCK_BYTES;
use risc0_zkvm_platform::{PAGE_SIZE, WORD_SIZE};

use super::addr::{ByteAddr, WordAddr};

pub const PAGE_WORDS: usize = PAGE_SIZE / WORD_SIZE;

/// The number of blocks that fit within a single page.
const BLOCKS_PER_PAGE: usize = PAGE_SIZE / BLOCK_BYTES;

const SHA_INIT: usize = 5;
const SHA_LOAD: usize = 16;
const SHA_MAIN: usize = 52;

const fn cycles_per_page(blocks_per_page: usize) -> usize {
    1 + SHA_INIT + (SHA_LOAD + SHA_MAIN) * blocks_per_page
}

struct Page(Vec<u8>);

#[derive(Clone, Copy, Debug, PartialEq, PartialOrd)]
enum PageState {
    Loaded,
    Dirty,
}

#[derive(Clone, Default, Debug)]
pub struct PageFaults {
    pub reads: BTreeSet<u32>,
    pub writes: BTreeSet<u32>,
}

pub struct PagedMemory {
    pub image: MemoryImage,
    page_cache: HashMap<u32, Page>,
    page_states: BTreeMap<u32, PageState>,
    pub cycles: usize,
}

impl WordAddr {
    fn page_idx(&self) -> u32 {
        self.0 / PAGE_WORDS as u32
    }
}

impl PagedMemory {
    pub fn new(image: MemoryImage) -> Self {
        Self {
            image,
            page_cache: HashMap::new(),
            page_states: BTreeMap::new(),
            cycles: 0,
        }
    }

    pub fn pre_peek(&self, addr: WordAddr) -> Result<u32> {
        let mut bytes = [0u8; WORD_SIZE];
        let addr: ByteAddr = addr.into();
        self.image.load_region_in_page(addr.0, &mut bytes)?;
        Ok(u32::from_le_bytes(bytes))
    }

    pub fn peek(&self, addr: WordAddr) -> Result<u32> {
        let page_idx = addr.page_idx();
        if let Some(cache) = self.page_cache.get(&page_idx) {
            cache.load(addr)
        } else {
            self.pre_peek(addr)
        }
    }

    pub fn load(&mut self, addr: WordAddr) -> Result<u32> {
        let page_idx = addr.page_idx();
        // tracing::trace!("load: 0x{addr:08x}, page: 0x{page_idx:05x}");
        if self.page_states.get(&page_idx).is_none() {
            self.load_page(page_idx);
            self.page_states.insert(page_idx, PageState::Loaded);
        }
        self.page_cache.get(&page_idx).unwrap().load(addr)
    }

    pub fn store(&mut self, addr: WordAddr, data: u32) -> Result<()> {
        let page_idx = addr.page_idx();
        tracing::trace!("store: {addr:?}, page: 0x{page_idx:05x}, data: 0x{data:08x}");
        let state = if let Some(state) = self.page_states.get(&page_idx) {
            *state
        } else {
            self.load_page(page_idx);
            self.page_states.insert(page_idx, PageState::Loaded);
            PageState::Loaded
        };

        if state == PageState::Loaded {
            self.add_cost(page_idx);
            self.update(page_idx, PageState::Dirty);
            self.page_states.insert(page_idx, PageState::Dirty);
        }

        self.page_cache
            .get_mut(&page_idx)
            .unwrap()
            .store(addr, data);

        Ok(())
    }

    pub fn get_paging_cycles(&self) -> usize {
        self.cycles
    }

    pub fn commit(&mut self, pc: ByteAddr) -> (SystemState, MemoryImage, SystemState) {
        let pre_state = self.image.get_system_state();
        let info = &self.image.info;

        let mut image = MemoryImage {
            pages: BTreeMap::new(),
            info: info.clone(),
            pc: pc.0,
        };

        for (page_idx, page_state) in &self.page_states {
            // Copy 'original' version of all pages, this is just the subset of
            // pages for the previous segment.
            image
                .pages
                .insert(*page_idx, self.image.load_page(*page_idx));

            // Update all 'dirty' pages into the image that accumulates over
            // segments.
            if *page_state == PageState::Dirty {
                let page = self.page_cache.get(page_idx).unwrap();
                self.image.pages.insert(*page_idx, page.0.clone());
            }
        }

        // Update the merkle tree
        for (page_idx, page_state) in &self.page_states {
            if *page_state == PageState::Dirty {
                tracing::trace!("dirty: 0x{page_idx:05x}");
                self.image.update_page(*page_idx);
            }
        }
        let post_state = self.image.get_system_state();

        (pre_state, image, post_state)
    }

    pub fn clear(&mut self) {
        self.page_cache.clear();
        self.page_states.clear();
        self.cycles = 0;
    }

    pub fn get_faults(&self) -> PageFaults {
        let mut faults = PageFaults::default();
        for (page_idx, page_state) in &self.page_states {
            faults.reads.insert(*page_idx);
            if *page_state == PageState::Dirty {
                faults.writes.insert(*page_idx);
            }
        }
        faults
    }

    fn load_page(&mut self, page_idx: u32) {
        tracing::trace!("load_page: 0x{page_idx:05x}");
        let page = self.image.load_page(page_idx);
        self.page_cache.insert(page_idx, Page(page));
        self.add_cost(page_idx);
        self.update(page_idx, PageState::Loaded);
    }

    fn update(&mut self, mut page_idx: u32, goal: PageState) {
        // tracing::trace!("update(0x{page_idx:05x}, {goal:?})");
        while page_idx != self.image.info.root_idx {
            let info = &self.image.info;
            let entry_addr = info.get_page_entry_addr(page_idx);
            let parent_idx = info.get_page_index(entry_addr);

            if let Some(state) = self.page_states.get_mut(&parent_idx) {
                if goal > *state {
                    *state = goal;
                    self.add_cost(parent_idx);
                }
            } else {
                let page = self.image.load_page(parent_idx);
                self.page_cache.insert(parent_idx, Page(page));
                self.page_states.insert(parent_idx, goal);
                self.add_cost(parent_idx);
            }

            page_idx = parent_idx;
        }
    }

    fn add_cost(&mut self, page_idx: u32) {
        let info = &self.image.info;

        let page_cycles = if page_idx == info.root_idx {
            let num_root_entries = info.num_root_entries as usize;
            cycles_per_page(num_root_entries / 2)
        } else {
            cycles_per_page(BLOCKS_PER_PAGE)
        };

        // tracing::trace!("add_cost(0x{page_idx:05x}) <= {page_cycles}");
        self.cycles += page_cycles;
    }
}

impl Page {
    fn load(&self, addr: WordAddr) -> Result<u32> {
        let word_addr = (addr.0 % PAGE_WORDS as u32) as usize;
        let byte_addr = word_addr * WORD_SIZE;
        // tracing::trace!("load: 0x{word_addr:04x}");
        let mut bytes = [0u8; WORD_SIZE];
        bytes.clone_from_slice(&self.0[byte_addr..byte_addr + WORD_SIZE]);
        Ok(u32::from_le_bytes(bytes))
        // Ok(self.0[addr])
    }

    fn store(&mut self, addr: WordAddr, data: u32) {
        let word_addr = (addr.0 % PAGE_WORDS as u32) as usize;
        let byte_addr = word_addr * WORD_SIZE;
        // tracing::trace!("store: 0x{word_addr:04x} <= 0x{data:08x}");
        self.0[byte_addr..byte_addr + WORD_SIZE].clone_from_slice(&data.to_le_bytes());
        // self.0[addr] = data;
    }
}
