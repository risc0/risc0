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
mod emu;
mod opt;
mod paging;
mod poseidon2;
pub mod trace;

use anyhow::{Result, anyhow, ensure};
use bytemuck::Zeroable as _;

use risc0_binfmt::MemoryImage;

use crate::execute::Segment;
use crate::prove::RowInfo;
use trace::Trace;

const fn compute_max_wit_per_row() -> usize {
    use risc0_circuit_rv32im_sys::*;

    let mut max = 0;

    macro_rules! max_wit_row_size {
        ($max:expr, $($block_name:ident),*) => {
            paste::paste! {
                $({
                    let v = (std::mem::size_of::<[<$block_name Witness>]>()
                     * BlockType::$block_name.count_per_row() as usize);
                    if v >= max {
                        max = v;
                    }
                })*
            }
        }
    }

    visit_blocks!(max_wit_row_size, max);

    max
}

const MAX_WIT_PER_ROW: usize = compute_max_wit_per_row();

struct ReplayHostIo<'a> {
    reads: &'a [Vec<u8>],
    writes: &'a [u32],
}

impl<'a> ReplayHostIo<'a> {
    fn new(reads: &'a [Vec<u8>], writes: &'a [u32]) -> Self {
        Self { reads, writes }
    }
}

impl<'a> emu::HostIo for ReplayHostIo<'a> {
    fn on_write(&mut self, _fd: u32, _data: &[u8]) -> Result<u32> {
        ensure!(!self.writes.is_empty(), "write missing from replay");

        let bytes = self.writes[0];
        self.writes = &self.writes[1..];

        tracing::trace!("onWrite: {bytes} bytes");

        Ok(bytes)
    }

    fn on_read(&mut self, _fd: u32, data: &mut [u8]) -> Result<u32> {
        ensure!(!self.reads.is_empty(), "read missing from replay");

        let record = &self.reads[0];

        ensure!(data.len() >= record.len(), "Read record too big");

        tracing::trace!("onRead: {} bytes", record.len());

        let ret = record
            .len()
            .try_into()
            .map_err(|_| anyhow!("read record too long"))?;

        let dst = &mut data[..record.len()];
        dst.copy_from_slice(&record[..]);

        self.reads = &self.reads[1..];

        Ok(ret)
    }
}

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
        let rows = 1usize << po2;
        let mut row_info = vec![RowInfo::zeroed(); rows];
        let mut aux = vec![0u32; rows * MAX_WIT_PER_ROW];
        let mut trace = Trace::new(&mut row_info, &mut aux);

        let io = ReplayHostIo::new(&self.read_record, &self.write_record);
        let is_final = emu::emulate(&mut trace, &self.image, io, rows, self.end_cycle)?;
        let cycles = trace.user_cycles();

        tracing::info!(
            "Finalizing, trace row count = {}, aux size = {}",
            trace.get_row_count(),
            trace.get_aux_size()
        );

        trace.finalize();

        let row_count = trace.get_row_count();
        let aux_size = trace.get_aux_size();

        row_info.truncate(row_count);
        aux.truncate(aux_size);

        Ok(PreflightContext2 {
            is_final,
            cycles,
            row_info,
            aux,
            po2: po2 as u32,
        })
    }
}
