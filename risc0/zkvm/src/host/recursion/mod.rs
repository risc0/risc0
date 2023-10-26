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

//! This module implements the verifier for the recursion circuit.
//!
//! This module implements receipts that are generated from the recursion
//! circuit as well as verification functions for each type of receipt.

#[cfg(feature = "prove")]
mod prove;
mod receipt;
#[cfg(test)]
#[cfg(feature = "prove")]
mod tests;

pub use risc0_circuit_recursion::control_id::ALLOWED_IDS_ROOT;

#[cfg(feature = "prove")]
pub use self::prove::{identity_p254, join, lift, poseidon_hal_pair, Program, Prover, ProverOpts};
pub use self::receipt::{valid_control_ids, SuccinctReceipt};

const CIRCUIT: risc0_circuit_recursion::CircuitImpl = risc0_circuit_recursion::CircuitImpl::new();
