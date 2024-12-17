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

use std::rc::Rc;

use anyhow::Result;
use risc0_circuit_rv32im_v2_sys::{
    risc0_circuit_rv32im_v2_cpu_accum, risc0_circuit_rv32im_v2_cuda_eval_check,
    risc0_circuit_rv32im_v2_cuda_witgen, RawAccumBuffers, RawBuffer, RawExecBuffers,
    RawPreflightTrace,
};
use risc0_core::{
    field::{map_pow, Elem, RootsOfUnity},
    scope,
};
use risc0_sys::ffi_wrap;
use risc0_zkp::{
    core::log2_ceil,
    field::ExtElem as _,
    hal::{
        cuda::{BufferImpl as CudaBuffer, CudaHal, CudaHalPoseidon2, CudaHash, CudaHashPoseidon2},
        AccumPreflight, Buffer, CircuitHal, Hal,
    },
    INV_RATE,
};

use crate::{
    prove::{SegmentProver, GLOBAL_MIX, GLOBAL_OUT},
    zirgen::{
        circuit::{ExtVal, Val, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE, REGISTER_GROUP_DATA},
        info::{NUM_POLY_MIX_POWERS, POLY_MIX_POWERS},
    },
};

use super::{
    CircuitAccumulator, CircuitWitnessGenerator, MetaBuffer, PreflightTrace, SegmentProverImpl,
    StepMode,
};

pub struct CudaCircuitHal<CH: CudaHash> {
    hal: Rc<CudaHal<CH>>, // retain a reference to ensure the context remains valid
}

impl<CH: CudaHash> CudaCircuitHal<CH> {
    pub fn new(hal: Rc<CudaHal<CH>>) -> Self {
        Self { hal }
    }
}

impl<CH: CudaHash> CircuitWitnessGenerator<CudaHal<CH>> for CudaCircuitHal<CH> {
    fn generate_witness(
        &self,
        mode: StepMode,
        preflight: &PreflightTrace,
        global: &MetaBuffer<CudaHal<CH>>,
        data: &MetaBuffer<CudaHal<CH>>,
    ) -> Result<()> {
        scope!("witgen");

        let cycles = preflight.cycles.len();
        assert_eq!(cycles, data.rows);
        tracing::debug!("witgen: {cycles}");

        let global_ptr = global.buf.as_device_ptr();
        let data_ptr = data.buf.as_device_ptr();
        let buffers = RawExecBuffers {
            global: RawBuffer {
                buf: global_ptr.as_ptr() as *const Val,
                rows: global.rows,
                cols: global.cols,
                checked_reads: global.checked_reads,
            },
            data: RawBuffer {
                buf: data_ptr.as_ptr() as *const Val,
                rows: data.rows,
                cols: data.cols,
                checked_reads: data.checked_reads,
            },
        };

        let preflight = RawPreflightTrace {
            cycles: preflight.cycles.as_ptr(),
            txns: preflight.txns.as_ptr(),
            txns_len: preflight.txns.len() as u32,
            table_split_cycle: preflight.table_split_cycle,
        };
        ffi_wrap(|| unsafe {
            risc0_circuit_rv32im_v2_cuda_witgen(mode as u32, &buffers, &preflight, cycles as u32)
        })
    }
}

impl<CH: CudaHash> CircuitAccumulator<CudaHal<CH>> for CudaCircuitHal<CH> {
    fn step_accum(
        &self,
        preflight: &PreflightTrace,
        data: &MetaBuffer<CudaHal<CH>>,
        accum: &MetaBuffer<CudaHal<CH>>,
        mix: &MetaBuffer<CudaHal<CH>>,
    ) -> Result<()> {
        scope!("accumulate");

        let cycles = preflight.cycles.len();
        tracing::debug!("accumulate: {cycles}");

        let data_vec = data.buf.to_vec();
        let accum_vec = accum.buf.to_vec();
        let mix_vec = mix.buf.to_vec();
        let buffers = RawAccumBuffers {
            data: RawBuffer {
                buf: data_vec.as_ptr(),
                rows: data.rows,
                cols: data.cols,
                checked_reads: data.checked_reads,
            },
            accum: RawBuffer {
                buf: accum_vec.as_ptr(),
                rows: accum.rows,
                cols: accum.cols,
                checked_reads: accum.checked_reads,
            },
            mix: RawBuffer {
                buf: mix_vec.as_ptr(),
                rows: mix.rows,
                cols: mix.cols,
                checked_reads: mix.checked_reads,
            },
        };
        let preflight = RawPreflightTrace {
            cycles: preflight.cycles.as_ptr(),
            txns: preflight.txns.as_ptr(),
            txns_len: preflight.txns.len() as u32,
            table_split_cycle: preflight.table_split_cycle,
        };
        let result = ffi_wrap(|| unsafe {
            risc0_circuit_rv32im_v2_cpu_accum(&buffers, &preflight, cycles as u32)
        });
        data.buf.view_mut(|view| {
            view.copy_from_slice(&data_vec);
        });
        accum.buf.view_mut(|view| {
            view.copy_from_slice(&accum_vec);
        });
        mix.buf.view_mut(|view| {
            view.copy_from_slice(&mix_vec);
        });
        result
    }
}

