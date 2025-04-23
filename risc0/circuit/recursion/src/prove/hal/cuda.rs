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

use anyhow::{bail, Result};
use risc0_circuit_recursion_sys::{
    risc0_circuit_recursion_cuda_accum, risc0_circuit_recursion_cuda_eval_check,
    risc0_circuit_recursion_cuda_witgen, RawAccumBuffers, RawExecBuffers, RawPreflightTrace,
    StepMode,
};
use risc0_sys::ffi_wrap;
use risc0_zkp::{
    core::log2_ceil,
    field::{
        baby_bear::{BabyBearElem, BabyBearExtElem},
        map_pow, RootsOfUnity,
    },
    hal::{
        cuda::{
            BufferImpl as CudaBuffer, CudaHal, CudaHalPoseidon2, CudaHalPoseidon254, CudaHalSha256,
            CudaHash, CudaHashPoseidon2, CudaHashPoseidon254, CudaHashSha256,
        },
        AccumPreflight, Buffer, CircuitHal,
    },
    INV_RATE,
};

use crate::{
    prove::{RecursionProver, RecursionProverImpl},
    GLOBAL_MIX, GLOBAL_OUT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL, REGISTER_GROUP_DATA,
};

use super::{CircuitAccumulator, CircuitWitnessGenerator};

type CudaCircuitHalSha256 = CudaCircuitHal<CudaHashSha256>;
type CudaCircuitHalPoseidon2 = CudaCircuitHal<CudaHashPoseidon2>;
type CudaCircuitHalPoseidon254 = CudaCircuitHal<CudaHashPoseidon254>;

struct CudaCircuitHal<CH: CudaHash> {
    _hal: Rc<CudaHal<CH>>, // retain a reference to ensure the context remains valid
}

impl<CH: CudaHash> CudaCircuitHal<CH> {
    pub fn new(_hal: Rc<CudaHal<CH>>) -> Self {
        Self { _hal }
    }
}

impl<CH: CudaHash> CircuitWitnessGenerator<CudaHal<CH>> for CudaCircuitHal<CH> {
    fn generate_witness(
        &self,
        mode: StepMode,
        total_cycles: u32,
        preflight: &RawPreflightTrace,
        ctrl: &CudaBuffer<BabyBearElem>,
        data: &CudaBuffer<BabyBearElem>,
        global: &CudaBuffer<BabyBearElem>,
    ) -> Result<()> {
        let ctrl = ctrl.as_device_ptr();
        let data = data.as_device_ptr();
        let global = global.as_device_ptr();
        let buffers = RawExecBuffers {
            ctrl: ctrl.as_ptr() as *const BabyBearElem,
            data: data.as_ptr() as *const BabyBearElem,
            global: global.as_ptr() as *const BabyBearElem,
        };
        ffi_wrap(|| unsafe {
            risc0_circuit_recursion_cuda_witgen(mode, &buffers, preflight, total_cycles)
        })
    }
}

impl<CH: CudaHash> CircuitAccumulator<CudaHal<CH>> for CudaCircuitHal<CH> {
    fn accumulate(
        &self,
        work_cycles: u32,
        total_cycles: u32,
        ctrl: &CudaBuffer<BabyBearElem>,
        global: &CudaBuffer<BabyBearElem>,
        data: &CudaBuffer<BabyBearElem>,
        mix: &CudaBuffer<BabyBearElem>,
        accum: &CudaBuffer<BabyBearElem>,
    ) -> Result<()> {
        let ctrl = ctrl.as_device_ptr();
        let global = global.as_device_ptr();
        let data = data.as_device_ptr();
        let mix = mix.as_device_ptr();
        let accum = accum.as_device_ptr();
        let buffers = RawAccumBuffers {
            ctrl: ctrl.as_ptr() as *const BabyBearElem,
            global: global.as_ptr() as *const BabyBearElem,
            data: data.as_ptr() as *const BabyBearElem,
            mix: mix.as_ptr() as *const BabyBearElem,
            accum: accum.as_ptr() as *const BabyBearElem,
        };
        ffi_wrap(|| unsafe {
            risc0_circuit_recursion_cuda_accum(&buffers, work_cycles, total_cycles)
        })
    }
}

