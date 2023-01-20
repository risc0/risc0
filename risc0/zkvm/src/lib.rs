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

//! A virtual machine to produce ZK proofs of computation
//!
//! The RISC Zero zkVM is a RISC-V virtual machine that produces
//! [zero-knowledge proofs](https://en.wikipedia.org/wiki/Zero-knowledge_proof)
//! of code it executes. By using the zkVM, a cryptographic
//! [Receipt](Receipt) is produced which anyone can [verify] was produced by
//! the zkVM's guest code. No additional information about the code execution
//! (such as, for example, the inputs provided) is revealed by publishing the
//! [Receipt](Receipt).
//!
//! This is the reference documentation for the RISC Zero zkVM. We have
//! additional (non-reference) resources for using our zkVM that you may also
//! find helpful, especially if you're new to the RISC Zero zkVM. These include:
//!
//! * Our [Hello Multiply!](https://www.risczero.com/docs/examples/hello_multiply)
//! tutorial, which walks you through writing your first zkVM project.
//! * A [zkVM Rust starter template](https://github.com/risc0/risc0-rust-starter),
//! a template for starting zkVM projects. It includes code for building and
//! launching a zkVM guest and guidance on where projects most commonly modify
//! host and guest code.
//! * The [zkVM Rust examples repository](https://github.com/risc0/risc0-rust-examples),
//! which contains various examples using our zkVM.
//! * [This clip](https://youtu.be/cLqFvhmXiD0) from our presentation at ZK Hack
//! III gives an overview of the RISC Zero zkVM.
//! [Our YouTube channel](https://www.youtube.com/@risczero) has many more
//! videos as well.
//! * And more on [the RISC Zero website](https://www.risczero.com/)!
//!
//! [verify]: ../risc0_zkp/verify/fn.verify.html

#![cfg_attr(not(feature = "std"), no_std)]
#![cfg_attr(not(feature = "std"), feature(alloc_error_handler))]
#![deny(rustdoc::broken_intra_doc_links)]

extern crate alloc;

mod control_id;
#[cfg(any(target_os = "zkvm", doc))]
pub mod guest;
#[cfg(feature = "prove")]
pub mod prove;
pub mod receipt;
pub mod serde;
pub mod sha;
#[cfg(test)]
mod tests;

pub use anyhow::Result;
use control_id::CONTROL_ID;
use risc0_zkp::core::sha::Digest;
pub use risc0_zkvm_platform::{memory::MEM_SIZE, PAGE_SIZE};

#[cfg(feature = "prove")]
pub use crate::prove::{elf::Program, image::MemoryImage, loader::Loader, Prover, ProverOpts};
pub use crate::receipt::Receipt;

const CIRCUIT: risc0_circuit_rv32im::CircuitImpl = risc0_circuit_rv32im::CircuitImpl::new();

#[derive(Clone, Debug, Eq, PartialEq)]
pub struct ControlId {
    pub table: alloc::vec::Vec<Digest>,
}

impl ControlId {
    pub fn new() -> Self {
        let mut table = alloc::vec::Vec::new();
        for entry in CONTROL_ID {
            table.push(Digest::from(entry));
        }
        ControlId { table }
    }
}
