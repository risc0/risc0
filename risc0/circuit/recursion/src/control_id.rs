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
    digest!("9c21e442dceef6109854304f0f34c86333886428fdde772a74f3b83391b6aa6f"), // recursion lift_rv32im_m3_20.zkr
    digest!("a84a21626eae4156ce800b5c98e6c252daed5e07c6aa0e04df2356741b4e124f"), // recursion lift_rv32im_m3_12.zkr
    digest!("72086c30ab215715b0456d0f98c1c07342ec404456ef7911d0cf5e2a1b481c64"), // recursion lift_rv32im_m3_19.zkr
    digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"), // recursion join.zkr
    digest!("6c21a9211b97803ae5c89d39f9f5e7487eb79b1064ea77732eb95935e448f436"), // recursion lift_rv32im_m3_17.zkr
    digest!("ee76e76c16b2232b39d1380722b41d3d23ff9647171569130f53804e6f3b8916"), // recursion lift_rv32im_m3_21.zkr
    digest!("67ee721bbc4e366de3b6655305e86f453102671529b9d566b283f8583cdb656d"), // recursion lift_rv32im_m3_16.zkr
    digest!("b065b932007e212b597e2b1cc4f205624d93c666135fcb1cda74e85ede68d10a"), // recursion lift_rv32im_m3_18.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
    digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"), // recursion identity.zkr
    digest!("f3143667bbaa0a46980b9b3cb104cf357d6f4536470b742cb3c0c0544e3cd742"), // recursion lift_rv32im_m3_22.zkr
    digest!("68da7d2d7e24bb3173ef594ce5aa2412be35cb26b9f15e1f8f23ca33f9b83517"), // recursion lift_rv32im_m3_14.zkr
    digest!("fc98ed1d3b2f631e05a1b319167f014fd491241274b1e831e2986e358ab1655d"), // recursion lift_rv32im_m3_13.zkr
    digest!("19ed996d1523d51e16a5f6047929a75c23ea9d42b78d92323b3cdf565053df03"), // recursion lift_rv32im_m3_15.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("e502bd6db99ca929a1f0e9614b43c80f74f67039694a84700d01d94559f7780f"), // recursion lift_rv32im_m3_povw_15.zkr
    digest!("69ed8f3e2f08006aa5d5c7424431f1081578f520895c171403e5495c66b39760"), // recursion lift_rv32im_m3_povw_20.zkr
    digest!("cd9994608bb03709a638e871d9f53d2f83d6f355cee13912f1d72d485094166a"), // recursion lift_rv32im_m3_povw_18.zkr
    digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"), // recursion resolve_povw.zkr
    digest!("7c2ea13ae031cd385f21d46b3206191041f55f1961c9e76a64cf593268331611"), // recursion lift_rv32im_m3_povw_19.zkr
    digest!("1d00183fd7f979057fa3b45943ad5b6ddf9a1e5375501a3c3a8aa86213db3633"), // recursion lift_rv32im_m3_povw_16.zkr
    digest!("7da3024be0284f4f8f400740405dfb6268c11c1e320fc64bbfdd93663ecd3064"), // recursion lift_rv32im_m3_povw_17.zkr
    digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"), // recursion join_unwrap_povw.zkr
    digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"), // recursion join_povw.zkr
    digest!("0276022f1248bf6124a63e5bb98e47678628fb55c5f3ce51ee43261df1f3563d"), // recursion lift_rv32im_m3_povw_12.zkr
    digest!("9fe3b11040b2be669fe70e557c00eb0f9ee9ad6a1149510b5d26f5314528285c"), // recursion lift_rv32im_m3_povw_14.zkr
    digest!("391e600337bc7a1b9175b1318612c621b950da3805cf7f3ff8fb9569a84cf942"), // recursion lift_rv32im_m3_povw_21.zkr
    digest!("ea98d1580a1bf1669f2a6d5cf421d05f440f6131c50eb777799e276b07c51876"), // recursion lift_rv32im_m3_povw_22.zkr
    digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"), // recursion unwrap_povw.zkr
    digest!("2edfeb1c56ed2a4546151b50efd6ac179cb406399b572f021a5db312f79f5657"), // recursion lift_rv32im_m3_povw_13.zkr
    digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"), // recursion resolve_unwrap_povw.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("1717bc6729393357f06ed543bdf9894e24863b4f2ae02f0004ef3a5f70e47347");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("c07a65145c3cb48b6101962ea607a4dd93c753bb26975cb47feb00d3666e4404");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 36] = [
    (
        "lift_rv32im_m3_20.zkr",
        digest!("9c21e442dceef6109854304f0f34c86333886428fdde772a74f3b83391b6aa6f"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("a84a21626eae4156ce800b5c98e6c252daed5e07c6aa0e04df2356741b4e124f"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("72086c30ab215715b0456d0f98c1c07342ec404456ef7911d0cf5e2a1b481c64"),
    ),
    (
        "join.zkr",
        digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("6c21a9211b97803ae5c89d39f9f5e7487eb79b1064ea77732eb95935e448f436"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("ee76e76c16b2232b39d1380722b41d3d23ff9647171569130f53804e6f3b8916"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("c14c6a5dcee60c0ec0a19a72c5b80c1e12a43772708c432bd9b73f3fe028884b"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("67ee721bbc4e366de3b6655305e86f453102671529b9d566b283f8583cdb656d"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("b065b932007e212b597e2b1cc4f205624d93c666135fcb1cda74e85ede68d10a"),
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
        digest!("f3143667bbaa0a46980b9b3cb104cf357d6f4536470b742cb3c0c0544e3cd742"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("68da7d2d7e24bb3173ef594ce5aa2412be35cb26b9f15e1f8f23ca33f9b83517"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("fc98ed1d3b2f631e05a1b319167f014fd491241274b1e831e2986e358ab1655d"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("703e9c2c1cb6d73b468a49344e31f86f1fd5ad541036393473de6919934cdb5d"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("19ed996d1523d51e16a5f6047929a75c23ea9d42b78d92323b3cdf565053df03"),
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
        digest!("e502bd6db99ca929a1f0e9614b43c80f74f67039694a84700d01d94559f7780f"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("69ed8f3e2f08006aa5d5c7424431f1081578f520895c171403e5495c66b39760"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("cd9994608bb03709a638e871d9f53d2f83d6f355cee13912f1d72d485094166a"),
    ),
    (
        "resolve_povw.zkr",
        digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("7c2ea13ae031cd385f21d46b3206191041f55f1961c9e76a64cf593268331611"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("1d00183fd7f979057fa3b45943ad5b6ddf9a1e5375501a3c3a8aa86213db3633"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("6322c577f80acd1a78214c57557081501243540fa2a4335f5f57437065ec3128"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("7da3024be0284f4f8f400740405dfb6268c11c1e320fc64bbfdd93663ecd3064"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("dde6a61f759d9618bba919360eb2b848ab2bf61c2fc4373b9b0ee463ce90425c"),
    ),
    (
        "join_povw.zkr",
        digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("0276022f1248bf6124a63e5bb98e47678628fb55c5f3ce51ee43261df1f3563d"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("9fe3b11040b2be669fe70e557c00eb0f9ee9ad6a1149510b5d26f5314528285c"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("391e600337bc7a1b9175b1318612c621b950da3805cf7f3ff8fb9569a84cf942"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("ea98d1580a1bf1669f2a6d5cf421d05f440f6131c50eb777799e276b07c51876"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("2edfeb1c56ed2a4546151b50efd6ac179cb406399b572f021a5db312f79f5657"),
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
        digest!("93734f1b9e3177936ac4cfb533808610fd2ee36daba9698ee73ef7e6cc6237ad"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("f3860ce9c22f259751f5cf81ff7dc59d666f646022c9b37b3a7a5469035b1604"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("34ec3c48ccde5e6384c15d438773d68132482e8dc9211248e96354ae7f77e1a0"),
    ),
    (
        "join.zkr",
        digest!("dc44002689aa7852410ad1c840388d66b8b9a2f6d0c4fb6b3ac6ec2ea17d9855"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("45795ef4c429eab4348cce918150ec10549666dd2b7b06eeca7ce4ce431b2910"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("fc49183bee6ab9886cfe5b0e51ac68b06766c4d72ba34c413296ab7b35915ba5"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("af73de3f0592b27c4cfdcb1c1fda796f79ebb5dd0e4ac1969857cc8bf33a3413"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("75d4881300eafff8f2f54ec477d5d9506ff7d7dd15ef3f813a23ac525e16cd6b"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("430aa6ca103c2aebe66ddef56926da5c7bc75336d22c162f843da91096164588"),
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
        digest!("5a3348cfa03357b4dae24bbc2f6a9e86ae9231cbee685054ef42b3383cc41c71"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("421e1dbc10308fc0329ba2d53b865f6c11dd3cd700535a6ee8d421b0e91f0d84"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("af024952fe4190bdc7d65ab630caa85fe0d93171e1daab13913479673a506162"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("0656f13576fdd62d761d661042ea7b0c89713353688cf4c040bb9ec32f1fcf2c"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("769565c2a9d157ac05a19a5fc404694148150e63a850e6c53b84db71859169e5"),
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
        digest!("c3be5d4afb4e4bbdb9a5c9c723e5f16f59e17db170bb73e00187abfe9b78ee3f"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("861145482f26e8e2eb67ce87565a6eeee20ee3a0b802067320f1c56b031695a2"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("a624677d3d9f5b11c182291ee513f217658428dbfd29b4c8876e36465e9586b8"),
    ),
    (
        "resolve_povw.zkr",
        digest!("51fe537675d705e759c0cb0862f0cb7c5d70ce3dc483efc3cb1646c2b6f0cba3"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("cd7f7b127069d3d2b8e0065a6c466a5ccbe69b8f9d2b4d84a2913a191ab1d28a"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("11b6d80926d69bf650f008eb3902783a358dfcf20a28e6ba484abe14ebc0fdda"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("697ddb038b67275e435c6e8f99e8447428b1d31c358ad6a3352763045641f577"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("9e686249fd96b2f74284ae1dd83172b70b37234a81f07368c917dc652e8ee8e3"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("8cae4f60f8b44780351ec5740118fcc348d8fa0d029f07d2c77a3f9239165319"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("b3d252bde8395371c0ee074358a33cba69530690a3cd6e7a9e10d2bd1482c01f"),
    ),
    (
        "join_povw.zkr",
        digest!("9e97b7ba610dc00ec2628d53274c303eb0d78e6e5c33ef118cf60a5135efa97f"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("c40635cd62a562226eff17434102484771a2aa98f7bf9572bdb64090211bbd80"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("99fbeefcb6a7bd64da96e7448fb101639a8392574bd4d51abe67028406a62874"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("e54c57ee5b4cdb55d4192699b4eae0a5712d7103159cab14b741f543902ba688"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("52ccfec2f2f1176e1aad3474570a04275f7a20c843cdcd4a7174d68ec3a22f35"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("3b5de70ddecc2fabcd3b9b9150ff64e7fc084ecb80f97cac2f9ee11e326087d1"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("c5f80932f35c73aa7aa2f416dd88278a56df45d8d4dcd19cffabef461ca2e15a"),
    ),
    (
        "resolve_unwrap_povw.zkr",
        digest!("1332cc7a1cb90467d849db4ebc4fcc201f81fe0a2ab06d6a398d76b7dd8aa694"),
    ),
];
