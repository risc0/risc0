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

use crate::{BufferRow, Buffers,CycleContext};
use anyhow::Result;
use rayon::iter::{IntoParallelIterator, ParallelIterator};
use risc0_core::field::{Elem, ExtElem, RootsOfUnity};
use risc0_zkp::adapter::MixState;
use risc0_zkp::hal::cpu::{CpuBuffer, SyncSlice};
use risc0_zkp::INV_RATE;


pub fn run_serial<Val: Elem>(
    buffers: Buffers<&CpuBuffer<Val>, &CpuBuffer<Val>, ()>,
    tot_cycles: usize,
    mut circuit_fn: impl for<'a> FnMut(
        Buffers<RowSlice<'a, Val>, GlobalsRow<'a, Val>, ()>,
        /*cycle=*/ usize,
    ) -> Result<()>,
) -> Result<()> {
    let buffers = buffers
        .map_rows(CpuBuffer::as_slice_sync)
        .map_globals(CpuBuffer::as_slice_sync);

    for cycle in 0..tot_cycles {
        let cycle_ctx = buffers
            .as_ref()
            .map_globals(GlobalsRow::new)
            .map_rows(|buf| RowSlice::new(buf, cycle, tot_cycles, /*back_factor=*/ 1));
        circuit_fn(cycle_ctx, cycle)?
    }

    Ok(())
}
