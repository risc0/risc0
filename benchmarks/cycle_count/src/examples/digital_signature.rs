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

use digital_signature_core::{Message, Passphrase, SigningRequest};
use risc0_zkvm::{serde::to_vec, ExecutorEnv};
use sha2::{Digest, Sha256};

use crate::{exec_compute, CycleCounter};

pub struct Job<'a> {
    pub env: ExecutorEnv<'a>,
}

const METHOD_ELF: &'static [u8] = digital_signature_methods::SIGN_ELF;

impl CycleCounter for Job<'_> {
    const NAME: &'static str = "digital-signature";

    fn new() -> Self {
        let params = SigningRequest {
            passphrase: Passphrase {
                pass: Sha256::digest("passphrase").try_into().unwrap(),
            },
            msg: Message {
                msg: Sha256::digest("message").try_into().unwrap(),
            },
        };
        let env = ExecutorEnv::builder()
            .add_input(&to_vec(&params).unwrap())
            .build()
            .unwrap();

        Job { env }
    }

    fn exec_compute(&mut self) -> u32 {
        exec_compute(METHOD_ELF, self.env.clone())
    }
}
