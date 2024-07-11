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

use anyhow::{bail, Result};
use cust::{
    memory::{DeviceBox, GpuBuffer as _},
    prelude::*,
    DeviceCopy,
};
use risc0_circuit_rv32im_sys::ffi::RawPreflightTrace;
use risc0_core::field::{
    baby_bear::{BabyBearElem, BabyBearExtElem},
    map_pow, Elem, RootsOfUnity,
};
use risc0_sys::{cuda::SpparkError, CppError};
use risc0_zkp::{
    core::log2_ceil,
    field::ExtElem as _,
    hal::{
        cuda::{
            BufferImpl as CudaBuffer, CudaHal, CudaHalPoseidon2, CudaHalSha256, CudaHash,
            CudaHashPoseidon2, CudaHashSha256, DeviceExtElem,
        },
        Buffer, CircuitHal, Hal,
    },
    INV_RATE, ZK_CYCLES,
};

use crate::{
    info::{NUM_POLY_MIX_POWERS, POLY_MIX_POWERS},
    prove::{engine::SegmentProverImpl, hal::StepMode, SegmentProver},
    GLOBAL_MIX, GLOBAL_OUT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL, REGISTER_GROUP_DATA,
};

use super::CircuitWitnessGenerator;

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

#[derive(Clone, Copy, DeviceCopy)]
#[repr(C)]
struct AccumContext {
    ram: DevicePointer<DeviceExtElem>,
    bytes: DevicePointer<DeviceExtElem>,
}

