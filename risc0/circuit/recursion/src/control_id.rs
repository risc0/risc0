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
    digest!("d4c4a53b4a3ebe4a027e36680045f4639407650e55263d328da0ce5dfa251d00"), // recursion identity.zkr
    digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"), // recursion join.zkr
    digest!("27095903856bda18aacb1a2744f25d5035b6b91b11762b004479f66b3808461a"), // recursion lift_join10_rv32im_v2_14.zkr
    digest!("dedd046fc677c55cfc8fd03557b5b73802df8b24138fc5402ff5cc063ecbfd58"), // recursion lift_join10_rv32im_v2_15.zkr
    digest!("5777113d18a62d0e4b24db23d23831021391023446168b43be3e600d116cb248"), // recursion lift_join10_rv32im_v2_16.zkr
    digest!("43e01b6a51be8547341b0b5e4da05c41fd6749767ce5d04b5488195659235623"), // recursion lift_join10_rv32im_v2_17.zkr
    digest!("4ecc5e2c4992e70448f37732698aa35660e1203881039c5416491b2f762bb133"), // recursion lift_join10_rv32im_v2_18.zkr
    digest!("0d8875644e8e75730c2beb5ca375b952ad88f46325a26a6aa8f3f025176a5a59"), // recursion lift_join10_rv32im_v2_19.zkr
    digest!("0c0f1835f512ca66eeef7d0ded36702cc21ff35edc771b73edde772e5edf4728"), // recursion lift_join10_rv32im_v2_20.zkr
    digest!("625cc74256a1872abcf2676cbbe3412a73ed0d5f433a7a6ab6c04132ed0ba709"), // recursion lift_join10_rv32im_v2_21.zkr
    digest!("c83b970317be1724c7af81161e60ea42f8f93e6c5427212a8fd4b46d06582175"), // recursion lift_join10_rv32im_v2_22.zkr
    digest!("fb946142053c7b6d7443d44a32c6391aebdc130d1fa7672b4eb14b4fe0d94d60"), // recursion lift_join2_rv32im_v2_14.zkr
    digest!("28c1cc0f68837b0539345d6fb2d0f661c841393a20079c095351184fe1c95271"), // recursion lift_join2_rv32im_v2_15.zkr
    digest!("a1ce4f190b0ebb2efbe9f9622664c726e8a01015d47b54740f715c67aece2812"), // recursion lift_join2_rv32im_v2_16.zkr
    digest!("5f6118014b16d56829e5e205d25f48001e6ab7605ec3f7495ae8d10f9b2c2851"), // recursion lift_join2_rv32im_v2_17.zkr
    digest!("7587084260cd1810f982aa3c342ad04528799e74c4ac6533be5c0931b9e0ab32"), // recursion lift_join2_rv32im_v2_18.zkr
    digest!("9873df09fc9c54713101261777a6796bd738f169f97afa73674e9f427509f469"), // recursion lift_join2_rv32im_v2_19.zkr
    digest!("c64f9017da24b01042c8c83d123a1c115fd7d0389dbba642649c554adf201619"), // recursion lift_join2_rv32im_v2_20.zkr
    digest!("e9575968b8c278113ee9e82878e9af6991675f17ba727768b7b3d02b03403b0d"), // recursion lift_join2_rv32im_v2_21.zkr
    digest!("7772cd05351ddc157e407a5f8841ef05b4aa1c64a3b24d49987b3b17e9ffdc14"), // recursion lift_join2_rv32im_v2_22.zkr
    digest!("e315de420e2b3463eacf6a7711e786660ee7476b713f770330238239dd8fa71e"), // recursion lift_join3_rv32im_v2_14.zkr
    digest!("842afa147cec9966fc564e0b18e84632569d6a52d8d7a60ad72ba12778293a5f"), // recursion lift_join3_rv32im_v2_15.zkr
    digest!("e129565b1875b854ed360d3b639e3e44b246583b94ca4726dba87929e63aea76"), // recursion lift_join3_rv32im_v2_16.zkr
    digest!("afc2623ba60cb0749d4505107b5f703451bb5738870831368c26b427b2352f00"), // recursion lift_join3_rv32im_v2_17.zkr
    digest!("5abeb439dbe71737ebfbcd2c7c3ec0188338a240d78bf05d5bc3495185a6a508"), // recursion lift_join3_rv32im_v2_18.zkr
    digest!("c17f161086fc3032c320fb420b90156bc210dc211f7c9648ac81b06af9b12b68"), // recursion lift_join3_rv32im_v2_19.zkr
    digest!("80a7ef27dfd15b3b615eca73d7c4bf19d821c762ec9b0e3af918683e5b53b05a"), // recursion lift_join3_rv32im_v2_20.zkr
    digest!("ae24e96fa68d501e72b06e4d57ddf7118a03f60762f3fd467ebae31faf9abc5d"), // recursion lift_join3_rv32im_v2_21.zkr
    digest!("ecb4c543e99a8b3ad1392b10c4ecb75bbdf1546d45bf78682f03ab3a99dc8a3d"), // recursion lift_join3_rv32im_v2_22.zkr
    digest!("72d1bf09902ef5555a56817109812e62d869e61e1bfba621d49f826906d86e41"), // recursion lift_join4_rv32im_v2_14.zkr
    digest!("ba27320048b0bd4142b1df1d7ada7a526fc5ba3defaa6663696f4576ab78db45"), // recursion lift_join4_rv32im_v2_15.zkr
    digest!("117ab65329ca693dbafedf10633a0d14ad572743106bfc6f89233d283a53d35c"), // recursion lift_join4_rv32im_v2_16.zkr
    digest!("7dd6e313ee04c867ebfe125665ecad551db16f6ba1f127436bb3ab16d562066a"), // recursion lift_join4_rv32im_v2_17.zkr
    digest!("2115894a61a70613a44e7a6364af535ac3217943020742598a70184d6678b457"), // recursion lift_join4_rv32im_v2_18.zkr
    digest!("c136f242ecf8e762bde0e262b54e1904cf935e3fa6bb8736e675920e0d365560"), // recursion lift_join4_rv32im_v2_19.zkr
    digest!("c226ab3505c0b4319de59e3a704520296c121e0f323bf9450c8637779d2df440"), // recursion lift_join4_rv32im_v2_20.zkr
    digest!("c65ba5519e265f16ce0fb81f5841f1288c41621a8d5244413e28c2306b441c2f"), // recursion lift_join4_rv32im_v2_21.zkr
    digest!("74c124761ba8ee668e70de730e1db964baebfa4897245d54bc3c3d778420fb12"), // recursion lift_join4_rv32im_v2_22.zkr
    digest!("3f78bf159aab0f32320d05416ca2c359ec4e626dff0fdb523c009450b4e0b30a"), // recursion lift_join5_rv32im_v2_14.zkr
    digest!("7e627427b771701f6345b7436187fd2e909397659406fc0ae689e33667460776"), // recursion lift_join5_rv32im_v2_15.zkr
    digest!("80b94842c82bc7315983ce190807385b2b2a2814994f2c1f906ec805116baa0e"), // recursion lift_join5_rv32im_v2_16.zkr
    digest!("1582ba76f42e2e05ec57f06c4624a94d474d631310fc1e3be7d99b3ab9652a54"), // recursion lift_join5_rv32im_v2_17.zkr
    digest!("ef8bee28e8e3494fa970a33aaaddf719b6978404270c0b12365e385388d2281a"), // recursion lift_join5_rv32im_v2_18.zkr
    digest!("9b5f986ceec3af1040e96d240e5ddc25adcc595779040f403f40ea1077c46d45"), // recursion lift_join5_rv32im_v2_19.zkr
    digest!("5b95240c7e6f8e744f32ea634ba78308d98c910d1c557521585ef4744a855575"), // recursion lift_join5_rv32im_v2_20.zkr
    digest!("ed4b535f65a1b71519081d38d8282450e085dc298c51e549010adb06a0d46c27"), // recursion lift_join5_rv32im_v2_21.zkr
    digest!("60f564004a7f687230b68f039fc4c71a3666075376e72434496ad5447c034c72"), // recursion lift_join5_rv32im_v2_22.zkr
    digest!("b2693034f830c22bc3dfb2506adb6d56203507477fa08245419989760be5a52f"), // recursion lift_join6_rv32im_v2_14.zkr
    digest!("ab20521d63a86d2eebc9cf316256185f92e99737d316044b48889f1ad41a5866"), // recursion lift_join6_rv32im_v2_15.zkr
    digest!("8af7c560b454740945c46a476385342e2e3695106a56ee6694a9750981164103"), // recursion lift_join6_rv32im_v2_16.zkr
    digest!("05d71520a258c46c5d27300bfdd8560768f745710fcd487404dcc63c964dea41"), // recursion lift_join6_rv32im_v2_17.zkr
    digest!("58136b6b29785f1647d5d76b5921a54756d3cd11e481781c077e776cda2b250d"), // recursion lift_join6_rv32im_v2_18.zkr
    digest!("840f936da3d6eb6dc8a63c37ef95152513083f2524d35860ee48cd454cdc4a25"), // recursion lift_join6_rv32im_v2_19.zkr
    digest!("bfd2d872b00df91481ec2b3d2a6ba848da16755aaa0cd74eccdf475a8f3cb153"), // recursion lift_join6_rv32im_v2_20.zkr
    digest!("48d2e8439ad2716b193ee22458a2b517560370389226df246141a215d3b6d260"), // recursion lift_join6_rv32im_v2_21.zkr
    digest!("11570638a376232aafa76260812f42391b3773623f791a03b19eca709cb71a00"), // recursion lift_join6_rv32im_v2_22.zkr
    digest!("87ac27538ba03416bd3fea672c1d3c366dd51a11a2ab5a3427d2ab4b3ea5df49"), // recursion lift_join7_rv32im_v2_14.zkr
    digest!("73f33970718b702076468451fc86164b6a4c581c2cfbb2192da301424676f421"), // recursion lift_join7_rv32im_v2_15.zkr
    digest!("92a4df0147e603614b52377667a8e92fc41c4e2f0bfd4865123abd59188dc10d"), // recursion lift_join7_rv32im_v2_16.zkr
    digest!("02aca319d9bd526cb9636f0c31146e1437fe7d4793373c324850ea6a8e7f9e25"), // recursion lift_join7_rv32im_v2_17.zkr
    digest!("a68f072a24457f50639b862065a6995cb2e18f0e2b139b11a925aa7086215f56"), // recursion lift_join7_rv32im_v2_18.zkr
    digest!("5817e02020247e1e61005875c962394fc3c497071197484f7c44ba4b008b1e15"), // recursion lift_join7_rv32im_v2_19.zkr
    digest!("f6ed732049835b18a4a2276cff14314394152147b590e2022dc2a41e433d6e63"), // recursion lift_join7_rv32im_v2_20.zkr
    digest!("1c167977459d3d655696033aeebd2b697b983b032853851c91043128c001ae06"), // recursion lift_join7_rv32im_v2_21.zkr
    digest!("c25c4c207c0c403c37a7650ba7e66436efb8043b19e6fc46230d0b35f348476d"), // recursion lift_join7_rv32im_v2_22.zkr
    digest!("4516445aa006f2717b3eb60244655c5f7fdd683254e463708be9003657ba4349"), // recursion lift_join8_rv32im_v2_14.zkr
    digest!("9506e31be5872957d1249b21d321795a9d09d51d738d98719ce30410422c812d"), // recursion lift_join8_rv32im_v2_15.zkr
    digest!("06085544705bf95b75da3a71ae117f1b554133417d421d31e0360935ec52a63f"), // recursion lift_join8_rv32im_v2_16.zkr
    digest!("36bf414304af564c944f640013d4bc38ffa6e553eb3f9d75f1ab614c37b38463"), // recursion lift_join8_rv32im_v2_17.zkr
    digest!("0208e73f381abf17f757105548208d4d98b94f1bc74d7824241a5750cb0c9734"), // recursion lift_join8_rv32im_v2_18.zkr
    digest!("c241a10158105c2a86fd700ba4ebf01bbfef350b629b7a1a46cc4042e1b5ea4e"), // recursion lift_join8_rv32im_v2_19.zkr
    digest!("b6776d110c3ad2060d22c53443e70f2f71c6a85d7613c87288cde7192c2da555"), // recursion lift_join8_rv32im_v2_20.zkr
    digest!("00c42c1355570006c36c4f52338bdd5ae2aa350c58b2ed303f5b2040bc284b45"), // recursion lift_join8_rv32im_v2_21.zkr
    digest!("0a1af26e2eaf73032b3f2f2526c2a221f7b55f568c57bc43fa81af06ef7d1218"), // recursion lift_join8_rv32im_v2_22.zkr
    digest!("22fb1124edd00552b5cc4a4b74517760c4e3004374e6653ade68bc308235885f"), // recursion lift_join9_rv32im_v2_14.zkr
    digest!("9a7c78626ca07c20a9ae0e1a38b7620fbeb8fe0141cbae0040e0a54a2e3ba147"), // recursion lift_join9_rv32im_v2_15.zkr
    digest!("21f8c16e98874c6364a9225d0c6b1f6d7d5426540f24c8323d9d1702162c1e04"), // recursion lift_join9_rv32im_v2_16.zkr
    digest!("7d78631b7455190015c6e025ce428e5bafef4665005aa36da85def23d4b94a43"), // recursion lift_join9_rv32im_v2_17.zkr
    digest!("7836b30aa6616d08d210cf66f0589f26f6c9993269b8231ff29f875848d74002"), // recursion lift_join9_rv32im_v2_18.zkr
    digest!("935fb00f8ec9c35deb1ba7603bd67e38c24d4c538f70e81518f14a49c313d239"), // recursion lift_join9_rv32im_v2_19.zkr
    digest!("4f68e50844b8864e8d464c49f520a653bd791509586ff4194860fc2df303c10c"), // recursion lift_join9_rv32im_v2_20.zkr
    digest!("beba8206267ec142cb1dbe1f7866660c73df1e643862e422d7646f08d11dd365"), // recursion lift_join9_rv32im_v2_21.zkr
    digest!("50d4632543a53f12503d485435ea430195cc420df2791d0bee762123406cf660"), // recursion lift_join9_rv32im_v2_22.zkr
    digest!("24a93346123509519195653ec9d6d46a55a7db2c53d796324ede0218de94c577"), // recursion lift_join_rv32im_v2_14.zkr
    digest!("b6ccbe31c999d72297e5412f1bf6d220cb0230156c6d1166c82fa50077160b17"), // recursion lift_join_rv32im_v2_15.zkr
    digest!("d04f584858ce2e5c39cc3c2f748efc0744c6fe55206e7c632ee0a73737c92766"), // recursion lift_join_rv32im_v2_16.zkr
    digest!("94111a12def08662ba746d4609513f0d74287127e65b343cfc543c329e654418"), // recursion lift_join_rv32im_v2_17.zkr
    digest!("e7acda6a4a5a966957d1ad09564b154a39236d1ab387d334089b3111ce4bf619"), // recursion lift_join_rv32im_v2_18.zkr
    digest!("5f5b2e5117d7ba1dd1766c30423c892b70d84d5719cdf86c41ef5c330a291c20"), // recursion lift_join_rv32im_v2_19.zkr
    digest!("ecea0e39f46be9242372c22d723d0157d97bdd22bc7b001467eb9e044468c106"), // recursion lift_join_rv32im_v2_20.zkr
    digest!("cff24f680d7bce5de142474d45a9502d27cda5305ed3ed21a30e2429cc2c9e28"), // recursion lift_join_rv32im_v2_21.zkr
    digest!("c3f9244553362f1d0874b721eb2f90537a304b3c38d140666c831a3c01abe83c"), // recursion lift_join_rv32im_v2_22.zkr
    digest!("fc4c1f181291530c8ff73355c37aad4db379f63e2d74d15ac3ee4e42d364891a"), // recursion lift_rv32im_v2_14.zkr
    digest!("36514d36dda6c848183a2d6187f79f6287e4a44e748fba154548463ce1fc6265"), // recursion lift_rv32im_v2_15.zkr
    digest!("0bef5e34d752b46874fb523c7d01963a37771d25a6af7c26b808fa26b8a0d815"), // recursion lift_rv32im_v2_16.zkr
    digest!("ac1a445d5babf304365232571f822725dcf71f3c8d5e7032c1bba04bad19a85e"), // recursion lift_rv32im_v2_17.zkr
    digest!("20ae3d31f954e9594cb968463ce0f823b869e3640169a561fc917226f4ca8963"), // recursion lift_rv32im_v2_18.zkr
    digest!("6f16e65efedcbf11b20b9e194e123e33aaedcd0abf1e6e5440efa263daeb375a"), // recursion lift_rv32im_v2_19.zkr
    digest!("6da21d5bc6a7534bc686b9294717f12994b13c67183c86668c62d01fcc453151"), // recursion lift_rv32im_v2_20.zkr
    digest!("60ea420126e9446430dbed5ca8b29017b6d0f31782710a1d8f8bdd3de5854714"), // recursion lift_rv32im_v2_21.zkr
    digest!("d5f05524e8bbb123f8fb1b5299413c50462cef399119953f494e57354351e844"), // recursion lift_rv32im_v2_22.zkr
    digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"), // recursion resolve.zkr
    digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"), // recursion union.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("6fa49f052b692402ece5311894b4e85b91dfbd0405a19b2a372a914f86edf53c");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("c07a65145c3cb48b6101962ea607a4dd93c753bb26975cb47feb00d3666e4404");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 137] = [
    (
        "identity.zkr",
        digest!("d4c4a53b4a3ebe4a027e36680045f4639407650e55263d328da0ce5dfa251d00"),
    ),
    (
        "join.zkr",
        digest!("7a8f24092c34ed3eb81b3d0a0b796c588c615d3488ef9e61c21dbd1e4b83ea6e"),
    ),
    (
        "lift_14.zkr",
        digest!("23e5d56caa83174f0fedca480049590b5f1ee627233ee5682358b70ecdcc5d00"),
    ),
    (
        "lift_15.zkr",
        digest!("fea7d846f2096d20a353df500ce925480d6fe930adb2fa29518dd759854ced43"),
    ),
    (
        "lift_16.zkr",
        digest!("919c664b394f6b3e7500d151204ede5e6afd4d1a3724925ca341971e93cffc46"),
    ),
    (
        "lift_17.zkr",
        digest!("bc52395cbfbbdc6783e19443161c0a559496a017aeb6370232a5313125032175"),
    ),
    (
        "lift_18.zkr",
        digest!("442f0a4cef957609ab5ee447a279351e6dc212734cbc6e3e5bbf8b086f1a7818"),
    ),
    (
        "lift_19.zkr",
        digest!("d621555070b62e383b8e16511aa8b244cb442656c5c396302fe75816c477b902"),
    ),
    (
        "lift_20.zkr",
        digest!("66f12c252c978962a100976c69ea6a4dfb2b4a2a504d6d5c60fb8e2fff6f4b61"),
    ),
    (
        "lift_21.zkr",
        digest!("88a6322eccb8f141087c48174211df1d0e071603ebfefb69f0099836569e384a"),
    ),
    (
        "lift_22.zkr",
        digest!("bb71f46d8931c80fbcf10f3b5314b93cb7b8061d4658c55000c2c26967b58a0c"),
    ),
    (
        "lift_23.zkr",
        digest!("34a4dd0eb8f410674c09c0419c8bf62ef768a476ccd8e84f5809534e0b0e0065"),
    ),
    (
        "lift_24.zkr",
        digest!("d8c1dd073822ac1da582bd52bed7ee35f106326dcb7a191d66df420016339571"),
    ),
    (
        "lift_join10_rv32im_v2_14.zkr",
        digest!("27095903856bda18aacb1a2744f25d5035b6b91b11762b004479f66b3808461a"),
    ),
    (
        "lift_join10_rv32im_v2_15.zkr",
        digest!("dedd046fc677c55cfc8fd03557b5b73802df8b24138fc5402ff5cc063ecbfd58"),
    ),
    (
        "lift_join10_rv32im_v2_16.zkr",
        digest!("5777113d18a62d0e4b24db23d23831021391023446168b43be3e600d116cb248"),
    ),
    (
        "lift_join10_rv32im_v2_17.zkr",
        digest!("43e01b6a51be8547341b0b5e4da05c41fd6749767ce5d04b5488195659235623"),
    ),
    (
        "lift_join10_rv32im_v2_18.zkr",
        digest!("4ecc5e2c4992e70448f37732698aa35660e1203881039c5416491b2f762bb133"),
    ),
    (
        "lift_join10_rv32im_v2_19.zkr",
        digest!("0d8875644e8e75730c2beb5ca375b952ad88f46325a26a6aa8f3f025176a5a59"),
    ),
    (
        "lift_join10_rv32im_v2_20.zkr",
        digest!("0c0f1835f512ca66eeef7d0ded36702cc21ff35edc771b73edde772e5edf4728"),
    ),
    (
        "lift_join10_rv32im_v2_21.zkr",
        digest!("625cc74256a1872abcf2676cbbe3412a73ed0d5f433a7a6ab6c04132ed0ba709"),
    ),
    (
        "lift_join10_rv32im_v2_22.zkr",
        digest!("c83b970317be1724c7af81161e60ea42f8f93e6c5427212a8fd4b46d06582175"),
    ),
    (
        "lift_join10_rv32im_v2_23.zkr",
        digest!("8d9c327333959f17364f766db3d3e944e4eb703e24aee81948867f35791a3a36"),
    ),
    (
        "lift_join10_rv32im_v2_24.zkr",
        digest!("ba97f3759ac3814b48fee535a8609470f2afdd49bba33b5bf4e8c83f5171e207"),
    ),
    (
        "lift_join2_rv32im_v2_14.zkr",
        digest!("fb946142053c7b6d7443d44a32c6391aebdc130d1fa7672b4eb14b4fe0d94d60"),
    ),
    (
        "lift_join2_rv32im_v2_15.zkr",
        digest!("28c1cc0f68837b0539345d6fb2d0f661c841393a20079c095351184fe1c95271"),
    ),
    (
        "lift_join2_rv32im_v2_16.zkr",
        digest!("a1ce4f190b0ebb2efbe9f9622664c726e8a01015d47b54740f715c67aece2812"),
    ),
    (
        "lift_join2_rv32im_v2_17.zkr",
        digest!("5f6118014b16d56829e5e205d25f48001e6ab7605ec3f7495ae8d10f9b2c2851"),
    ),
    (
        "lift_join2_rv32im_v2_18.zkr",
        digest!("7587084260cd1810f982aa3c342ad04528799e74c4ac6533be5c0931b9e0ab32"),
    ),
    (
        "lift_join2_rv32im_v2_19.zkr",
        digest!("9873df09fc9c54713101261777a6796bd738f169f97afa73674e9f427509f469"),
    ),
    (
        "lift_join2_rv32im_v2_20.zkr",
        digest!("c64f9017da24b01042c8c83d123a1c115fd7d0389dbba642649c554adf201619"),
    ),
    (
        "lift_join2_rv32im_v2_21.zkr",
        digest!("e9575968b8c278113ee9e82878e9af6991675f17ba727768b7b3d02b03403b0d"),
    ),
    (
        "lift_join2_rv32im_v2_22.zkr",
        digest!("7772cd05351ddc157e407a5f8841ef05b4aa1c64a3b24d49987b3b17e9ffdc14"),
    ),
    (
        "lift_join2_rv32im_v2_23.zkr",
        digest!("57ef0502aa58492139fb4877918c531cb6095f395cf4b0033d89113b7e84e80a"),
    ),
    (
        "lift_join2_rv32im_v2_24.zkr",
        digest!("77597a489a915e34ecac871d6d1b152fa15d4a17bb185f337a626659a109b109"),
    ),
    (
        "lift_join3_rv32im_v2_14.zkr",
        digest!("e315de420e2b3463eacf6a7711e786660ee7476b713f770330238239dd8fa71e"),
    ),
    (
        "lift_join3_rv32im_v2_15.zkr",
        digest!("842afa147cec9966fc564e0b18e84632569d6a52d8d7a60ad72ba12778293a5f"),
    ),
    (
        "lift_join3_rv32im_v2_16.zkr",
        digest!("e129565b1875b854ed360d3b639e3e44b246583b94ca4726dba87929e63aea76"),
    ),
    (
        "lift_join3_rv32im_v2_17.zkr",
        digest!("afc2623ba60cb0749d4505107b5f703451bb5738870831368c26b427b2352f00"),
    ),
    (
        "lift_join3_rv32im_v2_18.zkr",
        digest!("5abeb439dbe71737ebfbcd2c7c3ec0188338a240d78bf05d5bc3495185a6a508"),
    ),
    (
        "lift_join3_rv32im_v2_19.zkr",
        digest!("c17f161086fc3032c320fb420b90156bc210dc211f7c9648ac81b06af9b12b68"),
    ),
    (
        "lift_join3_rv32im_v2_20.zkr",
        digest!("80a7ef27dfd15b3b615eca73d7c4bf19d821c762ec9b0e3af918683e5b53b05a"),
    ),
    (
        "lift_join3_rv32im_v2_21.zkr",
        digest!("ae24e96fa68d501e72b06e4d57ddf7118a03f60762f3fd467ebae31faf9abc5d"),
    ),
    (
        "lift_join3_rv32im_v2_22.zkr",
        digest!("ecb4c543e99a8b3ad1392b10c4ecb75bbdf1546d45bf78682f03ab3a99dc8a3d"),
    ),
    (
        "lift_join3_rv32im_v2_23.zkr",
        digest!("c4e47c70f27bb673fc9f5c3561092233fe05a33d9d1b86172239160b7dca8f6d"),
    ),
    (
        "lift_join3_rv32im_v2_24.zkr",
        digest!("845f994d8b81cd1cb6310319db346b5aa081cb0e70a71655f391a2198e216e34"),
    ),
    (
        "lift_join4_rv32im_v2_14.zkr",
        digest!("72d1bf09902ef5555a56817109812e62d869e61e1bfba621d49f826906d86e41"),
    ),
    (
        "lift_join4_rv32im_v2_15.zkr",
        digest!("ba27320048b0bd4142b1df1d7ada7a526fc5ba3defaa6663696f4576ab78db45"),
    ),
    (
        "lift_join4_rv32im_v2_16.zkr",
        digest!("117ab65329ca693dbafedf10633a0d14ad572743106bfc6f89233d283a53d35c"),
    ),
    (
        "lift_join4_rv32im_v2_17.zkr",
        digest!("7dd6e313ee04c867ebfe125665ecad551db16f6ba1f127436bb3ab16d562066a"),
    ),
    (
        "lift_join4_rv32im_v2_18.zkr",
        digest!("2115894a61a70613a44e7a6364af535ac3217943020742598a70184d6678b457"),
    ),
    (
        "lift_join4_rv32im_v2_19.zkr",
        digest!("c136f242ecf8e762bde0e262b54e1904cf935e3fa6bb8736e675920e0d365560"),
    ),
    (
        "lift_join4_rv32im_v2_20.zkr",
        digest!("c226ab3505c0b4319de59e3a704520296c121e0f323bf9450c8637779d2df440"),
    ),
    (
        "lift_join4_rv32im_v2_21.zkr",
        digest!("c65ba5519e265f16ce0fb81f5841f1288c41621a8d5244413e28c2306b441c2f"),
    ),
    (
        "lift_join4_rv32im_v2_22.zkr",
        digest!("74c124761ba8ee668e70de730e1db964baebfa4897245d54bc3c3d778420fb12"),
    ),
    (
        "lift_join4_rv32im_v2_23.zkr",
        digest!("177927598469e4701716937685427c1a0eda1475f6ae6c6a62479b270bd0da6a"),
    ),
    (
        "lift_join4_rv32im_v2_24.zkr",
        digest!("d3fdca59a4b8140b1703be686f57d01a5bcb86062162d34e6f5b644961810120"),
    ),
    (
        "lift_join5_rv32im_v2_14.zkr",
        digest!("3f78bf159aab0f32320d05416ca2c359ec4e626dff0fdb523c009450b4e0b30a"),
    ),
    (
        "lift_join5_rv32im_v2_15.zkr",
        digest!("7e627427b771701f6345b7436187fd2e909397659406fc0ae689e33667460776"),
    ),
    (
        "lift_join5_rv32im_v2_16.zkr",
        digest!("80b94842c82bc7315983ce190807385b2b2a2814994f2c1f906ec805116baa0e"),
    ),
    (
        "lift_join5_rv32im_v2_17.zkr",
        digest!("1582ba76f42e2e05ec57f06c4624a94d474d631310fc1e3be7d99b3ab9652a54"),
    ),
    (
        "lift_join5_rv32im_v2_18.zkr",
        digest!("ef8bee28e8e3494fa970a33aaaddf719b6978404270c0b12365e385388d2281a"),
    ),
    (
        "lift_join5_rv32im_v2_19.zkr",
        digest!("9b5f986ceec3af1040e96d240e5ddc25adcc595779040f403f40ea1077c46d45"),
    ),
    (
        "lift_join5_rv32im_v2_20.zkr",
        digest!("5b95240c7e6f8e744f32ea634ba78308d98c910d1c557521585ef4744a855575"),
    ),
    (
        "lift_join5_rv32im_v2_21.zkr",
        digest!("ed4b535f65a1b71519081d38d8282450e085dc298c51e549010adb06a0d46c27"),
    ),
    (
        "lift_join5_rv32im_v2_22.zkr",
        digest!("60f564004a7f687230b68f039fc4c71a3666075376e72434496ad5447c034c72"),
    ),
    (
        "lift_join5_rv32im_v2_23.zkr",
        digest!("6044370a5493e242e5cc487442d91c4149ad042fe881d513c92c9d673c0e160a"),
    ),
    (
        "lift_join5_rv32im_v2_24.zkr",
        digest!("63a215420e85c93ff003af4760b03074992cfa5541d2c05c0f1b6010d2213f54"),
    ),
    (
        "lift_join6_rv32im_v2_14.zkr",
        digest!("b2693034f830c22bc3dfb2506adb6d56203507477fa08245419989760be5a52f"),
    ),
    (
        "lift_join6_rv32im_v2_15.zkr",
        digest!("ab20521d63a86d2eebc9cf316256185f92e99737d316044b48889f1ad41a5866"),
    ),
    (
        "lift_join6_rv32im_v2_16.zkr",
        digest!("8af7c560b454740945c46a476385342e2e3695106a56ee6694a9750981164103"),
    ),
    (
        "lift_join6_rv32im_v2_17.zkr",
        digest!("05d71520a258c46c5d27300bfdd8560768f745710fcd487404dcc63c964dea41"),
    ),
    (
        "lift_join6_rv32im_v2_18.zkr",
        digest!("58136b6b29785f1647d5d76b5921a54756d3cd11e481781c077e776cda2b250d"),
    ),
    (
        "lift_join6_rv32im_v2_19.zkr",
        digest!("840f936da3d6eb6dc8a63c37ef95152513083f2524d35860ee48cd454cdc4a25"),
    ),
    (
        "lift_join6_rv32im_v2_20.zkr",
        digest!("bfd2d872b00df91481ec2b3d2a6ba848da16755aaa0cd74eccdf475a8f3cb153"),
    ),
    (
        "lift_join6_rv32im_v2_21.zkr",
        digest!("48d2e8439ad2716b193ee22458a2b517560370389226df246141a215d3b6d260"),
    ),
    (
        "lift_join6_rv32im_v2_22.zkr",
        digest!("11570638a376232aafa76260812f42391b3773623f791a03b19eca709cb71a00"),
    ),
    (
        "lift_join6_rv32im_v2_23.zkr",
        digest!("7677121e8caf90774f46ef5bbc8bc954667f1316f7de3c04ef40175ce7612d1b"),
    ),
    (
        "lift_join6_rv32im_v2_24.zkr",
        digest!("36ffa70c67dc513c18210e57bcb80b39d4d9d532e5ced90d4369320e6773fe61"),
    ),
    (
        "lift_join7_rv32im_v2_14.zkr",
        digest!("87ac27538ba03416bd3fea672c1d3c366dd51a11a2ab5a3427d2ab4b3ea5df49"),
    ),
    (
        "lift_join7_rv32im_v2_15.zkr",
        digest!("73f33970718b702076468451fc86164b6a4c581c2cfbb2192da301424676f421"),
    ),
    (
        "lift_join7_rv32im_v2_16.zkr",
        digest!("92a4df0147e603614b52377667a8e92fc41c4e2f0bfd4865123abd59188dc10d"),
    ),
    (
        "lift_join7_rv32im_v2_17.zkr",
        digest!("02aca319d9bd526cb9636f0c31146e1437fe7d4793373c324850ea6a8e7f9e25"),
    ),
    (
        "lift_join7_rv32im_v2_18.zkr",
        digest!("a68f072a24457f50639b862065a6995cb2e18f0e2b139b11a925aa7086215f56"),
    ),
    (
        "lift_join7_rv32im_v2_19.zkr",
        digest!("5817e02020247e1e61005875c962394fc3c497071197484f7c44ba4b008b1e15"),
    ),
    (
        "lift_join7_rv32im_v2_20.zkr",
        digest!("f6ed732049835b18a4a2276cff14314394152147b590e2022dc2a41e433d6e63"),
    ),
    (
        "lift_join7_rv32im_v2_21.zkr",
        digest!("1c167977459d3d655696033aeebd2b697b983b032853851c91043128c001ae06"),
    ),
    (
        "lift_join7_rv32im_v2_22.zkr",
        digest!("c25c4c207c0c403c37a7650ba7e66436efb8043b19e6fc46230d0b35f348476d"),
    ),
    (
        "lift_join7_rv32im_v2_23.zkr",
        digest!("3da96b5c976b7a646e3d4121f756674df9ff0d5e8ac8e823ead38f6159c44939"),
    ),
    (
        "lift_join7_rv32im_v2_24.zkr",
        digest!("0ee9fe4157e1a43ce3279b250a92ca02e56ad33bc75f0c0685d16003c9488f4c"),
    ),
    (
        "lift_join8_rv32im_v2_14.zkr",
        digest!("4516445aa006f2717b3eb60244655c5f7fdd683254e463708be9003657ba4349"),
    ),
    (
        "lift_join8_rv32im_v2_15.zkr",
        digest!("9506e31be5872957d1249b21d321795a9d09d51d738d98719ce30410422c812d"),
    ),
    (
        "lift_join8_rv32im_v2_16.zkr",
        digest!("06085544705bf95b75da3a71ae117f1b554133417d421d31e0360935ec52a63f"),
    ),
    (
        "lift_join8_rv32im_v2_17.zkr",
        digest!("36bf414304af564c944f640013d4bc38ffa6e553eb3f9d75f1ab614c37b38463"),
    ),
    (
        "lift_join8_rv32im_v2_18.zkr",
        digest!("0208e73f381abf17f757105548208d4d98b94f1bc74d7824241a5750cb0c9734"),
    ),
    (
        "lift_join8_rv32im_v2_19.zkr",
        digest!("c241a10158105c2a86fd700ba4ebf01bbfef350b629b7a1a46cc4042e1b5ea4e"),
    ),
    (
        "lift_join8_rv32im_v2_20.zkr",
        digest!("b6776d110c3ad2060d22c53443e70f2f71c6a85d7613c87288cde7192c2da555"),
    ),
    (
        "lift_join8_rv32im_v2_21.zkr",
        digest!("00c42c1355570006c36c4f52338bdd5ae2aa350c58b2ed303f5b2040bc284b45"),
    ),
    (
        "lift_join8_rv32im_v2_22.zkr",
        digest!("0a1af26e2eaf73032b3f2f2526c2a221f7b55f568c57bc43fa81af06ef7d1218"),
    ),
    (
        "lift_join8_rv32im_v2_23.zkr",
        digest!("d78df447fd374e435f92434b0a0c9e0d307af9763e3d6b740271ea23e609dd60"),
    ),
    (
        "lift_join8_rv32im_v2_24.zkr",
        digest!("6a0f481bd6ef362275712636d89f570cce14c3461aba1c555c283c485427c72b"),
    ),
    (
        "lift_join9_rv32im_v2_14.zkr",
        digest!("22fb1124edd00552b5cc4a4b74517760c4e3004374e6653ade68bc308235885f"),
    ),
    (
        "lift_join9_rv32im_v2_15.zkr",
        digest!("9a7c78626ca07c20a9ae0e1a38b7620fbeb8fe0141cbae0040e0a54a2e3ba147"),
    ),
    (
        "lift_join9_rv32im_v2_16.zkr",
        digest!("21f8c16e98874c6364a9225d0c6b1f6d7d5426540f24c8323d9d1702162c1e04"),
    ),
    (
        "lift_join9_rv32im_v2_17.zkr",
        digest!("7d78631b7455190015c6e025ce428e5bafef4665005aa36da85def23d4b94a43"),
    ),
    (
        "lift_join9_rv32im_v2_18.zkr",
        digest!("7836b30aa6616d08d210cf66f0589f26f6c9993269b8231ff29f875848d74002"),
    ),
    (
        "lift_join9_rv32im_v2_19.zkr",
        digest!("935fb00f8ec9c35deb1ba7603bd67e38c24d4c538f70e81518f14a49c313d239"),
    ),
    (
        "lift_join9_rv32im_v2_20.zkr",
        digest!("4f68e50844b8864e8d464c49f520a653bd791509586ff4194860fc2df303c10c"),
    ),
    (
        "lift_join9_rv32im_v2_21.zkr",
        digest!("beba8206267ec142cb1dbe1f7866660c73df1e643862e422d7646f08d11dd365"),
    ),
    (
        "lift_join9_rv32im_v2_22.zkr",
        digest!("50d4632543a53f12503d485435ea430195cc420df2791d0bee762123406cf660"),
    ),
    (
        "lift_join9_rv32im_v2_23.zkr",
        digest!("5a4d232600d34d2a8dd6787606adec7085445f66edb83933b8e08240afb3331c"),
    ),
    (
        "lift_join9_rv32im_v2_24.zkr",
        digest!("dc9f942b24f4ae0df059550975d9e24954c3a72c8eaaf4411d8ecb0229433564"),
    ),
    (
        "lift_join_rv32im_v2_14.zkr",
        digest!("24a93346123509519195653ec9d6d46a55a7db2c53d796324ede0218de94c577"),
    ),
    (
        "lift_join_rv32im_v2_15.zkr",
        digest!("b6ccbe31c999d72297e5412f1bf6d220cb0230156c6d1166c82fa50077160b17"),
    ),
    (
        "lift_join_rv32im_v2_16.zkr",
        digest!("d04f584858ce2e5c39cc3c2f748efc0744c6fe55206e7c632ee0a73737c92766"),
    ),
    (
        "lift_join_rv32im_v2_17.zkr",
        digest!("94111a12def08662ba746d4609513f0d74287127e65b343cfc543c329e654418"),
    ),
    (
        "lift_join_rv32im_v2_18.zkr",
        digest!("e7acda6a4a5a966957d1ad09564b154a39236d1ab387d334089b3111ce4bf619"),
    ),
    (
        "lift_join_rv32im_v2_19.zkr",
        digest!("5f5b2e5117d7ba1dd1766c30423c892b70d84d5719cdf86c41ef5c330a291c20"),
    ),
    (
        "lift_join_rv32im_v2_20.zkr",
        digest!("ecea0e39f46be9242372c22d723d0157d97bdd22bc7b001467eb9e044468c106"),
    ),
    (
        "lift_join_rv32im_v2_21.zkr",
        digest!("cff24f680d7bce5de142474d45a9502d27cda5305ed3ed21a30e2429cc2c9e28"),
    ),
    (
        "lift_join_rv32im_v2_22.zkr",
        digest!("c3f9244553362f1d0874b721eb2f90537a304b3c38d140666c831a3c01abe83c"),
    ),
    (
        "lift_join_rv32im_v2_23.zkr",
        digest!("755007581e76c11d22457a0e14e7ed40f7a1816a535e763206c8816f25c36219"),
    ),
    (
        "lift_join_rv32im_v2_24.zkr",
        digest!("9805b06f621a7c33c635603547c3db134d258a418e918956bcc3f13a8eb3400f"),
    ),
    (
        "lift_rv32im_v2_14.zkr",
        digest!("fc4c1f181291530c8ff73355c37aad4db379f63e2d74d15ac3ee4e42d364891a"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("36514d36dda6c848183a2d6187f79f6287e4a44e748fba154548463ce1fc6265"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("0bef5e34d752b46874fb523c7d01963a37771d25a6af7c26b808fa26b8a0d815"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("ac1a445d5babf304365232571f822725dcf71f3c8d5e7032c1bba04bad19a85e"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("20ae3d31f954e9594cb968463ce0f823b869e3640169a561fc917226f4ca8963"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("6f16e65efedcbf11b20b9e194e123e33aaedcd0abf1e6e5440efa263daeb375a"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("6da21d5bc6a7534bc686b9294717f12994b13c67183c86668c62d01fcc453151"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("60ea420126e9446430dbed5ca8b29017b6d0f31782710a1d8f8bdd3de5854714"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("d5f05524e8bbb123f8fb1b5299413c50462cef399119953f494e57354351e844"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("b4459e2bc38f800ed80c956234d59a4611d0f825eae566478ac4c06a07a61c21"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("4434690c184bd542c823aa1efcf6c15cf8c83d0aafbf4f3e0552d8125eedd12a"),
    ),
    (
        "resolve.zkr",
        digest!("53a7b23d07f99e5d5685e85874f5181e8486aa267a0ae607ffe9ba47c8bdda4a"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("d9263d55844edd3c3295e91916284f50085c9f1904e90765c04f4a5c23311836"),
    ),
    (
        "union.zkr",
        digest!("7771415b778fea1923440e2eb22c4a1e1d7ada2d42cbe03d13402743c0988a31"),
    ),
];

/// Control IDs for included recursion programs (ZKRs), using SHA-256.
pub const SHA256_CONTROL_IDS: [(&str, Digest); 137] = [
    (
        "identity.zkr",
        digest!("9262c0902e17395ca3acf873675468675035ab24228265379087e8ace5c3f894"),
    ),
    (
        "join.zkr",
        digest!("dc44002689aa7852410ad1c840388d66b8b9a2f6d0c4fb6b3ac6ec2ea17d9855"),
    ),
    (
        "lift_14.zkr",
        digest!("1a985d1028d6c5479e3e872f57ae4dc9ddacc3cfbc6f424095ce85324103b88c"),
    ),
    (
        "lift_15.zkr",
        digest!("1c627c5b154680c70d62a67c46c7eac854768bcb64d3c74eb150c8988b062fec"),
    ),
    (
        "lift_16.zkr",
        digest!("8843478fd585afc7cf84c8905ce16ed8cadbb61c45248619f9b252900e5167c8"),
    ),
    (
        "lift_17.zkr",
        digest!("4a54533e7ef8b620ca102ed763ebc94e969fd608d669623d466d43775dbec7a1"),
    ),
    (
        "lift_18.zkr",
        digest!("954ffa89a80c010191f3ade9ca63c1f4f9689410df02faa801dc1b98ac557cfb"),
    ),
    (
        "lift_19.zkr",
        digest!("87150aa1b6b0fc92b68d9238d0c2a83a17da3d5d3775fd23b2517e0d7fd7697b"),
    ),
    (
        "lift_20.zkr",
        digest!("00676bedc32cc1e0dd7e490be83f4be39f379beedc35983ace0782061d65d73d"),
    ),
    (
        "lift_21.zkr",
        digest!("10d8d3a1eee1dec7c6cc0553222ab8ac9b6bfeb0bd1553e097fb29a3ef22a606"),
    ),
    (
        "lift_22.zkr",
        digest!("fcbe182cb5a235fc28d43ba1137908609958587e18060aa712be08d5833a8af3"),
    ),
    (
        "lift_23.zkr",
        digest!("f3f8278b8f56e0c2292cf7d0b395405dcf67760638e4ad901b3df406303c90b9"),
    ),
    (
        "lift_24.zkr",
        digest!("a827fd3663ab862331c47b1ba985fde346c13851535b1d80693b6367771644a7"),
    ),
    (
        "lift_join10_rv32im_v2_14.zkr",
        digest!("6e20f09a490010cf09f43a42b984245e728fcb43bed6096a0f3048bf64155fe5"),
    ),
    (
        "lift_join10_rv32im_v2_15.zkr",
        digest!("b4f3abb938900776ada6b3349393ee04064169c8ba22680f657fdc885aae09ad"),
    ),
    (
        "lift_join10_rv32im_v2_16.zkr",
        digest!("c41be2d2fe67cf1517288110716f4b0f573a1125d67cf38c8656ca61743a2d25"),
    ),
    (
        "lift_join10_rv32im_v2_17.zkr",
        digest!("ad678f12534dfea1cfbfbf9427542bdba94f2611ddcff7190eb831a7b4a9a8e9"),
    ),
    (
        "lift_join10_rv32im_v2_18.zkr",
        digest!("c1cbff2b62de7bd9013eb8b415219c11b6a3eea35c97de0dcf2125293930b5ea"),
    ),
    (
        "lift_join10_rv32im_v2_19.zkr",
        digest!("b2fa6a8ed7300dac9491aec233fa88c63a5acc80ef1c3b0afca950623b683c98"),
    ),
    (
        "lift_join10_rv32im_v2_20.zkr",
        digest!("6d80eea2f43c5b9e8114b5f26002122f834da35788167ef61795b5989420a75e"),
    ),
    (
        "lift_join10_rv32im_v2_21.zkr",
        digest!("e09f0c5a1acb2cf339d57b8fe51f4c086b1081fe65bc98ba5c8a4caba28a53a3"),
    ),
    (
        "lift_join10_rv32im_v2_22.zkr",
        digest!("7a9c1c1f3eaf8b58becd3d5b3796f4efef9c90f42677deb4d4b701f159eb1ea7"),
    ),
    (
        "lift_join10_rv32im_v2_23.zkr",
        digest!("bb6c93a4712d247c488f1db8d1841bac11a8c6a9f51d10f262c4669a417d593b"),
    ),
    (
        "lift_join10_rv32im_v2_24.zkr",
        digest!("20d8a4bb297e68582bafbb2199db653c083fa92f1a37e3907a057fa0481075a9"),
    ),
    (
        "lift_join2_rv32im_v2_14.zkr",
        digest!("5d35d008c9e5759f6c47941e3edec835168f6aba71d681bcc899891f42e60986"),
    ),
    (
        "lift_join2_rv32im_v2_15.zkr",
        digest!("efd39994369fa6011718811a6a7ad1695f64bdcb8d15f5ed63441a57aed7b269"),
    ),
    (
        "lift_join2_rv32im_v2_16.zkr",
        digest!("6ed39d7ebc9a6c7f0aa0a0b54c64bcb053b0bcacbbdba415538c8c61c441e09a"),
    ),
    (
        "lift_join2_rv32im_v2_17.zkr",
        digest!("22f696066c37cbe394655ff4bcbfc35cbec78a97cc5dfd6ac6c544ffed6d0e14"),
    ),
    (
        "lift_join2_rv32im_v2_18.zkr",
        digest!("d00bdd1336838f69958b40f3b838f9443c658a8c3e79df2777c9b9dcf528ae0b"),
    ),
    (
        "lift_join2_rv32im_v2_19.zkr",
        digest!("0afb4be6b877770cc0c7dcd937d155c37fac5eea819e6b611427d54395670e2d"),
    ),
    (
        "lift_join2_rv32im_v2_20.zkr",
        digest!("2c16d26d43d6d52c9c3b6c8a0dad5f6f1e04e5b0506d735df09a771c40ac72c3"),
    ),
    (
        "lift_join2_rv32im_v2_21.zkr",
        digest!("87c20423c800ae9d3e8d1c6ceacacf6115e53780f2f62f886387d752ceb66727"),
    ),
    (
        "lift_join2_rv32im_v2_22.zkr",
        digest!("da69d42f86ec6419480a3ba8fb89b626611ad092bf15863cba61b9646f02830c"),
    ),
    (
        "lift_join2_rv32im_v2_23.zkr",
        digest!("cdb0a406ffbaa2f9ed134f753fa493b075f6f9eb945ea101a33afaac6f47e8d6"),
    ),
    (
        "lift_join2_rv32im_v2_24.zkr",
        digest!("ab81f43bc86f1e74a0f079169058c5762525e394583a5a836fc8871009722cab"),
    ),
    (
        "lift_join3_rv32im_v2_14.zkr",
        digest!("0a21714899537932962c86ef5c151a0aef9bd734e61ea5469db7a55736293a02"),
    ),
    (
        "lift_join3_rv32im_v2_15.zkr",
        digest!("d5a5285010ef095000d2e1ffeea4ee0d16a135d28a558eea672ea94f89ef3aea"),
    ),
    (
        "lift_join3_rv32im_v2_16.zkr",
        digest!("28a951fd9bc1df39e60560a34ef332f0addbf62b308a3e950b5077582be47039"),
    ),
    (
        "lift_join3_rv32im_v2_17.zkr",
        digest!("466e6f14116f02c6239fdeb50c144d0435b36fc22bc00bb580b97d25a8012619"),
    ),
    (
        "lift_join3_rv32im_v2_18.zkr",
        digest!("0b41427d07666da73f2f325cd7b6c34d1bef8497b705d707f558ee450e7dd672"),
    ),
    (
        "lift_join3_rv32im_v2_19.zkr",
        digest!("8623a867f6d2fd7558cc91b79958e76cc9f3f24bbf19fe0626eb5ab232c63f85"),
    ),
    (
        "lift_join3_rv32im_v2_20.zkr",
        digest!("d345d456a93f9e5015df75739d0e3202012d79a6dd1e9b3731787a2a7ef22ad6"),
    ),
    (
        "lift_join3_rv32im_v2_21.zkr",
        digest!("0d416281f2a6c24be7c82588629e878ab4353da6ee472fe398af127400886274"),
    ),
    (
        "lift_join3_rv32im_v2_22.zkr",
        digest!("d00b78e329d3df1a9074e72a6a1870f0a061727397901d0344eb07c4f1e3d161"),
    ),
    (
        "lift_join3_rv32im_v2_23.zkr",
        digest!("94c6f64dcb5d03a25fcd55a27042114919ec638bcf651fd5c04854736467c373"),
    ),
    (
        "lift_join3_rv32im_v2_24.zkr",
        digest!("2a5eef4521acc263e188b404e3d5aa2d4a172c22d0ec8b5b0e676c622fe24ae2"),
    ),
    (
        "lift_join4_rv32im_v2_14.zkr",
        digest!("9144a60cb5f2522662c5ea26267d150358d4bcd03e2e92695b680b4e288d290c"),
    ),
    (
        "lift_join4_rv32im_v2_15.zkr",
        digest!("d9ce24b4b2551d83614173b58ccff2a7385d3498c7a5e3d04889513a414aab5e"),
    ),
    (
        "lift_join4_rv32im_v2_16.zkr",
        digest!("bb6e569090e7d700eb9e73da806d31e65be4d927757a30c6d1ea80cdf633e303"),
    ),
    (
        "lift_join4_rv32im_v2_17.zkr",
        digest!("4e3724580471b26155b12b9cfaed13322d6d578c26996fc3b778aa9e29b18c22"),
    ),
    (
        "lift_join4_rv32im_v2_18.zkr",
        digest!("158d276b84bbe9b9cb2141970431356cb19ecfec22a2a880ff90a5d5f09dcee4"),
    ),
    (
        "lift_join4_rv32im_v2_19.zkr",
        digest!("884c45f181e021ff27590ac9efc56987fb15ddf817bbabd21635dd366c46aad2"),
    ),
    (
        "lift_join4_rv32im_v2_20.zkr",
        digest!("49c05ea9a3d3d1b78383294b816e0bded6542d8a9e846db146ac7f779baba8d0"),
    ),
    (
        "lift_join4_rv32im_v2_21.zkr",
        digest!("d9040672a6f021771c86c76d2d24519db8225026d0b386d3e95a22f814356317"),
    ),
    (
        "lift_join4_rv32im_v2_22.zkr",
        digest!("20b32b0875e6cc7a58011b531f085d8b7a5f91cef1855516517019b2120b3ae4"),
    ),
    (
        "lift_join4_rv32im_v2_23.zkr",
        digest!("d5c1b0163dd1476bc922d264da596ceb972422044b2a382b07262230b9428e2d"),
    ),
    (
        "lift_join4_rv32im_v2_24.zkr",
        digest!("d4a3ced06498bcec346e4de88cc9c198eae49ac836f58056c1a0020a867708d1"),
    ),
    (
        "lift_join5_rv32im_v2_14.zkr",
        digest!("17ebfa013c3d07bff8f703b60537db739b4df662a59599cd2ca54770bc83786b"),
    ),
    (
        "lift_join5_rv32im_v2_15.zkr",
        digest!("1cc84e1ff6acdeb84f8590a0ce77091ce948cc4cf8231a5dd441ddc4ea5f1954"),
    ),
    (
        "lift_join5_rv32im_v2_16.zkr",
        digest!("a932694c1547aa8a29484ba59317ba7197b987837221616090f1bb23b2149bb6"),
    ),
    (
        "lift_join5_rv32im_v2_17.zkr",
        digest!("b96cbcee54518f358a35959208f9fb88f5c1d801cb9a81b64c2e7434b7ea91c7"),
    ),
    (
        "lift_join5_rv32im_v2_18.zkr",
        digest!("1e0eeef5b561910c5a46ee69f3efd95af472e9ca21f2a85ea491a43aeedd6a30"),
    ),
    (
        "lift_join5_rv32im_v2_19.zkr",
        digest!("c5ffca19c41f5d61c6f82b76086f8a0762e1fd8f6f75ef33cdb50b84c219e4e4"),
    ),
    (
        "lift_join5_rv32im_v2_20.zkr",
        digest!("e47939dada5f0fd58841dbb0734081cbc2ed89c07986afc9b61329f92d148b5a"),
    ),
    (
        "lift_join5_rv32im_v2_21.zkr",
        digest!("144dcfce4332048f552057263477cb5f838865f5849024628b301c2e0063ed77"),
    ),
    (
        "lift_join5_rv32im_v2_22.zkr",
        digest!("84cfec4329dae3d95abc7699408d89860ced3ee05409e18459cde87aa9ea270b"),
    ),
    (
        "lift_join5_rv32im_v2_23.zkr",
        digest!("54e07b3851fdc47fd0f3ba1d82d5214fe438f5a0f91dc0e53cf07b58d9b645bf"),
    ),
    (
        "lift_join5_rv32im_v2_24.zkr",
        digest!("8dc6d10ded3ccff0568edb7f81d014dd792e33c4b3e7b3888b4cafd239b26f4c"),
    ),
    (
        "lift_join6_rv32im_v2_14.zkr",
        digest!("7809e7789dfd734677ca68bddd4e30feb353a57f912fec6a66544a94c73ccdec"),
    ),
    (
        "lift_join6_rv32im_v2_15.zkr",
        digest!("6594d6363889998ebfb1914a71391486b3948de25eb506d783c5efa22ebb8db1"),
    ),
    (
        "lift_join6_rv32im_v2_16.zkr",
        digest!("ac521ace90c0d2444058f0ca423a77af1df462c4dd036f9783a4441902b9cb33"),
    ),
    (
        "lift_join6_rv32im_v2_17.zkr",
        digest!("e214c1ae7556027540fe504175ad62e87b7b7967cfac9f09d1d600a8f495246b"),
    ),
    (
        "lift_join6_rv32im_v2_18.zkr",
        digest!("23946676d4231d6b83c8fa08db6b5a8b175ba6cd6c162ddbb8d52a19b7c42402"),
    ),
    (
        "lift_join6_rv32im_v2_19.zkr",
        digest!("bc4ddc1b48e97cb3fd887a50f4ad01b74fce615af073e5de3c48dee0fd1ddf92"),
    ),
    (
        "lift_join6_rv32im_v2_20.zkr",
        digest!("53ac908b45373e0fd6fd1efd410164acfcdc4629c4236d82c062a9b5d4b332df"),
    ),
    (
        "lift_join6_rv32im_v2_21.zkr",
        digest!("8dd3da87c375e5407622d8ce1feb936ed5bba880895c4d25a12c2108dc4c5a39"),
    ),
    (
        "lift_join6_rv32im_v2_22.zkr",
        digest!("441e23555ae8dfee0d933a3ba044125a2f5a0ef867d0fcbf307ae045d0ec5aa6"),
    ),
    (
        "lift_join6_rv32im_v2_23.zkr",
        digest!("9b47608bf66a79bd71b0f61ec5943fbfd34959dc6aea6a559b33c1645587197d"),
    ),
    (
        "lift_join6_rv32im_v2_24.zkr",
        digest!("aeede429ed2bb33c4d0156437c1c17a52352b5c155078af42531266e7e6912fa"),
    ),
    (
        "lift_join7_rv32im_v2_14.zkr",
        digest!("2df072bee8a0cb7f8e85488a7b18bf1b16c3c82ca9cbfe0ca5784ff0c884e403"),
    ),
    (
        "lift_join7_rv32im_v2_15.zkr",
        digest!("b77f1ec5261788a250e4f075d590db7a3263a4f68cfee955d153d3a9d95926a7"),
    ),
    (
        "lift_join7_rv32im_v2_16.zkr",
        digest!("8d08647e4e1567365112ee60f5aea546046be38f81d7498ae556a25a42868d7f"),
    ),
    (
        "lift_join7_rv32im_v2_17.zkr",
        digest!("020e15ca1121f42e9e1c4755353c24eef65352ed1f5973bc1bc8ecbcb07d2473"),
    ),
    (
        "lift_join7_rv32im_v2_18.zkr",
        digest!("45affa4c92b6f35aeb6ef789eb1e9721f85d53471effc694d01f33e29473abea"),
    ),
    (
        "lift_join7_rv32im_v2_19.zkr",
        digest!("a36428ff22f3a4ddd4d4a7249a400fec72aebe56ecdad846be1ea8fe7e2f7d65"),
    ),
    (
        "lift_join7_rv32im_v2_20.zkr",
        digest!("b6b1a408baf8be61b2e9b7b23acfc1b9a6fac9a8f4e81addc4ac53481045a134"),
    ),
    (
        "lift_join7_rv32im_v2_21.zkr",
        digest!("e5a72fc73c42b8dce95388ba38c22d9fe63d7230183ccf7ca6dfc05b54daa0b1"),
    ),
    (
        "lift_join7_rv32im_v2_22.zkr",
        digest!("1f18f495832955784bd0ae69ab7aeb60cad9b062bb8a9627a5de25fdda368e96"),
    ),
    (
        "lift_join7_rv32im_v2_23.zkr",
        digest!("51de52be1f48ee6e83c000dc4a49ad62ec7351d1d9368eecd2201e7d4777138a"),
    ),
    (
        "lift_join7_rv32im_v2_24.zkr",
        digest!("b6150edd77de2ca8493eb1727f3c6dc071e2052979fc1d7f7011c687dd29e2a7"),
    ),
    (
        "lift_join8_rv32im_v2_14.zkr",
        digest!("0c0804bf069d79bb3e36194780672288bc896891f41705ba091948f5f697ccc3"),
    ),
    (
        "lift_join8_rv32im_v2_15.zkr",
        digest!("663e2cff0e98b6acc3f91b9885dfbd53415af2ade6e3032f74147ba8d5e520ec"),
    ),
    (
        "lift_join8_rv32im_v2_16.zkr",
        digest!("6677e5d75c2ecc7c6edaea269a51c29900939e672538b7ebafca8ddbd7b5a57b"),
    ),
    (
        "lift_join8_rv32im_v2_17.zkr",
        digest!("b17e6bb09b44c6e9e05c881f94434ab4dae14228ba65a4b8bae4bb4f782c15ab"),
    ),
    (
        "lift_join8_rv32im_v2_18.zkr",
        digest!("315a34e87a599690d8305c264b25d44bf9d5cb3c3d51278935bcf2d9541efbad"),
    ),
    (
        "lift_join8_rv32im_v2_19.zkr",
        digest!("074761f0befce9480c42123907cb4ced59a4023621c553bb703adb7da159c3fd"),
    ),
    (
        "lift_join8_rv32im_v2_20.zkr",
        digest!("30abedb03b3db05c26fc8d2992f4c0f560b4b8fa4debe50447285a7f21e15006"),
    ),
    (
        "lift_join8_rv32im_v2_21.zkr",
        digest!("6195afa570435017b02950108545378f99ac90a9d45ee31bceb0f67406447be1"),
    ),
    (
        "lift_join8_rv32im_v2_22.zkr",
        digest!("ebf82d7917375ff92b31d5324b22b889e063413a29716adf5ead72d8ff929ed8"),
    ),
    (
        "lift_join8_rv32im_v2_23.zkr",
        digest!("dd06900fdb91830a19cf43eb7784f62bd27f178865eff5c932280ea341ad3feb"),
    ),
    (
        "lift_join8_rv32im_v2_24.zkr",
        digest!("6e4455e649c62f24652e69d9d06a020c7e7e969450cbff8cd017ea91100a55a2"),
    ),
    (
        "lift_join9_rv32im_v2_14.zkr",
        digest!("c9c908961226358c652242f0bdb11582e1f2834c7637918b8262c3e6f1067a02"),
    ),
    (
        "lift_join9_rv32im_v2_15.zkr",
        digest!("e7864cb3df6985800b5523d33d6526b1a3b1aa0ba808e9d35e46ca7df6c9f509"),
    ),
    (
        "lift_join9_rv32im_v2_16.zkr",
        digest!("c7eef815cc190a8d2335beaf40773448c65891647ff5a7055c96f8b61eee87b6"),
    ),
    (
        "lift_join9_rv32im_v2_17.zkr",
        digest!("84b583f8a5bfe3bada6f7bf02c2e27990736bf79ce22df2894268daff7c019f5"),
    ),
    (
        "lift_join9_rv32im_v2_18.zkr",
        digest!("d96a4aef81ff0de596b06b10c44a43b4a773100d97e40e2abf71e6c95c31cd9c"),
    ),
    (
        "lift_join9_rv32im_v2_19.zkr",
        digest!("b0ad878d47ec722fead5eec26fb40896bd3ee4afff3a31cdbfe55a0f02223011"),
    ),
    (
        "lift_join9_rv32im_v2_20.zkr",
        digest!("b91d20145a59c5d0fc3ea47170867537b5db4d7d50395377aa42aba47c03f15f"),
    ),
    (
        "lift_join9_rv32im_v2_21.zkr",
        digest!("0b6d144f6b3790a1358834c0536112b3c3994701812e6f5e3ef68b1ce82a7bd1"),
    ),
    (
        "lift_join9_rv32im_v2_22.zkr",
        digest!("d6bbb95eba94ecc339b4c79b8d73d9186b63de9ebdba5436d278ef9c4de2b761"),
    ),
    (
        "lift_join9_rv32im_v2_23.zkr",
        digest!("2e185ecf5b369460b910bcf27db885c24b49e3d3990f3665877f583bae357f06"),
    ),
    (
        "lift_join9_rv32im_v2_24.zkr",
        digest!("8031b0bd6ffca234a8a9dba1650417e93732cc67f9da689a0a317f20bd173dbc"),
    ),
    (
        "lift_join_rv32im_v2_14.zkr",
        digest!("c64bd6c9ff8edfd9fc2bf2b411b2aa0df90a70b32a0c8162b6f6b152c12e1091"),
    ),
    (
        "lift_join_rv32im_v2_15.zkr",
        digest!("0a415b59bd224c45473938d622d8299266a6cb53f220d3aa0a1c27eed8bca65e"),
    ),
    (
        "lift_join_rv32im_v2_16.zkr",
        digest!("e4f3af5b4f7c5ddfad270a3fd701bb6f7a0efb62788f944e8e9c53e5d2a97256"),
    ),
    (
        "lift_join_rv32im_v2_17.zkr",
        digest!("3bda20197abe455cde4e975b93e092c6d6c4f1202498efa144a6441aec045a33"),
    ),
    (
        "lift_join_rv32im_v2_18.zkr",
        digest!("83b0a30719bc9d807ee27dc1df497f5374b72c255dadfc748b807886174c4974"),
    ),
    (
        "lift_join_rv32im_v2_19.zkr",
        digest!("2da088f57e4383a04ecd1092a509b3d8600d6f4b4d4c3b9a09a2505b8f89f3cc"),
    ),
    (
        "lift_join_rv32im_v2_20.zkr",
        digest!("05263f2d60ac280ac25b91a455815d435828e2e69c0b341d9d5cb70a5452f1b1"),
    ),
    (
        "lift_join_rv32im_v2_21.zkr",
        digest!("576c0cf918235e283001b616e636e85ab52eadfb3130a2c4ed4627faa6db0ee6"),
    ),
    (
        "lift_join_rv32im_v2_22.zkr",
        digest!("09db134ea03d536bc0d3983f5eac09f448a8e14116c767e3819636a26a95a185"),
    ),
    (
        "lift_join_rv32im_v2_23.zkr",
        digest!("add9192a404bb8a63e3e576d7b1a7a501ed21273f88adc9962ce2eb4edeec774"),
    ),
    (
        "lift_join_rv32im_v2_24.zkr",
        digest!("22cfcc236118f1a96a59b81495bb99b1aeaa6dd3f294d83a2830f2789e41bc84"),
    ),
    (
        "lift_rv32im_v2_14.zkr",
        digest!("871d6e417472fc94a463cc9290313da3d70e6b17683f328f265e98d64a4963ef"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("0c812a92e36a5009e5ba39a40050ef2e3206f819497052bb62da1155be757068"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("92f3c9ee2e5e1a23d90a0e7dd52bf7b9b4f1e272613ac76e5bf6e932fa8de0ec"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("4d9c713b2dfa00271b9d4a87ef4244974a85bbb20b493cd103d75b4fcc60d411"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("7054dde82886b4a8955539872ff4784973a61782ec71348a405564a21ae3f630"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("c4abec2567fbd603ce616ecd27923f45b601d5f86cc48d1f1fb3091615afb6fd"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("1263bd3dcecab89069b91de5c4c99bdc33f853b00b50e1f35e4ffa392badd7a4"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("7380d1f06f8fb3dc3f9c7d278071fbc3bf30073229c6885d1a41c6528e90e4c7"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("793cbfc8de47a9beeb2221cac0d06470fc87e26771330561369fb518cc3b1b05"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("7bc461a9ff258b32178124b8c8f78cadac35db313b57f62d51958ec9ec37fb71"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("dc295096d9db9166e06e424445563cc4bec8fdb1a69e3b2fcee1bba75fa85883"),
    ),
    (
        "resolve.zkr",
        digest!("ecc34946284eb02d1e119ef0878ae65ba5e855d6e0b5db4e462a694007b2a0f4"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("f76f9b9d05ad0576c5d15dacd003c41d101f015482a79ae6aa65c9d52b4a9148"),
    ),
    (
        "union.zkr",
        digest!("44bfa51c5030508d7eddc1b1489145a6e519842f7283098a17f13fe9113497dc"),
    ),
];
