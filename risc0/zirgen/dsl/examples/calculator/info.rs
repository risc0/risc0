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

// This code is automatically generated

use risc0_zkp::adapter::{CircuitInfo, ProtocolInfo};

use super::CircuitImpl;

impl CircuitInfo for CircuitImpl {
    #[rustfmt::skip]
    const CIRCUIT_INFO: ProtocolInfo = ProtocolInfo(*b"ZIRGEN_TEST_____");

    #[rustfmt::skip]
    const OUTPUT_SIZE: usize = 4;

    #[rustfmt::skip]
    const MIX_SIZE: usize = 4;
}

#[allow(dead_code)]
pub const NUM_POLY_MIX_POWERS: usize = 8;

#[allow(dead_code)]
pub const POLY_MIX_POWERS: &[usize] = &[0, 1, 2, 3, 4, 5, 6, 7];
