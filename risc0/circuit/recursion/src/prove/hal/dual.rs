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
use risc0_circuit_recursion_sys::{RawPreflightTrace, StepMode};
use risc0_zkp::{
    field::baby_bear::{BabyBearElem, BabyBearExtElem},
    hal::{
        AccumPreflight, CircuitHal,
        cuda::{BufferImpl as CudaBuffer, CudaHal, CudaHalPoseidon2, CudaHalPoseidon254, CudaHash},
    },
};

use crate::prove::{RecursionProver, RecursionProverImpl};

use super::{
    CircuitAccumulator, CircuitWitnessGenerator,
    cpu::CpuHal,
    cuda::{CudaCircuitHal, CudaCircuitHalPoseidon2, CudaCircuitHalPoseidon254},
};

type RealDualHal<HashT> =
    risc0_zkp::hal::dual::DualHal<risc0_zkp::field::baby_bear::BabyBear, CudaHal<HashT>, CpuHal>;
type RealDualHalBuffer<T> =
    risc0_zkp::hal::dual::BufferImpl<T, CudaBuffer<T>, risc0_zkp::hal::cpu::CpuBuffer<T>>;

struct DualHal<HashT: CudaHash> {
    cuda_rhal: Rc<CudaCircuitHal<HashT>>,
    cpu_rhal: Rc<super::cpu::CpuCircuitHal>,
    _dual_hal: Rc<RealDualHal<HashT>>,
}

impl<HashT: CudaHash> CircuitWitnessGenerator<RealDualHal<HashT>> for DualHal<HashT>
where
    CudaCircuitHal<HashT>: CircuitWitnessGenerator<CudaHal<HashT>>,
{
    fn generate_witness(
        &self,
        mode: StepMode,
        total_cycles: u32,
        preflight: &RawPreflightTrace,
        ctrl: &RealDualHalBuffer<BabyBearElem>,
        data: &RealDualHalBuffer<BabyBearElem>,
        global: &RealDualHalBuffer<BabyBearElem>,
    ) -> Result<()> {
        self.cuda_rhal.generate_witness(
            mode,
            total_cycles,
            preflight,
            &ctrl.lhs,
            &data.lhs,
            &global.lhs,
        )?;
        self.cpu_rhal.generate_witness(
            mode,
            total_cycles,
            preflight,
            &ctrl.rhs,
            &data.rhs,
            &global.rhs,
        )?;
        ctrl.assert_eq();
        data.assert_eq();
        global.assert_eq();
        Ok(())
    }
}

impl<HashT: CudaHash> CircuitHal<RealDualHal<HashT>> for DualHal<HashT>
where
    CudaCircuitHal<HashT>: CircuitHal<CudaHal<HashT>>,
{
    fn eval_check(
        &self,
        check: &RealDualHalBuffer<BabyBearElem>,
        groups: &[&RealDualHalBuffer<BabyBearElem>],
        globals: &[&RealDualHalBuffer<BabyBearElem>],
        poly_mix: BabyBearExtElem,
        po2: usize,
        steps: usize,
    ) {
        self.cuda_rhal.eval_check(
            &check.lhs,
            &groups.iter().map(|g| &g.lhs).collect::<Vec<_>>()[..],
            &globals.iter().map(|g| &g.lhs).collect::<Vec<_>>()[..],
            poly_mix,
            po2,
            steps,
        );
        self.cpu_rhal.eval_check(
            &check.rhs,
            &groups.iter().map(|g| &g.rhs).collect::<Vec<_>>()[..],
            &globals.iter().map(|g| &g.rhs).collect::<Vec<_>>()[..],
            poly_mix,
            po2,
            steps,
        );
        check.assert_eq();
        for g in groups {
            g.assert_eq();
        }
        for g in globals {
            g.assert_eq();
        }
    }

    #[allow(unused)]
    fn accumulate(
        &self,
        _preflight: &AccumPreflight,
        ctrl: &RealDualHalBuffer<BabyBearElem>,
        io: &RealDualHalBuffer<BabyBearElem>,
        data: &RealDualHalBuffer<BabyBearElem>,
        mix: &RealDualHalBuffer<BabyBearElem>,
        accum: &RealDualHalBuffer<BabyBearElem>,
        steps: usize,
    ) {
        unimplemented!()
    }
}

impl<HashT: CudaHash> CircuitAccumulator<RealDualHal<HashT>> for DualHal<HashT>
where
    CudaCircuitHal<HashT>: CircuitAccumulator<CudaHal<HashT>>,
{
    fn accumulate(
        &self,
        work_cycles: u32,
        total_cycles: u32,
        ctrl: &RealDualHalBuffer<BabyBearElem>,
        global: &RealDualHalBuffer<BabyBearElem>,
        data: &RealDualHalBuffer<BabyBearElem>,
        mix: &RealDualHalBuffer<BabyBearElem>,
        accum: &RealDualHalBuffer<BabyBearElem>,
    ) -> Result<()> {
        CircuitAccumulator::accumulate(
            &*self.cuda_rhal,
            work_cycles,
            total_cycles,
            &ctrl.lhs,
            &global.lhs,
            &data.lhs,
            &mix.lhs,
            &accum.lhs,
        )?;
        CircuitAccumulator::accumulate(
            &*self.cpu_rhal,
            work_cycles,
            total_cycles,
            &ctrl.rhs,
            &global.rhs,
            &data.rhs,
            &mix.rhs,
            &accum.rhs,
        )?;
        ctrl.assert_eq();
        global.assert_eq();
        data.assert_eq();
        mix.assert_eq();
        accum.assert_eq();
        Ok(())
    }
}

#[cfg_attr(not(feature = "dual"), expect(dead_code))]
pub(crate) fn recursion_prover(hashfn: &str) -> Result<Box<dyn RecursionProver>> {
    match hashfn {
        "poseidon2" => {
            let cuda_hal = Rc::new(CudaHalPoseidon2::new());
            let cuda_rhal = Rc::new(CudaCircuitHalPoseidon2::new(cuda_hal.clone()));

            let cpu_hal = Rc::new(CpuHal::new(
                risc0_zkp::core::hash::poseidon2::Poseidon2HashSuite::new_suite(),
            ));
            let cpu_rhal = Rc::new(super::cpu::CpuCircuitHal);

            let dual_hal = Rc::new(RealDualHal::new(cuda_hal, cpu_hal));
            let circuit_hal = Rc::new(DualHal {
                cuda_rhal,
                cpu_rhal,
                _dual_hal: dual_hal.clone(),
            });
            Ok(Box::new(RecursionProverImpl::new(dual_hal, circuit_hal)))
        }
        "poseidon_254" => {
            let cuda_hal = Rc::new(CudaHalPoseidon254::new());
            let cuda_rhal = Rc::new(CudaCircuitHalPoseidon254::new(cuda_hal.clone()));

            let cpu_hal = Rc::new(CpuHal::new(
                risc0_zkp::core::hash::poseidon_254::Poseidon254HashSuite::new_suite(),
            ));
            let cpu_rhal = Rc::new(super::cpu::CpuCircuitHal);

            let dual_hal = Rc::new(RealDualHal::new(cuda_hal, cpu_hal));
            let circuit_hal = Rc::new(DualHal {
                cuda_rhal,
                cpu_rhal,
                _dual_hal: dual_hal.clone(),
            });
            Ok(Box::new(RecursionProverImpl::new(dual_hal, circuit_hal)))
        }
        _ => bail!("Unsupported hashfn: {hashfn}"),
    }
}
