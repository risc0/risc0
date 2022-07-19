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

use anyhow::Result;
use risc0_circuit_rv32im_legacy::CircuitImpl;
use risc0_zkp::{
    core::sha::default_implementation,
    hal::cpu::CpuHal,
    prove::{adapter::ProveAdapter, executor::Executor},
    MAX_CYCLES_PO2, MIN_PO2,
};

use crate::{elf::Program, method_id::MethodId, platform::memory::MEM_SIZE, receipt::Receipt};

use self::exec::MachineState;

#[cfg(feature = "circuit")]
pub mod exec;

pub struct Prover {
    elf: Program,
    method_id: MethodId,
    inputs: Vec<u32>,
    outputs: Vec<u32>,
    commit: Vec<u32>,
}

impl Prover {
    pub fn new(elf: &[u8], method_id: &MethodId) -> Result<Self> {
        let elf = Program::load_elf(&elf, MEM_SIZE as u32)?;
        Ok(Prover {
            elf,
            method_id: method_id.clone(),
            inputs: Vec::new(),
            outputs: Vec::new(),
            commit: Vec::new(),
        })
    }

    pub fn add_input(&mut self, slice: &[u32]) {
        self.inputs.extend_from_slice(slice);
    }

    pub fn get_output(&self) -> &[u32] {
        &self.outputs
    }

    pub fn run(self) -> Result<Receipt> {
        // Set the memory handlers to call back to the impl
        // MemoryHandler handler(impl.get());
        // Make the circuit
        let circuit = CircuitImpl::new();
        let machine = MachineState::new();
        let mut executor = Executor::new(circuit, machine, MIN_PO2, MAX_CYCLES_PO2);
        // executor.step(code);

        let mut prover = ProveAdapter::new(&mut executor);
        let hal = CpuHal {};
        let sha = default_implementation();
        let seal = risc0_zkp::prove::prove(&hal, sha, &mut prover);

        // Attach the full version of the output journal & construct receipt object
        let receipt = Receipt {
            journal: self.commit,
            seal,
        };

        // Verify receipt to make sure it works
        receipt.verify(&self.method_id)?;

        Ok(receipt)
    }
}
