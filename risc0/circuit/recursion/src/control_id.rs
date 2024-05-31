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
    digest!("4882cd253cc9c775ca50d63162756140aa910608886b9c3f97d0d55653a86671"),
    digest!("bea76f74072983519b9ca337aae9e653b5468d721b1f9664c7bc2c50fa1fc236"),
    digest!("54f2492833c36345869f4b0c877c20283bb49e23d91f2221fc18483e1c3d8f62"),
    digest!("8ba9655c9c05b448bf45ed0252afae6ec7dbe51e48ac854b909e8a3634a77f46"),
    digest!("205aee38a87b8842baf45940820d4a35fa72f840155f404341209204afba365d"),
    digest!("b7d027515b61043b2c4332025f1c1a3b3d37801f306c064fa7a24468ff4ab52e"),
    digest!("94e63e70c527f37670e5a01e716b9c2424c9e741a3688c0d7c7d7d255e91a21d"),
    digest!("1b3f2e445ef19f462a5f570e0b61b43a84203c71af79913c447459048198a05d"),
    digest!("99e1c075b4777652d667fb5bd176323a8cdc3319b9bede4415ff2f6bb5acc501"),
    digest!("01f0065599a53470e5b94e4ff70e68178ec5c66255774f58e805d839d50f5a03"),
    digest!("173d6916af4a8826fb04d263bbfd75229c536b20969bc86e6e301e5de4d53313"),
    digest!("e788e63a7e9d9804f83aa34326caec3f1e871065400e9b7673479c2dd9ebed1c"),
    digest!("89270350893c3958d2463b1e5227b122a2868213d146c83fe99e9c584067fe52"),
    digest!("f0ce6e070e088e46eea00e4eb8729972c6a35417b9720f6d7c9f2620df6ce460"),
];

/// Root of the Merkle tree constructed from [ALLOWED_CONTROL_IDS], using Poseidon2.
pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("97daec1ebae0011ad383fe5bb1247e4bbbe6d150ee1403115c296d4993384a53");

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
