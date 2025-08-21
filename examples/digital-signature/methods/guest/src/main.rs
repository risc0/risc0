// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#![no_main]
#![no_std]

use digital_signature_core::{SignMessageCommit, SigningRequest};
use risc0_zkvm::guest::env;
use risc0_zkvm::sha::{Impl, Sha256};

risc0_zkvm::guest::entry!(main);

fn main() {
    let request: SigningRequest = env::read();
    env::commit(&SignMessageCommit {
        identity: *Impl::hash_bytes(request.passphrase.as_bytes()),
        msg: request.msg,
    });
}
