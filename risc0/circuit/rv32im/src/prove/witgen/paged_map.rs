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

use risc0_binfmt::WordAddr;

const ENTRY_COUNT: usize = 1 << 11;
const PAGED_MAP_MASK: u32 = (1 << 10) - 1;

struct PagedMapEntry {
    words: Vec<Option<u32>>,
}

impl Default for PagedMapEntry {
    fn default() -> Self {
        Self {
            words: vec![None; ENTRY_COUNT],
        }
    }
}

struct PagedMapTable {
    entries: Vec<u32>,
}

impl Default for PagedMapTable {
    fn default() -> Self {
        Self {
            entries: vec![0; ENTRY_COUNT],
        }
    }
}

/// An associative map of [WordAddr] => `u32`, optimized for the rv32im preflight workload.
pub(crate) struct PagedMap {
    high: PagedMapTable,
    mid: Vec<PagedMapTable>,
    low: Vec<PagedMapEntry>,
}

impl Default for PagedMap {
    fn default() -> Self {
        Self {
            high: PagedMapTable::default(),
            mid: vec![PagedMapTable {
                entries: Vec::new(),
            }],
            low: vec![PagedMapEntry { words: Vec::new() }],
        }
    }
}

impl PagedMap {
    /// Returns the value corresponding to the key.
    #[inline(always)]
    pub fn get(&mut self, addr: &WordAddr) -> Option<u32> {
        let idx = addr.0 >> 20;
        let mid = self.high.entries.get(idx as usize).unwrap();
        if *mid != 0 {
            let mid_table = self.mid.get(*mid as usize).unwrap();
            let idx = (addr.0 >> 10) & PAGED_MAP_MASK;
            let low = mid_table.entries.get(idx as usize).unwrap();
            if *low != 0 {
                let low_table = self.low.get(*low as usize).unwrap();
                let idx = addr.0 & PAGED_MAP_MASK;
                return *low_table.words.get(idx as usize).unwrap();
            }
        }
        None
    }

    /// Returns a mutable reference to the value corresponding to the key.
    #[inline(always)]
    pub fn get_mut(&mut self, addr: &WordAddr) -> &mut Option<u32> {
        let high_idx = addr.0 >> 20;
        let mid_idx = (addr.0 >> 10) & PAGED_MAP_MASK;
        let low_idx = addr.0 & PAGED_MAP_MASK;
        // tracing::debug!("insert: {addr:?}, {high_idx:#010x}, {mid_idx:#010x}, {low_idx:#010x}");
        let mid = self.high.entries.get_mut(high_idx as usize).unwrap();
        if *mid == 0 {
            *mid = self.mid.len() as u32;
            self.mid.push(PagedMapTable::default());
        }
        let mid_table = self.mid.get_mut(*mid as usize).unwrap();
        let low = mid_table.entries.get_mut(mid_idx as usize).unwrap();
        if *low == 0 {
            *low = self.low.len() as u32;
            self.low.push(PagedMapEntry::default());
        }
        let low_table = self.low.get_mut(*low as usize).unwrap();
        low_table.words.get_mut(low_idx as usize).unwrap()
    }

    /// Inserts a key-value pair into the map.
    ///
    /// If the map did not have this key present, None is returned.
    ///
    /// If the map did have this key present, the value is updated, and the old value is returned.
    pub fn insert(&mut self, addr: &WordAddr, word: u32) -> Option<u32> {
        self.get_mut(addr).replace(word)
    }

    pub fn insert_default(&mut self, addr: &WordAddr, word: u32, default: u32) -> u32 {
        self.insert(addr, word).unwrap_or(default)
    }
}
