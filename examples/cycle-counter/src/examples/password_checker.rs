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

use password_checker_core::PasswordRequest;
use rand::prelude::*;
use risc0_zkvm::ExecutorEnv;

use crate::{exec, CycleCounter, Metrics};

pub struct Job {}

impl CycleCounter for Job {
    const NAME: &'static str = "password-checker";
    const METHOD_ELF: &'static [u8] = password_checker_methods::PW_CHECKER_ELF;

    fn run() -> Metrics {
        let mut rng = StdRng::from_entropy();
        let mut salt = [0u8; 32];
        rng.fill_bytes(&mut salt);
        let request = PasswordRequest {
            password: "S00perSecr1t!!!".into(),
            salt,
        };
        let env = ExecutorEnv::builder()
            .write(&request)
            .unwrap()
            .build()
            .unwrap();

        exec(Self::NAME, Self::METHOD_ELF, env)
    }
}
