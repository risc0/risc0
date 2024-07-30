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

extern crate alloc;

use alloc::{collections::BTreeMap, vec, vec::Vec};

use anyhow::{anyhow, ensure, Result};
use risc0_zkp::core::{
    digest::Digest,
    hash::sha::{Impl, Sha256, BLOCK_BYTES, SHA256_INIT},
};
use risc0_zkvm_platform::{
    memory::{GUEST_MAX_MEM, MEM_SIZE, PAGE_TABLE},
    syscall::DIGEST_BYTES,
    PAGE_SIZE,
};
use serde::{Deserialize, Serialize};

use crate::{elf::Program, Digestible, SystemState};

/// An image of a zkVM guest's memory
///
/// This is an image of the full memory state of the zkVM, including the data,
/// text, inputs, page table, and system memory. In addition to the memory image
/// proper, this includes some metadata about the page table.
#[derive(Clone, Serialize, Deserialize)]
pub struct MemoryImage {
    /// Sparse memory image as a map from page index to page.
    pub pages: BTreeMap<u32, Vec<u8>>,

    /// Metadata about the structure of the page table
    pub info: PageTableInfo,

    /// Program Counter from [Program] entry point
    pub pc: u32,
}

#[derive(Clone, Serialize, Deserialize)]
struct PersistentPageTableInfo;

/// Structure representing the page table for zkVM memory.
///
/// The notion of pages is borrowed from common operating system memory management, and the zkVM
/// organizes memory into a series of memory pages similarly. In the zkVM, the "page table" is
/// backed by a Merkle tree that verifies memory that is loaded into memory, or stored between
/// segments.
#[derive(Clone, Serialize, Deserialize)]
#[serde(try_from = "PersistentPageTableInfo", into = "PersistentPageTableInfo")]
pub struct PageTableInfo {
    /// Size of each page, in bytes.
    pub page_size: u32,
    page_size_po2: u32,
    /// Starting address for the page table in the memory space.
    pub page_table_addr: u32,
    _page_table_size: u32,
    /// Address of the root page, which is the top layer of the Merkle tree.
    pub root_addr: u32,
    /// Page index of the root page.
    pub root_idx: u32,
    root_page_addr: u32,
    /// Total number of pages covered by this page table.
    pub num_pages: u32,
    /// Number of entries in the root page. The root page may not be full, if the memory space is
    /// smaller than what the full number of entries could cover.
    pub num_root_entries: u32,
    _layers: Vec<u32>,
    /// Hash of an uninitialized page containing all zeros.
    zero_page_hash: Digest,
}

impl TryFrom<PersistentPageTableInfo> for PageTableInfo {
    type Error = anyhow::Error;

    fn try_from(_value: PersistentPageTableInfo) -> Result<Self, Self::Error> {
        Ok(PageTableInfo::default())
    }
}

impl From<PageTableInfo> for PersistentPageTableInfo {
    fn from(_value: PageTableInfo) -> Self {
        Self
    }
}

/// Compute and return the ImageID of the given `(merkle_root, pc)` pair.
fn compute_image_id(merkle_root: &Digest, pc: u32) -> Digest {
    SystemState {
        merkle_root: *merkle_root,
        pc,
    }
    .digest::<Impl>()
}

/// Compute `ceil(a / b)` via truncated integer division.
const fn div_ceil(a: u32, b: u32) -> u32 {
    (a + b - 1) / b
}

/// Round `a` up to the nearest multiple of `b`.
const fn round_up(a: u32, b: u32) -> u32 {
    div_ceil(a, b) * b
}

impl Default for PageTableInfo {
    fn default() -> Self {
        Self::new(PAGE_TABLE.start() as u32, PAGE_SIZE as u32).unwrap()
    }
}

