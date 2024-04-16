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

use anyhow::{anyhow, bail, ensure, Result};

use super::{Executor, Prover, ProverOpts};
use crate::{
    compute_image_id, host::api::AssetRequest, sha::Digestible, ApiClient, Asset, CompositeReceipt,
    ExecutorEnv, InnerReceipt, Receipt, SegmentReceipt, SessionInfo, SuccinctReceipt,
    VerifierContext,
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

    /// Internal implementation of the compress function.
    fn compress_internal(
        client: &ApiClient,
        opts: &ProverOpts,
        receipt: &CompositeReceipt,
    ) -> Result<SuccinctReceipt> {
        // Compress all receipts in the top-level session into one succinct receipt for the session.
        let continuation_receipt = receipt
            .segments
            .iter()
            .try_fold(
                None,
                |left: Option<SuccinctReceipt>, right: &SegmentReceipt| -> Result<_> {
                    Ok(Some(match left {
                        Some(left) => client.join(opts, &left, &client.lift(opts, right)?)?,
                        None => client.lift(opts, right)?,
                    }))
                },
            )?
            .ok_or(anyhow!(
                "malformed composite receipt has no continuation segment receipts"
            ))?;

        // Compress assumptions and resolve them to get the final succinct receipt.
        receipt.assumptions.iter().try_fold(
            continuation_receipt,
            |conditional: SuccinctReceipt, assumption: &InnerReceipt| match assumption {
                InnerReceipt::Succinct(assumption) => client.resolve(opts, &conditional, assumption),
                InnerReceipt::Composite(assumption) => {
                    client.resolve(opts, &conditional, &Self::compress_internal(client, opts, assumption)?)
                }
                InnerReceipt::Fake { .. } => bail!(
                    "compressing composite receipts with fake receipt assumptions is not supported"
                ),
                InnerReceipt::Compact(_) => bail!(
                    "compressing composite receipts with Compact receipt assumptions is not supported"
                ),
            },
        )
    }
}

impl Prover for ExternalProver {
    fn prove_with_ctx(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        elf: &[u8],
        opts: &ProverOpts,
    ) -> Result<Receipt> {
        tracing::debug!("Launching {}", &self.r0vm_path.to_string_lossy());

        let image_id = compute_image_id(elf)?;
        let client = ApiClient::new_sub_process(&self.r0vm_path)?;
        let binary = Asset::Inline(elf.to_vec().into());
        let receipt = client.prove(&env, opts.clone(), binary)?;
        if opts.prove_guest_errors {
            receipt.verify_integrity_with_context(ctx)?;
            ensure!(
                receipt.get_claim()?.pre.digest() == image_id,
                "received unexpected image ID: expected {}, found {}",
                hex::encode(image_id),
                hex::encode(receipt.get_claim()?.pre.digest())
            );
        } else {
            receipt.verify_with_context(ctx, image_id)?;
        }

        Ok(receipt)
    }

    fn get_name(&self) -> String {
        self.name.clone()
    }

    fn compress(&self, opts: &ProverOpts, receipt: &Receipt) -> Result<Receipt> {
        match receipt.inner {
            InnerReceipt::Succinct(_) | InnerReceipt::Compact(_) => Ok(receipt.clone()),
            InnerReceipt::Composite(ref composite) => {
                let client = ApiClient::new_sub_process(&self.r0vm_path)?;
                Ok(Receipt {
                    inner: InnerReceipt::Succinct(Self::compress_internal(
                        &client, opts, composite,
                    )?),
                    journal: receipt.journal.clone(),
                })
            }
            InnerReceipt::Fake { .. } => {
                bail!("ExternalProver cannot compress a fake receipt")
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
