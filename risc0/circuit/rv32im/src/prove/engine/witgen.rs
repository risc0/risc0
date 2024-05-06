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

use rand::thread_rng;
use risc0_zkp::{
    adapter::TapsProvider,
    field::{
        baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
        Elem as _,
    },
    hal::Hal,
    ZK_CYCLES,
};

use super::machine::MachineContext;
use crate::{
    prove::{emu::preflight::PreflightTrace, engine::loader::Loader, hal::CircuitWitnessGenerator},
    CIRCUIT,
};

pub(crate) struct WitnessGenerator<H>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
{
    // _hal: Rc<H>,
    pub steps: usize,
    pub ctrl: H::Buffer<H::Elem>,
    pub data: H::Buffer<H::Elem>,
    pub io: H::Buffer<H::Elem>,
    // last_cycle: usize,
}

impl<H> WitnessGenerator<H>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
{
    pub fn new<C>(
        hal: &H,
        circuit_hal: &C,
        po2: usize,
        io: &[BabyBearElem],
        trace: PreflightTrace,
    ) -> Self
    where
        C: CircuitWitnessGenerator<H>,
    {
        let steps = 1 << po2;

        nvtx::range_push!("load");
        let mut loader = Loader::new(steps, CIRCUIT.ctrl_size());
        let last_cycle = loader.load();
        nvtx::range_pop!();
        tracing::debug!("last_cycle: {last_cycle}");

        nvtx::range_push!("alloc(data)");
        let mut data = vec![BabyBearElem::INVALID; steps * CIRCUIT.data_size()];
        nvtx::range_pop!();

        let machine = MachineContext::new(trace);
        nvtx::range_push!("inject_exec_backs");
        for cycle in 0..last_cycle {
            machine.inject_exec_backs(steps, cycle, &mut data);
        }
        nvtx::range_pop!();

        {
            nvtx::range_push!("noise");
            let mut rng = thread_rng();
            for i in 0..ZK_CYCLES {
                let cycle = steps - ZK_CYCLES + i;
                // Set data to random for the ZK_CYCLES
                for j in 0..CIRCUIT.data_size() {
                    data[j * steps + cycle] = BabyBearElem::random(&mut rng);
                }
            }
            nvtx::range_pop!();
        }

        nvtx::range_push!("copy(ctrl)");
        let ctrl = hal.copy_from_elem("ctrl", &loader.ctrl);
        nvtx::range_pop!();

        nvtx::range_push!("copy(data)");
        let data = hal.copy_from_elem("data", &data);
        nvtx::range_pop!();

        nvtx::range_push!("copy(io)");
        let io = hal.copy_from_elem("io", io);
        nvtx::range_pop!();

        // let hal_any = hal as &dyn Any;
        // let witgen = hal_any.downcast_ref::<dyn CircuitWitnessGenerator<H>>();
        circuit_hal.generate_witness(&machine.raw_trace, steps, last_cycle, &ctrl, &io, &data);

        // Zero out 'invalid' entries in data and output.
        nvtx::range_push!("zeroize");
        hal.eltwise_zeroize_elem(&data);
        hal.eltwise_zeroize_elem(&io);
        nvtx::range_pop!();

        Self {
            // _hal: hal,
            steps,
            ctrl,
            data,
            io,
            // last_cycle,
        }
    }

    #[cfg(test)]
    pub fn test_step_execute(
        &mut self,
        _trace: PreflightTrace,
        _is_fwd: bool,
    ) -> Vec<BabyBearElem> {
        // let machine = MachineContext::new(self.steps, trace);

        // if !is_fwd {
        //     for cycle in 0..self.last_cycle {
        //         machine.inject_exec_backs(self.steps, cycle, &self.data.as_slice_sync());
        //     }
        // }

        // {
        //     let args = &[
        //         self.ctrl.as_slice_sync(),
        //         self.io.as_slice_sync(),
        //         self.data.as_slice_sync(),
        //     ];

        //     if is_fwd {
        //         for cycle in 0..self.last_cycle {
        //             machine.step_exec(self.steps, cycle, args).unwrap();
        //         }
        //     } else {
        //         machine
        //             .rev_step_exec(self.steps, self.last_cycle, args)
        //             .unwrap();
        //     }
        // }

        // self.data
        //     .as_slice_mut()
        //     .par_iter_mut()
        //     .chain(self.io.as_slice_mut().par_iter_mut())
        //     .for_each(|value| *value = value.valid_or_zero());

        // self.data.as_slice().to_vec()
        todo!()
    }
}
