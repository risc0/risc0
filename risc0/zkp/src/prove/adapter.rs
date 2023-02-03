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

use std::sync::{
    atomic::{AtomicPtr, Ordering},
    Mutex,
};

use rand::thread_rng;
use rayon::prelude::*;
use risc0_core::field::{Elem, Field};

use crate::{
    adapter::{CircuitDef, CircuitStepContext, CircuitStepHandler, REGISTER_GROUP_ACCUM},
    core::sha::Sha256,
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
    C: 'static + CircuitDef<F>,
    S: CircuitStepHandler<F::Elem>,
{
    exec: &'a mut Executor<F, C, S>,
    mix: Vec<F::Elem>,
    accum: Vec<F::Elem>,
    steps: usize,
}

impl<'a, F, C, CS> ProveAdapter<'a, F, C, CS>
where
    F: Field,
    C: CircuitDef<F>,
    CS: CircuitStepHandler<F::Elem>,
{
    pub fn new(exec: &'a mut Executor<F, C, CS>) -> Self {
        let steps = exec.steps;
        ProveAdapter {
            exec,
            mix: Vec::new(),
            accum: Vec::new(),
            steps,
        }
    }

    pub fn get_taps(&self) -> &'static TapSet<'static> {
        self.exec.circuit.get_taps()
    }

    /// Perform initial 'execution' setting code + data.
    /// Additionally, write any 'results' as needed.
    pub fn execute<S: Sha256>(&mut self, iop: &mut WriteIOP<S>) {
        iop.write_field_elem_slice(&self.exec.io);
        iop.write_u32_slice(&[self.exec.po2 as u32]);
    }

    /// Perform 'accumulate' stage, using the iop for any RNG state.
    #[tracing::instrument(skip_all)]
    pub fn accumulate<S: Sha256>(&mut self, iop: &mut WriteIOP<S>) {
        // Make the mixing values
        self.mix
            .resize_with(C::MIX_SIZE, || F::Elem::random(&mut iop.rng));
        // Make and compute accum data
        let accum_size = self
            .exec
            .circuit
            .get_taps()
            .group_size(REGISTER_GROUP_ACCUM);
        self.accum.resize(self.steps * accum_size, F::Elem::INVALID);
        let mut args: &mut [&mut [F::Elem]] = &mut [
            &mut self.exec.code,
            &mut self.exec.io,
            &mut self.exec.data,
            &mut self.mix,
            &mut self.accum,
        ];
        let accum: Mutex<Accum<F::ExtElem>> = Mutex::new(Accum::new(self.steps));
        tracing::info_span!("step_compute_accum").in_scope(|| {
            // TODO: Add an abstraction layer for this so we can run
            // it on cuda, etc.
            // TODO: Figure out a safer way to pass args to this parallelization.
            let args_ptr: AtomicPtr<&mut [&mut [F::Elem]]> = AtomicPtr::new(&mut args);
            let c = &self.exec.circuit;
            (0..self.steps - ZK_CYCLES).into_par_iter().for_each_init(
                || Handler::<F>::new(&accum),
                |accum_handler, cycle| {
                    let args: &mut [&mut [F::Elem]] =
                        unsafe { &mut *args_ptr.load(Ordering::Relaxed) };
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
            let args_ptr: AtomicPtr<&mut [&mut [F::Elem]]> = AtomicPtr::new(&mut args);
            let c = &self.exec.circuit;
            (0..self.steps - ZK_CYCLES).into_par_iter().for_each_init(
                || Handler::<F>::new(&accum),
                |accum_handler, cycle| {
                    let args = unsafe { &mut *args_ptr.load(Ordering::Relaxed) };
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
        // Zero out 'invalid' entries in accum
        for value in self.accum.iter_mut().chain(self.exec.io.iter_mut()) {
            *value = value.valid_or_zero();
        }
        // Add random noise to end of accum and change invalid element to zero
        let mut rng = thread_rng();
        for i in self.steps - ZK_CYCLES..self.steps {
            for j in 0..accum_size {
                self.accum[j * self.steps + i] = F::Elem::random(&mut rng);
            }
        }
    }

    pub fn po2(&self) -> u32 {
        self.exec.po2 as u32
    }

    pub fn get_code(&self) -> &[F::Elem] {
        &self.exec.code
    }

    pub fn get_data(&self) -> &[F::Elem] {
        &self.exec.data
    }

    pub fn get_accum(&self) -> &[F::Elem] {
        &self.accum
    }

    pub fn get_mix(&self) -> &[F::Elem] {
        &self.mix
    }

    pub fn get_io(&self) -> &[F::Elem] {
        &self.exec.io
    }

    pub fn get_steps(&self) -> usize {
        self.steps
    }
}
