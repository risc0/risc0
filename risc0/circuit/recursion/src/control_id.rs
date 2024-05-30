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
    digest!("30dae603fcd283331d01105ea129ce43a0957a59b4f0013359a5642dfda0ba26"),
    digest!("2afea6024b79430b49f60518f27d7262f2ec5b1306a9030cc2e4d955e5dc5964"),
    digest!("8dc2760e1e24082cb66c83470c24a8017e95ce4d5eab170522f783418d545e72"),
    digest!("35feaa4eebbefd45b0a36a350671c82154f90c660389ed3a8ff7bd2a30805973"),
    digest!("7436486fdf9a7d3a3f8a03263bc7541a3c173c2ab5d2eb2c53939d0243dc0d16"),
    digest!("3abdc115ddf6af1977863c29c0f2b91f8c0c2a1c35e82158104b651f6a07a816"),
    digest!("17d75c070f373f333bbbaf33a688bb74fc05670435cd5d6378d37b608448e300"),
    digest!("f3cf1217485c403cea526b1e52e70835c31bdc6e3016ee12916f6c6561fc0977"),
    digest!("4043ce1426811d4f0e6a9c27256d052513c95739e9b80c74f628f313c739b75c"),
    digest!("b4edfc3f2c49f10285bcdc7493eb81063959820a59569356fb73b62c1586e01f"),
    digest!("cc1bd6753bb8fd41d41bba14bb56e90ffa9ddf4f20f7727734d140675a9cc52b"),
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
    digest!("dc6df62d962be908cb34c477e3c87d417d4c7d682ac9974509ecad6998641f2d");

/// Control ID for the identity recursion programs (ZKR), using Poseidon over the BN254 scalar field.
pub const BN254_IDENTITY_CONTROL_ID: Digest =
    digest!("0df1dcdc119a670072f4baac5a076a03e372a726cd1e20bacb2cf6be4d83ff10");

/// Control IDs for included recursion programs (ZKRs), using Poseidon2 over BabyBear.
pub const POSEIDON2_CONTROL_IDS: [(&str, Digest); 15] = [
    (
        "identity.zkr",
        digest!("4882cd253cc9c775ca50d63162756140aa910608886b9c3f97d0d55653a86671"),
    ),
    (
        "join.zkr",
        digest!("bea76f74072983519b9ca337aae9e653b5468d721b1f9664c7bc2c50fa1fc236"),
    ),
    (
        "lift_14.zkr",
        digest!("54f2492833c36345869f4b0c877c20283bb49e23d91f2221fc18483e1c3d8f62"),
    ),
    (
        "lift_15.zkr",
        digest!("8ba9655c9c05b448bf45ed0252afae6ec7dbe51e48ac854b909e8a3634a77f46"),
    ),
    (
        "lift_16.zkr",
        digest!("205aee38a87b8842baf45940820d4a35fa72f840155f404341209204afba365d"),
    ),
    (
        "lift_17.zkr",
        digest!("b7d027515b61043b2c4332025f1c1a3b3d37801f306c064fa7a24468ff4ab52e"),
    ),
    (
        "lift_18.zkr",
        digest!("94e63e70c527f37670e5a01e716b9c2424c9e741a3688c0d7c7d7d255e91a21d"),
    ),
    (
        "lift_19.zkr",
        digest!("1b3f2e445ef19f462a5f570e0b61b43a84203c71af79913c447459048198a05d"),
    ),
    (
        "lift_20.zkr",
        digest!("99e1c075b4777652d667fb5bd176323a8cdc3319b9bede4415ff2f6bb5acc501"),
    ),
    (
        "lift_21.zkr",
        digest!("01f0065599a53470e5b94e4ff70e68178ec5c66255774f58e805d839d50f5a03"),
    ),
    (
        "lift_22.zkr",
        digest!("173d6916af4a8826fb04d263bbfd75229c536b20969bc86e6e301e5de4d53313"),
    ),
    (
        "lift_23.zkr",
        digest!("e788e63a7e9d9804f83aa34326caec3f1e871065400e9b7673479c2dd9ebed1c"),
    ),
    (
        "lift_24.zkr",
        digest!("89270350893c3958d2463b1e5227b122a2868213d146c83fe99e9c584067fe52"),
    ),
    (
        "resolve.zkr",
        digest!("f0ce6e070e088e46eea00e4eb8729972c6a35417b9720f6d7c9f2620df6ce460"),
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
        digest!("1cc1b80bd6a3c76b7be88844d9983351148bc6fa102e527c7746733581297f02"),
    ),
    (
        "join.zkr",
        digest!("37eaae1dff32c34e83d7a5e38b4882c6a63b11b8f71add29ec5f37278cb9831b"),
    ),
    (
        "lift_14.zkr",
        digest!("a09cf821cee406dfd57d846ab36a677d509c6b8180dc23c22391405c8c05be90"),
    ),
    (
        "lift_15.zkr",
        digest!("f90bdc6ee9bad51a0b24732ddc4c50c2bcc54b2ee3deb0697b6965f2bb927c4d"),
    ),
    (
        "lift_16.zkr",
        digest!("f52da1c8cc73d1b801ef0947d1ac7ccccd936f2c65ca49feebcfdfe9cbaf4529"),
    ),
    (
        "lift_17.zkr",
        digest!("9026f4e8a9475ba6f879bc9ef312d33fd5f227a28c6791121e10afbec2df4eb9"),
    ),
    (
        "lift_18.zkr",
        digest!("84ac989092a65bb93b5831d33e99d92288fc2f4d5447d3a73e5e90b9d2eabc8c"),
    ),
    (
        "lift_19.zkr",
        digest!("86032eac3303844abc762fb3a784b7cbc68c1c24bd457d4df86d89d591c56402"),
    ),
    (
        "lift_20.zkr",
        digest!("6ab2d0ba2d824c701fca30d24dcabd7e843b95d97f874a8b9cdf3992ab7e35fd"),
    ),
    (
        "lift_21.zkr",
        digest!("447842a828cf6bdf0a12067ef5abfdb73e536a00ec02c6af7076a3767989e1af"),
    ),
    (
        "lift_22.zkr",
        digest!("198e6867803679ceb2de85f98a01d79ad51208770dc9213f68bdc88a77e2950e"),
    ),
    (
        "lift_23.zkr",
        digest!("cfbe814692e8ab0c87b531e73f8650882c40bb302471f871b5ff40242bd66c87"),
    ),
    (
        "lift_24.zkr",
        digest!("eac11081209fd98bcde51632315afc0c6ab91397ab83880be9ccf08e3c061439"),
    ),
    (
        "resolve.zkr",
        digest!("f6c0883f10b49f164a76e1b5dec3468357eec828749a1603442105d57dd62bd4"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("3c7b9195e051f01d9dc21d96a1dd26c7035bc225511a715cf8c7ba83f8df7687"),
    ),
];
