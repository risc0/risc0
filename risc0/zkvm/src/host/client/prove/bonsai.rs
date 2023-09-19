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

use core::time::Duration;

use anyhow::{anyhow, bail, Result};
use bonsai_sdk::alpha::Client;
use risc0_binfmt::MemoryImage;

use super::Prover;
use crate::{ExecutorEnv, ProverOpts, Receipt, VerifierContext};

/// An implementation of a [Prover] that runs proof workloads via Bonsai.
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

    fn prove(
        &self,
        env: ExecutorEnv<'_>,
        _ctx: &VerifierContext,
        _opts: &ProverOpts,
        image: MemoryImage,
    ) -> Result<Receipt> {
        let client = Client::from_env()?;

        // upload the image
        let image_id = hex::encode(image.compute_id());
        let image = bincode::serialize(&image)?;

        // return value 'exists' is ignored here
        client.upload_img(&image_id, image)?;

        // upload input data
        let input_id = client.upload_input(env.input)?;

        // While this is the executor, we want to start a session on the bonsai prover.
        // By doing so, we can return a session ID so that the prover can use it to
        // retrieve the receipt.
        let session = client.create_session(image_id, input_id)?;

        loop {
            // The session has already been started in the executor. Poll bonsai to check if
            // the proof request succeeded.
            let res = session.status(&client)?;
            if res.status == "RUNNING" {
                std::thread::sleep(Duration::from_secs(5));
                continue;
            }
            if res.status == "SUCCEEDED" {
                // Download the receipt, containing the output
                let receipt_url = res
                    .receipt_url
                    .ok_or(anyhow!("API error, missing receipt on completed session"))?;

                let receipt_buf = client.download(&receipt_url)?;
                let receipt: Receipt = bincode::deserialize(&receipt_buf)?;
                return Ok(receipt);
            } else {
                bail!("Bonsai prover workflow exited: {}", res.status);
            }
        }
    }
}
