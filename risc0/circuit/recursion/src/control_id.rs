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
    digest!("411fa636f2d364648f035174d3778d6340d9ae1dd648fc35657c173f01e27e5f"), // recursion lift_rv32im_v2_14.zkr
    digest!("1ca3ca03030719064ba61b3125bdd326fc57f74e799ef860bdea6f3227381e16"), // recursion lift_rv32im_v2_15.zkr
    digest!("c32b3627d2b3d60c64adf523a98bd16c0ff607471f3d6630d1f26d5e9406d841"), // recursion lift_rv32im_v2_16.zkr
    digest!("c9b08054994f542a6310b00d9b6fc6528ed7bb6f4ca5476a686847127cdfdc5b"), // recursion lift_rv32im_v2_17.zkr
    digest!("e7934a23ddce1423b425cf32aa23be29f48cd40e0b6ff9376dce6f3bf9d0bc35"), // recursion lift_rv32im_v2_18.zkr
    digest!("8c2fdd36ede09a4b9d316a43c51f1160cbd8876659c5f35810c3a119c60d3843"), // recursion lift_rv32im_v2_19.zkr
    digest!("34530b42028fb631c90e1226bb0e750d4b9b593840d45216f75dca449dac7734"), // recursion lift_rv32im_v2_20.zkr
    digest!("fd84d83092a1e1244d423a26d89c892ab098b467c6d82229912deb26e37d2562"), // recursion lift_rv32im_v2_21.zkr
    digest!("9d9dbf33535ab11f52a93839dfd23b352b7626009e81d9459fd04e488898ec6a"), // recursion lift_rv32im_v2_22.zkr
    digest!("c6972402cc81bc6c1122e65aa7cf463f3ac3f477c7dd860582ca7420fc7b8b02"), // recursion lift_rv32im_v2_povw_14.zkr
    digest!("2f6ea1104bdd5955faa135611e8f803e7b4461703b937e704da70955ec115467"), // recursion lift_rv32im_v2_povw_15.zkr
    digest!("a7b55654228123448cd67c400d9bf80b4e54eb3997ee92103e900903b6578862"), // recursion lift_rv32im_v2_povw_16.zkr
    digest!("2adab2445391035b21f255606a1ba060a7d5a64db5cdf13d9fda7f22a2853270"), // recursion lift_rv32im_v2_povw_17.zkr
    digest!("58b27422240db834c08b8e6c12000c093efce8613263f05825c380009c41da48"), // recursion lift_rv32im_v2_povw_18.zkr
    digest!("26c84437d3e26875b259880d0f29da47ed5ca869133637701d33fb15a83dce4b"), // recursion lift_rv32im_v2_povw_19.zkr
    digest!("177fde1441dc735dbd6a58245d82b2036623ac41547dc345f1fd7c486ac51462"), // recursion lift_rv32im_v2_povw_20.zkr
    digest!("eac3fb487080a62e6ff85d331dd72a4706e50e55c9cb842dea48d71e3e119a04"), // recursion lift_rv32im_v2_povw_21.zkr
    digest!("0344cd54d62d2a1b6538b674d5aa141250ff4c5be08c6e3d16cb5e1de632252d"), // recursion lift_rv32im_v2_povw_22.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"), // recursion resolve_povw.zkr
    digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"), // recursion resolve_unwrap_povw.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
    digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"), // recursion unwrap_povw.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("a54dc85ac99f851c92d7c96d7318af41dbe7c0194edfcc37eb4d422a998c1f56");

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
        digest!("411fa636f2d364648f035174d3778d6340d9ae1dd648fc35657c173f01e27e5f"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("1ca3ca03030719064ba61b3125bdd326fc57f74e799ef860bdea6f3227381e16"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("c32b3627d2b3d60c64adf523a98bd16c0ff607471f3d6630d1f26d5e9406d841"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("c9b08054994f542a6310b00d9b6fc6528ed7bb6f4ca5476a686847127cdfdc5b"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("e7934a23ddce1423b425cf32aa23be29f48cd40e0b6ff9376dce6f3bf9d0bc35"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("8c2fdd36ede09a4b9d316a43c51f1160cbd8876659c5f35810c3a119c60d3843"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("34530b42028fb631c90e1226bb0e750d4b9b593840d45216f75dca449dac7734"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("fd84d83092a1e1244d423a26d89c892ab098b467c6d82229912deb26e37d2562"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("9d9dbf33535ab11f52a93839dfd23b352b7626009e81d9459fd04e488898ec6a"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("817a4b13453eac5a4e67ea1bdcc0677681faa94e386bdd4b510429363685f067"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("6c4f9e2ae5d3d5375956f608a54112418333ad2008052b059f3b500ba8df9d63"),
    ),
    (
        "lift_rv32im_v2_povw_14.zkr",
        digest!("c6972402cc81bc6c1122e65aa7cf463f3ac3f477c7dd860582ca7420fc7b8b02"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("2f6ea1104bdd5955faa135611e8f803e7b4461703b937e704da70955ec115467"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("a7b55654228123448cd67c400d9bf80b4e54eb3997ee92103e900903b6578862"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("2adab2445391035b21f255606a1ba060a7d5a64db5cdf13d9fda7f22a2853270"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("58b27422240db834c08b8e6c12000c093efce8613263f05825c380009c41da48"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("26c84437d3e26875b259880d0f29da47ed5ca869133637701d33fb15a83dce4b"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("177fde1441dc735dbd6a58245d82b2036623ac41547dc345f1fd7c486ac51462"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("eac3fb487080a62e6ff85d331dd72a4706e50e55c9cb842dea48d71e3e119a04"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("0344cd54d62d2a1b6538b674d5aa141250ff4c5be08c6e3d16cb5e1de632252d"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("bd19f156d23811155241e10f7d03ab483949e5039a512d75b7e3da40fcb5490e"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("7898f8140d13c04781c2073b2b28541dfa40f23fa824c30228b80b2601d7114a"),
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
        digest!("52d814fea0ff156f2b8b34f7c47d7bfb5c09c527d7907a8664bd95f104633852"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("ca0c7e2ffb7cc226f544dfbebd420a898ba1ec42cb6da27c1446f7dafc41c534"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("b20d5da6ac0f4bface80e6f902cd0f77e3f5e3a8174379595ac74d6f052acae5"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("7e81c18847d0693f69eaffe6a43e3883f81f57ecea2b740a682870d9d810faaf"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("b8f1d3b165d1a9eab7c6c37d3e9583b9907af5ef847c90ca2e4d18c689897a95"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("9385cfb4c04bb8a7afca8b2d1bf083cb5d7d975d8a47b92f02710a81cd49d2cb"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("771619915ed607e737578315c855ba70c322ac02cfdd01da0e4d1bed4c51cb0d"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("c662b29a03a3475a3dae43ef30b0e4234a9e00d99b49d1f61d8ae91c7957a148"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("5d68f47ef1f5ab04588c370a79d1216eeec96c5d75fcf73af3a2a59b76bd2879"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("bb5ced4a8480a2347cfa43125a9c5b165e2ff3bc99b42927d43f49d23d8b3208"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("3e6ac6e4ca5d76858edae7a4f080a2a34649ea6ce0870d0d77ec18b7299b1dbd"),
    ),
    (
        "lift_rv32im_v2_povw_14.zkr",
        digest!("e5e64a61ebe66ad5361417b2c5b879f555567b8b27f24263b285fd2a44e9d879"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("058a1436c07037e4b02856b51a09a4b8b81f0653dacde6efbead574d2ccc877c"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("39ac8603e8fdd8b1571546cf21afc4fecbd763abdc83c6f556f865f1639cf793"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("2f83f136dff007043e04c793946ec7b1d6fc85aa80fd56b3cddfd41e5b5e80cd"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("8fc29c56e18387c39b45a6ad5efe70c4b05f4755dafe79ceb503f00d99711171"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("a6e06036f3b4c84aac96b2c43b18fba7328a0f1c6d0a1a92f6601ceb7f136a23"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("97a1d6b0d9c7cbc754a24b76a068c43a3dd0a194708e88b5ba061617c3bff7b4"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("268d25ef3fa8fc664c1a9629870be677b66e537d8b56fceddf4e55cea3ec8167"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("e836234e551bf0404665c68a6489527e0f38d77e058a702911298912d4fdfee0"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("5544f519c4d65a1546475b23860e26ff7299059e24cacb3b10854cc2872e7736"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("ae43f6e6b2565ef910c9736eb616a1d045ff049571c37ac728ad70d8cca2d66d"),
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
