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

use factors_methods::{MULTIPLY_ELF, MULTIPLY_ID};
use risc0_zkvm::serde::{from_slice, to_vec};
use risc0_zkvm::Prover;

fn main() {
    // Pick two numbers
    let a: u64 = 17;
    let b: u64 = 23;

    // Multiply them inside the ZKP
    // First, we make the prover, loading the 'multiply' method
    let mut prover = Prover::new(MULTIPLY_ELF, MULTIPLY_ID).expect(
        "Prover should be constructed from valid method source code and corresponding method ID",
    );

    // Next we send a & b to the guest
    prover.add_input_u32_slice(&to_vec(&a).expect("should be serializable"));
    prover.add_input_u32_slice(&to_vec(&b).expect("should be serializable"));
    // Run prover & generate receipt
    let receipt = prover
        .run()
        .expect("Should be able to prove valid code that fits in the cycle count.");

    // Extract journal of receipt (i.e. output c, where c = a * b)
    let c: u64 = from_slice(&receipt.journal).expect(
        "Journal output should deserialize into the same types (& order) that it was written",
    );

    // Print an assertion
    println!("I know the factors of {}, and I can prove it!", c);

    // Here is where one would send 'receipt' over the network...

    // Verify receipt, panic if it's wrong
    receipt.verify(&MULTIPLY_ID).expect(
        "Code you have proven should successfully verify; did you specify the correct method ID?",
    );
}

#[cfg(test)]
mod tests {
    use factors_methods::{MULTIPLY_ELF, MULTIPLY_ID};
    use risc0_zkvm::serde::{from_slice, to_vec};
    use risc0_zkvm::Prover;

    const TEST_FACTOR_ONE: u64 = 17;
    const TEST_FACTOR_TWO: u64 = 23;

    #[test]
    fn run_factors() {
        let mut prover = Prover::new(MULTIPLY_ELF, MULTIPLY_ID).expect(
            "Prover should be constructed from valid method source code and corresponding method ID",
        );

        prover.add_input_u32_slice(&to_vec(&TEST_FACTOR_ONE).expect("should be serializable"));
        prover.add_input_u32_slice(&to_vec(&TEST_FACTOR_TWO).expect("should be serializable"));

        let receipt = prover.run().expect("Should be able to prove valid code");
        receipt
            .verify(&MULTIPLY_ID)
            .expect("Proven code should verify");

        let result: u64 = from_slice(&receipt.journal).expect(
            "Journal output should deserialize into the same types (& order) that it was written",
        );
        assert_eq!(
            result,
            TEST_FACTOR_ONE * TEST_FACTOR_TWO,
            "We expect the zkVM output to be the product of the inputs"
        )
    }
}
