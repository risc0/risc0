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

use crate::utils::{self, ClientEnvs};
use anyhow::Result;
use bonsai_sdk::alpha::SessionId;
use clap::Parser;
use hex::FromHex;
use risc0_zkvm::{sha::Digest, Receipt};
use tracing::{debug, error, info, instrument, trace};

/// `cargo risczero verify`
#[derive(Parser, Debug, Clone, PartialEq, Eq)]
pub struct VerifyCommand {
    /// Receipt source
    #[command(flatten)]
    source: Source,

    /// The hex-encoded image ID to verify the receipt against.
    image_id: String,

    /// The client environment variables.
    #[command(flatten)]
    client: ClientEnvs,
}

#[derive(Parser, Debug, Clone, PartialEq, Eq)]
#[group(required = true, multiple = false)]
struct Source {
    /// The path to the receipt file.
    #[arg(group = "source", long)]
    path: Option<String>,

    /// The Bonsai ID of the receipt to download and verify.
    #[arg(groups = ["source", "bonsai"], long)]
    id: Option<String>,
}

#[derive(Debug, Clone, PartialEq, Eq)]
enum SourceType<'a> {
    Path(&'a str),
    Id(&'a str),
}

impl VerifyCommand {
    #[instrument(skip(self))]
    pub fn run(&self) -> Result<()> {
        debug!("Running verify command");
        let receipt = self.get_receipt()?;
        let image_id = self.get_image_id()?;
        let result = receipt.verify(image_id);
        match result {
            Ok(_) => {
                info!("Receipt verified successfully");
                println!("✅ Receipt is valid!");
            }
            Err(ref error) => {
                error!(?error, "Receipt verification failed");
                eprintln!("❌ Receipt is not valid");
            }
        }

        Ok(result?)
    }

    fn get_image_id(&self) -> Result<Digest> {
        trace!("Parsing image ID");
        let image_id = Digest::from_hex(&self.image_id)?;
        debug!(?image_id, "Parsed image ID");
        Ok(image_id)
    }

    fn get_receipt(&self) -> Result<Receipt> {
        trace!("Getting receipt");
        let source = self.source();
        let receipt = match source {
            SourceType::Path(path) => {
                let receipt_raw = std::fs::read(path)?;
                parse_receipt(receipt_raw)?
            }
            SourceType::Id(id) => {
                let id = SessionId::new(id.into());
                let client = utils::get_client(&self.client)?;
                let receipt_raw = client.receipt_download(&id)?;
                parse_receipt(receipt_raw)?
            }
        };
        debug!("Got receipt");

        Ok(receipt)
    }

    fn source(&self) -> SourceType {
        match (&self.source.path, &self.source.id) {
            (Some(path), None) => SourceType::Path(path),
            (None, Some(id)) => SourceType::Id(id),
            (Some(_), Some(_)) => {
                unreachable!("Both path and ID provided. Please provide only one.")
            }
            _ => unreachable!("No path or ID provided. Please provide one."),
        }
    }
}

fn parse_receipt(receipt_raw: Vec<u8>) -> Result<Receipt> {
    let receipt: Receipt = bincode::deserialize(&receipt_raw)?;
    Ok(receipt)
}