impl PageTableInfo {
    /// Crate a new page table info struct with the given address and page size.
    pub fn new(page_table_addr: u32, page_size: u32) -> Result<Self> {
        let max_mem = page_table_addr;
        ensure!(max_mem >= page_size, "Max memory must be at least one page");
        ensure!(
            page_size > 0 && (page_size & (page_size - 1)) == 0,
            "Page size must be a power of 2"
        );

        let mut layers = Vec::new();
        let mut page_table_size = 0u32;
        let mut remain = max_mem;
        while remain >= page_size {
            let num_pages = remain / page_size;
            remain = num_pages
                .checked_mul(DIGEST_BYTES as u32)
                .ok_or(anyhow!("Invalid page_size specified"))?;
            layers.push(remain);
            page_table_size += remain;
        }
        let max_mem = max_mem + page_table_size;
        let num_pages = max_mem / page_size;
        let page_table_size = round_up(page_table_size, BLOCK_BYTES as u32);
        let root_addr = page_table_addr + page_table_size;
        let root_idx = root_addr / page_size;
        let root_page_addr = root_idx * page_size;
        let num_root_entries = (root_addr - root_page_addr) / DIGEST_BYTES as u32;
        ensure!(root_idx == num_pages, "Invalid root index");
        let zero_page_hash = hash_page_bytes(&vec![0_u8; page_size as usize]);

        tracing::debug!("root_page_addr: 0x{root_page_addr:08x}, root_addr: 0x{root_addr:08x}");

        Ok(Self {
            page_size,
            page_size_po2: page_size.ilog2(),
            page_table_addr,
            _page_table_size: page_table_size,
            root_addr,
            root_idx,
            root_page_addr,
            num_pages,
            num_root_entries,
            _layers: layers,
            zero_page_hash,
        })
    }

    /// Calculate the page address given its index.
    pub fn get_page_addr(&self, page_idx: u32) -> u32 {
        page_idx * self.page_size
    }

    /// Calculate the index given its address.
    pub fn get_page_index(&self, addr: u32) -> u32 {
        addr >> self.page_size_po2
    }

    /// Calculate the index of the page that contains the hash of this page.
    pub fn get_page_entry_addr(&self, page_idx: u32) -> u32 {
        self.page_table_addr + page_idx * DIGEST_BYTES as u32
    }
}

impl MemoryImage {
    /// Construct the initial memory image for `program`
    ///
    /// The result is a MemoryImage with the ELF of `program` loaded (but
    /// execution not yet begun), and with the page table Merkle tree
    /// constructed.
    pub fn new(program: &Program, page_size: u32) -> Result<Self> {
        // Compute the page table hashes except for the very last root hash.
        let info = PageTableInfo::new(PAGE_TABLE.start() as u32, page_size)?;
        let mut img = Self {
            pages: BTreeMap::new(),
            info,
            pc: program.entry,
        };

        // Load the ELF into the memory image.
        for (&addr, &data) in program.image.iter() {
            if addr as usize >= GUEST_MAX_MEM {
                anyhow::bail!("Invalid Elf Program, address outside GUEST_MAX_MEM");
            }
            img.store_region_in_page(addr, &data.to_le_bytes());
        }

        img.hash_pages();
        Ok(img)
    }

    /// Load a page specified by page_idx. If no page is found, a zero page is
    /// returned.
    pub fn load_page(&self, page_idx: u32) -> Vec<u8> {
        self.pages
            .get(&page_idx)
            .cloned()
            .unwrap_or_else(|| vec![0; self.info.page_size as usize])
    }

    /// Writes the given byte array in this memory image at the given
    /// address.  The caller is responsible for ensuring the bytes do
    /// not overlap a page boundary.
    pub fn store_region_in_page(&mut self, addr: u32, bytes: &[u8]) {
        let page_idx = self.info.get_page_index(addr);
        let page = self.pages.entry(page_idx).or_insert_with(|| {
            if addr as usize >= MEM_SIZE {
                panic!("address {addr:08X} outside MEM_SIZE")
            }
            vec![0_u8; self.info.page_size as usize]
        });
        let page_start = self.info.get_page_addr(page_idx);
        page[(addr - page_start) as usize..(addr - page_start) as usize + bytes.len()]
            .clone_from_slice(bytes);
    }

    /// Reads the given byte array in this memory image at the given
    /// address  The caller is responsible for ensuring the bytes do
    /// not overlap a page boundary.
    pub fn load_region_in_page(&self, addr: u32, bytes: &mut [u8]) -> Result<()> {
        let page_idx = self.info.get_page_index(addr);
        let page_start = self.info.get_page_addr(page_idx);

        if let Some(page) = self.pages.get(&page_idx) {
            bytes.clone_from_slice(
                &page[(addr - page_start) as usize..(addr - page_start) as usize + bytes.len()],
            );
        } else {
            ensure!(
                addr as usize <= MEM_SIZE,
                "address {addr:08X} outside MEM_SIZE ({MEM_SIZE:08X})"
            );
            bytes.fill(0);
        }

        Ok(())
    }