impl<CH: CudaHash> CircuitHal<CudaHal<CH>> for CudaCircuitHal<CH> {
    fn eval_check(
        &self,
        check: &CudaBuffer<BabyBearElem>,
        groups: &[&CudaBuffer<BabyBearElem>],
        globals: &[&CudaBuffer<BabyBearElem>],
        poly_mix: BabyBearExtElem,
        po2: usize,
        steps: usize,
    ) {
        let ctrl = groups[REGISTER_GROUP_CTRL];
        let data = groups[REGISTER_GROUP_DATA];
        let accum = groups[REGISTER_GROUP_ACCUM];
        let mix = globals[GLOBAL_MIX];
        let out = globals[GLOBAL_OUT];
        tracing::debug!(
            "check: {}, code: {}, data: {}, accum: {}, mix: {} out: {}",
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
        let rou = BabyBearElem::ROU_FWD[po2 + EXP_PO2];
        let poly_mix_pows = map_pow(poly_mix, crate::info::POLY_MIX_POWERS);

        let check = check.as_device_ptr();
        let ctrl = ctrl.as_device_ptr();
        let data = data.as_device_ptr();
        let accum = accum.as_device_ptr();
        let mix = mix.as_device_ptr();
        let out = out.as_device_ptr();

        ffi_wrap(|| unsafe {
            risc0_circuit_recursion_cuda_eval_check(
                check.as_ptr() as *const BabyBearElem,
                ctrl.as_ptr() as *const BabyBearElem,
                data.as_ptr() as *const BabyBearElem,
                accum.as_ptr() as *const BabyBearElem,
                mix.as_ptr() as *const BabyBearElem,
                out.as_ptr() as *const BabyBearElem,
                &rou as *const BabyBearElem,
                po2 as u32,
                domain as u32,
                poly_mix_pows.as_ptr(),
            )
        })
        .unwrap();
    }

    #[allow(unused)]
    fn accumulate(
        &self,
        _preflight: &AccumPreflight,
        ctrl: &CudaBuffer<BabyBearElem>,
        io: &CudaBuffer<BabyBearElem>,
        data: &CudaBuffer<BabyBearElem>,
        mix: &CudaBuffer<BabyBearElem>,
        accum: &CudaBuffer<BabyBearElem>,
        steps: usize,
    ) {
        unimplemented!()
    }
}

#[cfg(test)]
mod tests {
    use std::rc::Rc;

    use risc0_core::field::baby_bear::BabyBear;
    use risc0_zkp::{
        core::hash::sha::Sha256HashSuite,
        hal::{cpu::CpuHal, cuda::CudaHalSha256},
    };
    use test_log::test;

    use crate::prove::hal::cpu::CpuCircuitHal;

    #[test]
    fn eval_check() {
        const PO2: usize = 4;
        let cpu_hal: CpuHal<BabyBear> = CpuHal::new(Sha256HashSuite::new_suite());
        let cpu_eval = CpuCircuitHal;
        let gpu_hal = Rc::new(CudaHalSha256::new());
        let gpu_eval = super::CudaCircuitHalSha256::new(gpu_hal.clone());
        crate::testutil::eval_check(&cpu_hal, cpu_eval, gpu_hal.as_ref(), gpu_eval, PO2);
    }
}

pub fn recursion_prover(hashfn: &str) -> Result<Box<dyn RecursionProver>> {
    match hashfn {
        "poseidon2" => {
            let hal = Rc::new(CudaHalPoseidon2::new());
            let circuit_hal = Rc::new(CudaCircuitHalPoseidon2::new(hal.clone()));
            Ok(Box::new(RecursionProverImpl::new(hal, circuit_hal)))
        }
        "poseidon_254" => {
            let hal = Rc::new(CudaHalPoseidon254::new());
            let circuit_hal = Rc::new(CudaCircuitHalPoseidon254::new(hal.clone()));
            Ok(Box::new(RecursionProverImpl::new(hal, circuit_hal)))
        }
        "sha-256" => {
            let hal = Rc::new(CudaHalSha256::new());
            let circuit_hal = Rc::new(CudaCircuitHalSha256::new(hal.clone()));
            Ok(Box::new(RecursionProverImpl::new(hal, circuit_hal)))
        }
        _ => bail!("Unsupported hashfn: {hashfn}"),
    }
}
