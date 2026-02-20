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
    digest!("40c69e47f34c481feea8a93e484b4e07af6293600ddc7c5c2dae8833f2e00304"), // recursion lift_rv32im_m3_20.zkr
    digest!("454b5922f7f5e5480072f1151e268c2afd954102390296674b6eae73db6abd03"), // recursion lift_rv32im_m3_12.zkr
    digest!("e8b4c017e450a6659a1fa43df602bf65f2191275caf81166ffdfbc4173b93022"), // recursion lift_rv32im_m3_19.zkr
    digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"), // recursion join.zkr
    digest!("cd3e0a52700975123f0558535c902445ba0e794b8650db2a3c46615803b86706"), // recursion lift_rv32im_m3_17.zkr
    digest!("bde77f3b4b45092878bf7873c8386c4a275c3a3666eaaf4e7c35d012d3c6806a"), // recursion lift_rv32im_m3_21.zkr
    digest!("dafa1422aa5f404fe9028506fd84ff6ebef4d1092208306c945209350d73686e"), // recursion lift_rv32im_m3_16.zkr
    digest!("930cc050d5baf937af4d553cc487ff6e240ecc2ba8ee9a15968c1809f56d6c6b"), // recursion lift_rv32im_m3_18.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
    digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"), // recursion identity.zkr
    digest!("e6ccf36a978ced4d39709a2dc2662307cd886919bb97a8233ef13b32efc29468"), // recursion lift_rv32im_m3_22.zkr
    digest!("c0199b254f69b73aa99c1741081b3b11c4a3c911e56b2d4e92b0f224b538543d"), // recursion lift_rv32im_m3_14.zkr
    digest!("04713164e286141bda0d40582a6ad31c8bac3956c5de9719080b344db2d9863d"), // recursion lift_rv32im_m3_13.zkr
    digest!("7ec92e64aec8961c73f7f0520805551206d4a32f4284186c6c43f06b5a743563"), // recursion lift_rv32im_m3_15.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("7db89565cf743d511d047d249912633c7a2ea171b813db6b7c0c84014e5f723d"), // recursion lift_rv32im_m3_povw_15.zkr
    digest!("b49b910d79107a29aa07f2735dca874104bf0634a11ebb5d8610ca03d775f152"), // recursion lift_rv32im_m3_povw_20.zkr
    digest!("34f8b956a9975c6e1248dc02da56be494beba001e610d9738f5c8a0481d98a3f"), // recursion lift_rv32im_m3_povw_18.zkr
    digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"), // recursion resolve_povw.zkr
    digest!("abe32c5b3699765c40e94111ed88460da8b08c2cdf2b0642e10b474cefa1e04f"), // recursion lift_rv32im_m3_povw_19.zkr
    digest!("6658052bd6c472692570a80647cd4003ff932d5a93df701832935e542b10ba44"), // recursion lift_rv32im_m3_povw_16.zkr
    digest!("30799a4ce9f5a83c41edf52a95b877535cf136465a1d470850785f1e8a94b622"), // recursion lift_rv32im_m3_povw_17.zkr
    digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"), // recursion join_unwrap_povw.zkr
    digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"), // recursion join_povw.zkr
    digest!("2857852c8a0c20174c4282169b163d3afe3ec67237ed9677ac576d376e72dc64"), // recursion lift_rv32im_m3_povw_12.zkr
    digest!("7838d02f3f5884245dd6300a719e67659f87055a4de75b016fc20a6de0cabb36"), // recursion lift_rv32im_m3_povw_14.zkr
    digest!("0b2c171f0b155054b861ab1e2206d725dd6ceb3bcf9ebc48b4f34249db1aca23"), // recursion lift_rv32im_m3_povw_21.zkr
    digest!("e6a8a5402e5bec5a16ca386102083a0d6fa7596d06f78d5952f25765e378742b"), // recursion lift_rv32im_m3_povw_22.zkr
    digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"), // recursion unwrap_povw.zkr
    digest!("7545b747bfdec72dc4989a1a071f9c12ae05cf6c10f61e7182471a1ce4a82642"), // recursion lift_rv32im_m3_povw_13.zkr
    digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"), // recursion resolve_unwrap_povw.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("8d3d3217d5f1cc1e7ced740ef427553c897d990be857bc5d9c2c7e112e2ddf65");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("c07a65145c3cb48b6101962ea607a4dd93c753bb26975cb47feb00d3666e4404");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 36] = [
    (
        "lift_rv32im_m3_20.zkr",
        digest!("40c69e47f34c481feea8a93e484b4e07af6293600ddc7c5c2dae8833f2e00304"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("454b5922f7f5e5480072f1151e268c2afd954102390296674b6eae73db6abd03"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("e8b4c017e450a6659a1fa43df602bf65f2191275caf81166ffdfbc4173b93022"),
    ),
    (
        "join.zkr",
        digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("cd3e0a52700975123f0558535c902445ba0e794b8650db2a3c46615803b86706"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("bde77f3b4b45092878bf7873c8386c4a275c3a3666eaaf4e7c35d012d3c6806a"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("9f402631d3ab284362894e1f7dfc7f10de92e56cd3130715abe6234764da7575"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("dafa1422aa5f404fe9028506fd84ff6ebef4d1092208306c945209350d73686e"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("930cc050d5baf937af4d553cc487ff6e240ecc2ba8ee9a15968c1809f56d6c6b"),
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
        digest!("e6ccf36a978ced4d39709a2dc2662307cd886919bb97a8233ef13b32efc29468"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("c0199b254f69b73aa99c1741081b3b11c4a3c911e56b2d4e92b0f224b538543d"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("04713164e286141bda0d40582a6ad31c8bac3956c5de9719080b344db2d9863d"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("cf37e42ac9d0be26e794f922a2df8e5e4508fb060c9cf8710fc5cb53b925bf6b"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("7ec92e64aec8961c73f7f0520805551206d4a32f4284186c6c43f06b5a743563"),
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
        digest!("7db89565cf743d511d047d249912633c7a2ea171b813db6b7c0c84014e5f723d"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("b49b910d79107a29aa07f2735dca874104bf0634a11ebb5d8610ca03d775f152"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("34f8b956a9975c6e1248dc02da56be494beba001e610d9738f5c8a0481d98a3f"),
    ),
    (
        "resolve_povw.zkr",
        digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("abe32c5b3699765c40e94111ed88460da8b08c2cdf2b0642e10b474cefa1e04f"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("6658052bd6c472692570a80647cd4003ff932d5a93df701832935e542b10ba44"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("f6041b4c71999161545e3243eb867a4363ea4c72eed5ab0bcd24735e1dda9115"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("30799a4ce9f5a83c41edf52a95b877535cf136465a1d470850785f1e8a94b622"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("d98cc95313daec768007576b73ea355bc6c41c56824b002b79675e432f618770"),
    ),
    (
        "join_povw.zkr",
        digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("2857852c8a0c20174c4282169b163d3afe3ec67237ed9677ac576d376e72dc64"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("7838d02f3f5884245dd6300a719e67659f87055a4de75b016fc20a6de0cabb36"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("0b2c171f0b155054b861ab1e2206d725dd6ceb3bcf9ebc48b4f34249db1aca23"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("e6a8a5402e5bec5a16ca386102083a0d6fa7596d06f78d5952f25765e378742b"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("7545b747bfdec72dc4989a1a071f9c12ae05cf6c10f61e7182471a1ce4a82642"),
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
        digest!("f671ad80426f066fa79c95c8988ff10b0d547dcb6466b596fb9e5e592943b1bc"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("83fafc022bd5ecc1c6aff4554d33b7324c3f783b53b932d1ca8ba422fca76cba"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("0f04e9db23d5334f3dfc1129ee798f4ae4187162f68dcf4877f35b444fe0c2c0"),
    ),
    (
        "join.zkr",
        digest!("dc44002689aa7852410ad1c840388d66b8b9a2f6d0c4fb6b3ac6ec2ea17d9855"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("2505bd6cc572053773ee1755897ca8daeeb97827ee60b3d3fd8f05c6289922f1"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("beb56da3ef556cf7e7d4bb36cc29c0f2c81ce546de29cc6442aba5d3ffb5205d"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("21a88d31b685668505926bcef941eca521df188bdff5a4b415fbe6ca1b28812a"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("bff94e25f8a9bf588d8c3238c1791b0722bff0ebb95ea7b6b0593ffe559dc21c"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("85b9ed8cb434d65fd7614be62dc74707cbdb9f525324d52d9f47710d3b171962"),
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
        digest!("2cf6ed72aa7c5df2057a029183168ba4c72e054a89554eaff36567fedb74f149"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("3b46b3f0fa5192e9d0fe773b5d7c60fa29faeacab657d120d8512b8c95e03e3a"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("3a90ad6e8d01205df78eb19a0fc4edef184ed905cdf0c7457eb8ce6a53d8edea"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("74f0794d0e5ec88eac9995aac4515cf193121137c983822f72550ea046d2b982"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("c64d6277fa8ec0625fe03db2627c56453d07d13531b67b06948a8c13d8df0a7c"),
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
        digest!("97de05e52309375e10d13dade3ab8e8f131581aea88da94146d4034dd0a6486a"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("d43512e1cd5e107e08e5f9376d6d715a6f1b368476a0d0e3549d10b57b33344f"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("260703add36cb34ed46ce02d874ec482e433cb3251b776818350171df49692e8"),
    ),
    (
        "resolve_povw.zkr",
        digest!("51fe537675d705e759c0cb0862f0cb7c5d70ce3dc483efc3cb1646c2b6f0cba3"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("32d65f80590994f173b72f70c06290252387691ec500173b8430e8f59bfebde0"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("b7bb692ebf0ded1a4e2f54eba74d2312730d15a17275fac7323ca68c4d9793be"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("319f6b6319144df4acf08d9a5f07309b353dfb8fd5ad8909c44824490ce0e8e6"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("b83bc0a77526ca28f3bb075f11eac3c03160c18e63a446d5aa0e2b7260df188e"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("8cae4f60f8b44780351ec5740118fcc348d8fa0d029f07d2c77a3f9239165319"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("22d995512b99a83633355e2d8ceb488d6defaced0cef96dd4d8f60052b00e1a9"),
    ),
    (
        "join_povw.zkr",
        digest!("9e97b7ba610dc00ec2628d53274c303eb0d78e6e5c33ef118cf60a5135efa97f"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("2492518afaf0750422e6115f1796a106dd51a50867a10cbc74e5fe0f4f08b45b"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("6a992b5338802f37b0bbf8dff896221d9d0b0d783dcd47f8ec4ee2de87cd7a82"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("a9fdc2af777f8b4a5f4206d55f528bf6ce74d80b4f4852a8498155265b3e6bf7"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("030214c753f5f6a543a5bc4942ca6bc6cd07e00bf98995bc79484f7ca1cda312"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("3b5de70ddecc2fabcd3b9b9150ff64e7fc084ecb80f97cac2f9ee11e326087d1"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("13adf221ef247201785db04fa79ea86e93199719fb2a024fe452c7b8d03c410f"),
    ),
    (
        "resolve_unwrap_povw.zkr",
        digest!("1332cc7a1cb90467d849db4ebc4fcc201f81fe0a2ab06d6a398d76b7dd8aa694"),
    ),
];
