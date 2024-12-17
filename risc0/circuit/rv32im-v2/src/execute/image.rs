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

use std::{collections::BTreeMap, sync::LazyLock};

use anyhow::{anyhow, bail, Result};
use derive_more::Debug;
use risc0_binfmt::Program;
use risc0_zkp::{
    core::{
        digest::{Digest, DIGEST_WORDS},
        hash::poseidon2::{poseidon2_mix, CELLS},
    },
    field::Elem as _,
};
use serde::{Deserialize, Serialize};

use crate::zirgen::circuit::Val;

use super::{
    addr::{ByteAddr, WordAddr},
    pager::PAGE_WORDS,
    platform::*,
};

static ZERO_CACHE: LazyLock<ZeroCache> = LazyLock::new(ZeroCache::new);

struct ZeroCache {
    pub page: Page,
    pub digests: Vec<Digest>,
}

impl ZeroCache {
    fn new() -> Self {
        let page = Page::default();
        let mut digest = page.digest();
        let mut digests = vec![Digest::ZERO; MERKLE_TREE_DEPTH + 1];
        for depth in (0..MERKLE_TREE_DEPTH + 1).rev() {
            digests[depth] = digest;
            digest = DigestPair {
                lhs: digest,
                rhs: digest,
            }
            .digest();
        }
        Self { page, digests }
    }
}

#[derive(Clone, Serialize, Deserialize)]
pub struct Page(Vec<u8>);

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct MemoryImage2 {
    #[debug("{}", pages.len())]
    // #[debug("{:#010x?}", pages.keys())]
    pub pages: BTreeMap<u32, Page>,
    #[debug("{}", digests.len())]
    // #[debug("{:#010x?}", digests.keys())]
    pub digests: BTreeMap<u32, Digest>,
}

impl Default for MemoryImage2 {
    fn default() -> Self {
        Self {
            pages: Default::default(),
            digests: BTreeMap::from([(1, ZERO_CACHE.digests[0])]),
        }
    }
}

impl MemoryImage2 {
    pub fn new(program: Program) -> Self {
        let mut this = Self::default();
        let mut cur_page_idx = 0xffffffff_u32;
        let mut cur_page: Option<Page> = None;

        let mut image = program.image;
        image.insert(SUSPEND_PC_ADDR.0, program.entry);
        image.insert(SUSPEND_MODE_ADDR.0, 1);

        for (&addr, &word) in image.iter() {
            let addr = ByteAddr(addr).waddr();
            let page_idx = addr.page_idx();
            if page_idx != cur_page_idx {
                if let Some(page) = cur_page.take() {
                    this.set_page(cur_page_idx, page);
                }
                cur_page = Some(Page::default());
                cur_page_idx = page_idx;
            }

            cur_page.as_mut().unwrap().store(addr, word);
        }

        if let Some(page) = cur_page.take() {
            this.set_page(cur_page_idx, page);
        }

        this
    }

    pub fn with_kernel(mut user: Program, mut kernel: Program) -> Self {
        kernel.image.append(&mut user.image);
        kernel
            .image
            .insert(MEPC_ADDR.0, user.entry - WORD_SIZE as u32);
        // .insert(MEPC_ADDR.waddr().0, user.entry - WORD_SIZE as u32);
        Self::new(kernel)
    }

    /// Return the page data, fails if unavailable
    pub fn get_page(&mut self, page_idx: u32) -> Result<Page> {
        // If page exists, return it
        if let Some(page) = self.pages.get(&page_idx) {
            return Ok(page.clone());
        }

        // Otherwise try an expand
        let digest_idx = MEMORY_PAGES as u32 + page_idx;
        if self.expand_if_zero(digest_idx) {
            let zero_page = &ZERO_CACHE.page;
            self.pages.insert(page_idx, zero_page.clone());
            return Ok(zero_page.clone());
        }

        // Otherwise fail
        bail!("Unavailable page: {page_idx}")
    }

    /// Set the data for a page
    pub fn set_page(&mut self, page_idx: u32, page: Page) {
        // tracing::trace!("set_page({page_idx:#08x})");
        let digest_idx = MEMORY_PAGES as u32 + page_idx;
        self.expand_if_zero(digest_idx);
        self.digests.insert(digest_idx, page.digest());
        self.pages.insert(page_idx, page);
        self.fixup_digests(digest_idx);
    }

    /// Get a digest, fails if unavailable
    pub fn get_digest(&mut self, digest_idx: u32) -> Result<&Digest> {
        // Expand if needed
        self.expand_if_zero(digest_idx);
        self.digests
            .get(&digest_idx)
            .ok_or(anyhow!("Unavailable digest: {digest_idx}"))
    }

