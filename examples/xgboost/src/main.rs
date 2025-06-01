// Copyright 2024 RISC Zero, Inc.
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

use forust_ml::GradientBooster;
use risc0_zkvm::{default_prover, ExecutorEnv};
use xgboost_methods::XGBOOST_ELF;

const JSON_MODEL: &str = include_str!("../res/trained_model.json");

fn main() {
    let answer = predict();
    println!("Prediction from the trained XGBoost model is: {}", &answer);
}

fn predict() -> f64 {
    // We import the trained model
    let model: GradientBooster = serde_json::from_str(JSON_MODEL).unwrap();

    // We serialize the model to a byte array before transferring it to the guest.
    let model_bytes: Vec<u8> = rmp_serde::to_vec(&model).unwrap();

    // We define an input value for the model (inputs are block number and number of transaction in that block.  Note we modify the block number to a f64 value).
    //**************************//
    // ADD YOUR INPUT DATA HERE //
    //**************************//
    let data: Vec<f64> = vec![18511304.0, 117.0];

    // We transfer the input data, the rmp array length, and the serialized model over to the guest.
    let env = ExecutorEnv::builder()
        .write(&data)
        .unwrap()
        .write(&model_bytes)
        .unwrap()
        .build()
        .unwrap();

    // Obtain the default prover.
    // To bypass the prover, use:
    // ```
    // RISC0_DEV_MODE=True cargo run -r
    // ```
    let prover = default_prover().unwrap();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove(env, XGBOOST_ELF).unwrap().receipt;

    // We return the inference value committed to the journal.
    receipt.journal.decode().unwrap()
}

#[cfg(test)]
mod test {
    #[test]
    fn basic() {
        const EXPECTED: f64 = 30.528042544062632;
        let result = super::predict();
        assert_eq!(result, EXPECTED);
    }
}
