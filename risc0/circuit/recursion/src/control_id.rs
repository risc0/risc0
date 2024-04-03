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
    "ec8bb4496d18984ef78ac827b3ccd36d121dca1621fc12143a4eef60bc5e1339";

pub const RECURSION_CONTROL_IDS: [(&str, &str); 15] = [
    (
        "identity.zkr",
        "63d1f31503bc4b3d4a0a3d5bb358f63d3e7bc760f17002747a1ed0585c450a45",
    ),
    (
        "join.zkr",
        "27eada2cd321780dc6de631e4632b31751f94a4cc42f2862f8ac5a4e2968d226",
    ),
    (
        "lift_14.zkr",
        "6ee4b60ba803976cb9524940f335d83886893a45e24be6764824414ee3d2f914",
    ),
    (
        "lift_15.zkr",
        "9d0560739edbba39df66987543158a5288e626417341244d9f37cb3ea0e7e10a",
    ),
    (
        "lift_16.zkr",
        "0a77f64453a7e51a2bfcd5264c490b4c3926e3418d8f011d6dbb7d5d1c355062",
    ),
    (
        "lift_17.zkr",
        "b6644c086e898d6398be980460ab032af151e70ea6eb875d2d476d1882c17a0a",
    ),
    (
        "lift_18.zkr",
        "78669c3e7ad433464fe27821d0ad7857311e470edfb9905aa8dbe01e0332df00",
    ),
    (
        "lift_19.zkr",
        "24184c30c991dd445bf98506ba065d1b9f502f18465f883939ed200822032025",
    ),
    (
        "lift_20.zkr",
        "9ecd861337b4ea5da09b97015d94212f5de708251271d4014cba6968262b6129",
    ),
    (
        "lift_21.zkr",
        "43b91276d76977598136142c6303ee4dee53df66f9419f233eeecc6e5672ba00",
    ),
    (
        "lift_22.zkr",
        "8ee73e54db42260b7f61605adddd9b128ea6a508fb7d4a0031c4823dad94c157",
    ),
    (
        "lift_23.zkr",
        "923081004bf1c1745467c5577392672741e705533af55616fc59a3582ea98b38",
    ),
    (
        "lift_24.zkr",
        "77450228a462712e2eac6d4a37125e765655a62cb483a80efa61576563b43e14",
    ),
    (
        "resolve.zkr",
        "c3c7b6162d1ab926e8a5c3442af08654c752404c061c133bec86b910e862545f",
    ),
    (
        "test_recursion_circuit.zkr",
        "ca7ade1f42976e5e103ad45c97e42963515f5b4b33076418e0a9390a576edd4e",
    ),
];

pub const BN254_CONTROL_ID: &str =
    "30428f0c61dc6b56cf3909d956697e1d397de975c39168193da9e49a8a430611";
