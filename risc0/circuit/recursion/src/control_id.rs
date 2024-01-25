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
    "dfe8716485ce37583122a060ba00f823236ef0089a5359095eca6302694c3e02";

pub const RECURSION_CONTROL_IDS: [(&str, &str); 15] = [
    (
        "identity.zkr",
        "e98992189a026320a91d564f59e407664adcbf342932d62d2d00356e5965f440",
    ),
    (
        "join.zkr",
        "40838c2880e79c3f078b9e21c91122405463e4460032dd69126b4870e5158518",
    ),
    (
        "lift_14.zkr",
        "ba39a74c8dc4106aa676d562ac9b5e1b4b9f1273d0481d0b7aa028323cfb5073",
    ),
    (
        "lift_15.zkr",
        "dbf9f006f702e71b1fad7f425d8074213154c219d6eb6c0ba084fa0680d54225",
    ),
    (
        "lift_16.zkr",
        "50b6d356a9fb8e3c51b17f2d4088550851dc510f4ac5a522d5fcd459ab44ed12",
    ),
    (
        "lift_17.zkr",
        "d554fe4a5e313202d39b9a2cff74fe25cf6faa4ed4575127f759a82647deb848",
    ),
    (
        "lift_18.zkr",
        "d017df2b6c3f801673598b55e28f3d064644c242faa278026c4c36622a2acd6c",
    ),
    (
        "lift_19.zkr",
        "f605e6754bb765316b37ba202569664172dff918811af2552e5d3a079ad20001",
    ),
    (
        "lift_20.zkr",
        "5942a4044f835a10f50372692307747120b1d9542b1c5563fb5cf85b66900e42",
    ),
    (
        "lift_21.zkr",
        "cac0aa4dc9d3e515e5bdb428f005410c8fbf714e8f38eb0210fb856714115e5a",
    ),
    (
        "lift_22.zkr",
        "1c7928777876fd54dc28bc386030050b4f243640ecda6901f9d16e5e3a0aed27",
    ),
    (
        "lift_23.zkr",
        "10cec15e41e3d0734e87183c3504d7577d08522ac5289520931cd357be169434",
    ),
    (
        "lift_24.zkr",
        "e448b86cbf56cf2d68c5220a5d4a054afc2c573aa40b3008cbae6d1e952e0603",
    ),
    (
        "resolve.zkr",
        "57de5e24fceeac338a621a4048adf60ba83a3f5271dad9012bdc8200b74fb142",
    ),
    (
        "test_recursion_circuit.zkr",
        "ecb24f6113e75e2107e2484c5505ef5721704b6271a20725d194891c5e7ca659",
    ),
];
