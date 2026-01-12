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

use anyhow::{Result, bail};
use risc0_circuit_recursion_sys::{
    RawAccumBuffers, RawExecBuffers, RawPreflightTrace, StepMode,
    risc0_circuit_recursion_cpu_accum, risc0_circuit_recursion_cpu_eval_check,
    risc0_circuit_recursion_cpu_witgen,
};
use risc0_sys::ffi_wrap;
use risc0_zkp::{
    INV_RATE,
    core::{
        hash::{
            poseidon_254::Poseidon254HashSuite, poseidon2::Poseidon2HashSuite, sha::Sha256HashSuite,
        },
        log2_ceil,
    },
    field::{
        RootsOfUnity as _,
        baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
        map_pow,
    },
    hal::{AccumPreflight, CircuitHal, cpu::CpuBuffer},
};

use crate::{
    GLOBAL_MIX, GLOBAL_OUT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL, REGISTER_GROUP_DATA,
    prove::{RecursionProver, RecursionProverImpl},
};

use super::{CircuitAccumulator, CircuitWitnessGenerator};

pub(crate) type CpuHal = risc0_zkp::hal::cpu::CpuHal<BabyBear>;

#[derive(Default)]
pub(crate) struct CpuCircuitHal;

impl CircuitWitnessGenerator<CpuHal> for CpuCircuitHal {
    fn generate_witness(
        &self,
        mode: StepMode,
        total_cycles: u32,
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
            risc0_circuit_recursion_cpu_witgen(mode, &buffers, preflight, total_cycles)
        })
    }
}

impl CircuitAccumulator<CpuHal> for CpuCircuitHal {
    fn accumulate(
        &self,
        work_cycles: u32,
        total_cycles: u32,
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
        ffi_wrap(|| unsafe {
            risc0_circuit_recursion_cpu_accum(&buffers, work_cycles, total_cycles)
        })
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
pub(crate) fn recursion_prover(hashfn: &str) -> Result<Box<dyn RecursionProver>> {
    let suite = match hashfn {
        "poseidon2" => Poseidon2HashSuite::new_suite(),
        "poseidon_254" => Poseidon254HashSuite::new_suite(),
        "sha-256" => Sha256HashSuite::new_suite(),
        _ => bail!("Unsupported hashfn: {hashfn}"),
    };

    let hal = Rc::new(CpuHal::new(suite));
    let circuit_hal = Rc::new(CpuCircuitHal);
    Ok(Box::new(RecursionProverImpl::new(hal, circuit_hal)))
}
