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

    let (lhs, rhs, modulus): (BigUint, BigUint, BigUint) = env::read();
    let lhs = lhs.to_u32_array();
    let rhs = rhs.to_u32_array();
    let modulus = modulus.to_u32_array();

    let mut result = [0u32; risc0_bigint2::field::FIELD_256_WIDTH_WORDS];
    risc0_bigint2::field::modadd_256(lhs, rhs, modulus, mut result);

    let result = BigUint::from_slice(&result);

    env::commit(&result);
}

#[cfg(not(any(feature = "num-bigint-dig", feature = "num-bigint")))]
fn main() {
    panic!("No bigint library enabled");
}
