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
    digest!("63d1f31503bc4b3d4a0a3d5bb358f63d3e7bc760f17002747a1ed0585c450a45"),
    digest!("10487d125b96c44d770a3910fd1d473c5efe1e38fc4b0b128ccbf303addb2b17"),
    digest!("26a0752bf807b76a9ef621713bffc06cd07a7d38480cb52237aaec70ee289641"),
    digest!("3b1e9c4dab14540ee210c06a1bdf8513bf96672655c2a1360a95a556207e6a4b"),
    digest!("e809fd145941b451fc41543c3c27ba3a573d6614a9100d59634601673deafb5e"),
    digest!("df8a642741f8e209bfa0f5674c5f0241bfe7414268617547f54626569319f820"),
    digest!("94f1e411a8c87675f7508d42501ec219b27992601cbada04a2bff65afaf23a0f"),
    digest!("57f7ef699f24ea4918e37765c456480a39e6fd2034d68e225f176a1c306c6416"),
    digest!("2b360b5d938e497772e7b218fb8dbf68824ae418adc35b6f69a3c834d30dc655"),
    digest!("527e880933a1eb5cd9e867699866912fa9d15273e3892a1b19d6995f23febb31"),
    digest!("d6e2d442bc63510d98f04b33de581b0a91d819309194fc7178361955daca1c0f"),
    digest!("a69b130c9a867503a22f5b0f646c735b15343a6979a9f417fa2406107f6c566b"),
    digest!("2eed3b08d7d5ba4c6ca45568fb2cf2308e7e1804612a7e6f7c2bfa5909134567"),
    digest!("2b17d069bcab4043c69ccb36f5e08964535c71508d30475720620522c5319413"),
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("1a7a123fbc044710907ff72b7f6c9367d298530cac1dd7198c17ef5042c5483d");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("1106438a9ae4a93d196891c375e97d391d7e6956d90939cf566bdc610c8f4230");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 15] = [
    (
        "identity.zkr",
        digest!("63d1f31503bc4b3d4a0a3d5bb358f63d3e7bc760f17002747a1ed0585c450a45"),
    ),
    (
        "join.zkr",
        digest!("10487d125b96c44d770a3910fd1d473c5efe1e38fc4b0b128ccbf303addb2b17"),
    ),
    (
        "lift_14.zkr",
        digest!("26a0752bf807b76a9ef621713bffc06cd07a7d38480cb52237aaec70ee289641"),
    ),
    (
        "lift_15.zkr",
        digest!("3b1e9c4dab14540ee210c06a1bdf8513bf96672655c2a1360a95a556207e6a4b"),
    ),
    (
        "lift_16.zkr",
        digest!("e809fd145941b451fc41543c3c27ba3a573d6614a9100d59634601673deafb5e"),
    ),
    (
        "lift_17.zkr",
        digest!("df8a642741f8e209bfa0f5674c5f0241bfe7414268617547f54626569319f820"),
    ),
    (
        "lift_18.zkr",
        digest!("94f1e411a8c87675f7508d42501ec219b27992601cbada04a2bff65afaf23a0f"),
    ),
    (
        "lift_19.zkr",
        digest!("57f7ef699f24ea4918e37765c456480a39e6fd2034d68e225f176a1c306c6416"),
    ),
    (
        "lift_20.zkr",
        digest!("2b360b5d938e497772e7b218fb8dbf68824ae418adc35b6f69a3c834d30dc655"),
    ),
    (
        "lift_21.zkr",
        digest!("527e880933a1eb5cd9e867699866912fa9d15273e3892a1b19d6995f23febb31"),
    ),
    (
        "lift_22.zkr",
        digest!("d6e2d442bc63510d98f04b33de581b0a91d819309194fc7178361955daca1c0f"),
    ),
    (
        "lift_23.zkr",
        digest!("a69b130c9a867503a22f5b0f646c735b15343a6979a9f417fa2406107f6c566b"),
    ),
    (
        "lift_24.zkr",
        digest!("2eed3b08d7d5ba4c6ca45568fb2cf2308e7e1804612a7e6f7c2bfa5909134567"),
    ),
    (
        "resolve.zkr",
        digest!("2b17d069bcab4043c69ccb36f5e08964535c71508d30475720620522c5319413"),
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
        digest!("f004477880d8dcdf347a5aae9d6d5a922475cfe7507cd3320dd45d69f6bd27fb"),
    ),
    (
        "join.zkr",
        digest!("6f3f6433d8990fcd9452ca8190fa167e61b7b577f8528e60ed7316bc9b3911d4"),
    ),
    (
        "lift_14.zkr",
        digest!("021ddafb1f23d7ff5f93748bcbee0b0fa0c28c70477331e6ffd232cf38f6496d"),
    ),
    (
        "lift_15.zkr",
        digest!("ff550d051e475f8c99b49ccca8c6757832021b93274132927e26341742722621"),
    ),
    (
        "lift_16.zkr",
        digest!("82bbda05a0e847e71b39254cdab9b717b9f49e16ef5b46a75e06b22a702a24fd"),
    ),
    (
        "lift_17.zkr",
        digest!("07f415783b3dd9964a6380b44dadddca4398743d6b2ca0f9de2c1bd6826e1b35"),
    ),
    (
        "lift_18.zkr",
        digest!("0133911f970ee5377ad01c60f1910add01670712e9b019f76214540bb64f88c2"),
    ),
    (
        "lift_19.zkr",
        digest!("8518d85436c05691fe43c94a098c2a918dabb00f209049801162db1ce7dba12a"),
    ),
    (
        "lift_20.zkr",
        digest!("eb7ad87fd2f55164efe29c7a5a83ec265bcaa0c7ddc0ab0eae04b0b866d95339"),
    ),
    (
        "lift_21.zkr",
        digest!("eecfd1d6cd91597fe61dad69485bf115ee03ee52b0921e1f574f3430bc39fde6"),
    ),
    (
        "lift_22.zkr",
        digest!("078dc3148255bb319ec5b602c04a6b50bc3c185450a36afe79be837d5eba2904"),
    ),
    (
        "lift_23.zkr",
        digest!("3f855c40e5c81396cb12e2053d4866d73f66fa2d105f4157f278c7474b1308ba"),
    ),
    (
        "lift_24.zkr",
        digest!("e24a0b8d77812d50d1337f3ae8bfbbdca2f3b609bc843ec096901eb015a083dd"),
    ),
    (
        "resolve.zkr",
        digest!("765aad3340312db7fd7c2c35133fb13d377409bbecb0b7e4cd9aa18eefa83e3b"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("3c7b9195e051f01d9dc21d96a1dd26c7035bc225511a715cf8c7ba83f8df7687"),
    ),
];
