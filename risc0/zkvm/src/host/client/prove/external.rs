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

use std::path::{Path, PathBuf};

use anyhow::{ensure, Result};

use super::{Executor, Prover, ProverOpts};
use crate::{
    compute_image_id, host::api::AssetRequest, sha::Digestible, ApiClient, Asset, ExecutorEnv,
    ProveInfo, SessionInfo, VerifierContext,
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
    fn prove_with_ctx(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        elf: &[u8],
        opts: &ProverOpts,
    ) -> Result<ProveInfo> {
        tracing::debug!("Launching {}", &self.r0vm_path.to_string_lossy());

        let image_id = compute_image_id(elf)?;
        let client = ApiClient::new_sub_process(&self.r0vm_path)?;
        let binary = Asset::Inline(elf.to_vec().into());
        let prove_info = client.prove(&env, opts.clone(), binary)?;
        //let receipt = prove_info.receipt;
        if opts.prove_guest_errors {
            prove_info.receipt.verify_integrity_with_context(ctx)?;
            ensure!(
                prove_info.receipt.get_claim()?.pre.digest() == image_id,
                "received unexpected image ID: expected {}, found {}",
                hex::encode(image_id),
                hex::encode(prove_info.receipt.get_claim()?.pre.digest())
            );
        } else {
            prove_info.receipt.verify_with_context(ctx, image_id)?;
        }

        Ok(prove_info)
    }

    fn get_name(&self) -> String {
        self.name.clone()
    }
}

impl Executor for ExternalProver {
    fn execute(&self, env: ExecutorEnv<'_>, elf: &[u8]) -> Result<SessionInfo> {
        let binary = Asset::Inline(elf.to_vec().into());
        let client = ApiClient::new_sub_process(&self.r0vm_path)?;
        let segments_out = AssetRequest::Inline;
        client.execute(&env, binary, segments_out, |_, _| Ok(()))
    }
}
