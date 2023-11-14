#![no_main]

use bonsai_groth16_verifier::Groth16;
use risc0_zkvm::guest::env;

risc0_zkvm::guest::entry!(main);

pub fn main() {
    let proof: Groth16 = env::read();
    proof.verify().unwrap();
    env::commit(&proof.digest());
}
