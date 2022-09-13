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

//! A virtual machine that produces zero-knowledge proofs of computation.
//!
//! The RISC Zero zkVM is a RISC-V virtual machine that produces
//! [zero-knowledge proofs](https://en.wikipedia.org/wiki/Zero-knowledge_proof)
//! about the code it executes. When programs are executed in the RISC Zero
//! zkVM, a cryptographic [Receipt](host::Receipt) is generated. Anyone with the
//! receipt can verify that it was produced via execution of the zkVM's guest
//! code. No additional information about code execution (such as which inputs
//! were provided to the guest) is revealed by publishing the
//! [Receipt](host::Receipt). A high-level overview of how the zkVM is
//! structured to accomplish this is available in our [Overview of the zkVM](https://www.risczero.com/docs/explainers/zkvm/zkvm_overview).
//!
//! Developers new to RISC Zero are encouraged to begin with our
//! [Risc Zero Rust Starter repository](https://github.com/risc0/risc0-rust-starter),
//! a minimal example program that demonstrates through zero-knowledge proof
//! that a number is composite. The example also introduces key components of
//! the RISC Zero zkVM.

#![cfg_attr(not(feature = "std"), no_std)]

extern crate alloc;

pub mod core;
#[cfg(feature = "prove")]
pub mod elf;
#[cfg(feature = "host")]
pub mod host;
pub mod method_id;
#[cfg(feature = "prove")]
pub mod prove;
pub mod receipt;
pub mod serde;

#[cfg(feature = "circuit")]
pub const CIRCUIT: risc0_zkvm_circuit::CircuitImpl = risc0_zkvm_circuit::CircuitImpl::new();
