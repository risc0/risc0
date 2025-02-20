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
    digest!("77353a3b1083b23f5e8d5d6477516154048a5d01b93fc1623616626e92ed574d"), // recursion lift_rv32im_v2_14.zkr
    digest!("14ef58514513ca4e0bec6c1fe7bbba66c1d8c10643ca19297e006f10b995db27"), // recursion lift_rv32im_v2_15.zkr
    digest!("583eb71236f2fe1c62eef0087834c619c8de4a0ebf102e207719a168ce79ae19"), // recursion lift_rv32im_v2_16.zkr
    digest!("e19d882607c3631e5cf76a207a6ffa3b1338b2241c66a456b12a0559671d6322"), // recursion lift_rv32im_v2_17.zkr
    digest!("e4d5675340ae9d65d3b35c4048c62d012cdd5a3d1b4e011e0ad91d64e556f566"), // recursion lift_rv32im_v2_18.zkr
    digest!("b60edb5b2fac8536e2a0240dce47d514bccf8e0267320631a2e11102bbf5bc59"), // recursion lift_rv32im_v2_19.zkr
    digest!("dc1d6969cee6e610703a486f6404f4120ff90d427961cd0652424852589a634d"), // recursion lift_rv32im_v2_20.zkr
    digest!("1eb38c0745858056f305804b8abbb419083280661bc0d93ddbb4fa3167cb4103"), // recursion lift_rv32im_v2_21.zkr
    digest!("f45a86712afefd2f0d680e0e8594e944d63d0f4903fe4e4de63b0b4e9198103e"), // recursion lift_rv32im_v2_22.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("1193543e87956d31c39a87145e84332461dab71dc450b74507381f2d18e43447");

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
        digest!("77353a3b1083b23f5e8d5d6477516154048a5d01b93fc1623616626e92ed574d"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("14ef58514513ca4e0bec6c1fe7bbba66c1d8c10643ca19297e006f10b995db27"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("583eb71236f2fe1c62eef0087834c619c8de4a0ebf102e207719a168ce79ae19"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("e19d882607c3631e5cf76a207a6ffa3b1338b2241c66a456b12a0559671d6322"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("e4d5675340ae9d65d3b35c4048c62d012cdd5a3d1b4e011e0ad91d64e556f566"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("b60edb5b2fac8536e2a0240dce47d514bccf8e0267320631a2e11102bbf5bc59"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("dc1d6969cee6e610703a486f6404f4120ff90d427961cd0652424852589a634d"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("1eb38c0745858056f305804b8abbb419083280661bc0d93ddbb4fa3167cb4103"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("f45a86712afefd2f0d680e0e8594e944d63d0f4903fe4e4de63b0b4e9198103e"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("b854f4267540e83358291a1a23dc016a1bd289087ff56f298cf59e2aa65a332a"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("91d1b0623e592a1d673f46632681d4373723db2cd73d8b4833b709154912665b"),
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
        digest!("281635b321be66cef070c16f765444347af73932d405712cad4f64c3ad7dae97"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("cd41be230ef338997d781ee62bb401e58ca35f8c1d5162721fc3d679055baad6"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("dfb722b49eaeddf40a89e0219fdb1b02dc26181a13234aa087b349d23a511459"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("c160715460bdde7b7dd56247a5327a823635ff61b94599e5fc2341b5b3f8d3b4"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("e731cd79b262a984b6f650a850a3e8a0275d2c3cefe9d0ccd5ccad9e0bf3e293"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("f714aea4bcacc4384cb4483e57d11f34a99327e866da5dfe113e8ccb903280a1"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("c37ab45733c8da1cd2c0a9a84a1cf5bbcb52051dba389094ebce0f58a11eded9"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("95f7ee991026454064d2df73e7174931209519fd3f56be0bc189108ab6f2e75c"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("7eae3cb05770e82684ef33b25a389804efd62a0a0015e78439e0123cc98bfea2"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("03f1e007bc7c459bcf19105199f803b510d49f57a277f5296b30f01253527836"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("b74e114afe82034a01eaf6e5d5144bcf7acab0bee3d7295be14dc11d102e494a"),
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
