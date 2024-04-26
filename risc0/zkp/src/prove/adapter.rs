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

use risc0_core::field::{Elem, Field};

use crate::{
    adapter::{CircuitProveDef, CircuitStepHandler},
    hal::{cpu::CpuBuffer, Hal},
    prove::{executor::Executor, write_iop::WriteIOP},
    taps::TapSet,
};

pub struct ProveAdapter<'a, F, C, S>
where
    F: Field,
    C: 'static + CircuitProveDef<F>,
    S: CircuitStepHandler<F::Elem>,
{
    exec: &'a mut Executor<F, C, S>,
    mix: CpuBuffer<F::Elem>,
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
            steps,
        }
    }

    pub fn get_taps(&self) -> &'static TapSet<'static> {
        self.exec.circuit.get_taps()
    }

    /// Write the globals and po2 to the IOP, and mix them into the Fiat-Shamir state.
    pub fn execute<H>(&mut self, iop: &mut WriteIOP<F>, hal: &H)
    where
        H: Hal<Field = F, Elem = F::Elem, ExtElem = F::ExtElem>,
    {
        // Concat io (i.e. globals) and po2 into a vector.
        let vec: Vec<F::Elem> = self
            .exec
            .io
            .as_slice()
            .iter()
            .chain(F::Elem::from_u32_slice(&[self.exec.po2 as u32]))
            .copied()
            .collect();

        iop.commit(&hal.get_hash_suite().hashfn.hash_elem_slice(&vec));
        iop.write_field_elem_slice(vec.as_slice());
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
