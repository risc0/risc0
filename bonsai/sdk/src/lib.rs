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

#![deny(missing_docs)]

//! A library to handle HTTP REST requests to the Bonsai-alpha prover interface
//!
//! ## Example Usage
//!
//! ```no_run
//! # mod methods {
//! #   pub const METHOD_ELF: &[u8] = &[];
//! #   pub const METHOD_ID: [u32; 8] = [0, 0, 0, 0, 0, 0, 0, 0];
//! # }
//! use std::time::Duration;
//!
//! use anyhow::Result;
//! use bonsai_sdk::alpha as bonsai_sdk;
//! use methods::{METHOD_ELF, METHOD_ID};
//! use risc0_zkvm::{compute_image_id, serde::to_vec, Receipt};
//!
//! fn run_bonsai(input_data: Vec<u8>) -> Result<()> {
//!     let client = bonsai_sdk::Client::from_env(risc0_zkvm::VERSION)?;
//!
//!     // Compute the image_id, then upload the ELF with the image_id as its key.
//!     let image_id = hex::encode(compute_image_id(METHOD_ELF)?);
//!     client.upload_img(&image_id, METHOD_ELF.to_vec())?;
//!
//!     // Prepare input data and upload it.
//!     let input_data = to_vec(&input_data).unwrap();
//!     let input_data = bytemuck::cast_slice(&input_data).to_vec();
//!     let input_id = client.upload_input(input_data)?;
//!
//!     // Add a list of assumptions
//!     let assumptions: Vec<String> = vec![];
//!
//!     // Start a session running the prover
//!     let session = client.create_session(image_id, input_id, assumptions)?;
//!     loop {
//!         let res = session.status(&client)?;
//!         if res.status == "RUNNING" {
//!             eprintln!(
//!                 "Current status: {} - state: {} - continue polling...",
//!                 res.status,
//!                 res.state.unwrap_or_default()
//!             );
//!             std::thread::sleep(Duration::from_secs(15));
//!             continue;
//!         }
//!         if res.status == "SUCCEEDED" {
//!             // Download the receipt, containing the output
//!             let receipt_url = res
//!                 .receipt_url
//!                 .expect("API error, missing receipt on completed session");
//!
//!             let receipt_buf = client.download(&receipt_url)?;
//!             let receipt: Receipt = bincode::deserialize(&receipt_buf)?;
//!             receipt
//!                 .verify(METHOD_ID)
//!                 .expect("Receipt verification failed");
//!         } else {
//!             panic!(
//!                 "Workflow exited: {} - | err: {}",
//!                 res.status,
//!                 res.error_msg.unwrap_or_default()
//!             );
//!         }
//!
//!         break;
//!     }
//!
//!     // Optionally run stark2snark
//!     // run_stark2snark(session.uuid)?;
//!
//!     Ok(())
//! }
//!
//! ```
//!
//! ## STARK to SNARK
//!
//! After a STARK proof is generated, it is possible to convert the proof to SNARK.
//!
//! ### Example
//!
//! ```no_run
//! use std::time::Duration;
//!
//! use anyhow::Result;
//! use bonsai_sdk::alpha as bonsai_sdk;
//!
//! fn run_stark2snark(session_id: String) -> Result<()> {
//!     let client = bonsai_sdk::Client::from_env(risc0_zkvm::VERSION)?;
//!
//!     let snark_session = client.create_snark(session_id)?;
//!     eprintln!("Created snark session: {}", snark_session.uuid);
//!     loop {
//!         let res = snark_session.status(&client)?;
//!         match res.status.as_str() {
//!             "RUNNING" => {
//!                 eprintln!("Current status: {} - continue polling...", res.status,);
//!                 std::thread::sleep(Duration::from_secs(15));
//!                 continue;
//!             }
//!             "SUCCEEDED" => {
//!                 let snark_receipt = res.output;
//!                 eprintln!("Snark proof!: {snark_receipt:?}");
//!                 break;
//!             }
//!             _ => {
//!                 panic!(
//!                     "Workflow exited: {} err: {}",
//!                     res.status,
//!                     res.error_msg.unwrap_or_default()
//!                 );
//!             }
//!         }
//!     }
//!     Ok(())
//! }
//! ```

/// Bonsai Alpha SDK
pub mod alpha;
#[cfg(feature = "async")]
/// Bonsai Alpha SDK async
pub mod alpha_async;

/// HTTP header key for the API key
pub const API_KEY_HEADER: &str = "x-api-key";
/// HTTP header for the risc0 version string
pub const VERSION_HEADER: &str = "x-risc0-version";
/// Environment variable name for the API url
pub const API_URL_ENVVAR: &str = "BONSAI_API_URL";
/// Environment variable name for the API key
pub const API_KEY_ENVVAR: &str = "BONSAI_API_KEY";
