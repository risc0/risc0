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
    test_harness::{test_witgen, test_zkr, witness_test_data},
    BigIntClaim, BigIntContext, BIGINT_PO2,
};

macro_rules! bigint_tests {
    ($($name:ident($gen:ident, $prog:ident, $zkr:expr, $in:expr, $pub:expr, $priv:expr, $const:expr, $z:expr),)*) => {
        $(
            paste::paste! {
                fn [<$name _values>]() -> Vec<BigUint> {
                    $in.into_iter().map($crate::test_harness::from_hex).collect()
                }

                fn [<$name _context>]() -> anyhow::Result<BigIntContext> {
                    let mut ctx = BigIntContext::from_values([<$name _values>]());
                    $crate::generated::$gen(&mut ctx)?;
                    Ok(ctx)
                }

                #[test]
                fn [<$name _witgen>]() -> anyhow::Result<()> {
                    let z = BabyBearExtElem::from_subelems(
                        $z.into_iter().map(BabyBearElem::from_u64)
                    );

                    test_witgen(
                        [<$name _context>]()?,
                        witness_test_data(&$pub),
                        witness_test_data(&$priv),
                        witness_test_data(&$const),
                        z,
                    )
                }

                #[test]
                fn [<$name _zkr>]() -> anyhow::Result<()> {
                    test_zkr([<$name _context>]()?, $zkr)
                }

                #[test]
                fn [<$name _prove>]() -> Result<()> {
                    use $crate::generated::$prog;
                    let claim = BigIntClaim::from_biguints(&$prog, &[<$name _values>]());
                    let zkr = $crate::zkr::get_zkr($zkr, BIGINT_PO2)?;
                    let receipt = $crate::prove::<sha::Impl>(&[&claim], &$prog, zkr)?;
                    crate::verify::<sha::Impl>(&$prog, &[&claim], &receipt)?;
                    Ok(())
                }
            }
        )*
    }
}

