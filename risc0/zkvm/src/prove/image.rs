// Copyright 2022 RISC Zero, Inc.
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

use anyhow::{bail, Result};
use risc0_zkp::core::sha::{Digest, Sha, BLOCK_SIZE, SHA256_INIT};
use risc0_zkvm_platform::{
    memory::{MEM_SIZE, PAGE_TABLE, STACK},
    syscall::DIGEST_BYTES,
    WORD_SIZE,
};

use crate::{prove::elf::Program, sha};

/// Compute `ceil(a / b)` via truncated integer division.
const fn div_ceil(a: usize, b: usize) -> usize {
    (a + b - 1) / b
}

/// Round `a` up to the nearest multipe of `b`.
const fn round_up(a: usize, b: usize) -> usize {
    div_ceil(a, b) * b
}

pub struct PageTableInfo {
    pub mem_start: usize,
    pub page_size: usize,
    page_table_addr: usize,
    _page_table_size: usize,
    root_addr: usize,
    root_offset: usize,
    pub root_idx: usize,
    root_page_addr: usize,
    num_pages: usize,
    num_root_entries: usize,
    _layers: Vec<usize>,
}

impl PageTableInfo {
    pub fn new(mem_start: usize, page_table_addr: usize, page_size: usize) -> Self {
        let max_mem = page_table_addr - mem_start;
        assert!(max_mem >= page_size);

        let mut layers = Vec::new();
        let mut page_table_size = 0;
        let mut remain = max_mem;
        while remain >= page_size {
            let num_pages = remain / page_size;
            remain = num_pages * DIGEST_BYTES;
            layers.push(remain);
            page_table_size += remain;
        }
        let max_mem = max_mem + page_table_size;
        let num_pages = max_mem / page_size;
        let final_addr = page_table_addr + page_table_size;
        let page_table_size = round_up(page_table_size, BLOCK_SIZE);
        let root_addr = page_table_addr + page_table_size;
        let root_idx = (root_addr - mem_start) / page_size;
        let root_page_addr = root_idx * page_size + mem_start;
        let num_root_entries = (root_addr - root_page_addr) / DIGEST_BYTES;
        let root_offset = (root_addr - final_addr) / DIGEST_BYTES;
        assert_eq!(root_idx, num_pages);

        log::debug!("root_page_addr: 0x{root_page_addr:08x}, root_addr: 0x{root_addr:08x}");

        Self {
            mem_start,
            page_size,
            page_table_addr,
            _page_table_size: page_table_size,
            root_addr,
            root_offset,
            root_idx,
            root_page_addr,
            num_pages,
            num_root_entries,
            _layers: layers,
        }
    }

    pub fn get_page_addr(&self, page_idx: usize) -> usize {
        page_idx * self.page_size + self.mem_start
    }

    pub fn get_page_index(&self, addr: usize) -> usize {
        assert!(
            addr >= self.mem_start,
            "0x{addr:08x} >= 0x{:08x}",
            self.mem_start
        );
        (addr - self.mem_start) / self.page_size
    }

    pub fn get_page_entry_addr(&self, page_idx: usize) -> usize {
        self.page_table_addr + page_idx * DIGEST_BYTES
    }

    pub fn get_page_info(&self, addr: u32) -> (u32, u32) {
        if addr == self.root_page_addr as u32 {
            ((self.num_root_entries / 2) as u32, self.root_offset as u32)
        } else {
            ((self.page_size / BLOCK_SIZE) as u32, 0)
        }
    }
}

pub struct MemoryImage {
    pub image: Vec<u8>,
    pub root: Digest,
    pub info: PageTableInfo,
}

impl MemoryImage {
    pub fn new(program: &Program, page_size: usize) -> Self {
        let mut image = vec![0_u8; MEM_SIZE];

        // Load the ELF into the memory image.
        for (addr, data) in program.image.iter() {
            let addr = *addr as usize;
            let bytes = data.to_le_bytes();
            for i in 0..WORD_SIZE {
                image[addr + i] = bytes[i];
            }
        }

        // Compute the page table hashes except for the very last root hash.
        let info = PageTableInfo::new(STACK.start(), PAGE_TABLE.start(), page_size);
        for i in 0..info.num_pages {
            let page_addr = info.get_page_addr(i);
            let page = &image[page_addr..page_addr + page_size];
            let digest = hash_page(page);
            let entry_addr = info.get_page_entry_addr(i);
            image[entry_addr..entry_addr + DIGEST_BYTES].copy_from_slice(digest.as_bytes());
        }

        // Now compute the final root hash.
        let root_page_addr = info.root_page_addr;
        let root_page = &image[root_page_addr..info.root_addr];
        let root = hash_page(root_page);
        log::debug!("image_id: {root:?}");

        Self { image, root, info }
    }

    pub fn check(&self, addr: usize) -> Result<()> {
        let mut page_idx = self.info.get_page_index(addr);
        while page_idx < self.info.root_idx {
            let page_addr = self.info.get_page_addr(page_idx);
            let page = &self.image[page_addr..page_addr + self.info.page_size];
            let expected = hash_page(page);
            let entry_addr = self.info.get_page_entry_addr(page_idx);
            let entry = &self.image[entry_addr..entry_addr + DIGEST_BYTES];
            let actual = Digest::from_bytes(entry);
            log::debug!(
                "page_idx: {page_idx}, page_addr: 0x{page_addr:08x} entry_addr: 0x{entry_addr:08x}"
            );
            if expected != actual {
                bail!("Invalid page table entry: {} != {}", expected, actual);
            }
            page_idx = self.info.get_page_index(entry_addr);
        }

        let root_page_addr = self.info.root_page_addr;
        let root_page_bytes = self.info.num_root_entries * DIGEST_BYTES;
        let root_page = &self.image[root_page_addr..root_page_addr + root_page_bytes];
        let expected = hash_page(root_page);
        if expected != self.root {
            bail!("Invalid root hash: {} != {}", expected, self.root);
        }

        Ok(())
    }
}

