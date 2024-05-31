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
    digest!("bebb4c5f19d4973b590313766e476d3d7cce5c18b2d600188d7476767a4a8614"),
    digest!("0296f8241298c95f780501761519030966b9902bc508b539881b0c49bf326b6e"),
    digest!("b3b5d8727f259c31dfa971583c8db640a4a78b5b791fd76c15e90d2c5a85e45b"),
    digest!("3376da16801abe4c46bf9c508d67c559a6ba4a46e0f8c602bfd9a337c9b0f40b"),
    digest!("61c4fc0b6df2a935904374720c967b081deb844653f81956b71c4e1e863e6e3e"),
    digest!("1f2a072b0e7ae7113aa1193120e2543daf39ad727c2128539c84072ae150c960"),
    digest!("0c31d02a1900786d81bdae23ce96ce474c8b0b7182a91457aeac5a25b79f5c65"),
    digest!("1ef23b55919a8313dfb56057c4174431839660377a3e22738e279c02901ad345"),
    digest!("d695e66e4db81a4b6e8d535a5ba1370757291d1ef7fe1973db9cb83716565637"),
    digest!("9ef20b736835d16fb922710871488552582aee312f0925599d3fee12934b3465"),
    digest!("da824e2ecc179c2c1359bb75b154f8490086cd0f85e3391cc96ffc3b8e3afa11"),
    digest!("0d14977019e31b5aa2fb5d5f2f9a7d1150da1030aca1ee2a34dd511e76bda158"),
    digest!("a64159309c31972e41a9482d96c92c2782b4246170de98777577c1190efec732"),
    digest!("caad2362d9db1608bb4ab87165b18d70f3e76b16f21f80020c15171b69a4c95e"),
    digest!("02e9f7467f2bd4076f877a046021b32199b59e440dec4b4e18b8a8632c1bc702"),
    digest!("ee0ab647b41c086185cf5e149096ea1d1619943c59f16c2c4bf0a2679198b114"),
    digest!("db54df48d0c7a9298bbb634118282c2c876a271987fba070ef33b41ecaac5423"),
    digest!("0cfffb61eb5b2b0f9f5d2962a14b5807d1bf3117bd9f9f33a4b3f646cd555609"),
    digest!("4bebf924ca87650ba14c1f520a9670617440b4106581d91da6d5b364aada226c"),
    digest!("87dd874630d3572517a5ad0089cd1b60223a6916d1403538aaffda5339831d6e"),
    digest!("0229f8673856573bdc343c3b0d9fff116552831f4c0a4067e9ea4f39e3bc7d38"),
    digest!("28f1e255768c485955556e470ea71720840a74074406cd0d26dd18719e038917"),
    digest!("f7c1d5574d19ae5764d46330c18e9f4caed1d8501ccd0a689a220d2faf664955"),
    digest!("7f5db3464d8f3e2a96b3dc01ef7ced2abc0519610ad12f300c0ebb5341d87022"),
    digest!("65a1da29a2b29322ba6ecf0e63c26d4534ec424dff073c427bc9562a93b32f1d"),
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("02e7b069b7a5e327def07d423f1e4a16ef0c42765923f472b1517e5f0b13a745");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("c8e417a593c1129505bd2805e5cd6678a4408ab8bf9bab0e640cde1b66acd324");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 15] = [
    (
        "identity.zkr",
        digest!("0d14977019e31b5aa2fb5d5f2f9a7d1150da1030aca1ee2a34dd511e76bda158"),
    ),
    (
        "join.zkr",
        digest!("a64159309c31972e41a9482d96c92c2782b4246170de98777577c1190efec732"),
    ),
    (
        "lift_14.zkr",
        digest!("caad2362d9db1608bb4ab87165b18d70f3e76b16f21f80020c15171b69a4c95e"),
    ),
    (
        "lift_15.zkr",
        digest!("02e9f7467f2bd4076f877a046021b32199b59e440dec4b4e18b8a8632c1bc702"),
    ),
    (
        "lift_16.zkr",
        digest!("ee0ab647b41c086185cf5e149096ea1d1619943c59f16c2c4bf0a2679198b114"),
    ),
    (
        "lift_17.zkr",
        digest!("db54df48d0c7a9298bbb634118282c2c876a271987fba070ef33b41ecaac5423"),
    ),
    (
        "lift_18.zkr",
        digest!("0cfffb61eb5b2b0f9f5d2962a14b5807d1bf3117bd9f9f33a4b3f646cd555609"),
    ),
    (
        "lift_19.zkr",
        digest!("4bebf924ca87650ba14c1f520a9670617440b4106581d91da6d5b364aada226c"),
    ),
    (
        "lift_20.zkr",
        digest!("87dd874630d3572517a5ad0089cd1b60223a6916d1403538aaffda5339831d6e"),
    ),
    (
        "lift_21.zkr",
        digest!("0229f8673856573bdc343c3b0d9fff116552831f4c0a4067e9ea4f39e3bc7d38"),
    ),
    (
        "lift_22.zkr",
        digest!("28f1e255768c485955556e470ea71720840a74074406cd0d26dd18719e038917"),
    ),
    (
        "lift_23.zkr",
        digest!("f7c1d5574d19ae5764d46330c18e9f4caed1d8501ccd0a689a220d2faf664955"),
    ),
    (
        "lift_24.zkr",
        digest!("7f5db3464d8f3e2a96b3dc01ef7ced2abc0519610ad12f300c0ebb5341d87022"),
    ),
    (
        "resolve.zkr",
        digest!("65a1da29a2b29322ba6ecf0e63c26d4534ec424dff073c427bc9562a93b32f1d"),
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
        digest!("875e3270eb39643c3e280cd676c12a66553f90be8ddea59e3086355f90723327"),
    ),
    (
        "join.zkr",
        digest!("87a57cd491838844849f5925d1ba8132bb890b8a412894a118df25074476e065"),
    ),
    (
        "lift_14.zkr",
        digest!("ce32593f092cc7c67752ec891df638925344e8cb24b8e7b9d97d6bcc7a8d0290"),
    ),
    (
        "lift_15.zkr",
        digest!("9cbb742da7f4ab4d53712aa390a3ae8a7aeb353e24a89449a67029eab025ca33"),
    ),
    (
        "lift_16.zkr",
        digest!("955d3bd5837605b86c8ed4f940f8709396566e3975011de82df69b0eab80b6e9"),
    ),
    (
        "lift_17.zkr",
        digest!("d907653b8cd57d0bec2985a0cd9edf07afe5bfe0927fc0daec534af04f4a3902"),
    ),
    (
        "lift_18.zkr",
        digest!("8d10445ed255571bd9e5469a6df127537e65c36a82fcef2afc72533024324fbe"),
    ),
    (
        "lift_19.zkr",
        digest!("502de452bbb40cb20d17a477b8b51196bcd5356ad599108b0d2e8762da1c7b7f"),
    ),
    (
        "lift_20.zkr",
        digest!("cf67803d2b202fa85f0ee405946b0da2a321f7feaf7bcdd9ca7318aad07c498a"),
    ),
    (
        "lift_21.zkr",
        digest!("4f6d7538060733cf1aacde8d3f0aed8ecda733a5b8f30b5c1c0eddf024fd72b1"),
    ),
    (
        "lift_22.zkr",
        digest!("308e76fa8915b9049a2b11b167e00073675de9d1b76c5c81eec1928f5dfc4c1d"),
    ),
    (
        "lift_23.zkr",
        digest!("8477e4194a2d4321a907003c5523227fb5a1e962940364ac92804596095097ec"),
    ),
    (
        "lift_24.zkr",
        digest!("0b92c1b4afde1fdcc7f9d99e00ae1a86630cf305910bd8f57318d1b703c054f4"),
    ),
    (
        "resolve.zkr",
        digest!("fbf6caeb87e27a0075343c0b87d8820a05ed81b5c28e74632777a747120391cc"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("3c7b9195e051f01d9dc21d96a1dd26c7035bc225511a715cf8c7ba83f8df7687"),
    ),
];
