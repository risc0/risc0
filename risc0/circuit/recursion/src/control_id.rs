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
    digest!("8a08ed23ee4cc74bf4a0f013b7ef42521d6ed840dc706545c1fa0b0ea3050320"), // recursion lift_rv32im_m3_12.zkr
    digest!("699e2006f88a871b7942e21d73fbd2043c9b423357b1a327ff129121631b8d18"), // recursion lift_rv32im_m3_13.zkr
    digest!("ca7e6e6e9d36bd52b5391448b2bf0e4235bb6f5d92f1d237341257159e435344"), // recursion lift_rv32im_m3_14.zkr
    digest!("8cca7a2a1a1f6f066b202d7214f873252f92bd69a9595d6e55fa02091fc3416a"), // recursion lift_rv32im_m3_15.zkr
    digest!("7ce4af6c0d79b43a9cc285367bc04563602a503c092987107c67550d45582026"), // recursion lift_rv32im_m3_16.zkr
    digest!("509e2f5bb183eb21401925633a80393e21164d736288ae452ce2bb500ff2b31a"), // recursion lift_rv32im_m3_17.zkr
    digest!("bcee5817ff471d1d25ae3d3e2801f75128e6bc5895e4cb75d5b29045697f2913"), // recursion lift_rv32im_m3_18.zkr
    digest!("ad423444c52b0867469f6b2d2730cd67f6ccde768b78b177a827432582e51250"), // recursion lift_rv32im_m3_19.zkr
    digest!("43d0420330803110acabc05516b073248d370e208566296bbad14526f6825928"), // recursion lift_rv32im_m3_20.zkr
    digest!("fef3ed615aad632c0d904c7420e30f4d0d0ad001e7dce461d2b24a384407486f"), // recursion lift_rv32im_m3_21.zkr
    digest!("4faa7c28bab1292e990b984da39e7a102e92a954c5b3bf00184a0d53274bfc45"), // recursion lift_rv32im_m3_22.zkr
    digest!("7143912af13ea8718c60371a2abdb40c1a0f845709e2535c8ecdfd685e4d7c21"), // recursion lift_rv32im_m3_23.zkr
    digest!("41578c6088b8b04da5907464eecd090d02acd7005333a828bfc7971207738641"), // recursion lift_rv32im_m3_24.zkr
    digest!("78f55a4184c1bb655bfc97196252f14755092a1095a6e80d6a60e1678c6e1d54"), // recursion lift_rv32im_m3_povw_12.zkr
    digest!("2165b06592e7c35e19099b4f70d94875e98d00088e7acb55fe5d00389468c06b"), // recursion lift_rv32im_m3_povw_13.zkr
    digest!("ee6d1051257f4f5f0ff9f6651cb657011fd5ae20740f1629ba673a24bce7c13c"), // recursion lift_rv32im_m3_povw_14.zkr
    digest!("de35bd36c2f9064dd9f47a01db05c44dd68c034625007529d540682e54d89f5a"), // recursion lift_rv32im_m3_povw_15.zkr
    digest!("f991d2074ec5d55f8ca1903f7e02b4552216111f705b291ba1f67d44e438fe2e"), // recursion lift_rv32im_m3_povw_16.zkr
    digest!("e5753e332dde2b009d78d9749b874546cb781a293329713e3469e04620499c72"), // recursion lift_rv32im_m3_povw_17.zkr
    digest!("4e3553391b474122820b961c12d86f3bd353dd00a861526b249f446edf6e1a10"), // recursion lift_rv32im_m3_povw_18.zkr
    digest!("90705559a944ec2c21aba96ae1eba135bbc0361ef354d54eec93e41d9db9f92a"), // recursion lift_rv32im_m3_povw_19.zkr
    digest!("e9b1e2350ab1d6141dd0cb3d4003bb5b91a8500faab184456274461f925dcc6b"), // recursion lift_rv32im_m3_povw_20.zkr
    digest!("e1fd9a31d366a20f97ef872d4470665eecd32170b4b2923f602aea0434758c12"), // recursion lift_rv32im_m3_povw_21.zkr
    digest!("464065412583a82377f40462667eb34920c5bb67547556665fc9fd00a04ce806"), // recursion lift_rv32im_m3_povw_22.zkr
    digest!("cec1926b89df8a446640eb0a53aaa62fbcf24b16afe93c25e366a767af325e25"), // recursion lift_rv32im_m3_povw_23.zkr
    digest!("76c5f133df349734c67218614623964e6a4fa56ea10dff1f8882ad1d0b3a120d"), // recursion lift_rv32im_m3_povw_24.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("2a55083764d8516ebfb0d51804fe2f3ce948ec2cf107543e59a1dd0beece8073");

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
        digest!("8a08ed23ee4cc74bf4a0f013b7ef42521d6ed840dc706545c1fa0b0ea3050320"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("699e2006f88a871b7942e21d73fbd2043c9b423357b1a327ff129121631b8d18"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("ca7e6e6e9d36bd52b5391448b2bf0e4235bb6f5d92f1d237341257159e435344"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("8cca7a2a1a1f6f066b202d7214f873252f92bd69a9595d6e55fa02091fc3416a"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("7ce4af6c0d79b43a9cc285367bc04563602a503c092987107c67550d45582026"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("509e2f5bb183eb21401925633a80393e21164d736288ae452ce2bb500ff2b31a"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("bcee5817ff471d1d25ae3d3e2801f75128e6bc5895e4cb75d5b29045697f2913"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("ad423444c52b0867469f6b2d2730cd67f6ccde768b78b177a827432582e51250"),
    ),
    (
        "lift_rv32im_m3_20.zkr",
        digest!("43d0420330803110acabc05516b073248d370e208566296bbad14526f6825928"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("fef3ed615aad632c0d904c7420e30f4d0d0ad001e7dce461d2b24a384407486f"),
    ),
    (
        "lift_rv32im_m3_22.zkr",
        digest!("4faa7c28bab1292e990b984da39e7a102e92a954c5b3bf00184a0d53274bfc45"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("7143912af13ea8718c60371a2abdb40c1a0f845709e2535c8ecdfd685e4d7c21"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("41578c6088b8b04da5907464eecd090d02acd7005333a828bfc7971207738641"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("78f55a4184c1bb655bfc97196252f14755092a1095a6e80d6a60e1678c6e1d54"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("2165b06592e7c35e19099b4f70d94875e98d00088e7acb55fe5d00389468c06b"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("ee6d1051257f4f5f0ff9f6651cb657011fd5ae20740f1629ba673a24bce7c13c"),
    ),
    (
        "lift_rv32im_m3_povw_15.zkr",
        digest!("de35bd36c2f9064dd9f47a01db05c44dd68c034625007529d540682e54d89f5a"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("f991d2074ec5d55f8ca1903f7e02b4552216111f705b291ba1f67d44e438fe2e"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("e5753e332dde2b009d78d9749b874546cb781a293329713e3469e04620499c72"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("4e3553391b474122820b961c12d86f3bd353dd00a861526b249f446edf6e1a10"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("90705559a944ec2c21aba96ae1eba135bbc0361ef354d54eec93e41d9db9f92a"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("e9b1e2350ab1d6141dd0cb3d4003bb5b91a8500faab184456274461f925dcc6b"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("e1fd9a31d366a20f97ef872d4470665eecd32170b4b2923f602aea0434758c12"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("464065412583a82377f40462667eb34920c5bb67547556665fc9fd00a04ce806"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("cec1926b89df8a446640eb0a53aaa62fbcf24b16afe93c25e366a767af325e25"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("76c5f133df349734c67218614623964e6a4fa56ea10dff1f8882ad1d0b3a120d"),
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
        digest!("2b9966ab1678ccd614641b39f3b11860310e42fb6f8a9850ddbb24cba7b3d6a9"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("3f9e73eb9f04ba1848210e47c2ec707cb0f1c4f5805e8009333b0c69304a9299"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("525c06299979e20c32fca53cdbb1a97fd5b6fe5247db986713ff0407c3240743"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("5096e729f54446c3b556f50cf965f52cb99432ededbf43f9e13d49fcc5b5cbb4"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("598fceea9cec07f6c5e3e039df8de85a7d710443ec49573394016512bf025d43"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("6d846834ea93e8abbee84621460965e11b80a4bc568579143aceda6e070a74be"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("06e6a1cfc985bd541220fc75c7de4d614d8f278e2f52cfacc45723050e6f82ab"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("c7cffaeb1d1f33d8596606b487adcb6a38b7a2422dba9361fa8ae28e04984de4"),
    ),
    (
        "lift_rv32im_m3_20.zkr",
        digest!("44fff362299255008bf46173e24928b817f089b303ef47a8ed83f16b52fe3fc1"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("95fce817264e667a068cd8c2b7a4d7516900b8ea3ad102ff0a90b3184eae99ab"),
    ),
    (
        "lift_rv32im_m3_22.zkr",
        digest!("af8562f2421caff3a366dc6eab2bc56ea4568cd3b8e866583c0672fc6d876a4b"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("cc10dbde121241644bb0bac4d2f79f9c2f55f7e751ff6e6811afaec0ca23b1b3"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("6910bad361ed4fde311183320c75222d220b5854f4f730b8ce290fe66977b7aa"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("9d73db945166a6dba1ad4ba042dcb5cb6dc77c0eb8c9de032ccabfaf58060b65"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("ee9b648f6d105408c5201b002e5dc7d006a48ae19ff622d20903b79f88418368"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("71e4f78d7c80fabdd6012550f9a0b3847119066ba87c67dee1d43972add132f4"),
    ),
    (
        "lift_rv32im_m3_povw_15.zkr",
        digest!("f450ccbb61798a09f9ec847315949ad8f988acbfe2aaffeade2d2fc90e2b0342"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("89d9895cfe1ffbeed00eb0f9899b296f2eec6767ac42586830ae0cde98e72159"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("2f1c6169d8e5892221fc3342a8b144e93e3baf2b2ac37b05f4577243e054748e"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("142cc323a9188ff1c4cf46af4d9e662c32d65b22eef9d81f13666591cf5145be"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("9365d9ce6ad013e32dafb1064242190f0cc532d3ceb0018e654e591a3fa1db41"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("6d066386ea58ff7b099798b0a9a8fad5e36b37e984f8062d6f68e4a87494148c"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("6e78cc3426e94780f111ac0727e1de3d141685ede479c036912c62adca20fb55"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("342e9345c8cbe8d3e410075b9abc9115c073808c16dcc2e16046ddbec192527f"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("4d61ccb04f43f106d2710046c511fb62100ef5ed60258f6279424dec96bfe046"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("6fa976ae40bc6a0721c49004d624d3ffdfde0a37fddf0d81779954eba2e0bb9b"),
    ),
];
