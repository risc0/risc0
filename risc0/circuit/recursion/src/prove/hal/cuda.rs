// Copyright 2025 RISC Zero, Inc.
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
    risc0_circuit_recursion_cuda_accum, risc0_circuit_recursion_cuda_eval_check,
    risc0_circuit_recursion_cuda_witgen,
};
use risc0_sys::ffi_wrap;
use risc0_zkp::{
    INV_RATE,
    core::log2_ceil,
    field::{
        RootsOfUnity,
        baby_bear::{BabyBearElem, BabyBearExtElem},
        map_pow,
    },
    hal::{
        AccumPreflight, Buffer, CircuitHal,
        cuda::{
            BufferImpl as CudaBuffer, CudaHal, CudaHalPoseidon2, CudaHalPoseidon254, CudaHalSha256,
            CudaHash, CudaHashPoseidon2, CudaHashPoseidon254, CudaHashSha256,
        },
    },
};

use crate::{
    GLOBAL_MIX, GLOBAL_OUT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL, REGISTER_GROUP_DATA,
    prove::{RecursionProver, RecursionProverImpl},
};

use super::{CircuitAccumulator, CircuitWitnessGenerator};

pub type CudaCircuitHalSha256 = CudaCircuitHal<CudaHashSha256>;
pub type CudaCircuitHalPoseidon2 = CudaCircuitHal<CudaHashPoseidon2>;
pub type CudaCircuitHalPoseidon254 = CudaCircuitHal<CudaHashPoseidon254>;

pub struct CudaCircuitHal<CH: CudaHash> {
    hal: Rc<CudaHal<CH>>,
}

impl<CH: CudaHash> CudaCircuitHal<CH> {
    pub fn new(hal: Rc<CudaHal<CH>>) -> Self {
        #[cfg(test)]
        gpu_guard::assert_gpu_semaphore_held();

        Self { hal }
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
            risc0_circuit_recursion_cuda_witgen(
                self.hal.stream.as_inner(),
                mode,
                &buffers,
                preflight,
                total_cycles,
            )
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
            risc0_circuit_recursion_cuda_accum(
                self.hal.stream.as_inner(),
                &buffers,
                work_cycles,
                total_cycles,
            )
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
        let poly_mix_pows_vec = map_pow(poly_mix, crate::info::POLY_MIX_POWERS);
        let poly_mix_pows =
            CudaBuffer::copy_from("poly_mix", &poly_mix_pows_vec[..], self.hal.stream.clone());

        let check = check.as_device_ptr();
        let ctrl = ctrl.as_device_ptr();
        let data = data.as_device_ptr();
        let accum = accum.as_device_ptr();
        let mix = mix.as_device_ptr();
        let out = out.as_device_ptr();
        let poly_mix_pows = poly_mix_pows.as_device_ptr();

        ffi_wrap(|| unsafe {
            risc0_circuit_recursion_cuda_eval_check(
                self.hal.stream.as_inner(),
                check.as_ptr() as *const BabyBearElem,
                ctrl.as_ptr() as *const BabyBearElem,
                data.as_ptr() as *const BabyBearElem,
                accum.as_ptr() as *const BabyBearElem,
                mix.as_ptr() as *const BabyBearElem,
                out.as_ptr() as *const BabyBearElem,
                &rou as *const BabyBearElem,
                po2 as u32,
                domain as u32,
                poly_mix_pows.as_ptr() as *const BabyBearExtElem,
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

#[cfg_attr(feature = "dual", expect(dead_code))]
pub(crate) fn recursion_prover(hashfn: &str) -> Result<Box<dyn RecursionProver>> {
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
    #[gpu_guard::gpu_guard]
    fn eval_check() {
        const PO2: usize = 4;
        let cpu_hal: CpuHal<BabyBear> = CpuHal::new(Sha256HashSuite::new_suite());
        let cpu_eval = CpuCircuitHal;
        let gpu_hal = Rc::new(CudaHalSha256::new());
        let gpu_eval = super::CudaCircuitHalSha256::new(gpu_hal.clone());
        crate::testutil::eval_check(&cpu_hal, cpu_eval, gpu_hal.as_ref(), gpu_eval, PO2);
    }
}
