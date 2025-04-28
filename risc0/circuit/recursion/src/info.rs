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

// This code is automatically generated

use risc0_zkp::adapter::{CircuitInfo, ProtocolInfo};

use super::CircuitImpl;

impl CircuitInfo for CircuitImpl {
    #[rustfmt::skip]
    const CIRCUIT_INFO: ProtocolInfo = ProtocolInfo(*b"RECURSION:rev1v1");

    #[rustfmt::skip]
    const OUTPUT_SIZE: usize = 32;

    #[rustfmt::skip]
    const MIX_SIZE: usize = 20;
}

#[allow(dead_code)]
pub const NUM_POLY_MIX_POWERS: usize = 158;

#[allow(dead_code)]
pub const POLY_MIX_POWERS: &[usize] = &[
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
    74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97,
    98, 99, 100, 101, 103, 110, 121, 122, 132, 137, 144, 151, 158, 168, 177, 188, 203, 216, 224,
    228, 231, 242, 243, 258, 265, 272, 279, 289, 298, 309, 324, 337, 345, 352, 363, 420, 501, 516,
    533, 629, 696, 760, 862, 907, 1007, 1052, 1057, 1062, 1107, 1117, 1129, 1177, 1189, 1193, 1197,
    1209, 1213, 1217, 1221, 1257,
];