    /// Set a digest
    pub fn set_digest(&mut self, digest_idx: u32, digest: Digest) {
        // If digest is in a zero region, reify for proper uncles
        self.expand_if_zero(digest_idx);
        // Set the digest value
        self.digests.insert(digest_idx, digest);
        // Fixup digest values
        self.fixup_digests(digest_idx);
    }

    /// Return the root digest
    pub fn image_id(&mut self) -> &Digest {
        self.get_digest(1).unwrap()
    }

    /// Expand if digest at `digest_idx` is a zero, return if expanded
    fn expand_if_zero(&mut self, digest_idx: u32) -> bool {
        let ret = self.is_zero(digest_idx);
        if ret {
            self.expand_zero(digest_idx);
        }
        ret
    }

    /// Check if given MT node is a zero
    fn is_zero(&self, mut digest_idx: u32) -> bool {
        // Compute the depth in the tree of this node
        let mut depth = digest_idx.ilog2() as usize;
        // Go up until we hit a valid node or get past the root
        while !self.digests.contains_key(&digest_idx) && digest_idx > 0 {
            digest_idx /= 2;
            depth -= 1;
        }
        if digest_idx == 0 {
            false
        } else {
            self.digests[&digest_idx] == ZERO_CACHE.digests[depth]
        }
    }

    /// Expand zero MT node.
    ///
    /// Presumes `is_zero(digest_idx)` returned true.
    fn expand_zero(&mut self, mut digest_idx: u32) {
        // Compute the depth in the tree of this node
        let mut depth = digest_idx.ilog2() as usize;
        // Go up until we hit the valid zero node
        while !self.digests.contains_key(&digest_idx) {
            let parent_idx = digest_idx / 2;
            let lhs_idx = parent_idx * 2;
            let rhs_idx = parent_idx * 2 + 1;
            self.digests.insert(lhs_idx, ZERO_CACHE.digests[depth]);
            self.digests.insert(rhs_idx, ZERO_CACHE.digests[depth]);
            digest_idx = parent_idx;
            depth -= 1;
        }
    }

    /// Fixup digests after a change
    fn fixup_digests(&mut self, mut digest_idx: u32) {
        while digest_idx != 1 {
            let parent_idx = digest_idx / 2;
            let lhs_idx = parent_idx * 2;
            let rhs_idx = parent_idx * 2 + 1;
            let lhs = self.digests.get(&lhs_idx);
            let rhs = self.digests.get(&rhs_idx);
            if let (Some(&lhs), Some(&rhs)) = (lhs, rhs) {
                let parent_digest = DigestPair { lhs, rhs }.digest();
                self.digests.insert(parent_idx, parent_digest);
                digest_idx = parent_idx;
            } else {
                break;
            };
        }
    }
}

impl Default for Page {
    fn default() -> Self {
        Self(vec![0; PAGE_BYTES])
    }
}

impl Page {
    pub fn digest(&self) -> Digest {
        let mut cells = [Val::ZERO; CELLS];
        for i in 0..PAGE_WORDS / DIGEST_WORDS {
            for j in 0..DIGEST_WORDS {
                let addr = WordAddr((i * DIGEST_WORDS + j) as u32);
                let word = self.load(addr);
                cells[2 * j] = Val::new(word & 0xffff);
                cells[2 * j + 1] = Val::new(word >> 16);
            }
            poseidon2_mix(&mut cells);
        }
        cells_to_digest(&cells)
    }

    pub fn load(&self, addr: WordAddr) -> u32 {
        let byte_addr = addr.page_subaddr().baddr().0 as usize;
        let mut bytes = [0u8; WORD_SIZE];
        bytes.clone_from_slice(&self.0[byte_addr..byte_addr + WORD_SIZE]);
        #[allow(clippy::let_and_return)] // easier to toggle optional tracing
        let word = u32::from_le_bytes(bytes);
        // tracing::trace!("load({addr:?}) -> {word:#010x}");
        word
    }

    pub fn store(&mut self, addr: WordAddr, word: u32) {
        let byte_addr = addr.page_subaddr().baddr().0 as usize;
        // tracing::trace!("store({addr:?}, {byte_addr:#05x}, {word:#010x})");
        self.0[byte_addr..byte_addr + WORD_SIZE].clone_from_slice(&word.to_le_bytes());
    }
}

struct DigestPair {
    lhs: Digest,
    rhs: Digest,
}

