// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use password_checker_core::PasswordRequest;
use pbkdf2::pbkdf2_hmac_array;
use risc0_zkvm::{guest::env, sha::Digest};
use sha2::Sha256;

/// Constant policy, compiled into the guest, for this example.
///
/// Note that the policy gets included in the program, and so is reflected in
/// the image ID. If the policy is changed, it will change the image ID.
const POLICY: PasswordPolicy = PasswordPolicy {
    min_length: 3,
    max_length: 64,
    min_numeric: 2,
    min_uppercase: 2,
    min_lowercase: 2,
    min_special_chars: 1,
};

/// Number of iterations used for PBKDF2. In this demo, it is set to a low value to keep proving
/// times short. Using a higher iteration count would be required for a real deployment.
const PBKDF2_SHA256_ITERATIONS: u32 = 10;

fn main() {
    let request: PasswordRequest = env::read();

    if !POLICY.is_valid(&request.password) {
        panic!("Password invalid. Please try again.");
    }

    let password_hash: Digest = pbkdf2_hmac_array::<Sha256, 32>(
        &request.password.as_bytes(),
        &request.salt,
        PBKDF2_SHA256_ITERATIONS,
    )
    .into();

    env::commit(&password_hash);
    env::commit(&request.salt);
}

struct PasswordPolicy {
    pub min_length: usize,
    pub max_length: usize,
    pub min_uppercase: usize,
    pub min_lowercase: usize,
    pub min_numeric: usize,
    pub min_special_chars: usize,
}

impl PasswordPolicy {
    pub fn is_valid(&self, pw: &str) -> bool {
        let metrics = PasswordMetrics::new(pw);
        self.correct_length(pw)
            && (metrics.numeric >= self.min_numeric)
            && (metrics.uppercase >= self.min_uppercase)
            && (metrics.lowercase >= self.min_lowercase)
            && (metrics.special >= self.min_special_chars)
    }

    fn correct_length(&self, password: &str) -> bool {
        password.len() > (self.min_length - 1) && password.len() < (self.max_length + 1)
    }
}

struct PasswordMetrics {
    pub numeric: usize,
    pub special: usize,
    pub uppercase: usize,
    pub lowercase: usize,
}

impl PasswordMetrics {
    pub fn new(password: &str) -> Self {
        let mut numeric = 0;
        let mut special = 0;
        let mut uppercase = 0;
        let mut lowercase = 0;
        for ch in password.chars() {
            if ch.is_ascii_digit() {
                numeric += 1;
            }
            if ch.is_ascii_punctuation() {
                special += 1;
            }
            if ch.is_ascii_uppercase() {
                uppercase += 1;
            }
            if ch.is_ascii_lowercase() {
                lowercase += 1;
            }
        }
        PasswordMetrics {
            numeric,
            special,
            uppercase,
            lowercase,
        }
    }
}
