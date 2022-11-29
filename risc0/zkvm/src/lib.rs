// Copyright 2022 Risc0, Inc.
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

//! A virtual machine to produces ZK proofs of computation
//!
//! The RISC Zero zkVM is a RISC-V virtual machine that produces
//! [zero-knowledge proofs](https://en.wikipedia.org/wiki/Zero-knowledge_proof)
//! of code it executes. By using the zkVM, a cryptographic
//! [Receipt](Receipt) is produced which anyone can verify was produced by
//! the zkVM's guest code. No additional information about the code execution
//! (such as, for example, the inputs provided) is revealed by publishing the
//! [Receipt](Receipt). A high-level overview of how the zkVM is
//! structured to accomplish this is available in our
//! [Overview of the zkVM](https://www.risczero.com/docs/explainers/zkvm/)
//! explainer.
//!
//! Developers new to RISC Zero are encouraged to get started with our
//! [RISC Zero Rust Starter repository](https://github.com/risc0/risc0-rust-starter),
//! which provides an example of producing a zero-knowledge proof that a number
//! is composite, along with an introduction to key components of the RISC Zero
//! zkVM.

#![cfg_attr(not(feature = "std"), no_std)]
#![cfg_attr(not(feature = "std"), feature(alloc_error_handler))]
#![deny(rustdoc::broken_intra_doc_links)]

extern crate alloc;

#[cfg(any(target_os = "zkvm", doc))]
pub mod guest;
pub mod method_id;
#[cfg(not(target_os = "zkvm"))]
pub mod prove;
pub mod receipt;
pub mod serde;
pub mod sha;
#[cfg(test)]
mod tests;

pub use anyhow::Result;

#[cfg(not(target_os = "zkvm"))]
pub use crate::prove::{Prover, ProverOpts};
pub use crate::{
    method_id::{MethodId, DEFAULT_METHOD_ID_LIMIT},
    receipt::Receipt,
};

const CIRCUIT: risc0_circuit_rv32im::CircuitImpl = risc0_circuit_rv32im::CircuitImpl::new();
