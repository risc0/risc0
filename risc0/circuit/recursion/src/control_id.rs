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
    digest!("6b1c2000022866333869852738d70b091453f70c7c1a2748a408841bfbf9ff2c"), // recursion lift_rv32im_v2_14.zkr
    digest!("61656c077d35bb394403a743bd51e901131d955b386736015340b41b1e383a57"), // recursion lift_rv32im_v2_15.zkr
    digest!("3010cc0736a3aa038e8dc5065a09b60d4ea6d7621f715e74da042a19428aac29"), // recursion lift_rv32im_v2_16.zkr
    digest!("736fd2527b2f0c464480e4618810fc7333ee9964dad4262103a4095e45a92033"), // recursion lift_rv32im_v2_17.zkr
    digest!("83422f2178f2291c68f25c16a340601a5cea4564eb8ece6a43f15e57777d5504"), // recursion lift_rv32im_v2_18.zkr
    digest!("b57d02474b9cb94ee409d65947bcad582df1d329a4998c23d9ed792b1b18600e"), // recursion lift_rv32im_v2_19.zkr
    digest!("21100c6b71caca2a2a6e61672bc4933940ff1f512cfe134d28289f6a2851f16c"), // recursion lift_rv32im_v2_20.zkr
    digest!("5856376bcb60753d53d6365ca7e17662f2edbc23204d9f25d0317f185d22cf3f"), // recursion lift_rv32im_v2_21.zkr
    digest!("2752365410cfa105e7637e18b33b596268c52210c4bde81de4e6cd00bd728b1b"), // recursion lift_rv32im_v2_22.zkr
    digest!("05fad839a9c6dc104a6bba66573cdf71e20e866d5b80b773f924a61df56b2450"), // recursion lift_rv32im_v2_povw_14.zkr
    digest!("32770322b503cd4ca75a52344658b324dbe969593eda6058cdc77c4d7620d942"), // recursion lift_rv32im_v2_povw_15.zkr
    digest!("d4692d517e98413f3856a00c90f5115f5c1a0c3e28ae59649355ca1503517421"), // recursion lift_rv32im_v2_povw_16.zkr
    digest!("d34fea63ab6c5830aae7195bbbb5b6608de70c3dc2df05447acc5d08dcd2d830"), // recursion lift_rv32im_v2_povw_17.zkr
    digest!("0ef0d729dfdff4191a4a3e1cf631485ef1ef003efa48a165cb7ee6105d7f991a"), // recursion lift_rv32im_v2_povw_18.zkr
    digest!("f3a3c308b356c406e3a79b236a842725ec1b1e5619a85459cb9f7913792cca27"), // recursion lift_rv32im_v2_povw_19.zkr
    digest!("56426436d8b9054d74f4d149e0c4c9519b2fa16a8cd8d56910690038e27c5f57"), // recursion lift_rv32im_v2_povw_20.zkr
    digest!("02f4994f228be220215eeb411f5cd667d67fa646d49c0262d1d08f5bf8925173"), // recursion lift_rv32im_v2_povw_21.zkr
    digest!("798fb406225d7b687d27f9314c6cc6603868fb0eeeefb53fb82bfb2a1b67142b"), // recursion lift_rv32im_v2_povw_22.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("20ac6e29b1806a143b508414140e2e15e461f93e04e3830af39cca362b8f005d"), // recursion resolve_povw.zkr
    digest!("ba1d7275d5840e4f998e2c5120810c0eb197e90219696e2a64dec7662aa3cb06"), // recursion resolve_unwrap_povw.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
    digest!("1688f04cca489638862dba455c1d5c561513f975c885a3491f0fe12df761c847"), // recursion unwrap_povw.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("8de29b199629fe27736a081d23dc694b587a3d22ca39cc4078c98e14757bfa1a");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("d77f22a183ba57fd484ddde237f4b6f6dd5110f64d0188cff557b6e7f3c0561d");

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
        digest!("6b1c2000022866333869852738d70b091453f70c7c1a2748a408841bfbf9ff2c"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("61656c077d35bb394403a743bd51e901131d955b386736015340b41b1e383a57"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("3010cc0736a3aa038e8dc5065a09b60d4ea6d7621f715e74da042a19428aac29"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("736fd2527b2f0c464480e4618810fc7333ee9964dad4262103a4095e45a92033"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("83422f2178f2291c68f25c16a340601a5cea4564eb8ece6a43f15e57777d5504"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("b57d02474b9cb94ee409d65947bcad582df1d329a4998c23d9ed792b1b18600e"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("21100c6b71caca2a2a6e61672bc4933940ff1f512cfe134d28289f6a2851f16c"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("5856376bcb60753d53d6365ca7e17662f2edbc23204d9f25d0317f185d22cf3f"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("2752365410cfa105e7637e18b33b596268c52210c4bde81de4e6cd00bd728b1b"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("accc063514fadb2f0ebae32c77c05e71b9ba7d437892f70d7434171e28081432"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("37072e21fb2b2a316acb5e3e8970482f0a40a8653cfc2943f7f27734cca36968"),
    ),
    (
        "lift_rv32im_v2_povw_14.zkr",
        digest!("05fad839a9c6dc104a6bba66573cdf71e20e866d5b80b773f924a61df56b2450"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("32770322b503cd4ca75a52344658b324dbe969593eda6058cdc77c4d7620d942"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("d4692d517e98413f3856a00c90f5115f5c1a0c3e28ae59649355ca1503517421"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("d34fea63ab6c5830aae7195bbbb5b6608de70c3dc2df05447acc5d08dcd2d830"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("0ef0d729dfdff4191a4a3e1cf631485ef1ef003efa48a165cb7ee6105d7f991a"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("f3a3c308b356c406e3a79b236a842725ec1b1e5619a85459cb9f7913792cca27"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("56426436d8b9054d74f4d149e0c4c9519b2fa16a8cd8d56910690038e27c5f57"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("02f4994f228be220215eeb411f5cd667d67fa646d49c0262d1d08f5bf8925173"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("798fb406225d7b687d27f9314c6cc6603868fb0eeeefb53fb82bfb2a1b67142b"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("be3a0c3ed9e08469d3210a2bd3a858552a6f2b15c6e07766c7d0f309ea1b873d"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("6271684f67463923ad148d6a7bc1845d100a812454b4b76620d6633a866bb362"),
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
        digest!("21b69722a96f9d0d4cfe4e8487a1a6d4738d2f4c3d04793aec8727eacf340437"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("98f01834084ea747ab627a267fe4b28af900355192f5c00849920d112d45beca"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("e8be248b654c7daee6d53936adb4dd4298aee688befc31511dff9cd5a8fc55c0"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("0368a51bd97c987d03c9d54fbfcf07f20896dbe23fac915086ec4bbb115a05c0"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("ab139eaed510cce4011d119fd22756007ffb65f2fd285c53338522b040183bed"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("3d045552350ebb184841a1485d7d39de7fc945064074c8dc2f367c7a98d2c1bc"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("c1501c8c7d65becc0e9ea1f2ea753cfc24d5bbf0e89d5ac2fc9ab3bd580798f7"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("54bcc7da3e8f4ec4d97873599c3024c32e77d8c671c2a717931938d9aefbf2e5"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("2a79f433d6c94add9f7c0b10b4350bd476d7e3280b75b5eabc46f10e59d14536"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("63789b3164af4e319db8205b93829d8e5c755e11c97992a4b9b1e9d728b5027e"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("9d134913ed5701ec8ba7197fcdc0d9a9c427d4d7c2e4dc9db5080f01411ec113"),
    ),
    (
        "lift_rv32im_v2_povw_14.zkr",
        digest!("1564f519018eeb9cf229763aa34b7675f3e4be6031a8f4bf5272b1d1b3db0a81"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("87e471fcd81c14c51d471a2ecd22d653896630185a079e46c314f22ad016182b"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("369deafa3cc9efda82523cb92ae37aef6f6c361f423adafb4b54c8e85031b7cd"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("b67dc8a1d7a77b9b39788740572635859e182b53fa01c0de2d67b454869692ae"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("10b9da654d816d674a53ec3a20470fb80580685c3d863c1daeef932da6f299fc"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("13afd5738984ff10b8f54f32837e9d9903b85632efaf4afe9052787e016f9f3b"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("725212b169e044c0c0bf2dae29d56b3caa372b6ce128373aecf01a90a0003bb5"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("65b4f64b1eba438b4ec5baafdc041dc32d16810e995219077684e1fea1e4a9bc"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("2825d8948c3dbf9d2925b12ba3ea83578b3a68fb973eab1d6846f9273e6610e0"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("c9d18ad7d470a67dcec4eb5d2e76e7596faae34a29e683aee8f28c50e1722392"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("5fdbb53cf1367f8c233e3928ded0dd4817b3ce1d855bde6f62ebc4ab338e3b1f"),
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
