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

use std::marker::PhantomData;
use std::mem::size_of;

use bytemuck::Pod;
use enum_map::EnumMap;

use risc0_circuit_rv32im_sys::{
    BlockType, BlockWitness, FpDigest, GlobalsWitness, HasBlockType, RowInfo, visit_blocks,
};

#[derive(Default)]
struct BlockCursor {
    row: usize,
    begin: usize,
    end: usize,
}

#[derive(Copy, Clone)]
pub struct TraceIndex<WitnessT> {
    aux_idx: usize,
    _witness: PhantomData<WitnessT>,
}

impl<WitnessT> TraceIndex<WitnessT> {
    pub fn cast<OtherWitnessT>(self) -> TraceIndex<OtherWitnessT> {
        TraceIndex {
            aux_idx: self.aux_idx,
            _witness: PhantomData,
        }
    }
}

pub struct Trace<'a> {
    rows: &'a mut [RowInfo],
    row_next: usize,
    aux: &'a mut [u32],
    aux_next: usize,

    globals: TraceIndex<GlobalsWitness>,
    user_cycles: u32,

    cursors: EnumMap<BlockType, BlockCursor>,
}

impl<'a> Trace<'a> {
    pub fn new(rows: &'a mut [RowInfo], aux: &'a mut [u32]) -> Self {
        let mut s_ = Self {
            rows,
            row_next: 0,
            aux,
            aux_next: 0,

            globals: TraceIndex {
                aux_idx: 0,
                _witness: PhantomData,
            },
            user_cycles: 0,
            cursors: EnumMap::default(),
        };
        let idx = s_.add_block(GlobalsWitness {
            rootIn: FpDigest::default(),
            rootOut: FpDigest::default(),
            p2Count: 0,
            finalCycle: 0,
            v2Compat: 0,
            povwNonce: [0u32; 8],
        });
        s_.globals = idx;
        s_
    }

    pub fn globals(&self) -> &GlobalsWitness {
        self.get_block(self.globals)
    }

    pub fn globals_mut(&mut self) -> &mut GlobalsWitness {
        self.get_block_mut(self.globals)
    }

    pub fn get_row_count(&self) -> usize {
        self.row_next
    }

    pub fn get_aux_size(&self) -> usize {
        self.aux_next
    }

    pub fn add_block<WitnessT: HasBlockType + Pod>(
        &mut self,
        wit: WitnessT,
    ) -> TraceIndex<WitnessT> {
        let wit_size = size_of::<WitnessT>();
        assert!(wit_size.is_multiple_of(size_of::<u32>()));

        let block_type = WitnessT::BLOCK_TYPE;
        let cursor = &mut self.cursors[block_type];

        if cursor.begin == cursor.end {
            cursor.begin = self.aux_next;
            cursor.end =
                self.aux_next + block_type.count_per_row() as usize * wit_size / size_of::<u32>();
            cursor.row = self.row_next;
            self.row_next += 1;
            self.rows[cursor.row].row_type = block_type as u8;
            self.rows[cursor.row].block_count = 0;
            self.rows[cursor.row].aux_offset = self.aux_next as u32;
            self.aux_next = cursor.end;
        }
        self.rows[cursor.row].block_count += 1;

        let end = cursor.begin + wit_size / size_of::<u32>();
        let dest_slice: &mut [WitnessT] =
            bytemuck::cast_slice_mut(&mut self.aux[cursor.begin..end]);
        dest_slice[0] = wit;

        let idx = TraceIndex {
            aux_idx: cursor.begin,
            _witness: PhantomData,
        };

        cursor.begin = end;

        idx
    }

    pub fn get_block<WitnessT: Pod>(&self, index: TraceIndex<WitnessT>) -> &WitnessT {
        let wit_size = size_of::<WitnessT>();
        assert!(wit_size.is_multiple_of(size_of::<u32>()));

        let idx = index.aux_idx;
        let end = idx + wit_size / size_of::<u32>();
        let slice: &[WitnessT] = bytemuck::cast_slice(&self.aux[idx..end]);
        &slice[0]
    }

    pub fn get_block_mut<WitnessT: HasBlockType + Pod>(
        &mut self,
        index: TraceIndex<WitnessT>,
    ) -> &mut WitnessT {
        let wit_size = size_of::<WitnessT>();
        assert!(wit_size.is_multiple_of(size_of::<u32>()));

        let idx = index.aux_idx;
        let end = idx + wit_size / size_of::<u32>();
        let slice: &mut [WitnessT] = bytemuck::cast_slice_mut(&mut self.aux[idx..end]);
        &mut slice[0]
    }

    pub fn finalize(&mut self) {
        while self.row_next < self.rows.len() {
            self.rows[self.row_next].row_type = BlockType::Empty as u8;
            self.rows[self.row_next].block_count = 0;
            self.rows[self.row_next].aux_offset = 0;
            self.row_next += 1;
        }
        self.rows.sort_by_key(|r| r.row_type);
    }

