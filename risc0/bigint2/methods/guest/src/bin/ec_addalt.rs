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

    const POINT_LHS: &[u32] = &[
        0x00000000, 0x00000000, 0x00000000, 0x00000000, //
        0x00000026, 0x00000000, 0x00000000, 0x00000000,
    ];
    let lhs = AffinePt::from_slice_alt(POINT_LHS);

    const POINT_RHS: &[u32] = &[
        0x00000001, 0x00000000, 0x00000000, 0x00000000, //
        0x00000070, 0x00000000, 0x00000000, 0x00000000,
    ];
    let rhs = AffinePt::from_slice_alt(POINT_RHS);

    const POINT_EXPECTED: &[u32] = &[
        0x00000069, 0x00000000, 0x00000000, 0x00000000, //
        0x00000044, 0x00000000, 0x00000000, 0x00000000,
    ];
    let expected = AffinePt::from_slice_alt(POINT_EXPECTED);

    let result = risc0_bigint2::ec::addalt(&lhs, &rhs);
    assert_eq!(result, expected);
}