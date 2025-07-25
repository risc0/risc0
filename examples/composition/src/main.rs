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

use composition_example_methods::{EXPONENTIATE_ELF, EXPONENTIATE_ID};
use hello_world::multiply;
use risc0_zkvm::{default_prover, ExecutorEnv};

fn main() {
    // Some party "Alice" picks two numbers and multiplies them, producing a receipt that attests
    // the fact that Alice knows the factorization of the product. This is similar to RSA keygen.
    let (multiply_receipt, n) = multiply(17, 23);

    // Alice might then send to "Bob" the product and the receipt that proves Alice knows the
    // factorization. Bob then raises a secret number to a public exponent mod the composite number
    // chosen by Alice. This is like an RSA encryption from Bob to Alice, verified by the zkVM.
    let env = ExecutorEnv::builder()
        // add_assumption makes the receipt to be verified available to the prover.
        .add_assumption(multiply_receipt)
        .write(&(n, 9u64, 100u64))
        .unwrap()
        .build()
        .unwrap();

    let receipt = default_prover()
        .prove(env, EXPONENTIATE_ELF)
        .unwrap()
        .receipt;

    // Anybody who receives the receipt for the exponentiation is assured both that:
    // A) The modulus n included in the journal has a known factorization.
    // B) The number c is the result of exponentiation of some known secret x ^ e mod n.
    //
    // These two statements are proven with a single receipt via composition.
    receipt.verify(EXPONENTIATE_ID).unwrap();

    // Decode the receipt to get (n, e, and c = x^e mod n).
    let (n, e, c): (u64, u64, u64) = receipt.journal.decode().unwrap();

    println!("{c} is the result of exponentiation by {e} under composite {n} with known factors");
}
