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

use crate::test_harness::{test_witgen, test_zkr, witness_test_data, bigint_tests};
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
//         from_hex("0b"), // order:      11
//         from_hex("07"), // rhs_x:       7
//         from_hex("07"), // rhs_y:       7
//         from_hex("06"), // expected_x:  6
//         from_hex("04"), // expected_y:  4
//     ])
// }



// name(zkr, in_values, public_witness, private_witness, constant_witness, golden_z)
bigint_tests! {
    ec_aff_add_test_8(
        ec_aff_add_test_8,
        [
            "0b",   // prime:      11
            "05",   // curve_a:     5
            "01",   // curve_b:     1
            "06",   // lhs_x:       6
            "04",   // lhs_y:       4
            "0b",   // order:      11
            "07",   // rhs_x:       7
            "07",   // rhs_y:       7
            "07",   // expected_x:  7
            "04",   // expected_y:  4
        ],
        ["0b", "05", "01", "06", "04", "0b", "07", "07", "07", "04"],
        [
            "01", "03", "c3c3", "1f1f", "01", "01", "c3c3", "1f1f", "01", "000000", "01", "43434343",
            "5f5f5f5f", "22", "000000", "03", "43434343", "5f5f5f5f", "010000", "07", "43434343",
            "5f5f5f5f", "00", "08", "c3c3", "1f1f", "000000", "09", "43434343", "5f5f5f5f", "01", "07",
            "c3c3", "1f1f", "010000", "0a", "43434343", "5f5f5f5f", "00", "04", "c3c3", "1f1f", "22",
            "22",
        ],
        ["01"],
        [1362462476, 830700020, 473719968, 1536856857]
    ),
    ec_aff_sub_test_8(
        ec_aff_sub_test_8,
        [
            "0b", // prime:      11
            "05", // curve_a:     5
            "01", // curve_b:     1
            "07", // lhs_x:       7
            "04", // lhs_y:       4
            "0b", // order:      11
            "06", // rhs_x:       6
            "04", // rhs_y:       4
            "07", // expected_x:  7
            "07", // expected_y:  7
        ],
        ["0b", "05", "01", "07", "04", "0b00", "06", "04", "07", "07"],
        [
            "01", "03", "c3c3", "1f1f", "00", "0a", "c3c3", "1f1f", "0a", "090000", "01", "43434343",
            "5f5f5f5f", "22", "020000", "08", "43434343", "5f5f5f5f", "050000", "01", "43434343",
            "5f5f5f5f", "01", "03", "c3c3", "1f1f", "050000", "09", "43434343", "5f5f5f5f", "01", "07",
            "c3c3", "1f1f", "050000", "01", "43434343", "5f5f5f5f", "01", "07", "c3c3", "1f1f", "22",
            "22",
        ],
        ["01"],
        [346372436, 1604795053, 31129203, 246390035]
    ),
    ec_aff_mul1_test_8(
        ec_aff_mul_test_8,
        [
            "0b",   // prime:      11
            "05",   // curve_a:     5
            "01",   // curve_b:     1
            "06",   // inp_x:       6
            "04",   // inp_y:       4
            "01",   // scale:       1
            "00",   // arb_x:       0
            "0a",   // arb_y:      10
            "000b", // order:      11
            "06",   // expected_x:  6
            "04",   // expected_y:  4
        ],
        ["0b", "05", "01", "07", "04", "0b00", "06", "04", "07", "07"],  // TODO: Unconvinced these numbers are right
        [
            "01", "03", "c3c3", "1f1f", "00", "0a", "c3c3", "1f1f", "0a", "090000", "01", "43434343",
            "5f5f5f5f", "22", "020000", "08", "43434343", "5f5f5f5f", "050000", "01", "43434343",
            "5f5f5f5f", "01", "03", "c3c3", "1f1f", "050000", "09", "43434343", "5f5f5f5f", "01", "07",
            "c3c3", "1f1f", "050000", "01", "43434343", "5f5f5f5f", "01", "07", "c3c3", "1f1f", "22",
            "22",
        ],
        ["01"],
        [346372436, 1604795053, 31129203, 246390035]
    ),
    ec_aff_mul2_test_8(
        ec_aff_mul_test_8,
        [
            "0b",   // prime:      11
            "05",   // curve_a:     5
            "01",   // curve_b:     1
            "06",   // inp_x:       6
            "04",   // inp_y:       4
            "02",   // scale:       2
            "08",   // arb_x:       8
            "05",   // arb_y:       5
            "000b", // order:      11
            "00",   // expected_x:  0
            "01",   // expected_y:  1
        ],
        ["0b", "05", "01", "07", "04", "0b00", "06", "04", "07", "07"],  // TODO: Unconvinced these numbers are right
        [
            "01", "03", "c3c3", "1f1f", "00", "0a", "c3c3", "1f1f", "0a", "090000", "01", "43434343",
            "5f5f5f5f", "22", "020000", "08", "43434343", "5f5f5f5f", "050000", "01", "43434343",
            "5f5f5f5f", "01", "03", "c3c3", "1f1f", "050000", "09", "43434343", "5f5f5f5f", "01", "07",
            "c3c3", "1f1f", "050000", "01", "43434343", "5f5f5f5f", "01", "07", "c3c3", "1f1f", "22",
            "22",
        ],
        ["01"],
        [346372436, 1604795053, 31129203, 246390035]
    ),
    ec_aff_doub_test_8(
        ec_aff_doub_test_8,
        [
            "0b",   // prime:      11
            "05",   // curve_a:     5
            "01",   // curve_b:     1
            "06",   // lhs_x:       6
            "04",   // lhs_y:       4
            "000b", // order:      11
            "00",   // expected_x:  0
            "01",   // expected_y:  1
        ],
        ["0b", "05", "01", "06", "04", "0b00", "00", "01"],
        [
            "030000", "03", "43434343", "5f5f5f5f", "010000", "03", "43434343", "5f5f5f5f", "00", "08",
            "c3c3", "1f1f", "07", "050000", "01", "43434343", "5f5f5f5f", "22", "010000", "0a",
            "43434343", "5f5f5f5f", "050000", "05", "43434343", "5f5f5f5f", "00", "0a", "c3c3", "1f1f",
            "090000", "01", "43434343", "5f5f5f5f", "01", "00", "c3c3", "1f1f", "000000", "00",
            "43434343", "5f5f5f5f", "01", "01", "c3c3", "1f1f", "22", "22",
        ],
        ["03", "01"],
        [1034309412, 1833449996, 1848796126, 1670858275]
    ),
    ec_aff_neg_test_8(
        ec_aff_neg_test_8,
        [
            "0b", // prime:      11
            "05", // curve_a:     5
            "01", // curve_b:     1
            "06", // inp_x:       6
            "04", // inp_y:       4
            "0b", // order:      11
            "06", // expected_x:  7
            "07", // expected_y:  4
        ],
        ["0b", "05", "01", "06", "04", "0b", "06", "07"],
        ["22", "22"],
        [],
        [853402342, 722268157, 1119795898, 1225181898]
    ),
    ec_pts_eq_test_8(
        ec_pts_eq_test_8,
        [
            "0b", // prime:      11
            "05", // curve_a:     5
            "01", // curve_b:     1
            "06", // lhs_x:       6
            "04", // lhs_y:       4
            "0b", // order:      11
            "06", // rhs_x:       6
            "04", // rhs_y:       4
        ],
        ["0b", "05", "01", "06", "04", "0b", "06", "04"],
        ["22", "22"],
        [],
        [536847593, 765334452, 1198237495, 1051679438]
    ),
}
