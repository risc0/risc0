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

use composition_example_methods::{EXPONENTIATE_ELF, EXPONENTIATE_ID};
use hello_world::multiply;
use risc0_zkvm::{default_prover, ExecutorEnv};

fn main() {
    // Pick two numbers and multiply them, with a receipt.
    let (multiply_receipt, n) = multiply(17, 23);

    // Here is where one would send 'receipt' over the network to a second prover that might not
    // know the factors, but wants to do additional work with the proven composite number.
    let env = ExecutorEnv::builder()
        // add_assumption makes the receipt to be verified available to the prover.
        .add_assumption(multiply_receipt.into())
        .write(&n)
        .unwrap()
        .write(&9u64)
        .unwrap()
        .write(&100u64)
        .unwrap()
        .build()
        .unwrap();

    let receipt = default_prover().prove(env, EXPONENTIATE_ELF).unwrap();

    // Here the receipt might be sent to a third party that is interested in the exponentiation
    // under a known composite. This is similar to a verifiable RSA encryption under a public key.
    receipt.verify(EXPONENTIATE_ID).unwrap();

    // Decode the receipt to get (n, e, and c = x^e mod n).
    let (n, e, c): (u64, u64, u64) = receipt.journal.decode().unwrap();

    println!("{c} is the result of exponentiation by {e} under composite {n} with known factors");
}
