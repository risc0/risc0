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
    add_8(
        add_test_8,
        ["01", "01", "02"],
        ["01", "01", "0200"],
        ["4242"],
        [],
        [1983457899, 309501857, 46296248, 1580058474]
    ),

    add_16(
        add_test_16,
        ["4701", "a301", "ea02"],
        ["0147", "01a3", "02ea00"],
        ["424242"],
        [],
        [1148591221, 1887677231, 891102735, 652823536]
    ),

    add_128(
        add_test_128,
        ["330e091fd68889efcc15be1e6244d811", "748ac69a07f0e07a234ac687f6749ea8", "a798cfb9de796a69ef6084a658b976b9"],
        ["11d844621ebe15ccef8988d61f090e33", "a89e74f687c64a237ae0f0079ac68a74", "b976b958a68460ef696a79deb9cf98a700"],
        ["4243424342434242434343424242424242"],
        [],
        [736894987, 494769951, 1734229809, 1455029597]
    ),

    // Add with a carry beyond the original size of the inputs
    add_128_carry(
        add_test_128,
        ["a0000000000000000000000000000000", "a0000000000000000000000000000000", "0140000000000000000000000000000000"],
        ["000000000000000000000000000000a0", "000000000000000000000000000000a0", "0000000000000000000000000000004001"],
        ["4242424242424242424242424242424342"],
        [],
        [788413327, 1502115561, 1713800611, 1714763433]
    ),

    // add16 const style Test
    // Does a 16 bit add test with the same data as used in the const add test
    add_16_cs(
        add_test_16,
        ["4747", "0033", "477a"],
        ["4747", "3300", "7a4700"],
        ["424242"],
        [],
        [831726650, 1332173325, 949108060, 1753072944]
    ),

    const_add(
        const_add_test_8,
        ["33", "477a"],
        ["33", "7a4700"],
        ["424242"],
        ["4747"],
        [144302856, 1655447286, 469208524, 466230429]
    ),

    // Construct a bigint claim of 0x5432 + 0xb7 == 0x54e9 with a const times a variable
    const_add_alt(
        const_add_alt_test_16,
        ["b7", "54e9"],
        ["b700", "e95400"],
        ["424242"],
        ["3254"],
        [1034326444, 1974114120, 1047167256, 1612405850]
    ),

    const_mul(
        const_mul_test_8,
        ["b7", "3c2fbe"],
        ["b7", "be2f3c"],
        ["e6ffc3", "1f1f1f"],
        ["3254"],
        [1618220606, 1134200541, 886680393, 718538158]
    ),

    // Runs the tests for the constant 1
    const_one(
        const_one_test_8,
        ["01"],
        ["01"],
        ["22"],
        ["01"],
        [1981369411, 178339811, 860262558, 1122064780]
    ),

    // Construct a bigint claim of 0x1234 - 0x1234 == 0 with a const minus a variable
    const_twobyte(
        const_twobyte_test_16,
        ["1234"],
        ["3412"],
        ["2222"],
        ["3412"],
        [704963733, 1314188424, 65714486, 1269082877]
    ),

    sub_8(
        sub_test_8,
        ["ef", "47", "a8"],
        ["ef", "47", "a8"],
        ["42"],
        [],
        [1108111447, 1632642494, 500504840, 734386563]
    ),

    sub_128(
        sub_test_128,
        ["a798cfb9de796a69ef6084a658b976b9", "748ac69a07f0e07a234ac687f6749ea8", "330e091fd68889efcc15be1e6244d811"],
        ["b976b958a68460ef696a79deb9cf98a7", "a89e74f687c64a237ae0f0079ac68a74", "11d844621ebe15ccef8988d61f090e33"],
        ["42414241424142424141414242424242"],
        [],
        [1536154592, 1933208113, 1653281541, 642770476]
    ),

    mul_8(
        mul_test_8,
        ["ef", "47", "4249"],
        ["ef", "47", "4942"],
        ["05c3", "201f"],
        [],
        [1429446629, 1772489311, 98405109, 498936513]
    ),

    mul_128(
        mul_test_128,
        ["a9ff9e10", "1c1f1d23", "12ac9e9716ca6c30"],
        [
            "109effa9000000000000000000000000",
            "231d1f1c000000000000000000000000",
            "306cca16979eac12000000000000000000000000000000000000000000000000"
        ],
        [
            "071c3b4e48351705050505050505050505050505050505050505050505050505",
            "fcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfc",
            "0101010101010101010101010101010101010101010101010101010101010101",
            "0404040404040404040404040404040404040404040404040404040404040404",
        ],
        [],
        [1269517810, 1259488229, 1292517392, 1940782769]
    ),

    reduce_8(
        reduce_test_8,
        ["af", "11", "05"],
        ["af", "11", "05"],
        ["0a", "05", "e3", "1f", "22"],
        [],
        [762402419, 1860570455, 581591651, 1077948011]
    ),

    reduce_128(
        reduce_test_128,
        ["13311441233256657667877895590007", "11", "07"],
        [
            "07005995788767766556322341143113",
            "11000000000000000000000000000000",
            "07000000000000000000000000000000",
        ],
        [
            "0000c908f807f7061505120231012101",
            "07000000000000000000000000000000",
            "24243124342434242524252427242624242424242424242424242424242424",
            "fcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfc",
            "01010101010101010101010101010101010101010101010101010101010101",
            "04040404040404040404040404040404040404040404040404040404040404",
            "22222222222222222222222222222222",
            ],
        [],
        [732911456, 1581837877, 1546196128, 905951498]
    ),

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
            "0700",
            "01",
            "e3e3",
            "1f1f",
            "22",
            "22",
        ],
        [
            "01",
        ],
        [1440011210, 947754115, 1108426756, 492078813]
    ),
}
