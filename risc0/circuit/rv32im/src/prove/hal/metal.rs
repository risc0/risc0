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

use std::{collections::HashMap, ffi::c_void, rc::Rc};

use anyhow::{bail, Result};
use metal::{ComputePipelineDescriptor, MTLResourceOptions, MTLResourceUsage};
use risc0_circuit_rv32im_sys::ffi::RawPreflightTrace;
use risc0_core::field::{
    baby_bear::{BabyBearElem, BabyBearExtElem},
    map_pow, RootsOfUnity,
};
use risc0_sys::CppError;
use risc0_zkp::{
    core::log2_ceil,
    field::Elem as _,
    hal::{
        metal::{
            BufferImpl as MetalBuffer, KernelArg, MetalHal, MetalHalPoseidon2, MetalHalSha256,
            MetalHash,
        },
        Buffer as _, CircuitHal,
    },
    INV_RATE, ZK_CYCLES,
};

const METAL_LIB: &[u8] = include_bytes!(env!("RV32IM_METAL_PATH"));

const KERNEL_NAMES: &[&str] = &["eval_check", "k_step_compute_accum", "k_step_verify_accum"];

use crate::{
    prove::{engine::SegmentProverImpl, SegmentProver},
    GLOBAL_MIX, GLOBAL_OUT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL, REGISTER_GROUP_DATA,
};

use super::{CircuitWitnessGenerator, StepMode};

#[derive(Debug)]
pub struct MetalCircuitHal<MH: MetalHash> {
    hal: Rc<MetalHal<MH>>,
    kernels: HashMap<String, ComputePipelineDescriptor>,
}

impl<MH: MetalHash> MetalCircuitHal<MH> {
    pub fn new(hal: Rc<MetalHal<MH>>) -> Self {
        let library = hal.device.new_library_with_data(METAL_LIB).unwrap();
        let mut kernels = HashMap::new();
        for name in KERNEL_NAMES {
            let function = library.get_function(name, None).unwrap();
            let pipeline = ComputePipelineDescriptor::new();
            pipeline.set_compute_function(Some(&function));
            kernels.insert(name.to_string(), pipeline);
        }
        Self { hal, kernels }
    }
}

impl<MH: MetalHash> CircuitWitnessGenerator<MetalHal<MH>> for MetalCircuitHal<MH> {
    #[allow(unused)]
    fn generate_witness(
        &self,
        mode: StepMode,
        trace: &RawPreflightTrace,
        steps: usize,
        count: usize,
        ctrl: &MetalBuffer<BabyBearElem>,
        io: &MetalBuffer<BabyBearElem>,
        data: &MetalBuffer<BabyBearElem>,
    ) {
        tracing::debug!("witgen: {steps}, {count}");

        // TODO: call metal kernels for witgen.
        // For now we use the CPU implementation.

        extern "C" {
            fn risc0_circuit_rv32im_cpu_witgen(
                mode: u32,
                trace: *const RawPreflightTrace,
                steps: u32,
                count: u32,
                ctrl: *const BabyBearElem,
                io: *const BabyBearElem,
                data: *const BabyBearElem,
            ) -> CppError;
        }

        unsafe {
            risc0_circuit_rv32im_cpu_witgen(
                mode as u32,
                trace,
                steps as u32,
                count as u32,
                ctrl.as_ptr() as *const BabyBearElem,
                io.as_ptr() as *const BabyBearElem,
                data.as_ptr() as *const BabyBearElem,
            )
            .unwrap();
        }
    }
}

#[repr(C)]
struct AccumContext {
    ram: *const c_void,
    bytes: *const c_void,
}

impl<MH: MetalHash> CircuitHal<MetalHal<MH>> for MetalCircuitHal<MH> {
    #[tracing::instrument(skip_all)]
    fn eval_check(
        &self,
        check: &MetalBuffer<BabyBearElem>,
        groups: &[&MetalBuffer<BabyBearElem>],
        globals: &[&MetalBuffer<BabyBearElem>],
        poly_mix: BabyBearExtElem,
        po2: usize,
        steps: usize,
    ) {
        const EXP_PO2: usize = log2_ceil(INV_RATE);
        let domain = steps * INV_RATE;
        let rou = BabyBearElem::ROU_FWD[po2 + EXP_PO2];
        let rou =
            MetalBuffer::copy_from("rou", &self.hal.device, self.hal.cmd_queue.clone(), &[rou]);
        let poly_mix_pows = map_pow(poly_mix, crate::info::POLY_MIX_POWERS);
        let poly_mix_pows = MetalBuffer::copy_from(
            "poly_mix",
            &self.hal.device,
            self.hal.cmd_queue.clone(),
            poly_mix_pows.as_slice(),
        );
        let po2 = MetalBuffer::copy_from(
            "po2",
            &self.hal.device,
            self.hal.cmd_queue.clone(),
            &[po2 as u32],
        );
        let size = MetalBuffer::copy_from(
            "size",
            &self.hal.device,
            self.hal.cmd_queue.clone(),
            &[domain as u32],
        );
        let args = [
            check.as_arg(),
            groups[REGISTER_GROUP_CTRL].as_arg(),
            groups[REGISTER_GROUP_DATA].as_arg(),
            groups[REGISTER_GROUP_ACCUM].as_arg(),
            globals[GLOBAL_MIX].as_arg(),
            globals[GLOBAL_OUT].as_arg(),
            poly_mix_pows.as_arg(),
            rou.as_arg(),
            po2.as_arg(),
            size.as_arg(),
        ];
        let kernel = self.kernels.get("eval_check").unwrap();
        self.hal.dispatch(kernel, &args, domain as u64, None);
    }

