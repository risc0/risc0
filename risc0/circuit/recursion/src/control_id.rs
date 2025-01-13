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
    digest!("2fd3c00a3359de45f4c8964c8dda4f706fbd8d57e2af5b190c554c668977bd41"), // recursion lift_rv32im_v2_14.zkr
    digest!("b3a7d910d36adf5d2bd4a409c0e4352a6581492ad45a693ad5c48a4eda3b606d"), // recursion lift_rv32im_v2_15.zkr
    digest!("cda166366c82e16e101bd439af418e50149462447b162a1c0f11921449d5784f"), // recursion lift_rv32im_v2_16.zkr
    digest!("cfc4505c8734ae62b7178a643f30530c9498517341c2ff1ab30b80221a0ae26f"), // recursion lift_rv32im_v2_17.zkr
    digest!("e0abee492fc65a59cd51ee0a4308663407b0e06cb9864f3268dfb63d53649d4a"), // recursion lift_rv32im_v2_18.zkr
    digest!("8599373e9159d328dcc78f4ba34bd81f6b514604e6d6ec6f53e7ed1f55c30566"), // recursion lift_rv32im_v2_19.zkr
    digest!("9c44ee592e594b25cd4aac120018c413d7c4846085a76a5c7069576cec51281c"), // recursion lift_rv32im_v2_20.zkr
    digest!("59c57e00a6bfa665cbfd6f4709fc476283042042f0064f4c0298cd11302fb83a"), // recursion lift_rv32im_v2_21.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("1e116c1a1d135612aa89444ad19fc3489c93b8653196256f6a2d976de4428951");

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
        digest!("2fd3c00a3359de45f4c8964c8dda4f706fbd8d57e2af5b190c554c668977bd41"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("b3a7d910d36adf5d2bd4a409c0e4352a6581492ad45a693ad5c48a4eda3b606d"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("cda166366c82e16e101bd439af418e50149462447b162a1c0f11921449d5784f"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("cfc4505c8734ae62b7178a643f30530c9498517341c2ff1ab30b80221a0ae26f"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("e0abee492fc65a59cd51ee0a4308663407b0e06cb9864f3268dfb63d53649d4a"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("8599373e9159d328dcc78f4ba34bd81f6b514604e6d6ec6f53e7ed1f55c30566"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("9c44ee592e594b25cd4aac120018c413d7c4846085a76a5c7069576cec51281c"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("59c57e00a6bfa665cbfd6f4709fc476283042042f0064f4c0298cd11302fb83a"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("15a9613592b1994cd13e961eea109d69bc9ffa271bcb42680291b43480b50c00"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("81dced6ffdd1c10e6f50512bb5a67627bb3b4d6e7f39f167358511674e0ac13f"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("55a49338a188912268eda807dd4cf563bee14b20f455d4368a323f6aeb88ec60"),
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
        digest!("73df356afb836e7de7e73667e79795d13c477f87dc53e007326f6034f28e973d"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("af61a74dcc03575ff0437f2d3efe9cf53717d6913666e28f62d7bd9a477bf6d2"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("df365ae2190da15083f2838c6e01a846a75ede7501bdde8f0c958e586de10ae0"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("8e683a04df3720de4212f2723f7ad65eddeb548a56f3ddca1e4b07ec1c80cd7d"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("e56a7d692c56653c1c3989c5f13d3ef4476d28968382faeda45100cf1d249d37"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("532b6ffff06963c8f9814eed72fd6f72ada2fe5b17a06b09a0635f173ce40ec0"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("065ebbf0008bb94b75620bb52c222363b6783b305104d23bbab6e6c19e95d122"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("9776610ff5a6cb224c5a83d305f5ad3ae75cc727eacc9a524462a6cafa68c073"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("a9d9b966ea9b382c9540f43ba4a4ab6b2f7bc0a0df54b0612939ccd7142b450f"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("f5867328bbc7838bcce17a7f751857e89ac9802799483dcc545951ca68fcecd8"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("01ba967233f3b1dc1345f8715cb1be9710a920d8f7774724bcd0611038416c3d"),
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
