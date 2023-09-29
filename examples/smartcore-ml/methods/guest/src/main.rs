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

#![no_main]

use risc0_zkvm::guest::env;
use smartcore::{
    linalg::basic::matrix::DenseMatrix, tree::decision_tree_classifier::DecisionTreeClassifier,
};

risc0_zkvm::guest::entry!(main);

pub fn main() {
    // Read the model from the host into a Forust-ML GradientBooster object. We
    // MUST explicitly declare the type in order for deserialization to be
    // successful.
    type Model = DecisionTreeClassifier<f64, u32, DenseMatrix<f64>, Vec<u32>>;
    let trained_model: Model = env::read();

    // Read the input data into a DenseMatrix.
    let x_data: DenseMatrix<f64> = env::read();

    // We call the predict() function on our trained model to perform inference.
    let y_hat = trained_model.predict(&x_data).unwrap();

    // This line is optional and can be commented out, but it's useful to see
    // the output of the computation before the proving step begins.
    println!("answer: {:?}", &y_hat);

    // This is also optional, though it's quite useful for benchmarking the
    // various operations in the guest code. env::get_cycle_count() can be
    // called anywhere in the guest, multiple times. So if we are interested in
    // knowing how many cycles the inference computation takes, we can calculate
    // total cycles before and after model.predict() and the difference between
    // the two values equals the total cycle count for that section of the guest
    // code.
    println!(
        "Total cycles for guest code execution: {}",
        env::get_cycle_count()
    );

    // We commit the output to the journal.
    env::commit(&y_hat);
}
