// Copyright 2026 RISC Zero, Inc.
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

use std::ptr::NonNull;

use anyhow::Result;

use crate::execute::Segment;
use risc0_circuit_rv32im_sys::*;
use risc0_zkp::{core::digest::DIGEST_WORDS, field::baby_bear::Elem};

pub struct SegmentContext {
    ctx: NonNull<risc0_circuit_rv32im_sys::SegmentContext>,
}

/// Safety: A [PreflightContext] is an immutable object that can be safely
/// passed between threads.
#[derive(Default)]
pub struct PreflightContext {
    ctx: *const risc0_circuit_rv32im_sys::PreflightContext,
    po2: u32,
}

unsafe impl Send for PreflightContext {}

impl SegmentContext {
    pub fn new(segment: &Segment) -> Result<Self> {
        tracing::debug!("load_segment: {segment:#?}",);

        let mut pages: Vec<RawPage> = Vec::with_capacity(segment.partial_image.pages.len());
        for (&addr, page) in segment.partial_image.pages.iter() {
            let slice: &[u32] = bytemuck::cast_slice(page.data().as_slice());
            pages.push(RawPage {
                addr,
                data: slice.as_ptr(),
            });
        }

        // NOTE: If the memory image digests are not computed by this point, they will be here.
        let mut digests: Vec<RawDigestEntry> = Vec::new();
        let mut memory_image = segment.partial_image.clone();
        for (&idx, &digest) in memory_image.digests() {
            let mut words = [0; DIGEST_WORDS];
            for (i, word) in words.iter_mut().enumerate() {
                *word = Elem::new(digest.as_words()[i]).as_u32_montgomery();
            }
            digests.push(RawDigestEntry { idx, digest: words })
        }

        let image = RawMemoryImage {
            pages: RawSlice {
                ptr: pages.as_ptr(),
                len: pages.len(),
            },
            digests: RawSlice {
                ptr: digests.as_ptr(),
                len: digests.len(),
            },
        };

        let mut reads: Vec<RawSlice<u8>> = Vec::with_capacity(segment.read_record.len());
        for record in segment.read_record.iter() {
            reads.push(RawSlice {
                ptr: record.as_ptr(),
                len: record.len(),
            });
        }

        let raw_segment = RawSegment {
            image,
            reads: RawSlice {
                ptr: reads.as_ptr(),
                len: reads.len(),
            },
            writes: RawSlice {
                ptr: segment.write_record.as_ptr(),
                len: segment.write_record.len(),
            },
            insn_counter: segment.insn_counter,
            povw_nonce: segment.povw_nonce.map(|n| n.to_u32s()).unwrap_or_default(),
        };

        let ctx = ffi_wrap_ptr_mut(|| unsafe { risc0_circuit_rv32im_segment_new(&raw_segment) })?;

        Ok(Self { ctx })
    }

    pub fn preflight(&self, po2: usize) -> Result<PreflightContext> {
        tracing::debug!("preflight");
        let ctx = ffi_wrap_ptr(|| unsafe {
            risc0_circuit_rv32im_segment_preflight(self.ctx.as_ptr(), po2)
        })?;
        Ok(PreflightContext {
            ctx,
            po2: po2 as u32,
        })
    }
}

impl Drop for SegmentContext {
    fn drop(&mut self) {
        unsafe { risc0_circuit_rv32im_segment_free(self.ctx.as_ptr()) };
    }
}

impl PreflightContext {
    pub fn is_final(&self) -> bool {
        unsafe { risc0_circuit_rv32im_preflight_is_final(self.ctx) == 1 }
    }

    pub fn po2(&self) -> u32 {
        self.po2
    }

    pub fn row_info_ptr(&self) -> *const RowInfo {
        unsafe { risc0_circuit_rv32im_preflight_row_info(self.ctx) }
    }

    pub fn row_info_size(&self) -> usize {
        unsafe { risc0_circuit_rv32im_preflight_row_info_size(self.ctx) }
    }

    pub fn aux_ptr(&self) -> *const u32 {
        unsafe { risc0_circuit_rv32im_preflight_aux(self.ctx) }
    }

    pub fn aux_size(&self) -> usize {
        unsafe { risc0_circuit_rv32im_preflight_aux_size(self.ctx) }
    }

    pub fn block_counts(&self) -> enum_map::EnumMap<BlockType, u32> {
        let counts_ptr = unsafe { risc0_circuit_rv32im_preflight_block_counts(self.ctx) };
        let counts_slice = unsafe { std::slice::from_raw_parts(counts_ptr, BlockType::COUNT - 1) };

        let mut counts = enum_map::EnumMap::<BlockType, u32>::default();
        for (bt, &count) in counts_slice.iter().enumerate() {
            let block_type = BlockType::try_from(bt as u8).unwrap();
            counts[block_type] += count;
        }
        counts
    }
}

impl Drop for PreflightContext {
    fn drop(&mut self) {
        unsafe { risc0_circuit_rv32im_preflight_free(self.ctx) };
    }
}
