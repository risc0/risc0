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

use risc0_zkvm::ExecutorEnv;

use crate::{exec, CycleCounter, Metrics};

pub struct Job {}

impl CycleCounter for Job {
    const NAME: &'static str = "bevy";
    const METHOD_ELF: &'static [u8] = bevy_methods::BEVY_GUEST_ELF;

    fn run() -> Metrics {
        let input: u32 = 3;
        let env = ExecutorEnv::builder()
            .write(&input)
            .unwrap()
            .build()
            .unwrap();

        exec(Self::NAME, Self::METHOD_ELF, env)
    }
}
