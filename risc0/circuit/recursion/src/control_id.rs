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
    digest!("0e51536ec08ac01e42de3d2a0b2a552d8ff2c75e4ef2b5285eed23582a13ef5d"), // recursion identity.zkr
    digest!("d7b56f6ef29d18203ac26960eb21160d60da6f1975124261fbe38d1364fa0e6b"), // recursion join.zkr
    digest!("1131f74f290f9d52f9aa2e7343b0445dff1765597a1e1849ed5f3f0afaba9f4e"), // recursion lift_14.zkr
    digest!("fa847f14bcdf7b75e75305209d29130bd07eb8387fe0f041e0d49c093a7b2564"), // recursion lift_15.zkr
    digest!("27c51b1abd46313679ed653a53945c7790832f5dd1906032c02916185b51fb06"), // recursion lift_16.zkr
    digest!("dbbe1a1ba268e716507e33528c843c3a63868f42bd236e71114d740b98f3690b"), // recursion lift_17.zkr
    digest!("618a6e1264419228270fdd7236f0232f715e98697a46f532a3d5d96251a7fe75"), // recursion lift_18.zkr
    digest!("c607b103592326302802cf1ff1c6ee5dab7f112e85c6106b4085e55c46535f1d"), // recursion lift_19.zkr
    digest!("deca5917ab949d3769a17415d4b5753d0a49f818af600815ad92c85067322217"), // recursion lift_20.zkr
    digest!("cc4245191072ea38989b65721112584cd548385f0eda402d76c70e0e718e0f73"), // recursion lift_21.zkr
    digest!("dd6cd51e766f484d625df405e74e11067283c1269dbdae21bc6a031b1daa952e"), // recursion lift_22.zkr
    digest!("4726ab732cc10d26e233aa6c82a32001f2d83a1878e5da7531017b737054dc6d"), // recursion lift_23.zkr
    digest!("8ea32467c6445926da67365554e3b64be92a5076d071ff0632f45b294787253f"), // recursion lift_24.zkr
    digest!("18386311e4b86b527f3d966de55df3271f7e52209c037b607a41a62c8b4c9f61"), // recursion resolve.zkr
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("9a3767040e4cf554112afa68bc043274a8636a06565e1d5e2b7fa90fda941218");

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
        digest!("1131f74f290f9d52f9aa2e7343b0445dff1765597a1e1849ed5f3f0afaba9f4e"),
    ),
    (
        "lift_15.zkr",
        digest!("fa847f14bcdf7b75e75305209d29130bd07eb8387fe0f041e0d49c093a7b2564"),
    ),
    (
        "lift_16.zkr",
        digest!("27c51b1abd46313679ed653a53945c7790832f5dd1906032c02916185b51fb06"),
    ),
    (
        "lift_17.zkr",
        digest!("dbbe1a1ba268e716507e33528c843c3a63868f42bd236e71114d740b98f3690b"),
    ),
    (
        "lift_18.zkr",
        digest!("618a6e1264419228270fdd7236f0232f715e98697a46f532a3d5d96251a7fe75"),
    ),
    (
        "lift_19.zkr",
        digest!("c607b103592326302802cf1ff1c6ee5dab7f112e85c6106b4085e55c46535f1d"),
    ),
    (
        "lift_20.zkr",
        digest!("deca5917ab949d3769a17415d4b5753d0a49f818af600815ad92c85067322217"),
    ),
    (
        "lift_21.zkr",
        digest!("cc4245191072ea38989b65721112584cd548385f0eda402d76c70e0e718e0f73"),
    ),
    (
        "lift_22.zkr",
        digest!("dd6cd51e766f484d625df405e74e11067283c1269dbdae21bc6a031b1daa952e"),
    ),
    (
        "lift_23.zkr",
        digest!("4726ab732cc10d26e233aa6c82a32001f2d83a1878e5da7531017b737054dc6d"),
    ),
    (
        "lift_24.zkr",
        digest!("8ea32467c6445926da67365554e3b64be92a5076d071ff0632f45b294787253f"),
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
        digest!("4ac8c994cce686f1f34b58a02306d5f4dc3b23f541b12e356b35cba2329cda38"),
    ),
    (
        "lift_15.zkr",
        digest!("0f5a3e976ea0708785937f7b56aa60eb11d8e74b275ec1bd335912545952b68f"),
    ),
    (
        "lift_16.zkr",
        digest!("539d5e95f78508c153991d01b2b5b21694184380d0f15bb7b0d5e38a3cf9ca44"),
    ),
    (
        "lift_17.zkr",
        digest!("a5f05912ab428681e340d874964e8f51e02cf1a6f1470e00b93185a436b65a1f"),
    ),
    (
        "lift_18.zkr",
        digest!("bb856ca8c5605b3eb0f62a9ef33210420bb68c65506f3c25b20d9834c24e9aa3"),
    ),
    (
        "lift_19.zkr",
        digest!("a0acd1c590a1658523a4a1029189bd7ca24f96e9b3784e277e3ccaa87027a1e6"),
    ),
    (
        "lift_20.zkr",
        digest!("c3af6e7b961dac1fa6aa5a011cd1609660149454fed7b619e3ef6d40163239f9"),
    ),
    (
        "lift_21.zkr",
        digest!("49905762e43368cdf1347ccc9eb3c5867322156f2a8239f45f379dc8cfee3739"),
    ),
    (
        "lift_22.zkr",
        digest!("0269b381b8cc63762251921c3c63d2f3e2ac84d320480626efae4f7960c10fe4"),
    ),
    (
        "lift_23.zkr",
        digest!("7952502886f18c76c7db510749f666b0103ad0eb4942ab9afc575ee38812dba4"),
    ),
    (
        "lift_24.zkr",
        digest!("a575522c04912c0f0b69b40943e1f18505a2c327baaba4af987115eccd935a46"),
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
