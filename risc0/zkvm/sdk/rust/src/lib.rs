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
//! [Receipt](host::Receipt) is produced which anyone can verify was produced by
//! the zkVM's guest code. No additional information about the code execution
//! (such as, for example, the inputs provided) is revealed by publishing the
//! [Receipt](host::Receipt). A high-level overview of how the zkVM is
//! structured to accomplish this is available in our
//! [Overview of the zkVM](https://www.risczero.com/docs/explainers/zkvm/zkvm_overview)
//! explainer.
//!
//! Developers new to RISC Zero are encouraged to get started with our
//! [Risc Zero Rust Starter repository](https://github.com/risc0/risc0-rust-starter),
//! which provides an example of producing a zero-knowledge proof that a number
//! is composite, along with an introduction to key components of the RISC Zero
//! zkVM.

#![cfg_attr(not(feature = "std"), no_std)]

extern crate alloc;

pub mod core;
#[cfg(feature = "prove")]
pub mod elf;
#[cfg(feature = "host")]
pub mod host;
#[cfg(feature = "host")]
pub mod method_id;
#[cfg(feature = "prove")]
pub mod prove;
#[cfg(feature = "host")]
pub mod receipt;
pub mod serde;
#[cfg(feature = "verify")]
pub mod verify;

pub use risc0_zkvm_platform as platform;

const CODE_SIZE: usize = 16;
const DATA_SIZE: usize = 162;
const ACCUM_SIZE: usize = 10;
