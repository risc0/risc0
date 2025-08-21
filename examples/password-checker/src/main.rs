// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use password_checker_core::PasswordRequest;
use password_checker_methods::PW_CHECKER_ELF;
use rand::RngCore as _;
use risc0_zkvm::{ExecutorEnv, default_prover, sha::Digest};

fn main() {
    let mut rng = rand::rng();
    let mut salt = [0u8; 32];
    rng.fill_bytes(&mut salt);

    let request = PasswordRequest {
        password: "S00perSecr1t!!!".into(),
        salt,
    };

    let password_hash = password_checker(request);
    println!("Password hash is: {}", &password_hash);
}

fn password_checker(request: PasswordRequest) -> Digest {
    let env = ExecutorEnv::builder()
        .write(&request)
        .unwrap()
        .build()
        .unwrap();

    // Obtain the default prover.
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, PW_CHECKER_ELF).unwrap().receipt;

    receipt.journal.decode().unwrap()
}

#[cfg(test)]
mod tests {
    use password_checker_core::PasswordRequest;

    #[test]
    fn main() {
        const TEST_SALT: [u8; 32] = [0u8; 32];
        const TEST_PASSWORD: &str = "S00perSecr1t!!!";

        let request = PasswordRequest {
            password: TEST_PASSWORD.into(),
            salt: TEST_SALT,
        };

        super::password_checker(request);
    }
}
