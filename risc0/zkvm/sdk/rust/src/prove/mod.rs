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

pub mod exec;

use anyhow::Result;
use risc0_zkp::{
    core::sha::default_implementation, hal::cpu::CpuHal, prove::adapter::ProveAdapter,
};

use crate::{elf::Program, platform::memory::MEM_SIZE, receipt::Receipt};

use self::exec::{IoHandler, RV32Executor};

pub struct Prover {
    elf: Program,
    inner: ProverImpl,
}

impl Prover {
    pub fn new(elf: &[u8]) -> Result<Self> {
        Ok(Prover {
            elf: Program::load_elf(&elf, MEM_SIZE as u32)?,
            inner: ProverImpl::new(),
        })
    }

    pub fn add_input(&mut self, slice: &[u32]) {
        self.inner.inputs.extend_from_slice(slice);
    }

    pub fn get_output(&self) -> &[u32] {
        &self.inner.outputs
    }

    pub fn run(mut self) -> Result<Receipt> {
        let mut executor = RV32Executor::new(&self.elf, &mut self.inner);
        executor.run()?;

        let mut prover = ProveAdapter::new(&mut executor.executor);
        let hal = CpuHal {};
        let sha = default_implementation();
        let seal = risc0_zkp::prove::prove(&hal, sha, &mut prover);

        // Attach the full version of the output journal & construct receipt object
        let receipt = Receipt {
            journal: self.inner.commit,
            seal,
        };

        // Verify receipt to make sure it works
        // receipt.verify(&self.method_id)?;

        Ok(receipt)
    }
}

struct ProverImpl {
    pub inputs: Vec<u32>,
    pub outputs: Vec<u32>,
    pub commit: Vec<u32>,
}

impl ProverImpl {
    fn new() -> Self {
        Self {
            inputs: Vec::new(),
            outputs: Vec::new(),
            commit: Vec::new(),
        }
    }
}

impl IoHandler for ProverImpl {
    fn on_txrx(&mut self, _channel: u32, _buf: &[u8]) -> Vec<u8> {
        todo!()
    }
}
