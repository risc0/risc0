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

/// Merkle root of the RECURSION_CONTROL_IDS
pub const ALLOWED_IDS_ROOT: &str =
    "75310e05f78b6d149d87c66ea5e2eb0b3d5afc45f0581017319c9f4cfd865113";

pub const RECURSION_CONTROL_IDS: [(&str, &str); 15] = [
    (
        "identity.zkr",
        "4882cd253cc9c775ca50d63162756140aa910608886b9c3f97d0d55653a86671",
    ),
    (
        "join.zkr",
        "bea76f74072983519b9ca337aae9e653b5468d721b1f9664c7bc2c50fa1fc236",
    ),
    (
        "lift_14.zkr",
        "1ca9f73882f7b11685e6c6702d41f038ed7cd341b71d97115adaf81e8404873c",
    ),
    (
        "lift_15.zkr",
        "55a319417092cc0ee5685455de8551421ef36b3de7cff0391478bf0335c4045e",
    ),
    (
        "lift_16.zkr",
        "0e9269332ef0c02843ee796bade0cc1bfa03071a74ec15623f0c766158771166",
    ),
    (
        "lift_17.zkr",
        "b20f380484297d66efbfd930108ea541d734dd1e6189dc1f0f647d10487ca43a",
    ),
    (
        "lift_18.zkr",
        "202feb2b77a5c4675f02e50843635766dd9a9963d67af608525eab708ed1b023",
    ),
    (
        "lift_19.zkr",
        "c884c54fd8e34558654fcb058e369955d3d75b516469ef5066208b3e4974b609",
    ),
    (
        "lift_20.zkr",
        "f9b12b4707d9a9274665064ca487604e700c561e753b284c151ccc42b5bc5b11",
    ),
    (
        "lift_21.zkr",
        "02591155c3ef402f8ca4b45c21491973fe305769e9f12f21c86d15307731643b",
    ),
    (
        "lift_22.zkr",
        "f9cb321681130d5d77bf4e013d7ea0220571b75f39499b5a256a64275aa10e6d",
    ),
    (
        "lift_23.zkr",
        "3b5368352b643730fe48d459ca66fc272de8e46e1dc0d349b98f886cefdd9219",
    ),
    (
        "lift_24.zkr",
        "758ac221b3f3843dfe5fee23bf3097567f97103c5211e5075f8e151950a0b038",
    ),
    (
        "resolve.zkr",
        "ea9f2c0e3d0fd2047a6f1b2c96f1dc15c3a9b6712b253f587a804511b9430248",
    ),
    (
        "test_recursion_circuit.zkr",
        "ca7ade1f42976e5e103ad45c97e42963515f5b4b33076418e0a9390a576edd4e",
    ),
];

pub const BN254_CONTROL_ID: &str =
    "10ff834dbef62ccbba201ecd26a772e3036a075aacbaf47200679a11dcdcf10d";
