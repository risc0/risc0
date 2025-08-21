// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkvm::{Receipt, VerifierContext, guest::env, sha::Digest};

fn main() {
    let (receipt, image_id, dev_mode): (Receipt, Digest, bool) = env::read();
    let ctx = VerifierContext::default().with_dev_mode(dev_mode);
    receipt.verify_with_context(&ctx, image_id).unwrap();
}
