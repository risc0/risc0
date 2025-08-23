// Copyright 2025 RISC Zero, Inc.
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

use std::rc::Rc;

use anyhow::Result;
use rayon::prelude::*;
use risc0_circuit_rv32im_sys::{
    RawAccumBuffers, RawBuffer, RawExecBuffers, RawPreflightTrace, risc0_circuit_rv32im_cpu_accum,
    risc0_circuit_rv32im_cpu_poly_fp, risc0_circuit_rv32im_cpu_witgen,
};
use risc0_core::scope;
use risc0_sys::ffi_wrap;
use risc0_zkp::{
    INV_RATE,
    core::{hash::poseidon2::Poseidon2HashSuite, log2_ceil},
    field::{Elem, ExtElem as _, RootsOfUnity as _, map_pow},
    hal::{AccumPreflight, CircuitHal, cpu::CpuBuffer},
};

use super::{
    CircuitAccumulator, CircuitWitnessGenerator, MetaBuffer, SegmentProver, SegmentProverImpl,
    StepMode,
};
use crate::{
    prove::{GLOBAL_MIX, GLOBAL_OUT, witgen::preflight::PreflightTrace},
    zirgen::{
        circuit::{CircuitField, ExtVal, REGISTER_GROUP_ACCUM, REGISTER_GROUP_DATA, Val},
        info::POLY_MIX_POWERS,
    },
};

type CpuHal = risc0_zkp::hal::cpu::CpuHal<CircuitField>;

#[derive(Default)]
pub struct CpuCircuitHal;

impl CircuitWitnessGenerator<CpuHal> for CpuCircuitHal {
    fn generate_witness(
        &self,
        mode: StepMode,
        preflight: &PreflightTrace,
        global: &MetaBuffer<CpuHal>,
        data: &MetaBuffer<CpuHal>,
    ) -> Result<()> {
        scope!("cpu_witgen");
        let cycles = preflight.cycles.len();
        tracing::debug!("witgen: {cycles}");
        let global_buf = global.buf.as_slice();
        let data_buf = data.buf.as_slice();
        let buffers = RawExecBuffers {
            global: RawBuffer {
                buf: global_buf.as_ptr(),
                rows: global.rows,
                cols: global.cols,
                checked: global.checked,
            },
            data: RawBuffer {
                buf: data_buf.as_ptr(),
                rows: data.rows,
                cols: data.cols,
                checked: data.checked,
            },
        };
        let preflight = RawPreflightTrace {
            cycles: preflight.cycles.as_ptr(),
            txns: preflight.txns.as_ptr(),
            bigint_bytes: preflight.bigint_bytes.as_ptr(),
            txns_len: preflight.txns.len() as u32,
            bigint_bytes_len: preflight.bigint_bytes.len() as u32,
            table_split_cycle: preflight.table_split_cycle,
        };
        ffi_wrap(|| unsafe {
            risc0_circuit_rv32im_cpu_witgen(mode as u32, &buffers, &preflight, cycles as u32)
        })
    }
}

