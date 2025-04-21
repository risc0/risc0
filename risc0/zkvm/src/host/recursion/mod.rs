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

//! Prover implementation for the recursion VM.
//!
//! This module contains the recursion programs used with the zkVM.
//! As examples, the [lift], [join], and [resolve] programs are used
//! oto compress a collection of STARK receipts for a composition into
//! a single succinct receipt.
//!
#[cfg(feature = "prove")]
pub(crate) mod prove;
#[cfg(test)]
#[cfg(feature = "prove")]
mod tests;

// NOTE: merkle modules is next to receipts because it needs to be compiled for the zkVM, as part
// of SuccinctReceipt, but is logically part of the recursion system.
#[cfg(feature = "prove")]
pub use crate::receipt::merkle::{MerkleGroup, MerkleProof};
pub use risc0_circuit_recursion::control_id::{ALLOWED_CONTROL_IDS, ALLOWED_CONTROL_ROOT};

#[cfg(test)]
#[cfg(feature = "prove")]
pub use self::prove::test_zkr;
#[cfg(feature = "prove")]
pub use self::prove::{identity_p254, join, lift, resolve, Prover, RECURSION_PO2};
#[cfg(feature = "prove")]
pub use risc0_circuit_recursion::prove::Program;
