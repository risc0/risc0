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

use super::page::PageRef;

/// One page’s contribution to a segment:
/// - pre: bytes at segment start
/// - post: bytes at segment end
#[derive(Clone)]
pub struct SegmentPage {
    pub page_idx: u32,
    pub pre: PageRef,
    pub post: PageRef,
    pub wrote: bool,
}

/// Full record for a segment, sent to the background hasher.
pub struct SegmentRecord {
    pub segment_id: u64,
    pub pages: Vec<SegmentPage>,
}

/// Live tracker for the *current* segment on the main thread.
pub struct SegmentTracker {
    pub id: u64,
    pub pages: Vec<SegmentPage>,
    pub page_index_map: HashMap<u32, usize>,
}

impl SegmentTracker {
    pub fn new() -> Self {
        SegmentTracker {
            id: 0,
            pages: Vec::new(),
            page_index_map: HashMap::new(),
        }
    }

    pub fn begin_next_segment(&mut self) {
        self.id = self.id.wrapping_add(1);
        self.pages.clear();
        self.page_index_map.clear();
    }

    pub fn snapshot(&mut self) -> SegmentRecord {
        SegmentRecord {
            segment_id: self.id,
            pages: std::mem::take(&mut self.pages),
        }
    }
}
