use k256::ecdsa::{signature::Verifier, Signature, VerifyingKey};
use risc0_zkvm::guest::env;

fn main() {
    let input: Vec<(Vec<u8>, Signature, VerifyingKey)> = env::read();

    for (msg, sig, vk) in input {
        vk.verify(&msg, &sig).unwrap();
    }
}
