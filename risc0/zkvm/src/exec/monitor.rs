// Copyright 2023 RISC Zero, Inc.
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

use std::{array, collections::BTreeSet};

use anyhow::Result;
use risc0_zkp::core::hash::sha::BLOCK_BYTES;
use risc0_zkvm_platform::{memory::SYSTEM, syscall::reg_abi::REG_MAX, PAGE_SIZE, WORD_SIZE};
use rrs_lib::{MemAccessSize, Memory};

use super::{io::SyscallContext, TraceEvent};
use crate::{session::PageFaults, MemoryImage};

/// The number of blocks that fit within a single page.
const BLOCKS_PER_PAGE: usize = PAGE_SIZE / BLOCK_BYTES;

const SHA_INIT: usize = 5;
const SHA_LOAD: usize = 16;
const SHA_MAIN: usize = 52;

const fn cycles_per_page(blocks_per_page: usize) -> usize {
    1 + SHA_INIT + (SHA_LOAD + SHA_MAIN) * blocks_per_page
}

#[derive(Debug)]
enum Action {
    PageRead(u32, usize),
    PageWrite(u32, usize),
    StoreU8(u32, u8),
    StoreU16(u32, u16),
    StoreU32(u32, u32),
}

pub struct MemoryMonitor {
    pub image: MemoryImage,
    pub faults: PageFaults,
    session_cycle: usize,
    pub trace_events: BTreeSet<TraceEvent>,
    resident: Vec<bool>,
    dirty: Vec<bool>,
    pending_actions: Vec<Action>,
    pub page_read_cycles: usize,
    pub page_write_cycles: usize,
    enable_trace: bool,
}

impl MemoryMonitor {
    pub fn new(image: MemoryImage, enable_trace: bool) -> Self {
        let resident = vec![false; image.info.num_pages as usize + 1];
        let dirty = vec![false; image.info.num_pages as usize + 1];
        Self {
            image,
            faults: PageFaults::default(),
            session_cycle: 0,
            trace_events: BTreeSet::new(),
            resident,
            dirty,
            pending_actions: Vec::new(),
            page_read_cycles: 0,
            page_write_cycles: 0,
            enable_trace,
        }
    }

    pub fn load_u8(&mut self, addr: u32) -> u8 {
        // log::trace!("load_u8: 0x{addr:08x}");
        self.load_page(addr);
        let mut bytes = [0_u8];
        self.image.load_region_in_page(addr, &mut bytes);
        bytes[0]
    }

    pub fn load_u16(&mut self, addr: u32) -> u16 {
        assert_eq!(addr % 2, 0, "unaligned load");
        // log::trace!("load_u16: 0x{addr:08x}");
        self.load_page(addr);
        let mut bytes = [0_u8; 2];
        self.image.load_region_in_page(addr, &mut bytes);
        u16::from_le_bytes(bytes)
    }

    pub fn load_u32(&mut self, addr: u32) -> u32 {
        assert_eq!(addr % WORD_SIZE as u32, 0, "unaligned load");
        // log::trace!("load_u32: 0x{addr:08x}");
        self.load_page(addr);
        let mut bytes = [0_u8; WORD_SIZE];
        self.image.load_region_in_page(addr, &mut bytes);
        u32::from_le_bytes(bytes)
    }

    fn load_page(&mut self, addr: u32) {
        let info = &self.image.info;
        let page_idx = info.get_page_index(addr);
        if self.resident[page_idx as usize] {
            return;
        }

        let page_cycles = if page_idx == info.root_idx {
            let num_root_entries = info.num_root_entries as usize;
            cycles_per_page(num_root_entries / 2)
        } else {
            let entry_addr = info.get_page_entry_addr(page_idx);
            self.load_page(entry_addr);
            cycles_per_page(BLOCKS_PER_PAGE)
        };

        log::debug!("load_page: 0x{page_idx:08x}");
        self.resident[page_idx as usize] = true;
        self.pending_actions
            .push(Action::PageRead(page_idx, page_cycles));
        self.page_read_cycles += page_cycles;
        self.faults.reads.insert(page_idx);
    }

