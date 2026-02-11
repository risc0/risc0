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
    digest!("7e3b88202336f737e0d93f5d03a1da3be5d8af2fe5ed656073480303c4ffdd33"), // recursion lift_rv32im_m3_20.zkr
    digest!("f95c3d75817b5e211351794adf23b90c9f416d4d23ff2839b95fbe42e56e1f03"), // recursion lift_rv32im_m3_12.zkr
    digest!("ff2e4a2759e8290ba22ae62c798f7134fa0f981444fd3b5ca17131311b828810"), // recursion lift_rv32im_m3_19.zkr
    digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"), // recursion join.zkr
    digest!("2f37d269bac9b90dac83c22fe9c1071924fb394c00f745126b1c0d4cafaeea15"), // recursion lift_rv32im_m3_17.zkr
    digest!("e602214ce7eead64c8e8f74286b84149f9d7b11153902415b73c5237c6e24f5e"), // recursion lift_rv32im_m3_21.zkr
    digest!("4839d33b1d854302b9902c764b62e32f82372b7124459c452edf9e4234e2ff41"), // recursion lift_rv32im_m3_16.zkr
    digest!("c2708f5f55b6770c23a5ca5960cbaf4f5baf8c0c034202665490bd31cf478301"), // recursion lift_rv32im_m3_18.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
    digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"), // recursion identity.zkr
    digest!("6bdb4d43693fba07b81e7550a8d1bf5ef90e3305b17d545b4a0654084c99c157"), // recursion lift_rv32im_m3_22.zkr
    digest!("b255ab054255582362727410588f5c72936d7f35d8d9e22c3bad852264047f38"), // recursion lift_rv32im_m3_14.zkr
    digest!("7111b2200803935126832136229f6776ad56c3653209f6668138ac4a64c45d5b"), // recursion lift_rv32im_m3_13.zkr
    digest!("8a653b62f4706275b8510824ee3d1370488bc05ea10999469483765797421316"), // recursion lift_rv32im_m3_15.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("11d22d6f887eb56d7aa2d111bb85a259a138ea0ac5c52d454105fa1aea889734"), // recursion lift_rv32im_m3_povw_15.zkr
    digest!("0df6c00c502cb955305c456bf3d60435c6908125c21b022445bbd952c7711075"), // recursion lift_rv32im_m3_povw_20.zkr
    digest!("8d157b56a56e13134d7c84773a5e86178a1700638da0524185be9407a1ee0e44"), // recursion lift_rv32im_m3_povw_18.zkr
    digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"), // recursion resolve_povw.zkr
    digest!("a293106a1cfa5128b124420017479522cee4b508f0ea193e7e3dc5328b463a2d"), // recursion lift_rv32im_m3_povw_19.zkr
    digest!("c789dc1e4069565d3fd22512635b0f223ae76103be9ac87186776e4b31413745"), // recursion lift_rv32im_m3_povw_16.zkr
    digest!("8999c4378fa6de1dd0db9d633ad8de11a33f5a42334537678764ca25329b076d"), // recursion lift_rv32im_m3_povw_17.zkr
    digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"), // recursion join_unwrap_povw.zkr
    digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"), // recursion join_povw.zkr
    digest!("9fe4105c4fa541246f768d38344e644e635d060f5488430f25dfa4449bf8ba24"), // recursion lift_rv32im_m3_povw_12.zkr
    digest!("7772f82997024303d036733d2ce5ea12a52d682e710436007f61c05de8fd5c34"), // recursion lift_rv32im_m3_povw_14.zkr
    digest!("2177c56fb4959f4b8d6cd967eff45109b94fe32f6f6c4c724620ed1512f7f01a"), // recursion lift_rv32im_m3_povw_21.zkr
    digest!("2a30b03eb6b08171a9167f078dea150cfd2b3e0c6f853a3ebcba0d371454e742"), // recursion lift_rv32im_m3_povw_22.zkr
    digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"), // recursion unwrap_povw.zkr
    digest!("eb3cfc419617d030e7abce1dc11c250cfc29ac74068d5a39625dec6d7157f610"), // recursion lift_rv32im_m3_povw_13.zkr
    digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"), // recursion resolve_unwrap_povw.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("50942045b7b8345923d83f723fd6cf4d13f89e1f6ff5b2173e2b0d41cc175429");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("c07a65145c3cb48b6101962ea607a4dd93c753bb26975cb47feb00d3666e4404");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 36] = [
    (
        "lift_rv32im_m3_20.zkr",
        digest!("7e3b88202336f737e0d93f5d03a1da3be5d8af2fe5ed656073480303c4ffdd33"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("f95c3d75817b5e211351794adf23b90c9f416d4d23ff2839b95fbe42e56e1f03"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("ff2e4a2759e8290ba22ae62c798f7134fa0f981444fd3b5ca17131311b828810"),
    ),
    (
        "join.zkr",
        digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("2f37d269bac9b90dac83c22fe9c1071924fb394c00f745126b1c0d4cafaeea15"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("e602214ce7eead64c8e8f74286b84149f9d7b11153902415b73c5237c6e24f5e"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("bad53a7778f5ee18b02ea30f2e44c0418ef0885209a79703842b5367b6e6fe04"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("4839d33b1d854302b9902c764b62e32f82372b7124459c452edf9e4234e2ff41"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("c2708f5f55b6770c23a5ca5960cbaf4f5baf8c0c034202665490bd31cf478301"),
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
        digest!("6bdb4d43693fba07b81e7550a8d1bf5ef90e3305b17d545b4a0654084c99c157"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("b255ab054255582362727410588f5c72936d7f35d8d9e22c3bad852264047f38"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("7111b2200803935126832136229f6776ad56c3653209f6668138ac4a64c45d5b"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("d5156406a98a18265e052163dcc8c85f28c5b005dd726b770a339a19897c4326"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("8a653b62f4706275b8510824ee3d1370488bc05ea10999469483765797421316"),
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
        digest!("11d22d6f887eb56d7aa2d111bb85a259a138ea0ac5c52d454105fa1aea889734"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("0df6c00c502cb955305c456bf3d60435c6908125c21b022445bbd952c7711075"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("8d157b56a56e13134d7c84773a5e86178a1700638da0524185be9407a1ee0e44"),
    ),
    (
        "resolve_povw.zkr",
        digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("a293106a1cfa5128b124420017479522cee4b508f0ea193e7e3dc5328b463a2d"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("c789dc1e4069565d3fd22512635b0f223ae76103be9ac87186776e4b31413745"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("c604e3607d8eaf25abd68639f0f01a27b1c3ab23322fb91bfb89a10508ab795d"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("8999c4378fa6de1dd0db9d633ad8de11a33f5a42334537678764ca25329b076d"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("43585d3334f353092b1a8616db58c50717bc646b6e6e9e5ad155d3534afaf010"),
    ),
    (
        "join_povw.zkr",
        digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("9fe4105c4fa541246f768d38344e644e635d060f5488430f25dfa4449bf8ba24"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("7772f82997024303d036733d2ce5ea12a52d682e710436007f61c05de8fd5c34"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("2177c56fb4959f4b8d6cd967eff45109b94fe32f6f6c4c724620ed1512f7f01a"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("2a30b03eb6b08171a9167f078dea150cfd2b3e0c6f853a3ebcba0d371454e742"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("eb3cfc419617d030e7abce1dc11c250cfc29ac74068d5a39625dec6d7157f610"),
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
        digest!("db9cc26b818b5cfb9139d6b2558ca50482f4b544fe76204f2f900c3cd4b72b5a"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("fb4101bb26336d3e16c55c81f4d835aa309dd91cda7fd78c8d6504ac6a32ab79"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("4f6c3cfef8885369c7a6f8dc95b98763204af1bdb0fe1c365475de741268338a"),
    ),
    (
        "join.zkr",
        digest!("dc44002689aa7852410ad1c840388d66b8b9a2f6d0c4fb6b3ac6ec2ea17d9855"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("50e4ae885c7a85f1de0d0485a8a9a08bcff633f16ac027b15ecad19815ec1d1f"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("61a17a52f1de6f9b2c079ab38608c9aea2619f21239bd3ddc728e0db4de10898"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("a0a192e1de919aa73cee2736cdb5a532075eb2b05cf7dfcac3b24a487f726dd0"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("bdc1d1b124c8beb2798ee9aa76f1c999886a9e9b341a0a476bcecc675bbbbae5"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("98004df9dc196300b3fb14452934cb0e9e3e2064887b31e35269550f3c324c16"),
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
        digest!("0e1b3ddd6c40610385102ffec75793bb6c791fa21c9da9aec474a263478b030a"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("0522a904388c28f2314f66ab250a710489e67ba7f7bd54cbe158c2592cd22a56"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("908782d64069de0164aea60391646de1055330e3a274889e670ea1bc56818ed5"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("cd674964b93ba67efdded64781b61fd320888c87129b5147b44a890cbf01cceb"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("31de0bab8859ec21d955b556a59790b027cb2ce64a6c0397c9cc5a53df7d6b75"),
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
        digest!("6438ba94d6e2870514c9185823f00c38ab9e6b4c86e6f7c24554093e7d5245cd"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("e98176b37926ff1dcd36f75b47f0818db1dc9c944d779a19f3f6adea1f049ead"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("97d480646e0264c7b12a75d9a092ce49c75015145a616ddca01f2050d2e4a5b0"),
    ),
    (
        "resolve_povw.zkr",
        digest!("51fe537675d705e759c0cb0862f0cb7c5d70ce3dc483efc3cb1646c2b6f0cba3"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("83ec84ebf5c6e832c5d2432bc8e1eaaa737802b8c2ce585a016413eef10ded54"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("a811a4bb772ec25989976225a3afdaa02e17b326878ed32e933b9d2405ca5dc6"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("7afc5fec403f204486f45bd60199fd7b329e8edd53a09e6489643329a79aa89d"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("2f74e2489db62851a408a8f94180c7ac3e077000872a5b98aaa2f1ff6c7bb87a"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("8cae4f60f8b44780351ec5740118fcc348d8fa0d029f07d2c77a3f9239165319"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("3d1edf87bd86b8f02f324bb2cbc9d6eeb0c1635fe964bfe0bf59f64ccecdaa99"),
    ),
    (
        "join_povw.zkr",
        digest!("9e97b7ba610dc00ec2628d53274c303eb0d78e6e5c33ef118cf60a5135efa97f"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("e07f23f1b8bfd38bf5f0415ebc0f07cec0b189b1780037b2819e2dfeccd0d4da"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("d6a71635d6bf0d84151423cf2da5f967b404dc26bc8973a27c374b2bbe1b7cd5"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("0c0ce14a78c862cba9404be7bb05e5514e184435dd8eda27e6050295cb431052"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("69eb3726b836b252b06859ee4ba7fa8e84bc2b2f934ea2373482c8807bc47f39"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("3b5de70ddecc2fabcd3b9b9150ff64e7fc084ecb80f97cac2f9ee11e326087d1"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("99a6303df6188f998194e05960e84bdbd3bbd7fa7366ae67f62c2fa218d72491"),
    ),
    (
        "resolve_unwrap_povw.zkr",
        digest!("1332cc7a1cb90467d849db4ebc4fcc201f81fe0a2ab06d6a398d76b7dd8aa694"),
    ),
];
