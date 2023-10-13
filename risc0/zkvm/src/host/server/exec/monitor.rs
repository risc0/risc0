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

use std::{array, collections::BTreeSet, mem::take};

use anyhow::{bail, Result};
use risc0_binfmt::MemoryImage;
use risc0_zkp::core::hash::sha::BLOCK_BYTES;
use risc0_zkvm_platform::{
    memory::{is_guest_memory, SYSTEM},
    syscall::reg_abi::REG_MAX,
    PAGE_SIZE, WORD_SIZE,
};
use rrs_lib::{MemAccessSize, Memory};

use super::syscall::SyscallContext;
use crate::host::{client::exec::TraceEvent, server::session::PageFaults};

/// The number of blocks that fit within a single page.
const BLOCKS_PER_PAGE: usize = PAGE_SIZE / BLOCK_BYTES;

const SHA_INIT: usize = 5;
const SHA_LOAD: usize = 16;
const SHA_MAIN: usize = 52;

const fn cycles_per_page(blocks_per_page: usize) -> usize {
    1 + SHA_INIT + (SHA_LOAD + SHA_MAIN) * blocks_per_page
}

#[derive(Clone, Debug)]
enum Action {
    PageRead(u32, usize),
    PageWrite(u32, usize),
    StoreU8(u32, u8),
    StoreU16(u32, u16),
    StoreU32(u32, u32),
    StoreReg(usize, u32),
}

#[derive(Clone)]
struct Page {
    buf: Vec<u8>,
}

impl Page {
    fn load_bytes(&self, addr: u32, bytes: &mut [u8]) {
        let addr = addr as usize;
        bytes.clone_from_slice(&self.buf[addr..addr + bytes.len()]);
    }

    fn store_bytes(&mut self, addr: u32, bytes: &[u8]) {
        let addr = addr as usize;
        self.buf[addr..addr + bytes.len()].clone_from_slice(bytes);
    }
}

pub struct MemoryMonitor {
    image: MemoryImage,
    num_pages: usize,
    pub faults: PageFaults,
    session_cycle: usize,
    pub trace_events: BTreeSet<TraceEvent>,
    resident: Vec<bool>,
    dirty: Vec<bool>,
    pending_actions: Vec<Action>,
    pub page_read_cycles: usize,
    pub page_write_cycles: usize,
    enable_trace: bool,
    pages: Vec<Option<Page>>,
    registers: [u32; REG_MAX],
}

impl MemoryMonitor {
    pub fn new(image: MemoryImage, enable_trace: bool) -> Self {
        let num_pages = image.info.num_pages as usize + 1;
        let resident = vec![false; num_pages];
        let dirty = vec![false; num_pages];
        let pages = vec![None; num_pages];
        Self {
            image,
            num_pages,
            faults: PageFaults::default(),
            session_cycle: 0,
            trace_events: BTreeSet::new(),
            resident,
            dirty,
            pending_actions: Vec::new(),
            page_read_cycles: 0,
            page_write_cycles: 0,
            enable_trace,
            pages,
            registers: [0; REG_MAX],
        }
    }

    fn check_guest_addr(addr: u32) -> Result<()> {
        if !is_guest_memory(addr) {
            bail!("address 0x{addr:08x} is an invalid guest address");
        }
        Ok(())
    }

    fn check_guest_addr_range(start_addr: u32, end_addr: u32) -> Result<()> {
        if !is_guest_memory(start_addr) || !is_guest_memory(end_addr) {
            bail!("address range 0x{start_addr:08x} - 0x{end_addr:08x} is outside of guest memory");
        }
        Ok(())
    }

    pub fn load_u8(&mut self, addr: u32) -> Result<u8> {
        // log::trace!("load_u8: 0x{addr:08x}");
        let mut bytes = [0_u8];
        self.load_bytes(addr, &mut bytes)?;
        Ok(bytes[0])
    }

    pub fn load_u16(&mut self, addr: u32) -> Result<u16> {
        if addr % 2 != 0 {
            bail!("unaligned load at 0x{addr:08x}");
        }
        // log::trace!("load_u16: 0x{addr:08x}");
        let mut bytes = [0_u8; 2];
        self.load_bytes(addr, &mut bytes)?;
        Ok(u16::from_le_bytes(bytes))
    }

    pub fn load_u32(&mut self, addr: u32) -> Result<u32> {
        if addr % WORD_SIZE as u32 != 0 {
            bail!("unaligned load at 0x{addr:08x}");
        }
        // log::trace!("load_u32: 0x{addr:08x}");
        let mut bytes = [0_u8; WORD_SIZE];
        self.load_bytes(addr, &mut bytes)?;
        Ok(u32::from_le_bytes(bytes))
    }

