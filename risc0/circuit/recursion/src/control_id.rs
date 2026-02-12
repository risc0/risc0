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
    digest!("92c9cb01af953e1196065530bd1a530ec927b65cd76037316b9f0b0024c51a3a"), // recursion lift_rv32im_m3_20.zkr
    digest!("f5cff93555beac4026452f1dc0b27d6635d28f67eb2d514c33f0392ed0450700"), // recursion lift_rv32im_m3_12.zkr
    digest!("7f1c610d0a2fef2b11ec9b4230815811eb5722455bc54d497d1ac208223dff5a"), // recursion lift_rv32im_m3_19.zkr
    digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"), // recursion join.zkr
    digest!("7181cf17e430836b8462a3133a2aad3d063a5e32e2391262b4781e0ba777d53a"), // recursion lift_rv32im_m3_17.zkr
    digest!("cf491930b82127394999f612536e5e5f408d73030532b11c82b61638de131368"), // recursion lift_rv32im_m3_21.zkr
    digest!("f3b8a212a369563a592e925cd7eb9620692d4a5fc2455860b5d5dc1750752d49"), // recursion lift_rv32im_m3_16.zkr
    digest!("17bc4e72c8ab2b65cb7a834de3e8b525d81d674255d28b11fd18f851b9ef2601"), // recursion lift_rv32im_m3_18.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
    digest!("0d79bc33b4760b4783cbb96fdc87724c7e0c463eb0ba1b2705d39f43c698bd2d"), // recursion identity.zkr
    digest!("266af82fcfeea64cd8334c13e8d6c769f39377170d629b13c36a600bf9df200f"), // recursion lift_rv32im_m3_22.zkr
    digest!("9f2c3d13e250c43e5edcf759cdabc62ecf1d403b250f3d48e9fa0251895bd061"), // recursion lift_rv32im_m3_14.zkr
    digest!("4d3d7a6ecc77cc52fb9918708b81da6e098047048d5ccd245aa86d1720e70d5f"), // recursion lift_rv32im_m3_13.zkr
    digest!("51072358ab925c6bd1bd524f09fc702234caea4f6b865e152681cc223f8e2042"), // recursion lift_rv32im_m3_15.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("9ff86f235384c3406f2c6f76b21a8e239edbb20c145b0566c62c0207e24dbf01"), // recursion lift_rv32im_m3_povw_15.zkr
    digest!("796c9845f0043a2cf732036816d0281f8258a549dd6e0a612815a8547c73ce45"), // recursion lift_rv32im_m3_povw_20.zkr
    digest!("ec2e7f38a83a154dd9762b1dd4dd9d0e5168cb5e8fafeb71a694665e84c9fe5f"), // recursion lift_rv32im_m3_povw_18.zkr
    digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"), // recursion resolve_povw.zkr
    digest!("5bc0064ed90c7529c8bf5e41c839321e85bb40291e83fd1c877e8c191b62f02f"), // recursion lift_rv32im_m3_povw_19.zkr
    digest!("004d2c3e2594bf48115e56669b9d99725fd1ad3373cf5629684e9506bd547e68"), // recursion lift_rv32im_m3_povw_16.zkr
    digest!("d2fa210b16a494511a153060e072c241c4fd37205e1fd3153bdb760692b35e38"), // recursion lift_rv32im_m3_povw_17.zkr
    digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"), // recursion join_unwrap_povw.zkr
    digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"), // recursion join_povw.zkr
    digest!("ea56b77496e4ad6e4747c2087fc31c67254243179ec01b5f6329b46f73abd839"), // recursion lift_rv32im_m3_povw_12.zkr
    digest!("f9ec9c04124eca27dd17390a7fca483526681d33638c732c9de38e24fceafd67"), // recursion lift_rv32im_m3_povw_14.zkr
    digest!("d1323751ca5f9106d9b39a0403564c3e9c4f5e6081e4042303c1f152cf458b3f"), // recursion lift_rv32im_m3_povw_21.zkr
    digest!("cfd847620616931f1572472554e3d26c6888800f66e08557dfefdf24802d396c"), // recursion lift_rv32im_m3_povw_22.zkr
    digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"), // recursion unwrap_povw.zkr
    digest!("b2b63a6f57122a49195fe52978cefb647a6a066e7d882347cae2fc27f6bd1f69"), // recursion lift_rv32im_m3_povw_13.zkr
    digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"), // recursion resolve_unwrap_povw.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("0cc79f313e84020dca473353a0821a5975ed234b7cc6084a5376c025b2cdb574");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("c07a65145c3cb48b6101962ea607a4dd93c753bb26975cb47feb00d3666e4404");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 36] = [
    (
        "lift_rv32im_m3_20.zkr",
        digest!("92c9cb01af953e1196065530bd1a530ec927b65cd76037316b9f0b0024c51a3a"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("f5cff93555beac4026452f1dc0b27d6635d28f67eb2d514c33f0392ed0450700"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("7f1c610d0a2fef2b11ec9b4230815811eb5722455bc54d497d1ac208223dff5a"),
    ),
    (
        "join.zkr",
        digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("7181cf17e430836b8462a3133a2aad3d063a5e32e2391262b4781e0ba777d53a"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("cf491930b82127394999f612536e5e5f408d73030532b11c82b61638de131368"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("5d848231d47aec5a2a079d0a6eb3a1243c8994172b754618eb442e2b1645494e"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("f3b8a212a369563a592e925cd7eb9620692d4a5fc2455860b5d5dc1750752d49"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("17bc4e72c8ab2b65cb7a834de3e8b525d81d674255d28b11fd18f851b9ef2601"),
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
        digest!("266af82fcfeea64cd8334c13e8d6c769f39377170d629b13c36a600bf9df200f"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("9f2c3d13e250c43e5edcf759cdabc62ecf1d403b250f3d48e9fa0251895bd061"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("4d3d7a6ecc77cc52fb9918708b81da6e098047048d5ccd245aa86d1720e70d5f"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("4f04412d61616d16fbc80022fc1a346554eb50457ce13c524d654c5c99c16e66"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("51072358ab925c6bd1bd524f09fc702234caea4f6b865e152681cc223f8e2042"),
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
        digest!("9ff86f235384c3406f2c6f76b21a8e239edbb20c145b0566c62c0207e24dbf01"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("796c9845f0043a2cf732036816d0281f8258a549dd6e0a612815a8547c73ce45"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("ec2e7f38a83a154dd9762b1dd4dd9d0e5168cb5e8fafeb71a694665e84c9fe5f"),
    ),
    (
        "resolve_povw.zkr",
        digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("5bc0064ed90c7529c8bf5e41c839321e85bb40291e83fd1c877e8c191b62f02f"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("004d2c3e2594bf48115e56669b9d99725fd1ad3373cf5629684e9506bd547e68"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("4f0b471b52bdac03e528554d502d313a2ef11142b0ecb266dfbcd00c70b2cd70"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("d2fa210b16a494511a153060e072c241c4fd37205e1fd3153bdb760692b35e38"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("f74a894ff593584f65847630ead1a23af78c5f5fed2b61090866e01fa5767f12"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("ef4bd775fee9fb36c2f27c68458200285777b06c145e1a6451994f0b2f89bf6d"),
    ),
    (
        "join_povw.zkr",
        digest!("96cdf605f755f175a5661812810f2d491507c05f2ea4a83e4c3cad693d26651e"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("ea56b77496e4ad6e4747c2087fc31c67254243179ec01b5f6329b46f73abd839"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("f9ec9c04124eca27dd17390a7fca483526681d33638c732c9de38e24fceafd67"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("d1323751ca5f9106d9b39a0403564c3e9c4f5e6081e4042303c1f152cf458b3f"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("cfd847620616931f1572472554e3d26c6888800f66e08557dfefdf24802d396c"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("b2b63a6f57122a49195fe52978cefb647a6a066e7d882347cae2fc27f6bd1f69"),
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
        digest!("9b4092897f9e29e8b55ff7d18bf8f85a1a98378d4e00c65c2cfda317f4dfcd6c"),
    ),
    (
        "lift_rv32im_m3_12.zkr",
        digest!("9cd4caa0f077eb183ccc6994a667c53b6388d4c45c6756a5c223994191278132"),
    ),
    (
        "lift_rv32im_m3_19.zkr",
        digest!("5dfed31778f0b0c40daf348ac44a7da5beeaf3323a5589aac4dc25c8fdb26e8b"),
    ),
    (
        "join.zkr",
        digest!("dc44002689aa7852410ad1c840388d66b8b9a2f6d0c4fb6b3ac6ec2ea17d9855"),
    ),
    (
        "lift_rv32im_m3_17.zkr",
        digest!("b06c89bf6b0a8902ca1e2db32c102296206040d1d5cf99432cdb9660a236c254"),
    ),
    (
        "lift_rv32im_m3_21.zkr",
        digest!("1e2f0d54c1942d84bfdb749d5feb3ff085f68d70fd169e9c4050569ab116cfde"),
    ),
    (
        "lift_rv32im_m3_23.zkr",
        digest!("e204aec95ce4adff820d2eb3c344dc88a96a74d509344be16b50ca1c0cc24adf"),
    ),
    (
        "lift_rv32im_m3_16.zkr",
        digest!("0de21ceb8f6389d4c2d28086e5abc7a6c83ad6b490a5a6e803025258e854a0cd"),
    ),
    (
        "lift_rv32im_m3_18.zkr",
        digest!("acd1cf8002d451877d365ebc97da3955069920950a53ad282d0e72c54f17694e"),
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
        digest!("899afdce55e83867e73cfa1ceccef81f81c2d69716e20f6e2c3583aad9350e4d"),
    ),
    (
        "lift_rv32im_m3_14.zkr",
        digest!("8b375303fd5739691e2911cc40cbd0aecef096c1256e6133effbd8d418e231c3"),
    ),
    (
        "lift_rv32im_m3_13.zkr",
        digest!("9bcdabc2d4e0eff752282972a9564bcf48993c22e22c2697fc2d627a4a575ccc"),
    ),
    (
        "lift_rv32im_m3_24.zkr",
        digest!("d1d74da71cedf0ee00d8db53ba89ce760dbed450c3ed6fdb252a5a1e00944032"),
    ),
    (
        "lift_rv32im_m3_15.zkr",
        digest!("6186c7421816f3717e78a76a7d5e471b0f2d1f463e52c34a5b482a1ab3583a23"),
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
        digest!("874453e1478343beea580d9dec5380c6bfeb0f3996fdae56cfd692ddee4238d8"),
    ),
    (
        "lift_rv32im_m3_povw_20.zkr",
        digest!("2e5419c68e988fdb5c68598bf53272f2863c1606964c67deca75efb2328c29e6"),
    ),
    (
        "lift_rv32im_m3_povw_18.zkr",
        digest!("32e2f3d0762b342fd58c990cafc11e48923ea1e0129b926985951b931598b855"),
    ),
    (
        "resolve_povw.zkr",
        digest!("51fe537675d705e759c0cb0862f0cb7c5d70ce3dc483efc3cb1646c2b6f0cba3"),
    ),
    (
        "lift_rv32im_m3_povw_19.zkr",
        digest!("3f04e9125e3da6c711b1728e392db4a89d72391a9e9620d4fbcbd5416c3deded"),
    ),
    (
        "lift_rv32im_m3_povw_16.zkr",
        digest!("b810cce8d97e87e9f49054d05bd45ebbe7eb322dcc4f65fc09750c7d41fd4bfd"),
    ),
    (
        "lift_rv32im_m3_povw_23.zkr",
        digest!("92ea96576cf58bc224ba0d15cdc515432923d84085e63624cede1bd1d2440a37"),
    ),
    (
        "lift_rv32im_m3_povw_17.zkr",
        digest!("7f93628f00b90a39d5ea7fba3fd3444645cf3ba23b64b4362a103034c92f8619"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("8cae4f60f8b44780351ec5740118fcc348d8fa0d029f07d2c77a3f9239165319"),
    ),
    (
        "lift_rv32im_m3_povw_24.zkr",
        digest!("b53efd34f6e38c7718d6d28c33128979c7ba3bd5d19353367b33d3b33f933462"),
    ),
    (
        "join_povw.zkr",
        digest!("9e97b7ba610dc00ec2628d53274c303eb0d78e6e5c33ef118cf60a5135efa97f"),
    ),
    (
        "lift_rv32im_m3_povw_12.zkr",
        digest!("9474a05f4204974cb108ccdfe95571a2fd42d4823438589e3453d25ea967d76e"),
    ),
    (
        "lift_rv32im_m3_povw_14.zkr",
        digest!("dcc44e701ed8a6befa3f6837eaaf094874549c45c83da3db27be2a7f69a3ea0f"),
    ),
    (
        "lift_rv32im_m3_povw_21.zkr",
        digest!("5934be1d8f6c3976e7062a99666bbffaccf7e6f1ec81837b181ab8f016760234"),
    ),
    (
        "lift_rv32im_m3_povw_22.zkr",
        digest!("363b7dde33a210cc0ae2a3b7a5db97134f164fdad785bfc439dddb31b0d1c85b"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("3b5de70ddecc2fabcd3b9b9150ff64e7fc084ecb80f97cac2f9ee11e326087d1"),
    ),
    (
        "lift_rv32im_m3_povw_13.zkr",
        digest!("779f42fc7733f565fc24a0955a9f34637edc94d51690a3938ebdbade85ecd25c"),
    ),
    (
        "resolve_unwrap_povw.zkr",
        digest!("1332cc7a1cb90467d849db4ebc4fcc201f81fe0a2ab06d6a398d76b7dd8aa694"),
    ),
];
