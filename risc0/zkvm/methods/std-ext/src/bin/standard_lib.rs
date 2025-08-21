// Copyright 2025 RISC Zero, Inc.
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

use std::io::{BufRead, BufReader, Read, Write, stdin, stdout};

use risc0_zkvm as _;

fn main() {
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
        "ARGS" => {
            // Collect args into a vector and commit them to the journal.
            let args: Vec<String> = std::env::args().collect();
            risc0_zkvm::guest::env::commit(&args);
        }
        "BUF_READ" => {
            let capacity: usize = risc0_zkvm::guest::env::read();
            let mut reader = BufReader::with_capacity(capacity, risc0_zkvm::guest::env::stdin());
            let buf = reader.fill_buf().unwrap();
            risc0_zkvm::guest::env::commit_slice(buf)
        }
        _ => {
            panic!("Unknown test mode {test_mode}");
        }
    }
}
