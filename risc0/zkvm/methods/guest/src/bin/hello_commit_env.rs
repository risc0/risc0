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

#![no_std]
#![no_main]

use risc0_zkvm::guest::env;

risc0_zkvm::entry!(main);

// using option_env so test runs in the repo does not fail
// env! macro can also be used
// in this example code would look better with env!
const COMMIT_STR: &str = match option_env!("COMMIT_STR") {
    Some(s) => s,
    None => "hello world",
};

const SHOULD_COMMIT: bool = match option_env!("SHOULD_COMMIT") {
    Some(s) => {
        matches!(s.as_bytes(), b"true")
    }
    None => false,
};

fn main() {
    if SHOULD_COMMIT {
        env::commit_slice(COMMIT_STR.as_bytes());
    }
}
