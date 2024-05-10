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
    digest!("1ca9f73882f7b11685e6c6702d41f038ed7cd341b71d97115adaf81e8404873c"),
    digest!("55a319417092cc0ee5685455de8551421ef36b3de7cff0391478bf0335c4045e"),
    digest!("0e9269332ef0c02843ee796bade0cc1bfa03071a74ec15623f0c766158771166"),
    digest!("b20f380484297d66efbfd930108ea541d734dd1e6189dc1f0f647d10487ca43a"),
    digest!("202feb2b77a5c4675f02e50843635766dd9a9963d67af608525eab708ed1b023"),
    digest!("c884c54fd8e34558654fcb058e369955d3d75b516469ef5066208b3e4974b609"),
    digest!("f9b12b4707d9a9274665064ca487604e700c561e753b284c151ccc42b5bc5b11"),
    digest!("02591155c3ef402f8ca4b45c21491973fe305769e9f12f21c86d15307731643b"),
    digest!("f9cb321681130d5d77bf4e013d7ea0220571b75f39499b5a256a64275aa10e6d"),
    digest!("3b5368352b643730fe48d459ca66fc272de8e46e1dc0d349b98f886cefdd9219"),
    digest!("758ac221b3f3843dfe5fee23bf3097567f97103c5211e5075f8e151950a0b038"),
    digest!("ea9f2c0e3d0fd2047a6f1b2c96f1dc15c3a9b6712b253f587a804511b9430248"),
];

pub const ALLOWED_CONTROL_ROOT: Digest =
    digest!("75310e05f78b6d149d87c66ea5e2eb0b3d5afc45f0581017319c9f4cfd865113");

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
        digest!("1ca9f73882f7b11685e6c6702d41f038ed7cd341b71d97115adaf81e8404873c"),
    ),
    (
        "lift_15.zkr",
        digest!("55a319417092cc0ee5685455de8551421ef36b3de7cff0391478bf0335c4045e"),
    ),
    (
        "lift_16.zkr",
        digest!("0e9269332ef0c02843ee796bade0cc1bfa03071a74ec15623f0c766158771166"),
    ),
    (
        "lift_17.zkr",
        digest!("b20f380484297d66efbfd930108ea541d734dd1e6189dc1f0f647d10487ca43a"),
    ),
    (
        "lift_18.zkr",
        digest!("202feb2b77a5c4675f02e50843635766dd9a9963d67af608525eab708ed1b023"),
    ),
    (
        "lift_19.zkr",
        digest!("c884c54fd8e34558654fcb058e369955d3d75b516469ef5066208b3e4974b609"),
    ),
    (
        "lift_20.zkr",
        digest!("f9b12b4707d9a9274665064ca487604e700c561e753b284c151ccc42b5bc5b11"),
    ),
    (
        "lift_21.zkr",
        digest!("02591155c3ef402f8ca4b45c21491973fe305769e9f12f21c86d15307731643b"),
    ),
    (
        "lift_22.zkr",
        digest!("f9cb321681130d5d77bf4e013d7ea0220571b75f39499b5a256a64275aa10e6d"),
    ),
    (
        "lift_23.zkr",
        digest!("3b5368352b643730fe48d459ca66fc272de8e46e1dc0d349b98f886cefdd9219"),
    ),
    (
        "lift_24.zkr",
        digest!("758ac221b3f3843dfe5fee23bf3097567f97103c5211e5075f8e151950a0b038"),
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
