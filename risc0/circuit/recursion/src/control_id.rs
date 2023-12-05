// Copyright 2023 RISC Zero, Inc.
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

pub const RECURSION_CONTROL_IDS: [(&str, &str); 15] = [
    (
        "identity.zkr",
        "d75bc4134cbc30422041e12c8f3ea9768efdd41f7006bc1929a61843fbb9513b",
    ),
    (
        "join.zkr",
        "f5c57b24147ee94b9e6aa447f3b312640b052257d5553c5929e3c1211c414c02",
    ),
    (
        "lift_14.zkr",
        "ba8ecf588e144202e0ed1176c9fbd2211235d136c2e7413086bab6162271ce70",
    ),
    (
        "lift_15.zkr",
        "d688a01a07741f66ffc78d2392d71d43de374822d980c83a5b0d551e779fbc21",
    ),
    (
        "lift_16.zkr",
        "d0a2312a236fc8555cb48d4f67f0ab6c08b33d4b60901e193f33a354b42ec95a",
    ),
    (
        "lift_17.zkr",
        "fdb3db4689e0da497e14fe360b6b5003c16d4c1801d26b0066081840a22e6c66",
    ),
    (
        "lift_18.zkr",
        "1f336126cd60bd021569216874162c4f39750976b8c2443e7eb6755add7a2b4a",
    ),
    (
        "lift_19.zkr",
        "5e2c1331fb45a7771906871b80f397180a00f141256d8f4c3d5ede5a13196f6f",
    ),
    (
        "lift_20.zkr",
        "800da7765edc9651018a4c0ca1c93775d2045249e13f7e0ea83fda7209f34050",
    ),
    (
        "lift_21.zkr",
        "4f585b72d02be059d8557110ea0e2a1603a9a108aa116645e5f9ed2fa903003c",
    ),
    (
        "lift_22.zkr",
        "04b8d8497fde79654fbb8920118f3974b6d2442ce140c16e02bd6f63afcd0955",
    ),
    (
        "lift_23.zkr",
        "c2884640a0521366e4896167bbec273207e24064cfc4ab2ae916825e77fb9a10",
    ),
    (
        "lift_24.zkr",
        "c6968d61a11e0d2538f7b46cac4e8d69fe9be862f590531545c4cd308b64e91c",
    ),
    (
        "resolve.zkr",
        "2369ec64d831d361d77c7924a78be8250995e414f314d13c022d453a6180f45b",
    ),
    (
        "test_recursion_circuit.zkr",
        "93ddfd13ad326c73317033379bda035dd1e97a056aaed01c5beca909d764d213",
    ),
];

/// Merkle root of the RECURSION_CONTROL_IDS
pub const ALLOWED_IDS_ROOT: &str =
    "48062923d32b9b6f53983e29fb83b63d07da85088fe62d4c06b13336e6dfa63e";
