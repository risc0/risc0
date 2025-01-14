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

use risc0_zkp::core::digest::Digest;
use risc0_zkp::digest;

/// Smallest cycle limit, as a power of two (po2), supported as a lift program.
pub const MIN_LIFT_PO2: usize = 14;

/// Control IDs allowed in the default set of recursion programs. Includes control IDs for the base
/// set of recursion programs, and each power-of-two of the rv32im circuit, using Poseidon2.
pub const ALLOWED_CONTROL_IDS: &[Digest] = &[
    digest!("30dae603fcd283331d01105ea129ce43a0957a59b4f0013359a5642dfda0ba26"), // rv32im po2=13
    digest!("2afea6024b79430b49f60518f27d7262f2ec5b1306a9030cc2e4d955e5dc5964"), // rv32im po2=14
    digest!("8dc2760e1e24082cb66c83470c24a8017e95ce4d5eab170522f783418d545e72"), // rv32im po2=15
    digest!("35feaa4eebbefd45b0a36a350671c82154f90c660389ed3a8ff7bd2a30805973"), // rv32im po2=16
    digest!("7436486fdf9a7d3a3f8a03263bc7541a3c173c2ab5d2eb2c53939d0243dc0d16"), // rv32im po2=17
    digest!("3abdc115ddf6af1977863c29c0f2b91f8c0c2a1c35e82158104b651f6a07a816"), // rv32im po2=18
    digest!("17d75c070f373f333bbbaf33a688bb74fc05670435cd5d6378d37b608448e300"), // rv32im po2=19
    digest!("f3cf1217485c403cea526b1e52e70835c31bdc6e3016ee12916f6c6561fc0977"), // rv32im po2=20
    digest!("4043ce1426811d4f0e6a9c27256d052513c95739e9b80c74f628f313c739b75c"), // rv32im po2=21
    digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"), // recursion identity.zkr
    digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"), // recursion join.zkr
    digest!("2f609032975d7931e9d569484cdb5c1e8758af6f6d24c91968e8171b4e48652a"), // recursion lift_14.zkr
    digest!("53b94f649b8fef3283c730425bf9be1618b82a76e270bd44b351f16eda68d00d"), // recursion lift_15.zkr
    digest!("919c664b394f6b3e7500d151204ede5e6afd4d1a3724925ca341971e93cffc46"), // recursion lift_16.zkr
    digest!("bc52395cbfbbdc6783e19443161c0a559496a017aeb6370232a5313125032175"), // recursion lift_17.zkr
    digest!("442f0a4cef957609ab5ee447a279351e6dc212734cbc6e3e5bbf8b086f1a7818"), // recursion lift_18.zkr
    digest!("d621555070b62e383b8e16511aa8b244cb442656c5c396302fe75816c477b902"), // recursion lift_19.zkr
    digest!("66f12c252c978962a100976c69ea6a4dfb2b4a2a504d6d5c60fb8e2fff6f4b61"), // recursion lift_20.zkr
    digest!("88a6322eccb8f141087c48174211df1d0e071603ebfefb69f0099836569e384a"), // recursion lift_21.zkr
    digest!("389f762ad8de0008fd9dd0317854321cb671cf33f6918233b4fce02766385814"), // recursion lift_rv32im_v2_14.zkr
    digest!("edfbe875e0794d18f210e55cf417c120bff7451f88ae21761026417329ef5a48"), // recursion lift_rv32im_v2_15.zkr
    digest!("1ce9b474c53ea03b49164b54061201638dbc812df6a45b403a181c2fd6ad1620"), // recursion lift_rv32im_v2_16.zkr
    digest!("4dd13e2811db420cc82646124c6db373d1f3107367f5c057073752451a786365"), // recursion lift_rv32im_v2_17.zkr
    digest!("f2facb5268d0102055be3c69b6a746106ba713334108472f80776f004f50f876"), // recursion lift_rv32im_v2_18.zkr
    digest!("18d8b94849312250b13c493abaf54705b797663e5a241f68060a39622180c21b"), // recursion lift_rv32im_v2_19.zkr
    digest!("dbb3510f153c041ad2ec94670c14aa0b683e195e77ba1709a41ae30bd668bc76"), // recursion lift_rv32im_v2_20.zkr
    digest!("86393706163b9e6e4a4d7a00a4cd08485fe4b861a8486a49628da121e6351e43"), // recursion lift_rv32im_v2_21.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("ffe166017b1ab460995b45510524c60e3756344feff2414f44cda25c33a78058");

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
        digest!("389f762ad8de0008fd9dd0317854321cb671cf33f6918233b4fce02766385814"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("edfbe875e0794d18f210e55cf417c120bff7451f88ae21761026417329ef5a48"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("1ce9b474c53ea03b49164b54061201638dbc812df6a45b403a181c2fd6ad1620"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("4dd13e2811db420cc82646124c6db373d1f3107367f5c057073752451a786365"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("f2facb5268d0102055be3c69b6a746106ba713334108472f80776f004f50f876"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("18d8b94849312250b13c493abaf54705b797663e5a241f68060a39622180c21b"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("dbb3510f153c041ad2ec94670c14aa0b683e195e77ba1709a41ae30bd668bc76"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("86393706163b9e6e4a4d7a00a4cd08485fe4b861a8486a49628da121e6351e43"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("b429735c463d7d2e81bf1661a9305b30361ccf221a62154974171f60f37d396d"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("e58e4c240ea1ea1d57625d33737cb675968b60175752e1061603ab27202e962d"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("e74f3107acb32a0c433b2b15e788a22653eee412a21f0d4388ca2a1bc760f64d"),
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
        digest!("26eb18409abe9fc5a7d731536180296035e49c5e3224bdaa2022ac202aad00ba"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("04e30be04917cbba10da7cd1f6e093f1b9616277fc3217482e96d9c8eba86af7"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("162ab46d469335997e47b5ff4b5422959feb85597e0448d911b2ef3373ec776c"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("9a6fe02fbe22a7ebb23077dbae25066171097bc730e1c6fd25dd443bf9879946"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("2db2b20129795e3a5de7377e868f5093bc89521ed24c3c79d422199505cdc628"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("d33d6fd01d4b185918842e8bd791a884f21aa53baa148c4a31632c6a8685f83a"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("6a3282de57e30ba4b68cbb97219bd971fa6cb399477350b4a115f3c7d91e7a1e"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("a08a094177b4593d928b543bea879be6d1f651043f5d04a1f2e47746ff0bdfa2"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("b74809f70d7aceda4e1af64bc37aa3b6311045bac2a2ecfc7cfdf43046ac1ca9"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("4b1a5eaf6b1609ef4a6f4d2d4d943a337b80c27f32b673795fde7169011526c4"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("95d66f644f20e4fd8e04c41f59c9214a5e9302b0292d02a00a56331964b8eaae"),
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
