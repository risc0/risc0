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
use risc0_circuit_recursion_sys::{
    risc0_circuit_recursion_cpu_accum, risc0_circuit_recursion_cpu_eval_check,
    risc0_circuit_recursion_cpu_witgen, RawAccumBuffers, RawExecBuffers, RawPreflightTrace,
    StepMode,
};
use risc0_sys::ffi_wrap;
use risc0_zkp::{
    core::{hash::HashSuite, log2_ceil},
    field::{
        baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
        map_pow, RootsOfUnity as _,
    },
    hal::{cpu::CpuBuffer, AccumPreflight, CircuitHal},
    INV_RATE,
};

use crate::{
    prove::{RecursionProver, RecursionProverImpl},
    GLOBAL_MIX, GLOBAL_OUT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL, REGISTER_GROUP_DATA,
};

use super::{CircuitAccumulator, CircuitWitnessGenerator};

type CpuHal = risc0_zkp::hal::cpu::CpuHal<BabyBear>;

#[derive(Default)]
pub struct CpuCircuitHal;

impl CircuitWitnessGenerator<CpuHal> for CpuCircuitHal {
    fn generate_witness(
        &self,
        mode: StepMode,
        cycles: u32,
        preflight: &RawPreflightTrace,
        ctrl: &CpuBuffer<BabyBearElem>,
        data: &CpuBuffer<BabyBearElem>,
        global: &CpuBuffer<BabyBearElem>,
    ) -> Result<()> {
        let ctrl = ctrl.as_slice();
        let data = data.as_slice();
        let global = global.as_slice();
        let buffers = RawExecBuffers {
            ctrl: ctrl.as_ptr(),
            data: data.as_ptr(),
            global: global.as_ptr(),
        };
        ffi_wrap(|| unsafe {
            risc0_circuit_recursion_cpu_witgen(mode, &buffers, preflight, cycles)
        })
    }
}

impl CircuitAccumulator<CpuHal> for CpuCircuitHal {
    fn accumulate(
        &self,
        steps: u32,
        cycles: u32,
        ctrl: &CpuBuffer<BabyBearElem>,
        global: &CpuBuffer<BabyBearElem>,
        data: &CpuBuffer<BabyBearElem>,
        mix: &CpuBuffer<BabyBearElem>,
        accum: &CpuBuffer<BabyBearElem>,
    ) -> Result<()> {
        let ctrl = ctrl.as_slice();
        let global = global.as_slice();
        let data = data.as_slice();
        let mix = mix.as_slice();
        let accum = accum.as_slice();
        let buffers = RawAccumBuffers {
            ctrl: ctrl.as_ptr(),
            global: global.as_ptr(),
            data: data.as_ptr(),
            mix: mix.as_ptr(),
            accum: accum.as_ptr(),
        };
        ffi_wrap(|| unsafe { risc0_circuit_recursion_cpu_accum(&buffers, steps, cycles) })
    }
}

impl CircuitHal<CpuHal> for CpuCircuitHal {
    fn eval_check(
        &self,
        check: &CpuBuffer<BabyBearElem>,
        groups: &[&CpuBuffer<BabyBearElem>],
        globals: &[&CpuBuffer<BabyBearElem>],
        poly_mix: BabyBearExtElem,
        po2: usize,
        steps: usize,
    ) {
        const EXP_PO2: usize = log2_ceil(INV_RATE);
        let domain = steps * INV_RATE;

        let ctrl = groups[REGISTER_GROUP_CTRL].as_slice();
        let data = groups[REGISTER_GROUP_DATA].as_slice();
        let accum = groups[REGISTER_GROUP_ACCUM].as_slice();
        let mix = globals[GLOBAL_MIX].as_slice();
        let global = globals[GLOBAL_OUT].as_slice();
        let check = check.as_slice();

        let poly_mix_pows = map_pow(poly_mix, crate::info::POLY_MIX_POWERS);
        let poly_mix_pows = poly_mix_pows.as_slice();

        let rou = BabyBearElem::ROU_FWD[po2 + EXP_PO2];

        let buffers = RawAccumBuffers {
            ctrl: ctrl.as_ptr(),
            global: global.as_ptr(),
            data: data.as_ptr(),
            mix: mix.as_ptr(),
            accum: accum.as_ptr(),
        };

        ffi_wrap(|| unsafe {
            risc0_circuit_recursion_cpu_eval_check(
                &buffers,
                poly_mix_pows.as_ptr(),
                check.as_ptr(),
                rou,
                po2 as u32,
                domain as u32,
            )
        })
        .unwrap();
    }

    #[allow(unused)]
    fn accumulate(
        &self,
        _preflight: &AccumPreflight,
        ctrl: &CpuBuffer<BabyBearElem>,
        io: &CpuBuffer<BabyBearElem>,
        data: &CpuBuffer<BabyBearElem>,
        mix: &CpuBuffer<BabyBearElem>,
        accum: &CpuBuffer<BabyBearElem>,
        steps: usize,
    ) {
        unimplemented!()
    }
}

#[allow(dead_code)]
pub fn recursion_prover(suite: HashSuite<BabyBear>) -> Result<Box<dyn RecursionProver>> {
    let hal = Rc::new(CpuHal::new(suite));
    let circuit_hal = Rc::new(CpuCircuitHal);
    Ok(Box::new(RecursionProverImpl::new(hal, circuit_hal)))
}
