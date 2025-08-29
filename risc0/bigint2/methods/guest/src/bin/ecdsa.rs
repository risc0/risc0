// Copyright 2025 RISC Zero, Inc.
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
