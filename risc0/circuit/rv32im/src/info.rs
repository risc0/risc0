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
pub const NUM_POLY_MIX_POWERS: usize = 229;

#[allow(dead_code)]
pub const POLY_MIX_POWERS: &[usize] = &[
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
    74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97,
    98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
    117, 118, 120, 128, 130, 131, 140, 141, 142, 143, 144, 146, 149, 150, 158, 163, 171, 175, 179,
    180, 181, 183, 184, 189, 201, 204, 207, 213, 214, 219, 225, 229, 233, 239, 246, 248, 251, 252,
    254, 273, 279, 282, 289, 290, 300, 303, 307, 310, 316, 320, 323, 324, 334, 380, 404, 421, 428,
    437, 452, 462, 510, 540, 558, 630, 641, 643, 646, 659, 678, 921, 1195, 1285, 1379, 1398, 1445,
    1653, 1739, 1804, 1916, 1935, 2011, 2245, 2396, 2838, 2839, 2840, 2850, 2898, 2946, 3586, 3604,
    3606, 3690, 3758, 3826, 3894, 3962, 4030, 4036, 4128, 4132, 4160, 4188, 4220, 4252, 4396, 4424,
    4428, 4450, 4478, 4511, 5219,
];
