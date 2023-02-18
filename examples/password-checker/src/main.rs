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

use methods::{PW_CHECKER_ELF, PW_CHECKER_ID};
use password_checker_core::PasswordRequest;
use rand::prelude::*;
use risc0_zkp::core::sha::Digest;
use risc0_zkvm::serde::{from_slice, to_vec};
use risc0_zkvm::Prover;

fn main() {
    let mut rng = StdRng::from_entropy();
    let mut salt = [0u8; 32];
    rng.fill_bytes(&mut salt);

    let request = PasswordRequest {
        password: "S00perSecr1t!!!".into(),
        salt,
    };

    // a new prover is created to run the pw_checker method
    let mut prover = Prover::new(PW_CHECKER_ELF, PW_CHECKER_ID).unwrap();

    // Adding input to the prover makes it readable by the guest
    let vec = to_vec(&request).unwrap();
    prover.add_input_u32_slice(&vec);

    let receipt = prover.run().unwrap();
    let password_hash: Digest = from_slice(&receipt.journal).unwrap();
    println!("Password hash is: {}", &password_hash);

    // In most scenarios, we would serialize and send the receipt to a verifier here
    // The verifier checks the receipt with the following call, which panics if the
    // receipt is wrong
    receipt.verify(&PW_CHECKER_ID).unwrap();
}

#[cfg(test)]
mod tests {
    use methods::{PW_CHECKER_ELF, PW_CHECKER_ID};
    use password_checker_core::PasswordRequest;
    use risc0_zkvm::serde::to_vec;
    use risc0_zkvm::Prover;

    const TEST_SALT: [u8; 32] = [0u8; 32];
    const TEST_PASSWORD: &str = "S00perSecr1t!!!";

    #[test]
    fn main() {
        let request = PasswordRequest {
            password: TEST_PASSWORD.into(),
            salt: TEST_SALT,
        };

        // a new prover is created to run the pw_checker method
        let mut prover = Prover::new(PW_CHECKER_ELF, PW_CHECKER_ID).unwrap();

        // Adding input to the prover makes it readable by the guest
        let vec = to_vec(&request).unwrap();
        prover.add_input_u32_slice(&vec);

        let receipt = prover.run().unwrap();
        assert!(receipt.verify(&PW_CHECKER_ID).is_ok());
    }
}
