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

#![allow(dead_code)]

mod constants;
mod decode;
mod opt;
mod paging;
mod poseidon2;
mod trace;

use crate::execute::Segment;
use crate::prove::RowInfo;
use anyhow::Result;
use risc0_binfmt::MemoryImage;

pub struct PreflightContext2 {
    /// Did this preflight result in termination
    pub is_final: bool,
    /// How many cycles did this preflight do
    pub cycles: u32,
    pub row_info: Vec<RowInfo>,
    pub aux: Vec<u32>,
    pub po2: u32,
}

pub struct SegmentContext2 {
    pub image: MemoryImage,
    pub read_record: Vec<Vec<u8>>,
    pub write_record: Vec<u32>,
    pub end_cycle: u32,
}

impl SegmentContext2 {
    pub fn new(segment: &Segment) -> Result<Self> {
        Ok(Self {
            image: segment.partial_image.clone(),
            read_record: segment.read_record.clone(),
            write_record: segment.write_record.clone(),
            end_cycle: segment.insn_counter,
        })
    }

    pub fn preflight(&self, po2: usize) -> Result<PreflightContext2> {
        Ok(PreflightContext2 {
            is_final: true,
            cycles: 0,
            row_info: vec![],
            aux: vec![],
            po2: po2 as u32,
        })
    }
}
