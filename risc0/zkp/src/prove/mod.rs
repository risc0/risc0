// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
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

pub use prover::Prover;
