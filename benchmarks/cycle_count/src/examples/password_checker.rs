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

use password_checker_core::PasswordRequest;
use rand::prelude::*;
use risc0_zkvm::{serde::to_vec, ExecutorEnv, MemoryImage};

use crate::{exec_compute, get_image, CycleCounter};

pub struct Job<'a> {
    pub env: ExecutorEnv<'a>,
    pub image: MemoryImage,
}

const METHOD_PATH: &'static str = password_checker_methods::PW_CHECKER_PATH;

impl CycleCounter for Job<'_> {
    const NAME: &'static str = "password-checker";

    fn new() -> Self {
        let image = get_image(METHOD_PATH);
        let mut rng = StdRng::from_entropy();
        let mut salt = [0u8; 32];
        rng.fill_bytes(&mut salt);
        let request = PasswordRequest {
            password: "S00perSecr1t!!!".into(),
            salt,
        };
        let env = ExecutorEnv::builder()
            .add_input(&to_vec(&request).unwrap())
            .build()
            .unwrap();

        Job { env, image }
    }

    fn exec_compute(&mut self) -> u32 {
        exec_compute(self.image.clone(), self.env.clone())
    }
}
