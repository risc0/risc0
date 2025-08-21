// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::{fmt::Write as _, path::Path};

use k256::ecdsa::{Signature, SigningKey, VerifyingKey, signature::Signer as _};

const NUM_SIGNATURES: usize = 7;
const SIGNING_KEY: [u8; 32] = [
    191, 95, 105, 40, 155, 50, 183, 58, 61, 48, 1, 231, 44, 100, 10, 170, 64, 121, 99, 101, 208,
    121, 205, 143, 242, 81, 225, 52, 158, 95, 99, 36,
];

fn byte_slice_fmt(b: &[u8]) -> String {
    format!(
        "[{}]",
        b.iter()
            .map(|b| format!("0x{b:x}"))
            .collect::<Vec<_>>()
            .join(", ")
    )
}

fn main() {
    let mut output = String::new();

    write!(&mut output, "const VERIFYING_KEY: [u8; 33] = ").unwrap();
    let signing_key = SigningKey::from_bytes((&SIGNING_KEY).into()).unwrap();
    let verifying_key = VerifyingKey::from(&signing_key);
    writeln!(
        &mut output,
        "{};",
        byte_slice_fmt(&verifying_key.to_sec1_bytes()[..])
    )
    .unwrap();

    writeln!(&mut output).unwrap();
    writeln!(
        &mut output,
        "const SIGNATURES: [[u8; 64]; {NUM_SIGNATURES}] = ["
    )
    .unwrap();

    for i in 0..NUM_SIGNATURES {
        let payload = i.to_le_bytes();
        let signature: Signature = signing_key.sign(&payload[..]);
        writeln!(
            &mut output,
            "{},",
            byte_slice_fmt(&signature.to_bytes()[..])
        )
        .unwrap();
    }
    write!(&mut output, "];").unwrap();

    writeln!(&mut output).unwrap();
    writeln!(
        &mut output,
        "const PAYLOADS: [[u8; 8]; {NUM_SIGNATURES}] = ["
    )
    .unwrap();

    for i in 0..NUM_SIGNATURES {
        let payload = i.to_le_bytes();
        writeln!(&mut output, "{},", byte_slice_fmt(&payload[..])).unwrap();
    }
    write!(&mut output, "];").unwrap();

    let out_dir = std::env::var_os("OUT_DIR").unwrap();
    std::fs::write(Path::new(&out_dir).join("ecdsa_signatures.rs"), &output).unwrap();
}
