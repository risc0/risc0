// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
    digest!("7d40e30f18c33757a1a06613d779bf32415a9a577abfe66b4be5a71352ce5011"), // recursion lift_rv32im_v2_14.zkr
    digest!("86dfe305f9858148efda7f10c7614762b3ba603519d92f2b91c55c220b63e952"), // recursion lift_rv32im_v2_15.zkr
    digest!("2f61ee3922aa323fb59c7a0268bda909df6c08070f4cf466e5a3440e299a7d69"), // recursion lift_rv32im_v2_16.zkr
    digest!("35e2b36e7e7b953c18016969cf0aab642f21df617616e450e4de9a778b252025"), // recursion lift_rv32im_v2_17.zkr
    digest!("6d26ea13c4575577e44eeb371656e60f2c4d6f187ccd15555b29f1062f6af71e"), // recursion lift_rv32im_v2_18.zkr
    digest!("b712f9541933da35f90d0a5cf3bd95040528056ff9efa203390a224ae63c5232"), // recursion lift_rv32im_v2_19.zkr
    digest!("5b35585d98a08c611375e365c0fee5401cb8aa1a3a8dbd744b177e0f6dee4837"), // recursion lift_rv32im_v2_20.zkr
    digest!("0d74121afe5e3511242dee572bec7c50b49fd6031c20052d714d0903688d3f56"), // recursion lift_rv32im_v2_21.zkr
    digest!("a7d8d52e8ad8ce18c44c3b5e86b80a1f1617ce76dc6a396731e292407322ad01"), // recursion lift_rv32im_v2_22.zkr
    digest!("cafb932f00329270a7e0fd65fd50b3659202b9281498382b5903996582df0a72"), // recursion lift_rv32im_v2_povw_14.zkr
    digest!("5302d93dd3b8a10cb4ef026df2150e58603c68118b03f90eb1e14e32dcc6de53"), // recursion lift_rv32im_v2_povw_15.zkr
    digest!("f08ce649e0bfdb39ca4899497617812287c8df0e3cbc4e21dc9f8940cec98427"), // recursion lift_rv32im_v2_povw_16.zkr
    digest!("1723360ea2856c54551548213c7ebc430f698c228d066f4cec2bee714a32a375"), // recursion lift_rv32im_v2_povw_17.zkr
    digest!("753aab0b6ec0ef09f2e8640f8c0d821f70da6c4cbea7b054bf7bad0add8d474d"), // recursion lift_rv32im_v2_povw_18.zkr
    digest!("a1617b2cb33bb775a827725c850c323415e6425ba519dd21dc699f6fb62ab749"), // recursion lift_rv32im_v2_povw_19.zkr
    digest!("bd086c5adbaf482acd4ed94ab3e691657325a005d26ff73b0ae7f70df52eb036"), // recursion lift_rv32im_v2_povw_20.zkr
    digest!("aa81304c6d117c1dbb669670623e6f1959e683068d67c66d44fcf228a081b331"), // recursion lift_rv32im_v2_povw_21.zkr
    digest!("c3565e5b9879bd74374356267dd92942001cff3f2567c1226e48225e2fb9db19"), // recursion lift_rv32im_v2_povw_22.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"), // recursion resolve_povw.zkr
    digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"), // recursion resolve_unwrap_povw.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
    digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"), // recursion unwrap_povw.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("4c729b33037f061e4e22505266cfdb6b6780a932cb41be4a505d9950c210b507");

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
        digest!("7d40e30f18c33757a1a06613d779bf32415a9a577abfe66b4be5a71352ce5011"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("86dfe305f9858148efda7f10c7614762b3ba603519d92f2b91c55c220b63e952"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("2f61ee3922aa323fb59c7a0268bda909df6c08070f4cf466e5a3440e299a7d69"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("35e2b36e7e7b953c18016969cf0aab642f21df617616e450e4de9a778b252025"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("6d26ea13c4575577e44eeb371656e60f2c4d6f187ccd15555b29f1062f6af71e"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("b712f9541933da35f90d0a5cf3bd95040528056ff9efa203390a224ae63c5232"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("5b35585d98a08c611375e365c0fee5401cb8aa1a3a8dbd744b177e0f6dee4837"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("0d74121afe5e3511242dee572bec7c50b49fd6031c20052d714d0903688d3f56"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("a7d8d52e8ad8ce18c44c3b5e86b80a1f1617ce76dc6a396731e292407322ad01"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("31c89f6ba1e3d8676f9a3a457794aa4654028474a3d92a0585b0607557ac0273"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("bc9ec8079125bd1c20a0c03b2ab80e2593285f693e855312cd3b0c304ce0984c"),
    ),
    (
        "lift_rv32im_v2_povw_14.zkr",
        digest!("cafb932f00329270a7e0fd65fd50b3659202b9281498382b5903996582df0a72"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("5302d93dd3b8a10cb4ef026df2150e58603c68118b03f90eb1e14e32dcc6de53"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("f08ce649e0bfdb39ca4899497617812287c8df0e3cbc4e21dc9f8940cec98427"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("1723360ea2856c54551548213c7ebc430f698c228d066f4cec2bee714a32a375"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("753aab0b6ec0ef09f2e8640f8c0d821f70da6c4cbea7b054bf7bad0add8d474d"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("a1617b2cb33bb775a827725c850c323415e6425ba519dd21dc699f6fb62ab749"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("bd086c5adbaf482acd4ed94ab3e691657325a005d26ff73b0ae7f70df52eb036"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("aa81304c6d117c1dbb669670623e6f1959e683068d67c66d44fcf228a081b331"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("c3565e5b9879bd74374356267dd92942001cff3f2567c1226e48225e2fb9db19"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("80b82f245716ec711d0c0204fe6a582ea2cd971ec721d22aec0d385ee3792b05"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("0d0bde17a3242b3129deac23a3362816f768a411d88b5a22f9adcf226bb2b934"),
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
        digest!("05e278dcb9a90117f27096335bbca93f0a1c39a146ef7f0ff3e24788371c9761"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("7e38d2117f64c78e27159a356dda2a0b2de70d530a866f6e4c923342149d7956"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("0737dbaf9346383bb66795aa9bc5a42472712660c28612af149ddd58271695d9"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("80a3e859059f483e2bc4e3eeac4eb9848e7ea5e0c8620398e7d57ae755477024"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("e48862f9cafea1e66e47e1abb613bfa8a72d4825efd9b5d2424d476ecfe236b8"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("60f23f4f8d16cf61c552a55aeb630929b5d4e35653839a0d4c63218859a0c06e"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("e00a7eb1edc3124384405a596d1584c55e07c24fd285643bcc6e79be9caa7a86"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("dac9f70bf0f3f5a8d05e89d9f9628a4182c40e63f423a36642e9116ee77d158b"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("a782f2c9e15371f2ec7b4eb084aea5a41eae636e4c468df7aab45206113852a6"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("e8a5ebe9dba0b85cfdebba2bdefd8389be319a9b56c7e15c28a2420fdbece02f"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("498e5c6db1d5528643b8cdb3a61ef795f8c98a15ae86c5af2ccc43c88ba50ccb"),
    ),
    (
        "lift_rv32im_v2_povw_14.zkr",
        digest!("19ec9d4704c53dd1d43b380b86a86c2d8cf442daae8b1c1095115e49fdda178d"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("e008a1ad88a785160e8da3f4470ba9bcd256be7f3a1492593aebc68bf31a7f76"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("9107dca5c68e62ecdd062fbb719f8a4bdcff8fa329a4e6b455dfb354fefd1e92"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("34af63bf2a82fbdbe66dfbdcfc548f9317781a70be71b1d85a7822def90dabf2"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("fd654104f9271c7542a58f53bedf8019f6055a59751e300e840dd955738bd306"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("e1a6971d87ce4851b5dbde91e2dc04045b3e2a070f97fd7bb6b534808295b9fe"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("989494d0dd1722328ebabfb5863e7bf56e305a29ba93f991e211842825cb0d2d"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("e86481989c66e5a186db3ce6db9760c6c04e848f02894a23813310ebff7880c6"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("555f26058d1ea6ad8d461cde66e40ed5022d8b9e06496f34b06ab8920924148e"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("d4352fd30d4afea80a4ca229dfa5683228f725b41241f3afd5a9205e53b207ff"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("e796bc07137377a3f687be2b095268f26b5a12ea23af3c1b855ea8178de3921b"),
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
