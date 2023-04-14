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
use risc0_zkvm_platform::{memory::SYSTEM, WORD_SIZE};
use rrs_lib::{MemAccessSize, Memory};

use super::{io::SyscallContext, OpCodeResult, SyscallRecord};
use crate::{binfmt::image::PageTableInfo, session::PageFaults, MemoryImage};

#[derive(Eq, Ord, PartialEq, PartialOrd)]
struct MemStore {
    addr: u32,
    data: u8,
}

pub struct MemoryMonitor {
    pub image: MemoryImage,
    pub(crate) faults: PageFaults,
    pending_faults: PageFaults,
    pending_writes: BTreeSet<MemStore>,
    cycle: usize,
    op_result: Option<OpCodeResult>,
    pub syscalls: Vec<SyscallRecord>,
}

impl MemoryMonitor {
    pub fn new(image: MemoryImage) -> Self {
        Self {
            image,
            faults: PageFaults::new(),
            pending_faults: PageFaults::new(),
            pending_writes: BTreeSet::new(),
            cycle: 0,
            op_result: None,
            syscalls: Vec::new(),
        }
    }

    pub fn load_u8(&mut self, addr: u32) -> u8 {
        let info = &self.image.info;
        self.pending_faults.include(info, addr, IncludeDir::Read);
        self.image.buf[addr as usize]
    }

    pub fn load_u16(&mut self, addr: u32) -> u16 {
        assert_eq!(addr % 2, 0, "unaligned load");
        u16::from_le_bytes(self.load_array(addr))
    }

    pub fn load_u32(&mut self, addr: u32) -> u32 {
        assert_eq!(addr % WORD_SIZE as u32, 0, "unaligned load");
        u32::from_le_bytes(self.load_array(addr))
    }

    pub fn load_array<const N: usize>(&mut self, addr: u32) -> [u8; N] {
        array::from_fn(|idx| self.load_u8(addr + idx as u32))
    }

    pub fn load_register(&mut self, idx: usize) -> u32 {
        self.load_u32(get_register_addr(idx))
    }

    pub fn load_registers<const N: usize>(&mut self, idxs: [usize; N]) -> [u32; N] {
        idxs.map(|idx| self.load_register(idx))
    }

    pub fn load_string(&mut self, mut addr: u32) -> Result<String> {
        let mut s: Vec<u8> = Vec::new();
        loop {
            let b = self.load_u8(addr);
            if b == 0 {
                break;
            }
            s.push(b);
            addr += 1;
        }
        String::from_utf8(s).map_err(anyhow::Error::msg)
    }

    pub fn store_u8(&mut self, addr: u32, data: u8) {
        let info = &self.image.info;
        self.pending_faults.include(info, addr, IncludeDir::Write);
        self.pending_writes.insert(MemStore { addr, data });
    }

    pub fn store_u16(&mut self, addr: u32, data: u16) {
        assert_eq!(addr % 2, 0, "unaligned store");
        self.store_region(addr, &data.to_le_bytes());
    }

    pub fn store_u32(&mut self, addr: u32, data: u32) {
        assert_eq!(addr % WORD_SIZE as u32, 0, "unaligned store");
        self.store_region(addr, &data.to_le_bytes());
    }

    pub fn store_region(&mut self, addr: u32, slice: &[u8]) {
        slice
            .iter()
            .enumerate()
            .for_each(|(i, x)| self.store_u8(addr + i as u32, *x));
    }

    pub fn store_register(&mut self, idx: usize, data: u32) {
        self.store_u32(get_register_addr(idx), data);
    }

    pub fn save_op(&mut self, op_result: OpCodeResult) {
        self.op_result = Some(op_result);
    }

    pub fn restore_op(&self) -> Option<OpCodeResult> {
        self.op_result.clone()
    }

    // commit all pending activity
    pub fn commit(&mut self, cycle: usize) {
        for op in self.pending_writes.iter() {
            self.image.buf[op.addr as usize] = op.data;
        }
        self.pending_writes.clear();
        self.faults.append(&mut self.pending_faults);
        self.cycle = cycle;
        let op_result = self.op_result.take().unwrap();
        if let Some(syscall) = op_result.syscall {
            self.syscalls.push(syscall);
        }
        // self.faults.dump();
    }

    pub fn total_faults(&self) -> usize {
        let reads = self.faults.reads.union(&self.pending_faults.reads).count();
        let writes = self
            .faults
            .writes
            .union(&self.pending_faults.writes)
            .count();
        reads + writes
    }

    pub fn clear(&mut self) {
        self.faults.clear();
        self.pending_writes.clear();
        self.pending_faults.clear();
        self.syscalls.clear();
    }

    pub fn clear_pending_faults(&mut self) {
        self.pending_faults.clear();
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
        self.cycle
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

enum IncludeDir {
    Read,
    Write,
}

impl PageFaults {
    pub fn new() -> Self {
        Self {
            reads: BTreeSet::new(),
            writes: BTreeSet::new(),
        }
    }

    fn include(&mut self, info: &PageTableInfo, addr: u32, dir: IncludeDir) {
        let mut addr = addr;
        loop {
            let page_idx = info.get_page_index(addr);
            let entry_addr = info.get_page_entry_addr(page_idx);
            match dir {
                IncludeDir::Read => self.reads.insert(page_idx),
                IncludeDir::Write => self.writes.insert(page_idx),
            };
            if page_idx == info.root_idx {
                break;
            }
            addr = entry_addr;
        }
    }

    fn clear(&mut self) {
        self.reads.clear();
        self.writes.clear();
    }

    fn append(&mut self, rhs: &mut Self) {
        self.reads.append(&mut rhs.reads);
        self.writes.append(&mut rhs.writes);
    }

    #[allow(dead_code)]
    fn dump(&self) {
        log::debug!("PageFaultInfo");
        log::debug!("  reads>");
        for idx in self.reads.iter().rev() {
            log::debug!("  0x{:08X}", idx);
        }
        log::debug!("  writes>");
        for idx in self.writes.iter().rev() {
            log::debug!("  0x{:08X}", idx);
        }
    }
}