extern "C" {
    fn risc0_circuit_rv32im_cuda_witgen(
        mode: u32,
        trace: *const RawPreflightTrace,
        steps: u32,
        count: u32,
        ctrl: DevicePointer<u8>,
        io: DevicePointer<u8>,
        data: DevicePointer<u8>,
    ) -> CppError;

    fn risc0_circuit_rv32im_cuda_step_compute_accum(
        ctx: DevicePointer<AccumContext>,
        steps: u32,
        count: u32,
        ctrl: DevicePointer<u8>,
        io: DevicePointer<u8>,
        data: DevicePointer<u8>,
        mix: DevicePointer<u8>,
        accum: DevicePointer<u8>,
    ) -> CppError;

    fn risc0_circuit_rv32im_cuda_step_verify_accum(
        ctx: DevicePointer<AccumContext>,
        steps: u32,
        count: u32,
        ctrl: DevicePointer<u8>,
        io: DevicePointer<u8>,
        data: DevicePointer<u8>,
        mix: DevicePointer<u8>,
        accum: DevicePointer<u8>,
    ) -> CppError;

    fn risc0_circuit_rv32im_cuda_eval_check(
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

impl<CH: CudaHash> CircuitWitnessGenerator<CudaHal<CH>> for CudaCircuitHal<CH> {
    fn generate_witness(
        &self,
        mode: StepMode,
        trace: &RawPreflightTrace,
        steps: usize,
        count: usize,
        ctrl: &CudaBuffer<BabyBearElem>,
        io: &CudaBuffer<BabyBearElem>,
        data: &CudaBuffer<BabyBearElem>,
    ) {
        tracing::debug!("witgen: {steps}, {count}");
        unsafe {
            risc0_circuit_rv32im_cuda_witgen(
                mode as u32,
                trace,
                steps as u32,
                count as u32,
                ctrl.as_device_ptr(),
                io.as_device_ptr(),
                data.as_device_ptr(),
            )
            .unwrap();
        }
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
        nvtx::range_push!("eval_check");

        let ctrl = groups[REGISTER_GROUP_CTRL];
        let data = groups[REGISTER_GROUP_DATA];
        let accum = groups[REGISTER_GROUP_ACCUM];
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
        let rou = BabyBearElem::ROU_FWD[po2 + EXP_PO2];

        let poly_mix_pows = map_pow(poly_mix, POLY_MIX_POWERS);
        let poly_mix_pows: &[u32; BabyBearExtElem::EXT_SIZE * NUM_POLY_MIX_POWERS] =
            BabyBearExtElem::as_u32_slice(poly_mix_pows.as_slice())
                .try_into()
                .unwrap();

        unsafe {
            risc0_circuit_rv32im_cuda_eval_check(
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
        };

        nvtx::range_pop!();
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
        nvtx::range_push!("accumulate");

        let count = steps - ZK_CYCLES;

        let ram = vec![DeviceExtElem(BabyBearExtElem::ONE); steps];
        let ram = DeviceBuffer::from_slice(&ram).unwrap();

        let bytes = vec![DeviceExtElem(BabyBearExtElem::ONE); steps];
        let bytes = DeviceBuffer::from_slice(&bytes).unwrap();

        let ctx = AccumContext {
            ram: ram.as_device_ptr(),
            bytes: bytes.as_device_ptr(),
        };
        let ctx = DeviceBox::new(&ctx).unwrap();

        tracing::info_span!("step_compute_accum").in_scope(|| {
            unsafe {
                risc0_circuit_rv32im_cuda_step_compute_accum(
                    ctx.as_device_ptr(),
                    steps as u32,
                    count as u32,
                    ctrl.as_device_ptr(),
                    io.as_device_ptr(),
                    data.as_device_ptr(),
                    mix.as_device_ptr(),
                    accum.as_device_ptr(),
                )
                .unwrap();
            };
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
                    ram.as_device_ptr(),
                    steps as u32,
                    AccumOpType::Multiply,
                )
            };
            if err.code != 0 {
                panic!("Failure during sppark_calc_prefix_operation(ram): {err}");
            }

            let err = unsafe {
                sppark_calc_prefix_operation(
                    bytes.as_device_ptr(),
                    steps as u32,
                    AccumOpType::Multiply,
                )
            };
            if err.code != 0 {
                panic!("Failure during sppark_calc_prefix_operation(bytes): {err}");
            }
        });

        tracing::info_span!("step_verify_accum").in_scope(|| {
            unsafe {
                risc0_circuit_rv32im_cuda_step_verify_accum(
                    ctx.as_device_ptr(),
                    steps as u32,
                    count as u32,
                    ctrl.as_device_ptr(),
                    io.as_device_ptr(),
                    data.as_device_ptr(),
                    mix.as_device_ptr(),
                    accum.as_device_ptr(),
                )
                .unwrap();
            };
        });

        tracing::info_span!("zeroize").in_scope(|| {
            self.hal.eltwise_zeroize_elem(accum);
            self.hal.eltwise_zeroize_elem(io);
        });

        nvtx::range_pop!();
    }
}

pub type CudaCircuitHalSha256 = CudaCircuitHal<CudaHashSha256>;
pub type CudaCircuitHalPoseidon2 = CudaCircuitHal<CudaHashPoseidon2>;

pub fn segment_prover(hashfn: &str) -> Result<Box<dyn SegmentProver>> {
    match hashfn {
        "sha-256" => {
            let hal = Rc::new(CudaHalSha256::new());
            let circuit_hal = Rc::new(CudaCircuitHalSha256::new(hal.clone()));
            Ok(Box::new(SegmentProverImpl::new(hal, circuit_hal)))
        }
        "poseidon2" => {
            let hal = Rc::new(CudaHalPoseidon2::new());
            let circuit_hal = Rc::new(CudaCircuitHalPoseidon2::new(hal.clone()));
            Ok(Box::new(SegmentProverImpl::new(hal, circuit_hal)))
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
    fn eval_check() {
        const PO2: usize = 4;
        let cpu_hal: CpuHal<BabyBear> = CpuHal::new(Sha256HashSuite::new_suite());
        let cpu_eval = CpuCircuitHal::new();
        let gpu_hal = Rc::new(CudaHalSha256::new());
        let gpu_eval = super::CudaCircuitHal::new(gpu_hal.clone());
        crate::prove::hal::testutil::eval_check(
            &cpu_hal,
            cpu_eval,
            gpu_hal.as_ref(),
            gpu_eval,
            PO2,
        );
    }
}
