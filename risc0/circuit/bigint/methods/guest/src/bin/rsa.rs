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

use risc0_circuit_bigint::rsa;
use risc0_zkvm::guest::env;

fn main() {
    // Computes and proves the result of modpow with exponent of 65537
    let input: Vec<u32> = env::read();
    let base: [u32; rsa::WIDTH_WORDS] = input.try_into().expect("Inputs must be 96 words");
    let input: Vec<u32> = env::read();
    let modulus: [u32; rsa::WIDTH_WORDS] = input.try_into().expect("Inputs must be 96 words");

    let mut result = [0u32; rsa::WIDTH_WORDS];

    // Safety: Parameters are dereferenceable and aligned
    unsafe {
        rsa::modpow_65537(&mut result, &base, &modulus);
    }

    env::commit(&result.to_vec());
}
