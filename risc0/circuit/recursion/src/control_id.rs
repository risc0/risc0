// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkp::core::digest::Digest;
use risc0_zkp::digest;

/// Smallest cycle limit, as a power of two (po2), supported as a lift program.
pub const MIN_LIFT_PO2: usize = 12;

/// Control IDs allowed in the default set of recursion programs. Includes control IDs for the base
/// set of recursion programs, and each power-of-two of the rv32im circuit, using Poseidon2.
pub const ALLOWED_CONTROL_IDS: &[Digest] = &[
    digest!("519fc2583d0bb9327272f83996dd344e36eb902aa812f5256d745727aea8572b"), // recursion lift_rv32im_m3_20.zkr
    digest!("1dc9e10915e56e3934c3cf5295699a3ee91cf83b1994e528dcb33e2521ddc735"), // recursion lift_rv32im_m3_12.zkr
    digest!("d2be9e02e022f615208b492864050d4fe3468033fc13d27387a15d426337d60a"), // recursion lift_rv32im_m3_19.zkr
    digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"), // recursion join.zkr
    digest!("0a883f073ba39e482a840b02fc74eb0334e22b053d8b02576aaf6b744b323b2c"), // recursion lift_rv32im_m3_17.zkr
    digest!("1d460271ae5b417118b99c074a463935e2bb9b2b2874f635b7f052065d750053"), // recursion lift_rv32im_m3_21.zkr
    digest!("b2d7880d1bc44764f99e9c04e55e426fa8e54f16d5b0ec4c3aaf714431e2880e"), // recursion lift_rv32im_m3_16.zkr
    digest!("507b5f666e481453d5839867d435885c393ae017ed199229aca2d2190548a80e"), // recursion lift_rv32im_m3_18.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
    digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"), // recursion identity.zkr
    digest!("e3b4af068b71ca0ae6934b6c9dd06a2d8506c02f332e7a0361b9384ccccb8745"), // recursion lift_rv32im_m3_22.zkr
    digest!("d725883f93363a2059e4b46e29e544478c47474786b5b20ca48e6268e1e73037"), // recursion lift_rv32im_m3_14.zkr
    digest!("9dcd6d1c86fb9e1df2ed7c21651274389188706f323af804de66c3441d555e2b"), // recursion lift_rv32im_m3_13.zkr
    digest!("9e992f58330d6353926c0714c655e61a15df574f2c124a274e2cee4344863047"), // recursion lift_rv32im_m3_15.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("b7ac2a1a69bc842224f11018fb5fcd12dbdea51cfd419f3600593f0aac470473"), // recursion lift_rv32im_m3_povw_15.zkr
    digest!("faf1054e1aba702ce2ec9a673da83e18dfb086249e77ae1808a0030229a36a68"), // recursion lift_rv32im_m3_povw_20.zkr
    digest!("715d634c11044202338faa06921e623148441d29ec24746d83c8d83c3554283f"), // recursion lift_rv32im_m3_povw_18.zkr
    digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"), // recursion resolve_povw.zkr
    digest!("3ada2e0afc16f93951f09618deba99011007285295f0842f6973c809bea1594f"), // recursion lift_rv32im_m3_povw_19.zkr
    digest!("e65d1158bb0528775e3acd330df3281066abc76c33ddbd66b55b135546047d0d"), // recursion lift_rv32im_m3_povw_16.zkr
    digest!("653dce4d67204a6b1829565144937861f2a49457c941010297ac9c5f0730ad10"), // recursion lift_rv32im_m3_povw_17.zkr
    digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"), // recursion join_unwrap_povw.zkr
    digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"), // recursion join_povw.zkr
    digest!("3f2b4e59af0a863426dca46224ec2f59c3af923d6ff1b2044337a4328de3f81f"), // recursion lift_rv32im_m3_povw_12.zkr
    digest!("c62701187ef7cd1125822821c7474f479c86814a23b75669043b6f66838d9205"), // recursion lift_rv32im_m3_povw_14.zkr
    digest!("444d921ae3c4bd36dcda74080ebff12e45fc9057db46f5628524db0e8adf7f71"), // recursion lift_rv32im_m3_povw_21.zkr
    digest!("5182f230f954001a71ae843a2df0f413a56ac035f60afe7090f17d478a7c7a6a"), // recursion lift_rv32im_m3_povw_22.zkr
    digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"), // recursion unwrap_povw.zkr
    digest!("9b3faf3984fb78698e58e364a5beee4229b06843aa7acc1392f542141f6c5d2a"), // recursion lift_rv32im_m3_povw_13.zkr
    digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"), // recursion resolve_unwrap_povw.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("fe88225c801f3c4a4c98a53d833d56545c7720418be3e434ee27e14f942e0825");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("c07a65145c3cb48b6101962ea607a4dd93c753bb26975cb47feb00d3666e4404");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 36] = [
    (
        "lift_rv32im_m3_20.zkr",
        digest!("519fc2583d0bb9327272f83996dd344e36eb902aa812f5256d745727aea8572b"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("1dc9e10915e56e3934c3cf5295699a3ee91cf83b1994e528dcb33e2521ddc735"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("d2be9e02e022f615208b492864050d4fe3468033fc13d27387a15d426337d60a"),
    ),
    (
        "join.zkr",
        digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("0a883f073ba39e482a840b02fc74eb0334e22b053d8b02576aaf6b744b323b2c"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("1d460271ae5b417118b99c074a463935e2bb9b2b2874f635b7f052065d750053"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("b8e15f63db930468f3ad884a6022a7676cc4096675c7ab45c47d9d3821bac606"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("b2d7880d1bc44764f99e9c04e55e426fa8e54f16d5b0ec4c3aaf714431e2880e"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("507b5f666e481453d5839867d435885c393ae017ed199229aca2d2190548a80e"),
    ),
    (
        "union.zkr",
        digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"),
    ),
    (
        "identity.zkr",
        digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"),
    ),
    (
        "lift_rv32im_m3_22.zkr",
        digest!("e3b4af068b71ca0ae6934b6c9dd06a2d8506c02f332e7a0361b9384ccccb8745"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("d725883f93363a2059e4b46e29e544478c47474786b5b20ca48e6268e1e73037"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("9dcd6d1c86fb9e1df2ed7c21651274389188706f323af804de66c3441d555e2b"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("297af573fc28280df4aa104ea1a0322b252abf2c3299f86c101c76481ba0c52d"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("9e992f58330d6353926c0714c655e61a15df574f2c124a274e2cee4344863047"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("6d55102aa73086602f7039412200124bdec91f0c497c606f9aa09040403e030b"),
    ),
    (
        "resolve.zkr",
        digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"),
    ),
    (
        "lift_rv32im_m3_povw_15.zkr",
        digest!("b7ac2a1a69bc842224f11018fb5fcd12dbdea51cfd419f3600593f0aac470473"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("faf1054e1aba702ce2ec9a673da83e18dfb086249e77ae1808a0030229a36a68"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("715d634c11044202338faa06921e623148441d29ec24746d83c8d83c3554283f"),
    ),
    (
        "resolve_povw.zkr",
        digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("3ada2e0afc16f93951f09618deba99011007285295f0842f6973c809bea1594f"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("e65d1158bb0528775e3acd330df3281066abc76c33ddbd66b55b135546047d0d"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("9f9de676a7139523e355ce4b097ff71a94aff7333dd4006284393d0dd78f3354"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("653dce4d67204a6b1829565144937861f2a49457c941010297ac9c5f0730ad10"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("86d78a51f8850e043253af27b69330753281040b487ee806f17a4063c353d34f"),
    ),
    (
        "join_povw.zkr",
        digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("3f2b4e59af0a863426dca46224ec2f59c3af923d6ff1b2044337a4328de3f81f"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("c62701187ef7cd1125822821c7474f479c86814a23b75669043b6f66838d9205"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("444d921ae3c4bd36dcda74080ebff12e45fc9057db46f5628524db0e8adf7f71"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("5182f230f954001a71ae843a2df0f413a56ac035f60afe7090f17d478a7c7a6a"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("9b3faf3984fb78698e58e364a5beee4229b06843aa7acc1392f542141f6c5d2a"),
    ),
    (
        "resolve_unwrap_povw.zkr",
        digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"),
    ),
];

/// Control IDs for included recursion programs (ZKRs), using SHA-256.
pub const SHA256_CONTROL_IDS: [(&str, Digest); 36] = [
    (
        "lift_rv32im_m3_20.zkr",
        digest!("8e1c8070ee565bae9b8b2408664118cb48032518fb777cb367fae4fe6629694e"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("b45f67e62789cc4538b446ee16e7700481365a81f33eca478c184f27bb150d80"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("5fa6e10fde3c9a2d2fe0f545c9c30475616c80a8ca03ba1de43d3c62d65bb31b"),
    ),
    (
        "join.zkr",
        digest!("dc44002689aa7852410ad1c840388d66b8b9a2f6d0c4fb6b3ac6ec2ea17d9855"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("1696f91113c63e93f51471bf79abffc85da5baf178e77b99e85adf0e73faa6ac"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("8408aaf14e1e6efb0a14509805024d4ffca9bd2d8f57719aadbae1b9d706b6e3"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("1a2a35606c7dcea2c111576b4b22ab6e9906d76c3cee826d5e172ebfed054c30"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("ed6f800b86c2ec9f1ddd110f898a44a1416ba287a0a965a4a999934b49de8135"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("a7f32b455d88d653287c0e3f6f51e361854038e231e5b30f13e423e95834632b"),
    ),
    (
        "union.zkr",
        digest!("44bfa51c5030508d7eddc1b1489145a6e519842f7283098a17f13fe9113497dc"),
    ),
    (
        "identity.zkr",
        digest!("d7ecd18c7d06fc468166147cf20869aa10f32e097a0c166146a5a62dd2d975ea"),
    ),
    (
        "lift_rv32im_m3_22.zkr",
        digest!("f687e8f0d7de73c50f0fbd99007219e73395a78db03c8d29190a2b38b0d0de68"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("2d6cf2e4a6e4a7680bf59bdae0942783d5490fec6cce40371d5ff89141e67143"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("c8e44cd7a2fc08c2e50c92337bba17144ed30995534991a58656dfd9b431ade0"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("2056272024b13ad3e33f3c174eea7b7fc255bec8a179ed2c16a94c3c1e62ce7d"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("94953141032267d9fc2f6d066e3fae389f518b6b22754d6597345315af4ad311"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("3c7b9195e051f01d9dc21d96a1dd26c7035bc225511a715cf8c7ba83f8df7687"),
    ),
    (
        "resolve.zkr",
        digest!("ecc34946284eb02d1e119ef0878ae65ba5e855d6e0b5db4e462a694007b2a0f4"),
    ),
    (
        "lift_rv32im_m3_povw_15.zkr",
        digest!("193135bb38d64db8b615942b2f222511938b4aabccf4a59e32ecb7c50495920c"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("3f1c69ba4a21f7302099a99a4a1f05be6dae1671f1800335c7e5ad15ee7d3a2f"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("d4bffdbdd8b5b682b31d95230510559cc39c3777992c572be3cf253ce5d57f14"),
    ),
    (
        "resolve_povw.zkr",
        digest!("51fe537675d705e759c0cb0862f0cb7c5d70ce3dc483efc3cb1646c2b6f0cba3"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("7ef4f97c9ea845c30a8f7d2e2ed4199e2210bec0e6d6bdad54970c75482b67a1"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("5d99dd14180bc36a328ea44c523acee137cdc673db6dc3da09a174f14a91d892"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("849a4a8f4a2767a06fadf4ed6ace6ba4b74cc22c1e6b68bb0467d6fd94641a40"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("f87dc7627dbc2b66bcc9392a705e096622b707eabdd7d495a5534f26dfd27f01"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("8cae4f60f8b44780351ec5740118fcc348d8fa0d029f07d2c77a3f9239165319"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("c98b9446dd7fb69e7cad578fdacbc5840d9b21b25611c67e1ba259cd6d1c62fb"),
    ),
    (
        "join_povw.zkr",
        digest!("9e97b7ba610dc00ec2628d53274c303eb0d78e6e5c33ef118cf60a5135efa97f"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("9f872c419579be9e29f4ea2c33d776a8c6f76708f82dbb489c53caf50209f4fe"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("ffc394d87f264a9e4156c67c21455f63ec77f620b8d5a80fe8c5900d1705b3dd"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("cab2aeabaed2891a8c192d8c8ba8132a9404b81b7931dcef4c4ccf6ac0e097e2"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("102c704f1dbb8a5dc5451d2b91cded182d5700ba2de74e0daf8b61b5ea9f797f"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("3b5de70ddecc2fabcd3b9b9150ff64e7fc084ecb80f97cac2f9ee11e326087d1"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("97990852642cf805509c73da649d7a8c0abe5000c0a00e15129c3b0d516394e9"),
    ),
    (
        "resolve_unwrap_povw.zkr",
        digest!("1332cc7a1cb90467d849db4ebc4fcc201f81fe0a2ab06d6a398d76b7dd8aa694"),
    ),
];
