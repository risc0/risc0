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
    digest!("605f430b5ef7c6499eb7c913599dc1471be7d5105e42a81a35b3f33d7326d44a"), // recursion lift_rv32im_v2_povw_14.zkr
    digest!("0b22b2478894ab755ee0fa2f3a7b926fca482b2019abdd6fc94def0cfa01e34c"), // recursion lift_rv32im_v2_povw_15.zkr
    digest!("fbaedd46a7d9b06503d0dd16fc73af221eee1538a461f80e954b7d1cc03ebc6c"), // recursion lift_rv32im_v2_povw_16.zkr
    digest!("a8780143e16d363c927b1710596840327cc8dd0c26521f75be84825f0cdb9369"), // recursion lift_rv32im_v2_povw_17.zkr
    digest!("3ab64b262ad59019d1620b08c0e8cb58d0435a27ab8f803571d7806007158716"), // recursion lift_rv32im_v2_povw_18.zkr
    digest!("5258584371015b590c97e11de12ed019331fec624da8f4019ade1c52d391f603"), // recursion lift_rv32im_v2_povw_19.zkr
    digest!("60c4cc6ed63841100e4eb95dc000760d7bb1fb5a084c56125bab590c82374256"), // recursion lift_rv32im_v2_povw_20.zkr
    digest!("45076077f962077523366e49ab2ca50bc152c5617dd0da471bbeb96e6bb29250"), // recursion lift_rv32im_v2_povw_21.zkr
    digest!("4d0df174c23ce433a6909e3940755659bbabfc4e6969894f22b77f1f210b1a1d"), // recursion lift_rv32im_v2_povw_22.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"), // recursion resolve_povw.zkr
    digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"), // recursion resolve_unwrap_povw.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
    digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"), // recursion unwrap_povw.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("0844ab02fd28f72a6173c7671c58b537496dcd64b68b3565d070be0b0a1ab72e");

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
        digest!("605f430b5ef7c6499eb7c913599dc1471be7d5105e42a81a35b3f33d7326d44a"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("0b22b2478894ab755ee0fa2f3a7b926fca482b2019abdd6fc94def0cfa01e34c"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("fbaedd46a7d9b06503d0dd16fc73af221eee1538a461f80e954b7d1cc03ebc6c"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("a8780143e16d363c927b1710596840327cc8dd0c26521f75be84825f0cdb9369"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("3ab64b262ad59019d1620b08c0e8cb58d0435a27ab8f803571d7806007158716"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("5258584371015b590c97e11de12ed019331fec624da8f4019ade1c52d391f603"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("60c4cc6ed63841100e4eb95dc000760d7bb1fb5a084c56125bab590c82374256"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("45076077f962077523366e49ab2ca50bc152c5617dd0da471bbeb96e6bb29250"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("4d0df174c23ce433a6909e3940755659bbabfc4e6969894f22b77f1f210b1a1d"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("d9b89a74ca6aea6c3eaa7271357f0e4fa9c54a3a2ed69e11e840c91c35377b13"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("2c94d630a9f7114662e8712e72af9743e0c5b739087a1a6bd22b681bda6bfd39"),
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
        digest!("018f2998b26021c40e3720a1c0e02b78ad7079317e653488905ebd1774522ea3"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("889568295696dae49d29d67adb22c913456f1e721aa27b3883e0d2f0d2a086bc"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("7cb135a8b335cf3213feaa9c55547068941af8f2a88c6aeecbdaa308593b5346"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("a9b471af28fa56668c45bb8bc699256cd8ec404d8218c322090eb3a14603de06"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("a13f22eeb6600c2a953468c7a4c0f1147a82caa0630ee0d81a16dcb3e8836393"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("5ef94f08129b047e2c74413326cd21486849ed4d8cf2113765e2e357f41d3458"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("bb63b107d5b43e3727eefedafba93ee68e6bce83ecf0e45816215693c5ce8601"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("f3a052e9687abe27c12e5605d525e94e68f8e1dc59b10eed93beeb5d4d926e37"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("89cfd81959cbe6600f4f12bacf491e1d772989c524f7e7ff8238208778c84018"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("a274fce4f14e9b455682bd049987bba13d56324280410358c63844ffa9500115"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("eff473b765043a6f40c8f01b372536c82caac738deb866fba825cba71864764a"),
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
