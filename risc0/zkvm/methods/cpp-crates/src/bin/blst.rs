// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use blst::min_pk::SecretKey;
use rand::RngCore;
use risc0_zkvm::guest::env;

fn main() {
    let mut rng = rand::rng();
    let mut ikm = [0u8; 32];
    rng.fill_bytes(&mut ikm);

    let sk = SecretKey::key_gen(&ikm, &[]).unwrap();
    let pk = sk.sk_to_pk();

    let dst = b"BLS_SIG_BLS12381G2_XMD:SHA-256_SSWU_RO_NUL_";
    let msg = b"blst is such a blast";
    let sig = sk.sign(msg, dst, &[]);

    let err = sig.verify(true, msg, dst, &[], &pk, true);
    assert_eq!(err, blst::BLST_ERROR::BLST_SUCCESS);
    env::commit(&String::from_utf8(msg.to_vec()).unwrap());
}
