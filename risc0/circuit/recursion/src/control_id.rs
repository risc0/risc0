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
    digest!("512b79026fad0712ad93600ea0ea4234d0be686ea9473e4964f10914a0862c77"), // recursion lift_rv32im_v2_14.zkr
    digest!("78aabd63d877bc2806371f228fb05d0f9c8c3330bc782f62c7c6d80b4195de74"), // recursion lift_rv32im_v2_15.zkr
    digest!("0bef5e34d752b46874fb523c7d01963a37771d25a6af7c26b808fa26b8a0d815"), // recursion lift_rv32im_v2_16.zkr
    digest!("ac1a445d5babf304365232571f822725dcf71f3c8d5e7032c1bba04bad19a85e"), // recursion lift_rv32im_v2_17.zkr
    digest!("20ae3d31f954e9594cb968463ce0f823b869e3640169a561fc917226f4ca8963"), // recursion lift_rv32im_v2_18.zkr
    digest!("6f16e65efedcbf11b20b9e194e123e33aaedcd0abf1e6e5440efa263daeb375a"), // recursion lift_rv32im_v2_19.zkr
    digest!("6da21d5bc6a7534bc686b9294717f12994b13c67183c86668c62d01fcc453151"), // recursion lift_rv32im_v2_20.zkr
    digest!("60ea420126e9446430dbed5ca8b29017b6d0f31782710a1d8f8bdd3de5854714"), // recursion lift_rv32im_v2_21.zkr
    digest!("d5f05524e8bbb123f8fb1b5299413c50462cef399119953f494e57354351e844"), // recursion lift_rv32im_v2_22.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("539032186827b06719244873b17b2d4c122e2d02cfb1994fe958b2523b844576");

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
        digest!("512b79026fad0712ad93600ea0ea4234d0be686ea9473e4964f10914a0862c77"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("78aabd63d877bc2806371f228fb05d0f9c8c3330bc782f62c7c6d80b4195de74"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("0bef5e34d752b46874fb523c7d01963a37771d25a6af7c26b808fa26b8a0d815"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("ac1a445d5babf304365232571f822725dcf71f3c8d5e7032c1bba04bad19a85e"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("20ae3d31f954e9594cb968463ce0f823b869e3640169a561fc917226f4ca8963"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("6f16e65efedcbf11b20b9e194e123e33aaedcd0abf1e6e5440efa263daeb375a"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("6da21d5bc6a7534bc686b9294717f12994b13c67183c86668c62d01fcc453151"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("60ea420126e9446430dbed5ca8b29017b6d0f31782710a1d8f8bdd3de5854714"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("d5f05524e8bbb123f8fb1b5299413c50462cef399119953f494e57354351e844"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("b4459e2bc38f800ed80c956234d59a4611d0f825eae566478ac4c06a07a61c21"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("4434690c184bd542c823aa1efcf6c15cf8c83d0aafbf4f3e0552d8125eedd12a"),
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
        digest!("9515af7e33bb75efd90a1f23b12762ca36231881656b4af9fd1685a6ff4ec018"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("2b0d1276550887f6b27a423f43a4ce89abef45e056d86c8a59fa8d4593701844"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("92f3c9ee2e5e1a23d90a0e7dd52bf7b9b4f1e272613ac76e5bf6e932fa8de0ec"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("4d9c713b2dfa00271b9d4a87ef4244974a85bbb20b493cd103d75b4fcc60d411"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("7054dde82886b4a8955539872ff4784973a61782ec71348a405564a21ae3f630"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("c4abec2567fbd603ce616ecd27923f45b601d5f86cc48d1f1fb3091615afb6fd"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("1263bd3dcecab89069b91de5c4c99bdc33f853b00b50e1f35e4ffa392badd7a4"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("7380d1f06f8fb3dc3f9c7d278071fbc3bf30073229c6885d1a41c6528e90e4c7"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("793cbfc8de47a9beeb2221cac0d06470fc87e26771330561369fb518cc3b1b05"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("7bc461a9ff258b32178124b8c8f78cadac35db313b57f62d51958ec9ec37fb71"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("dc295096d9db9166e06e424445563cc4bec8fdb1a69e3b2fcee1bba75fa85883"),
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
