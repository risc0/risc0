use borsh::BorshDeserialize;
use risc0_zkvm::{sha::Digest, Receipt};
use wasm_bindgen::prelude::*;
use web_sys::console;

#[wasm_bindgen]
pub fn verify_proof(proof_bytes: &[u8], image_id_bytes: &[u8]) -> Result<u32, JsValue> {
    // deseralize proof into Receipt
    let receipt = Receipt::try_from_slice(proof_bytes)
        .map_err(|e| JsValue::from(format!("Bad receipt: {e}")))?;

    // decode and log journal value
    let value: u32 = receipt
        .journal
        .decode()
        .map_err(|e| JsValue::from(format!("Journal decode: {e}")))?;
    console::log_1(&format!("Decoded journal value = {value}").into());

    // deseralize and log image ID
    let image_id = Digest::try_from_slice(image_id_bytes)
        .map_err(|_| JsValue::from("ImageID not 32 bytes"))?;
    console::log_1(&format!("Image ID: 0x{image_id}").into());

    // verify proof
    receipt
        .verify(image_id)
        .map_err(|e| JsValue::from(format!("Verify failed: {e}")))?;

    console::log_1(&"Proof verified successfully".into());
    Ok(value)
}