    pub fn load_u32_from_guest_addr(&mut self, addr: u32) -> Result<u32> {
        Self::check_guest_addr(addr)?;
        self.load_u32(addr)
    }

    fn get_page_index(&self, addr: u32) -> Result<u32> {
        let page_idx = self.image.info.get_page_index(addr);
        if self.num_pages <= page_idx as usize {
            bail!(
                "Page index 0x{page_idx:08x} for address [0x{addr:08x}] does not exist. Max page index is 0x{:08x}",
                self.num_pages
            )
        } else {
            Ok(page_idx)
        }
    }

    fn load_page(&mut self, addr: u32) -> Result<()> {
        let info = &self.image.info;
        let page_idx = self.get_page_index(addr)?;
        if self.resident[page_idx as usize] {
            return Ok(());
        }

        log::debug!("load_page: 0x{page_idx:08x}");
        let page_cycles = if page_idx == info.root_idx {
            let num_root_entries = info.num_root_entries as usize;
            cycles_per_page(num_root_entries / 2)
        } else {
            let entry_addr = info.get_page_entry_addr(page_idx);
            self.load_page(entry_addr)?;
            cycles_per_page(BLOCKS_PER_PAGE)
        };

        self.resident[page_idx as usize] = true;
        self.pending_actions
            .push(Action::PageRead(page_idx, page_cycles));
        self.page_read_cycles += page_cycles;
        self.faults.reads.insert(page_idx);
        Ok(())
    }

    fn mark_page(&mut self, addr: u32) {
        let info = &self.image.info;
        let page_idx = info.get_page_index(addr);
        if self.dirty[page_idx as usize] {
            return;
        }

        log::debug!("mark_page: 0x{page_idx:08x}");
        let page_cycles = if page_idx == info.root_idx {
            let num_root_entries = info.num_root_entries as usize;
            cycles_per_page(num_root_entries / 2)
        } else {
            let entry_addr = info.get_page_entry_addr(page_idx);
            self.mark_page(entry_addr);
            cycles_per_page(BLOCKS_PER_PAGE)
        };

        self.dirty[page_idx as usize] = true;
        self.pending_actions
            .push(Action::PageWrite(page_idx, page_cycles));
        self.page_write_cycles += page_cycles;
        self.faults.writes.insert(page_idx);
    }

    pub fn load_array<const N: usize>(&mut self, addr: u32) -> Result<[u8; N]> {
        // log::trace!("load_array: 0x{addr:08x}");
        let mut vals = Vec::new();
        for i in 0..N {
            vals.push(self.load_u8(addr + i as u32)?);
        }
        Ok(array::from_fn(|idx| vals[idx]))
    }

    pub fn load_array_from_guest_addr<const N: usize>(&mut self, addr: u32) -> Result<[u8; N]> {
        Self::check_guest_addr_range(addr, addr + u32::try_from(N)?)?;
        self.load_array(addr)
    }

    pub fn load_register(&self, idx: usize) -> u32 {
        // log::trace!("load_register: x{idx}");
        self.registers[idx]
    }

    pub fn load_guest_addr_from_register(&self, idx: usize) -> Result<u32> {
        // log::trace!("load_register: x{idx}");
        let addr = self.registers[idx];
        Self::check_guest_addr(addr)?;
        Ok(addr)
    }

    pub fn load_registers(&self) -> [u32; REG_MAX] {
        self.registers
    }

    fn init_registers(&mut self) -> Result<()> {
        let mut bytes = [0_u8; WORD_SIZE * REG_MAX];
        self.load_bytes(SYSTEM.start() as u32, &mut bytes)?;
        for idx in 0..REG_MAX {
            self.registers[idx] =
                u32::from_le_bytes(bytes[idx * WORD_SIZE..(idx + 1) * WORD_SIZE].try_into()?);
        }
        Ok(())
    }

    fn load_bytes(&mut self, addr: u32, bytes: &mut [u8]) -> Result<()> {
        self.load_page(addr)?;
        let info = &self.image.info;
        let page_idx = self.get_page_index(addr)?;
        let offset = addr % info.page_size;
        self.pages[page_idx as usize]
            .get_or_insert_with(|| Page {
                buf: self.image.load_page(page_idx),
            })
            .load_bytes(offset, bytes);
        Ok(())
    }

