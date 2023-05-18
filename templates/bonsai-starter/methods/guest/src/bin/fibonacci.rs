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
#![no_std]

use ethabi::ethereum_types::U256;
use ethabi::{ParamType, Token};
use risc0_zkvm::guest::env;

risc0_zkvm::guest::entry!(main);

fn fibonacci(n: U256) -> U256 {
    let (mut prev, mut curr) = (U256::one(), U256::one());
    for _ in 2..=n.as_u32() {
        (prev, curr) = (curr, prev + curr);
    }
    return curr;
}

const INPUT_LEN: usize = core::mem::size_of::<U256>();

pub fn main() {
    // NOTE: Reads must be of known length. https://github.com/risc0/risc0/issues/402
    let mut input_bytes = [0u8; INPUT_LEN];
    env::read_slice(&mut input_bytes);
    let input = ethabi::decode_whole(&[ParamType::Uint(256)], &input_bytes).unwrap();
    let n: U256 = input[0].clone().into_uint().unwrap();

    // Run the computation.
    let result = fibonacci(n);

    // Commit the journal that will be decoded in the application contract.
    env::commit_slice(&ethabi::encode(&[Token::Uint(n), Token::Uint(result)]));
}
