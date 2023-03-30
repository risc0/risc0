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

use clap::{Arg, Command};
use risc0_zkvm::{
    serde::{from_slice, to_vec},
    sha::Digest,
    Prover, Receipt,
};
use sha_methods::{HASH_ELF, HASH_ID};

fn provably_hash(input: &str) -> Receipt {
    // Make the prover.
    let mut prover = Prover::new(HASH_ELF)
        .expect("Prover should be constructed from valid ELF binary");

    prover.add_input_u32_slice(&to_vec(input).expect("input string should serialize"));

    // Run prover & generate receipt
    prover.run().expect("Code should be provable unless it had an error or exceeded the maximum cycle limit")
}

fn main() {
    // Parse command line
    let matches = Command::new("hash")
        .arg(Arg::new("message").default_value(""))
        .get_matches();
    let message = matches.get_one::<String>("message").unwrap();

    // Prove hash and verify it
    let receipt = provably_hash(message);
    receipt.verify(&HASH_ID).expect("Proven code should verify");

    let digest: Digest = from_slice(&receipt.journal).expect("Journal should contain SHA Digest");

    println!("I provably know data whose SHA-256 hash is {}", digest);
}

#[cfg(test)]
mod tests {
    use risc0_zkvm::{serde::from_slice, sha::Digest};
    use sha_methods::HASH_ID;

    use crate::provably_hash;

    const TEST_STRING: &str = "abc";

    #[test]
    fn main() {
        let receipt = provably_hash(TEST_STRING);
        receipt.verify(&HASH_ID).expect("Proven code should verify");

        let digest: Digest =
            from_slice(&receipt.journal).expect("Journal should contain SHA Digest");
        assert_eq!(
            hex::encode(digest.as_bytes()),
            "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad",
            "We expect to match the reference SHA-256 hash of the standard test value 'abc'"
        );
    }
}
