// Copyright 2025 RISC Zero, Inc.
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

//! Cryptographic algorithms for producing a ZK proof of compute
//!
//! This module is not typically used directly. Instead, we recommend the
//! higher-level tools offered in [`risc0_zkvm`].
//!
//! [`risc0_zkvm`]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/

mod fri;
mod merkle;
pub mod poly_group;
pub mod prover;
pub mod soundness;
pub mod write_iop;

pub(crate) use merkle::MerkleTreeProver;
pub use prover::Prover;
