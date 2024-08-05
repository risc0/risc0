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
    const CIRCUIT_INFO: ProtocolInfo = ProtocolInfo(*b"RV32IM:rev1v1___");

    #[rustfmt::skip]
    const OUTPUT_SIZE: usize = 138;

    #[rustfmt::skip]
    const MIX_SIZE: usize = 40;
}

#[allow(dead_code)]
pub const NUM_POLY_MIX_POWERS: usize = 219;

#[allow(dead_code)]
pub const POLY_MIX_POWERS: &[usize] = &[
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
    74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97,
    98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
    117, 118, 120, 128, 130, 143, 144, 146, 149, 158, 162, 171, 175, 179, 180, 181, 184, 189, 195,
    200, 204, 207, 213, 214, 219, 225, 229, 233, 238, 246, 248, 251, 252, 254, 273, 279, 282, 289,
    290, 300, 302, 306, 310, 316, 320, 323, 324, 332, 380, 404, 421, 428, 435, 452, 462, 510, 538,
    558, 641, 644, 657, 921, 1195, 1285, 1379, 1398, 1445, 1641, 1727, 1792, 1904, 1923, 1997,
    2231, 2673, 2674, 2675, 2685, 2733, 2781, 3349, 3367, 3369, 3453, 3521, 3589, 3657, 3725, 3793,
    3799, 3803, 3831, 3859, 3891, 3923, 4055, 4083, 4087, 4109, 4137, 4170, 4846,
];
