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
    "b584335eed0877448ca6222b5d59ec4f46f7e03878b78a20a7788b311a9b5132";

pub const RECURSION_CONTROL_IDS: [(&str, &str); 15] = [
    (
        "identity.zkr",
        "b046ec62b0168930138735042d89f26a4f6cd94314292a1d45b8f5520dfcfc33",
    ),
    (
        "join.zkr",
        "1ae5b8530e69e75a3a26ea753f8af26766e9251a9d38fa0a30c441664c24ba66",
    ),
    (
        "lift_14.zkr",
        "93e4db2c1da8ba3c20d52c663d564375213b693f5ba58e3bb5d7be220d0ee70c",
    ),
    (
        "lift_15.zkr",
        "68880d1fe0a4ae69b4012c61b349fb5ce10366565b5e8c0e6b354b42e239ba4c",
    ),
    (
        "lift_16.zkr",
        "1c5ba85dca5ec90388a5b65dcb16ac1cc0acc3721116eb71eeb8bc2ba4db1b41",
    ),
    (
        "lift_17.zkr",
        "df0f263636734f3e058a7522fb4afa69b874db54b406833a8300d207cbf27331",
    ),
    (
        "lift_18.zkr",
        "faf10522bed46f4d95f2e3521ef9bb4b087d1f58964c96506ddf4d353db10f48",
    ),
    (
        "lift_19.zkr",
        "b9bdba6a18bfc426727fea2240bfc24c2bbecf4fa7b7b464eeb8d94a0bcab427",
    ),
    (
        "lift_20.zkr",
        "3ee88d5597dc53530fd809029b42184e59f6cf2cd200df718a405055818edb2c",
    ),
    (
        "lift_21.zkr",
        "b2e21d490d22a41c8658247108e1af47d07a8567636a625415edb94fb6789745",
    ),
    (
        "lift_22.zkr",
        "d34ecd3268bdb54b91730455cdd17b72ea6c264e92f56e2aaa40f2210c456b22",
    ),
    (
        "lift_23.zkr",
        "1779eb31fd7a2258ff45bb183c091c7795709a603d96c86f87688e2c80f1a960",
    ),
    (
        "lift_24.zkr",
        "4a64f2107f05403e5c087d456822820cf25d9540d4a2104ce00d9e6322942f09",
    ),
    (
        "resolve.zkr",
        "92f4554f6e07002c0e77dc4b9313a5047b75ba11bb6fcf6365944606a06e2906",
    ),
    (
        "test_recursion_circuit.zkr",
        "cdd619419544d9056869b64fe58d884a8bbe261d26df4356a9e4966adfc01317",
    ),
];
