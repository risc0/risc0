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
    digest!("30dae603fcd283331d01105ea129ce43a0957a59b4f0013359a5642dfda0ba26"), // rv32im po2=13
    digest!("2afea6024b79430b49f60518f27d7262f2ec5b1306a9030cc2e4d955e5dc5964"), // rv32im po2=14
    digest!("8dc2760e1e24082cb66c83470c24a8017e95ce4d5eab170522f783418d545e72"), // rv32im po2=15
    digest!("35feaa4eebbefd45b0a36a350671c82154f90c660389ed3a8ff7bd2a30805973"), // rv32im po2=16
    digest!("7436486fdf9a7d3a3f8a03263bc7541a3c173c2ab5d2eb2c53939d0243dc0d16"), // rv32im po2=17
    digest!("3abdc115ddf6af1977863c29c0f2b91f8c0c2a1c35e82158104b651f6a07a816"), // rv32im po2=18
    digest!("17d75c070f373f333bbbaf33a688bb74fc05670435cd5d6378d37b608448e300"), // rv32im po2=19
    digest!("f3cf1217485c403cea526b1e52e70835c31bdc6e3016ee12916f6c6561fc0977"), // rv32im po2=20
    digest!("4043ce1426811d4f0e6a9c27256d052513c95739e9b80c74f628f313c739b75c"), // rv32im po2=21
    digest!("b4edfc3f2c49f10285bcdc7493eb81063959820a59569356fb73b62c1586e01f"), // rv32im po2=22
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
    digest!("bb71f46d8931c80fbcf10f3b5314b93cb7b8061d4658c55000c2c26967b58a0c"), // recursion lift_22.zkr
    digest!("a084cf6b05d2c607eebb6f57d109551657266167e2afc06d64cd34490c336b31"), // recursion lift_rv32im_v2_14.zkr
    digest!("89230c25d5ccea29f599523d7699a943346f3f6f1420e0649578e12ab75cb41c"), // recursion lift_rv32im_v2_15.zkr
    digest!("caaf630aaf8d560f95d1c93ade9180590bcd0f63fbd93330feb7ca0d301dac1f"), // recursion lift_rv32im_v2_16.zkr
    digest!("c2419c4db04b36562c3e1706b3e98c58d6edd4235159345b612a5d06ca97733f"), // recursion lift_rv32im_v2_17.zkr
    digest!("9a5ce50c4ae76843ea9c4a31253cfe50f04e8065b3972a00f013a93327cb091c"), // recursion lift_rv32im_v2_18.zkr
    digest!("67a1685c89c230360655a6435984b741fe4be423cb165a6a257e596716230b4d"), // recursion lift_rv32im_v2_19.zkr
    digest!("fef8d86aa122b71a47d7b2561b77f123b1757508992e725e96485739545a530b"), // recursion lift_rv32im_v2_20.zkr
    digest!("901415588ac942590f086941459d201f88cb881416d4936b3441010e507faf23"), // recursion lift_rv32im_v2_21.zkr
    digest!("5a11e25b7721da3ef256734f1334ea1d987f922a2c0c713ffbd6b3399a6d0004"), // recursion lift_rv32im_v2_22.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("91d639615549c55dc491e60a5c3d9d301c364549c3372023fddbf406202af45b");

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
        digest!("a084cf6b05d2c607eebb6f57d109551657266167e2afc06d64cd34490c336b31"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("89230c25d5ccea29f599523d7699a943346f3f6f1420e0649578e12ab75cb41c"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("caaf630aaf8d560f95d1c93ade9180590bcd0f63fbd93330feb7ca0d301dac1f"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("c2419c4db04b36562c3e1706b3e98c58d6edd4235159345b612a5d06ca97733f"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("9a5ce50c4ae76843ea9c4a31253cfe50f04e8065b3972a00f013a93327cb091c"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("67a1685c89c230360655a6435984b741fe4be423cb165a6a257e596716230b4d"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("fef8d86aa122b71a47d7b2561b77f123b1757508992e725e96485739545a530b"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("901415588ac942590f086941459d201f88cb881416d4936b3441010e507faf23"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("5a11e25b7721da3ef256734f1334ea1d987f922a2c0c713ffbd6b3399a6d0004"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("4bd85f4a0c60cd7742265425df366c07335ecb4eb1b1c369bf682074c3a15473"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("aecb0c726796da462b5ca70e95512628c9ec6f5a0e4fd3545258894ba7cd981c"),
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
        digest!("6b704971d04c50e58f960006ce87c5395f54657f298fe55410529c43072f5088"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("dcd475c66b1fc56d3f170edd5b94b7c0109884a5537eb4bd165c80ab02595c76"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("e3a4ddf3734c039a4469670e9696587daff2a53b9be56a65a6ea69cd9b98a59e"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("d3245335a6d19ca0ba405199d8a22fb4469c72ae160ad9022028082b61f91837"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("70f500949ced73a30c2b59b5cf8717c77ec4cd8f48697d96255705eea143cd6f"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("792447c6b89384bee730b3d63bac0c46d91a9ec6f8c8b20ef229ca6b74f86dcd"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("e4fc9a584b0b712885ab1a166d5c1b4ea831f696b36be4004a21c77839aa729e"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("d800c50f2521f95e3943dcd274f8d958be76e5b2127cee333e8d190b3a4fcd29"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("f33101e9ad85431d33a4d1457656a57094bd9591c32df4bef3b6216499743b02"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("e468c1d87449ea11137779c874a2837ba148f86ef7708962d3949e1240c306a9"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("4c4e377c0d1f65c68acf92627fc36c7dc64ac185a1ea22cecd5ddd1269de9d87"),
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