impl DigestPair {
    pub fn digest(&self) -> Digest {
        let mut cells = [Val::ZERO; CELLS];
        for i in 0..DIGEST_WORDS {
            cells[i] = Val::new(self.rhs.as_words()[i]);
            cells[DIGEST_WORDS + i] = Val::new(self.lhs.as_words()[i]);
        }
        poseidon2_mix(&mut cells);
        cells_to_digest(&cells)
    }
}

fn cells_to_digest(cells: &[Val; CELLS]) -> Digest {
    Digest::new([
        cells[0].as_u32(),
        cells[1].as_u32(),
        cells[2].as_u32(),
        cells[3].as_u32(),
        cells[4].as_u32(),
        cells[5].as_u32(),
        cells[6].as_u32(),
        cells[7].as_u32(),
    ])
}

#[cfg(test)]
mod tests {
    use std::collections::BTreeMap;

    use risc0_binfmt::Program;
    use risc0_zkp::digest;
    use test_log::test;

    use super::{MemoryImage2, ZERO_CACHE};

    #[test]
    fn poseidon2_zeros() {
        let expected = [
            digest!("f85c5a32ccc45c22f9686b08d710d4597d7ce256cdcd63146426270d9432c644"),
            digest!("2ce7714c40af126c2e86f320b10de417eddd8f51d2b9133d3105c3541a154812"),
            digest!("889c443e0c55734c0212fe6c400f00423c421f2070b1340351e77826e4918274"),
            digest!("53ea92273a7dfb7622de685c49f4ce1bd69db1696cd6846e9f5de56c89098b01"),
            digest!("82db13229831cb2ad63df0476dc1f217c702503d46770c283b6ecc1520fff074"),
            digest!("45cba5321f90c34b780d5d1790f23612fb834b3d21dc1e53594826470719ba34"),
            digest!("132689262568ae5ac27a4b65018aef0b2e4345578a16453acd874973a61c6350"),
            digest!("9fc9626e87aa3614eb38b44d9d832712fb2ea32427c6fd49281ca225f1fefd0d"),
            digest!("70947164fe9a4353fa33fb024f09ea0df24be40d88b6025278a3472ac49e6715"),
            digest!("4b707f15d9941c0168d630618cdcc05ccae5d84ab9674a6666123a0039915173"),
            digest!("97fb1325724ddb74b1446b5bfa13f02c2ecb1b2b2a2f5b1334a04c5c76335d12"),
            digest!("adba743a459eb5357487a1238a0c4c238b8313458283900447e9b8540adfb042"),
            digest!("a16e68725fe981434dcca548e972214b2dd85e017c3a4e03909a0f4c31a08741"),
            digest!("fb94f356397279703f12c24da7aa371e192294347af15d46f10ab512708cdb68"),
            digest!("30a2fe1aa5c2ae0e10b91074e34b06742be91e450a9bc10f28ab082263c48750"),
            digest!("2347f636d9a0ea45bbe8bf519f39d3127f72b625e2e5495f26a6dd583eb2965d"),
            digest!("e43d140e71e366521152d932e846c73535674921576711023deaee06de3b091e"),
            digest!("35500a740d3a8b4e5a0ca06a8362f3444456e3206826102dd9e9bc3e5a1a5a18"),
            digest!("7c650c1a2000ef1a9baf4f56c2d66e76a3a0b4510175b171268d156a25d8dd45"),
            digest!("d73a1e0997a00543afd8de5261f316704215ce384e3ea13df3f87e000f04fb5f"),
            digest!("5b77f60275cb272fa0a3d267bdf1fc15021dbe7185ed6a3c94e45d70bbd70148"),
            digest!("e053c93b359c8905c5d8523139988b0ed4ef3426864a80498dfcb91d9b813364"),
            digest!("242ce034cc4e9326f8b7071124454b2be1a1cd5d21b6483c7ff81d4ba5ac9566"),
        ];
        assert_eq!(ZERO_CACHE.digests, expected);
    }

    #[test]
    fn image_circuit_match() {
        let entry = 0x10000;
        let program = Program {
            entry,
            image: BTreeMap::from([(entry, 0x1234b337)]),
        };
        let mut image = MemoryImage2::new(program);
        assert_eq!(
            *image.get_digest(0x0040_0100).unwrap(),
            digest!("242ce034cc4e9326f8b7071124454b2be1a1cd5d21b6483c7ff81d4ba5ac9566")
        );
        assert_eq!(
            *image.image_id(),
            digest!("9d41290fa400705127c0240cb646586cc6ea8a23d560aa57cfa86c1369d9d53f")
        );
    }
}
