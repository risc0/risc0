// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
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