    pub fn load_string(&mut self, mut addr: u32) -> Result<String> {
        // log::trace!("load_string: 0x{addr:08x}");
        let mut s: Vec<u8> = Vec::new();
        loop {
            let bytes = self.load_u8(addr)?;
            if bytes == 0 {
                break;
            }
            s.push(bytes);
            addr += 1;
        }
        String::from_utf8(s).map_err(anyhow::Error::msg)
    }

    pub fn load_string_from_guest_memory(&mut self, mut addr: u32) -> Result<String> {
        let start_addr = addr;
        let mut len = 0;
        loop {
            if self.load_u8(addr)? == 0 {
                break;
            }
            addr += 1;
            len += 1;
        }
        Self::check_guest_addr_range(start_addr, start_addr + len)?;
        self.load_string(start_addr)
    }

    fn raw_store_u8(&mut self, addr: u32, data: u8) -> Result<()> {
        // log::trace!("raw_store_u8: 0x{addr:08x}");
        let old = self.load_u8(addr)?;
        self.pending_actions.push(Action::StoreU8(addr, old));
        self.store_bytes(addr, &[data])?;
        self.mark_page(addr);
        Ok(())
    }

    pub fn store_u8(&mut self, addr: u32, data: u8) -> Result<()> {
        // log::trace!("store_u8: 0x{addr:08x}");
        self.raw_store_u8(addr, data)?;
        if self.enable_trace {
            self.trace_events.insert(TraceEvent::MemorySet {
                addr,
                value: data as u32,
            });
        }
        Ok(())
    }

    pub fn store_u16(&mut self, addr: u32, data: u16) -> Result<()> {
        // log::trace!("store_u16: 0x{addr:08x}");
        assert_eq!(addr % 2, 0, "unaligned store");
        let old = self.load_u16(addr)?;
        self.pending_actions.push(Action::StoreU16(addr, old));
        self.store_bytes(addr, &data.to_le_bytes())?;
        self.mark_page(addr);
        if self.enable_trace {
            self.trace_events.insert(TraceEvent::MemorySet {
                addr,
                value: data as u32,
            });
        }
        Ok(())
    }

    pub fn store_u32(&mut self, addr: u32, data: u32) -> Result<()> {
        // log::trace!("store_u32: 0x{addr:08x}");
        assert_eq!(addr % WORD_SIZE as u32, 0, "unaligned store");
        let old = self.load_u32(addr)?;
        self.pending_actions.push(Action::StoreU32(addr, old));
        self.store_bytes(addr, &data.to_le_bytes())?;
        self.mark_page(addr);
        if self.enable_trace {
            self.trace_events
                .insert(TraceEvent::MemorySet { addr, value: data });
        }
        Ok(())
    }

    pub fn store_u32_to_guest_memory(&mut self, addr: u32, data: u32) -> Result<()> {
        Self::check_guest_addr_range(addr, addr + 4)?;
        self.store_u32(addr, data)
    }

    pub fn store_region(&mut self, addr: u32, slice: &[u8]) -> Result<()> {
        // log::trace!("store_region: 0x{addr:08x}");
        slice
            .iter()
            .enumerate()
            .try_for_each(|(i, x)| self.raw_store_u8(addr + i as u32, *x))?;
        Ok(())
    }

    pub fn store_region_to_guest_memory(&mut self, addr: u32, slice: &[u8]) -> Result<()> {
        Self::check_guest_addr_range(addr, addr + u32::try_from(slice.len())?)?;
        self.store_region(addr, slice)
    }

    pub fn store_register(&mut self, idx: usize, data: u32) {
        // log::trace!("store_register: x{idx} <= 0x{data:08x}");
        let old = self.load_register(idx);
        self.pending_actions.push(Action::StoreReg(idx, old));
        self.registers[idx] = data;
        self.mark_page(SYSTEM.start() as u32);
        if self.enable_trace {
            self.trace_events
                .insert(TraceEvent::RegisterSet { idx, value: data });
        }
    }

    fn store_bytes(&mut self, addr: u32, bytes: &[u8]) -> Result<()> {
        let info = &self.image.info;
        let page_idx = self.get_page_index(addr)?;
        let offset = addr % info.page_size;
        self.pages[page_idx as usize]
            .get_or_insert_with(|| Page {
                buf: self.image.load_page(page_idx),
            })
            .store_bytes(offset, bytes);
        Ok(())
    }

