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

use std::time::Duration;

use anyhow::{anyhow, bail, ensure, Context, Result};
use bonsai_sdk::alpha::Client;

use super::Prover;
use crate::{
    compute_image_id, is_dev_mode, sha::Digestible, ExecutorEnv, Groth16Receipt, InnerReceipt,
    ProveInfo, ProverOpts, Receipt, ReceiptKind, VerifierContext,
};

/// An implementation of a [Prover] that runs proof workloads via Bonsai.
///
/// Requires `BONSAI_API_URL` and `BONSAI_API_KEY` environment variables to
/// submit proving sessions to Bonsai.
pub struct BonsaiProver {
    name: String,
}

impl BonsaiProver {
    /// Construct a [BonsaiProver].
    pub fn new(name: &str) -> Self {
        Self {
            name: name.to_string(),
        }
    }
}

impl Prover for BonsaiProver {
    fn get_name(&self) -> String {
        self.name.clone()
    }

    fn prove_with_ctx(
        &self,
        env: ExecutorEnv<'_>,
        ctx: &VerifierContext,
        elf: &[u8],
        opts: &ProverOpts,
    ) -> Result<ProveInfo> {
        let client = Client::from_env(crate::VERSION)?;

        // Compute the ImageID and upload the ELF binary
        let image_id = compute_image_id(elf)?;
        let image_id_hex = hex::encode(image_id);
        client.upload_img(&image_id_hex, elf.to_vec())?;

        // upload input data
        let input_id = client.upload_input(env.input)?;

        // upload receipts
        let mut receipts_ids: Vec<String> = vec![];
        for assumption in &env.assumptions.borrow().cached {
            let serialized_receipt = match assumption {
                crate::AssumptionReceipt::Proven(receipt) => bincode::serialize(receipt)?,
                crate::AssumptionReceipt::Unresolved(_) => {
                    bail!("only proven assumptions can be uploaded to Bonsai.")
                }
            };
            let receipt_id = client.upload_receipt(serialized_receipt)?;
            receipts_ids.push(receipt_id);
        }

        // While this is the executor, we want to start a session on the bonsai prover.
        // By doing so, we can return a session ID so that the prover can use it to
        // retrieve the receipt.
        let session = client.create_session(image_id_hex, input_id, receipts_ids)?;
        tracing::debug!("Bonsai proving SessionID: {}", session.uuid);

        let succinct_prove_info = loop {
            // The session has already been started in the executor. Poll bonsai to check if
            // the proof request succeeded.
            let res = session.status(&client)?;
            if res.status == "RUNNING" {
                // TODO(#1759): Improve upon this polling solution.
                std::thread::sleep(Duration::from_secs(5));
                continue;
            }
            if res.status == "SUCCEEDED" {
                // Download the receipt, containing the output
                let receipt_url = res
                    .receipt_url
                    .ok_or(anyhow!("API error, missing receipt on completed session"))?;

                let stats = res
                    .stats
                    .context("Missing stats object on Bonsai status res")?;
                tracing::debug!(
                    "Bonsai usage: cycles: {} total_cycles: {}",
                    stats.cycles,
                    stats.total_cycles
                );

                let receipt_buf = client.download(&receipt_url)?;
                let receipt: Receipt = bincode::deserialize(&receipt_buf)?;

                if opts.prove_guest_errors {
                    receipt.verify_integrity_with_context(ctx)?;
                } else {
                    receipt.verify_with_context(ctx, image_id)?;
                }
                break ProveInfo {
                    receipt,
                    stats: crate::SessionStats {
                        segments: stats.segments,
                        total_cycles: stats.total_cycles,
                        user_cycles: stats.cycles,
                    },
                };
            } else {
                bail!(
                    "Bonsai prover workflow [{}] exited: {} err: {}",
                    session.uuid,
                    res.status,
                    res.error_msg
                        .unwrap_or("Bonsai workflow missing error_msg".into()),
                );
            }
        };
        match opts.receipt_kind {
            // If the caller requested a composite or succinct receipt, we are done.
            ReceiptKind::Composite | ReceiptKind::Succinct => {
                return Ok(succinct_prove_info);
            }
            // If they requested a groth16 receipts, we need to continue.
            ReceiptKind::Groth16 => {}
        }

        // Request that Bonsai compress further, to Groth16.
        let snark_session = client.create_snark(session.uuid)?;
        let snark_receipt = loop {
            let res = snark_session.status(&client)?;
            match res.status.as_str() {
                "RUNNING" => {
                    // TODO(#1759): Improve upon this polling solution.
                    std::thread::sleep(Duration::from_secs(5));
                    continue;
                }
                "SUCCEEDED" => {
                    break res.output.with_context(|| {
                        format!(
                            "Bonsai prover workflow [{}] reported success, but provided no receipt",
                            snark_session.uuid
                        )
                    })?;
                }
                _ => {
                    bail!(
                        "Bonsai prover workflow [{}] exited: {} err: {}",
                        snark_session.uuid,
                        res.status,
                        res.error_msg
                            .unwrap_or("Bonsai workflow missing error_msg".into()),
                    );
                }
            }
        };

        // Assemble the groth16 receipt, and verify it.
        // TODO(bonsai-alpha#461): If the Groth16 parameters used by Bonsai do not match, this
        // verification will fail. When Bonsai returned ReceiptMetadata, we'll be able to detect
        // this error condition and report a better message. Constructing the receipt here will all
        // the verifier parameters for this version of risc0-zkvm, which may be different than
        // Bonsai. By verifying the receipt though, we at least know the proving key used on Bonsai
        // matches the verifying key used here.
        let groth16_receipt = Receipt::new(
            InnerReceipt::Groth16(Groth16Receipt {
                seal: snark_receipt.snark.to_vec(),
                claim: succinct_prove_info.receipt.claim()?,
                verifier_parameters: ctx.groth16_verifier_parameters.digest(),
            }),
            succinct_prove_info.receipt.journal.bytes,
        );
        groth16_receipt
            .verify_integrity_with_context(ctx)
            .context("failed to verify Groth16Receipt returned by Bonsai")?;

        // Return the groth16 receipt, with the stats collected earlier.
        Ok(ProveInfo {
            receipt: groth16_receipt,
            stats: succinct_prove_info.stats,
        })
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
                    is_dev_mode(),
                    "dev mode must be enabled to compress fake receipts"
                );
                Ok(receipt.clone())
            }
            // NOTE: Bonsai always returns a SuccinctReceipt, and does not currently support
            // compression of existing receipts uploaded by clients.
            (_, ReceiptKind::Succinct) => {
                bail!("BonsaiProver does not support compression on existing receipts");
            }
            (_, ReceiptKind::Groth16) => {
                // Caller is requesting a Groth16Receipt. Provide a hint on how to get one.
                bail!([
                    "BonsaiProver does not support compression on existing receipts",
                    "Set receipt_kind on ProverOpts in initial prove request to get a Groth16Receipt."
                ].join(""));
            }
        }
    }
}
