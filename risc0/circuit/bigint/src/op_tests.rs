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

use anyhow::Result;
use num_bigint::BigUint;
use risc0_zkp::core::hash::sha;
use risc0_zkp::field::{
    baby_bear::{BabyBearElem, BabyBearExtElem},
    Elem, ExtElem,
};
use test_log::test;

use crate::{
    test_harness::{bigint_tests, test_witgen, test_zkr, witness_test_data},
    BigIntClaim, BigIntContext, BIGINT_PO2,
};

// name(zkr, in_values, public_witness, private_witness, constant_witness, golden_z)
bigint_tests! {
    nondet_inv(
        nondet_inv_test_8,
        ["21", "2f", "0a"],
        [
            "21",
            "2f",
            "0a",
        ],
        [
            "0a",
            "070000",
            "01",
            "43434343",
            "5f5f5f5f",
            "22",
            "22",
        ],
        [
            "01",
        ],
        [1654613039, 1512761039, 1416363071, 340820247]
    ),
}
