// Copyright (c) 2024 RISC Zero, Inc.
//
// All rights reserved.

use num_bigint::BigUint;
use risc0_circuit_bigint::rsa;
use risc0_zkvm::guest::env;

fn main() {
    // Read RSA input values
    let input: Vec<[BigUint; 3]> = env::read();
    let claims: Vec<_> = input
        .into_iter()
        .map(|[n, s, m]| rsa::claim(&rsa::RSA_256_X2, n, s, m))
        .collect();
    risc0_circuit_bigint::prove(&rsa::RSA_256_X2, &claims).expect("Unable to compose with RSA");
}
