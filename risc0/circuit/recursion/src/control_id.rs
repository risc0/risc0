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

/// Smallest cycle limit, as a power of two (po2), supported as a lift program.
pub const MIN_LIFT_PO2: usize = 14;

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
    digest!("0e51536ec08ac01e42de3d2a0b2a552d8ff2c75e4ef2b5285eed23582a13ef5d"), // recursion identity.zkr
    digest!("d7b56f6ef29d18203ac26960eb21160d60da6f1975124261fbe38d1364fa0e6b"), // recursion join.zkr
    digest!("7773ab2d4b30ca25cc34b767c1f8705cc36c6a402cc332625c0dc46a4005860f"), // recursion lift_14.zkr
    digest!("70aba662f2e14c2bacbe15238a579477f63bcf39a7d8084304b0133cddd0a360"), // recursion lift_15.zkr
    digest!("01bda36ae05c6d01e7b7456ba6c0a874dd9ca42cd4b8ee4a828f553e2447e00f"), // recursion lift_16.zkr
    digest!("f8b22905ba96ed5887cd3b3145d5030783decc28af5efe26522c2174022a7226"), // recursion lift_17.zkr
    digest!("fdd2f13930df963ede66f1386622311c1b9d4b2a0e7e3e6edfe4cb4d85da9f23"), // recursion lift_18.zkr
    digest!("e1df1b0b388dff616883f819fef0976e608cc910e42da842ec84f309f37f4f6a"), // recursion lift_19.zkr
    digest!("37046137bc9927551ba7ec5426e832117e481c5bb15d8f07fc22391143a68500"), // recursion lift_20.zkr
    digest!("e26e5b6dee02511cfd5d59539c1ce319e44c66088396a7634630a224e2a19d1a"), // recursion lift_21.zkr
    digest!("18386311e4b86b527f3d966de55df3271f7e52209c037b607a41a62c8b4c9f61"), // recursion resolve.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("00f3523b8f755871cfcbf6320424232f2a73bf30ac530771ee993c49e83c5733");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("4e160df1e119ac0e3d658755a9edf38c8feb307b34bc10b57f4538dbe122a005");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 15] = [
    (
        "identity.zkr",
        digest!("0e51536ec08ac01e42de3d2a0b2a552d8ff2c75e4ef2b5285eed23582a13ef5d"),
    ),
    (
        "join.zkr",
        digest!("d7b56f6ef29d18203ac26960eb21160d60da6f1975124261fbe38d1364fa0e6b"),
    ),
    (
        "lift_14.zkr",
        digest!("7773ab2d4b30ca25cc34b767c1f8705cc36c6a402cc332625c0dc46a4005860f"),
    ),
    (
        "lift_15.zkr",
        digest!("70aba662f2e14c2bacbe15238a579477f63bcf39a7d8084304b0133cddd0a360"),
    ),
    (
        "lift_16.zkr",
        digest!("01bda36ae05c6d01e7b7456ba6c0a874dd9ca42cd4b8ee4a828f553e2447e00f"),
    ),
    (
        "lift_17.zkr",
        digest!("f8b22905ba96ed5887cd3b3145d5030783decc28af5efe26522c2174022a7226"),
    ),
    (
        "lift_18.zkr",
        digest!("fdd2f13930df963ede66f1386622311c1b9d4b2a0e7e3e6edfe4cb4d85da9f23"),
    ),
    (
        "lift_19.zkr",
        digest!("e1df1b0b388dff616883f819fef0976e608cc910e42da842ec84f309f37f4f6a"),
    ),
    (
        "lift_20.zkr",
        digest!("37046137bc9927551ba7ec5426e832117e481c5bb15d8f07fc22391143a68500"),
    ),
    (
        "lift_21.zkr",
        digest!("e26e5b6dee02511cfd5d59539c1ce319e44c66088396a7634630a224e2a19d1a"),
    ),
    (
        "lift_22.zkr",
        digest!("44f6a149c16f43395a0f48280f3f4951d8e9190e5283664900a90e23b035c926"),
    ),
    (
        "lift_23.zkr",
        digest!("4b9be03eef41791dbed89a3ce6c89510c3af68703104ae1188557964b3e31f41"),
    ),
    (
        "lift_24.zkr",
        digest!("990aed351db0e70650f1530e9581e6572f11ca3144dbe147e6b98031cecd8760"),
    ),
    (
        "resolve.zkr",
        digest!("18386311e4b86b527f3d966de55df3271f7e52209c037b607a41a62c8b4c9f61"),
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
        digest!("837e1f68eed165e971fed56ed1d67d6a3d2ccf47bae684f2c48f3f5fd8a012a4"),
    ),
    (
        "join.zkr",
        digest!("3f05e906f54f94f11681350590b7b232af6b2686f57e24c4f1d8fce5ee6e6e08"),
    ),
    (
        "lift_14.zkr",
        digest!("a634212fc2f318afbcffcc023e340e070eea7b0c03a0297ad172501115055c2b"),
    ),
    (
        "lift_15.zkr",
        digest!("b63667e4675c3b612dfd637a97ea4a46c63a4ddb2d20eb6380daae9c5293bb7d"),
    ),
    (
        "lift_16.zkr",
        digest!("08eb6fccfea07bf35a7b27794f9f21f145a855ffcf8804e35529c3a0a6bf2791"),
    ),
    (
        "lift_17.zkr",
        digest!("01dbd8955bb105e87c02aa499bd9a52aafaaa1ba83df21ae9b76059dcb651b56"),
    ),
    (
        "lift_18.zkr",
        digest!("2d688d2abed0c71320d68dd8d6fca27fd1f81f537e2019f023accdbda815790d"),
    ),
    (
        "lift_19.zkr",
        digest!("9d1aa819960a2351728fe8617a87cd119cfec71ef4d14e000a8df69700c29344"),
    ),
    (
        "lift_20.zkr",
        digest!("c99a923325c50ea25bb3354a2caf11b3e7bab8249de3c3c9f3395a406e07d1b7"),
    ),
    (
        "lift_21.zkr",
        digest!("a049ba76c0849eecd50d2056c8a2dd5190df0026154df298cb706ae401376f56"),
    ),
    (
        "lift_22.zkr",
        digest!("e906d4aea74db6f027889df140608296c179b1de4e8f288324d4fe2618a999de"),
    ),
    (
        "lift_23.zkr",
        digest!("a85682973202e6b77d997c4904d209efdf85a9f002492e868aeec763dff24302"),
    ),
    (
        "lift_24.zkr",
        digest!("6c19051b474436e361bfa1e55055234b00a296ab8815f30f8770ba8dfd820801"),
    ),
    (
        "resolve.zkr",
        digest!("37e7b3ff1e380743cbd33650426cc339b5f545d5256acc07717a18d59328d220"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("3c7b9195e051f01d9dc21d96a1dd26c7035bc225511a715cf8c7ba83f8df7687"),
    ),
];