    pub fn undo(&mut self) -> Result<()> {
        let pending_actions = take(&mut self.pending_actions);
        for action in pending_actions.iter().rev() {
            match action {
                Action::PageRead(page_idx, cycles) => {
                    log::debug!("undo: PageRead(0x{page_idx:08x}, {cycles})");
                    self.resident[*page_idx as usize] = false;
                    self.faults.reads.remove(page_idx);
                    self.page_read_cycles -= cycles;
                }
                Action::PageWrite(page_idx, cycles) => {
                    log::debug!("undo: PageWrite(0x{page_idx:08x}, {cycles})");
                    self.dirty[*page_idx as usize] = false;
                    self.faults.writes.remove(page_idx);
                    self.page_write_cycles -= cycles;
                }
                Action::StoreU8(addr, data) => {
                    log::debug!("undo: StoreU8(0x{addr:08x}, {data})");
                    self.store_bytes(*addr, &data.to_le_bytes())?;
                }
                Action::StoreU16(addr, data) => {
                    log::debug!("undo: StoreU16(0x{addr:08x}, {data})");
                    self.store_bytes(*addr, &data.to_le_bytes())?;
                }
                Action::StoreU32(addr, data) => {
                    log::debug!("undo: StoreU32(0x{addr:08x}, {data})");
                    self.store_bytes(*addr, &data.to_le_bytes())?;
                }
                Action::StoreReg(idx, data) => {
                    log::debug!("undo: StoreReg(x{idx}, {data})");
                    self.registers[*idx] = *data;
                }
            }
        }
        Ok(())
    }

    // commit all pending activity
    pub fn commit(&mut self, cycle: usize) {
        self.pending_actions.clear();
        self.session_cycle = cycle;
        if self.enable_trace {
            self.trace_events.clear();
        }
    }

    pub fn clear_segment(&mut self) -> Result<()> {
        self.resident.fill(false);
        self.dirty.fill(false);
        self.pages.fill(None);
        self.page_read_cycles = 0;
        self.page_write_cycles = 0;
        self.faults.clear();
        self.init_registers()
    }

    pub fn clear_session(&mut self) -> Result<()> {
        self.clear_segment()?;
        self.session_cycle = 0;
        Ok(())
    }

    pub fn build_image(&mut self, pc: u32) -> MemoryImage {
        // self.faults.dump();

        // Write all dirty pages back to the memory image.
        for page_idx in self.faults.writes.iter() {
            if let Some(page) = self.pages[*page_idx as usize].as_ref() {
                log::debug!("flush page: 0x{page_idx:08x}");
                let info = &self.image.info;
                let addr = info.get_page_addr(*page_idx);
                self.image.store_region_in_page(addr, &page.buf);
            }
        }

        // Write the system register file to the system page.
        let mut bytes = [0_u8; WORD_SIZE * REG_MAX];
        for idx in 0..REG_MAX {
            bytes[idx * WORD_SIZE..(idx + 1) * WORD_SIZE]
                .copy_from_slice(&self.registers[idx].to_le_bytes());
        }
        let sys_addr = SYSTEM.start() as u32;
        self.image.store_region_in_page(sys_addr, &bytes);

        // Update the merkle tree and PC.
        self.image
            .hash_pages_iter(self.faults.writes.iter().cloned());
        self.image.pc = pc;
        self.image.clone()
    }
}

impl Memory for MemoryMonitor {
    fn read_mem(&mut self, addr: u32, size: MemAccessSize) -> Option<u32> {
        // log::trace!("read_mem: 0x{addr:08x}");
        if !is_guest_memory(addr) {
            return None;
        }
        match size {
            MemAccessSize::Byte => self.load_u8(addr).map(|x| x as u32).ok(),
            MemAccessSize::HalfWord => self.load_u16(addr).map(|x| x as u32).ok(),
            MemAccessSize::Word => self.load_u32(addr).ok(),
        }
    }

    fn write_mem(&mut self, addr: u32, size: MemAccessSize, store_data: u32) -> bool {
        // log::trace!("write_mem: 0x{addr:08x} <= 0x{store_data:08x}");
        if !is_guest_memory(addr) {
            return false;
        }
        match size {
            MemAccessSize::Byte => self.store_u8(addr, store_data as u8),
            MemAccessSize::HalfWord => self.store_u16(addr, store_data as u16),
            MemAccessSize::Word => self.store_u32(addr, store_data),
        }
        .is_ok()
    }
}

impl SyscallContext for MemoryMonitor {
    fn get_cycle(&self) -> usize {
        self.session_cycle
    }

    fn load_register(&mut self, idx: usize) -> u32 {
        self.registers[idx]
    }

    fn load_u32(&mut self, addr: u32) -> Result<u32> {
        MemoryMonitor::load_u32(self, addr)
    }

    fn load_u8(&mut self, addr: u32) -> Result<u8> {
        MemoryMonitor::load_u8(self, addr)
    }
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
