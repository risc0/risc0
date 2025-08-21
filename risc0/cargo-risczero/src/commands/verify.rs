// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use crate::utils::{self, ClientEnvs};
use anyhow::Result;
use bonsai_sdk::blocking::SessionId;
use clap::Parser;
use hex::FromHex;
use risc0_zkvm::{Receipt, sha::Digest};

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
    pub fn run(&self) -> Result<()> {
        let receipt = self.get_receipt()?;
        let image_id = self.get_image_id()?;
        let result = receipt.verify(image_id);
        match result {
            Ok(_) => {
                println!("✅ Receipt is valid!");
            }
            Err(_) => {
                eprintln!("❌ Receipt is invalid");
            }
        }

        Ok(result?)
    }

    fn get_image_id(&self) -> Result<Digest> {
        Ok(Digest::from_hex(&self.image_id)?)
    }

    fn get_receipt(&self) -> Result<Receipt> {
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

        Ok(receipt)
    }

    fn source(&self) -> SourceType<'_> {
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
