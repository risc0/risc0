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
    "89dfc82261b33a2174de881e8fc54017e2a21647850a8b73fa28c56b31bad34b";

pub const RECURSION_CONTROL_IDS: [(&str, &str); 15] = [
    (
        "identity.zkr",
        "a09149331924d71cf14f5b613484540d681f1d63753e9919c87d72414c100e6c",
    ),
    (
        "join.zkr",
        "457ae5443b8c522e474bd369e122896146263b5e619c641abf3fb633dc42dd0b",
    ),
    (
        "lift_14.zkr",
        "ddeedc095ce4c0060c29eb2d4b80fd3ebc89661c7c9dee1b13ed6e344b826053",
    ),
    (
        "lift_15.zkr",
        "78c3a62952dbf93b85d0484b6fe61505c5eaca61f251ce47c4a38f6d9b160b5d",
    ),
    (
        "lift_16.zkr",
        "f738ef56a740de749bd90c01dfd21a3c76e16f4e884bf02fd5c55f71f822873e",
    ),
    (
        "lift_17.zkr",
        "9dd53c2ad993c9189cc4811b20c9c9182b18df2e0a1ea66c661dc872ac9a7216",
    ),
    (
        "lift_18.zkr",
        "00123470ff364b39904fc75613f1135224e4c506b60d391dcd65d2061c875614",
    ),
    (
        "lift_19.zkr",
        "43731b0bfbf7fe46aaa4a51ec97ae73c1c588b289e5e2b5536dd976d3577b075",
    ),
    (
        "lift_20.zkr",
        "dbcd525a242b2c6a5d12472ec5418f4bc444b940b1c9944b08b1f84fdaf8eb3b",
    ),
    (
        "lift_21.zkr",
        "1138f71c52032c32ede9ea1b59daf11114bbec6e22e1fd19cd7b974ca6cf2059",
    ),
    (
        "lift_22.zkr",
        "1c12fe18d839ec4d60fea23b2d063a12acf1642fc488d04fef67c65126363550",
    ),
    (
        "lift_23.zkr",
        "42cce4089799b41ef12de32bb6422e38f222b871473fd927c89cfe21b924d54d",
    ),
    (
        "lift_24.zkr",
        "3159823a26f2f33abf4f015628dd120970845453bdee2e3636be2a15140e4475",
    ),
    (
        "resolve.zkr",
        "61a2fa5df9c9686208e9a926098cf8270bbfe76b843a2f3708a251549f21a530",
    ),
    (
        "test_recursion_circuit.zkr",
        "ca7ade1f42976e5e103ad45c97e42963515f5b4b33076418e0a9390a576edd4e",
    ),
];

pub const BN254_CONTROL_ID: &str =
    "2793e3a11528690d665e95dc211752ea64a77b509aa87339e2ba5cec97bc09af";
