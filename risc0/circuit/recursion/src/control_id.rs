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
    digest!("85da7a229d849c2df4b4981b7832d454aafe861565c09077dfe3b370a0df6e58"), // recursion lift_rv32im_v2_14.zkr
    digest!("e898f63e57c60550cf8a4538ac128b459205bf1932ad8626cf8d3a69a643de3a"), // recursion lift_rv32im_v2_15.zkr
    digest!("1200206540c0875eda6a093da5f95f3ae39876110b5a2a13bb78122414cd4c47"), // recursion lift_rv32im_v2_16.zkr
    digest!("65886d687ac8776f3174295d0cf6382d24fdfd6040070d05eeadb604325b1d0d"), // recursion lift_rv32im_v2_17.zkr
    digest!("2e92d814ded6f733640e8f499cc8ec4446d0b51ae5410964e0cefa278bab3176"), // recursion lift_rv32im_v2_18.zkr
    digest!("6defb6501a5dd05d6858733427d61010d59201341cc93c1138345137c55a372c"), // recursion lift_rv32im_v2_19.zkr
    digest!("a207f7229e901538c003ed4a05c7895fb2b22611de5add35ba988450b2537b5d"), // recursion lift_rv32im_v2_20.zkr
    digest!("5ab2507285106c5b3485a61a36dea7127ba29528ccca18040c6ba05da61a8d1f"), // recursion lift_rv32im_v2_21.zkr
    digest!("00bba10ac0db121f677243735a888162e909c14b3567a11d5e5b2961080d1b2b"), // recursion lift_rv32im_v2_22.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("ce52bf56033842021af3cf6db8a50d1b7535c125a34f1a22c6fdcf002c5a1529");

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
        digest!("85da7a229d849c2df4b4981b7832d454aafe861565c09077dfe3b370a0df6e58"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("e898f63e57c60550cf8a4538ac128b459205bf1932ad8626cf8d3a69a643de3a"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("1200206540c0875eda6a093da5f95f3ae39876110b5a2a13bb78122414cd4c47"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("65886d687ac8776f3174295d0cf6382d24fdfd6040070d05eeadb604325b1d0d"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("2e92d814ded6f733640e8f499cc8ec4446d0b51ae5410964e0cefa278bab3176"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("6defb6501a5dd05d6858733427d61010d59201341cc93c1138345137c55a372c"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("a207f7229e901538c003ed4a05c7895fb2b22611de5add35ba988450b2537b5d"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("5ab2507285106c5b3485a61a36dea7127ba29528ccca18040c6ba05da61a8d1f"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("00bba10ac0db121f677243735a888162e909c14b3567a11d5e5b2961080d1b2b"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("b0ff641317b165613645116689599952631ed33ed94de72217e8ca2ec271b853"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("3b3a722b8e6fd90cc0649d17e05744175afbe60fe3543f77a947e9678418bc29"),
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
        digest!("8fdb6632219b902a4e290590a6b5d18cba98aca1eb1dc9d51afaf233024fa716"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("d1c5699afe0dbf843cd750ba8adce426700afe6322cc9f795339f55803fd5f1b"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("ac56de3ed1f29daddd44698b8ce4f6024db0ac0abdf391a7dcfbab7e4ff687d9"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("7bac7a1f161c8789ee0653422ec6b791e9303a925a9754af9496582c3fa4e11c"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("d7c7f79fe812bdec12e27795d892825dbb307036bc6296326bc38b029af89945"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("550660dec08c81a8b076f2fcd9bf92a3ac5e2943562f96922be27bbecc48674c"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("9871771f56c6bea04adfe958c7d66aae8e81427b6719d5ee00b2f309d8a3f8ef"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("32b412915501d9df535e3de25e3f4b5cca78efc647d288a914b752955c27489a"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("1956d254dd700164d267aee2c55f4e953a34834ca37c0f7b2e345403371a9fc7"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("11c481d4ec58516eed75460dd44717905f5a338668cd72a52d7987a3f7710fd8"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("5a52b5f66d844a23c33d1e3e0eb3273470d574e813694792ec1138d37065415d"),
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
