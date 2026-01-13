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

use std::rc::Rc;

use anyhow::Result;
use rayon::{iter::IntoParallelIterator, prelude::*};
use risc0_circuit_keccak_sys::{
    RawBuffer, RawExecBuffers, RawPreflightTrace, ScatterInfo, risc0_circuit_keccak_cpu_poly_fp,
    risc0_circuit_keccak_cpu_witgen,
};
use risc0_core::scope;
use risc0_sys::ffi_wrap;
use risc0_zkp::{
    INV_RATE,
    core::{hash::poseidon2::Poseidon2HashSuite, log2_ceil},
    field::{Elem as _, ExtElem as _, RootsOfUnity as _, map_pow},
    hal::{
        AccumPreflight, CircuitHal,
        cpu::{CpuBuffer, CpuHal},
    },
};

use crate::{
    prove::{GLOBAL_MIX, GLOBAL_OUT, KeccakProver, KeccakProverImpl},
    zirgen::{
        circuit::{CircuitField, ExtVal, REGISTER_GROUP_ACCUM, REGISTER_GROUP_DATA, Val},
        info::POLY_MIX_POWERS,
    },
};

use super::{
    CircuitWitnessGenerator, ForwardPreflightOrder, MetaBuffer, PreflightCycleOrder,
    PreflightTrace, StepMode,
};

#[derive(Default)]
pub struct CpuCircuitHal;

impl CircuitWitnessGenerator<CpuHal<CircuitField>> for CpuCircuitHal {
    type PreferredPreflightOrder = ForwardPreflightOrder;

    fn scatter_preflight(
        &self,
        into: &MetaBuffer<CpuHal<CircuitField>>,
        infos: &[ScatterInfo],
        data: &[u32],
    ) -> Result<()> {
        scope!("scatter");
        let mut into_slice = into.buf.as_slice_mut();
        for info in infos {
            let inner_count = 32 / info.bits;
            let mask: u32 = if info.bits == 32 {
                0xffffffff
            } else {
                (1 << info.bits) - 1
            };
            for i in 0..info.count as u32 {
                let from_idx = info.offset + (i / inner_count);
                let word = data[from_idx as usize];
                let j = i % inner_count;
                let val = (word >> (j * info.bits)) & mask;
                let col = info.col as u32 + i;
                let into_idx = col as usize * into.rows + info.row as usize;
                into_slice[into_idx] = val.into();
            }
        }
        Ok(())
    }

    fn generate_witness<O: PreflightCycleOrder>(
        &self,
        mode: StepMode,
        preflight: &PreflightTrace<O>,
        global: &MetaBuffer<CpuHal<CircuitField>>,
        data: &MetaBuffer<CpuHal<CircuitField>>,
    ) -> Result<()> {
        scope!("witgen");

        let cycles = preflight.cycle;
        assert_eq!(cycles, data.rows);
        tracing::debug!("witgen: {cycles}");

        let global_buf = global.buf.as_slice();
        let data_buf = data.buf.as_slice();
        let buffers = RawExecBuffers {
            global: RawBuffer {
                buf: global_buf.as_ptr(),
                rows: global.rows,
                cols: global.cols,
                checked_reads: global.checked_reads,
            },
            data: RawBuffer {
                buf: data_buf.as_ptr(),
                rows: data.rows,
                cols: data.cols,
                checked_reads: data.checked_reads,
            },
        };
        let run_order: Vec<u32> = preflight
            .cycles
            .values()
            .flatten()
            .map(|c| c.cycle)
            .collect();
        let preimage_idx: Vec<u32> = preflight
            .cycles
            .values()
            .flatten()
            .map(|c| c.preimage_idx)
            .collect();
        let preflight = RawPreflightTrace {
            preimages: preflight.preimages.as_ptr(),
            preimages_count: preflight.preimages.len() as u32,
            preimage_idxs: preimage_idx.as_ptr(),
            run_order: run_order.as_ptr(),
        };
        ffi_wrap(|| unsafe {
            risc0_circuit_keccak_cpu_witgen(mode as u32, &buffers, &preflight, cycles as u32)
        })
    }
}

impl CircuitHal<CpuHal<CircuitField>> for CpuCircuitHal {
    fn accumulate(
        &self,
        _preflight: &AccumPreflight,
        _ctrl: &CpuBuffer<Val>,
        _io: &CpuBuffer<Val>,
        _data: &CpuBuffer<Val>,
        _mix: &CpuBuffer<Val>,
        _accum: &CpuBuffer<Val>,
        _steps: usize,
    ) {
    }

    fn eval_check(
        &self,
        check: &CpuBuffer<Val>,
        groups: &[&CpuBuffer<Val>],
        globals: &[&CpuBuffer<Val>],
        poly_mix: ExtVal,
        po2: usize,
        steps: usize,
    ) {
        scope!("eval_check");

        let check = check.as_slice();
        let accum = groups[REGISTER_GROUP_ACCUM].as_slice();
        let data = groups[REGISTER_GROUP_DATA].as_slice();
        let mix = globals[GLOBAL_MIX].as_slice();
        let out = globals[GLOBAL_OUT].as_slice();

        tracing::debug!(
            "check: {}, data: {}, accum: {}, mix: {} out: {}",
            check.len(),
            data.len(),
            accum.len(),
            mix.len(),
            out.len()
        );

        const EXP_PO2: usize = log2_ceil(INV_RATE);
        let domain = steps * INV_RATE;
        let poly_mix_pows = map_pow(poly_mix, POLY_MIX_POWERS);

        // SAFETY: Convert a borrow of a cell into a raw const slice so that we can pass
        // it over the thread boundary. This should be safe because the scope of the
        // usage is within this function and each thread access will not overlap with
        // each other.

        let data = unsafe { std::slice::from_raw_parts(data.as_ptr(), data.len()) };
        let out = unsafe { std::slice::from_raw_parts(out.as_ptr(), out.len()) };
        let poly_mix_pows = poly_mix_pows.as_slice();

        (0..domain).into_par_iter().for_each(|cycle| {
            let args = &[data.as_ptr(), out.as_ptr()];
            let mut tot = ExtVal::ZERO;
            unsafe {
                risc0_circuit_keccak_cpu_poly_fp(
                    cycle,
                    domain,
                    poly_mix_pows.as_ptr(),
                    args.as_ptr(),
                    &mut tot,
                )
            };
            let x = Val::ROU_FWD[po2 + EXP_PO2].pow(cycle);
            // TODO: what is this magic number 3?
            let y = (Val::new(3) * x).pow(1 << po2);
            let ret = tot * (y - Val::new(1)).inv();

            // SAFETY: This conversion is to make the check slice mutable, which should be
            // safe because each thread access will not overlap with each other.
            let check =
                unsafe { std::slice::from_raw_parts_mut(check.as_ptr() as *mut Val, check.len()) };
            for i in 0..ExtVal::EXT_SIZE {
                check[i * domain + cycle] = ret.elems()[i];
            }
        });
    }
}

#[allow(dead_code)]
pub fn keccak_prover() -> Result<Box<dyn KeccakProver>> {
    let hash_suite = Poseidon2HashSuite::new_suite();
    let hal = Rc::new(CpuHal::new(hash_suite));
    let circuit_hal = Rc::new(CpuCircuitHal);
    Ok(Box::new(KeccakProverImpl { hal, circuit_hal }))
}
