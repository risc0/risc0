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
use methods::{HMAC_ELF, HMAC_ID};
use risc0_zkp::core::sha::Digest;
use risc0_zkvm::serde::{from_slice, to_vec};
use risc0_zkvm::{Prover, Receipt};

fn hmac(key: &str, message: &str) -> Receipt {
    // Make the prover.
    let mut prover = Prover::new(HMAC_ELF, HMAC_ID)
        .expect("Prover should be constructed from matching code and method ID");

    prover.add_input_u32_slice(&to_vec(key).expect("input string should serialize"));
    prover.add_input_u32_slice(&to_vec(message).expect("input string should serialize"));

    // Run prover & generate receipt
    prover.run().expect("Code should be provable")
}

fn main() {
    // Parse command line
    let matches = Command::new("hash")
        .arg(Arg::new("message").default_value("Some text"))
        .arg(Arg::new("key").default_value("123"))
        .get_matches();

    let message = matches.get_one::<String>("message").unwrap();
    let key = matches.get_one::<String>("key").unwrap();

    // Prove hash and verify it
    let receipt = hmac(key, message);
    receipt.verify(HMAC_ID).expect("Proven code should verify");

    let journal = receipt.journal;
    let digest =
        from_slice::<Digest>(journal.as_slice()).expect("Journal should contain SHA Digest");

    println!("I provably know the message and key such that HMAC is {}", digest);
}

// #[cfg(test)]
// mod tests {
//     use methods::HMAC_ID;
//     use risc0_zkp::core::sha::Digest;
//     use risc0_zkvm::serde::from_slice;
//
//     use crate::hmac;
//
//     const TEST_STRING: &str = "abc";
//
//     #[test]
//     fn main() {
//         let receipt = hmac(TEST_STRING);
//         receipt.verify(HMAC_ID).expect("Proven code should verify");
//
//         let digest = from_slice::<Digest>(receipt.journal.as_slice())
//             .expect("Journal should contain SHA Digest");
//         assert_eq!(
//             hex::encode(digest.as_bytes()),
//             "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad",
//             "We expect to match the reference SHA-256 hash of the standard test value 'abc'"
//         );
//     }
// }
