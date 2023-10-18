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
#![no_main]

use risc0_zkvm::guest::env;

risc0_zkvm::entry!(main);

pub fn main() {
    let input: Vec<u8> = env::read();

    let mut num_iter: u32;
    num_iter = input[0] as u32;
    num_iter = num_iter | ((input[1] as u32) << 8);
    num_iter = num_iter | ((input[2] as u32) << 16);
    num_iter = num_iter | ((input[3] as u32) << 24);

    let mut pre_output = blake3::hash(&input[4..]);
    let mut output = pre_output.as_bytes();
    for _ in 1..num_iter {
        pre_output = blake3::hash(output);
        output = pre_output.as_bytes();
    }

    env::commit(&risc0_zkvm::sha::Digest::try_from(*output).unwrap())
}
