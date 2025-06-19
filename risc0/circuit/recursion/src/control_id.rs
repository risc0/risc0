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
    digest!("4ab5c83addc77519371b254430287c349291a249b87ee21b74080e393d06822f"), // recursion lift_rv32im_v2_14.zkr
    digest!("6d40a7332a20f1497652292af043a5138903793bf392311879cf9e4a6b36e23f"), // recursion lift_rv32im_v2_15.zkr
    digest!("b1178d0cad0cf5037a321c74983f471540464e3bbb0e740f142d954bb6268630"), // recursion lift_rv32im_v2_16.zkr
    digest!("d05fa43ccdfd4e3c8c8f3e4a6e321a6374b39152791a8e1ff003732941035229"), // recursion lift_rv32im_v2_17.zkr
    digest!("60287d75cd18c0028bd4704698d744525a593b523cd8b34ec1708241c0afc12e"), // recursion lift_rv32im_v2_18.zkr
    digest!("d824054b00fe4d14d35c77681f900013ceddf411468a895329138853d16df344"), // recursion lift_rv32im_v2_19.zkr
    digest!("296f511b002ae2433be7ef332b11963650c34a06e5e22a01326c87687f342a6c"), // recursion lift_rv32im_v2_20.zkr
    digest!("c4995e0bcee5bc555b0ec93a792b5c0836ca30385c67f214a667752b6dd48169"), // recursion lift_rv32im_v2_21.zkr
    digest!("f43c552f907e9555b9496f1281774364e2da7154cf803967b57b1566bbd99d54"), // recursion lift_rv32im_v2_22.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("89a1d401f47dce14dbfffa17aa6dbb64363b984ab221e35cdb710e470eaa0b29");

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
        digest!("4ab5c83addc77519371b254430287c349291a249b87ee21b74080e393d06822f"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("6d40a7332a20f1497652292af043a5138903793bf392311879cf9e4a6b36e23f"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("b1178d0cad0cf5037a321c74983f471540464e3bbb0e740f142d954bb6268630"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("d05fa43ccdfd4e3c8c8f3e4a6e321a6374b39152791a8e1ff003732941035229"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("60287d75cd18c0028bd4704698d744525a593b523cd8b34ec1708241c0afc12e"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("d824054b00fe4d14d35c77681f900013ceddf411468a895329138853d16df344"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("296f511b002ae2433be7ef332b11963650c34a06e5e22a01326c87687f342a6c"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("c4995e0bcee5bc555b0ec93a792b5c0836ca30385c67f214a667752b6dd48169"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("f43c552f907e9555b9496f1281774364e2da7154cf803967b57b1566bbd99d54"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("460c3c1f0773da4dd9ab985bfb2bb615fcd0664de0c8e14b33522c3008396e46"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("31697d442c7cb45335e618136e154a6a4aeceb0811374e69fc40a96199124d3a"),
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
        digest!("8c32e3da286503e0734481b70e31afa98aad1e36fc1c7f48f74f02ff88455463"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("ca696f55644c8925a0883c128b92fdc3035a83c8e5f5b45b4362f6b272508d5f"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("2f927a6c9006f7c43cd853b1eeca2dad2b334e617727ad6473e90f71cbcb9fa8"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("98308ed6ff5305300b6a4ccd758ec7b29ba25aafec4056a7dc0aad297d017b94"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("efdff8c7b77bf6e587c238d7645f5f499d65af163985c146f8811f3ed1a01d0b"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("7fcc43e17c25e77a51384bac58efe46e017ca25c3e1d64fbe66629edb212f854"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("a765aaa0e59dd692c338661383f6d033d145176c463f3dabf03ee81beb5f874a"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("790efa4a129a1db5a76d7223327f42cc00e18dc9a04d0919aa238a5e69096599"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("9c1af82842611a71dec26ad6eb7c76ff5abd681668f53ab25ad9a1f9e631d757"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("b337e6dcec6b4cb5e5a262c5116ca48587bf635a6e1203185227a9e3fd338851"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("3f119df29ad5e179f7ec400ebb9f14bbac321d3984542cacb3ffab43390a5c40"),
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
