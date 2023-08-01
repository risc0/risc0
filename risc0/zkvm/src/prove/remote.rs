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

use ::bonsai_sdk::alpha::SdkErr;
use anyhow::{bail, Result};
use bonsai_sdk::alpha as bonsai_sdk;
use risc0_binfmt::MemoryImage;

use super::Prover;
use crate::{ExecutorEnv, Receipt, Segment, SegmentReceipt, Session, VerifierContext};

/// An implementation of a [Prover] that runs proof workloads remotely.
pub struct RemoteProver {
    name: String,
}

impl RemoteProver {
    /// construct a remote prover. Unlike the [LocalProver], the hal is taken
    /// care of by the remote prover.
    pub fn new(name: &str) -> Self {
        Self {
            name: name.to_string(),
        }
    }
}

impl Prover for RemoteProver {
    fn get_name(&self) -> String {
        self.name.clone()
    }

    fn get_peak_memory_usage(&self) -> usize {
        0
    }

    fn prove_session(&self, _ctx: &VerifierContext, _session: &Session) -> Result<Receipt> {
        bail!("this is unimplemented for prover [{}]", self.get_name())
    }

    fn prove_segment(&self, _ctx: &VerifierContext, _segment: &Segment) -> Result<SegmentReceipt> {
        bail!("this is unimplemented for prover [{}]", self.get_name())
    }

    fn prove(
        &self,
        env: ExecutorEnv<'_>,
        _ctx: &VerifierContext,
        image: MemoryImage,
    ) -> Result<Receipt> {
        let client = bonsai_sdk::Client::from_env()?;

        // upload the image
        let image_id = hex::encode(image.compute_id());
        let image = bincode::serialize(&image)?;

        // ImageIdExists indicates that this image has already been uploaded to bonsai.
        // If this is the case, simply move on to uploading the input.
        match client.upload_img(&image_id, image) {
            Ok(()) => (),
            Err(SdkErr::ImageIdExists) => (),
            Err(err) => return Err(err.into()),
        }

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
                let receipt_url = match res.receipt_url {
                    Some(url) => url,
                    None => bail!("API error, missing receipt on completed session"),
                };

                let receipt_buf = client.download(&receipt_url)?;
                let receipt: Receipt = bincode::deserialize(&receipt_buf)?;
                return Ok(receipt);
            } else {
                bail!("Bonsai prover workflow exited: {}", res.status);
            }
        }
    }
}
