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

//! CubeCL circuit HAL for the recursion circuit.
//!
//! Uses the CubeClHal for NTT/hash/elementwise operations and falls back
//! to CPU FFI for circuit-specific operations (witgen, accum, eval_check).

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
    core::log2_ceil,
    field::{
        RootsOfUnity as _,
        baby_bear::{BabyBearElem, BabyBearExtElem},
        map_pow,
    },
    hal::{
        AccumPreflight, Buffer, CircuitHal,
        cubecl::{buffer::CubeClBuffer, hal::CubeClHal},
    },
};

use crate::{
    GLOBAL_MIX, GLOBAL_OUT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL, REGISTER_GROUP_DATA,
    prove::{RecursionProver, RecursionProverImpl},
};

use super::{CircuitAccumulator, CircuitWitnessGenerator};

pub struct CubeClCircuitHal {
    #[allow(dead_code)]
    hal: Rc<CubeClHal>,
}

impl CubeClCircuitHal {
    pub fn new(hal: Rc<CubeClHal>) -> Self {
        Self { hal }
    }
}

impl CircuitWitnessGenerator<CubeClHal> for CubeClCircuitHal {
    fn generate_witness(
        &self,
        mode: StepMode,
        total_cycles: u32,
        preflight: &RawPreflightTrace,
        ctrl: &CubeClBuffer<BabyBearElem>,
        data: &CubeClBuffer<BabyBearElem>,
        global: &CubeClBuffer<BabyBearElem>,
    ) -> Result<()> {
        // CPU fallback: read GPU buffers to host, run CPU witgen, write back
        let ctrl_vec = ctrl.to_vec();
        let global_vec = global.to_vec();

        // data is the output buffer - read current contents, let FFI modify, write back
        data.view_mut(|data_slice| {
            let buffers = RawExecBuffers {
                ctrl: ctrl_vec.as_ptr(),
                data: data_slice.as_ptr(),
                global: global_vec.as_ptr(),
            };
            ffi_wrap(|| unsafe {
                risc0_circuit_recursion_cpu_witgen(mode, &buffers, preflight, total_cycles)
            })
            .unwrap();
        });

        Ok(())
    }
}

impl CircuitAccumulator<CubeClHal> for CubeClCircuitHal {
    fn accumulate(
        &self,
        work_cycles: u32,
        total_cycles: u32,
        ctrl: &CubeClBuffer<BabyBearElem>,
        global: &CubeClBuffer<BabyBearElem>,
        data: &CubeClBuffer<BabyBearElem>,
        mix: &CubeClBuffer<BabyBearElem>,
        accum: &CubeClBuffer<BabyBearElem>,
    ) -> Result<()> {
        // CPU fallback: read all input buffers, run CPU accum, write back accum
        let ctrl_vec = ctrl.to_vec();
        let global_vec = global.to_vec();
        let data_vec = data.to_vec();
        let mix_vec = mix.to_vec();

        // accum is the output buffer
        accum.view_mut(|accum_slice| {
            let buffers = RawAccumBuffers {
                ctrl: ctrl_vec.as_ptr(),
                global: global_vec.as_ptr(),
                data: data_vec.as_ptr(),
                mix: mix_vec.as_ptr(),
                accum: accum_slice.as_ptr(),
            };
            ffi_wrap(|| unsafe {
                risc0_circuit_recursion_cpu_accum(&buffers, work_cycles, total_cycles)
            })
            .unwrap();
        });

        Ok(())
    }
}

impl CircuitHal<CubeClHal> for CubeClCircuitHal {
    fn eval_check(
        &self,
        check: &CubeClBuffer<BabyBearElem>,
        groups: &[&CubeClBuffer<BabyBearElem>],
        globals: &[&CubeClBuffer<BabyBearElem>],
        poly_mix: BabyBearExtElem,
        po2: usize,
        steps: usize,
    ) {
        const EXP_PO2: usize = log2_ceil(INV_RATE);
        let domain = steps * INV_RATE;

        // Read input buffers to host
        let ctrl_vec = groups[REGISTER_GROUP_CTRL].to_vec();
        let data_vec = groups[REGISTER_GROUP_DATA].to_vec();
        let accum_vec = groups[REGISTER_GROUP_ACCUM].to_vec();
        let mix_vec = globals[GLOBAL_MIX].to_vec();
        let global_vec = globals[GLOBAL_OUT].to_vec();

        let poly_mix_pows = map_pow(poly_mix, crate::info::POLY_MIX_POWERS);
        let poly_mix_pows = poly_mix_pows.as_slice();

        let rou = BabyBearElem::ROU_FWD[po2 + EXP_PO2];

        let buffers = RawAccumBuffers {
            ctrl: ctrl_vec.as_ptr(),
            global: global_vec.as_ptr(),
            data: data_vec.as_ptr(),
            mix: mix_vec.as_ptr(),
            accum: accum_vec.as_ptr(),
        };

        // check is the output buffer
        check.view_mut(|check_slice| {
            ffi_wrap(|| unsafe {
                risc0_circuit_recursion_cpu_eval_check(
                    &buffers,
                    poly_mix_pows.as_ptr(),
                    check_slice.as_ptr(),
                    rou,
                    po2 as u32,
                    domain as u32,
                )
            })
            .unwrap();
        });
    }

    #[allow(unused)]
    fn accumulate(
        &self,
        _preflight: &AccumPreflight,
        ctrl: &CubeClBuffer<BabyBearElem>,
        io: &CubeClBuffer<BabyBearElem>,
        data: &CubeClBuffer<BabyBearElem>,
        mix: &CubeClBuffer<BabyBearElem>,
        accum: &CubeClBuffer<BabyBearElem>,
        steps: usize,
    ) {
        unimplemented!()
    }
}

pub(crate) fn recursion_prover(hashfn: &str) -> Result<Box<dyn RecursionProver>> {
    match hashfn {
        "poseidon2" => {
            let hal = Rc::new(CubeClHal::new());
            let circuit_hal = Rc::new(CubeClCircuitHal::new(hal.clone()));
            Ok(Box::new(RecursionProverImpl::new(hal, circuit_hal)))
        }
        _ => bail!("CubeCL HAL only supports poseidon2, got: {hashfn}"),
    }
}

#[cfg(test)]
mod tests {
    use std::rc::Rc;

    use risc0_core::field::baby_bear::BabyBear;
    use risc0_zkp::{
        core::hash::poseidon2::Poseidon2HashSuite,
        hal::{cpu::CpuHal, cubecl::hal::CubeClHal},
    };
    use test_log::test;

    use crate::prove::hal::cpu::CpuCircuitHal;

    #[test]
    #[gpu_guard::gpu_guard]
    fn eval_check() {
        const PO2: usize = 4;
        let cpu_hal: CpuHal<BabyBear> = CpuHal::new(Poseidon2HashSuite::new_suite());
        let cpu_eval = CpuCircuitHal;
        let gpu_hal = Rc::new(CubeClHal::new());
        let gpu_eval = super::CubeClCircuitHal::new(gpu_hal.clone());
        crate::testutil::eval_check(&cpu_hal, cpu_eval, gpu_hal.as_ref(), gpu_eval, PO2);
    }
}
