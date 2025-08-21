// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use serde::{Deserialize, Serialize};

#[derive(Deserialize, Serialize)]
pub struct Inputs {
    pub g1_compressed: Vec<u8>,
    pub g2_compressed: Vec<u8>,
    pub a: Vec<u8>,
    pub b: Vec<u8>,
}
