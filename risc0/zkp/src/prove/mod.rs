// Copyright 2025 RISC Zero, Inc.
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

//! Cryptographic algorithms for producing a ZK proof of compute
//!
//! This module is not typically used directly. Instead, we recommend the
//! higher-level tools offered in [`risc0_zkvm::prove`].
//!
//! [`risc0_zkvm::prove`]: https://docs.rs/risc0-zkvm/latest/risc0_zkvm/prove/index.html

mod fri;
mod merkle;
pub mod poly_group;
pub mod prover;
pub mod soundness;
pub mod write_iop;

pub use prover::Prover;