    pub fn rows(&self) -> &[RowInfo] {
        self.rows
    }

    pub fn aux(&self) -> &[u32] {
        self.aux
    }

    pub fn set_user_cycles(&mut self, cycles: u32) {
        self.user_cycles = cycles;
    }

    pub fn user_cycles(&self) -> u32 {
        self.user_cycles
    }
}

fn decode_witness<WitnessT: Pod>(aux: &[u32], offset: usize, i: usize) -> BlockWitness
where
    BlockWitness: From<WitnessT>,
{
    let wit_size = size_of::<WitnessT>() / size_of::<u32>();
    let start = offset + i * wit_size;
    let wit: &[WitnessT] = bytemuck::cast_slice(&aux[start..(start + wit_size)]);
    wit[0].into()
}

pub fn decode_trace(rows: &[RowInfo], aux: &[u32]) -> Vec<BlockWitness> {
    let mut out = vec![];

    macro_rules! decode_witness {
            ($block_type:expr, $aux:expr, $offset:expr, $i: expr, $($block_name:ident),*) => {
                paste::paste! {
                    match $block_type {
                        $(BlockType::$block_name => {
                            decode_witness::<risc0_circuit_rv32im_sys::[<$block_name Witness>]>(
                                $aux, $offset, $i
                            )
                        }),*
                    }
                }
            }
        }

    for row in rows.iter() {
        let block_type = BlockType::try_from(row.row_type).unwrap();
        let offset = row.aux_offset as usize;

        for i in 0..row.block_count {
            let i = i as usize;
            out.push(visit_blocks!(decode_witness, block_type, aux, offset, i));
        }
    }

    out
}

#[cfg(test)]
pub mod tests {
    use super::*;

    use bytemuck::Zeroable as _;

    use risc0_circuit_rv32im_sys::{MakeTableWitness, PageInPageWitness};

    fn test_trace(num_rows: usize, aux_bytes: usize, wits: &[BlockWitness]) {
        let mut rows = vec![RowInfo::zeroed(); num_rows + 1];

        assert_eq!(BlockType::PageInPage.count_per_row(), 1);

        let mut aux = vec![0u32; aux_bytes / size_of::<u32>()];
        let mut trace = Trace::new(&mut rows, &mut aux);

        macro_rules! add_witness {
            ($w:expr, $trace:expr, $($block_name:ident),*) => {
                paste::paste! {
                    match $w {
                        $(BlockWitness::$block_name(w) => {
                            let idx = trace.add_block(w.clone());
                            assert_eq!(trace.get_block(idx), w);
                            assert_eq!(trace.get_block_mut(idx), w);
                        }),*
                    }
                }
            }
        }

        for w in wits {
            visit_blocks!(add_witness, w, trace);
        }
        trace.finalize();

        assert_eq!(trace.get_row_count(), num_rows + 1);
        assert_eq!(trace.get_aux_size(), aux_bytes / size_of::<u32>());

        let mut wits = wits.to_vec();
        wits.insert(
            0,
            GlobalsWitness {
                rootIn: FpDigest::default(),
                rootOut: FpDigest::default(),
                p2Count: 0,
                finalCycle: 0,
                v2Compat: 0,
                povwNonce: [0u32; 8],
            }
            .into(),
        );
        assert_eq!(decode_trace(&rows, &aux), wits);
    }

    #[test]
    fn three_rows_filled() {
        let aux_bytes = size_of::<MakeTableWitness>()
            * BlockType::MakeTable.count_per_row() as usize
            + size_of::<PageInPageWitness>() * 2
            + size_of::<GlobalsWitness>();

        let wits = vec![
            PageInPageWitness {
                addr: 0xFFF1,
                node: Default::default(),
            }
            .into(),
            PageInPageWitness {
                addr: 0xFFF2,
                node: Default::default(),
            }
            .into(),
            MakeTableWitness {
                table: 12,
                start: 30,
            }
            .into(),
            MakeTableWitness {
                table: 13,
                start: 30,
            }
            .into(),
        ];

        test_trace(3, aux_bytes, &wits);
    }

    #[test]
    fn four_rows_not_full() {
        let aux_bytes = size_of::<MakeTableWitness>()
            * BlockType::MakeTable.count_per_row() as usize
            + size_of::<PageInPageWitness>() * 2
            + size_of::<GlobalsWitness>();

        let wits = vec![
            PageInPageWitness {
                addr: 0xFFF1,
                node: Default::default(),
            }
            .into(),
            PageInPageWitness {
                addr: 0xFFF2,
                node: Default::default(),
            }
            .into(),
            MakeTableWitness {
                table: 12,
                start: 30,
            }
            .into(),
            MakeTableWitness {
                table: 13,
                start: 30,
            }
            .into(),
        ];

        test_trace(4, aux_bytes, &wits);
    }
}
