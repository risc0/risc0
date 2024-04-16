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

use std::sync::Mutex;

use anyhow::Result;
use rand::thread_rng;
use rayon::prelude::*;
use risc0_zkp::{
    adapter::{CircuitInfo as _, CircuitStep as _, CircuitStepContext, TapsProvider},
    field::{
        baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem},
        Elem as _,
    },
    hal::cpu::CpuBuffer,
    prove::{
        accum::{Accum, Handler},
        write_iop::WriteIOP,
    },
    ZK_CYCLES,
};

use super::machine::MachineContext;
use crate::{
    prove::{emu::preflight::PreflightTrace, engine::loader::Loader},
    CircuitImpl, CIRCUIT,
};

pub struct WitnessGenerator {
    steps: usize,
    pub ctrl: CpuBuffer<BabyBearElem>,
    pub data: CpuBuffer<BabyBearElem>,
    pub io: CpuBuffer<BabyBearElem>,
}

impl WitnessGenerator {
    pub fn new(po2: usize, io: &[BabyBearElem]) -> Self {
        let steps = 1 << po2;
        Self {
            steps,
            ctrl: CpuBuffer::from_fn("ctrl", steps * CIRCUIT.ctrl_size(), |_| BabyBearElem::ZERO),
            data: CpuBuffer::from_fn("data", steps * CIRCUIT.data_size(), |_| {
                BabyBearElem::INVALID
            }),
            io: CpuBuffer::from(Vec::from(io)),
        }
    }

    #[tracing::instrument(skip_all)]
    pub fn execute(&mut self, trace: PreflightTrace) -> Result<()> {
        let mut machine = MachineContext::new(self.steps, trace);
        self.compute_execute(&mut machine)?;
        self.compute_verify(&mut machine);

        // Zero out 'invalid' entries in data and output.
        self.data
            .as_slice_mut()
            .par_iter_mut()
            .chain(self.io.as_slice_mut().par_iter_mut())
            .for_each(|value| *value = value.valid_or_zero());

        Ok(())
    }

    #[cfg(test)]
    pub fn test_step_execute(&mut self, trace: PreflightTrace, is_fwd: bool) -> Vec<BabyBearElem> {
        let machine = MachineContext::new(self.steps, trace);
        let mut loader = Loader::new(self.steps, &mut self.ctrl);
        let last_cycle = loader.load();

        if !is_fwd {
            for cycle in 0..last_cycle {
                machine.inject_exec_backs(self.steps, cycle, &self.data.as_slice_sync());
            }
        }

        {
            let args = &[
                self.ctrl.as_slice_sync(),
                self.io.as_slice_sync(),
                self.data.as_slice_sync(),
            ];

            if is_fwd {
                for cycle in 0..last_cycle {
                    machine.step_exec(self.steps, cycle, args).unwrap();
                }
            } else {
                machine.rev_step_exec(self.steps, last_cycle, args);
            }
        }

        self.data
            .as_slice_mut()
            .par_iter_mut()
            .chain(self.io.as_slice_mut().par_iter_mut())
            .for_each(|value| *value = value.valid_or_zero());

        self.data.as_slice().to_vec()
    }

    #[tracing::instrument(skip_all)]
    fn compute_execute(&mut self, machine: &mut MachineContext) -> Result<()> {
        tracing::debug!("load");
        let mut loader = Loader::new(self.steps, &mut self.ctrl);
        let last_cycle = loader.load();

        #[cfg(not(feature = "seq"))]
        tracing::info_span!("inject_exec_backs").in_scope(|| {
            tracing::debug!("inject_exec_backs");
            for cycle in 0..last_cycle {
                machine.inject_exec_backs(self.steps, cycle, &self.data.as_slice_sync());
            }
        });

        tracing::info_span!("step_exec").in_scope(|| {
            tracing::debug!("step_exec");
            let args = &[
                self.ctrl.as_slice_sync(),
                self.io.as_slice_sync(),
                self.data.as_slice_sync(),
            ];

            #[cfg(not(feature = "seq"))]
            machine.par_step_exec(self.steps, last_cycle, args);

            #[cfg(feature = "seq")]
            for cycle in 0..last_cycle {
                machine.step_exec(self.steps, cycle, args).unwrap();
            }
        });

        Ok(())
    }

