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

use risc0_zkp::core::digest::Digest;
use risc0_zkp::digest;

/// Smallest cycle limit, as a power of two (po2), supported as a lift program.
pub const MIN_LIFT_PO2: usize = 14;

/// Control IDs allowed in the default set of recursion programs. Includes control IDs for the base
/// set of recursion programs, and each power-of-two of the rv32im circuit, using Poseidon2.
pub const ALLOWED_CONTROL_IDS: &[Digest] = &[
    digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"), // recursion identity.zkr
    digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"), // recursion join.zkr
    digest!("642e28295ee19a245418033cbd2ffc49be95401b22fe007454efeb1ef3bf540c"), // recursion lift_rv32im_v2_14.zkr
    digest!("2f4b5005c155475631f1cc04b3e43c5e9fcbfd40d99dd646086032080615f02b"), // recursion lift_rv32im_v2_15.zkr
    digest!("612ec2536d89a94f4623b96580b3471382ce3b67c93570352a2b1d604634684f"), // recursion lift_rv32im_v2_16.zkr
    digest!("d5ffe907fec0165d0a6edf308a76e408ee54bc1fe1796020fc9caf655333fa12"), // recursion lift_rv32im_v2_17.zkr
    digest!("ad9bb40020725e31ddce266a2c1d4b50f523761a282e3d757ffc82655c2d705f"), // recursion lift_rv32im_v2_18.zkr
    digest!("52c55a5fe36c2066a3027847bdad8b42e955811507f4375ac4b35009c4132a3c"), // recursion lift_rv32im_v2_19.zkr
    digest!("5737954a63f2344ab5f8f42731339a6e7b99b441bbc2286c3ef0610f3de72c40"), // recursion lift_rv32im_v2_20.zkr
    digest!("dc58493f7bf98418d11dbd43d779425e778043086a2e3b0186f51b6d90bbe338"), // recursion lift_rv32im_v2_21.zkr
    digest!("05d09f2a2a3d002f38414e2da130590a7f6c196a44685811df79b21295f37b03"), // recursion lift_rv32im_v2_22.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("9febb533e3371a5a906084264081010d6e6b0718eb074a15ad7d3f71c3c0c95f");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("c07a65145c3cb48b6101962ea607a4dd93c753bb26975cb47feb00d3666e4404");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 27] = [
    (
        "identity.zkr",
        digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"),
    ),
    (
        "join.zkr",
        digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"),
    ),
    (
        "lift_14.zkr",
        digest!("2f609032975d7931e9d569484cdb5c1e8758af6f6d24c91968e8171b4e48652a"),
    ),
    (
        "lift_15.zkr",
        digest!("53b94f649b8fef3283c730425bf9be1618b82a76e270bd44b351f16eda68d00d"),
    ),
    (
        "lift_16.zkr",
        digest!("919c664b394f6b3e7500d151204ede5e6afd4d1a3724925ca341971e93cffc46"),
    ),
    (
        "lift_17.zkr",
        digest!("bc52395cbfbbdc6783e19443161c0a559496a017aeb6370232a5313125032175"),
    ),
    (
        "lift_18.zkr",
        digest!("442f0a4cef957609ab5ee447a279351e6dc212734cbc6e3e5bbf8b086f1a7818"),
    ),
    (
        "lift_19.zkr",
        digest!("d621555070b62e383b8e16511aa8b244cb442656c5c396302fe75816c477b902"),
    ),
    (
        "lift_20.zkr",
        digest!("66f12c252c978962a100976c69ea6a4dfb2b4a2a504d6d5c60fb8e2fff6f4b61"),
    ),
    (
        "lift_21.zkr",
        digest!("88a6322eccb8f141087c48174211df1d0e071603ebfefb69f0099836569e384a"),
    ),
    (
        "lift_22.zkr",
        digest!("bb71f46d8931c80fbcf10f3b5314b93cb7b8061d4658c55000c2c26967b58a0c"),
    ),
    (
        "lift_23.zkr",
        digest!("34a4dd0eb8f410674c09c0419c8bf62ef768a476ccd8e84f5809534e0b0e0065"),
    ),
    (
        "lift_24.zkr",
        digest!("d8c1dd073822ac1da582bd52bed7ee35f106326dcb7a191d66df420016339571"),
    ),
    (
        "lift_rv32im_v2_14.zkr",
        digest!("642e28295ee19a245418033cbd2ffc49be95401b22fe007454efeb1ef3bf540c"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("2f4b5005c155475631f1cc04b3e43c5e9fcbfd40d99dd646086032080615f02b"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("612ec2536d89a94f4623b96580b3471382ce3b67c93570352a2b1d604634684f"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("d5ffe907fec0165d0a6edf308a76e408ee54bc1fe1796020fc9caf655333fa12"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("ad9bb40020725e31ddce266a2c1d4b50f523761a282e3d757ffc82655c2d705f"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("52c55a5fe36c2066a3027847bdad8b42e955811507f4375ac4b35009c4132a3c"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("5737954a63f2344ab5f8f42731339a6e7b99b441bbc2286c3ef0610f3de72c40"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("dc58493f7bf98418d11dbd43d779425e778043086a2e3b0186f51b6d90bbe338"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("05d09f2a2a3d002f38414e2da130590a7f6c196a44685811df79b21295f37b03"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("0a5cf07710d940654664826917d57351f73a6d28df0b2421b070d273596efc2b"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("6eaaa00ea303632145eaeb5bbf98826ca2f1b368cb4f8d0bce4a9952958d000b"),
    ),
    (
        "resolve.zkr",
        digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("6d55102aa73086602f7039412200124bdec91f0c497c606f9aa09040403e030b"),
    ),
    (
        "union.zkr",
        digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"),
    ),
];

/// Control IDs for included recursion programs (ZKRs), using SHA-256.
pub const SHA256_CONTROL_IDS: [(&str, Digest); 27] = [
    (
        "identity.zkr",
        digest!("d7ecd18c7d06fc468166147cf20869aa10f32e097a0c166146a5a62dd2d975ea"),
    ),
    (
        "join.zkr",
        digest!("dc44002689aa7852410ad1c840388d66b8b9a2f6d0c4fb6b3ac6ec2ea17d9855"),
    ),
    (
        "lift_14.zkr",
        digest!("d164a42f8bb7c70049e4873871fab98d88d04f1914b25a1370a7a877b7ff2ca3"),
    ),
    (
        "lift_15.zkr",
        digest!("f2ffb9a1c43b01741e01a2d07d5f65ffe0ce231c70ddb128094f2a22f073c33c"),
    ),
    (
        "lift_16.zkr",
        digest!("8843478fd585afc7cf84c8905ce16ed8cadbb61c45248619f9b252900e5167c8"),
    ),
    (
        "lift_17.zkr",
        digest!("4a54533e7ef8b620ca102ed763ebc94e969fd608d669623d466d43775dbec7a1"),
    ),
    (
        "lift_18.zkr",
        digest!("954ffa89a80c010191f3ade9ca63c1f4f9689410df02faa801dc1b98ac557cfb"),
    ),
    (
        "lift_19.zkr",
        digest!("87150aa1b6b0fc92b68d9238d0c2a83a17da3d5d3775fd23b2517e0d7fd7697b"),
    ),
    (
        "lift_20.zkr",
        digest!("00676bedc32cc1e0dd7e490be83f4be39f379beedc35983ace0782061d65d73d"),
    ),
    (
        "lift_21.zkr",
        digest!("10d8d3a1eee1dec7c6cc0553222ab8ac9b6bfeb0bd1553e097fb29a3ef22a606"),
    ),
    (
        "lift_22.zkr",
        digest!("fcbe182cb5a235fc28d43ba1137908609958587e18060aa712be08d5833a8af3"),
    ),
    (
        "lift_23.zkr",
        digest!("f3f8278b8f56e0c2292cf7d0b395405dcf67760638e4ad901b3df406303c90b9"),
    ),
    (
        "lift_24.zkr",
        digest!("a827fd3663ab862331c47b1ba985fde346c13851535b1d80693b6367771644a7"),
    ),
    (
        "lift_rv32im_v2_14.zkr",
        digest!("babc9eac7bc7ce0685b360d52a97d914373094857f1449ab45d87c6525e075b4"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("0a1cf2dada20e3941bda6ad10c2167ce163cdc1936dffc9f11bd673a24ace105"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("55899aa3923a17b62cd5895e6dc2122441e938c3f2ff854d1a82880b7c5c27d3"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("fe107b68082207d67e1b4f8958ec0fbd4cdd371f9f0929832b1ec590a279bc89"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("28d3df9db77848b4a4782c17ddbd56f1be2e6e5102afccde11029f19c00e3760"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("b23286e1d35254d70e606c12bb71b80fed5dcbb6fb55fe490eacc69a22671231"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("95e3303b641713be152d3dcd0c760ef2861dd576193cd3605887af11ded36494"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("947dc8ccc40661a4884f2a750ba04a81ac5ba6708697c59461aa9f518e03895c"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("37f15be66359d80b9f611e64efcf3869307c7f28216242e99de5fad4bbaac85d"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("edafc2cc1d6e232efb52ef3fb6c5ce3fae6bf65ec1327738832bf72a7a78b6ba"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("e4aa267978b48e0764e62603044c0db57d084cbfe378dd0c5f35e919affcc593"),
    ),
    (
        "resolve.zkr",
        digest!("ecc34946284eb02d1e119ef0878ae65ba5e855d6e0b5db4e462a694007b2a0f4"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("3c7b9195e051f01d9dc21d96a1dd26c7035bc225511a715cf8c7ba83f8df7687"),
    ),
    (
        "union.zkr",
        digest!("44bfa51c5030508d7eddc1b1489145a6e519842f7283098a17f13fe9113497dc"),
    ),
];