impl CircuitAccumulator<CpuHal> for CpuCircuitHal {
    fn step_accum(
        &self,
        preflight: &PreflightTrace,
        data: &MetaBuffer<CpuHal>,
        accum: &MetaBuffer<CpuHal>,
        global: &MetaBuffer<CpuHal>,
        mix: &MetaBuffer<CpuHal>,
    ) -> Result<()> {
        scope!("accumulate");
        let cycles = preflight.cycles.len();
        tracing::debug!("accumulate: {cycles}");
        let data_buf = data.buf.as_slice();
        let accum_buf = accum.buf.as_slice();
        let global_buf = global.buf.as_slice();
        let mix_buf = mix.buf.as_slice();
        let buffers = RawAccumBuffers {
            data: RawBuffer {
                buf: data_buf.as_ptr(),
                rows: data.rows,
                cols: data.cols,
                checked: data.checked,
            },
            accum: RawBuffer {
                buf: accum_buf.as_ptr(),
                rows: accum.rows,
                cols: accum.cols,
                checked: accum.checked,
            },
            global: RawBuffer {
                buf: global_buf.as_ptr(),
                rows: global.rows,
                cols: global.cols,
                checked: global.checked,
            },
            mix: RawBuffer {
                buf: mix_buf.as_ptr(),
                rows: mix.rows,
                cols: mix.cols,
                checked: mix.checked,
            },
        };
        let preflight = RawPreflightTrace {
            cycles: preflight.cycles.as_ptr(),
            txns: preflight.txns.as_ptr(),
            bigint_bytes: preflight.bigint_bytes.as_ptr(),
            txns_len: preflight.txns.len() as u32,
            bigint_bytes_len: preflight.bigint_bytes.len() as u32,
            table_split_cycle: preflight.table_split_cycle,
        };
        ffi_wrap(|| unsafe { risc0_circuit_rv32im_cpu_accum(&buffers, &preflight, cycles as u32) })
    }
}

impl CircuitHal<CpuHal> for CpuCircuitHal {
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

        const EXP_PO2: usize = log2_ceil(INV_RATE);
        let domain = steps * INV_RATE;
        let poly_mix_pows = map_pow(poly_mix, POLY_MIX_POWERS);

        // SAFETY: Convert a borrow of a cell into a raw const slice so that we can pass
        // it over the thread boundary. This should be safe because the scope of the
        // usage is within this function and each thread access will not overlap with
        // each other.

        let data = groups[REGISTER_GROUP_DATA].as_slice();
        let accum = groups[REGISTER_GROUP_ACCUM].as_slice();
        let mix = globals[GLOBAL_MIX].as_slice();
        let out = globals[GLOBAL_OUT].as_slice();
        let check = check.as_slice();

        let data = unsafe { std::slice::from_raw_parts(data.as_ptr(), data.len()) };
        let accum = unsafe { std::slice::from_raw_parts(accum.as_ptr(), accum.len()) };
        let mix = unsafe { std::slice::from_raw_parts(mix.as_ptr(), mix.len()) };
        let out = unsafe { std::slice::from_raw_parts(out.as_ptr(), out.len()) };
        let check = unsafe { std::slice::from_raw_parts(check.as_ptr(), check.len()) };
        let poly_mix_pows = poly_mix_pows.as_slice();

        let args: &[&[Val]] = &[accum, data, out, mix];

        (0..domain).into_par_iter().for_each(|cycle| {
            let args: Vec<*const Val> = args.iter().map(|x| (*x).as_ptr()).collect();
            let mut tot = ExtVal::ZERO;
            unsafe {
                risc0_circuit_rv32im_cpu_poly_fp(
                    cycle,
                    domain,
                    poly_mix_pows.as_ptr(),
                    args.as_ptr(),
                    &mut tot,
                )
            };
            let x = Val::ROU_FWD[po2 + EXP_PO2].pow(cycle);
            // Multiply by 3 to shift the evaluation point in the field.
            // This avoids collisions at roots of unity during polynomial checks,
            // and is part of the protocol’s algebraic structure.
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

    fn accumulate(
        &self,
        _preflight: &AccumPreflight,
        _ctrl: &CpuBuffer<Val>,
        _global: &CpuBuffer<Val>,
        _data: &CpuBuffer<Val>,
        _mix: &CpuBuffer<Val>,
        _accum: &CpuBuffer<Val>,
        _steps: usize,
    ) {
        unimplemented!()
    }
}

#[allow(dead_code)]
pub fn segment_prover() -> Result<Box<dyn SegmentProver>> {
    let hal_factory = || {
        let suite = Poseidon2HashSuite::new_suite();
        (Rc::new(CpuHal::new(suite)), Rc::new(CpuCircuitHal))
    };
    Ok(Box::new(SegmentProverImpl::new(hal_factory)))
}
