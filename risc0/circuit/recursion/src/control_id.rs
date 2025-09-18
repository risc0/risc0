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
    digest!("1f33a90515706f41340af919314e4c3cc85442479531710904c6ba131f4b2962"), // recursion lift_rv32im_v2_14.zkr
    digest!("762711134793e91997139e05d049442c4783be08ab24b573ec13523133e4e065"), // recursion lift_rv32im_v2_15.zkr
    digest!("3251734732c79403dcf82c458068844c4ede4b2218d5e30207f98c6255a9e666"), // recursion lift_rv32im_v2_16.zkr
    digest!("685b893a7975490216a62f69e52f0f0dacacca483ecb3933109f6c16f62c3065"), // recursion lift_rv32im_v2_17.zkr
    digest!("d43be91060188570930b455ba45e5c58a0476161ab0b1366553eff0af6343718"), // recursion lift_rv32im_v2_18.zkr
    digest!("7161d0174fcba64a3a367938452d2f01cfd5440f360be1184643224e68f06113"), // recursion lift_rv32im_v2_19.zkr
    digest!("50de0a336e6efd3655b0b8380d39d55445de67388d2f9e269d99b401e7031a1d"), // recursion lift_rv32im_v2_20.zkr
    digest!("1f963246a2b1ae408a5658506adb0a163c33d56d6cdfc16a1f0889099117e214"), // recursion lift_rv32im_v2_21.zkr
    digest!("7ec4145feeba1a6dab6e8315e82d2d0ddc73fe70c5da2d3b380dff2116488f14"), // recursion lift_rv32im_v2_22.zkr
    digest!("a26e2311fee31962a4590c62984f5f4f7f1f7b2a1f78ec58eefa4233a06cef4b"), // recursion lift_rv32im_v2_povw_14.zkr
    digest!("ffbd691e41b59650a4c99f0f36f0184172bc4d014677c7642731bd299ac68253"), // recursion lift_rv32im_v2_povw_15.zkr
    digest!("a3053b716d4cf306da0d9717424dd30ab7f73b69d1ccd8176f55c62f4a8ae337"), // recursion lift_rv32im_v2_povw_16.zkr
    digest!("e6c3656f7cd6b4174d484f4fb7c0412f2524202352fc5d4c25b98310b427cc00"), // recursion lift_rv32im_v2_povw_17.zkr
    digest!("afcbe164cd5c4466f8784153cd519f5ac426ef15cd09d71b6dad270c15e51b2a"), // recursion lift_rv32im_v2_povw_18.zkr
    digest!("85f40b184fd27a5231a38f30d0b2c1088565f45a49ad2d493b0b060d57490929"), // recursion lift_rv32im_v2_povw_19.zkr
    digest!("7adb3c1c89a8394565569d73cb7ee743e5b643300be6af3d6d2cb85ba7b96100"), // recursion lift_rv32im_v2_povw_20.zkr
    digest!("4709d9087b16770393627a4716f7c839198b8372de98e1034c6b1d15fe96044d"), // recursion lift_rv32im_v2_povw_21.zkr
    digest!("247713163666b16e0550164ec062c03c6a6aee6ffcec901582b3e03174701f46"), // recursion lift_rv32im_v2_povw_22.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"), // recursion resolve_povw.zkr
    digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"), // recursion resolve_unwrap_povw.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
    digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"), // recursion unwrap_povw.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("3b304d1098ad401d3a04bc11976f476633a71b482b7851189663ca61209abe45");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("c07a65145c3cb48b6101962ea607a4dd93c753bb26975cb47feb00d3666e4404");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 32] = [
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
        digest!("1f33a90515706f41340af919314e4c3cc85442479531710904c6ba131f4b2962"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("762711134793e91997139e05d049442c4783be08ab24b573ec13523133e4e065"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("3251734732c79403dcf82c458068844c4ede4b2218d5e30207f98c6255a9e666"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("685b893a7975490216a62f69e52f0f0dacacca483ecb3933109f6c16f62c3065"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("d43be91060188570930b455ba45e5c58a0476161ab0b1366553eff0af6343718"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("7161d0174fcba64a3a367938452d2f01cfd5440f360be1184643224e68f06113"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("50de0a336e6efd3655b0b8380d39d55445de67388d2f9e269d99b401e7031a1d"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("1f963246a2b1ae408a5658506adb0a163c33d56d6cdfc16a1f0889099117e214"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("7ec4145feeba1a6dab6e8315e82d2d0ddc73fe70c5da2d3b380dff2116488f14"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("8ffc3c3a6e14046750a524642cecf952537fe571db049133457d5c422b0c5c08"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("26fe2a6f2f956d5c9a0f6f1b45f610611c5a0e14b630822e108c801cd253de0c"),
    ),
    (
        "lift_rv32im_v2_povw_14.zkr",
        digest!("a26e2311fee31962a4590c62984f5f4f7f1f7b2a1f78ec58eefa4233a06cef4b"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("ffbd691e41b59650a4c99f0f36f0184172bc4d014677c7642731bd299ac68253"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("a3053b716d4cf306da0d9717424dd30ab7f73b69d1ccd8176f55c62f4a8ae337"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("e6c3656f7cd6b4174d484f4fb7c0412f2524202352fc5d4c25b98310b427cc00"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("afcbe164cd5c4466f8784153cd519f5ac426ef15cd09d71b6dad270c15e51b2a"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("85f40b184fd27a5231a38f30d0b2c1088565f45a49ad2d493b0b060d57490929"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("7adb3c1c89a8394565569d73cb7ee743e5b643300be6af3d6d2cb85ba7b96100"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("4709d9087b16770393627a4716f7c839198b8372de98e1034c6b1d15fe96044d"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("247713163666b16e0550164ec062c03c6a6aee6ffcec901582b3e03174701f46"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("bfa73324742bd63ebcb364364f80d71619ccec600fe978049bc7936458dcb744"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("a956ae495b8e610e4524bc10cc86210e02b664277ad07a700f21f3734b9bf20b"),
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
pub const SHA256_CONTROL_IDS: [(&str, Digest); 32] = [
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
        digest!("fad3f85334d148983d1623f96158fad169f7b647a2138d394c33d43ae1c172fc"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("e094b34337cacf593345d15b3badf2081afb94531bb518946fd1f8b2a3c02104"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("bce3437574ca42bacce2e4d98f9e2fbcc68ff709fcc919e7a420a24d499bcdc5"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("23e91ebf9444175036d05103c8c330c98a0dce06bdf81e009e947e3e0d69a64f"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("ff5f7206aa5fa7721df9ed8a971f4b43a6c43e3cb240f2fb20cfba859c29b590"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("693d67ef59feddbb49302da5116cccc3fa0e5987cf942d0e549c1c0a612c8e52"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("6f8761d7c36df66a94c312a9764055d7ea14a915ab73b2737fa92f7276e5adc7"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("09268a7576a5f2c64f1dd49444847bd84ee137b29e2d402160b8636c6a6e147f"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("5811f7cc63f1a73fcc5d735a61370c6f539acff2902ed30adf10229c1af5795e"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("bad455ee45f9e5646ee93eabea554d3d87b351fb4e63c2f3d6e253866e7c916c"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("34f3c976700d9f0f8f8e0469ccfa2c743046e43c68c0ef9571d7e0a414def61d"),
    ),
    (
        "lift_rv32im_v2_povw_14.zkr",
        digest!("c78518cb657e1326f433635da24f95d684e5c868a8a2bdf72c4a9b1f8820c7f4"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("045943e42922549cdcda4ac545e80567f445f950f23cc417957b7963b3459bc6"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("14acaaa3b9c99bd324155e9d2c98b51b413ec31201b272d74bb8b9a1cd751360"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("d6c669709931834c5e39a8d30169d50ca0fb1dfa6dc3307b31b0123a652f2826"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("9610456fcd41cc7a33a2372c5af8d33a4676ab91e194020736103d2fdfbb4b80"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("df254467d4ece97c03d476dad9b68b59348dd6949b30cdbca4b7bdfc51e3a369"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("612830e1a0edf8c9ee99926399a62c8e418aa3f546bf608c67550163d9c10f89"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("1b1669ddc77369b591d878c7213a507eb93c51bb226d2c43381c16be8d336202"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("cda93eed7be151560c24ac1ab7fa0d3baafc551dd0e83040e89c116c5f931dfb"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("25d4ac6e9df7c68cefb956e49de90b4e9d6091f08af0a95f89cd0284330cdd43"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("b0af89a937da77a3ef308d04819a265ecd87158b397b8540964478ed0b81059a"),
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
