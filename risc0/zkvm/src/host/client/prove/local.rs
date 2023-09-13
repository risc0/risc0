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

use anyhow::Result;
use risc0_binfmt::MemoryImage;

use super::{Prover, ProverOpts};
use crate::{get_prover_server, ExecutorEnv, Receipt, VerifierContext};

/// A [Prover] implementation that selects a [crate::ProverServer] by calling
/// [get_prover_server].
pub struct LocalProver {
    name: String,
}

impl LocalProver {
    /// Construct a [LocalProver].
    pub fn new(name: &str) -> Self {
        Self {
            name: name.to_string(),
        }
    }
}

impl Prover for LocalProver {
    fn prove(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        opts: &ProverOpts,
        image: MemoryImage,
    ) -> Result<Receipt> {
        get_prover_server(opts)?.prove(env, ctx, image)
    }

    fn get_name(&self) -> String {
        self.name.clone()
    }
}
