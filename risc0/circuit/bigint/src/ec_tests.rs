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

use crate::test_harness::{
    bigint_short_tests, bigint_should_fail_tests, bigint_tests, test_witgen, test_zkr,
    witness_test_data,
};
use crate::{BigIntClaim, BigIntContext, BIGINT_PO2};
use anyhow::Result;
use num_bigint::BigUint;
use risc0_zkp::core::hash::sha;
use risc0_zkp::field::{
    baby_bear::{BabyBearElem, BabyBearExtElem},
    Elem, ExtElem,
};
use test_log::test;

// name(zkr, in_values, public_witness, private_witness, constant_witness, golden_z)
bigint_tests! {
    ec_add_test_8(
        ec_add_rz8test,
        [
            "00",   // lhs_x:        0
            "26",   // lhs_y:       38
            "01",   // rhs_x:        1
            "70",   // rhs_y:      112
            "69",   // expected_x: 105
            "44",   // expected_y:  68
        ],
        ["00", "26", "01", "70", "69", "44"],
        [
            "01", "010000", "43434343", "5f5f5f5f", "4a", "4b0000", "43434343", "5f5f5f5f", "200000", "69",
            "890000", "44", "43434343", "5f5f5f5f", "43434343", "5f5f5f5f", "22", "22",
        ],
        ["01", "b3"],
        [572061840, 516831536, 589702236, 483446720]
    ),
}

// name(zkr, in_values, golden_z)
bigint_short_tests! {
    ec_mul113_test_8(
        ec_mul_rz8test,
        [
            "9d",   // inp_x:      157
            "22",   // inp_y:       34
            "71",   // scale:      113
            "74",   // expected_x: 116
            "a7",   // expected_y: 167
        ]
    ),
}

bigint_should_fail_tests! {
    // Shouldn't be able to multiply by zero
    ec_mul0(
        ec_mul_freely_rz8test,
        [
            "ac",   // inp_x:      172
            "3c",   // inp_y:       60
            "00",   // scale:        0
        ]
    ),
}
