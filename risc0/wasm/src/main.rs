#![no_main]

use risc0_zkvm::{MethodId, Receipt};

// This binary is here as a way to check which deps are included
// when building for the wasm32-unknown-unknown target.
// Eventually this program should run a full verify with a real receipt.

#[no_mangle]
fn _start() {
    // TODO: use a real receipt and method_id
    let receipt = Receipt::new(&[], &[]);
    let method_id = MethodId::from_slice(&[]).unwrap();
    receipt.verify(method_id).unwrap();
}
