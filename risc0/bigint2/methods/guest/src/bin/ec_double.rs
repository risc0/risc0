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

use risc0_bigint2::ec::{AffinePoint, Secp256k1Curve};
#[allow(unused)]
use risc0_zkvm::guest::env;

fn main() {
    const POINT_G: [[u32; 8]; 2] = [
        [
            0x16F81798, 0x59F2815B, 0x2DCE28D9, 0x029BFCDB, 0xCE870B07, 0x55A06295, 0xF9DCBBAC,
            0x79BE667E,
        ],
        [
            0xFB10D4B8, 0x9C47D08F, 0xA6855419, 0xFD17B448, 0x0E1108A8, 0x5DA4FBFC, 0x26A3C465,
            0x483ADA77,
        ],
    ];
    const EXPECTED: [[u32; 8]; 2] = [
        [
            0x5C709EE5, 0xABAC09B9, 0x8CEF3CA7, 0x5C778E4B, 0x95C07CD8, 0x3045406E, 0x41ED7D6D,
            0xC6047F94,
        ],
        [
            0x50CFE52A, 0x236431A9, 0x3266D0E1, 0xF7F63265, 0x466CEAEE, 0xA3C58419, 0xA63DC339,
            0x1AE168FE,
        ],
    ];

    let in_pt = AffinePoint::<8, Secp256k1Curve>::new_unchecked(POINT_G[0], POINT_G[1]);
    let expected_pt = AffinePoint::new_unchecked(EXPECTED[0], EXPECTED[1]);

    let mut result = AffinePoint::new_unchecked([0u32; 8], [0u32; 8]);
    in_pt.double(&mut result);
    assert_eq!(result, expected_pt);
}
