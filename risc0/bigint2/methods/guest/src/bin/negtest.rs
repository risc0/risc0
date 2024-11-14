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

#[cfg(feature = "num-bigint")]
use num_bigint::BigUint;
#[cfg(feature = "num-bigint-dig")]
use num_bigint_dig::BitUint;

fn main() {
    let lhs = [10u32];
    let rhs = [47u32];
    let mut result = [0u32];

    unsafe {
        risc0_bigint2::ec::negtest_raw(&lhs, &rhs, &mut result);
    }
    assert_eq!(result, [10u32]);
}