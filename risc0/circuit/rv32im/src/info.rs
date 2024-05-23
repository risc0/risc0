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
pub const NUM_POLY_MIX_POWERS: usize = 210;

#[allow(dead_code)]
pub const POLY_MIX_POWERS: &[usize] = &[
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
    74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97,
    98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116,
    120, 128, 129, 130, 139, 140, 144, 147, 161, 172, 177, 178, 179, 182, 188, 199, 204, 211, 212,
    217, 223, 226, 227, 237, 244, 246, 248, 252, 280, 287, 288, 300, 301, 305, 310, 320, 321, 328,
    380, 404, 419, 428, 431, 452, 462, 510, 534, 558, 635, 637, 640, 653, 912, 1182, 1269, 1360,
    1376, 1420, 1570, 1653, 1715, 1824, 1841, 1911, 2142, 2579, 2580, 2581, 2591, 2639, 2687, 3255,
    3273, 3275, 3359, 3427, 3495, 3563, 3631, 3699, 3705, 3709, 3737, 3765, 3797, 3829, 3961, 3989,
    3993, 4015, 4043, 4075, 4747,
];
