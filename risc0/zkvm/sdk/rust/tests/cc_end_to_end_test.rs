#![cfg(feature = "risc_cc")]

use risc0_zkvm::host::Prover;
use risc0_zkvm::serde::{from_slice, to_vec};
use risc0_zkvm_methods::{CC_DEFAULT_ID, CC_DEFAULT_PATH, CC_RELEASE_ID, CC_RELEASE_PATH};

use std::path::Path;

fn test_cc_package<P: AsRef<Path>>(path: P, id: &[u8]) {
    let a: u64 = 17;
    let b: u64 = 23;

    let mut prover = Prover::new(&std::fs::read(path).unwrap(), id).unwrap();

    // Next we send a and b to the guest
    prover.add_input(to_vec(&a).unwrap().as_slice()).unwrap();
    prover.add_input(to_vec(&b).unwrap().as_slice()).unwrap();

    let receipt = prover.run().unwrap();

    // Extract journal of receipt (i.e. output c, where c = a + b)
    let c: u64 = from_slice(&receipt.get_journal_vec().unwrap()).unwrap();

    // Print an assertation
    println!("The sum of a and b is {}, and I can prove it!", c);

    receipt.verify(id).unwrap();
}

#[test]
fn default() {
    test_cc_package(CC_DEFAULT_PATH, CC_DEFAULT_ID);
}

#[test]
fn release() {
    test_cc_package(CC_RELEASE_PATH, CC_RELEASE_ID);
}
