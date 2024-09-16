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
    bigint_short_tests, bigint_tests, test_witgen, test_zkr, witness_test_data,
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

// fn ec_aff_sub_test_golden_values() -> Vec<BigUint> {
//     // TODO: These specific values yield an A - (-A), which should give a failure
//     // TODO: Add a test to ensure they do?
//     Vec::from([
//         from_hex("0b"), // prime:      11
//         from_hex("05"), // curve_a:     5
//         from_hex("01"), // curve_b:     1
//         from_hex("07"), // lhs_x:       7
//         from_hex("04"), // lhs_y:       4
//         from_hex("07"), // rhs_x:       7
//         from_hex("07"), // rhs_y:       7
//         from_hex("06"), // expected_x:  6
//         from_hex("04"), // expected_y:  4
//     ])
// }

// TODO: We build ZKRs for, but don't really test, the secp256k1 versions

// name(zkr, in_values, public_witness, private_witness, constant_witness, golden_z)
bigint_tests! {
    ec_add_test_8(
        ec_add_rz8test1,
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
    // This is `ec_add_test_8` with LHS & RHS swapped
    ec_add_test_8_reverse(
        ec_add_rz8test1,
        [
            "01",   // lhs_x:        1
            "70",   // lhs_y:      112
            "00",   // rhs_x:        0
            "26",   // rhs_y:       38
            "69",   // expected_x: 105
            "44",   // expected_y:  68
        ],
        ["01", "70", "00", "26", "69", "44"],
        [
            "b2", "b10000", "43434343",
            "5f5f5f5f", "4a", "4b0000", "43434343", "5f5f5f5f", "200000", "69", "890000",
            "44", "43434343", "5f5f5f5f", "43434343", "5f5f5f5f", "22", "22",
        ],
        ["01", "b3"],
        [57720872, 1358901605, 1880726009, 1745985109]
    ),
    ec_sub_test_8(
        ec_sub_rz8test1,
        [
            "97", // lhs_x:      151
            "ac", // lhs_y:      172
            "37", // rhs_x:       55
            "90", // rhs_y:      144
            "37", // expected_x:  55
            "90", // expected_y: 144
        ],
        ["97", "ac", "37", "90", "37", "90"],
        [
            "6e", "330000", "43434343",
            "5f5f5f5f", "91", "450000", "43434343", "5f5f5f5f", "760000", "37", "010100",
            "90", "43434343", "5f5f5f5f",
            "90434343", "5e5f5f5f", "22",
            "22"
        ],
        ["01", "b3"],
        [1361827893, 1544582164, 1574616391, 1372930459]
    ),
    ec_doub_test_8(
        ec_doub_rz8test1,
        [
            "37",   // lhs_x:       55
            "90",   // lhs_y:      144
            "97",   // expected_x: 151
            "ac",   // expected_y: 172
        ],
        ["37", "90", "97", "ac"],
        [
            "17", "22",
            "620100", "90434343", "5e5f5f5f", "070000",
            "97", "43434343", "5f5f5f5f", "a00000", "ac",
            "43434343", "5f5f5f5f", "22", "22",
        ],
        ["01", "b3"],
        [1739853020, 772298456, 1646252721, 890649739]
    ),
    ec_neg_test_8(
        ec_neg_rz8test1,
        [
            "14", // inp_x:       20
            "83", // inp_y:      131
            "14", // expected_x:  20
            "30", // expected_y:  48
        ],
        ["14", "83","14", "30"],
        ["22", "22"],
        ["b3"],
        [1955270777, 359504056, 1693947437, 583995072]
    ),
    ec_pts_eq_test_8(
        ec_pts_eq_rz8test1,
        [
            "1e", // lhs_x:      30
            "1b", // lhs_y:      27
            "1e", // rhs_x:      30
            "1b", // rhs_y:      27
        ],
        ["1e", "1b", "1e", "1b"],
        ["22", "22"],
        [],
        [171553196, 1884525848, 1964417951, 1602581249]
    ),
}

// name(zkr, in_values, golden_z)
bigint_short_tests! {
    ec_aff_mul1_test_8(
        ec_aff_mul_test_8,
        [
            "ac",   // inp_x:      172
            "3c",   // inp_y:       60
            "01",   // scale:        1
            "07",   // arb_x:        7
            "02",   // arb_y:        2
            "ac",   // expected_x: 172
            "3c",   // expected_y:  60
        ],
        [346372436, 1604795053, 31129203, 246390035]
    ),
    ec_aff_mul113_test_8(
        ec_aff_mul_test_8,
        [
            "9d",   // inp_x:      157
            "22",   // inp_y:       34
            "71",   // scale:      113
            "07",   // arb_x:        7
            "02",   // arb_y:        2
            "74",   // expected_x: 116
            "a7",   // expected_y: 167
        ],
        [346372436, 1604795053, 31129203, 246390035]
    ),
    ec_aff_mul2_test_32(
        ec_aff_mul_test_32,
        [
            "37",   // inp_x:       55
            "90",   // inp_y:      144
            "02",   // scale:        2
            "07",   // arb_x:        7
            "b1",   // arb_y:      177
            "97",   // expected_x: 151
            "ac",   // expected_y: 172
        ],
        [346372436, 1604795053, 31129203, 246390035]
    ),
    // ec_aff_mul2_test_256(
    //     ec_aff_mul_test_256,
    //     [
    //         "06",   // inp_x:       6
    //         "04",   // inp_y:       4
    //         "02",   // scale:       2
    //         "08",   // arb_x:       8
    //         "05",   // arb_y:       5
    //         "000b", // order:      11
    //         "00",   // expected_x:  0
    //         "01",   // expected_y:  1
    //     ],
    //     [346372436, 1604795053, 31129203, 246390035]
    // ),
}
