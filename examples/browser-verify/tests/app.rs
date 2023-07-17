use risc0_zkvm::SessionReceipt;
use risc0_zkvm_receipts::receipts::{FIB_ID, FIB_RECEIPT};
use wasm_bindgen_test::{wasm_bindgen_test, wasm_bindgen_test_configure};

wasm_bindgen_test_configure!(run_in_browser);

// This runs a unit test in the browser, so it can use browser APIs.
#[wasm_bindgen_test]
fn test_verify() {
    let receipt: SessionReceipt = bincode::deserialize(FIB_RECEIPT).unwrap();
    receipt.verify(FIB_ID).unwrap();
}
