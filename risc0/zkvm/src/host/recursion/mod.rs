// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

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
pub use risc0_circuit_recursion::control_id::{
    ALLOWED_CONTROL_IDS, ALLOWED_CONTROL_ROOT, BN254_IDENTITY_CONTROL_ID,
};

#[cfg(test)]
#[cfg(feature = "prove")]
pub use self::prove::test_zkr;
#[cfg(feature = "prove")]
pub use self::prove::{Prover, RECURSION_PO2, identity_p254, join, lift, resolve};
#[cfg(feature = "prove")]
pub use risc0_circuit_recursion::prove::Program;