// name: generated, program, zkr, in_values, public_witness, private_witness, constant_witness, golden_z
bigint_tests! {
    add_8(
        add_test_8, ADD_TEST_8, "add_test_8.zkr",
        ["01", "01", "02"],
        ["01", "01", "0200"],
        ["2222"],
        [],
        [962489600, 684492455, 226996643, 1609451183]
    ),

    add_16(
        add_test_16, ADD_TEST_16, "add_test_16.zkr",
        ["4701", "a301", "ea02"],
        ["0147", "01a3", "02ea00"],
        ["222222"],
        [],
        [1628396028, 1163057258, 1159504641, 518219607]
    ),

    add_128(
        add_test_128, ADD_TEST_128, "add_test_128.zkr",
        ["330e091fd68889efcc15be1e6244d811", "748ac69a07f0e07a234ac687f6749ea8", "a798cfb9de796a69ef6084a658b976b9"],
        ["11d844621ebe15ccef8988d61f090e33", "a89e74f687c64a237ae0f0079ac68a74", "b976b958a68460ef696a79deb9cf98a700"],
        ["2223222322232222232323222222222222"],
        [],
        [28354054, 127316002, 814881045, 149531627]
    ),

    // Add with a carry beyond the original size of the inputs
    add_128_carry(
        add_test_128, ADD_TEST_128, "add_test_128.zkr",
        ["a0000000000000000000000000000000", "a0000000000000000000000000000000", "0140000000000000000000000000000000"],
        ["000000000000000000000000000000a0", "000000000000000000000000000000a0", "0000000000000000000000000000004001"],
        ["2222222222222222222222222222222322"],
        [],
        [1617379037, 864333486, 348868579, 937145574]
    ),

    // add16 const style Test
    // Does a 16 bit add test with the same data as used in the const add test
    add_16_cs(
        add_test_16, ADD_TEST_16, "add_test_16.zkr",
        ["4747", "0033", "477a"],
        ["4747", "3300", "7a4700"],
        ["222222"],
        [],
        [1227093942, 1425511815, 962696871, 1223972504]
    ),

    const_add(
        const_add_test_8, CONST_ADD_TEST_8, "const_add_test_8.zkr",
        ["33", "477a"],
        ["33", "7a4700"],
        ["222222"],
        ["4747"],
        [1842985763, 737835842, 1760309670, 1101972070]
    ),

    // Construct a bigint claim of 0x5432 + 0xb7 == 0x54e9 with a const times a variable
    const_add_alt(
        const_add_alt_test_16, CONST_ADD_ALT_TEST_16, "const_add_alt_test_16.zkr",
        ["b7", "54e9"],
        ["b700", "e95400"],
        ["222222"],
        ["3254"],
        [1159662004, 1670679337, 1194077248, 1372635486]
    ),

    const_mul(
        const_mul_test_8, CONST_MUL_TEST_8, "const_mul_test_8.zkr",
        ["b7", "3c2fbe"],
        ["b7", "be2f3c"],
        ["a6bf83", "3f3f3f"],
        ["3254"],
        [1727847174, 1070626030, 998371662, 1475457516]
    ),

    // Runs the tests for the constant 1
    const_one(
        const_one_test_8, CONST_ONE_TEST_8, "const_one_test_8.zkr",
        ["01"],
        ["01"],
        ["22"],
        ["01"],
        [1981369411, 178339811, 860262558, 1122064780]
    ),

    // Construct a bigint claim of 0x1234 - 0x1234 == 0 with a const minus a variable
    const_twobyte(
        const_twobyte_test_16, CONST_TWOBYTE_TEST_16, "const_twobyte_test_16.zkr",
        ["1234"],
        ["3412"],
        ["2222"],
        ["3412"],
        [704963733, 1314188424, 65714486, 1269082877]
    ),

    sub_8(
        sub_test_8, SUB_TEST_8, "sub_test_8.zkr",
        ["ef", "47", "a8"],
        ["ef", "47", "a8"],
        ["22"],
        [],
        [776049965, 343441276, 1146763350, 1587586042]
    ),

    sub_128(
        sub_test_128, SUB_TEST_128, "sub_test_128.zkr",
        ["a798cfb9de796a69ef6084a658b976b9", "748ac69a07f0e07a234ac687f6749ea8", "330e091fd68889efcc15be1e6244d811"],
        ["b976b958a68460ef696a79deb9cf98a7", "a89e74f687c64a237ae0f0079ac68a74", "11d844621ebe15ccef8988d61f090e33"],
        ["22212221222122222121212222222222"],
        [],
        [890455888, 513281154, 753054158, 64454700]
    ),

    mul_8(
        mul_test_8, MUL_TEST_8, "mul_test_8.zkr",
        ["ef", "47", "4249"],
        ["ef", "47", "4942"],
        ["05c3", "201f"],
        [],
        [1429446629, 1772489311, 98405109, 498936513]
    ),

    mul_128(
        mul_test_128, MUL_TEST_128, "mul_test_128.zkr",
        ["a9ff9e10", "1c1f1d23", "12ac9e9716ca6c30"],
        ["109effa9000000000000000000000000", "231d1f1c000000000000000000000000", "306cca16979eac12000000000000000000000000000000000000000000000000"],
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
        reduce_test_8, REDUCE_TEST_8, "reduce_test_8.zkr",
        ["af", "11", "05"],
        ["af", "11", "05"],
        ["0a", "05", "c3c3", "1f1f", "22"],
        [],
        [247502032, 682060654, 655156825, 1411118715]
    ),

    reduce_128(
        reduce_test_128, REDUCE_TEST_128, "reduce_test_128.zkr",
        ["13311441233256657667877895590007", "11", "07"],
        [
            "07005995788767766556322341143113",
            "11000000000000000000000000000000",
            "07000000000000000000000000000000",
        ],
        [
            "0000c908f807f7061505120231012101",
            "07000000000000000000000000000000",
            "0505120515051505060506050805070505050505050505050505050505050505",
            "fcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfc",
            "0101010101010101010101010101010101010101010101010101010101010101",
            "0404040404040404040404040404040404040404040404040404040404040404",
            "22222222222222222222222222222222",
            ],
        [],
        [108881840, 768445877, 1224562786, 1348962832]
    ),
}
