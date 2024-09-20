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
    // This is `ec_add_test_8` with LHS & RHS swapped
    ec_add_test_8_reverse(
        ec_add_rz8test,
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
        ec_sub_rz8test,
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
        ec_doub_rz8test,
        [
            "37",   // lhs_x:       55
            "90",   // lhs_y:      144
            "97",   // expected_x: 151
            "ac",   // expected_y: 172
        ],
        ["37", "90", "97", "ac"],
        [
            "17", "742300", "a0c3c3", "1f1f1f", "22",
            "620100", "90434343", "5e5f5f5f", "070000",
            "97", "43434343", "5f5f5f5f", "a00000", "ac",
            "43434343", "5f5f5f5f", "22", "22",
        ],
        ["01", "01", "b3"],
        [1190259367, 1384309291, 214804156, 1381364702]
    ),
    ec_neg_test_8(
        ec_neg_rz8test,
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
        ec_pts_eq_rz8test,
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
    ec_on_curve_test_8(
        ec_on_curve_rz8test,
        [
            "72", // pt_x:     114
            "53", // pt_y:      83
        ],
        ["72", "53"],
        ["480000", "6c", "43434343", "5f5f5f5f", "d20000", "00", "43434343", "5f5f5f5f", "22"],
        ["0c", "01", "b3"],
        [1911339000, 1372438828, 513839539, 1170426606]
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
        ],
        [346372436, 1604795053, 31129203, 246390035]
    ),
    ec_mul2_test_32(
        ec_mul_rz8test,
        [
            "37",   // inp_x:       55
            "90",   // inp_y:      144
            "02",   // scale:        2
            "97",   // expected_x: 151
            "ac",   // expected_y: 172
        ],
        [346372436, 1604795053, 31129203, 246390035]
    ),
    ec_add_test_256(
        ec_add_secp256k1,
        [
            "79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798",   // lhs_x
            "483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8",   // lhs_y
            "0f66dc33e335abc9a7c06f71ad2c0db65d5ac4b6f46d2dad9465e6a4ac04dc3f",   // rhs_x
            "83641fc5398fcd2c6dddd83d95565b00b701323c2a8577b050650be0d3f64d1c",   // rhs_y
            "a901b0dbe8ab292d280d6b36858947854faad0a4dd0da7e2d4ad0ff53db079e0",   // expected_x
            "3f27e7e1834f1a61af6f04dc61e7ae64716bc5e0a6b063b301d0e60e47298a9d",   // expected_y
        ],
        [346372436, 1604795053, 31129203, 246390035]
    ),
    ec_sub_test_256(
        ec_sub_secp256k1,
        [
            "a901b0dbe8ab292d280d6b36858947854faad0a4dd0da7e2d4ad0ff53db079e0", // lhs_x
            "3f27e7e1834f1a61af6f04dc61e7ae64716bc5e0a6b063b301d0e60e47298a9d", // lhs_y
            "79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798", // rhs_x
            "483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8", // rhs_y
            "0f66dc33e335abc9a7c06f71ad2c0db65d5ac4b6f46d2dad9465e6a4ac04dc3f", // expected_x
            "83641fc5398fcd2c6dddd83d95565b00b701323c2a8577b050650be0d3f64d1c", // expected_y
        ],
        [1361827893, 1544582164, 1574616391, 1372930459]
    ),
    ec_doub_test_256(
        ec_doub_secp256k1,
        [
            "79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798",   // lhs_x
            "483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8",   // lhs_y
            "c6047f9441ed7d6d3045406e95c07cd85c778e4b8cef3ca7abac09b95c709ee5",   // expected_x
            "1ae168fea63dc339a3c58419466ceaeef7f632653266d0e1236431a950cfe52a",   // expected_y
        ],
        [1739853020, 772298456, 1646252721, 890649739]
    ),
    ec_neg_test_256(
        ec_neg_secp256k1,
        [
            "79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798", // inp_x
            "483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8", // inp_y
            "79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798", // expected_x
            "b7c52588d95c3b9aa25b0403f1eef75702e84bb7597aabe663b82f6f04ef2777", // expected_y
        ],
        [1955270777, 359504056, 1693947437, 583995072]
    ),
    ec_pts_eq_test_256(
        ec_pts_eq_secp256k1,
        [
            "1e", // lhs_x:      30
            "1b", // lhs_y:      27
            "1e", // rhs_x:      30
            "1b", // rhs_y:      27
        ],
        [171553196, 1884525848, 1964417951, 1602581249]
    ),
    ec_mul47_test_256(
        ec_mul_secp256k1,
        [
            "79be667ef9dcbbac55a06295ce870b07029bfcdb2dce28d959f2815b16f81798",   // inp_x
            "483ada7726a3c4655da4fbfc0e1108a8fd17b448a68554199c47d08ffb10d4b8",   // inp_y
            "2f",   // scale:      47
            "77f230936ee88cbbd73df930d64702ef881d811e0e1498e2f1c13eb1fc345d74",   // expected_x
            "958ef42a7886b6400a08266e9ba1b37896c95330d97077cbbe8eb3c7671c60d6",   // expected_y
        ],
        [346372436, 1604795053, 31129203, 246390035]
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
    // Shouldn't be able to multiply by the prime (b/c it's congruent to 0)
    ec_mul_prime(
        ec_mul_freely_rz8test,
        [
            "ac",   // inp_x:      172
            "3c",   // inp_y:       60
            "b3",   // scale:      179
        ]
    ),
    // Shouldn't be able to add P + P
    ec_add_self(
        ec_add_freely_rz8test,
        [
            "ac",   // lhs_x:      172
            "3c",   // lhs_y:       60
            "ac",   // rhs_x:      172
            "3c",   // rhs_y:       60
        ]
    ),
    // Shouldn't be able to add P + -P
    ec_add_neg(
        ec_add_freely_rz8test,
        [
            "ac",   // lhs_x:      172
            "3c",   // lhs_y:       60
            "ac",   // rhs_x:      172
            "77",   // rhs_y:      119
        ]
    ),
    // Shouldn't be able to subtract P - P
    ec_sub_self(
        ec_sub_freely_rz8test,
        [
            "ac",   // lhs_x:      172
            "3c",   // lhs_y:       60
            "ac",   // rhs_x:      172
            "3c",   // rhs_y:       60
        ]
    ),
    // Shouldn't be able to subtract P - -P
    ec_sub_neg(
        ec_sub_freely_rz8test,
        [
            "ac",   // lhs_x:      172
            "3c",   // lhs_y:       60
            "ac",   // rhs_x:      172
            "77",   // rhs_y:      119
        ]
    ),
}