fn hash_page(page: &[u8]) -> Digest {
    let sha = sha::sha();
    let mut state = SHA256_INIT;
    assert!(page.len() % BLOCK_SIZE == 0);
    for block in page.chunks_exact(BLOCK_SIZE) {
        let block1 = Digest::from_bytes(&block[0..DIGEST_BYTES]);
        let block2 = Digest::from_bytes(&block[DIGEST_BYTES..BLOCK_SIZE]);
        state = *sha.compress(&state, &block1, &block2);
    }
    state
}

#[cfg(test)]
mod tests {
    use risc0_zkvm_methods::MULTI_TEST_ELF;
    use risc0_zkvm_platform::{
        memory::{DATA, PAGE_TABLE, STACK, SYSTEM, TEXT},
        syscall::DIGEST_BYTES,
    };
    use test_log::test;

    use super::MemoryImage;
    use crate::prove::{elf::Program, image::PageTableInfo};

    fn page_table_size(max_mem: usize, page_size: usize) -> usize {
        PageTableInfo::new(0, max_mem, page_size)._page_table_size
    }

    #[test]
    fn check_integrity() {
        const PAGE_SIZE: usize = 1024;
        let program = Program::load_elf(MULTI_TEST_ELF, TEXT.end() as u32).unwrap();
        let image = MemoryImage::new(&program, PAGE_SIZE);
        // This is useful in case one needs to manually inspect the memory image.
        // std::fs::write("/tmp/test.img", &image.image).unwrap();
        image.check(STACK.start()).unwrap();
        image.check(DATA.start()).unwrap();
        image.check(TEXT.start()).unwrap();
        image.check(TEXT.start() + 5000).unwrap();
        image.check(SYSTEM.start()).unwrap();
        image.check(image.info.root_page_addr).unwrap();
    }

    #[test]
    fn page_table_info() {
        const PAGE_SIZE_1K: usize = 1024;
        let info = PageTableInfo::new(STACK.start(), PAGE_TABLE.start(), PAGE_SIZE_1K);
        assert_eq!(info._page_table_size, 5953216);
        assert_eq!(info._page_table_size / PAGE_SIZE_1K, 5813);
        assert_eq!(info._page_table_size / PAGE_SIZE_1K * PAGE_SIZE_1K, 5952512);
        assert_eq!(info._layers, vec![5767168, 180224, 5632, 160]);
        assert_eq!(info.root_addr, 0xd5ad6c0);
        assert_eq!(info.root_page_addr, 0xd5ad400);
        assert_eq!(info.num_root_entries, 22);
        assert_eq!(info.root_idx, 186037);
    }

    #[test]
    fn page_size_1k() {
        const PAGE_SIZE_1K: usize = 1024;
        assert_eq!(
            page_table_size(PAGE_SIZE_1K, PAGE_SIZE_1K),
            DIGEST_BYTES * 2
        );
        assert_eq!(
            page_table_size(PAGE_SIZE_1K * 2, PAGE_SIZE_1K),
            DIGEST_BYTES * 2
        );
        assert_eq!(
            page_table_size(PAGE_SIZE_1K * 256, PAGE_SIZE_1K),
            DIGEST_BYTES * 256 + 256
        );
        // max_mem: 256M, page: 1K bytes
        // Layer 1: 256M / 1K = 256K pages => 256K * 32 =   8M
        // Layer 2:   8M / 1K =   8K pages =>   8K * 32 = 256K
        // Layer 3: 256K / 1K =  256 pages =>  256 * 32 =   8K
        // Layer 4:   8K / 1K =    8 pages =>    8 * 32 =  256
        let info = PageTableInfo::new(0, 256 * 1024 * 1024, PAGE_SIZE_1K);
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
        const PAGE_SIZE_4K: usize = 4 * 1024;
        assert_eq!(
            page_table_size(PAGE_SIZE_4K, PAGE_SIZE_4K),
            DIGEST_BYTES * 2
        );
        assert_eq!(
            page_table_size(PAGE_SIZE_4K * 2, PAGE_SIZE_4K),
            DIGEST_BYTES * 2
        );
        assert_eq!(
            page_table_size(2 * 1024 * 1024, PAGE_SIZE_4K),
            16 * 1024 + 128
        );
        // max_mem: 256M, page: 4K bytes
        // Layer 1: 256M / 4K =  64K pages =>  64K * 32 =   2M
        // Layer 2:   2M / 4K =  512 pages =>  512 * 32 =  16K
        // Layer 3:  16K / 4K =    4 pages =>    4 * 32 =  128
        let info = PageTableInfo::new(0, 256 * 1024 * 1024, PAGE_SIZE_4K);
        assert_eq!(info._layers, vec![2 * 1024 * 1024, 16 * 1024, 128]);
        assert_eq!(info._page_table_size, 2 * 1024 * 1024 + 16 * 1024 + 128);
    }

    #[test]
    fn page_size_1k_fractional() {
        const PAGE_SIZE_1K: usize = 1024;

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

        let info = PageTableInfo::new(0, 0x1A00, PAGE_SIZE_1K);
        assert_eq!(info._layers, vec![192]);
        assert_eq!(info._page_table_size, 192);
        assert_eq!(info.root_addr, 0x1AC0);
        assert_eq!(info.root_page_addr, 0x1800);
        assert_eq!(info.num_root_entries, (0x1A00 - 0x1800) / DIGEST_BYTES + 6);
    }
}
