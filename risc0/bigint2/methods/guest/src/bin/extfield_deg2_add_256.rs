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

#[cfg(feature = "num-bigint-dig")]
extern crate num_bigint_dig as num_bigint;

#[allow(unused)]
use risc0_zkvm::guest::env;

#[cfg(any(feature = "num-bigint-dig", feature = "num-bigint"))]
fn main() {
    use num_bigint::BigUint;
    use risc0_bigint2::ToBigInt2Buffer;

    let (lhs_0, lhs_1, rhs_0, rhs_1, prime): (BigUint, BigUint, BigUint, BigUint, BigUint) =
        env::read();
    let lhs = [lhs_0.to_u32_array(), lhs_1.to_u32_array()];
    let rhs = [rhs_0.to_u32_array(), rhs_1.to_u32_array()];
    let prime = prime.to_u32_array();

    let mut result =
        [[0u32; risc0_bigint2::field::FIELD_256_WIDTH_WORDS]; risc0_bigint2::field::EXT_DEGREE_2];
    risc0_bigint2::field::extfield_deg2_add_256(&lhs, &rhs, &prime, &mut result);

    let result = (
        BigUint::from_slice(&result[0]),
        BigUint::from_slice(&result[1]),
    );

    env::commit(&result);
}

#[cfg(not(any(feature = "num-bigint-dig", feature = "num-bigint")))]
fn main() {
    panic!("No bigint library enabled");
}
