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
    digest!("99ee290b79bd411b534de65afb2e5b228523362990c36e3a67597f70b6b9bb01"), // recursion lift_rv32im_m3_12.zkr
    digest!("9ea6594e8e0e016b9bb11506abb3a1762229a37203a3b251ae09374b8291af02"), // recursion lift_rv32im_m3_13.zkr
    digest!("378a9865f82dae1d57cc6f69c82a45532154df4c0ed4563d3d933861208bbc4a"), // recursion lift_rv32im_m3_14.zkr
    digest!("9d0e75346d0e293dac7bec4d61a6680e6f798441ae0c471cf84ab9775b7a4560"), // recursion lift_rv32im_m3_15.zkr
    digest!("deece14371395e76f58296293e579c0eb2b15d544dd6492d78cbbe76decbee2b"), // recursion lift_rv32im_m3_16.zkr
    digest!("647eb710d1487863de97201f3936e5346a39da4020543f53a0d0bc7309ad9b6a"), // recursion lift_rv32im_m3_17.zkr
    digest!("7fbac65d0f92ba19cd06e41c1b616f660a097e3753e4064589f6dc7709ae3827"), // recursion lift_rv32im_m3_18.zkr
    digest!("5425ef6b7d67ab4dc4de4a4b120a250263489052842bd65b82df140000aa591a"), // recursion lift_rv32im_m3_19.zkr
    digest!("258a6449b63f265eda2606203c2d6e5a9238cc4b972a6c307527b316d1037800"), // recursion lift_rv32im_m3_20.zkr
    digest!("8aef0e7099e8cd67ed0e071e845a5d11121bfa39ec4358527eb25777a9324228"), // recursion lift_rv32im_m3_21.zkr
    digest!("3c5ca62070aa9255b6c2a4191a87bb778a069a59affc852c101af357d3fdf556"), // recursion lift_rv32im_m3_22.zkr
    digest!("36a05074e28f0129ff82d42ea6ae15507532d54320eed826adbb815347e07063"), // recursion lift_rv32im_m3_23.zkr
    digest!("db4a7e218571cb07c57cd91c60a15d19aa56f9035b77fb37be86c42e94be582e"), // recursion lift_rv32im_m3_24.zkr
    digest!("8d180e102d566a36e5366a4eb0c65f762bb8696de630c6343dfe4955c790964e"), // recursion lift_rv32im_m3_povw_12.zkr
    digest!("1d4ec717eaaadf73a112a147fdbd7e6695412307d0fdec346f709b12a9514018"), // recursion lift_rv32im_m3_povw_13.zkr
    digest!("09679c261bcf1e4264eb98513e9f72761299396cc9afc53cf7a81243187e0a5f"), // recursion lift_rv32im_m3_povw_14.zkr
    digest!("794fb16b66df4c01991291021a45ce32be2a4924f12c6d52ecf1041f3c363048"), // recursion lift_rv32im_m3_povw_15.zkr
    digest!("ddddc521e352496e1d7838074494604c60a14a38b773cb689584683b17d80d38"), // recursion lift_rv32im_m3_povw_16.zkr
    digest!("6114442d8fdecc0814482843d735e06744cf1c341bfc645faf2e7d344f301116"), // recursion lift_rv32im_m3_povw_17.zkr
    digest!("a0c7e9157f667f2a8729444befada033b8c3b03e9a17b422784b7905ad856e74"), // recursion lift_rv32im_m3_povw_18.zkr
    digest!("cc3b39359645bd69d664203e37ae5b027ef87724868e871abfc85507d4d49f11"), // recursion lift_rv32im_m3_povw_19.zkr
    digest!("e261da4f2fc8106ed7c07d487dfce0371332991ad07d873f3f5c026239ddcf5b"), // recursion lift_rv32im_m3_povw_20.zkr
    digest!("316b296dfb5e814daf16bb21e15b093c13aa831b020b6e0db38340661456bc54"), // recursion lift_rv32im_m3_povw_21.zkr
    digest!("6259472f89e23e6d3dd986679d7ad839d02ada239bf28b5b9216453d2bfe052e"), // recursion lift_rv32im_m3_povw_22.zkr
    digest!("4672e35d9ff96a681bcc2c61076cc72d8fec57225f232a52de0c4b1bd506470e"), // recursion lift_rv32im_m3_povw_23.zkr
    digest!("d8982804c993f66d8b9cad263c803f32747acb2f4983d10d0ae8585252c26759"), // recursion lift_rv32im_m3_povw_24.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("a033221c24fcf70e7abb240b5b7bd61e0de3a71fe35c1668a711bd484501cc38");

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
        digest!("99ee290b79bd411b534de65afb2e5b228523362990c36e3a67597f70b6b9bb01"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("9ea6594e8e0e016b9bb11506abb3a1762229a37203a3b251ae09374b8291af02"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("378a9865f82dae1d57cc6f69c82a45532154df4c0ed4563d3d933861208bbc4a"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("9d0e75346d0e293dac7bec4d61a6680e6f798441ae0c471cf84ab9775b7a4560"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("deece14371395e76f58296293e579c0eb2b15d544dd6492d78cbbe76decbee2b"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("647eb710d1487863de97201f3936e5346a39da4020543f53a0d0bc7309ad9b6a"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("7fbac65d0f92ba19cd06e41c1b616f660a097e3753e4064589f6dc7709ae3827"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("5425ef6b7d67ab4dc4de4a4b120a250263489052842bd65b82df140000aa591a"),
    ),
    (
        "lift_rv32im_m3_20.zkr",
        digest!("258a6449b63f265eda2606203c2d6e5a9238cc4b972a6c307527b316d1037800"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("8aef0e7099e8cd67ed0e071e845a5d11121bfa39ec4358527eb25777a9324228"),
    ),
    (
        "lift_rv32im_m3_22.zkr",
        digest!("3c5ca62070aa9255b6c2a4191a87bb778a069a59affc852c101af357d3fdf556"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("36a05074e28f0129ff82d42ea6ae15507532d54320eed826adbb815347e07063"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("db4a7e218571cb07c57cd91c60a15d19aa56f9035b77fb37be86c42e94be582e"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("8d180e102d566a36e5366a4eb0c65f762bb8696de630c6343dfe4955c790964e"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("1d4ec717eaaadf73a112a147fdbd7e6695412307d0fdec346f709b12a9514018"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("09679c261bcf1e4264eb98513e9f72761299396cc9afc53cf7a81243187e0a5f"),
    ),
    (
        "lift_rv32im_m3_povw_15.zkr",
        digest!("794fb16b66df4c01991291021a45ce32be2a4924f12c6d52ecf1041f3c363048"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("ddddc521e352496e1d7838074494604c60a14a38b773cb689584683b17d80d38"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("6114442d8fdecc0814482843d735e06744cf1c341bfc645faf2e7d344f301116"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("a0c7e9157f667f2a8729444befada033b8c3b03e9a17b422784b7905ad856e74"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("cc3b39359645bd69d664203e37ae5b027ef87724868e871abfc85507d4d49f11"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("e261da4f2fc8106ed7c07d487dfce0371332991ad07d873f3f5c026239ddcf5b"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("316b296dfb5e814daf16bb21e15b093c13aa831b020b6e0db38340661456bc54"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("6259472f89e23e6d3dd986679d7ad839d02ada239bf28b5b9216453d2bfe052e"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("4672e35d9ff96a681bcc2c61076cc72d8fec57225f232a52de0c4b1bd506470e"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("d8982804c993f66d8b9cad263c803f32747acb2f4983d10d0ae8585252c26759"),
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
        digest!("266894dec931b532999fb9c352ec3eef3af789eaff9e04537df14cf9c8dbdc62"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("fd1a0347f2438ec729bad29a92ee3c264240c647523063373e3c6c1a98e64715"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("48ff54cdb9739e6c7f44b7dde85f2b1458c8480f4fa1ec2c9ad849590bf3abdf"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("76de6c58cb8d7715173544e48484d29df9d95e8507ccb8402a63a121de9d1426"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("19216832d8843eb99af116391b1e858508769f2470ac080292bbfa64978b8c3e"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("e09130bc0644fb30226ea28d3a53d1335a4963c53c72f4bf78a2c0e53af24549"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("e94868bc6298b030d973ce332126080ac6e7dd7ecc6e8c95cb49729bd43b8260"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("e844ee01b86b5a1c197c4b81202ed49ac3b61635635ae86d34cb06af690e4888"),
    ),
    (
        "lift_rv32im_m3_20.zkr",
        digest!("bc6f0008408590f6d53cea2df7da4af82f925146744baeec7a151d2bf72b6737"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("6e9f42d3ead13f0ca98889c8d7aa04e9924a8f4cb530688f6295deb0887ad78b"),
    ),
    (
        "lift_rv32im_m3_22.zkr",
        digest!("d8e4685edd6c0674118385ae319f09e8b352ac08a75415a2141029d1b133a4a7"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("0954b2464bb0678b215c4df8caae0c2e4d364c3a23783235d48e97755be72728"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("a8dbae76a975c576b0887d5ff5c5231ec8335a743e6e33b797e0a1a9fd4dfd1c"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("993ba13324fac768098232ee61f5acef6f4b1989f6a4026bd6c43b2072f3bb0a"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("5f794536ec069be621cb253a7a8e444cf1c962fefd3ace4a3944f299e8536114"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("4f925f2a96f986bdd087dbbfecfdb9fc9f866102e292c5f6b6a3fe3998dc4ce9"),
    ),
    (
        "lift_rv32im_m3_povw_15.zkr",
        digest!("7671771c74bd0cb5bf8ea7cbcceefef253391f71dcaa5ac9f0ec6f808b2cc103"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("cd915c0bca90ef7aa67d1580863ca40f2ca3f971d23fb93e37b0338faea04844"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("383e2bc753bc1685582b48e224fc08b9160a7753ee6f4898691c08f6f3c51563"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("7d403def6fa071c8566b95da8d59d9f8c4f9e606eaa835d269129ba7ab578750"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("82540bc66cf27f20319dde163b9c9863bdb8e6521f3a055782c95b00cd7eb408"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("4187b16e2ff42e6c84f6c894531266235304c6f073145557cfe1f303dd31e5c9"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("eebe6fb70c5df5a18b24a4736f5ab6760a568b918010820070790df76c915b07"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("3365e1ec224be8537d67920fa85aeac6e3a6edfb6db7ceee0c0c0908352ba699"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("660fd0edfb8f8408a757ff73a00449591432912db20837cc3d6e8de20a31980e"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("66fdb3a72e44dd717ddd5c3e57a429ab6d830c2fced26be8e48c5cf667090ebf"),
    ),
];
