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

use crate::{exec_compute, get_image, CycleCounter};
use risc0_zkvm::{serde::to_vec, ExecutorEnv, MemoryImage};

pub struct Job<'a> {
    pub env: ExecutorEnv<'a>,
    pub image: MemoryImage,
}

const METHOD_PATH: &'static str = sha_methods::HASH_PATH;

impl CycleCounter for Job<'_> {
    const NAME: &'static str = "sha";

    fn new() -> Self {
        let image = get_image(METHOD_PATH);
        let env = ExecutorEnv::builder()
            .add_input(&to_vec("").unwrap())
            .build()
            .unwrap();

        Job { env, image }
    }

    fn exec_compute(&mut self) -> u32 {
        exec_compute(self.image.clone(), self.env.clone())
    }
}
