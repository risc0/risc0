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

pub mod ffi;

#[test]
fn eval_check_size() {
    // Make sure the generated eval check/poly fp doesn't increase in
    // size unexpectedly.  This can sometimes happen when the layout
    // of registers in the circuit changes, so we want to guard against that here.

    let generated = include_str!("../cxx/poly_fp.cpp");
    let lines = generated.lines().count();

    const LINE_LIMIT: usize = 38100;

    assert!(
        lines < LINE_LIMIT,
        "poly_fp.cpp is expected to be under {LINE_LIMIT} lines but has {lines} lines"
    );
}
