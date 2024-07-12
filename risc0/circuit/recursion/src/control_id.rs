// Copyright 2024 RISC Zero, Inc.
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

/// Control IDs allowed in the default set of recursion programs. Includes control IDs for the base
/// set of recursion programs, and each power-of-two of the rv32im circuit, using Poseidon2.
pub const ALLOWED_CONTROL_IDS: &[Digest] = &[
    digest!("30dae603fcd283331d01105ea129ce43a0957a59b4f0013359a5642dfda0ba26"), // rv32im po2=13
    digest!("2afea6024b79430b49f60518f27d7262f2ec5b1306a9030cc2e4d955e5dc5964"), // rv32im po2=14
    digest!("8dc2760e1e24082cb66c83470c24a8017e95ce4d5eab170522f783418d545e72"), // rv32im po2=15
    digest!("35feaa4eebbefd45b0a36a350671c82154f90c660389ed3a8ff7bd2a30805973"), // rv32im po2=16
    digest!("7436486fdf9a7d3a3f8a03263bc7541a3c173c2ab5d2eb2c53939d0243dc0d16"), // rv32im po2=17
    digest!("3abdc115ddf6af1977863c29c0f2b91f8c0c2a1c35e82158104b651f6a07a816"), // rv32im po2=18
    digest!("17d75c070f373f333bbbaf33a688bb74fc05670435cd5d6378d37b608448e300"), // rv32im po2=19
    digest!("f3cf1217485c403cea526b1e52e70835c31bdc6e3016ee12916f6c6561fc0977"), // rv32im po2=20
    digest!("4043ce1426811d4f0e6a9c27256d052513c95739e9b80c74f628f313c739b75c"), // rv32im po2=21
    digest!("b4edfc3f2c49f10285bcdc7493eb81063959820a59569356fb73b62c1586e01f"), // rv32im po2=22
    digest!("cc1bd6753bb8fd41d41bba14bb56e90ffa9ddf4f20f7727734d140675a9cc52b"), // rv32im po2=23
    digest!("22eb7f24b795b8620919ac47235a001f15cfa31751f0a421e415d01e0f506b08"), // recursion identity.zkr
    digest!("ba3c4924aa2ddc6d78d3145dd03f9160bb5ce96f36fdab69730b7107ad34ea0a"), // recursion join.zkr
    digest!("9cb73d556e58680259fae4568ee632684ef3a51f6465a81169f58f1c404a6816"), // recursion lift_14.zkr
    digest!("8e87f53b61b2d122003e6874c3c3bd01846b1959f860a85cc21be96f914e3040"), // recursion lift_15.zkr
    digest!("37d2fd2dda22fc35516a0c03e94d630840dfbc181494314547f12e5ee429984f"), // recursion lift_16.zkr
    digest!("9b11ae0692158a2e0483a71a10bf3a4b12a2f5486331823957230658e1ddb659"), // recursion lift_17.zkr
    digest!("ae4920680246642419bdb313b5ac753ae537d9286b38a53f9e842758baf64134"), // recursion lift_18.zkr
    digest!("3e52d65a4b1e4412f48fd06765e03d0baf81232a1959164331c538019c7b3e60"), // recursion lift_19.zkr
    digest!("848bc0511669bb2896b13462de79ee3a202d143e8a00b5093d6f7a2a60fac66d"), // recursion lift_20.zkr
    digest!("c0ef1413caa9e652c368602268fa22067a7989128f043838e6b96a483d706866"), // recursion lift_21.zkr
    digest!("bd680715f4b5f96fce403e387674b355763c8957552d21547352515eae90d930"), // recursion lift_22.zkr
    digest!("6d888660a8fd513d96af1c245eb8354e13423416ea8f4658f85092561b816a6c"), // recursion lift_23.zkr
    digest!("a0ce1a36fa38451527ec78663687c9560b0f947440da571f6f216641a35f7342"), // recursion lift_24.zkr
    digest!("617d277564bc3d4e2f572474302cb43974336b4c4c4f7e4df84a395fa5fa5c50"), // recursion resolve.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("c43de805675563551857de3ee487c5167a26141467196700f43eb51f9c0ef505");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("51b54a62f2aa599aef768744c95de8c7d89bf716e11b1179f05d6cf0bcfeb60e");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 15] = [
    (
        "identity.zkr",
        digest!("22eb7f24b795b8620919ac47235a001f15cfa31751f0a421e415d01e0f506b08"),
    ),
    (
        "join.zkr",
        digest!("ba3c4924aa2ddc6d78d3145dd03f9160bb5ce96f36fdab69730b7107ad34ea0a"),
    ),
    (
        "lift_14.zkr",
        digest!("9cb73d556e58680259fae4568ee632684ef3a51f6465a81169f58f1c404a6816"),
    ),
    (
        "lift_15.zkr",
        digest!("8e87f53b61b2d122003e6874c3c3bd01846b1959f860a85cc21be96f914e3040"),
    ),
    (
        "lift_16.zkr",
        digest!("37d2fd2dda22fc35516a0c03e94d630840dfbc181494314547f12e5ee429984f"),
    ),
    (
        "lift_17.zkr",
        digest!("9b11ae0692158a2e0483a71a10bf3a4b12a2f5486331823957230658e1ddb659"),
    ),
    (
        "lift_18.zkr",
        digest!("ae4920680246642419bdb313b5ac753ae537d9286b38a53f9e842758baf64134"),
    ),
    (
        "lift_19.zkr",
        digest!("3e52d65a4b1e4412f48fd06765e03d0baf81232a1959164331c538019c7b3e60"),
    ),
    (
        "lift_20.zkr",
        digest!("848bc0511669bb2896b13462de79ee3a202d143e8a00b5093d6f7a2a60fac66d"),
    ),
    (
        "lift_21.zkr",
        digest!("c0ef1413caa9e652c368602268fa22067a7989128f043838e6b96a483d706866"),
    ),
    (
        "lift_22.zkr",
        digest!("bd680715f4b5f96fce403e387674b355763c8957552d21547352515eae90d930"),
    ),
    (
        "lift_23.zkr",
        digest!("6d888660a8fd513d96af1c245eb8354e13423416ea8f4658f85092561b816a6c"),
    ),
    (
        "lift_24.zkr",
        digest!("a0ce1a36fa38451527ec78663687c9560b0f947440da571f6f216641a35f7342"),
    ),
    (
        "resolve.zkr",
        digest!("617d277564bc3d4e2f572474302cb43974336b4c4c4f7e4df84a395fa5fa5c50"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("6d55102aa73086602f7039412200124bdec91f0c497c606f9aa09040403e030b"),
    ),
];

/// Control IDs for included recursion programs (ZKRs), using SHA-256.
pub const SHA256_CONTROL_IDS: [(&str, Digest); 15] = [
    (
        "identity.zkr",
        digest!("9e1024be2b9eb84c73dd6056356dcacefec966ff22b7b57e31a7e4898976f334"),
    ),
    (
        "join.zkr",
        digest!("e484163ed7adbca77663ad90875bb1202b9824f60fd679a40f526ec40d29ad63"),
    ),
    (
        "lift_14.zkr",
        digest!("323e606ab939c9624ee68797baccc7cfb35ff038a9de92d472f7af1ac0010bb7"),
    ),
    (
        "lift_15.zkr",
        digest!("4042e290d7bc04108a63a8ab708465498c6fa9e9e964be9a7cf7d204ed3d6584"),
    ),
    (
        "lift_16.zkr",
        digest!("e9e2b8ab466fdd6673fa0c0d4e7340f0c1de4cf2c5d1c4bb3e720e75081ec8ba"),
    ),
    (
        "lift_17.zkr",
        digest!("18dc4cb56161bf3cba428fb8e70ad1a0e61e74738f136ac7bc7f0aa2302548f7"),
    ),
    (
        "lift_18.zkr",
        digest!("159776a2f540d9ab52d9b7a1dbd3041cafa80750d4266149e354453556d19e1b"),
    ),
    (
        "lift_19.zkr",
        digest!("42301f20318c3e30e9d848504e781551eec600b2d6a85468116ee42443374afd"),
    ),
    (
        "lift_20.zkr",
        digest!("00463a1fc1c55592ce35167e91010a78dedc807d15dbb426a3a4d69b6fc62bc4"),
    ),
    (
        "lift_21.zkr",
        digest!("86a1db1a49d5d7d511f2871b4e284df2139d030802b585248a6bc378fde8422b"),
    ),
    (
        "lift_22.zkr",
        digest!("a01053d59587f2b725c8e8242b04f4b3029b72a09eea1e3525052f9313a30743"),
    ),
    (
        "lift_23.zkr",
        digest!("6cd01079f927b6cf64fbc95b2204a659d35ce59b74a2439b0e5adab86e7a61b7"),
    ),
    (
        "lift_24.zkr",
        digest!("efafeab6272b96a559bec2c74fa6dda4d32cbdabe2d0a58da532c0a81ab4e3bb"),
    ),
    (
        "resolve.zkr",
        digest!("2abc94ad282abb14f88b843463be087f894ede12a327d831c3573941ea9b2ae5"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("3c7b9195e051f01d9dc21d96a1dd26c7035bc225511a715cf8c7ba83f8df7687"),
    ),
];
