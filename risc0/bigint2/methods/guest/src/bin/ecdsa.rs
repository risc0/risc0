// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#![no_std]
#![no_main]

use k256::ecdsa::{Signature, VerifyingKey, signature::Verifier as _};

include!(concat!(env!("OUT_DIR"), "/ecdsa_signatures.rs"));

risc0_zkvm::entry!(main);

fn main() {
    let vk = VerifyingKey::from_sec1_bytes(&VERIFYING_KEY[..]).unwrap();

    for (sig, payload) in SIGNATURES.iter().zip(PAYLOADS.iter()) {
        let sig = Signature::from_bytes(sig.into()).unwrap();
        core::hint::black_box(vk.verify(&payload[..], &sig)).unwrap();
    }
}
