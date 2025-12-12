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

use crate::rv32im::WORD_SIZE;

use super::page::{PAGE_OFFSET_MASK, PAGE_SHIFT, PAGE_SIZE, PageBytes, PageRef, PageVersion};
use super::segment::{SegmentPage, SegmentTracker};

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

/// Canonical owner of all page versions.
/// The page *slots* table is fixed-size; the versions map is sparse.
pub struct HostMemory {
    pub slots: Vec<PageSlot>,            // len = NUM_PAGES
    pub versions: HashMap<u32, PageRef>, // only allocated pages
}

impl HostMemory {
    pub fn new() -> Self {
        HostMemory {
            slots: vec![PageSlot::default(); NUM_PAGES],
            versions: HashMap::new(),
        }
    }

    /// Ensure there is a version for `page_idx` and return a clone of it.
    fn ensure_page_ref(&mut self, page_idx: u32) -> PageRef {
        self.versions
            .entry(page_idx)
            .or_insert_with(PageVersion::new_zeroed)
            .clone()
    }

    /// Returns raw pointer for writing.
    ///
    /// - pre: the version that was visible at segment start.
    /// - post: the version to be used *after* this write (may be new).
    ///
    /// Also:
    /// - updates the `SegmentTracker` with (page_idx, pre, post),
    /// - updates the PageSlot pointer + generation for fast-path JIT use.
    pub fn ensure_page_write_for_segment(
        &mut self,
        tracker: &mut SegmentTracker,
        current_tag: u16,
        page_idx: u32,
    ) -> PageRef {
        // Ensure a current version exists.
        let page = self.ensure_page_ref(page_idx);
        let slot = &mut self.slots[page_idx as usize];

        // Find or create SegmentPage record.
        let entry_idx = if let Some(&i) = tracker.page_index_map.get(&page_idx) {
            i
        } else {
            let idx = tracker.pages.len();
            tracker.pages.push(SegmentPage {
                page_idx,
                pre: page.clone(),
                post: page.clone(),
                wrote: false,
            });
            tracker.page_index_map.insert(page_idx, idx);
            idx
        };

        let seg_page = &mut tracker.pages[entry_idx];
        let post = seg_page.copy_on_write();

        // Update canonical version map and segment record.
        self.versions.insert(page_idx, post.clone());

        // Update slot pointer + generation for JIT fast path.
        slot.set(post.bytes.as_ptr(), current_tag);

        post
    }

    /// Ensure page exists for read, update generation and segment tracker
    /// if this is the first access in this segment.
    pub fn ensure_page_read_for_segment(
        &mut self,
        tracker: &mut SegmentTracker,
        current_tag: u16,
        page_idx: u32,
    ) -> PageRef {
        let page = self.ensure_page_ref(page_idx);
        let ptr = page.bytes.as_ptr();
        let slot = &mut self.slots[page_idx as usize];

        // First access this segment?
        if slot.tag() != current_tag || slot.ptr.is_null() {
            let idx = tracker.pages.len();
            tracker.pages.push(SegmentPage {
                page_idx,
                pre: page.clone(),
                post: page.clone(),
                wrote: false,
            });
            tracker.page_index_map.insert(page_idx, idx);
            slot.set(ptr, current_tag);
        } else {
            // Already active this segment; just return current pointer.
            if slot.ptr().is_null() {
                // Shouldn't happen: tag matches but no ptr. Fix by re-pointing.
                slot.set(ptr, current_tag);
            }
        }

        page
    }

    pub fn load_u32_untracked(&mut self, addr: u32) -> u32 {
        let page_idx = addr >> PAGE_SHIFT;
        let offset = (addr & PAGE_OFFSET_MASK) as usize;
        debug_assert!(offset + WORD_SIZE <= PAGE_SIZE);

        let page = self.ensure_page_ref(page_idx);
        unsafe {
            let ptr = page.bytes.as_ptr().add(offset) as *const u32;
            u32::from_le(ptr.read_unaligned())
        }
    }

    pub fn store_u32_untracked(&mut self, addr: u32, word: u32) {
        let page_idx = addr >> PAGE_SHIFT;
        let offset = (addr & PAGE_OFFSET_MASK) as usize;
        debug_assert!(offset + WORD_SIZE <= PAGE_SIZE);

        let page = self
            .versions
            .entry(page_idx)
            .or_insert_with(PageVersion::new_zeroed);

        let page = Arc::get_mut(page).expect("store_u32 requires unique ownership");
        unsafe {
            let ptr = page.bytes.as_mut_ptr().add(offset) as *mut u32;
            ptr.write_unaligned(word);
        }
    }
}