    /// Calculate and update the image merkle tree within this image.
    pub fn hash_pages(&mut self) {
        self.hash_pages_iter(0..self.info.num_pages)
    }

    /// Calculate and update the image merkle tree within this image based on
    /// the supplied page indices.
    pub fn hash_pages_iter<I: Iterator<Item = u32>>(&mut self, iter: I) {
        for page_idx in iter {
            self.update_page(page_idx);
        }
    }

    /// Calculate and update the image merkle tree within this image based on
    /// the supplied page index.
    pub fn update_page(&mut self, page_idx: u32) {
        let digest = self.hash_page(page_idx);
        let entry_addr = self.info.get_page_entry_addr(page_idx);
        self.store_region_in_page(entry_addr, digest.as_bytes());
    }

    fn hash_page(&self, page_idx: u32) -> Digest {
        if let Some(page) = self.pages.get(&page_idx) {
            hash_page_bytes(page)
        } else {
            self.info.zero_page_hash
        }
    }

    /// Verify the integrity of the MemoryImage.
    ///
    /// Confirms that the page table is a valid Merkle tree with the expected
    /// root and that the data from each page hashes to the expected page table
    /// entry.
    #[cfg(test)]
    fn check(&self, addr: u32) -> Result<()> {
        let mut page_idx = self.info.get_page_index(addr);
        while page_idx < self.info.root_idx {
            let page_addr = self.info.get_page_addr(page_idx);
            let expected = self.hash_page(page_idx);
            let entry_addr = self.info.get_page_entry_addr(page_idx);
            let mut entry = [0_u8; DIGEST_BYTES];
            self.load_region_in_page(entry_addr, &mut entry)?;
            let actual = Digest::try_from(entry)?;
            tracing::debug!(
                "page_idx: {page_idx}, page_addr: 0x{page_addr:08x} entry_addr: 0x{entry_addr:08x}"
            );
            if expected != actual {
                anyhow::bail!("Invalid page table entry: {} != {}", expected, actual);
            }
            page_idx = self.info.get_page_index(entry_addr);
        }

        let root_page_addr = self.info.root_page_addr;
        let root_page_bytes = self.info.num_root_entries * DIGEST_BYTES as u32;
        let mut root_page = vec![0_u8; root_page_bytes as usize];
        self.load_region_in_page(root_page_addr, &mut root_page)?;
        let expected = hash_page_bytes(&root_page);
        let root = self.compute_root_hash();
        if expected != root {
            anyhow::bail!("Invalid root hash: {} != {}", expected, root);
        }

        Ok(())
    }

    /// Compute and return the root merkle entry of this image.
    pub fn compute_root_hash(&self) -> Digest {
        let root_page = self
            .pages
            .get(&self.info.root_idx)
            .expect("Missing root page?");
        hash_page_bytes(&root_page[..(self.info.root_addr - self.info.root_page_addr) as usize])
    }

    /// Compute and return the ImageID of this image.
    pub fn compute_id(&self) -> Digest {
        compute_image_id(&self.compute_root_hash(), self.pc)
    }

    /// Return the [SystemState] for this image.
    pub fn get_system_state(&self) -> SystemState {
        SystemState {
            merkle_root: self.compute_root_hash(),
            pc: self.pc,
        }
    }
}

fn hash_page_bytes(page: &[u8]) -> Digest {
    let mut state = SHA256_INIT;
    assert!(page.len() % BLOCK_BYTES == 0);
    for block in page.chunks_exact(BLOCK_BYTES) {
        let block1 = Digest::try_from(&block[0..DIGEST_BYTES]).unwrap();
        let block2 = Digest::try_from(&block[DIGEST_BYTES..BLOCK_BYTES]).unwrap();
        state = *Impl::compress(&state, &block1, &block2);
    }
    state
}

#[cfg(test)]
mod tests {
    use risc0_zkvm_methods::MULTI_TEST_ELF;
    use risc0_zkvm_platform::{
        memory::{GUEST_MAX_MEM, PAGE_TABLE, STACK_TOP, SYSTEM, TEXT_START},
        syscall::DIGEST_BYTES,
    };
    use test_log::test;

    use crate::{elf::Program, image::PageTableInfo, MemoryImage};