impl<CH: CudaHash> CircuitHal<CudaHal<CH>> for CudaCircuitHal<CH> {
    fn accumulate(
        &self,
        _preflight: &AccumPreflight,
        _ctrl: &CudaBuffer<Val>,
        _io: &CudaBuffer<Val>,
        _data: &CudaBuffer<Val>,
        _mix: &CudaBuffer<Val>,
        _accum: &CudaBuffer<Val>,
        _steps: usize,
    ) {
    }

    fn eval_check(
        &self,
        check: &CudaBuffer<Val>,
        groups: &[&CudaBuffer<Val>],
        globals: &[&CudaBuffer<Val>],
        poly_mix: ExtVal,
        po2: usize,
        steps: usize,
    ) {
        scope!("eval_check");

        let accum = groups[REGISTER_GROUP_ACCUM];
        let ctrl = groups[REGISTER_GROUP_CODE];
        let data = groups[REGISTER_GROUP_DATA];
        let mix = globals[GLOBAL_MIX];
        let out = globals[GLOBAL_OUT];
        tracing::debug!(
            "check: {}, ctrl: {}, data: {}, accum: {}, mix: {} out: {}",
            check.size(),
            ctrl.size(),
            data.size(),
            accum.size(),
            mix.size(),
            out.size()
        );
        tracing::debug!(
            "total: {}",
            (check.size() + ctrl.size() + data.size() + accum.size() + mix.size() + out.size()) * 4
        );

        const EXP_PO2: usize = log2_ceil(INV_RATE);
        let domain = steps * INV_RATE;
        let rou = Val::ROU_FWD[po2 + EXP_PO2];

        tracing::debug!("steps: {steps}, domain: {domain}, po2: {po2}, rou: {rou:?}");
        let poly_mix_pows = map_pow(poly_mix, POLY_MIX_POWERS);
        let poly_mix_pows: &[u32; ExtVal::EXT_SIZE * NUM_POLY_MIX_POWERS] =
            ExtVal::as_u32_slice(poly_mix_pows.as_slice())
                .try_into()
                .unwrap();

        ffi_wrap(|| unsafe {
            risc0_circuit_rv32im_v2_cuda_eval_check(
                check.as_device_ptr(),
                ctrl.as_device_ptr(),
                data.as_device_ptr(),
                accum.as_device_ptr(),
                mix.as_device_ptr(),
                out.as_device_ptr(),
                &rou as *const Val,
                po2 as u32,
                domain as u32,
                poly_mix_pows.as_ptr(),
            )
        })
        .unwrap();
    }
}

pub type CudaCircuitHalPoseidon2 = CudaCircuitHal<CudaHashPoseidon2>;

pub fn segment_prover() -> Result<Box<dyn SegmentProver>> {
    let hal = Rc::new(CudaHalPoseidon2::new());
    let circuit_hal = Rc::new(CudaCircuitHalPoseidon2::new(hal.clone()));
    Ok(Box::new(SegmentProverImpl::new(hal, circuit_hal)))
}

// #[cfg(test)]
// mod tests {
//     use std::rc::Rc;

//     use risc0_core::field::baby_bear::BabyBear;
//     use risc0_zkp::{
//         core::hash::sha::Sha256HashSuite,
//         hal::{cpu::CpuHal, cuda::CudaHalSha256},
//     };
//     use test_log::test;

//     use crate::prove::hal::cpu::CpuCircuitHal;

//     #[test]
//     fn eval_check() {
//         const PO2: usize = 4;
//         let cpu_hal: CpuHal<BabyBear> = CpuHal::new(Sha256HashSuite::new_suite());
//         let cpu_eval = CpuCircuitHal;
//         let gpu_hal = Rc::new(CudaHalSha256::new());
//         let gpu_eval = super::CudaCircuitHal::new(gpu_hal.clone());
//         crate::prove::testutil::eval_check(&cpu_hal, cpu_eval, gpu_hal.as_ref(), gpu_eval, PO2);
//     }
// }
