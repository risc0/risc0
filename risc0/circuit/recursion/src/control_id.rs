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
    digest!("8af493194e835b276eefc2522cf71761afdb04286bd3490577d55419049eed21"), // recursion lift_rv32im_v2_14.zkr
    digest!("ff455665b3743b2e4ec959674cfec4064fa54420ef0f6d38a601e85a841c3a73"), // recursion lift_rv32im_v2_15.zkr
    digest!("94a836188680865ff490ae12c140ec1c3a462c67203eda37f3ac6720d680a862"), // recursion lift_rv32im_v2_16.zkr
    digest!("b8c3e64be7662b1c9fc04d65dc276b1a5402b66a657fca4486450417b517a96e"), // recursion lift_rv32im_v2_17.zkr
    digest!("7768ce5e55c6e0427962342cc0c4cd43b359da5187d65465317c8c065357cd1d"), // recursion lift_rv32im_v2_18.zkr
    digest!("cdfd5d3007f57a1836f83c351fbb3d0f7af43050f5f6a06296f9ba25b516eb69"), // recursion lift_rv32im_v2_19.zkr
    digest!("14eb825f500342317158942d328a745e9dda2043b5bc27248f726e57effe2d23"), // recursion lift_rv32im_v2_20.zkr
    digest!("d3286f768d13864fa7cc921a25ead7536d09d56ad304a9635c3fa60f511eea62"), // recursion lift_rv32im_v2_21.zkr
    digest!("5e37cb58440474617b5beb2e1f3e7472d76a5e7572bb4660896d1074dfa7905d"), // recursion lift_rv32im_v2_22.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("884389273e128b32475b334dec75ee619b77cb33d41c332021fe7e44c746ee60");

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
        digest!("8af493194e835b276eefc2522cf71761afdb04286bd3490577d55419049eed21"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("ff455665b3743b2e4ec959674cfec4064fa54420ef0f6d38a601e85a841c3a73"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("94a836188680865ff490ae12c140ec1c3a462c67203eda37f3ac6720d680a862"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("b8c3e64be7662b1c9fc04d65dc276b1a5402b66a657fca4486450417b517a96e"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("7768ce5e55c6e0427962342cc0c4cd43b359da5187d65465317c8c065357cd1d"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("cdfd5d3007f57a1836f83c351fbb3d0f7af43050f5f6a06296f9ba25b516eb69"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("14eb825f500342317158942d328a745e9dda2043b5bc27248f726e57effe2d23"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("d3286f768d13864fa7cc921a25ead7536d09d56ad304a9635c3fa60f511eea62"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("5e37cb58440474617b5beb2e1f3e7472d76a5e7572bb4660896d1074dfa7905d"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("387a9e1a4752e35bbcc27a05c9102713fd6e42728f1bae74bb21d9054a87cc08"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("60c7632be5c98c38b567522947c03a1048882d2beeba175b63060351486e670d"),
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
        digest!("d60c25f02824db9fc7bdcecdc4d431d2d22b65eba7948825948ae1bc92d60946"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("ef84c7599ba1c513dc60370fcf10f0ad97a1849f92e455b7d6dd8359c427a187"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("99139be7bc3b8692f5c38c37529cc84915cce84f8bcd3fa7913abc7984192b2b"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("bf6c6915e4f31661e11edb487a57c2a56aa44203b9e6886a2a703a44103b2748"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("21f330b32a66a4352025edf53ac05ecf10cd5ea9db6302c755de421d4cc6589e"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("57049b4e505fa5f706847e9ba3905d93eb0198fe1b69fd19405e3ae3aa266009"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("9889b3329bd0d2c4694113b4e56790f105efb2b79effd21bfc0c3c3f41bd8066"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("9c976973ab89b8497fc830c1a0305e9f907dbbd40574482e93f6e18458ee2a87"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("a1521c33c8faf68b3db10be0aa3fbde3e100ae8ec924206529db4f1cefe70d5b"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("45da7396e10423a381e3e42c25a5fb05bb27389e8ca1c73f046de24e790c7727"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("8645ae4ab3fa5686dafa447471959834cf4c68d65af8f04cc55300497d31c197"),
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
