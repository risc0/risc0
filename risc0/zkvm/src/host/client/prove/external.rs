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

use std::path::{Path, PathBuf};

use anyhow::Result;
use risc0_binfmt::MemoryImage;

use super::{Executor, Prover, ProverOpts};
use crate::{
    host::api::AssetRequest, ApiClient, ExecutorEnv, Receipt, SessionInfo, VerifierContext,
};

/// An implementation of a [Prover] that runs proof workloads via an external
/// `r0vm` process.
pub struct ExternalProver {
    name: String,
    r0vm_path: PathBuf,
}

impl ExternalProver {
    /// Construct an [ExternalProver].
    pub fn new<P: AsRef<Path>>(name: &str, r0vm_path: P) -> Self {
        Self {
            name: name.to_string(),
            r0vm_path: r0vm_path.as_ref().to_path_buf(),
        }
    }
}

impl Prover for ExternalProver {
    fn prove(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        opts: &ProverOpts,
        image: MemoryImage,
    ) -> Result<Receipt> {
        log::debug!("Launching {}", &self.r0vm_path.to_string_lossy());

        let image_id = image.compute_id();
        let client = ApiClient::new_sub_process(&self.r0vm_path)?;
        let receipt = client.prove(&env, opts.clone(), image.into())?;
        receipt.verify_with_context(ctx, image_id)?;

        Ok(receipt)
    }

    fn get_name(&self) -> String {
        self.name.clone()
    }
}

impl Executor for ExternalProver {
    fn execute(&self, env: ExecutorEnv<'_>, image: MemoryImage) -> Result<SessionInfo> {
        let client = ApiClient::new_sub_process(&self.r0vm_path)?;
        let segments_out = AssetRequest::Inline;
        client.execute(&env, image.into(), segments_out, |_, _| Ok(()))
    }
}
