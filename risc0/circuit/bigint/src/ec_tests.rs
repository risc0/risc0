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
    ec_aff_sub_test_8(
        ec_aff_sub_test_8,
        [
            "07", // lhs_x:       7
            "04", // lhs_y:       4
            "06", // rhs_x:       6
            "04", // rhs_y:       4
            "07", // expected_x:  7
            "07", // expected_y:  7
        ],
        ["07", "04", "06", "04", "07", "07"],
        [
            "0a", "090000", "43434343",
            "5f5f5f5f", "08", "080000", "43434343", "5f5f5f5f", "060000", "07", "0c0000",
            "07", "43434343", "5f5f5f5f",
            "43434343", "5f5f5f5f", "22",
            "22"
        ],
        ["01", "0b"],
        [1000059093, 850908814, 998969614, 1255729734]
    ),
    ec_aff_doub_test_8(
        ec_aff_doub_test_8,
        [
            "06",   // lhs_x:       6
            "04",   // lhs_y:       4
            "00",   // expected_x:  0
            "01",   // expected_y:  1
        ],
        ["06", "04", "00", "01"],
        [
            "07", "0a",
            "190000", "43434343", "5f5f5f5f", "0a0000",
            "00", "43434343", "5f5f5f5f", "110000", "01",
            "43434343", "5f5f5f5f", "22", "22",
        ],
        ["05", "0b"],
        [1791306115, 1120035716, 1834803380, 9559040]
    ),
    ec_aff_neg_test_8(
        ec_aff_neg_test_8,
        [
            "06", // inp_x:       6
            "04", // inp_y:       4
            "06", // expected_x:  7
            "07", // expected_y:  4
        ],
        ["06", "04","06", "07"],
        ["22", "22"],
        ["0b"],
        [1044718500, 1494589160, 1951071568, 947405500]
    ),
    ec_pts_eq_test_8(
        ec_pts_eq_test_8,
        [
            "06", // lhs_x:       6
            "04", // lhs_y:       4
            "06", // rhs_x:       6
            "04", // rhs_y:       4
        ],
        ["06", "04", "06", "04"],
        ["22", "22"],
        [],
        [622647450, 1812942703, 750340746, 582495994]
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