    fn mark_page(&mut self, addr: u32) {
        let info = &self.image.info;
        let page_idx = info.get_page_index(addr);
        if self.dirty[page_idx as usize] {
            return;
        }

        let page_cycles = if page_idx == info.root_idx {
            let num_root_entries = info.num_root_entries as usize;
            cycles_per_page(num_root_entries / 2)
        } else {
            let entry_addr = info.get_page_entry_addr(page_idx);
            self.mark_page(entry_addr);
            cycles_per_page(BLOCKS_PER_PAGE)
        };

        log::debug!("mark_page: 0x{page_idx:08x}");
        self.dirty[page_idx as usize] = true;
        self.pending_actions
            .push(Action::PageWrite(page_idx, page_cycles));
        self.page_write_cycles += page_cycles;
        self.faults.writes.insert(page_idx);
    }

    pub fn load_array<const N: usize>(&mut self, addr: u32) -> [u8; N] {
        array::from_fn(|idx| self.load_u8(addr + idx as u32))
    }

    pub fn load_register(&mut self, idx: usize) -> u32 {
        // log::trace!("load_register: R{idx}");
        self.load_u32(get_register_addr(idx))
    }

    pub fn load_registers<const N: usize>(&mut self, idxs: [usize; N]) -> [u32; N] {
        let mut bytes = [0_u8; WORD_SIZE * REG_MAX];
        let addr = SYSTEM.start() as u32;
        self.image.load_region_in_page(addr, &mut bytes);
        self.load_page(addr);
        idxs.map(|idx| {
            u32::from_le_bytes(
                bytes[idx * WORD_SIZE..(idx + 1) * WORD_SIZE]
                    .try_into()
                    .unwrap(),
            )
        })
    }

    pub fn load_string(&mut self, mut addr: u32) -> Result<String> {
        let mut s: Vec<u8> = Vec::new();
        loop {
            let bytes = self.load_u8(addr);
            if bytes == 0 {
                break;
            }
            s.push(bytes);
            addr += 1;
        }
        String::from_utf8(s).map_err(anyhow::Error::msg)
    }

    fn raw_store_u8(&mut self, addr: u32, data: u8) {
        let old = self.load_u8(addr);
        self.pending_actions.push(Action::StoreU8(addr, old));
        self.image.store_region_in_page(addr, &data.to_le_bytes());
        self.mark_page(addr);
    }

    pub fn store_u8(&mut self, addr: u32, data: u8) {
        // log::trace!("store_u8: 0x{addr:08x}");
        self.raw_store_u8(addr, data);
        if self.enable_trace {
            self.trace_events.insert(TraceEvent::MemorySet {
                addr,
                value: data as u32,
            });
        }
    }

    pub fn store_u16(&mut self, addr: u32, data: u16) {
        // log::trace!("store_u16: 0x{addr:08x}");
        assert_eq!(addr % 2, 0, "unaligned store");
        let old = self.load_u16(addr);
        self.pending_actions.push(Action::StoreU16(addr, old));
        self.image.store_region_in_page(addr, &data.to_le_bytes());
        self.mark_page(addr);
        if self.enable_trace {
            self.trace_events.insert(TraceEvent::MemorySet {
                addr,
                value: data as u32,
            });
        }
    }

    pub fn store_u32(&mut self, addr: u32, data: u32) {
        // log::trace!("store_u32: 0x{addr:08x}");
        assert_eq!(addr % WORD_SIZE as u32, 0, "unaligned store");
        let old = self.load_u32(addr);
        self.pending_actions.push(Action::StoreU32(addr, old));
        self.image.store_region_in_page(addr, &data.to_le_bytes());
        self.mark_page(addr);
        if self.enable_trace {
            self.trace_events.insert(TraceEvent::MemorySet {
                addr,
                value: data as u32,
            });
        }
    }

    pub fn store_region(&mut self, addr: u32, slice: &[u8]) {
        // log::trace!("store_region: 0x{addr:08x}");
        slice
            .iter()
            .enumerate()
            .for_each(|(i, x)| self.raw_store_u8(addr + i as u32, *x));
    }

