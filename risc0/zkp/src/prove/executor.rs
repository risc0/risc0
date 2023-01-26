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

use core::cmp::max;

use anyhow::{bail, Result};
use log::debug;
use rand::thread_rng;

use crate::{
    adapter::{CircuitDef, CircuitStepContext, CircuitStepHandler},
    field::{Elem, Field},
    taps::{REGISTER_GROUP_CODE, REGISTER_GROUP_DATA},
    MIN_PO2, ZK_CYCLES,
};

pub struct Executor<F, C, S>
where
    F: Field,
    C: 'static + CircuitDef<F>,
    S: CircuitStepHandler<F::Elem>,
{
    pub circuit: &'static C,
    // Circuit Step Handler
    pub handler: S,
    // Control Instructions
    pub code: Vec<F::Elem>,
    // Number of columns used for control instructions
    code_size: usize,
    // Execution Trace Data
    pub data: Vec<F::Elem>,
    // Number of columns used for execution trace data
    data_size: usize,
    // Circuit inputs/outputs
    pub io: Vec<F::Elem>,
    // Power of 2
    pub po2: usize,
    // steps = 2^po2 is the total number of cycles in the zkVM execution
    pub steps: usize,
    // Indicates whether the guest program has already halted
    pub halted: bool,
    // Maximum allowable execution length of guest program
    max_po2: usize,
    // Counter for zkVM execution
    pub cycle: usize,
}

impl<F, C, S> Executor<F, C, S>
where
    F: Field,
    C: 'static + CircuitDef<F>,
    S: CircuitStepHandler<F::Elem>,
{
    pub fn new(
        circuit: &'static C,
        handler: S,
        min_po2: usize,
        max_po2: usize,
        io: &[F::Elem],
    ) -> Self {
        let po2 = max(min_po2, MIN_PO2);
        let taps = circuit.get_taps();
        let code_size = taps.group_size(REGISTER_GROUP_CODE);
        let data_size = taps.group_size(REGISTER_GROUP_DATA);
        let steps = 1 << po2;
        debug!("po2: {po2}, steps: {steps}, code_size: {code_size}");
        Executor {
            circuit,
            handler,
            // Initialize trace to min_po2 size
            code: vec![F::Elem::ZERO; steps * code_size],
            code_size,
            data: vec![F::Elem::INVALID; steps * data_size],
            data_size,
            io: Vec::from(io),
            po2,
            steps,
            halted: false,
            max_po2,
            cycle: 0,
        }
    }

    pub fn step(&mut self, code: &[F::Elem], needed_fini: usize) -> Result<bool> {
        // debug!("code: {:?}", code);
        let next_cycles = self.cycle + needed_fini + ZK_CYCLES;
        if next_cycles >= self.steps {
            debug!(
                "cycle:{} + needed_fini:{} + ZK_CYCLES:{} = {} >= steps: {}",
                self.cycle, needed_fini, ZK_CYCLES, next_cycles, self.steps
            );
            if self.halted {
                debug!("halted");
                return Ok(false);
            }
            self.expand()?;
        }
        for i in 0..self.code_size {
            self.code[self.steps * i + self.cycle] = code[i];
        }
        let ctx = CircuitStepContext {
            size: self.steps,
            cycle: self.cycle,
        };
        let args: &mut [&mut [F::Elem]] = &mut [
            &mut self.code,
            &mut self.io,
            &mut self.data,
            &mut [],
            &mut [],
        ];
        let result = self.circuit.step_exec(&ctx, &mut self.handler, args)?;
        // debug!("result: {:?}", result);
        self.halted = self.halted || result == F::Elem::ZERO;
        self.cycle += 1;
        Ok(true)
    }

    pub fn expand(&mut self) -> Result<()> {
        debug!("expand");
        if self.steps >= (1 << self.max_po2) {
            bail!("Cannot expand, max po2 of {} reached.", self.max_po2);
        }
        let mut new_code = vec![F::Elem::ZERO; self.code.len() * 2];
        let mut new_data = vec![F::Elem::INVALID; self.data.len() * 2];
        for i in 0..self.code_size {
            let idx = i * self.steps;
            let src = &self.code[idx..idx + self.cycle];
            let tgt = &mut new_code[idx * 2..idx * 2 + self.cycle];
            tgt.copy_from_slice(src);
        }
        for i in 0..self.data_size {
            let idx = i * self.steps;
            let src = &self.data[idx..idx + self.cycle];
            let tgt = &mut new_data[idx * 2..idx * 2 + self.cycle];
            tgt.copy_from_slice(src);
        }
        self.code = new_code;
        self.data = new_data;
        self.po2 += 1;
        self.steps *= 2;
        Ok(())
    }

    #[tracing::instrument(skip_all)]
    pub fn finalize(&mut self) {
        assert!(self.halted);
        assert_eq!(self.cycle, self.steps - ZK_CYCLES);

        let mut rng = thread_rng();
        // Make code be all zeros of zk cycles, and data be random
        for i in self.cycle..self.steps {
            for j in 0..self.code_size {
                self.code[j * self.steps + i] = F::Elem::ZERO;
            }
            for j in 0..self.data_size {
                self.data[j * self.steps + i] = F::Elem::random(&mut rng);
            }
        }
        // Do the verify cycles
        let args: &mut [&mut [F::Elem]] = &mut [
            &mut self.code,
            &mut self.io,
            &mut self.data,
            &mut [],
            &mut [],
        ];

        self.handler.sort("ram");
        tracing::info_span!("step_verify_mem").in_scope(|| {
            for i in 0..self.cycle {
                let ctx = CircuitStepContext {
                    cycle: i,
                    size: self.steps,
                };
                self.circuit
                    .step_verify_mem(&ctx, &mut self.handler, args)
                    .unwrap();
            }
        });

        self.handler.sort("bytes");
        tracing::info_span!("step_verify_bytes").in_scope(|| {
            for i in 0..self.cycle {
                let ctx = CircuitStepContext {
                    cycle: i,
                    size: self.steps,
                };
                self.circuit
                    .step_verify_bytes(&ctx, &mut self.handler, args)
                    .unwrap();
            }
        });

        // Zero out 'invalid' entries in data and output.
        for value in [self.data.iter_mut(), self.io.iter_mut()]
            .into_iter()
            .flatten()
        {
            *value = value.valid_or_zero();
        }
    }

    pub fn get_code(&self, cycle: usize, offset: usize) -> F::Elem {
        self.code[self.steps * offset + cycle]
    }

    pub fn get_data(&self, cycle: usize, offset: usize) -> F::Elem {
        self.data[self.steps * offset + cycle]
    }

    pub fn get_io(&self, idx: usize) -> F::Elem {
        self.io[idx]
    }
}
