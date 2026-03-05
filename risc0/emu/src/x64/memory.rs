// Copyright 2025 RISC Zero, Inc.
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

use std::collections::HashMap;
use std::mem::offset_of;
use std::ptr;
use std::sync::Arc;

use risc0_binfmt::Page;

use crate::rv32im::WORD_SIZE;

use super::page::{PAGE_OFFSET_MASK, PAGE_SHIFT, PAGE_SIZE, PAGE_WRITABLE_FLAG};

pub const NUM_PAGES: usize = 1 << (32 - PAGE_SHIFT);
pub const PAGE_SLOT_PTR_OFFSET: i32 = offset_of!(PageSlot, ptr) as i32;
pub const PAGE_SLOT_TAG_OFFSET: i32 = offset_of!(PageSlot, tag) as i32;
pub const PAGE_SLOT_SIZE: usize = std::mem::size_of::<PageSlot>();
pub const PAGE_SLOT_SHIFT: usize = PAGE_SLOT_SIZE.ilog2() as usize;
pub const PAGE_SLOT_TAG_SHIFT: u32 = (PAGE_SIZE / PAGE_SLOT_SIZE).ilog2();
pub const PAGE_IDX_SHIFT: u32 = PAGE_SHIFT as u32 - PAGE_SLOT_TAG_SHIFT;

#[repr(C)]
#[derive(Clone, Copy, Debug, Default)]
pub struct PageSlot {
    ptr: *const u8,
    tag: u16,
}

impl PageSlot {
    #[inline]
    pub fn ptr(&self) -> *const u8 {
        self.ptr
    }

    #[inline]
    pub fn tag(&self) -> u16 {
        self.tag
    }

    #[inline]
    pub fn set(&mut self, ptr: *const u8, tag: u16) {
        self.ptr = ptr;
        self.tag = tag;
    }

    #[inline]
    pub fn update_tag(&mut self, tag: u16) {
        self.tag = tag;
    }

    #[inline]
    pub fn is_empty(&self) -> bool {
        self.ptr().is_null()
    }
}

pub type PageBytes = [u8; PAGE_SIZE];

/// Canonical owner of all pages.
/// The page *slots* table is fixed-size; the pages map is sparse.
pub struct HostMemory {
    pub slots: Vec<PageSlot>,      // len = NUM_PAGES
    pub pages: HashMap<u32, Page>, // only allocated pages
}

impl HostMemory {
    pub fn new() -> Self {
        HostMemory {
            slots: vec![PageSlot::default(); NUM_PAGES],
            pages: HashMap::new(),
        }
    }

    /// Returns raw pointer for writing.
    ///
    /// Also:
    /// - updates the PageSlot pointer + generation for fast-path JIT use.
    pub fn ensure_page_write_for_segment(
        &mut self,
        current_tag: u16,
        page_idx: u32,
    ) -> &mut PageBytes {
        // Ensure a current version exists.
        let page = self.pages.entry(page_idx).or_default();
        let slot = &mut self.slots[page_idx as usize];

        let page_mut = self.pages.get_mut(&page_idx).unwrap();

        let page_data = page_mut.ensure_writable();

        // Update slot pointer + generation for JIT fast path.
        slot.set(page_data.as_ptr(), current_tag | PAGE_WRITABLE_FLAG);

        page_data
    }

    /// Ensure page exists for read
    pub fn ensure_page_read_for_segment(&mut self, current_tag: u16, page_idx: u32) -> &PageBytes {
        let page = self.pages.entry(page_idx).or_default();
        let slot = &mut self.slots[page_idx as usize];

        slot.set(page.data().as_ptr(), current_tag);

        page.data()
    }

    pub fn load_u32_untracked(&mut self, addr: u32) -> u32 {
        let page_idx = addr >> PAGE_SHIFT;
        let offset = (addr & PAGE_OFFSET_MASK) as usize;
        debug_assert!(offset + WORD_SIZE <= PAGE_SIZE);

        let page = self.pages.entry(page_idx).or_default();
        unsafe {
            let ptr = page.data().as_ptr().add(offset) as *const u32;
            u32::from_le(ptr.read_unaligned())
        }
    }

    pub fn store_u32_untracked(&mut self, addr: u32, word: u32) {
        let page_idx = addr >> PAGE_SHIFT;
        let offset = (addr & PAGE_OFFSET_MASK) as usize;
        debug_assert!(offset + WORD_SIZE <= PAGE_SIZE);

        let page = self.pages.entry(page_idx).or_default();

        let page_data = page.ensure_writable();
        unsafe {
            let ptr = page_data.as_mut_ptr().add(offset) as *mut u32;
            ptr.write_unaligned(word);
        }
    }
}