    #[tracing::instrument(skip_all)]
    fn compute_verify(&mut self, machine: &mut MachineContext) {
        tracing::debug!("compute_verify");
        let mut rng = thread_rng();
        {
            let ctrl = self.ctrl.as_slice_sync();
            let data = self.data.as_slice_sync();

            for i in 0..ZK_CYCLES {
                let cycle = self.steps - ZK_CYCLES + i;
                // Set ctrl to all zeros for the ZK_CYCLES
                for j in 0..CIRCUIT.ctrl_size() {
                    ctrl.set(j * self.steps + cycle, BabyBearElem::ZERO);
                }
                // Set data to random for the ZK_CYCLES
                for j in 0..CIRCUIT.data_size() {
                    data.set(j * self.steps + cycle, BabyBearElem::random(&mut rng));
                }
            }
        }

        // Do the verify cycles
        let last_cycle = self.steps - ZK_CYCLES;

        machine.sort("ram");

        #[cfg(not(feature = "seq"))]
        tracing::info_span!("inject_verify_mem_backs").in_scope(|| {
            tracing::debug!("inject_verify_mem_backs");
            for cycle in 0..last_cycle {
                machine.inject_verify_mem_backs(self.steps, cycle, self.data.as_slice_sync());
            }
        });

        tracing::info_span!("step_verify_mem").in_scope(|| {
            tracing::debug!("step_verify_mem");
            let args = &[
                self.ctrl.as_slice_sync(),
                self.io.as_slice_sync(),
                self.data.as_slice_sync(),
            ];

            #[cfg(not(feature = "seq"))]
            machine.par_step_verify_mem(self.steps, last_cycle, args);

            #[cfg(feature = "seq")]
            for cycle in 0..last_cycle {
                machine.step_verify_mem(self.steps, cycle, args).unwrap();
            }
        });

        machine.sort("bytes");
        tracing::info_span!("step_verify_bytes").in_scope(|| {
            tracing::debug!("step_verify_bytes");
            let args = &[
                self.ctrl.as_slice_sync(),
                self.io.as_slice_sync(),
                self.data.as_slice_sync(),
            ];
            for cycle in 0..last_cycle {
                machine.step_verify_bytes(self.steps, cycle, args).unwrap();
            }
        });
    }

    #[tracing::instrument(skip_all)]
    pub fn accumulate(
        &mut self,
        iop: &mut WriteIOP<BabyBear>,
    ) -> (CpuBuffer<BabyBearElem>, CpuBuffer<BabyBearElem>) {
        tracing::debug!("accumulate");

        // Make the mixing values
        let mix = CpuBuffer::from_fn("mix", CircuitImpl::MIX_SIZE, |_| iop.random_elem());

        // Make and compute accum data
        let accum_size = CIRCUIT.accum_size();
        let accum = CpuBuffer::from_fn("accum", self.steps * accum_size, |_| BabyBearElem::INVALID);
        self.compute_accum(&mix, &accum);

        {
            // Zero out 'invalid' entries in accum and io
            let mut accum_slice = accum.as_slice_mut();
            let mut io = self.io.as_slice_mut();
            for value in accum_slice.iter_mut().chain(io.iter_mut()) {
                *value = value.valid_or_zero();
            }

            // Add random noise to end of accum and change invalid element to zero
            let mut rng = thread_rng();
            for i in self.steps - ZK_CYCLES..self.steps {
                for j in 0..accum_size {
                    accum_slice[j * self.steps + i] = BabyBearElem::random(&mut rng);
                }
            }
        }

        (mix, accum)
    }

    #[tracing::instrument(skip_all)]
    fn compute_accum(&mut self, mix: &CpuBuffer<BabyBearElem>, accum: &CpuBuffer<BabyBearElem>) {
        let args = &[
            self.ctrl.as_slice_sync(),
            self.io.as_slice_sync(),
            self.data.as_slice_sync(),
            mix.as_slice_sync(),
            accum.as_slice_sync(),
        ];
        let accum: Mutex<Accum<BabyBearExtElem>> = Mutex::new(Accum::new(self.steps));
        tracing::info_span!("step_compute_accum").in_scope(|| {
            // TODO: Add a way to be able to run this on cuda, metal, etc.
            (0..self.steps - ZK_CYCLES).into_par_iter().for_each_init(
                || Handler::<BabyBear>::new(&accum),
                |handler, cycle| {
                    CIRCUIT
                        .step_compute_accum(
                            &CircuitStepContext {
                                size: self.steps,
                                cycle,
                            },
                            handler,
                            args,
                        )
                        .unwrap();
                },
            );
        });
        tracing::info_span!("calc_prefix_products").in_scope(|| {
            accum.lock().unwrap().calc_prefix_products();
        });
        tracing::info_span!("step_verify_accum").in_scope(|| {
            (0..self.steps - ZK_CYCLES).into_par_iter().for_each_init(
                || Handler::<BabyBear>::new(&accum),
                |handler, cycle| {
                    CIRCUIT
                        .step_verify_accum(
                            &CircuitStepContext {
                                size: self.steps,
                                cycle,
                            },
                            handler,
                            args,
                        )
                        .unwrap();
                },
            );
        });
    }
}
