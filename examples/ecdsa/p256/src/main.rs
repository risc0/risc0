// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use p256::{
    EncodedPoint,
    ecdsa::{Signature, SigningKey, VerifyingKey, signature::Signer},
};
use p256_methods::{P256_VERIFY_ELF, P256_VERIFY_ID};
use rand_core::OsRng;
use risc0_zkvm::{ExecutorEnv, Receipt, default_prover};

/// Given an secp256r1 verifier key (i.e. public key), message and signature,
/// runs the ECDSA verifier inside the zkVM and returns a receipt, including a
/// journal and seal attesting to the fact that the prover knows a valid
/// signature from the committed public key over the committed message.
fn prove_ecdsa_verification(
    verifying_key: &VerifyingKey,
    message: &[u8],
    signature: &Signature,
) -> Receipt {
    let input = (verifying_key.to_encoded_point(true), message, signature);
    let env = ExecutorEnv::builder()
        .write(&input)
        .unwrap()
        .build()
        .unwrap();

    // Obtain the default prover.
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    prover.prove(env, P256_VERIFY_ELF).unwrap().receipt
}

fn main() {
    // Generate a random secp256r1 keypair and sign the message.
    let signing_key = SigningKey::random(&mut OsRng); // Serialize with `::to_bytes()`
    let message = b"This is a message that will be signed, and verified within the zkVM";
    let signature: Signature = signing_key.sign(message);

    // Run signature verified in the zkVM guest and get the resulting receipt.
    let receipt = prove_ecdsa_verification(signing_key.verifying_key(), message, &signature);

    // Verify the receipt and then access the journal.
    receipt.verify(P256_VERIFY_ID).unwrap();
    let (receipt_verifying_key, receipt_message): (EncodedPoint, Vec<u8>) =
        receipt.journal.decode().unwrap();

    println!(
        "Verified the signature over message {:?} with key {}",
        std::str::from_utf8(&receipt_message[..]).unwrap(),
        receipt_verifying_key,
    );
}