    pub fn store_register(&mut self, idx: usize, data: u32) {
        // log::trace!("store_register: R{idx}");
        let addr = get_register_addr(idx);
        let old = self.load_u32(addr);
        self.pending_actions.push(Action::StoreU32(addr, old));
        self.image.store_region_in_page(addr, &data.to_le_bytes());
        self.mark_page(addr);
        if self.enable_trace {
            self.trace_events.insert(TraceEvent::RegisterSet {
                reg: idx,
                value: data,
            });
        }
    }

    pub fn undo(&mut self) {
        for action in self.pending_actions.iter().rev() {
            match action {
                Action::PageRead(page_idx, cycles) => {
                    log::debug!("undo: PageRead(0x{page_idx:08x}, {cycles})");
                    self.faults.reads.remove(page_idx);
                    self.page_read_cycles -= cycles;
                }
                Action::PageWrite(page_idx, cycles) => {
                    log::debug!("undo: PageWrite(0x{page_idx:08x}, {cycles})");
                    self.faults.writes.remove(page_idx);
                    self.page_write_cycles -= cycles;
                }
                Action::StoreU8(addr, data) => {
                    log::debug!("undo: StoreU8(0x{addr:08x}, {data})");
                    self.image.store_region_in_page(*addr, &data.to_le_bytes())
                }
                Action::StoreU16(addr, data) => {
                    log::debug!("undo: StoreU16(0x{addr:08x}, {data})");
                    self.image.store_region_in_page(*addr, &data.to_le_bytes())
                }
                Action::StoreU32(addr, data) => {
                    log::debug!("undo: StoreU32(0x{addr:08x}, {data})");
                    self.image.store_region_in_page(*addr, &data.to_le_bytes())
                }
            }
        }
        self.pending_actions.clear();
    }

    // commit all pending activity
    pub fn commit(&mut self, cycle: usize) {
        self.pending_actions.clear();
        self.session_cycle = cycle;
        if self.enable_trace {
            self.trace_events.clear();
        }
        // self.faults.dump();
    }

    pub fn clear_segment(&mut self) {
        self.resident.fill(false);
        self.dirty.fill(false);
        self.page_read_cycles = 0;
        self.page_write_cycles = 0;
        self.faults.clear();
    }

    pub fn clear_session(&mut self) {
        self.clear_segment();
        self.session_cycle = 0;
    }
}

impl Memory for MemoryMonitor {
    fn read_mem(&mut self, addr: u32, size: MemAccessSize) -> Option<u32> {
        match size {
            MemAccessSize::Byte => Some(self.load_u8(addr) as u32),
            MemAccessSize::HalfWord => Some(self.load_u16(addr) as u32),
            MemAccessSize::Word => Some(self.load_u32(addr)),
        }
    }

    fn write_mem(&mut self, addr: u32, size: MemAccessSize, store_data: u32) -> bool {
        match size {
            MemAccessSize::Byte => self.store_u8(addr, store_data as u8),
            MemAccessSize::HalfWord => self.store_u16(addr, store_data as u16),
            MemAccessSize::Word => self.store_u32(addr, store_data),
        };
        true
    }
}

impl SyscallContext for MemoryMonitor {
    fn get_cycle(&self) -> usize {
        self.session_cycle
    }

    fn load_u32(&mut self, addr: u32) -> u32 {
        MemoryMonitor::load_u32(self, addr)
    }

    fn load_u8(&mut self, addr: u32) -> u8 {
        MemoryMonitor::load_u8(self, addr)
    }
}

fn get_register_addr(idx: usize) -> u32 {
    (SYSTEM.start() + idx * WORD_SIZE) as u32
}

impl PageFaults {
    fn clear(&mut self) {
        self.reads.clear();
        self.writes.clear();
    }

    #[allow(dead_code)]
    fn dump(&self) {
        log::debug!("PageFaultInfo");
        log::debug!("  reads>");
        for idx in self.reads.iter().rev() {
            log::debug!("  0x{:08X}", idx);
        }
        log::debug!("  writes>");
        for idx in self.writes.iter() {
            log::debug!("  0x{:08X}", idx);
        }
    }
}
