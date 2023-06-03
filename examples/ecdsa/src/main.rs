// Copyright 2023 RISC Zero, Inc.
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

use ecdsa_methods::ECDSA_VERIFY_ELF;
use k256::{
    ecdsa::{signature::Signer, Signature, SigningKey, VerifyingKey},
    EncodedPoint,
};
use rand_core::OsRng;
use risc0_zkvm::{
    serde::{from_slice, to_vec},
    Executor, ExecutorEnv, SessionReceipt,
};

fn prove_ecdsa_verification(
    verifying_key: &VerifyingKey,
    message: &[u8],
    signature: &Signature,
) -> SessionReceipt {
    let env = ExecutorEnv::builder()
        .add_input(&to_vec(&(verifying_key.to_encoded_point(true), message, signature)).unwrap())
        .build();

    let mut exec = Executor::from_elf(env, ECDSA_VERIFY_ELF).unwrap();
    exec.run().unwrap();
    let session = exec.run().unwrap();
    session.prove().unwrap()
}

fn main() {
    // Signing
    let signing_key = SigningKey::random(&mut OsRng); // Serialize with `::to_bytes()`
    let message = b"ECDSA proves knowledge of a secret number in the context of a single message";

    // Note: The signature type must be annotated or otherwise inferable as
    // `Signer` has many impls of the `Signer` trait (for both regular and
    // recoverable signature types).
    let signature: Signature = signing_key.sign(message);

    let receipt = prove_ecdsa_verification(signing_key.verifying_key(), message, &signature);

    let (receipt_verifying_key, receipt_message) =
        from_slice::<(EncodedPoint, Vec<u8>), _>(&receipt.journal)
            .unwrap()
            .try_into()
            .unwrap();

    println!(
        "Verified the signature over message {:?} with key {}",
        std::str::from_utf8(&receipt_message[..]).unwrap(),
        receipt_verifying_key,
    );
}
