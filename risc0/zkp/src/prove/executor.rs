// Copyright 2022 Risc0, Inc.
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
    taps::RegisterGroup,
    MIN_PO2, ZK_CYCLES,
};

pub struct Executor<F, C, S>
where
    F: Field,
    C: 'static + CircuitDef<F>,
    S: CircuitStepHandler<F::Elem>,
{
    pub circuit: &'static C,
    pub handler: S,
    pub code: Vec<F::Elem>,
    code_size: usize,
    pub data: Vec<F::Elem>,
    data_size: usize,
    pub output: Vec<F::Elem>,
    pub po2: usize,
    pub steps: usize,
    pub halted: bool,
    max_po2: usize,
    pub cycle: usize,
}

impl<F, C, S> Executor<F, C, S>
where
    F: Field,
    C: 'static + CircuitDef<F>,
    S: CircuitStepHandler<F::Elem>,
{
    pub fn new(circuit: &'static C, handler: S, min_po2: usize, max_po2: usize) -> Self {
        let po2 = max(min_po2, MIN_PO2);
        let taps = circuit.get_taps();
        let code_size = taps.group_size(RegisterGroup::Code);
        let data_size = taps.group_size(RegisterGroup::Data);
        let steps = 1 << po2;
        let output_size = C::OUTPUT_SIZE;
        debug!("po2: {po2}, steps: {steps}, code_size: {code_size}");
        Executor {
            circuit,
            handler,
            // Initialize trace to min_po2 size
            code: vec![F::Elem::ZERO; steps * code_size],
            code_size,
            data: vec![F::Elem::INVALID; steps * data_size],
            data_size,
            output: vec![F::Elem::INVALID; output_size],
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
            &mut self.output,
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
            &mut self.output,
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
        for value in [self.data.iter_mut(), self.output.iter_mut()]
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

    pub fn get_output(&self, idx: usize) -> F::Elem {
        self.output[idx]
    }
}
