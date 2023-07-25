// Copyright 2023 RISC Zero, Inc.
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

use std::io::{stdin, stdout, Read, Write};

use risc0_zkvm as _;

pub fn main() {
    let test_mode = std::env::var("TEST_MODE").unwrap();

    match test_mode.as_str() {
        "STDIO" => {
            // Test stdin, stdout, stderr
            eprintln!("Hello world on stderr!");
            println!("Hello world on stdout!");
            let mut from_stdin = Vec::new();
            stdin().read_to_end(&mut from_stdin).unwrap();
            stdout().write_all(&from_stdin).unwrap();
        }
        "ENV_VARS" => {
            // Read environment variables from standard input and print them to the journal.
            for var_name in stdin().lines() {
                let var_name = var_name.unwrap();
                let msg = match std::env::var(&var_name) {
                    Err(_) => format!("!{var_name}\n"),
                    Ok(val) => format!("{var_name}={val}\n"),
                };
                risc0_zkvm::guest::env::commit_slice(msg.as_bytes());
            }
        }
        _ => {
            panic!("Unknown test mode {test_mode}");
        }
    }
}
