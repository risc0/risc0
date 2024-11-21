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

use std::rc::Rc;

use risc0_bigint2::ec::{AffinePoint, WeierstrassCurve, SECP256K1_PRIME};
#[allow(unused)]
use risc0_zkvm::guest::env;

fn main() {
    let curve = Rc::new(WeierstrassCurve::<8>::new(
        SECP256K1_PRIME,
        [0u32; 8],
        [7, 0, 0, 0, 0, 0, 0, 0],
    ));
    let lhs = AffinePoint::new(
        [
            0x16f81798, 0x59f2815b, 0x2dce28d9, 0x029bfcdb, 0xce870b07, 0x55a06295, 0xf9dcbbac,
            0x79be667e,
        ],
        [
            0xfb10d4b8, 0x9c47d08f, 0xa6855419, 0xfd17b448, 0x0e1108a8, 0x5da4fbfc, 0x26a3c465,
            0x483ada77,
        ],
        Rc::clone(&curve),
    );
    let rhs = AffinePoint::new(
        [
            0xac04dc3f, 0x9465e6a4, 0xf46d2dad, 0x5d5ac4b6, 0xad2c0db6, 0xa7c06f71, 0xe335abc9,
            0x0f66dc33,
        ],
        [
            0xd3f64d1c, 0x50650be0, 0x2a8577b0, 0xb701323c, 0x95565b00, 0x6dddd83d, 0x398fcd2c,
            0x83641fc5,
        ],
        Rc::clone(&curve),
    );
    let expected = AffinePoint::new(
        [
            0x3db079e0, 0xd4ad0ff5, 0xdd0da7e2, 0x4faad0a4, 0x85894785, 0x280d6b36, 0xe8ab292d,
            0xa901b0db,
        ],
        [
            0x47298a9d, 0x01d0e60e, 0xa6b063b3, 0x716bc5e0, 0x61e7ae64, 0xaf6f04dc, 0x834f1a61,
            0x3f27e7e1,
        ],
        Rc::clone(&curve),
    );

    let result = risc0_bigint2::ec::add(&lhs, &rhs);

    assert_eq!(result, expected);
}
