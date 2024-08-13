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
use risc0_core::scope;
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

        let (loader, last_cycle) = scope!("load", {
            let mut loader = Loader::new(steps, CIRCUIT.ctrl_size());
            let last_cycle = loader.load();
            (loader, last_cycle)
        });
        tracing::debug!("last_cycle: {last_cycle}");

        let data = scope!(
            "alloc(data)",
            hal.alloc_elem_init("data", steps * CIRCUIT.data_size(), BabyBearElem::INVALID)
        );

        let machine = MachineContext::new(trace);
        if mode != StepMode::SeqForward {
            scope!("inject_exec_backs", {
                let mut offsets = vec![];
                let mut values = vec![];
                let mut index = Vec::with_capacity(last_cycle + 1);
                for cycle in 0..last_cycle {
                    index.push(offsets.len() as u32);
                    machine.inject_exec_backs(steps, cycle, &mut offsets, &mut values);
                }
                index.push(offsets.len() as u32);
                hal.scatter(&data, &index, &offsets, &values);
            });
        }

        if mode == StepMode::Parallel {
            scope!("noise(data)", {
                let mut rng = thread_rng();
                let noise = vec![BabyBearElem::random(&mut rng); ZK_CYCLES * CIRCUIT.data_size()];
                hal.eltwise_copy_elem_slice(
                    &data,
                    &noise,
                    CIRCUIT.data_size(), // from_rows
                    ZK_CYCLES,           // from_cols
                    0,                   // from_offset
                    ZK_CYCLES,           // from_stride
                    steps - ZK_CYCLES,   // into_offset
                    steps,               // into_stride
                );
            });
        }

        let ctrl = scope!("copy(ctrl)", hal.copy_from_elem("ctrl", &loader.ctrl));
        let io = scope!("copy(io)", hal.copy_from_elem("io", io));

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
        scope!("zeroize", {
            hal.eltwise_zeroize_elem(&data);
            hal.eltwise_zeroize_elem(&io);
        });

        Self {
            steps,
            ctrl,
            data,
            io,
        }
    }
}
