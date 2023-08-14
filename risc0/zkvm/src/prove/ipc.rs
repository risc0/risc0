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

use std::process::Command;

use anyhow::Result;
use risc0_binfmt::MemoryImage;

use super::Prover;
use crate::{ExecutorEnv, Receipt, Segment, SegmentReceipt, Session, VerifierContext};

pub struct IpcProver {
    name: String,
}

impl IpcProver {
    pub fn new(name: &str) -> Self {
        Self {
            name: name.to_string(),
        }
    }
}

impl Prover for IpcProver {
    fn prove_elf(&self, env: ExecutorEnv<'_>, elf: &[u8]) -> Result<Receipt> {
        // self.prove_elf_with_ctx(env, &VerifierContext::default(), elf)
        todo!()
    }

    fn prove(
        &self,
        _env: ExecutorEnv<'_>,
        _ctx: &VerifierContext,
        _image: MemoryImage,
    ) -> Result<Receipt> {
        // let cmd = Command::new("r0vm");
        todo!()
    }

    fn prove_session(&self, _ctx: &VerifierContext, _session: &Session) -> Result<Receipt> {
        todo!()
    }

    fn prove_segment(&self, _ctx: &VerifierContext, _segment: &Segment) -> Result<SegmentReceipt> {
        todo!()
    }

    fn get_peak_memory_usage(&self) -> usize {
        todo!()
    }

    fn get_name(&self) -> String {
        self.name.clone()
    }
}
