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

use risc0_zkvm::ExecutorEnv;

use crate::{exec_compute, CycleCounter};

pub struct Job<'a> {
    pub env: ExecutorEnv<'a>,
}

const METHOD_ELF: &'static [u8] = hello_world_methods::MULTIPLY_ELF;

impl CycleCounter for Job<'_> {
    const NAME: &'static str = "hello-world";

    fn new() -> Self {
        let a: u64 = 17;
        let b: u64 = 23;
        let env = ExecutorEnv::builder()
            .write(&a)
            .unwrap()
            .write(&b)
            .unwrap()
            .build()
            .unwrap();

        Job { env }
    }

    fn exec_compute(&mut self) -> u32 {
        exec_compute(METHOD_ELF, self.env.clone())
    }
}
