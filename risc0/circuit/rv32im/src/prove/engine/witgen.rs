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
    prove::{
        emu::preflight::PreflightTrace,
        engine::loader::Loader,
        hal::{CircuitWitnessGenerator, StepMode},
    },
    CIRCUIT,
};

pub(crate) struct WitnessGenerator<H>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
{
    pub steps: usize,
    pub ctrl: H::Buffer<H::Elem>,
    pub data: H::Buffer<H::Elem>,
    pub io: H::Buffer<H::Elem>,
}

impl<H> WitnessGenerator<H>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
{
    pub fn new<C: CircuitWitnessGenerator<H>>(
        hal: &H,
        circuit_hal: &C,
        po2: usize,
        io: &[BabyBearElem],
        trace: PreflightTrace,
        mode: StepMode,
    ) -> Self {
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
        if mode != StepMode::SeqForward {
            nvtx::range_push!("inject_exec_backs");
            for cycle in 0..last_cycle {
                machine.inject_exec_backs(steps, cycle, &mut data);
            }
            nvtx::range_pop!();
        }

        if mode == StepMode::Parallel {
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

        circuit_hal.generate_witness(
            mode,
            &machine.raw_trace,
            steps,
            last_cycle,
            &ctrl,
            &io,
            &data,
        );

        // Zero out 'invalid' entries in data and output.
        nvtx::range_push!("zeroize");
        hal.eltwise_zeroize_elem(&data);
        hal.eltwise_zeroize_elem(&io);
        nvtx::range_pop!();

        Self {
            steps,
            ctrl,
            data,
            io,
        }
    }
}
