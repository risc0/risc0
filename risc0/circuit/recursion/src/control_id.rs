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
    "0fc5ed20489da66ad74ed75a58111203e1eccb18b34c472ba14c4d5b8f68da57";

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
        "0b7a811c21a4236c0f75931b0878fc6390ef03169b15b92e109cc5555f28fe02",
    ),
    (
        "lift_15.zkr",
        "f3ec3701ea924909c2c78e6a6b01c617e5c7212c7791b5705220335be665d860",
    ),
    (
        "lift_16.zkr",
        "69f304481e0749675cd06e5502b0436de92aed113cfd5638a2891020de34134e",
    ),
    (
        "lift_17.zkr",
        "5480bc09f0b1e4341364770c86292737d095de10d0e4b937d76caf1f1b350559",
    ),
    (
        "lift_18.zkr",
        "386b691caf0c02059fb6ce33a910c61e771a4b1cbbfbdc0299b5b84269fe4e4b",
    ),
    (
        "lift_19.zkr",
        "f5b0e3010e0e22435ec683360c7de015e7ec8c3e65540d61f5c51a5c50e89871",
    ),
    (
        "lift_20.zkr",
        "88ea156ea2b41f5b85d6fa15cafaf14c40f0b22ec359b32e80d0b65a183c4218",
    ),
    (
        "lift_21.zkr",
        "ab3c4f6a3d494b412e52936d4a786731327ebd5036efb163a2b69d411841e724",
    ),
    (
        "lift_22.zkr",
        "544b9f032c394d494f2ede005268b40520ef03617166ef1b2a71326d5da0e651",
    ),
    (
        "lift_23.zkr",
        "639c35240ec2184819ea545d16b39a63f3d20c06855a86533bd53c0f0afff443",
    ),
    (
        "lift_24.zkr",
        "9a23ef2902cc7d3389b3df2493e1106e67d0806bd33dd4292cab970a5fd6392f",
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
