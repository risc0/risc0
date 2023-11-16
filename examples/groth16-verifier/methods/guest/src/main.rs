#![no_std]
#![no_main]

use risc0_zkvm::{
    groth16::Groth16,
    guest::env,
    sha::{Impl, Sha256},
};

risc0_zkvm::guest::entry!(main);

pub fn main() {
    let proof: Groth16 = env::read();
    proof.verify().unwrap();
    env::commit(Impl::hash_bytes(&proof.to_vec()));
}
