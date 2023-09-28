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
use smartcore::linalg::basic::matrix::DenseMatrix;
use smartcore::tree::decision_tree_classifier::*;
use rmp_serde::from_slice;


risc0_zkvm::guest::entry!(main);

pub fn main() {
    // Import the trained model and the input data.  First we read in the length of the model and data arrays.
    let model_length: usize = env::read();
    let data_length: usize = env::read();

    // Next, we construct buffers for the model and the input data using the corresponding lengths of their respective byte arrays.
    let mut model_bytes: Vec<u8> = vec![0;model_length];
    let mut data_bytes: Vec<u8> = vec![0;data_length];

   // The byte arrays are read in from the host
    env::read_slice(&mut model_bytes);
    env::read_slice(&mut data_bytes);
    
    // Deserialize the model bytes array into a Forust-ML GradientBooster object.  We MUST explicitly declare the type in order for deserialization to be successful.
    let trained_model: DecisionTreeClassifier<f64, u32, DenseMatrix<f64>, Vec<u32>>  = from_slice(&model_bytes).expect("Unable to deserialize byte array");

    // Deserialize the input data bytes array into a DenseMatrix.
    let x_data: DenseMatrix<f64> = from_slice(&data_bytes).expect("Unable to deserialize byte array");    

    // We call the predict() function on our trained model to perform inference.  
    let y_hat = trained_model.predict(&x_data).unwrap();

    //  This line is optional and can be commented out, but it's useful to see the output of the computation before the proving step begins.
    println!("answer: {:#?}", &y_hat);
    
    // This is also optional, though it' quite useful for benchmarking the various operations in the guest code.  
    // env::get_cycle_count() can be called anywhere in the guest, multiple times.  So if we are interested in knowing how many
    // cycles the inference computation takes, we can calculate total cycles before and after model.predict() and the difference between 
    // the two values equals the total cycle count for that section of the guest code.
    println!("Total cycles for guest code execution: {}", env::get_cycle_count());

    // We commit the output to the journal.
    env::commit(&y_hat);
}