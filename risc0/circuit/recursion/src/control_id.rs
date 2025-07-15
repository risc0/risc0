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
    digest!("7d40e30f18c33757a1a06613d779bf32415a9a577abfe66b4be5a71352ce5011"), // recursion lift_rv32im_v2_14.zkr
    digest!("86dfe305f9858148efda7f10c7614762b3ba603519d92f2b91c55c220b63e952"), // recursion lift_rv32im_v2_15.zkr
    digest!("2f61ee3922aa323fb59c7a0268bda909df6c08070f4cf466e5a3440e299a7d69"), // recursion lift_rv32im_v2_16.zkr
    digest!("35e2b36e7e7b953c18016969cf0aab642f21df617616e450e4de9a778b252025"), // recursion lift_rv32im_v2_17.zkr
    digest!("6d26ea13c4575577e44eeb371656e60f2c4d6f187ccd15555b29f1062f6af71e"), // recursion lift_rv32im_v2_18.zkr
    digest!("b712f9541933da35f90d0a5cf3bd95040528056ff9efa203390a224ae63c5232"), // recursion lift_rv32im_v2_19.zkr
    digest!("5b35585d98a08c611375e365c0fee5401cb8aa1a3a8dbd744b177e0f6dee4837"), // recursion lift_rv32im_v2_20.zkr
    digest!("0d74121afe5e3511242dee572bec7c50b49fd6031c20052d714d0903688d3f56"), // recursion lift_rv32im_v2_21.zkr
    digest!("a7d8d52e8ad8ce18c44c3b5e86b80a1f1617ce76dc6a396731e292407322ad01"), // recursion lift_rv32im_v2_22.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("b0a05c0793825d0f306e441e840d563102977c0b12f4de28b52bed72ff44be55");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("c07a65145c3cb48b6101962ea607a4dd93c753bb26975cb47feb00d3666e4404");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 43] = [
    (
        "identity.zkr",
        digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"),
    ),
    (
        "join.zkr",
        digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"),
    ),
    (
        "join_povw.zkr",
        digest!("a7ae21778918eb56c573d96c0fa503025fa50e0aa81b292b782e7a3daf96491f"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("bd5e9c75a894a020bfa1a50c1d430750345df43d0c3a4a138b80d54d0857c02d"),
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
        digest!("7d40e30f18c33757a1a06613d779bf32415a9a577abfe66b4be5a71352ce5011"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("86dfe305f9858148efda7f10c7614762b3ba603519d92f2b91c55c220b63e952"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("2f61ee3922aa323fb59c7a0268bda909df6c08070f4cf466e5a3440e299a7d69"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("35e2b36e7e7b953c18016969cf0aab642f21df617616e450e4de9a778b252025"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("6d26ea13c4575577e44eeb371656e60f2c4d6f187ccd15555b29f1062f6af71e"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("b712f9541933da35f90d0a5cf3bd95040528056ff9efa203390a224ae63c5232"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("5b35585d98a08c611375e365c0fee5401cb8aa1a3a8dbd744b177e0f6dee4837"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("0d74121afe5e3511242dee572bec7c50b49fd6031c20052d714d0903688d3f56"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("a7d8d52e8ad8ce18c44c3b5e86b80a1f1617ce76dc6a396731e292407322ad01"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("31c89f6ba1e3d8676f9a3a457794aa4654028474a3d92a0585b0607557ac0273"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("bc9ec8079125bd1c20a0c03b2ab80e2593285f693e855312cd3b0c304ce0984c"),
    ),
    (
        "lift_rv32im_v2_povw_14.zkr",
        digest!("6e2af04e832de33b785fc8299502b355c649413955b121327e7edf60bf78080f"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("c496a26f27da3c51e681597081c4b959567f6324a950e716010b884c3718f005"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("aaf2d6282a21a84db50cae4add7b0d0a9023500531ba834feb49b465a942d420"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("3e7c5948f4e88d77b7b825081c052a24a1b60a68a5da723cc02ee9018d780c30"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("f2c09e5227ed6e0b51749f531e0f894a6be23676b98d8e0b7074693b65413918"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("cda0fd54f21f1b646bcbbb5a7b900c0f02119d0bd572d816380a336a93ab0432"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("747a4b09ffa38956c230345c51883e4b0f046048bb31a86587177f0b41fd9516"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("62d0f532f011bd13589f335054a88f745d3a321f1d10c051bafbd80c513bd717"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("f71b662a40080e6637116f2f8b0f0e70bc055b778f09112a3b9073766ec31f1e"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("a7ac94682f178535adbe364ee36b2c10a20558101b19ae1e92ad0754137c815a"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("d9d7ec30966c2067f2791b020b3b9b4f861eaf25a2fbd1423935f46574d44967"),
    ),
    (
        "resolve.zkr",
        digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"),
    ),
    (
        "resolve_povw.zkr",
        digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"),
    ),
    (
        "resolve_unwrap_povw.zkr",
        digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("6d55102aa73086602f7039412200124bdec91f0c497c606f9aa09040403e030b"),
    ),
    (
        "union.zkr",
        digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"),
    ),
];

/// Control IDs for included recursion programs (ZKRs), using SHA-256.
pub const SHA256_CONTROL_IDS: [(&str, Digest); 43] = [
    (
        "identity.zkr",
        digest!("d7ecd18c7d06fc468166147cf20869aa10f32e097a0c166146a5a62dd2d975ea"),
    ),
    (
        "join.zkr",
        digest!("dc44002689aa7852410ad1c840388d66b8b9a2f6d0c4fb6b3ac6ec2ea17d9855"),
    ),
    (
        "join_povw.zkr",
        digest!("e243306b436cb2d2f916a8fffd69c319655b2c2444221847802a990c2bbcef30"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("b272dc8580e6d0f6d30c72f66c5a939f43b3a39179744297e8d7dc79f2dbccf1"),
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
        digest!("05e278dcb9a90117f27096335bbca93f0a1c39a146ef7f0ff3e24788371c9761"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("7e38d2117f64c78e27159a356dda2a0b2de70d530a866f6e4c923342149d7956"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("0737dbaf9346383bb66795aa9bc5a42472712660c28612af149ddd58271695d9"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("80a3e859059f483e2bc4e3eeac4eb9848e7ea5e0c8620398e7d57ae755477024"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("e48862f9cafea1e66e47e1abb613bfa8a72d4825efd9b5d2424d476ecfe236b8"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("60f23f4f8d16cf61c552a55aeb630929b5d4e35653839a0d4c63218859a0c06e"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("e00a7eb1edc3124384405a596d1584c55e07c24fd285643bcc6e79be9caa7a86"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("dac9f70bf0f3f5a8d05e89d9f9628a4182c40e63f423a36642e9116ee77d158b"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("a782f2c9e15371f2ec7b4eb084aea5a41eae636e4c468df7aab45206113852a6"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("e8a5ebe9dba0b85cfdebba2bdefd8389be319a9b56c7e15c28a2420fdbece02f"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("498e5c6db1d5528643b8cdb3a61ef795f8c98a15ae86c5af2ccc43c88ba50ccb"),
    ),
    (
        "lift_rv32im_v2_povw_14.zkr",
        digest!("b0118c13952b57cd9568f96c4ed226aa826ab63b6f0cffb5cd6055388e267e1b"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("715f48d5c3b6d67996b342d1b47c4da0bd29187ac1d707f1d0a5a1e88a3283fb"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("6100434edfdc10ca9629f5f06150ae8ccc5b986c1fcce66ac8dc32b699ba6250"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("1db89aa746158100c3b933acc9de615069d3145174eecd64aff622526bc7f48a"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("0bdf75e033f6a0294a40eb9ff70fff9dd587db35f015dd99837eb59be13daac9"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("c67476f0b343c292a665674dde4d20ca13011f9a125c285fbb1ff24f866e1b27"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("d172513e3b9a0fcd47cb285aaca258918959e3670f973ac30d6051d4244c469b"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("bfdf856010d8aafe163bd415b519ffc3f04d687f1c7c45550624a05fcfa4a570"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("b434136db2141f55d49d387dcf6a95b4667813e2612be035a9636bc7801b0a2c"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("8d841f1590aabf7ed2f85d149ccd598dd5734d5bb194bfbbc34965395ff92f2e"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("101de8081fae0fe3ad86288fc276b22222afda55e4c2413ada849ee01087be8e"),
    ),
    (
        "resolve.zkr",
        digest!("ecc34946284eb02d1e119ef0878ae65ba5e855d6e0b5db4e462a694007b2a0f4"),
    ),
    (
        "resolve_povw.zkr",
        digest!("51fe537675d705e759c0cb0862f0cb7c5d70ce3dc483efc3cb1646c2b6f0cba3"),
    ),
    (
        "resolve_unwrap_povw.zkr",
        digest!("1332cc7a1cb90467d849db4ebc4fcc201f81fe0a2ab06d6a398d76b7dd8aa694"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("3c7b9195e051f01d9dc21d96a1dd26c7035bc225511a715cf8c7ba83f8df7687"),
    ),
    (
        "union.zkr",
        digest!("44bfa51c5030508d7eddc1b1489145a6e519842f7283098a17f13fe9113497dc"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("3b5de70ddecc2fabcd3b9b9150ff64e7fc084ecb80f97cac2f9ee11e326087d1"),
    ),
];
