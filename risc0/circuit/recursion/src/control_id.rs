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
    digest!("55ba2d763ec3c016c0f97c298507115c77e0a25215e5771ba501d016edca522c"),
    digest!("c265954c4dcb2155e041286a246bfe400ba9d042d919aa3cb1a299651f84c13e"),
    digest!("467cd61da86f37347b45e64b5d4665308871bc301c67ba6c6d13c9470c3e4840"),
    digest!("57b2031d3881e92b85d73d2d0800a223fdaccd5e7bdd0a569c10556ec138f551"),
    digest!("c1f19103f8376c00fe20f62aa4370f628efe3a4a5eb1a5739466c944cf7dfe31"),
    digest!("548ec1774c6c833b18db2e2a1464cb1923c6c721df87b437509ba87292d20529"),
    digest!("ce535b3b10e4cc212842b90a918553633c4f5375dee51d4788798765df5a8750"),
    digest!("7dea3854a91c906f92f23a291340066ecbd5375669fe752a5047c926e4d56747"),
    digest!("dca31f53c5bf4c67ecdc9f1035cf5934072afc29573a1845100d6140befab657"),
    digest!("12da4520930b1740810a69428c02fb2fcb586763a0e3794c45196608b594dd69"),
    digest!("5c2dce7226ff9073b8e38919583c01375f11395111e9ae3bfd519b57f84a5e00"),
    digest!("22eb7f24b795b8620919ac47235a001f15cfa31751f0a421e415d01e0f506b08"),
    digest!("ba3c4924aa2ddc6d78d3145dd03f9160bb5ce96f36fdab69730b7107ad34ea0a"),
    digest!("9cb73d556e58680259fae4568ee632684ef3a51f6465a81169f58f1c404a6816"),
    digest!("8e87f53b61b2d122003e6874c3c3bd01846b1959f860a85cc21be96f914e3040"),
    digest!("37d2fd2dda22fc35516a0c03e94d630840dfbc181494314547f12e5ee429984f"),
    digest!("9b11ae0692158a2e0483a71a10bf3a4b12a2f5486331823957230658e1ddb659"),
    digest!("ae4920680246642419bdb313b5ac753ae537d9286b38a53f9e842758baf64134"),
    digest!("3e52d65a4b1e4412f48fd06765e03d0baf81232a1959164331c538019c7b3e60"),
    digest!("848bc0511669bb2896b13462de79ee3a202d143e8a00b5093d6f7a2a60fac66d"),
    digest!("c0ef1413caa9e652c368602268fa22067a7989128f043838e6b96a483d706866"),
    digest!("bd680715f4b5f96fce403e387674b355763c8957552d21547352515eae90d930"),
    digest!("6d888660a8fd513d96af1c245eb8354e13423416ea8f4658f85092561b816a6c"),
    digest!("a0ce1a36fa38451527ec78663687c9560b0f947440da571f6f216641a35f7342"),
    digest!("617d277564bc3d4e2f572474302cb43974336b4c4c4f7e4df84a395fa5fa5c50"),
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("a516a057c9fbf5629106300934d48e0e775d4230e41e503347cad96fcbde7e2e");

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
