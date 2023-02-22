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

use json_core::Outputs;
use json_methods::{SEARCH_JSON_ELF, SEARCH_JSON_ID};
use risc0_zkvm::{
    serde::{from_slice, to_vec},
    Prover,
};

fn main() {
    let data = include_str!("../res/example.json");

    // Make the prover.
    let mut prover = Prover::new(SEARCH_JSON_ELF, SEARCH_JSON_ID)
        .expect("Prover should be constructed from matching method code & ID");

    prover.add_input_u32_slice(&to_vec(&data).expect("should be serializable"));

    // Run prover & generate receipt
    let receipt = prover.run().expect("Code should be provable");

    receipt
        .verify(&SEARCH_JSON_ID)
        .expect("Proven code should verify");

    let journal = &receipt.journal;
    let outputs: Outputs = from_slice(&journal).expect("Journal should contain an Outputs object");

    println!("\nThe JSON file with hash\n  {:?}\nprovably contains a field 'critical_data' with value {}\n", outputs.hash, outputs.data);
}

#[cfg(test)]
mod tests {
    use json_core::Outputs;
    use json_methods::{SEARCH_JSON_ELF, SEARCH_JSON_ID};
    use risc0_zkvm::{
        serde::{from_slice, to_vec},
        Prover,
    };

    #[test]
    fn main() {
        let data = include_str!("../res/example.json");

        // Make the prover.
        let mut prover = Prover::new(SEARCH_JSON_ELF, SEARCH_JSON_ID)
            .expect("Prover should be constructed from matching method code & ID");
        prover.add_input_u32_slice(&to_vec(&data).expect("should be serializable"));

        // Run prover & generate receipt
        let receipt = prover.run().expect("Code should be provable");

        receipt
            .verify(&SEARCH_JSON_ID)
            .expect("Proven code should verify");

        let journal = &receipt.journal;
        let outputs: Outputs =
            from_slice(&journal).expect("Journal should contain an Outputs object");
        assert_eq!(
            outputs.data, 47,
            "Did not find the expected value in the critical_data field"
        );
    }
}
