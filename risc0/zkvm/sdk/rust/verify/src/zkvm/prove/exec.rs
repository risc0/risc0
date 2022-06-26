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

// TODO: WIP

use alloc::vec::Vec;

use risc0_zkp_core::fp::Fp;

pub struct ExecState {
    start_addr: u32,
    // std::map<uint32_t, uint32_t> image;
    // StepContext context;
    pub code: Vec<Fp>,
    pub data: Vec<Fp>,
    max_steps: usize,
    done: bool,
}

impl ExecState {
    pub fn new(elf: &[u8]) -> Self {
        // startAddr = loadElf(elfFile, kMemSize, image);
        todo!()
    }

    // A helper function to call init, step*, fini
    pub fn run(&self, max_steps: usize) {
        self.init(max_steps); // io
        while self.step() {}
        self.fini();
    }

    // Setup VM and run until 'reset' cycle
    pub fn init(&self, max_steps: usize) {
        todo!()
    }

    // Step a single RISC-V cycle, return false when done
    pub fn step(&self) -> bool {
        todo!()
    }

    // Finalize VM execution in preperation for prover
    pub fn fini(&self) {
        todo!()
    }

    // Get address of instruction about to be executed
    pub fn pc(&self) -> u32 {
        todo!()
    }

    // Get the state of all 32 registers
    pub fn registers(&self) -> Vec<u32> {
        todo!()
    }

    pub fn expand(&self) {
        todo!()
    }
}
