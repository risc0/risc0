// Copyright 2025 RISC Zero, Inc.
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
    host::api::AssetRequest, ApiClient, Asset, ExecutorEnv, InnerReceipt, ProveInfo, Receipt,
    ReceiptKind, SessionInfo, VerifierContext,
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

        let client = ApiClient::new_sub_process(&self.r0vm_path)?;
        let binary = Asset::Inline(elf.to_vec().into());
        let prove_info = client.prove(&env, opts, binary)?;
        prove_info.receipt.verify_integrity_with_context(ctx)?;

        Ok(prove_info)
    }

    fn get_name(&self) -> String {
        self.name.clone()
    }

    fn compress(&self, opts: &ProverOpts, receipt: &Receipt) -> Result<Receipt> {
        match (&receipt.inner, opts.receipt_kind) {
            // Compression is a no-op when the requested kind is at least as large as the current.
            (InnerReceipt::Composite(_), ReceiptKind::Composite)
            | (InnerReceipt::Succinct(_), ReceiptKind::Composite | ReceiptKind::Succinct)
            | (
                InnerReceipt::Groth16(_),
                ReceiptKind::Composite | ReceiptKind::Succinct | ReceiptKind::Groth16,
            ) => Ok(receipt.clone()),
            // Compression is always a no-op in dev mode
            (InnerReceipt::Fake { .. }, _) => {
                ensure!(
                    opts.dev_mode(),
                    "dev mode must be enabled to compress fake receipts"
                );
                Ok(receipt.clone())
            }
            (_, _) => {
                let client = ApiClient::new_sub_process(&self.r0vm_path)?;
                client.compress(opts, receipt.clone().try_into()?, AssetRequest::Inline)
            }
        }
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
