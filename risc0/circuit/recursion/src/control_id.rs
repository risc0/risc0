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
    digest!("fbb6d017b35c7f76876b244371fba768be93cd6651faee09ca650b066865562d"), // recursion lift_rv32im_m3_12.zkr
    digest!("484b406693aae06bbb2cf12b7fd6ee42751fa935c4055f64c10fae68a970d975"), // recursion lift_rv32im_m3_13.zkr
    digest!("04ad8569809d1d4176e29f1be09f855d30bbde5c2becdc3b15ba2c0124acf50f"), // recursion lift_rv32im_m3_14.zkr
    digest!("1acb1a12a2e898705a75751b7a5d8942ff861b654a3c6f736578b15865793b22"), // recursion lift_rv32im_m3_15.zkr
    digest!("74f0246a17717b19b5efc04ebdc76b2318f69b127a76376fa01dbc43438bf767"), // recursion lift_rv32im_m3_16.zkr
    digest!("c038a21cc1352a3aaa8c7557ae20c219d24f322999f0f73e5f1f13305be2881a"), // recursion lift_rv32im_m3_17.zkr
    digest!("49f89875c91ff477ffeabc724c1e7804a433365b6dc8a02d827440150dbe8e21"), // recursion lift_rv32im_m3_18.zkr
    digest!("42a80614b00c7d4417dc0952cb3c0f132e946a231126d100bbcef969e9916802"), // recursion lift_rv32im_m3_19.zkr
    digest!("d6f790427f84e4517c0faf1431ea9409b0080410abb6a419b0eda73763808940"), // recursion lift_rv32im_m3_20.zkr
    digest!("589ef5111dac9b064d06b94d0d5da92b13c1220af3461f5053962a2560a2233d"), // recursion lift_rv32im_m3_21.zkr
    digest!("603a5d62de96360c67781b35f3fbe75df2615b0e53afd85c12ba5513babf7b41"), // recursion lift_rv32im_m3_22.zkr
    digest!("d55d3966b93c5e05e5a5e86ef8e1141c26482d362a350c45bcc13654f0f5bc33"), // recursion lift_rv32im_m3_23.zkr
    digest!("88b2a26041efed1f6d744c0d045e1c5750624c628938b32ec8d70f3d5d39f047"), // recursion lift_rv32im_m3_24.zkr
    digest!("ed0ce92b0975f059c6e1423ef46b8227cc596052d461d81dbb9c9309c4818964"), // recursion lift_rv32im_m3_povw_12.zkr
    digest!("242be132a01303298414a5689410d00279a2ec06c4cfae66b00e6329bc204167"), // recursion lift_rv32im_m3_povw_13.zkr
    digest!("068a5e1d7f5f8f1910456f0e56dd3a32509a6838f261146e5bf2c2627d1fc947"), // recursion lift_rv32im_m3_povw_14.zkr
    digest!("f61b814e61aff32d3d261b0391a987281d948c306e196577db351f5a4c79183d"), // recursion lift_rv32im_m3_povw_15.zkr
    digest!("0497d305711cc23699ced617dd550a1f5f674f6221fe326e5b72340824133f28"), // recursion lift_rv32im_m3_povw_16.zkr
    digest!("ddea2568e327883cb0323e76912ea602d2aecd10273abc2f4f58820399d7723e"), // recursion lift_rv32im_m3_povw_17.zkr
    digest!("f782250b4cd7f84afc7cf4232c66f1015bf9f42c256bd8521929e2378b2f7c57"), // recursion lift_rv32im_m3_povw_18.zkr
    digest!("fbb18c1b9172a7094ce95f6d3688b4055ab4c02df6156d5c62cde3468b691d14"), // recursion lift_rv32im_m3_povw_19.zkr
    digest!("1cd3e3610269c2543d92ca19721d7141e373f06eb4fd0f547aa006583e2b5b4b"), // recursion lift_rv32im_m3_povw_20.zkr
    digest!("74707a1ddee27855e9cf6967ebcaa11bbbb331396e83c75acda808617db1022b"), // recursion lift_rv32im_m3_povw_21.zkr
    digest!("bbd2761b5304d268f334f95860036c56077f432710919e27ae1f946eb729f310"), // recursion lift_rv32im_m3_povw_22.zkr
    digest!("03381369a41f8910c6942e6e97e0df2bb93e7b44cc78dd63c7b234506134df19"), // recursion lift_rv32im_m3_povw_23.zkr
    digest!("c6d90b0e6f93075e5b89c5369d7052208c55d656a9d7442b8f6f321a4be30476"), // recursion lift_rv32im_m3_povw_24.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("4ec911509d6e5607f3bc083c61a2274824c71536ecffa208d02a472ffbde5b04");

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
        digest!("fbb6d017b35c7f76876b244371fba768be93cd6651faee09ca650b066865562d"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("484b406693aae06bbb2cf12b7fd6ee42751fa935c4055f64c10fae68a970d975"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("04ad8569809d1d4176e29f1be09f855d30bbde5c2becdc3b15ba2c0124acf50f"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("1acb1a12a2e898705a75751b7a5d8942ff861b654a3c6f736578b15865793b22"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("74f0246a17717b19b5efc04ebdc76b2318f69b127a76376fa01dbc43438bf767"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("c038a21cc1352a3aaa8c7557ae20c219d24f322999f0f73e5f1f13305be2881a"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("49f89875c91ff477ffeabc724c1e7804a433365b6dc8a02d827440150dbe8e21"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("42a80614b00c7d4417dc0952cb3c0f132e946a231126d100bbcef969e9916802"),
    ),
    (
        "lift_rv32im_m3_20.zkr",
        digest!("d6f790427f84e4517c0faf1431ea9409b0080410abb6a419b0eda73763808940"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("589ef5111dac9b064d06b94d0d5da92b13c1220af3461f5053962a2560a2233d"),
    ),
    (
        "lift_rv32im_m3_22.zkr",
        digest!("603a5d62de96360c67781b35f3fbe75df2615b0e53afd85c12ba5513babf7b41"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("d55d3966b93c5e05e5a5e86ef8e1141c26482d362a350c45bcc13654f0f5bc33"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("88b2a26041efed1f6d744c0d045e1c5750624c628938b32ec8d70f3d5d39f047"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("ed0ce92b0975f059c6e1423ef46b8227cc596052d461d81dbb9c9309c4818964"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("242be132a01303298414a5689410d00279a2ec06c4cfae66b00e6329bc204167"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("068a5e1d7f5f8f1910456f0e56dd3a32509a6838f261146e5bf2c2627d1fc947"),
    ),
    (
        "lift_rv32im_m3_povw_15.zkr",
        digest!("f61b814e61aff32d3d261b0391a987281d948c306e196577db351f5a4c79183d"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("0497d305711cc23699ced617dd550a1f5f674f6221fe326e5b72340824133f28"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("ddea2568e327883cb0323e76912ea602d2aecd10273abc2f4f58820399d7723e"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("f782250b4cd7f84afc7cf4232c66f1015bf9f42c256bd8521929e2378b2f7c57"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("fbb18c1b9172a7094ce95f6d3688b4055ab4c02df6156d5c62cde3468b691d14"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("1cd3e3610269c2543d92ca19721d7141e373f06eb4fd0f547aa006583e2b5b4b"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("74707a1ddee27855e9cf6967ebcaa11bbbb331396e83c75acda808617db1022b"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("bbd2761b5304d268f334f95860036c56077f432710919e27ae1f946eb729f310"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("03381369a41f8910c6942e6e97e0df2bb93e7b44cc78dd63c7b234506134df19"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("c6d90b0e6f93075e5b89c5369d7052208c55d656a9d7442b8f6f321a4be30476"),
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
        digest!("98ecfbbb067da23efb1cc874dea6ca433395591afd1859a338c3c10ed1d84071"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("99c2ef8b4d19ecb1f4d6e2b28d071e63579f75bf1b9748796d155bcbcabcda50"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("47c642f1a445beea9f73c0b587da5d0c35d9c952b710b12b0c0210a477515563"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("06eabb25242a44d56b0ee562edb27a5a26120f33d00515d6be2d806a83fca4f5"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("1b346ade2bd4b452a39884a797243479aff79d3125d0f2e9eec7ee97290edb5e"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("367cced45e770a3f530fe44419e2a556a4010b60b54ab3acf4a69de977260496"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("7f338fb38d8b4bc767d8f24198aa43d4871675e6ebd56875c2978cdf0cb33e2a"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("f14a7b75e0828403f1febf79e0c6cbc263d1b710fc4cee592bcb0e802b0cc0b5"),
    ),
    (
        "lift_rv32im_m3_20.zkr",
        digest!("64b1c383fcb072b2026aeb3be30b53eed62542666fb87e27491867e48695f7c9"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("9e3bb043a4300859155ac03aed84e4e306e946f6c46a4ef882a3d91009783706"),
    ),
    (
        "lift_rv32im_m3_22.zkr",
        digest!("dca41e94ee27f9476a553048de1c8a13cf531c2ebffb58f797797332b07b7a1a"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("17331283142784ed48300bdffd9b895fadc8ead395663c0d0379b397ba286bdf"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("7f0b975b24869c45b631c2f368ff22a348b304103badbd6eae3401b4c6e56acd"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("43340ac6b9c9c9c3d6ee0633b32b5e024beb866c5d369d1c10bbf730575c36f4"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("459327175d4babcf412164c882eed207b28856f944e5e2ff4c31f7dc11e70dc5"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("6fba24104b9a6ae6485e8805c36d0fcb1db9729f452584fa1fc33a7c81984aac"),
    ),
    (
        "lift_rv32im_m3_povw_15.zkr",
        digest!("8b314821feabcdf95c722f8955df2dd99b1e33d615510454d40556f680565ef4"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("73c6e499850a74eb210a9619477091ead10950c54a54cea9041ed1aede811659"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("e19401c8e2bc5a2ff82038c574910ee663c10f1bd8a605ec0069125d51fd1c43"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("792ac3e3f96d6a40aab10685e9cae6b6da1838010365a9343bb7f0eb212aa4ff"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("bf26bc76c299623797b9ee1de6a65aa8df3942709517cd3a1d72943d34c3057a"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("25175699057832902593e7639c69cf31471be74d83c505413b691ce132fa9def"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("5b1b7b3dc3066e7eb3fbd231c385fcd38ab7653a11499574685adbb48ac494f9"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("11b5a17eb713fd61deb4a201052a385f4ca6962b5574896598f28f82a50ad9d8"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("c9a548997950671ce41ce10d4e2c2995edf2c91f9acdb418a09edbc4c334e468"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("17e5b4d8f65760f1b255623d501d3bae7687554529957e73b6219e9e014c64a4"),
    ),
];
