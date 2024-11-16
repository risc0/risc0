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

#[allow(unused)]
use risc0_zkvm::guest::env;

use risc0_bigint2::ec::AffinePt;

#[cfg(feature = "num-bigint")]
use num_bigint::BigUint;
#[cfg(feature = "num-bigint-dig")]
use num_bigint_dig::BitUint;

fn main() {
    let scalar = BigUint::parse_bytes(b"2f", 16).unwrap();
    let point = AffinePt{
        x: BigUint::from_slice(&[
            0x16f81798, 0x59f2815b, 0x2dce28d9, 0x029bfcdb,
            0xce870b07, 0x55a06295, 0xf9dcbbac, 0x79be667e
        ]),
        y: BigUint::from_slice(&[
            0xfb10d4b8, 0x9c47d08f, 0xa6855419, 0xfd17b448,
            0x0e1108a8, 0x5da4fbfc, 0x26a3c465, 0x483ada77
        ])
    };
    let expected = AffinePt {
        x: BigUint::from_slice(&[
            0xfc345d74, 0xf1c13eb1, 0x0e1498e2, 0x881d811e,
            0xd64702ef, 0xd73df930, 0x6ee88cbb, 0x77f23093
        ]),
        y: BigUint::from_slice(&[
            0x671c60d6, 0xbe8eb3c7, 0xd97077cb, 0x96c95330,
            0x9ba1b378, 0x0a08266e, 0x7886b640, 0x958ef42a

        ])
    };

    let result = risc0_bigint2::ec::mul(&scalar, &point);
    assert_eq!(result, expected);
}