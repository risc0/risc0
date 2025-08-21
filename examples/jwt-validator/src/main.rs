// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use jwt_core::CustomClaims;
use jwt_methods::VALIDATOR_ID;
use jwt_validator::prove_token_validation;

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    let claims = CustomClaims {
        subject: "Hello, world!".to_string(),
    };

    let (receipt, _) = prove_token_validation(&claims);

    receipt
        .verify(VALIDATOR_ID)
        .expect("Proof of validation should successfully verify");
}
