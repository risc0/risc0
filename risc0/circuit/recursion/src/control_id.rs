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
    digest!("ea9f2c0e3d0fd2047a6f1b2c96f1dc15c3a9b6712b253f587a804511b9430248"),
];

pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("f20ad519aa71da4673c7392b30706a563380b81dabcb753babd679312397ac6e");

pub const BN254_CONTROL_ID: Digest =
    digest!("10ff834dbef62ccbba201ecd26a772e3036a075aacbaf47200679a11dcdcf10d");

pub const ZKR_CONTROL_IDS: [(&str, Digest); 15] = [
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
        digest!("ea9f2c0e3d0fd2047a6f1b2c96f1dc15c3a9b6712b253f587a804511b9430248"),
    ),
    (
        "test_recursion_circuit.zkr",
        digest!("ca7ade1f42976e5e103ad45c97e42963515f5b4b33076418e0a9390a576edd4e"),
    ),
];
