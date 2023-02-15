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

use std::io::prelude::*;

use json_core::Outputs;
use methods::{SEARCH_JSON_ELF, SEARCH_JSON_ID};
use risc0_zkvm::serde::{from_slice, to_vec};
use risc0_zkvm::Prover;

fn main() {
    let mut file =
        std::fs::File::open("json/res/example.json").expect("Example file should be accessible");
    let mut data = String::new();
    file.read_to_string(&mut data)
        .expect("Should not have I/O errors");

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
