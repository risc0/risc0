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
pub const ALLOWED_IDS_ROOT: &str = "{}";

pub const RECURSION_CONTROL_IDS: [(&str, &str); {}] = [{}];

pub const BN254_CONTROL_ID: &str = "{}";

#[test]
fn stable_root() {{
    // This tests that none of the control IDs have changed unexpectedly
    // If you have _intentionally_ changed control IDs, update this hash and bootstrap.

    assert_eq!(ALLOWED_IDS_ROOT, "88c1f749250aba181168c33839d7a351671e7a5b7f3e746dde91ef6c6e9ef344");
}}
