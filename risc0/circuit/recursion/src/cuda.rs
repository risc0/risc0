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

use cust::{memory::GpuBuffer as _, prelude::*};
use risc0_sys::{cuda::SpparkError, CppError};
use risc0_zkp::{
    core::log2_ceil,
    field::{
        baby_bear::{BabyBearElem, BabyBearExtElem},
        map_pow, Elem, ExtElem, RootsOfUnity,
    },
    hal::{
        cuda::{
            BufferImpl as CudaBuffer, CudaHal, CudaHash, CudaHashPoseidon, CudaHashPoseidon2,
            CudaHashSha256, DeviceExtElem,
        },
        Buffer, CircuitHal, Hal,
    },
    INV_RATE, ZK_CYCLES,
};

use crate::{
    GLOBAL_MIX, GLOBAL_OUT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL, REGISTER_GROUP_DATA,
};

#[repr(C)]
enum AccumOpType {
    #[allow(dead_code)]
    Add,
    Multiply,
}

pub struct CudaCircuitHal<CH: CudaHash> {
    hal: Rc<CudaHal<CH>>, // retain a reference to ensure the context remains valid
}

impl<CH: CudaHash> CudaCircuitHal<CH> {
    pub fn new(hal: Rc<CudaHal<CH>>) -> Self {
        Self { hal }
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
        let poly_mix_pows: &[u32; BabyBearExtElem::EXT_SIZE * crate::info::NUM_POLY_MIX_POWERS] =
            BabyBearExtElem::as_u32_slice(poly_mix_pows.as_slice())
                .try_into()
                .unwrap();

        extern "C" {
            fn risc0_circuit_recursion_cuda_eval_check(
                check: DevicePointer<u8>,
                ctrl: DevicePointer<u8>,
                data: DevicePointer<u8>,
                accum: DevicePointer<u8>,
                mix: DevicePointer<u8>,
                io: DevicePointer<u8>,
                rou: *const BabyBearElem,
                po2: u32,
                domain: u32,
                poly_mix_pows: *const u32,
            ) -> CppError;
        }

        unsafe {
            risc0_circuit_recursion_cuda_eval_check(
                check.as_device_ptr(),
                ctrl.as_device_ptr(),
                data.as_device_ptr(),
                accum.as_device_ptr(),
                mix.as_device_ptr(),
                out.as_device_ptr(),
                &rou as *const BabyBearElem,
                po2 as u32,
                domain as u32,
                poly_mix_pows.as_ptr(),
            )
            .unwrap();
        }
    }

    fn accumulate(
        &self,
        ctrl: &CudaBuffer<BabyBearElem>,
        io: &CudaBuffer<BabyBearElem>,
        data: &CudaBuffer<BabyBearElem>,
        mix: &CudaBuffer<BabyBearElem>,
        accum: &CudaBuffer<BabyBearElem>,
        steps: usize,
    ) {
        let count = steps - ZK_CYCLES;

        let wom = vec![DeviceExtElem(BabyBearExtElem::ONE); steps];
        let wom = DeviceBuffer::from_slice(&wom).unwrap();

        tracing::info_span!("step_compute_accum").in_scope(|| {
            extern "C" {
                fn risc0_circuit_recursion_cuda_step_compute_accum(
                    ctrl: DevicePointer<u8>,
                    data: DevicePointer<u8>,
                    mix: DevicePointer<u8>,
                    wom: DevicePointer<DeviceExtElem>,
                    steps: u32,
                    count: u32,
                ) -> CppError;
            }

            unsafe {
                risc0_circuit_recursion_cuda_step_compute_accum(
                    ctrl.as_device_ptr(),
                    data.as_device_ptr(),
                    mix.as_device_ptr(),
                    wom.as_device_ptr(),
                    steps as u32,
                    count as u32,
                )
                .unwrap();
            }
        });

        tracing::info_span!("prefix_products").in_scope(|| {
            extern "C" {
                fn sppark_calc_prefix_operation(
                    d_elems: DevicePointer<DeviceExtElem>,
                    count: u32,
                    op: AccumOpType,
                ) -> SpparkError;
            }

            let err = unsafe {
                sppark_calc_prefix_operation(
                    wom.as_device_ptr(),
                    steps as u32,
                    AccumOpType::Multiply,
                )
            };
            if err.code != 0 {
                panic!("Failure during sppark_calc_prefix_operation: {err}");
            }
        });

        tracing::info_span!("step_verify_accum").in_scope(|| {
            extern "C" {
                fn risc0_circuit_recursion_cuda_step_verify_accum(
                    ctrl: DevicePointer<u8>,
                    data: DevicePointer<u8>,
                    mix: DevicePointer<u8>,
                    wom: DevicePointer<DeviceExtElem>,
                    accum: DevicePointer<u8>,
                    steps: u32,
                    count: u32,
                ) -> CppError;
            }

            unsafe {
                risc0_circuit_recursion_cuda_step_verify_accum(
                    ctrl.as_device_ptr(),
                    data.as_device_ptr(),
                    mix.as_device_ptr(),
                    wom.as_device_ptr(),
                    accum.as_device_ptr(),
                    steps as u32,
                    count as u32,
                )
                .unwrap();
            }
        });

        tracing::info_span!("zeroize").in_scope(|| {
            self.hal.eltwise_zeroize_elem(accum);
            self.hal.eltwise_zeroize_elem(io);
        });
    }
}

pub type CudaCircuitHalSha256 = CudaCircuitHal<CudaHashSha256>;
pub type CudaCircuitHalPoseidon = CudaCircuitHal<CudaHashPoseidon>;
pub type CudaCircuitHalPoseidon2 = CudaCircuitHal<CudaHashPoseidon2>;

#[cfg(test)]
mod tests {
    use std::rc::Rc;

    use risc0_core::field::baby_bear::BabyBear;
    use risc0_zkp::{
        core::hash::sha::Sha256HashSuite,
        hal::{cpu::CpuHal, cuda::CudaHalSha256},
    };
    use test_log::test;

    use crate::{cpu::CpuCircuitHal, CircuitImpl};

    #[test]
    fn eval_check() {
        const PO2: usize = 4;
        let circuit = CircuitImpl::new();
        let cpu_hal: CpuHal<BabyBear> = CpuHal::new(Sha256HashSuite::new_suite());
        let cpu_eval = CpuCircuitHal::new(&circuit);
        let gpu_hal = Rc::new(CudaHalSha256::new());
        let gpu_eval = super::CudaCircuitHalSha256::new(gpu_hal.clone());
        crate::testutil::eval_check(&cpu_hal, cpu_eval, gpu_hal.as_ref(), gpu_eval, PO2);
    }
}
