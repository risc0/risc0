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
    digest!("712c2a63ebe77c08a43b952bc7c78b415bc66269f9298c2e9def025ad0e03d14"), // recursion lift_rv32im_m3_12.zkr
    digest!("fcdeb772213d47564746b3416157bc42785712435389127481e69052abed5b6b"), // recursion lift_rv32im_m3_13.zkr
    digest!("9a56cf03d0e60c692b577e50f416d042174dbb3d8d4d76506d2b7d5907330623"), // recursion lift_rv32im_m3_14.zkr
    digest!("d0cc5b0951cacc677cfec37329e33d747b63b40251d6d949fa03ca3e13403d3a"), // recursion lift_rv32im_m3_15.zkr
    digest!("7af06c69af43e86fae84f430c01403056cddb14e63aa90018d36f300439e0526"), // recursion lift_rv32im_m3_16.zkr
    digest!("00571a0578d1e114f5d6f83db5d5d86869590f055cca484fff4f1c5ce404b13d"), // recursion lift_rv32im_m3_17.zkr
    digest!("a30c4f3e68b60d5b7c9c8d739ef2e8039c178231f36dc92484c3a33577e9e338"), // recursion lift_rv32im_m3_18.zkr
    digest!("a8ecd60892253064e4be6275e904e347659644197b1e713e9e9a2928341c4e44"), // recursion lift_rv32im_m3_19.zkr
    digest!("ad28dd334dc467349b91c601d6377262ccdf1e09494f8633d130db4e8718145c"), // recursion lift_rv32im_m3_20.zkr
    digest!("e77b2e5f84b34920f0d464549269fa65f9dd025e212cf047f324e45b948a1508"), // recursion lift_rv32im_m3_21.zkr
    digest!("77919367ece7b51fb3780d088d9e173271d5eb098d953f5c063d2b5201cbbd4e"), // recursion lift_rv32im_m3_22.zkr
    digest!("92922a1d442a194d511a602df013094bc78aa71195a24f66f28aa53029d82904"), // recursion lift_rv32im_m3_23.zkr
    digest!("53a0ef34a433834b7cb37e023b3b7752dede5626d6ae8c456815ce64d9bdef32"), // recursion lift_rv32im_m3_24.zkr
    digest!("64c20b23e145912ca3cb45141ef9b976a39e6667154bb42ef1bd8a70171e8221"), // recursion lift_rv32im_m3_povw_12.zkr
    digest!("655cad3382bfe71de736882a245192589046613b3dd0c22cb0481c219cc68f47"), // recursion lift_rv32im_m3_povw_13.zkr
    digest!("44c2103b0982216c5909b25677936b42a9155b37fccb7d4b78f1b93dc67e333f"), // recursion lift_rv32im_m3_povw_14.zkr
    digest!("1260db2c72f27d2c20cd0300545bf425c282191eef6e575d6aba657485b0ef33"), // recursion lift_rv32im_m3_povw_15.zkr
    digest!("1c6a733c564a8f4ddf2927084ee3fb723b8eb5762ed95d1ceb13a2236dd93239"), // recursion lift_rv32im_m3_povw_16.zkr
    digest!("2a94db6614434517018a2311d9f8353a5c4b0e4d379ae02869a7f30ff896fc20"), // recursion lift_rv32im_m3_povw_17.zkr
    digest!("dabef04844f533618f107b68cbfa77622269f821fa12fe633ec32f7446d5dc1e"), // recursion lift_rv32im_m3_povw_18.zkr
    digest!("ecb1a611022cf9600490d55f0856f7464794230f362adb7261505118e42ae829"), // recursion lift_rv32im_m3_povw_19.zkr
    digest!("8c24c13484aac32fb15dbc3f038732095a2cb41893531c35097ef3266657d532"), // recursion lift_rv32im_m3_povw_20.zkr
    digest!("57850014111a1719505e81264fd4a5418e3b9a48075130510e723240b037076c"), // recursion lift_rv32im_m3_povw_21.zkr
    digest!("dea0274ef0e9955cbb68f811056f306526d8b260da6a7f593d631f49691cfe1d"), // recursion lift_rv32im_m3_povw_22.zkr
    digest!("fb113e36ff036914c2da426c1213252fe62ffc438d2c776c5c8a55555e0c6220"), // recursion lift_rv32im_m3_povw_23.zkr
    digest!("601e116614e2fd0448f6254428c6e125a12182360225b046e0761b6178a6fe20"), // recursion lift_rv32im_m3_povw_24.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("1515c06bccd4904a17cb072f53184151db9db33765e7e653cb89871573d9db21");

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
        digest!("712c2a63ebe77c08a43b952bc7c78b415bc66269f9298c2e9def025ad0e03d14"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("fcdeb772213d47564746b3416157bc42785712435389127481e69052abed5b6b"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("9a56cf03d0e60c692b577e50f416d042174dbb3d8d4d76506d2b7d5907330623"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("d0cc5b0951cacc677cfec37329e33d747b63b40251d6d949fa03ca3e13403d3a"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("7af06c69af43e86fae84f430c01403056cddb14e63aa90018d36f300439e0526"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("00571a0578d1e114f5d6f83db5d5d86869590f055cca484fff4f1c5ce404b13d"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("a30c4f3e68b60d5b7c9c8d739ef2e8039c178231f36dc92484c3a33577e9e338"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("a8ecd60892253064e4be6275e904e347659644197b1e713e9e9a2928341c4e44"),
    ),
    (
        "lift_rv32im_m3_20.zkr",
        digest!("ad28dd334dc467349b91c601d6377262ccdf1e09494f8633d130db4e8718145c"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("e77b2e5f84b34920f0d464549269fa65f9dd025e212cf047f324e45b948a1508"),
    ),
    (
        "lift_rv32im_m3_22.zkr",
        digest!("77919367ece7b51fb3780d088d9e173271d5eb098d953f5c063d2b5201cbbd4e"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("92922a1d442a194d511a602df013094bc78aa71195a24f66f28aa53029d82904"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("53a0ef34a433834b7cb37e023b3b7752dede5626d6ae8c456815ce64d9bdef32"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("64c20b23e145912ca3cb45141ef9b976a39e6667154bb42ef1bd8a70171e8221"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("655cad3382bfe71de736882a245192589046613b3dd0c22cb0481c219cc68f47"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("44c2103b0982216c5909b25677936b42a9155b37fccb7d4b78f1b93dc67e333f"),
    ),
    (
        "lift_rv32im_m3_povw_15.zkr",
        digest!("1260db2c72f27d2c20cd0300545bf425c282191eef6e575d6aba657485b0ef33"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("1c6a733c564a8f4ddf2927084ee3fb723b8eb5762ed95d1ceb13a2236dd93239"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("2a94db6614434517018a2311d9f8353a5c4b0e4d379ae02869a7f30ff896fc20"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("dabef04844f533618f107b68cbfa77622269f821fa12fe633ec32f7446d5dc1e"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("ecb1a611022cf9600490d55f0856f7464794230f362adb7261505118e42ae829"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("8c24c13484aac32fb15dbc3f038732095a2cb41893531c35097ef3266657d532"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("57850014111a1719505e81264fd4a5418e3b9a48075130510e723240b037076c"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("dea0274ef0e9955cbb68f811056f306526d8b260da6a7f593d631f49691cfe1d"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("fb113e36ff036914c2da426c1213252fe62ffc438d2c776c5c8a55555e0c6220"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("601e116614e2fd0448f6254428c6e125a12182360225b046e0761b6178a6fe20"),
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
        digest!("2192a014f0f3ad3d21c15742e856532d080ff28d95f13b9fcd7973b7469f2b3c"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("0ee4b788c27703df2820ba8b945a6b55be7f1256e6ed8136917dea17504b18a3"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("2a29021412788d3c96e7684e018d964444fe00407554233a0f7f29e991f5663c"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("60c14cc22166eb12db1181fdf331988078716e9f5d514c0bef7d23f20100a217"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("196d4a64752cf0db3f52101294eb65e62deb41506b5b16f68044983b0aede356"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("40cc829bb503ef9ee7744d6dd850cf91a0f368713952b2e19eb8a890821a76bb"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("25c9f51fa5043a7519da6c5873422446a121fb8cedb4ff3953b765ebbcc70bef"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("97440545bb129302078e313efee7414bebc3a27209d83b2ee39b8d2712c32084"),
    ),
    (
        "lift_rv32im_m3_20.zkr",
        digest!("b9c8aa02acc5c57b2730297fa104b1aeae18d1f31ef1d536eaf50265557ca125"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("28219fc80ce715b82830cc0f341adbab4ec5494a1bae84be6b05901f58ca29f4"),
    ),
    (
        "lift_rv32im_m3_22.zkr",
        digest!("9a83fb35f7b6273f59469e9d123bd72ddee2939535348d17ff9c692b982e6032"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("5afc01e8ca236f41c5053e00075bf3a57fa82f1941cd0b013316dabfae443f8d"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("465d9143637348b43fc7cf3f7faf9c2b09a49728eb5d28699ae78811d20e80f9"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("446deac37a38e5b7027c7fa66e3aa72c53968c615ff93bccd09be334af962fd6"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("2d3edd4864fb5cb0be1a40e77d58ff578d0abf79c7b6bb6430557727ef5a98fb"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("c98b4151e572539dbf6e862174a5005aec9a473350bfb14d6aad73c4f164d959"),
    ),
    (
        "lift_rv32im_m3_povw_15.zkr",
        digest!("6640b42430a2b33d6baf36ce6d4a3712ffec563f00d3216bfa3ffb9738682524"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("0c4771513483df3b4083d5b0be67b21d85cfe5b0bc6baf6cc6b613cfbe32c32a"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("bed170496ef22d76909cc00331c7e59ff826b357567b742e1c3f063fb760a710"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("5d3727f2be5356d1e294fa5e037ce214638e8f8a5d8ddb257b3cf09fd8d0e929"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("9a94131ff21416106c9afc155e1e07e747fd9da8633b7d8f232b14b7e22023d4"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("d554836cfdb7848d3a7322e91f1900505beefec1f51b02d4d5d34c2e0f1ee6c4"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("82378dbc6cb102179c0d784953f3a6598ba31a78d426aaa0a4735457a8900ba6"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("0ac27b4f838bac0a57408cbe2e640b4f0af67b6d0b98d810ee4580f848c7e54d"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("2f34d50bc34e8a065ada5c21693b6d03433799254b688c6ee5d2c10d183af362"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("c843deee19cc2544c3341d17bd5597f0786466393da7bc71d2d37f3a05977e5d"),
    ),
];
