// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_bigint2::ec::{AffinePoint, Curve, WeierstrassCurve};
#[allow(unused)]
use risc0_zkvm::guest::env;

// NOTE: This is manually constructed, to ensure changes to the API do not limit the ability to
//       define a custom curve.
// This is the secp256k1 curve.
const CURVE: &WeierstrassCurve<8> = &WeierstrassCurve::<8>::new(
    [
        0xFFFFFC2F, 0xFFFFFFFE, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
        0xFFFFFFFF,
    ],
    [0u32; 8],
    [7, 0, 0, 0, 0, 0, 0, 0],
);

#[derive(Debug, Eq, PartialEq, Ord, PartialOrd)]
pub enum TestSecp256k1Curve {}

impl Curve<8> for TestSecp256k1Curve {
    const CURVE: &'static WeierstrassCurve<8> = CURVE;
}

fn main() {
    let scalar = [
        0x409f9918, 0xd218afb5, 0x81d5a9ae, 0x1aabde69, 0xe5cd569f, 0x478b33e5, 0xd5ff94e4,
        0x232ad1e3,
    ];
    let point = AffinePoint::new_unchecked(
        [
            0x16f81798, 0x59f2815b, 0x2dce28d9, 0x029bfcdb, 0xce870b07, 0x55a06295, 0xf9dcbbac,
            0x79be667e,
        ],
        [
            0xfb10d4b8, 0x9c47d08f, 0xa6855419, 0xfd17b448, 0x0e1108a8, 0x5da4fbfc, 0x26a3c465,
            0x483ada77,
        ],
    );
    let expected = AffinePoint::new_unchecked(
        [
            0xd430a92d, 0x5fdd93b4, 0x23c8434f, 0x1616b5ae, 0x2570e09c, 0x673f0dec, 0xb6bdef51,
            0x2985d840,
        ],
        [
            0x34ab3c01, 0x0abd13e0, 0x8060d279, 0xa37beeeb, 0xb083593d, 0x4679f415, 0x6c4af2e8,
            0x1af7251d,
        ],
    );

    let mut result = AffinePoint::<8, TestSecp256k1Curve>::IDENTITY;
    point.mul(&scalar, &mut result);
    assert_eq!(result, expected);
}
