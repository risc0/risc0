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

use std::{collections::HashMap, rc::Rc};

use metal::ComputePipelineDescriptor;
use risc0_core::scope;
use risc0_zkp::{
    INV_RATE, ZK_CYCLES,
    core::log2_ceil,
    field::{
        Elem as _, RootsOfUnity,
        baby_bear::{BabyBearElem, BabyBearExtElem},
        map_pow,
    },
    hal::{
        AccumPreflight, Buffer as _, CircuitHal,
        metal::{BufferImpl as MetalBuffer, KernelArg, MetalHal, MetalHash},
    },
};

const METAL_LIB: &[u8] = include_bytes!(env!("RECURSION_METAL_PATH"));

const KERNEL_NAMES: &[&str] = &["eval_check", "step_compute_accum", "step_verify_accum"];

use crate::{
    GLOBAL_MIX, GLOBAL_OUT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CTRL, REGISTER_GROUP_DATA,
};

#[derive(Debug)]
pub struct MetalCircuitHal<MH: MetalHash> {
    hal: Rc<MetalHal<MH>>,
    kernels: HashMap<String, ComputePipelineDescriptor>,
}

impl<MH: MetalHash> MetalCircuitHal<MH> {
    pub fn new(hal: Rc<MetalHal<MH>>) -> Self {
        #[cfg(test)]
        gpu_guard::assert_gpu_semaphore_held();

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

impl<MH: MetalHash> CircuitHal<MetalHal<MH>> for MetalCircuitHal<MH> {
    fn eval_check(
        &self,
        check: &MetalBuffer<BabyBearElem>,
        groups: &[&MetalBuffer<BabyBearElem>],
        globals: &[&MetalBuffer<BabyBearElem>],
        poly_mix: BabyBearExtElem,
        po2: usize,
        steps: usize,
    ) {
        scope!("eval_check");

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

    fn accumulate(
        &self,
        _preflight: &AccumPreflight,
        ctrl: &MetalBuffer<BabyBearElem>,
        io: &MetalBuffer<BabyBearElem>,
        data: &MetalBuffer<BabyBearElem>,
        mix: &MetalBuffer<BabyBearElem>,
        accum: &MetalBuffer<BabyBearElem>,
        steps: usize,
    ) {
        let count = steps - ZK_CYCLES;

        let wom = vec![BabyBearExtElem::ONE; steps];
        let wom = MetalBuffer::copy_from("wom", &self.hal.device, self.hal.cmd_queue.clone(), &wom);

        let args = [
            KernelArg::Integer(steps as u32),
            ctrl.as_arg(),
            data.as_arg(),
            mix.as_arg(),
            wom.as_arg(),
        ];
        let kernel = self.kernels.get("step_compute_accum").unwrap();
        self.hal.dispatch(kernel, &args, count as u64, None);

        use risc0_zkp::hal::Hal as _;
        self.hal.prefix_products(&wom);

        let args = [
            KernelArg::Integer(steps as u32),
            ctrl.as_arg(),
            data.as_arg(),
            mix.as_arg(),
            wom.as_arg(),
            accum.as_arg(),
        ];
        let kernel = self.kernels.get("step_verify_accum").unwrap();
        self.hal.dispatch(kernel, &args, count as u64, None);

        self.hal
            .dispatch_by_name("eltwise_zeroize_fp", &[accum.as_arg()], accum.size() as u64);

        self.hal
            .dispatch_by_name("eltwise_zeroize_fp", &[io.as_arg()], io.size() as u64);
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

    use crate::{CircuitImpl, cpu::CpuCircuitHal};

    // TODO: figure out a better way to test this.
    #[test]
    #[gpu_guard::gpu_guard]
    #[ignore]
    fn eval_check() {
        // The number of cycles, choose a number that doesn't make tests take too long.
        const PO2: usize = 4;
        let circuit = CircuitImpl::new();
        let cpu_hal: CpuHal<BabyBear> = CpuHal::new(Sha256HashSuite::new_suite());
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
