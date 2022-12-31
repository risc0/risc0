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
use risc0_zkp::core::sha::{Digest, Sha};
use risc0_zkvm_platform::{
    memory::{MEM_SIZE, PAGE_TABLE, PROG},
    syscall::DIGEST_BYTES,
    WORD_SIZE,
};

use crate::{prove::elf::Program, sha};

struct PageTableInfo {
    page_size: usize,
    layers: Vec<usize>,
    total: usize,
}

impl PageTableInfo {
    pub fn new(max_mem: usize, page_size: usize) -> Self {
        assert!(max_mem >= page_size);

        let mut layers = Vec::new();
        let mut total = 0;
        let mut remain = max_mem;
        while remain >= page_size {
            let num_pages = remain / page_size;
            remain = num_pages * DIGEST_BYTES;
            layers.push(remain);
            total += remain;
        }

        Self {
            page_size,
            layers,
            total,
        }
    }
}

pub struct MemoryImage {
    pub image: Vec<u8>,
    pub root: Digest,
    info: PageTableInfo,
}

impl MemoryImage {
    pub fn new(elf_contents: &[u8], page_size: usize) -> Result<Self> {
        let program = Program::load_elf(elf_contents, PROG.end() as u32)?;
        let mut image = vec![0_u8; MEM_SIZE];

        // Load the ELF into the memory image.
        for (addr, data) in program.image {
            let addr = addr as usize;
            let bytes = data.to_le_bytes();
            for i in 0..WORD_SIZE {
                image[addr + i] = bytes[i];
            }
        }

        // TODO: load REG_PC
        // TODO: load SHA_K

        // Compute the page table hashes except for the very last root hash.
        let sha = sha::sha();
        let info = PageTableInfo::new(PAGE_TABLE.start(), page_size);
        let mem_size = PAGE_TABLE.start() + info.total;
        let num_pages = mem_size / page_size;
        for i in 0..num_pages {
            let digest = sha.hash_bytes(&image[i * page_size..(i + 1) * page_size]);
            let addr = PAGE_TABLE.start() + i * DIGEST_BYTES;
            image[addr..addr + DIGEST_BYTES].copy_from_slice(digest.as_bytes());
        }

        // Now compute the final root hash.
        let final_bytes = info.layers.last().unwrap();
        let final_page_addr = PAGE_TABLE.start() + info.total - final_bytes;
        let root = sha.hash_bytes(&image[final_page_addr..final_page_addr + final_bytes]);
        let root_addr = PAGE_TABLE.start() + info.total;
        image[root_addr..root_addr + DIGEST_BYTES].copy_from_slice(root.as_bytes());

        Ok(Self {
            image,
            root: *root,
            info,
        })
    }

    pub fn check(&self, page_idx: usize) -> Result<()> {
        let sha = sha::sha();

        let mut page_idx = page_idx;
        for _ in 0..self.info.layers.len() {
            let addr = page_idx * self.info.page_size;
            let page = &self.image[addr..addr + self.info.page_size];
            let expected = sha.hash_bytes(page);
            let page_table_addr = PAGE_TABLE.start() + page_idx * DIGEST_BYTES;
            let page_table_entry = &self.image[page_table_addr..page_table_addr + DIGEST_BYTES];
            let actual = Digest::from_bytes(page_table_entry);
            if *expected != actual {
                bail!("Invalid page table entry: {} != {}", *expected, actual);
            }
            page_idx = page_table_addr / self.info.page_size;
        }

        let final_bytes = self.info.layers.last().unwrap();
        let final_page_addr = PAGE_TABLE.start() + self.info.total - final_bytes;
        let final_page = &self.image[final_page_addr..final_page_addr + final_bytes];
        let expected = sha.hash_bytes(final_page);
        let root_addr = PAGE_TABLE.start() + self.info.total;
        let root_bytes = &self.image[root_addr..root_addr + DIGEST_BYTES];
        let actual = Digest::from_bytes(root_bytes);
        if *expected != actual {
            bail!("Invalid root hash: {} != {}", *expected, actual);
        }

        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use risc0_zkvm_methods::MULTI_TEST_ELF;
    use risc0_zkvm_platform::{
        memory::{PAGE_TABLE, PROG},
        syscall::DIGEST_BYTES,
    };

    use super::MemoryImage;
    use crate::prove::image::PageTableInfo;

    fn page_table_size(max_mem: usize, page_size: usize) -> usize {
        PageTableInfo::new(max_mem, page_size).total
    }

    #[test]
    fn check_integrity() {
        const PAGE_SIZE: usize = 1024;
        let image = MemoryImage::new(MULTI_TEST_ELF, PAGE_SIZE).unwrap();
        // std::fs::write("/tmp/test.img", &image.image).unwrap();
        image.check(0).unwrap();
        image.check(PROG.start() / PAGE_SIZE).unwrap();
        image.check((PROG.start() + 5000) / PAGE_SIZE).unwrap();
    }

    #[test]
    fn page_table_info() {
        const PAGE_SIZE_1K: usize = 1024;
        let info = PageTableInfo::new(PAGE_TABLE.start(), PAGE_SIZE_1K);
        assert_eq!(info.total, 7035584);
        assert_eq!(info.total / PAGE_SIZE_1K, 6870);
        assert_eq!(info.total / PAGE_SIZE_1K * PAGE_SIZE_1K, 7034880);
    }

    #[test]
    fn page_size_1k() {
        const PAGE_SIZE_1K: usize = 1024;
        assert_eq!(page_table_size(PAGE_SIZE_1K, PAGE_SIZE_1K), DIGEST_BYTES);
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
        let info = PageTableInfo::new(256 * 1024 * 1024, PAGE_SIZE_1K);
        assert_eq!(
            info.layers,
            vec![8 * 1024 * 1024, 256 * 1024, 8 * 1024, 256]
        );
        assert_eq!(info.total, 8 * 1024 * 1024 + 256 * 1024 + 8 * 1024 + 256);
    }

    #[test]
    fn page_size_4k() {
        const PAGE_SIZE_4K: usize = 4 * 1024;
        assert_eq!(page_table_size(PAGE_SIZE_4K, PAGE_SIZE_4K), DIGEST_BYTES);
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
        let info = PageTableInfo::new(256 * 1024 * 1024, PAGE_SIZE_4K);
        assert_eq!(info.layers, vec![2 * 1024 * 1024, 16 * 1024, 128]);
        assert_eq!(info.total, 2 * 1024 * 1024 + 16 * 1024 + 128);
    }
}
