// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use risc0_zkvm::Receipt;
use risc0_zkvm_receipts::{FIB_ID, FIB_RECEIPT};
use wasm_bindgen_test::{wasm_bindgen_test, wasm_bindgen_test_configure};

wasm_bindgen_test_configure!(run_in_browser);

// `test_verify` runs a unit test in the browser, so it can use browser APIs.
#[allow(dead_code)]
#[wasm_bindgen_test]
fn test_verify() {
    let receipt: Receipt = bincode::deserialize(FIB_RECEIPT).unwrap();
    receipt.verify(FIB_ID).unwrap();
}