    #[tracing::instrument(skip_all)]
    fn accumulate(
        &self,
        ctrl: &MetalBuffer<BabyBearElem>,
        io: &MetalBuffer<BabyBearElem>,
        data: &MetalBuffer<BabyBearElem>,
        mix: &MetalBuffer<BabyBearElem>,
        accum: &MetalBuffer<BabyBearElem>,
        steps: usize,
    ) {
        let count = steps - ZK_CYCLES;

        let ram = vec![BabyBearExtElem::ONE; steps];
        let ram = MetalBuffer::copy_from("ram", &self.hal.device, self.hal.cmd_queue.clone(), &ram);

        let bytes = vec![BabyBearExtElem::ONE; steps];
        let bytes = MetalBuffer::copy_from(
            "bytes",
            &self.hal.device,
            self.hal.cmd_queue.clone(),
            &bytes,
        );

        let ctx = AccumContext {
            ram: ram.as_device_ptr(),
            bytes: bytes.as_device_ptr(),
        };
        let ctx_buffer = self.hal.device.new_buffer_with_data(
            &ctx as *const AccumContext as *const c_void,
            std::mem::size_of_val(&ctx) as u64,
            MTLResourceOptions::StorageModeManaged,
        );
        let args = [
            KernelArg::Buffer {
                buffer: &ctx_buffer,
                offset: 0,
            },
            KernelArg::Integer(steps as u32),
            ctrl.as_arg(),
            io.as_arg(),
            data.as_arg(),
            mix.as_arg(),
            accum.as_arg(),
        ];

        tracing::info_span!("step_compute_accum").in_scope(|| {
            let kernel = self.kernels.get("k_step_compute_accum").unwrap();

            self.hal
                .dispatch_with_resources(kernel, &args, count as u64, None, |cmd_encoder| {
                    cmd_encoder.use_resource(&ram.as_buf(), MTLResourceUsage::Write);
                    cmd_encoder.use_resource(&bytes.as_buf(), MTLResourceUsage::Write);
                });
        });

        tracing::info_span!("prefix_products").in_scope(|| {
            use risc0_zkp::hal::Hal as _;
            self.hal.prefix_products(&ram);
            self.hal.prefix_products(&bytes);
        });

        tracing::info_span!("step_verify_accum").in_scope(|| {
            let kernel = self.kernels.get("k_step_verify_accum").unwrap();
            self.hal
                .dispatch_with_resources(kernel, &args, count as u64, None, |cmd_encoder| {
                    cmd_encoder.use_resource(&ram.as_buf(), MTLResourceUsage::Read);
                    cmd_encoder.use_resource(&bytes.as_buf(), MTLResourceUsage::Read);
                });
        });

        tracing::info_span!("zeroize").in_scope(|| {
            self.hal
                .dispatch_by_name("eltwise_zeroize_fp", &[accum.as_arg()], accum.size() as u64);

            self.hal
                .dispatch_by_name("eltwise_zeroize_fp", &[io.as_arg()], io.size() as u64);
        });
    }
}

pub fn segment_prover(hashfn: &str) -> Result<Box<dyn SegmentProver>> {
    match hashfn {
        "sha-256" => {
            let hal = Rc::new(MetalHalSha256::new());
            let circuit_hal = Rc::new(MetalCircuitHal::new(hal.clone()));
            Ok(Box::new(SegmentProverImpl::new(hal, circuit_hal)))
        }
        "poseidon2" => {
            let hal = Rc::new(MetalHalPoseidon2::new());
            let circuit_hal = Rc::new(MetalCircuitHal::new(hal.clone()));
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
        hal::{cpu::CpuHal, metal::MetalHalSha256},
    };
    use test_log::test;

    use crate::prove::hal::cpu::CpuCircuitHal;

    // TODO: figure out a better way to test this.
    #[test]
    #[ignore]
    fn eval_check() {
        // The number of cycles, choose a number that doesn't make tests take too long.
        const PO2: usize = 4;
        let cpu_hal = CpuHal::new(Sha256HashSuite::<BabyBear>::new_suite());
        let cpu_eval = CpuCircuitHal::new();
        let gpu_hal = Rc::new(MetalHalSha256::new());
        let gpu_eval = super::MetalCircuitHal::new(gpu_hal.clone());
        crate::prove::hal::testutil::eval_check(
            &cpu_hal,
            cpu_eval,
            gpu_hal.as_ref(),
            gpu_eval,
            PO2,
        );
    }

    #[test]
    #[ignore]
    fn memory_usage() {
        crate::prove::hal::testutil::EvalCheckParams::new(22);
    }
}
