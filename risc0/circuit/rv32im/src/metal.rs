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
        metal::{BufferImpl as MetalBuffer, MetalHal, MetalHash},
        CircuitHal,
    },
    INV_RATE,
};

const METAL_LIB: &[u8] = include_bytes!(env!("RV32IM_METAL_PATH"));

use crate::{
    GLOBAL_MIX, GLOBAL_OUT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE, REGISTER_GROUP_DATA,
};

#[derive(Debug)]
pub struct MetalCircuitHal<MH: MetalHash> {
    hal: Rc<MetalHal<MH>>,
    kernel: ComputePipelineDescriptor,
}

impl<MH: MetalHash> MetalCircuitHal<MH> {
    pub fn new(hal: Rc<MetalHal<MH>>) -> Self {
        let library = hal.device.new_library_with_data(METAL_LIB).unwrap();
        let function = library.get_function("eval_check", None).unwrap();
        let kernel = ComputePipelineDescriptor::new();
        kernel.set_compute_function(Some(&function));
        Self { hal, kernel }
    }
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
            groups[REGISTER_GROUP_CODE].as_arg(),
            groups[REGISTER_GROUP_DATA].as_arg(),
            groups[REGISTER_GROUP_ACCUM].as_arg(),
            globals[GLOBAL_MIX].as_arg(),
            globals[GLOBAL_OUT].as_arg(),
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

    use risc0_core::field::baby_bear::BabyBear;
    use risc0_zkp::{
        core::hash::sha::Sha256HashSuite,
        hal::{cpu::CpuHal, metal::MetalHalSha256},
    };
    use test_log::test;

    use crate::cpu::CpuCircuitHal;

    // TODO: figure out a better way to test this.
    #[test]
    #[ignore]
    fn eval_check() {
        // The number of cycles, choose a number that doesn't make tests take too long.
        const PO2: usize = 4;
        let circuit = crate::CircuitImpl::new();
        let cpu_hal = CpuHal::new(Sha256HashSuite::<BabyBear>::new_suite());
        let cpu_eval = CpuCircuitHal::new(&circuit);
        let gpu_hal = Rc::new(MetalHalSha256::new());
        let gpu_eval = super::MetalCircuitHal::new(gpu_hal.clone());
        crate::testutil::eval_check(&cpu_hal, cpu_eval, gpu_hal.as_ref(), gpu_eval, PO2);
    }

    #[test]
    #[ignore]
    fn memory_usage() {
        crate::testutil::EvalCheckParams::new(22);
    }
}
