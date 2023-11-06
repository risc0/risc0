// Copyright 2023 RISC Zero, Inc.
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
use rmp_serde;
use serde_json;
use xgboost_methods::XGBOOST_ELF;

const JSON_MODEL: &str = include_str!("../res/trained_model.json");

fn main() {
    let answer = predict();
    println!("Prediction from the trained XGBoost model is: {}", &answer);
}

fn predict() -> f32 {
    // We import the trained model
    let model: GradientBooster = serde_json::from_str(JSON_MODEL).unwrap();
    let rmp_model = rmp_serde::to_vec(&model).unwrap();
    let model_length = rmp_model.len();
    println!("rmp length: {}", &model_length);

    // We define an input value for the model (inputs are block number and numbe of transaction in that block.  Note we modify the block number to a f64 value).
    let data: Vec<f64> = vec![18511304.0, 2.1170];

    // We transfer the model and input data over to the guest
    let env = ExecutorEnv::builder()
        .write(&data)
        .unwrap()
        .write(&model_length)
        .unwrap()
        .write_slice(&rmp_model)
        .build()
        .unwrap();

    // Obtain the default prover.
    // To bypass the prover, use:
    // ```
    // RISC0_DEV_MODE=True cargo run -r
    // ```
    let prover = default_prover();

    // Produce a receipt by proving the specified ELF binary.
    let receipt = prover.prove_elf(env, XGBOOST_ELF).unwrap();

    println!("we verified the proof!");

    // We return the inference value committed the journal
    receipt.journal.decode().unwrap()
}

#[cfg(test)]
mod test {
    use forust_ml::GradientBooster;
    use methods::XGBOOST_ELF;
    use risc0_zkvm::{default_executor, ExecutorEnv};
    #[test]
    fn basic() {
        const EXPECTED: f32 = 32.80219;
        let result = super::predict();
        assert_eq!(result, EXPECTED);
    }
}
