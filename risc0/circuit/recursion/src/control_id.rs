// Copyright 2025 RISC Zero, Inc.
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
    digest!("5c620751fb79b1309ef3503080b34821e1f7e91dd122621a2d263b0551a4fe45"), // recursion lift_rv32im_m3_12.zkr
    digest!("921fa86eb8234c6b4d8025430967c2260b516304631fb732729b85066961860c"), // recursion lift_rv32im_m3_13.zkr
    digest!("de773c08ba15b65be38da731f84630265a3c8606bc302154ec424f4f823e081d"), // recursion lift_rv32im_m3_14.zkr
    digest!("9fab9a3fafc72f0ce5864e189e2525127f85c053fc4bdb42f343dc5eb7919212"), // recursion lift_rv32im_m3_15.zkr
    digest!("bfa08c6886b3f55047276a0711ddc32a7384403c43720f49b994e2324e0f296c"), // recursion lift_rv32im_m3_16.zkr
    digest!("c5405d37e980f20f74eed6467f2c824a7423c34b87153f6ae2770760a73b783e"), // recursion lift_rv32im_m3_17.zkr
    digest!("c1e9da01e9657e07d041e62ae7d8c846e576c56aeae9361f23287f0e4aa65212"), // recursion lift_rv32im_m3_18.zkr
    digest!("ce0f0a2a8b3c35122084014adfb44a044bb27201f83c8046a1087931df9c6e44"), // recursion lift_rv32im_m3_19.zkr
    digest!("4a8c2e150270691d40abe36ffe773f6bb5e147003e11d80f700a22340ae97b5d"), // recursion lift_rv32im_m3_20.zkr
    digest!("8b5ab317895d451352d1441e7d700230476c9155b95ac534a4e54530cbb56714"), // recursion lift_rv32im_m3_21.zkr
    digest!("9a4d06219da8fa6b5967d140e222a64930183e01de8b624dee7eae1e553a9655"), // recursion lift_rv32im_m3_22.zkr
    digest!("f152a344d8ab5d59dc430e0cf90d9032ee13ed635212fc0550b4fd31e6527622"), // recursion lift_rv32im_m3_23.zkr
    digest!("5c966c3d5f616e708e62534563e17361d43dea0cdf9dac16bef0176e4482a84d"), // recursion lift_rv32im_m3_24.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("5a10d90df6a79d64c117712a2f8f7e34e43611218d9bdc0cb50bcb542ed97b6b");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("c07a65145c3cb48b6101962ea607a4dd93c753bb26975cb47feb00d3666e4404");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 45] = [
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
        digest!("5c620751fb79b1309ef3503080b34821e1f7e91dd122621a2d263b0551a4fe45"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("921fa86eb8234c6b4d8025430967c2260b516304631fb732729b85066961860c"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("de773c08ba15b65be38da731f84630265a3c8606bc302154ec424f4f823e081d"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("9fab9a3fafc72f0ce5864e189e2525127f85c053fc4bdb42f343dc5eb7919212"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("bfa08c6886b3f55047276a0711ddc32a7384403c43720f49b994e2324e0f296c"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("c5405d37e980f20f74eed6467f2c824a7423c34b87153f6ae2770760a73b783e"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("c1e9da01e9657e07d041e62ae7d8c846e576c56aeae9361f23287f0e4aa65212"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("ce0f0a2a8b3c35122084014adfb44a044bb27201f83c8046a1087931df9c6e44"),
    ),
    (
        "lift_rv32im_m3_20.zkr",
        digest!("4a8c2e150270691d40abe36ffe773f6bb5e147003e11d80f700a22340ae97b5d"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("8b5ab317895d451352d1441e7d700230476c9155b95ac534a4e54530cbb56714"),
    ),
    (
        "lift_rv32im_m3_22.zkr",
        digest!("9a4d06219da8fa6b5967d140e222a64930183e01de8b624dee7eae1e553a9655"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("f152a344d8ab5d59dc430e0cf90d9032ee13ed635212fc0550b4fd31e6527622"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("5c966c3d5f616e708e62534563e17361d43dea0cdf9dac16bef0176e4482a84d"),
    ),
];

/// Control IDs for included recursion programs (ZKRs), using SHA-256.
pub const SHA256_CONTROL_IDS: [(&str, Digest); 45] = [
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
        digest!("7d85c28139efdcee0e83ffa6685531d4e706e9c7c549b96537a3123ccf23709b"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("03b79aeec4e5bc14826212d2790913cb47cac570642bef7276beb047595b3fca"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("5670bab85a29c946d0f1b17c50b1ef523d7457f74e7433d79ce98afd5e34797e"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("f439dbe68d53bf9cadefdaf112bc6ec8665b4048e20ed73f86d1e5fc9ca47536"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("dc2582d0a3206a80b46520da0f9fbca45bd571a8bc1dcfd19b475efd6be24105"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("fd5e250e851cefb9e181801ad4d7b0f0c4111bdde98957b5eda73c91ab83f685"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("2c14fa7eae56f5e620b4dc378887630a71939710e3b57c5eace2b88164ffaad3"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("c7038e2ebf79eb2137d6ffb5d49a3d7035d673e664fd540dfe2e0bb5843fe06f"),
    ),
    (
        "lift_rv32im_m3_20.zkr",
        digest!("1fb2a0c4e4b8620433c86a8da1411f5d3f2d3167bf7dcc0034300f65d9f2da90"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("f3123eff2248df9d6e821e902cbbc948fbd962aba8069470b79cef740713c3d2"),
    ),
    (
        "lift_rv32im_m3_22.zkr",
        digest!("95c3afa268da4ecf1c15e7cec1822872be07d2f50a7ea6edf126f69553800e3a"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("6e5ffb8b3f4f982b8e48f3a5bea5a89ee98e23ca1a1782423ec9e60cba6fdd0c"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("864ba026e4af421933369b6462eccb91e7c357b3a16d565be1905736ff0cb286"),
    ),
];