    fn page_table_size(max_mem: u32, page_size: u32) -> u32 {
        PageTableInfo::new(max_mem, page_size)
            .unwrap()
            ._page_table_size
    }

    #[test]
    fn check_integrity() {
        const PAGE_SIZE: u32 = 1024;
        let program = Program::load_elf(MULTI_TEST_ELF, GUEST_MAX_MEM as u32).unwrap();
        let prog_pc = program.entry;
        let image = MemoryImage::new(&program, PAGE_SIZE).unwrap();
        assert_eq!(image.pc, prog_pc);

        // This is useful in case one needs to manually inspect the memory image.
        // std::fs::write("/tmp/test.img", &image.image).unwrap();
        image.check(TEXT_START).unwrap();
        image.check(STACK_TOP).unwrap();
        image.check(TEXT_START + 5000).unwrap();
        image.check(SYSTEM.start() as u32).unwrap();
        image.check(image.info.root_page_addr).unwrap();
    }

    #[test]
    fn page_table_info() {
        const PAGE_SIZE_1K: u32 = 1024;
        let info = PageTableInfo::new(PAGE_TABLE.start() as u32, PAGE_SIZE_1K).unwrap();
        assert_eq!(info._page_table_size, 7035584);
        assert_eq!(info._page_table_size / PAGE_SIZE_1K, 6870);
        assert_eq!(info._page_table_size / PAGE_SIZE_1K * PAGE_SIZE_1K, 7034880);
        assert_eq!(info._layers, vec![6815744, 212992, 6656, 192]);
        assert_eq!(info.root_addr, 0xd6b5ac0);
        assert_eq!(info.root_page_addr, 0xd6b5800);
        assert_eq!(info.num_root_entries, 22);
        assert_eq!(info.root_idx, 219862);
    }

    #[test]
    fn page_size_1k() {
        const PAGE_SIZE_1K: u32 = 1024;
        assert_eq!(
            page_table_size(PAGE_SIZE_1K, PAGE_SIZE_1K),
            DIGEST_BYTES as u32 * 2
        );
        assert_eq!(
            page_table_size(PAGE_SIZE_1K * 2, PAGE_SIZE_1K),
            DIGEST_BYTES as u32 * 2
        );
        assert_eq!(
            page_table_size(PAGE_SIZE_1K * 256, PAGE_SIZE_1K),
            DIGEST_BYTES as u32 * 256 + 256
        );
        // max_mem: 256M, page: 1K bytes
        // Layer 1: 256M / 1K = 256K pages => 256K * 32 =   8M
        // Layer 2:   8M / 1K =   8K pages =>   8K * 32 = 256K
        // Layer 3: 256K / 1K =  256 pages =>  256 * 32 =   8K
        // Layer 4:   8K / 1K =    8 pages =>    8 * 32 =  256
        let info = PageTableInfo::new(256 * 1024 * 1024, PAGE_SIZE_1K).unwrap();
        assert_eq!(
            info._layers,
            vec![8 * 1024 * 1024, 256 * 1024, 8 * 1024, 256]
        );
        assert_eq!(
            info._page_table_size,
            8 * 1024 * 1024 + 256 * 1024 + 8 * 1024 + 256
        );
    }

    #[test]
    fn page_size_4k() {
        const PAGE_SIZE_4K: u32 = 4 * 1024;
        assert_eq!(
            page_table_size(PAGE_SIZE_4K, PAGE_SIZE_4K),
            DIGEST_BYTES as u32 * 2
        );
        assert_eq!(
            page_table_size(PAGE_SIZE_4K * 2, PAGE_SIZE_4K),
            DIGEST_BYTES as u32 * 2
        );
        assert_eq!(
            page_table_size(2 * 1024 * 1024, PAGE_SIZE_4K),
            16 * 1024 + 128
        );
        // max_mem: 256M, page: 4K bytes
        // Layer 1: 256M / 4K =  64K pages =>  64K * 32 =   2M
        // Layer 2:   2M / 4K =  512 pages =>  512 * 32 =  16K
        // Layer 3:  16K / 4K =    4 pages =>    4 * 32 =  128
        let info = PageTableInfo::new(256 * 1024 * 1024, PAGE_SIZE_4K).unwrap();
        assert_eq!(info._layers, vec![2 * 1024 * 1024, 16 * 1024, 128]);
        assert_eq!(info._page_table_size, 2 * 1024 * 1024 + 16 * 1024 + 128);
    }

