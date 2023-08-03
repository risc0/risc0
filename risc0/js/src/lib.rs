use risc0_zkvm::receipt;
use wasm_bindgen::prelude::*;

#[wasm_bindgen]
pub struct Receipt(receipt::Receipt);

#[wasm_bindgen]
impl Receipt {
    pub fn bincode_deserialize(buffer: &[u8]) -> Result<Receipt, JsError> {
        let receipt = bincode::deserialize(buffer)
            .map_err(|e| JsError::new(&format!("Failed to deserialize receipt: {e}")))?;
        Ok(Receipt(receipt))
    }

    #[wasm_bindgen(getter)]
    pub fn journal(&self) -> Vec<u8> {
        self.0.journal.clone()
    }

    pub fn validate(&self, image_id: &[u8]) -> Result<(), JsError> {
        let image_id: [u8; 32] = image_id.try_into()?;
        self.0
            .verify(image_id)
            .map_err(|e| JsError::new(&format!("Failed to validate proof: {e}")))
    }
}

#[cfg(test)]
pub mod tests {
    use risc0_zkvm_receipts::{FIB_ID, FIB_RECEIPT};
    use wasm_bindgen_test::wasm_bindgen_test_configure;

    wasm_bindgen_test_configure!(run_in_browser);

    use wasm_bindgen_test::*;

    use super::Receipt;

    #[wasm_bindgen_test]
    fn verify_receipt() {
        let receipt = Receipt::bincode_deserialize(FIB_RECEIPT)
            .unwrap_or_else(|_| panic!("invalid deserialization"));
        receipt
            .validate(&FIB_ID)
            .unwrap_or_else(|_| panic!("invalid validation"));
    }
}
