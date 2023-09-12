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

use std::sync::Mutex;

use rand::thread_rng;
use rayon::prelude::*;
use risc0_core::field::{Elem, Field};

use crate::{
    adapter::{CircuitProveDef, CircuitStepContext, CircuitStepHandler, REGISTER_GROUP_ACCUM},
    hal::cpu::CpuBuffer,
    prove::{
        accum::{Accum, Handler},
        executor::Executor,
        write_iop::WriteIOP,
    },
    taps::TapSet,
    ZK_CYCLES,
};

pub struct ProveAdapter<'a, F, C, S>
where
    F: Field,
    C: 'static + CircuitProveDef<F>,
    S: CircuitStepHandler<F::Elem>,
{
    exec: &'a mut Executor<F, C, S>,
    mix: CpuBuffer<F::Elem>,
    accum: CpuBuffer<F::Elem>,
    steps: usize,
}

impl<'a, F, C, CS> ProveAdapter<'a, F, C, CS>
where
    F: Field,
    C: 'static + CircuitProveDef<F>,
    CS: CircuitStepHandler<F::Elem>,
{
    pub fn new(exec: &'a mut Executor<F, C, CS>) -> Self {
        let steps = exec.steps;
        ProveAdapter {
            exec,
            mix: CpuBuffer::from(Vec::new()),
            accum: CpuBuffer::from(Vec::new()),
            steps,
        }
    }

    pub fn get_taps(&self) -> &'static TapSet<'static> {
        self.exec.circuit.get_taps()
    }

    /// Perform initial 'execution' setting code + data.
    /// Additionally, write any 'results' as needed.
    pub fn execute(&mut self, iop: &mut WriteIOP<F>) {
        iop.write_field_elem_slice(&self.exec.io.as_slice());
        iop.write_u32_slice(&[self.exec.po2 as u32]);
    }

    fn compute_accum(&mut self) {
        let args = &[
            self.exec.code.as_slice_sync(),
            self.exec.io.as_slice_sync(),
            self.exec.data.as_slice_sync(),
            self.mix.as_slice_sync(),
            self.accum.as_slice_sync(),
        ];
        let accum: Mutex<Accum<F::ExtElem>> = Mutex::new(Accum::new(self.steps));
        tracing::info_span!("step_compute_accum").in_scope(|| {
            // TODO: Add an way to be able to run this on cuda, metal, etc.
            let c = &self.exec.circuit;
            (0..self.steps - ZK_CYCLES).into_par_iter().for_each_init(
                || Handler::<F>::new(&accum),
                |accum_handler, cycle| {
                    c.step_compute_accum(
                        &CircuitStepContext {
                            size: self.steps,
                            cycle,
                        },
                        accum_handler,
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
            let c = &self.exec.circuit;
            (0..self.steps - ZK_CYCLES).into_par_iter().for_each_init(
                || Handler::<F>::new(&accum),
                |accum_handler, cycle| {
                    c.step_verify_accum(
                        &CircuitStepContext {
                            size: self.steps,
                            cycle,
                        },
                        accum_handler,
                        args,
                    )
                    .unwrap();
                },
            );
        });
    }

    /// Perform 'accumulate' stage, using the iop for any RNG state.
    #[tracing::instrument(skip_all)]
    pub fn accumulate(&mut self, iop: &mut WriteIOP<F>) {
        // Make the mixing values
        self.mix = CpuBuffer::from_fn(C::MIX_SIZE, |_| iop.random_elem());
        // Make and compute accum data
        let accum_size = self
            .exec
            .circuit
            .get_taps()
            .group_size(REGISTER_GROUP_ACCUM);
        self.accum = CpuBuffer::from_fn(self.steps * accum_size, |_| F::Elem::INVALID);

        self.compute_accum();

        // Zero out 'invalid' entries in accum and io
        let mut accum = self.accum.as_slice_mut();
        let mut io = self.exec.io.as_slice_mut();
        for value in accum.iter_mut().chain(io.iter_mut()) {
            *value = value.valid_or_zero();
        }
        // Add random noise to end of accum and change invalid element to zero
        let mut rng = thread_rng();
        for i in self.steps - ZK_CYCLES..self.steps {
            for j in 0..accum_size {
                accum[j * self.steps + i] = F::Elem::random(&mut rng);
            }
        }
    }

    pub fn po2(&self) -> u32 {
        self.exec.po2 as u32
    }

    pub fn get_code(&self) -> &CpuBuffer<F::Elem> {
        &self.exec.code
    }

    pub fn get_data(&self) -> &CpuBuffer<F::Elem> {
        &self.exec.data
    }

    pub fn get_accum(&self) -> &CpuBuffer<F::Elem> {
        &self.accum
    }

    pub fn get_mix(&self) -> &CpuBuffer<F::Elem> {
        &self.mix
    }

    pub fn get_io(&self) -> &CpuBuffer<F::Elem> {
        &self.exec.io
    }

    pub fn get_steps(&self) -> usize {
        self.steps
    }
}