    #[test]
    fn page_size_1k_fractional() {
        const PAGE_SIZE_1K: u32 = 1024;

        // max_mem: 6656, page: 1K bytes
        // Layer 1: 6656 / 1K = 6 pages => 6 * 32 = 192

        // 0x0000..0x0400 -> P0
        // 0x0400..0x0800 -> P1
        // 0x0800..0x0C00 -> P2
        // 0x0C00..0x1000 -> P3
        // 0x1000..0x1400 -> P4
        // 0x1400..0x1800 -> P5
        // 0x1800..0x1AC0 -> P6 (fractional)

        // 0x1A00: P0
        // 0x1A20: P1
        // 0x1A40: P2
        // 0x1A60: P3
        // 0x1A80: P4
        // 0x1AA0: P5
        // 0x1AC0: Root

        let info = PageTableInfo::new(0x1A00, PAGE_SIZE_1K).unwrap();
        assert_eq!(info._layers, vec![192]);
        assert_eq!(info._page_table_size, 192);
        assert_eq!(info.root_addr, 0x1AC0);
        assert_eq!(info.root_page_addr, 0x1800);
        assert_eq!(
            info.num_root_entries,
            (0x1A00 - 0x1800) / DIGEST_BYTES as u32 + 6
        );
    }

    #[test]
    #[should_panic(expected = "exceeds maximum address for guest programs")]
    fn test_fuzzing_oob_idx_bug() {
        let data = b"\x7f\x45\x4c\x46\x01\x01\x01\x01\x01\x01\xff\xff\x00\x00\x00\x00\x02\x00\xf3\x00\x00\x00\x00\x00\x00\x00\x01\x01\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x04\x20\x00\x08\x00\x00\x00\x96\x96\x00\x94\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\xff\x00\x00\x94\x00\x00\x00\xff\xf6\x12\xa9\x00\x00\x00\x00\x00\x00\xfe\x00\x00\x00\x00\x00\x0a\x9a\x38\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x96\x4c\x46\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x04\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x0a\x9d\xd8\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x40\x1e\x00\x00\x46\x4c\x00\x00\x00\x00\x00\x02\x00\x40\x00\x01\x01\x01\x00\x04\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x05\x00\x00\x07\x78\xc1\x0a\x00\x00\xba\x00\x00\x00\x00\xe3\x04\x00\x00\x31\x35\x32\x37\x38\x31\x46\x01\x01\x01\x01\x01\x01\xff\xff\x00\x00\x00\x00\x02\x00\xe5\x00\x00\x00\x00\x96\x96\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x04\x00\x00\x00\x00\x00\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x0b\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x06\x2e\xac\x00\x00\x00\x00\x00\x00\x0a\xce\x58\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x40\x1e\x1e\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x40\x00\x00\x00\x00\x00\x04\x00\x00\x00\x00\x00\x00\x05\x00\x00\x07\x00\xba\xe8\xad\x0a\x00\xe3\x04\x00\x00\x00\x00\x12\x00\x00\x00\x00\x08\x00\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x05\x00\x00\x00\x01\x01\x01\x50\xcf\x0a\x00\x01\x01\x01\x01\x01\x01\x01\x01\x00\x00\x00\x00\x00\x00\x00\x04\x01\x01\x01\x01\x01\x01\x01\x00\x00\x31\x35\x31\x35\x32\x37\x38\x31\x30\x34\x02\x00\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x05\x00\x00\x00\x01\x01\x01\x01\x01\x01\x01\x00\x00\x00\x00\x00\x00\x07\x00\x00\x00\xff\xff\xff\xff\x00\x00\x00\x00\xff\x04\x92\x01\x01\x01\x01\x01\x01\xa2\xf8\x00\x20\x00\x00\x00\x00\xff\x00\x40\x00\x04\x00\x00\x00\x38\x00\x00\x00\x00\x00\x00\x00\x02\x00\x0a\x40\x40\x00\x1a\x00\x19\x00";
        const PAGE_SIZE: u32 = 1024;
        let prog = Program::load_elf(data, GUEST_MAX_MEM as u32).unwrap();
        MemoryImage::new(&prog, PAGE_SIZE).unwrap();
    }
}
