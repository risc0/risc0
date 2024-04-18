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
    "88c1f749250aba181168c33839d7a351671e7a5b7f3e746dde91ef6c6e9ef344";

pub const RECURSION_CONTROL_IDS: [(&str, &str); 15] = [
    (
        "identity.zkr",
        "4882cd253cc9c775ca50d63162756140aa910608886b9c3f97d0d55653a86671",
    ),
    (
        "join.zkr",
        "d6d4e4502b24a53e2097c86b820695196b50214171d1af085cf0d329eda2354c",
    ),
    (
        "lift_14.zkr",
        "e54c9017d3cd7b10f8590a097cc4ee3d309c380bcc9b310ead94587341b4d550",
    ),
    (
        "lift_15.zkr",
        "9119b275ec70de27192e4d324bdb3c4d8a1b9e7137b9170ca0baed0d8bf77d0c",
    ),
    (
        "lift_16.zkr",
        "c5be2418325c0314e4bfe822d4c5bc5763abde06b59b7a4c35013e271470280a",
    ),
    (
        "lift_17.zkr",
        "aa78453ab464ed650ac5b70debc4453a2a703e6f83c10755f518bc081926481d",
    ),
    (
        "lift_18.zkr",
        "d5cdf820ae55b209a2bc1b2b58803c0b85408934fc575c38da42931673e38144",
    ),
    (
        "lift_19.zkr",
        "8fd2f733163e846b17a6503ad7070718f49b425c5d6b6a77751e9a221a407d4b",
    ),
    (
        "lift_20.zkr",
        "5ae5fb57f4d8ca65e83af3650ce36f00c309267032699b6e9865b21e847f2070",
    ),
    (
        "lift_21.zkr",
        "9407fc33d5126735f24ec662f156e50e377b45534ab789739145021f752c152a",
    ),
    (
        "lift_22.zkr",
        "90027841077ad96250be266855d8506d0164b775bea8c35594ab5a40f9530955",
    ),
    (
        "lift_23.zkr",
        "47d3095f79618d57f3ee9c1bb2046c680a18ab05d062af2e33e6a53d1202063a",
    ),
    (
        "lift_24.zkr",
        "1112c0660d6a8c3dc7b2961cfe996815a19fbf2583f2d0639d530826aa67764f",
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
