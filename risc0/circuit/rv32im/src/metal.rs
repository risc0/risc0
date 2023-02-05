// Copyright 2023 RISC Zero, Inc.
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

use metal::ComputePipelineDescriptor;
use risc0_core::field::{
    baby_bear::{BabyBearElem, BabyBearExtElem},
    RootsOfUnity,
};
use risc0_zkp::{
    core::log2_ceil,
    hal::{
        metal::{BufferImpl as MetalBuffer, MetalHal},
        EvalCheck,
    },
    INV_RATE,
};

const METAL_LIB: &[u8] = include_bytes!(env!("RV32IM_METAL_PATH"));

#[derive(Debug)]
pub struct MetalEvalCheck {
    hal: Rc<MetalHal>,
    kernel: ComputePipelineDescriptor,
}

impl MetalEvalCheck {
    pub fn new(hal: Rc<MetalHal>) -> Self {
        let library = hal.device.new_library_with_data(METAL_LIB).unwrap();
        let function = library.get_function("eval_check", None).unwrap();
        let kernel = ComputePipelineDescriptor::new();
        kernel.set_compute_function(Some(&function));
        Self { hal, kernel }
    }
}

impl EvalCheck<MetalHal> for MetalEvalCheck {
    #[tracing::instrument(skip_all)]
    fn eval_check(
        &self,
        check: &MetalBuffer<BabyBearElem>,
        code: &MetalBuffer<BabyBearElem>,
        data: &MetalBuffer<BabyBearElem>,
        accum: &MetalBuffer<BabyBearElem>,
        mix: &MetalBuffer<BabyBearElem>,
        out: &MetalBuffer<BabyBearElem>,
        poly_mix: BabyBearExtElem,
        po2: usize,
        steps: usize,
    ) {
        const EXP_PO2: usize = log2_ceil(INV_RATE);
        let domain = steps * INV_RATE;
        let poly_mix =
            MetalBuffer::copy_from(&self.hal.device, self.hal.cmd_queue.clone(), &[poly_mix]);
        let rou = BabyBearElem::ROU_FWD[po2 + EXP_PO2];
        let rou = MetalBuffer::copy_from(&self.hal.device, self.hal.cmd_queue.clone(), &[rou]);
        let po2 =
            MetalBuffer::copy_from(&self.hal.device, self.hal.cmd_queue.clone(), &[po2 as u32]);
        let size = MetalBuffer::copy_from(
            &self.hal.device,
            self.hal.cmd_queue.clone(),
            &[domain as u32],
        );
        let buffers = &[
            check.as_arg(),
            code.as_arg(),
            data.as_arg(),
            accum.as_arg(),
            mix.as_arg(),
            out.as_arg(),
            poly_mix.as_arg(),
            rou.as_arg(),
            po2.as_arg(),
            size.as_arg(),
        ];
        self.hal
            .dispatch(&self.kernel, buffers, domain as u64, None);
    }
}

#[cfg(test)]
mod tests {
    use std::rc::Rc;

    use risc0_zkp::hal::{cpu::BabyBearSha256CpuHal, metal::MetalHal};
    use test_log::test;

    use crate::cpu::CpuEvalCheck;

    // TODO: figure out a better way to test this.
    #[test]
    #[ignore]
    fn eval_check() {
        // The number of cycles, choose a number that doesn't make tests take too long.
        const PO2: usize = 4;
        let circuit = crate::CircuitImpl::new();
        let cpu_hal = BabyBearSha256CpuHal::new();
        let cpu_eval = CpuEvalCheck::new(&circuit);
        let gpu_hal = Rc::new(MetalHal::new());
        let gpu_eval = super::MetalEvalCheck::new(gpu_hal.clone());
        crate::testutil::eval_check(&cpu_hal, cpu_eval, gpu_hal.as_ref(), gpu_eval, PO2);
    }

    #[test]
    #[ignore]
    fn memory_usage() {
        crate::testutil::EvalCheckParams::new(22);
    }
}
