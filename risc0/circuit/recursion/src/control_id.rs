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
    digest!("a681c3606ce2056a11db411f92591859d4813317383d4f1fa166e91bc8fe5648"), // recursion identity.zkr
    digest!("be90046f2f27635c10f4b440c21cec1ab9be7c0ceedbcb771be8e62a47b6ef4a"), // recursion join.zkr
    digest!("7b3c9443ee71c5319e3a85667da1d34584bf7a5de3a71e409c87681d37f0b670"), // recursion join_povw.zkr
    digest!("38e835163b7a1d2980ba686e13021c16adffa71af7533f46edfc7a634d78c21a"), // recursion join_unwrap_povw.zkr
    digest!("9e9f8e566a45f36125dc976bd667261b7a9b7437a8f92149c423e263c53e6e6c"), // recursion lift_rv32im_v2_14.zkr
    digest!("0ade565f320cba2d0b23003a6323424d3f3d3609bcdcca4c14ab492b15cae153"), // recursion lift_rv32im_v2_15.zkr
    digest!("e1eba31fb23ce750e7f48433bec5d236ec0bf610a4ef876323be7a02b7b6f34a"), // recursion lift_rv32im_v2_16.zkr
    digest!("e29185730ab1be06964c0a5fe6c45d2d3b86ab5dcdfd65035bcf7922fed00040"), // recursion lift_rv32im_v2_17.zkr
    digest!("1b29d55d9d29fd0aa2aa510ef35e020b93513916ab11ae7423ab6f07f57b2630"), // recursion lift_rv32im_v2_18.zkr
    digest!("74705674d091c55c1fb5f4698dd7475ab60ec610518e15511e2e124817ce0d48"), // recursion lift_rv32im_v2_19.zkr
    digest!("aed42e431dbb0b18a0950638501e8e3b8553017440d1c7257f9d5a204f06a975"), // recursion lift_rv32im_v2_20.zkr
    digest!("3e57713187cf563ce07d0504f781b03b2c28a51eba3f2e17f97883653d28cf29"), // recursion lift_rv32im_v2_21.zkr
    digest!("e4e02930127ab85a4951403fbf2ad67401d3012255088939d85dd2175ff76f13"), // recursion lift_rv32im_v2_22.zkr
    digest!("113bb23e3a9ba6593c1c13161a9b5919cbf50d57ac3e517072b480108a48ac5a"), // recursion lift_rv32im_v2_povw_14.zkr
    digest!("f0ae31592076861ad3d8940846200114570f4534a2aedc3047ed3937beb81d3b"), // recursion lift_rv32im_v2_povw_15.zkr
    digest!("8d034b0d27bd225191ed695711c82a2364d6cf0fc87838669f18316c4cc5b832"), // recursion lift_rv32im_v2_povw_16.zkr
    digest!("fb0e0841e880bb36996a713f4243be1eb820e71874f9161bcfab8d44b406316f"), // recursion lift_rv32im_v2_povw_17.zkr
    digest!("da914504ada7d014f79eea621dba4c22d202140c8116dd4e051a452ad9e1eb55"), // recursion lift_rv32im_v2_povw_18.zkr
    digest!("b16cdc2d234451707fba0c51fc698b11ab27aa52400ade435074f42bacd7682e"), // recursion lift_rv32im_v2_povw_19.zkr
    digest!("c68e380eefbc0633a61cbd0274624324c3528672e9476f2c0426021862f12d76"), // recursion lift_rv32im_v2_povw_20.zkr
    digest!("46e47b41200a0c2c5825f021f3241519a8f32404a44df3472b69d6588b210a50"), // recursion lift_rv32im_v2_povw_21.zkr
    digest!("a9a2032f7791b6015d813e2db22bee34d1a7541ac2a8371e37a8a207ab08144f"), // recursion lift_rv32im_v2_povw_22.zkr
    digest!("f8d1a9137a554402c2d05f3508c41642dde583520e481319042a4655695f8a51"), // recursion resolve.zkr
    digest!("bace71573d8ede518baea63d8abcc20e75e35067f01daa45b675260464f38506"), // recursion resolve_povw.zkr
    digest!("2e4c4b5553ce1f454c03734c72a5f7180361cc17b49ab426c2c3a005b8dad709"), // recursion resolve_unwrap_povw.zkr
    digest!("dd82c51235f2d871e1c95174ab99b96124fc8621d6e4666e58a4676385d1674e"), // recursion union.zkr
    digest!("42bd680f1fd01b54cd9b12030c2b393a195fbb03b06b8b09c73ed84f663f4043"), // recursion unwrap_povw.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("e6feef13db7aed4a731c7b0852de1f5c89b137726073f625d05333184d3a551d");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("de81d091ba14062acb5023b3b36deee95624e3fd47475cb7ff64aed5f9eac20a");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 32] = [
    (
        "identity.zkr",
        digest!("a681c3606ce2056a11db411f92591859d4813317383d4f1fa166e91bc8fe5648"),
    ),
    (
        "join.zkr",
        digest!("be90046f2f27635c10f4b440c21cec1ab9be7c0ceedbcb771be8e62a47b6ef4a"),
    ),
    (
        "join_povw.zkr",
        digest!("7b3c9443ee71c5319e3a85667da1d34584bf7a5de3a71e409c87681d37f0b670"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("38e835163b7a1d2980ba686e13021c16adffa71af7533f46edfc7a634d78c21a"),
    ),
    (
        "lift_rv32im_v2_14.zkr",
        digest!("9e9f8e566a45f36125dc976bd667261b7a9b7437a8f92149c423e263c53e6e6c"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("0ade565f320cba2d0b23003a6323424d3f3d3609bcdcca4c14ab492b15cae153"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("e1eba31fb23ce750e7f48433bec5d236ec0bf610a4ef876323be7a02b7b6f34a"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("e29185730ab1be06964c0a5fe6c45d2d3b86ab5dcdfd65035bcf7922fed00040"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("1b29d55d9d29fd0aa2aa510ef35e020b93513916ab11ae7423ab6f07f57b2630"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("74705674d091c55c1fb5f4698dd7475ab60ec610518e15511e2e124817ce0d48"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("aed42e431dbb0b18a0950638501e8e3b8553017440d1c7257f9d5a204f06a975"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("3e57713187cf563ce07d0504f781b03b2c28a51eba3f2e17f97883653d28cf29"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("e4e02930127ab85a4951403fbf2ad67401d3012255088939d85dd2175ff76f13"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("b82a145643a1d22a79d0de679157405e389c8b410e5cea319f37941785eb1d36"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("69d3ed45f0eb2e5b0ea083353e1aaa311121cc203fd20c237c505f5a7d8cf061"),
    ),
    (
        "lift_rv32im_v2_povw_14.zkr",
        digest!("113bb23e3a9ba6593c1c13161a9b5919cbf50d57ac3e517072b480108a48ac5a"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("f0ae31592076861ad3d8940846200114570f4534a2aedc3047ed3937beb81d3b"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("8d034b0d27bd225191ed695711c82a2364d6cf0fc87838669f18316c4cc5b832"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("fb0e0841e880bb36996a713f4243be1eb820e71874f9161bcfab8d44b406316f"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("da914504ada7d014f79eea621dba4c22d202140c8116dd4e051a452ad9e1eb55"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("b16cdc2d234451707fba0c51fc698b11ab27aa52400ade435074f42bacd7682e"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("c68e380eefbc0633a61cbd0274624324c3528672e9476f2c0426021862f12d76"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("46e47b41200a0c2c5825f021f3241519a8f32404a44df3472b69d6588b210a50"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("a9a2032f7791b6015d813e2db22bee34d1a7541ac2a8371e37a8a207ab08144f"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("e26cb82479d95930bff62d6f917045236458cd69020ebf61e6b0892caa1c2105"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("f616ac0379d68d77db8c6f401156f51ab53441582fd2da4b9a1b4f53c536846b"),
    ),
    (
        "resolve.zkr",
        digest!("f8d1a9137a554402c2d05f3508c41642dde583520e481319042a4655695f8a51"),
    ),
    (
        "resolve_povw.zkr",
        digest!("bace71573d8ede518baea63d8abcc20e75e35067f01daa45b675260464f38506"),
    ),
    (
        "resolve_unwrap_povw.zkr",
        digest!("2e4c4b5553ce1f454c03734c72a5f7180361cc17b49ab426c2c3a005b8dad709"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("6d55102aa73086602f7039412200124bdec91f0c497c606f9aa09040403e030b"),
    ),
    (
        "union.zkr",
        digest!("dd82c51235f2d871e1c95174ab99b96124fc8621d6e4666e58a4676385d1674e"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("42bd680f1fd01b54cd9b12030c2b393a195fbb03b06b8b09c73ed84f663f4043"),
    ),
];

/// Control IDs for included recursion programs (ZKRs), using SHA-256.
pub const SHA256_CONTROL_IDS: [(&str, Digest); 32] = [
    (
        "identity.zkr",
        digest!("ed79a47144cc26a5a0c7b6fda9992471643a5aa14f04ded304b3456b7f282a0f"),
    ),
    (
        "join.zkr",
        digest!("34440f0ed57b6d90d3a25d3528eb424fb655319c91df364687234880b4c773b7"),
    ),
    (
        "join_povw.zkr",
        digest!("3c74870ec4352fbe085debb68c5fff40a42d8cb5c4b63bc59e09835d0a2b60a9"),
    ),
    (
        "join_unwrap_povw.zkr",
        digest!("7e147c2daac687fd1725897347baced9efb1b44602cccd7c7d5bcfe9b089dfba"),
    ),
    (
        "lift_rv32im_v2_14.zkr",
        digest!("463943d1c69cc903078826fe1e66d8d33e5d1ae609d4674862387bbd7a29469f"),
    ),
    (
        "lift_rv32im_v2_15.zkr",
        digest!("4506acc5b9cc9c69a1cbc668fe3dd3709fce3d98552f5d26a6de6d1e5e50d762"),
    ),
    (
        "lift_rv32im_v2_16.zkr",
        digest!("061b658a1d10645b4b361313c5c6a180b4af7eaa199ee704f28515ec89a8e948"),
    ),
    (
        "lift_rv32im_v2_17.zkr",
        digest!("e454eaf5bed6eb3ce95d7dcbf5bcf9cfaca73c803e9fe479a12b63722ddbd3bd"),
    ),
    (
        "lift_rv32im_v2_18.zkr",
        digest!("1d0dec46fd10979f5cfb78c65f31118a1f4eb21bb2b9b830b38094b16c8a5e71"),
    ),
    (
        "lift_rv32im_v2_19.zkr",
        digest!("c13a37932dabcae5a46c14f6f1521e0b78e7e8ea8a2aaa94af56f6add370936b"),
    ),
    (
        "lift_rv32im_v2_20.zkr",
        digest!("dcda775fad66f33ea1d1d45746db6c3b2ea83aaa639fe4bd8d69690887573716"),
    ),
    (
        "lift_rv32im_v2_21.zkr",
        digest!("21552f647821c3f6203c4a486a913994964b3234a5bfea881b7d84d37053008f"),
    ),
    (
        "lift_rv32im_v2_22.zkr",
        digest!("86c907ecdd22764bd6427246e858b4d1fb5d1bdb31dbfaed6909939f0fdeadc9"),
    ),
    (
        "lift_rv32im_v2_23.zkr",
        digest!("f2ee3d49bc9bc2d65d662e36cc8901ac416b068325ff55b4117cc503225c593e"),
    ),
    (
        "lift_rv32im_v2_24.zkr",
        digest!("8928def1e7891c38f2247cff5b16703acd542c5e2ac8bda63cf2fe3768f93016"),
    ),
    (
        "lift_rv32im_v2_povw_14.zkr",
        digest!("3e20c48ec4ea60462d53393b1cf3cb5f3205746d1795eda440c9c08e1a93af01"),
    ),
    (
        "lift_rv32im_v2_povw_15.zkr",
        digest!("68d86986f434ae1c4f57460805ecd7c65ce654845aa89add9e1059ba3a89673e"),
    ),
    (
        "lift_rv32im_v2_povw_16.zkr",
        digest!("d35c57690da0f25d174a8dc5da5b9e6ce54bb3aa305c28ac67943dec24819b0f"),
    ),
    (
        "lift_rv32im_v2_povw_17.zkr",
        digest!("b85919b52d28c81cf6c22a736080cbd72370370bd01b3257cb46cad74412ea4b"),
    ),
    (
        "lift_rv32im_v2_povw_18.zkr",
        digest!("cc55f5abb05241e5de10f277f3a989c5fe91622d121c2947b61ce81ae2c441c4"),
    ),
    (
        "lift_rv32im_v2_povw_19.zkr",
        digest!("b6bb27c545aaa5a20003af7ad74dbc8a95f38c07a5c47ebeea89ed229fe52e09"),
    ),
    (
        "lift_rv32im_v2_povw_20.zkr",
        digest!("e5ea43f3a698c863477ecf0baf4c6cd95e7f5afa173b9b6341c483a5c190906f"),
    ),
    (
        "lift_rv32im_v2_povw_21.zkr",
        digest!("42ab8fd19156c749a34c42f829a5c9b435f684204500eaaeb0027aa65658f496"),
    ),
    (
        "lift_rv32im_v2_povw_22.zkr",
        digest!("41702b3149bc1aec5f04138c7027440b8129c7b69b7f42a64248700a069e2d6d"),
    ),
    (
        "lift_rv32im_v2_povw_23.zkr",
        digest!("a120a69668358efcd550200d63c32fdff082816d33adb72933479d1b8b972e94"),
    ),
    (
        "lift_rv32im_v2_povw_24.zkr",
        digest!("91b04b89cd6b7fbdc755cb2161faa86276e6f3e94f10c3ea814a3834f16e2490"),
    ),
    (
        "resolve.zkr",
        digest!("9789b9b7cf8bbcb01f80c172b1c80c5f71d8250a11403c1e6d697c24be76fa89"),
    ),
    (
        "resolve_povw.zkr",
        digest!("d7eaa0de32bdedc32aa305c96511ff0a29a34e2ca7d8bd82837d99ca65aa188c"),
    ),
    (
        "resolve_unwrap_povw.zkr",
        digest!("8480835d6d92db608d34a1e5974a1e171ae4b89a745cdd2134251c9eb4bf0364"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("3c7b9195e051f01d9dc21d96a1dd26c7035bc225511a715cf8c7ba83f8df7687"),
    ),
    (
        "union.zkr",
        digest!("b1f99b50bd2ec62dc297d400e36ae0641bce3e161d97261887b0d87e5c2015f3"),
    ),
    (
        "unwrap_povw.zkr",
        digest!("d57e411156fe24e5fc500d6a327107d52f3f6b935c26e454366037214a85836b"),
    ),
];
