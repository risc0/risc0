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
    "ebffc51ad4a2e4546d6b3e21837f86647398f622f4cec800fa6f5f73f74bca03";

pub const RECURSION_CONTROL_IDS: [(&str, &str); 15] = [
    (
        "identity.zkr",
        "89a59a42bf19e55a283809117b18b373ce18e61441d7ec37d0c286604d0f5413",
    ),
    (
        "join.zkr",
        "444bb94e1fd09065d31bd10b78f0f948ac12d6033e88652a6129d745f553342e",
    ),
    (
        "lift_14.zkr",
        "3370171fac05bc1be77fac5aaea925230936a24c67e44b16dbd8a92e93550a18",
    ),
    (
        "lift_15.zkr",
        "aa696146661af5274958741e7076d9211add7a75e9aabb47fe2e274dffc3b465",
    ),
    (
        "lift_16.zkr",
        "9d62cb0a399bc01040cde12a8bccf127120c6961103e22658a49cf09f029011a",
    ),
    (
        "lift_17.zkr",
        "4a45d4587ec49c296a20502293e2d7140b640b1512d92743d65d903b1580aa6a",
    ),
    (
        "lift_18.zkr",
        "139622546aa7af1a6297543402aebb1c2143c64a39b421180d80bc068a064a50",
    ),
    (
        "lift_19.zkr",
        "78ac1d0f3abfde1d0d1979560338bf6d560f7a2364622e527a7f572375684739",
    ),
    (
        "lift_20.zkr",
        "973174463a5b8873af12ef6be488ae2e0e1d212ef0ef8402a2a85a3af4471c5e",
    ),
    (
        "lift_21.zkr",
        "396663680ccef168cb1b8311dc5f794c632e3926763f6e1fed07ab76b5215e5f",
    ),
    (
        "lift_22.zkr",
        "7f8bb82d39769148a387fb18de71ce3ce269df1c34fe9b2b9c7f3e2ef1162c52",
    ),
    (
        "lift_23.zkr",
        "a0919a27785bdd2d19793574227c8973431cd7311dfb6b0633f233675aa68052",
    ),
    (
        "lift_24.zkr",
        "1231500edd13906f604b4e6861ed6c75e4577733fa8b3e696c73d01fac3edf0c",
    ),
    (
        "resolve.zkr",
        "adda8d322bcb203676406f1537c08059cdea370e847efd6678f6030b5337a038",
    ),
    (
        "test_recursion_circuit.zkr",
        "63586953836a5f46f3866d6c0ef18b14568a31246607a6769dc3fe50d945de32",
    ),
];
