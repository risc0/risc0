// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkp::core::digest::Digest;
use risc0_zkp::digest;

const CONTROL_ID_ENTRIES: usize = risc0_zkp::MAX_CYCLES_PO2 - risc0_zkp::MIN_CYCLES_PO2 + 1;

pub type ControlIds = [Digest; CONTROL_ID_ENTRIES];

/// Control IDs for each power-of-two of the rv32im circuit using SHA-256.
pub const SHA256_CONTROL_IDS: ControlIds = [{}];

/// Control IDs for each power-of-two of the rv32im circuit using Poseidon2.
pub const POSEIDON2_CONTROL_IDS: ControlIds = [{}];

/// Control IDs for each power-of-two of the rv32im circuit using Blake2b.
pub const BLAKE2B_CONTROL_IDS: ControlIds = [{}];
