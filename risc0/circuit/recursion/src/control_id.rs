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
pub const MIN_LIFT_PO2: usize = 14;

/// Control IDs allowed in the default set of recursion programs. Includes control IDs for the base
/// set of recursion programs, and each power-of-two of the rv32im circuit, using Poseidon2.
pub const ALLOWED_CONTROL_IDS: &[Digest] = &[
    digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"), // recursion identity.zkr
    digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"), // recursion join.zkr
    digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"), // recursion join_povw.zkr
    digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"), // recursion join_unwrap_povw.zkr
    digest!("df52a06faa52227535754701b8e4786ce8cf914ad4cd58592918e641ad8d2271"), // recursion lift_rv32im_v2_14.zkr
    digest!("ce3aad0c8f2df13993ef2a73e33eca632df0142eb611ad2bfa661c3c9b8cdc29"), // recursion lift_rv32im_v2_15.zkr
    digest!("e806094668c21923358d224785f5420565cb82638799e536af4fbc30349a0975"), // recursion lift_rv32im_v2_16.zkr
    digest!("0f69725f91ccfc669577d658ac9d4a6cfc4f9c58bc05d45f94d4872a58adb417"), // recursion lift_rv32im_v2_17.zkr
    digest!("92fd161183eb814b412c6267fcc5bd232fbf42220287a23f158ed2024d989424"), // recursion lift_rv32im_v2_18.zkr
    digest!("0082d971a1f39731343be76facda760e6f6bce30c46bc95c4cf8230a288ad82f"), // recursion lift_rv32im_v2_19.zkr
    digest!("5a50865bd2098f74bff199080de5ce175db821558c33992464ac0616ab9d0214"), // recursion lift_rv32im_v2_20.zkr
    digest!("33be8c6b57a2d052d7a0f23825a5264637ffff515cce2176af7c7d468e421872"), // recursion lift_rv32im_v2_21.zkr
    digest!("6c342747a1254d61aeb09b395f868620f072781e0bfbd43debd94f13edce874f"), // recursion lift_rv32im_v2_22.zkr
    digest!("ad3f1207f86c0952d7e59c54f28f3f27e3be092edc107b3caaf2e11e4cdfbb3b"), // recursion lift_rv32im_v2_povw_14.zkr
    digest!("a2d72f74008ba34db44aed294812b10e5619dd3cf6df0d424586d306dde25964"), // recursion lift_rv32im_v2_povw_15.zkr
    digest!("5d11490f20262d0d1ba3d23beda5992b5dfd81013e147031f836d1728bf4ed75"), // recursion lift_rv32im_v2_povw_16.zkr
    digest!("1c9d663963285d048cf14f32ec088022d322f85de62ebf26e02afd68e03d5503"), // recursion lift_rv32im_v2_povw_17.zkr
    digest!("fcb2ba0055a1f307dd8df70a7e677408e623726dec48c83a3201153539d5e757"), // recursion lift_rv32im_v2_povw_18.zkr
    digest!("6fca5a6ca8e4e303a703070bb4ac8a4e13a741369f428e270290f27073891813"), // recursion lift_rv32im_v2_povw_19.zkr
    digest!("ebee6246b6d0ed6e9148953bc8cda12428b810125c13944420f29306bf995263"), // recursion lift_rv32im_v2_povw_20.zkr
    digest!("2a890134f6c61952eece160d42dc5f5337b4455fc96d6f00ab6e4d560739012e"), // recursion lift_rv32im_v2_povw_21.zkr
    digest!("c23eac3b94f6e31dfe6a3f2eadcb1f00eb84647220818f37f1cfa0087d10fc26"), // recursion lift_rv32im_v2_povw_22.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"), // recursion resolve_povw.zkr
    digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"), // recursion resolve_unwrap_povw.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
    digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"), // recursion unwrap_povw.zkr
    digest!("acab4638c9a6b727c6053a052d110b301fa8965601a180280afb073dfcfba949"), // recursion lift_rv32im_m3_12.zkr
    digest!("13af990df62fb86faa97ec1c18b656258ca94b645f70fc4aaf52ad5b521d6e18"), // recursion lift_rv32im_m3_13.zkr
    digest!("61c227189f0ece37c789d922dfa29c1130013b1267dd133f8e3cd53051996a5c"), // recursion lift_rv32im_m3_14.zkr
    digest!("42a7d04709e58f6ff3c6ac4d2a02645c087e5d31224a5962a2c42a3a9d65373d"), // recursion lift_rv32im_m3_15.zkr
    digest!("d2fdbb1ab92432483dd93e3aa61e47561fc75e6c41be2973a0256071e169072b"), // recursion lift_rv32im_m3_16.zkr
    digest!("69ef62537b09700db2f8ab1bf112b2057b097d337c68e32bd8a3161d7f0aa01c"), // recursion lift_rv32im_m3_17.zkr
    digest!("4660f82a65eba237a0ed5265f8d18429cdc9565efe191c63e425451fcb50ff36"), // recursion lift_rv32im_m3_18.zkr
    digest!("89d46f64719fc834567a69067a16081fd9f18865fce3f31b9a40da656232d839"), // recursion lift_rv32im_m3_19.zkr
    digest!("168faf453ef9e204f60208253c46ea1d71030c0d8c6d892f8a839e3006559e25"), // recursion lift_rv32im_m3_20.zkr
    digest!("fbf03b10ebd0d528b789254b886d867392b49e4cd843e93363ca5a1c1008615c"), // recursion lift_rv32im_m3_21.zkr
    digest!("51745c1df57b7b4d75504f256a9283539d085c29ed245953a10705550b5c2e71"), // recursion lift_rv32im_m3_22.zkr
    digest!("aa6da106d6bd1f330a9b884fdc430f4c4bbdf5654e2403612a34ce33a33e1055"), // recursion lift_rv32im_m3_23.zkr
    digest!("faadb0737b3d2d5a5625a172bf5fb119d88d9e1d0dae861c519b65625d8d5c0a"), // recursion lift_rv32im_m3_24.zkr
    digest!("e6c54017840aea6cb26b415bf3bc5024e57f0746c2a78c38f9a45706b4d00f15"), // recursion lift_rv32im_m3_povw_12.zkr
    digest!("e5f5e748b63fa25b959d25274581a675dd561c0d3036e907e33b722820540358"), // recursion lift_rv32im_m3_povw_13.zkr
    digest!("0bd9431cc99c600310f63b51700d88016b14c204592b2d4ed609f048e7d9c310"), // recursion lift_rv32im_m3_povw_14.zkr
    digest!("f21de13aa203ab4035428f2881b7b92c6874d75026096e37bedc206b61e7eb6e"), // recursion lift_rv32im_m3_povw_15.zkr
    digest!("13b88047c471235d5849fd77e79bc248a106282a7914c172560bf9657c748406"), // recursion lift_rv32im_m3_povw_16.zkr
    digest!("199ed810d0356e051ebc785771bb682ac70ca16fe0ce607038af633ca83ef82a"), // recursion lift_rv32im_m3_povw_17.zkr
    digest!("f0332845313ff4246e69f2144692430fa28b6216affddb1ceef052403aa9b470"), // recursion lift_rv32im_m3_povw_18.zkr
    digest!("c9df2930fa54394d01c4e61d5a01ec247e9baa35e2d30708b20b96552ec5045c"), // recursion lift_rv32im_m3_povw_19.zkr
    digest!("c2da4d399bac490d0fce1371fc251e7203aa6553e579c80e8b91d3503b5fe612"), // recursion lift_rv32im_m3_povw_20.zkr
    digest!("0979be2833e21d17f7f360375bcdf176bd3c765e5feead48463e654e38fca156"), // recursion lift_rv32im_m3_povw_21.zkr
    digest!("609825553be592460c629c3b3f6bcc15b3ef82070f2b586a9d210c22bcbc3f3c"), // recursion lift_rv32im_m3_povw_22.zkr
    digest!("dbca1f632df6f76d1b39466ef194d8271ababf4890ded21c490c0a4a074c2973"), // recursion lift_rv32im_m3_povw_23.zkr
    digest!("e4a1036aa8d6014634d6b44333cef92d309efa2ee3037747e712c5103d09d835"), // recursion lift_rv32im_m3_povw_24.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("6ab25f368575244b22d1614a2df37e0a54de5e319c3c390bd326bd0289cfdb29");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("c07a65145c3cb48b6101962ea607a4dd93c753bb26975cb47feb00d3666e4404");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 58] = [
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
        digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"),
    ),
    (
        "lift_rv32im_v2_14.zkr",
        digest!("df52a06faa52227535754701b8e4786ce8cf914ad4cd58592918e641ad8d2271"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("ce3aad0c8f2df13993ef2a73e33eca632df0142eb611ad2bfa661c3c9b8cdc29"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("e806094668c21923358d224785f5420565cb82638799e536af4fbc30349a0975"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("0f69725f91ccfc669577d658ac9d4a6cfc4f9c58bc05d45f94d4872a58adb417"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("92fd161183eb814b412c6267fcc5bd232fbf42220287a23f158ed2024d989424"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("0082d971a1f39731343be76facda760e6f6bce30c46bc95c4cf8230a288ad82f"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("5a50865bd2098f74bff199080de5ce175db821558c33992464ac0616ab9d0214"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("33be8c6b57a2d052d7a0f23825a5264637ffff515cce2176af7c7d468e421872"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("6c342747a1254d61aeb09b395f868620f072781e0bfbd43debd94f13edce874f"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("d423af1f2e48a109c612a82a5fa1490ee1675646c878335948e0e75e0a20081d"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("06987236d7c48128ab8c3505b88269637cbbd540636ccb4b4552d100e7f41742"),
    ),
    (
        "lift_rv32im_v2_povw_14.zkr",
        digest!("ad3f1207f86c0952d7e59c54f28f3f27e3be092edc107b3caaf2e11e4cdfbb3b"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("a2d72f74008ba34db44aed294812b10e5619dd3cf6df0d424586d306dde25964"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("5d11490f20262d0d1ba3d23beda5992b5dfd81013e147031f836d1728bf4ed75"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("1c9d663963285d048cf14f32ec088022d322f85de62ebf26e02afd68e03d5503"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("fcb2ba0055a1f307dd8df70a7e677408e623726dec48c83a3201153539d5e757"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("6fca5a6ca8e4e303a703070bb4ac8a4e13a741369f428e270290f27073891813"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("ebee6246b6d0ed6e9148953bc8cda12428b810125c13944420f29306bf995263"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("2a890134f6c61952eece160d42dc5f5337b4455fc96d6f00ab6e4d560739012e"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("c23eac3b94f6e31dfe6a3f2eadcb1f00eb84647220818f37f1cfa0087d10fc26"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("f64baf5f0f2fd36a8d16731d1463f20db42c2e02e1a4d91bd604a2034e94e047"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("d805245016e3d277cc4040064517f53112a6b719383ed2195395196ac1d46d42"),
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
    (
        "lift_rv32im_m3_12.zkr",
        digest!("acab4638c9a6b727c6053a052d110b301fa8965601a180280afb073dfcfba949"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("13af990df62fb86faa97ec1c18b656258ca94b645f70fc4aaf52ad5b521d6e18"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("61c227189f0ece37c789d922dfa29c1130013b1267dd133f8e3cd53051996a5c"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("42a7d04709e58f6ff3c6ac4d2a02645c087e5d31224a5962a2c42a3a9d65373d"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("d2fdbb1ab92432483dd93e3aa61e47561fc75e6c41be2973a0256071e169072b"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("69ef62537b09700db2f8ab1bf112b2057b097d337c68e32bd8a3161d7f0aa01c"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("4660f82a65eba237a0ed5265f8d18429cdc9565efe191c63e425451fcb50ff36"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("89d46f64719fc834567a69067a16081fd9f18865fce3f31b9a40da656232d839"),
    ),
    (
        "lift_rv32im_m3_20.zkr",
        digest!("168faf453ef9e204f60208253c46ea1d71030c0d8c6d892f8a839e3006559e25"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("fbf03b10ebd0d528b789254b886d867392b49e4cd843e93363ca5a1c1008615c"),
    ),
    (
        "lift_rv32im_m3_22.zkr",
        digest!("51745c1df57b7b4d75504f256a9283539d085c29ed245953a10705550b5c2e71"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("aa6da106d6bd1f330a9b884fdc430f4c4bbdf5654e2403612a34ce33a33e1055"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("faadb0737b3d2d5a5625a172bf5fb119d88d9e1d0dae861c519b65625d8d5c0a"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("e6c54017840aea6cb26b415bf3bc5024e57f0746c2a78c38f9a45706b4d00f15"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("e5f5e748b63fa25b959d25274581a675dd561c0d3036e907e33b722820540358"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("0bd9431cc99c600310f63b51700d88016b14c204592b2d4ed609f048e7d9c310"),
    ),
    (
        "lift_rv32im_m3_povw_15.zkr",
        digest!("f21de13aa203ab4035428f2881b7b92c6874d75026096e37bedc206b61e7eb6e"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("13b88047c471235d5849fd77e79bc248a106282a7914c172560bf9657c748406"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("199ed810d0356e051ebc785771bb682ac70ca16fe0ce607038af633ca83ef82a"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("f0332845313ff4246e69f2144692430fa28b6216affddb1ceef052403aa9b470"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("c9df2930fa54394d01c4e61d5a01ec247e9baa35e2d30708b20b96552ec5045c"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("c2da4d399bac490d0fce1371fc251e7203aa6553e579c80e8b91d3503b5fe612"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("0979be2833e21d17f7f360375bcdf176bd3c765e5feead48463e654e38fca156"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("609825553be592460c629c3b3f6bcc15b3ef82070f2b586a9d210c22bcbc3f3c"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("dbca1f632df6f76d1b39466ef194d8271ababf4890ded21c490c0a4a074c2973"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("e4a1036aa8d6014634d6b44333cef92d309efa2ee3037747e712c5103d09d835"),
    ),
];

/// Control IDs for included recursion programs (ZKRs), using SHA-256.
pub const SHA256_CONTROL_IDS: [(&str, Digest); 58] = [
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
        digest!("9e97b7ba610dc00ec2628d53274c303eb0d78e6e5c33ef118cf60a5135efa97f"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("8cae4f60f8b44780351ec5740118fcc348d8fa0d029f07d2c77a3f9239165319"),
    ),
    (
        "lift_rv32im_v2_14.zkr",
        digest!("61ee526aa224c2fbf764a5c24c810097a027cfb3d92d39f52cfed8b7e2c0d002"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("af41e81c676635387c0a440157ffd9b2bcc4188541e0d7a492623af3ad7bdc89"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("e0964e5993c4cad3b088b89608f976debed2b91a048b21032f4097d07943e9f0"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("09584a7c483b4e3e64b71590c21427cceba0fc518901b1de94130b78d46fb74f"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("bdae8aa0c755bb1ff8437ab92bd897af0bfd8924bed31142e92e4858dd6af915"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("1709f8b9cbd2e4acaeb30f141acc3ba8ec85a5bbf9764315354c194ceb069121"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("409a2aa7ee65646ceb06e1741ae00acf2ffc0ed0cbb7562767d50b8b8555ad63"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("849b1fdbd4166a9d6640872f14c86c861b4e668d6d9e8adf9e91b1b95f9375c6"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("e26e448c0f2e28e6e4f2b2ed600dd437c62ba4a88b8753f807e2de9d52e40cd0"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("5069f315a116b3b8d04c1da3ba94e77bace31509ea5ce26e0c6e66038b8234c9"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("f3ab6cbfed507549f10fcc64f6a8987c881c92b49ab55f8f4da6d1ea767defd8"),
    ),
    (
        "lift_rv32im_v2_povw_14.zkr",
        digest!("3ee6f7220d88611ed45ab685b6b40183e0c7371c0bf8ac93ac45e38f25795465"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("d248115e9adc6144e5a2a6dc5a04769dc060504143a64eab3b5100d1f240c9b4"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("5d135649e9a23427c97d16f572a9e98f7f5b917a536f70b76f94f4dc01e1e65b"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("2c28ebf90d7ef10b55789570663d2e785135e1966b2a5edc20562d80f5977c4c"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("0995b87f9c3df6c62fb7f0db03dd61db34aa868b8abe554d1e2ae91520a58825"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("c4fdefc142707f90bd07a5ed71eadd71b35eee5d4214e209643014130e0bd019"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("0190c8a2188d40f3905924359c09710f96707391bede3b2ba6a2c1f6394b4f6e"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("93302e6b24fcd9624faad96df57b1dece68a4dd33ed87f0ebd56b849778f349f"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("6803508e9e4d876d949a3e915f06c197e87cf1e33a6c4368c8821e856ab84158"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("3835accadcbadb74d455b1ad666015cb91ad7eaaaa9350de0cd2bea4bbdd74eb"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("a6095d927fafc2d42556b3b3136fd315179555ce1bcec1dd46468ff47e7e448d"),
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
    (
        "lift_rv32im_m3_12.zkr",
        digest!("9e34e0252b6f016e278b6c0649cfc7800cd70f41cf652c54188ce5bc0c327347"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("1a3909c450309c0d2c4a1e550de22cbc06f59110cb54a64fde01039c350d872d"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("7190281960000eb8b814e418ed7a87a08d8d41d30a979aa5f528b3c036b68e93"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("bb7a501b0f3cc1c19de83a32962cbc9df714aad55379d8b1ff27033f7c4b651e"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("ecb223bf063af0ca455eeaaa03e85216f5ae2cd61a4dab72e0125f8cf38e960b"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("19be3cabdf3f93f7f55f086866e7361c582fb03bdb79fb6bfe7b6709de19f410"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("ad4974db57bdd64b7bb8b2c08f04c9e1e8721540c2eebf89a9d938f36ce1d4fa"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("ebf79dc855301f015f5f0edf91dc50d25790047257fb7262c86d1fd7da713f09"),
    ),
    (
        "lift_rv32im_m3_20.zkr",
        digest!("2a402c49ddf8df1e55247cae4e0fc53e5b862445ba13ce45d4105b329e6d6bab"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("2b498cadb357964c558de229718c1ab8fcd65b8c3cb98be95bdbe89ea2ce34d9"),
    ),
    (
        "lift_rv32im_m3_22.zkr",
        digest!("0c4737e01047436e92260b504f4766650e51fcd48492620e69c5888480d47e9e"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("985c810fd2b8baae4a2bf795a3f11a6f65cf8d32e4af4fe3631536ebd4f92cbe"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("58ff171a15e7f19c377dc00acb3676ee8535fee6a31746c6c50fdbe258198ea2"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("a7d3e4e274a6513a39883a036650fbb002e1cc0a9f72f551f670c31c97b6d71e"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("1bf9507be3bb165bec2b7e2d4eaf6a1a4323b240a7c357a690459c53acfd3ce4"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("f740a42b715b3c5fab26b0f85771a6ced04479dcee0d42ee98be847c41bc93ca"),
    ),
    (
        "lift_rv32im_m3_povw_15.zkr",
        digest!("53457a799c2c418910899802fb49dfb66cfa8f07cdb0f84164502ca12e796725"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("20d2c3ad3b126f54e8df18e2c038d0e05cd94b30e795b88f8bbfd8406ef3bad2"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("5f25f53599620f2b06bc43f5aa2e83462b092299827123b175f57ed388242a94"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("b2538662f86dcf183b4f4ec47d2519b921a40886159520e941cb1268132856a1"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("c6d55a2f50736c75430e1fdad11ad0826061e523d66dbaa9a708a16850ca6825"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("7d804acb6c2aab9ac021ba55c4c3a549adb256a7f2e290d5c3ae1b071be8e995"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("1aad446c21fe1c037f13afb76f82517386bccde9f7d4e0275de4e0d014feddbe"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("214794ede4e9fc2135536861d1bc3384836314f67bd2e7d8b8b507921cc39071"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("51c276499fa50717e695b8d4489ada57e399fa93d013aaae3f723c05307c3bcd"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("8059208847d39b9995181af58d45f81f3835ec6fc668d0db5d073b691c0c1fd8"),
    ),
];
