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

use std::sync::{Arc, OnceLock};

use risc0_zkp::core::digest::Digest;

pub const PAGE_SHIFT: usize = 10; // 1 KiB pages
pub const PAGE_SIZE: usize = 1 << PAGE_SHIFT;
pub const PAGE_OFFSET_MASK: u32 = (1 << PAGE_SHIFT) - 1;

pub type PageBytes = [u8; PAGE_SIZE];

/// One immutable page version: bytes + memoized digest.
pub struct PageVersion {
    pub bytes: PageBytes,
    pub digest: OnceLock<Digest>,
}

pub type PageRef = Arc<PageVersion>;

impl PageVersion {
    pub fn new_zeroed() -> PageRef {
        Arc::new(PageVersion {
            bytes: [0u8; PAGE_SIZE],
            digest: OnceLock::new(),
        })
    }

    pub fn new(bytes: &PageBytes) -> PageRef {
        Arc::new(PageVersion {
            bytes: *bytes,
            digest: OnceLock::new(),
        })
    }
}

impl PageVersion {
    /// Compute or fetch the cached hash for a page version.
    /// The hashing function is left as a TODO.
    pub fn digest(&self) -> &Digest {
        self.digest.get_or_init(|| {
            // // TODO: replace with actual Poseidon2 over v.bytes
            // // For now, just a dummy hash.
            // let mut h = [0u32; 8];
            // for (i, chunk) in v.bytes.chunks(4).take(8).enumerate() {
            //     let mut word = 0u32;
            //     for (j, b) in chunk.iter().enumerate() {
            //         word |= (*b as u32) << (j * 8);
            //     }
            //     h[i] = word;
            // }
            // h
            Digest::ZERO
        })
    }
}
