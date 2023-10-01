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

use risc0_zkvm::{
    default_prover,
    serde::{from_slice, to_vec},
    ExecutorEnv,
};
use serde_json;
use smartcore::{
    linalg::basic::matrix::DenseMatrix, tree::decision_tree_classifier::DecisionTreeClassifier,
};
use smartcore_ml_methods::ML_TEMPLATE_ELF;

// The serialized trained model and input data are embedded from files
// corresponding paths listed below. Alternatively, the model can be trained in
// the host and/or data can be manually inputted as a smartcore DenseMatrix. If
// this approach is desired, be sure to import the corresponding SmartCore
// modules and serialize the model and data to byte arrays before transfer to
// the guest.
const JSON_MODEL: &str = include_str!("../res/ml-model/tree_model_bytes.json");
const JSON_DATA: &str = include_str!("../res/input-data/tree_model_data_bytes.json");

fn main() {
    let result = predict();
    println!("Prediction recorded in journal is: {:?}", &result);
}

fn predict() -> Vec<u32> {
    // Convert the model and input data from JSON into byte arrays.
    let model_bytes: Vec<u8> = serde_json::from_str(JSON_MODEL).unwrap();
    let data_bytes: Vec<u8> = serde_json::from_str(JSON_DATA).unwrap();

    // Deserialize the data from rmp into native rust types.
    type Model = DecisionTreeClassifier<f64, u32, DenseMatrix<f64>, Vec<u32>>;
    let model: Model =
        rmp_serde::from_slice(&model_bytes).expect("model failed to deserialize byte array");
    let data: DenseMatrix<f64> =
        rmp_serde::from_slice(&data_bytes).expect("data filed to deserialize byte array");

    let env = ExecutorEnv::builder()
        .add_input(&to_vec(&model).expect("model failed to serialize"))
        .add_input(&to_vec(&data).expect("data failed to serialize"))
        .build()
        .unwrap();

    // Obtain the default prover.
    // Note that for development purposes we do not need to run the prover. To
    // bypass the prover, use:
    // ```
    // RISC0_DEV_MODE=1 cargo run -r
    // ```
    let prover = default_prover();

    // This initiates a session, runs the STARK prover on the resulting exection
    // trace, and produces a receipt.
    let receipt = prover.prove_elf(env, ML_TEMPLATE_ELF).unwrap();

    // We read the result that the guest code committed to the journal. The
    // receipt can also be serialized and sent to a verifier.
    from_slice(&receipt.journal).unwrap()
}

#[cfg(test)]
mod test {
    use serde_json;
    use smartcore::{
        linalg::basic::matrix::DenseMatrix, svm::{Kernels, svc::{SVC, SVCParameters}},
    };
    #[test]
    fn basic() {
        const EXPECTED: &[u32] = &[
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
            2, 2, 2, 2, 2,
        ];
        let result = super::predict();
        assert_eq!(EXPECTED, result);
    }
    #[test]
    fn svc() {
        // Create sample x and y data to train a SVM classifier
        let x = DenseMatrix::from_2d_array(&[
            &[5.1, 3.5, 1.4, 0.2],
            &[4.9, 3.0, 1.4, 0.2],
            &[4.7, 3.2, 1.3, 0.2],
            &[4.6, 3.1, 1.5, 0.2],
            &[5.0, 3.6, 1.4, 0.2],
            &[5.4, 3.9, 1.7, 0.4],
            &[4.6, 3.4, 1.4, 0.3],
            &[5.0, 3.4, 1.5, 0.2],
            &[4.4, 2.9, 1.4, 0.2],
            &[4.9, 3.1, 1.5, 0.1],
            &[7.0, 3.2, 4.7, 1.4],
            &[6.4, 3.2, 4.5, 1.5],
            &[6.9, 3.1, 4.9, 1.5],
            &[5.5, 2.3, 4.0, 1.3],
            &[6.5, 2.8, 4.6, 1.5],
            &[5.7, 2.8, 4.5, 1.3],
            &[6.3, 3.3, 4.7, 1.6],
            &[4.9, 2.4, 3.3, 1.0],
            &[6.6, 2.9, 4.6, 1.3],
            &[5.2, 2.7, 3.9, 1.4],
            ]);

        let y: Vec<i32> = vec![
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
            ];
        
        //  We create the SVC params and train the SVC model.  These will NOT get serialized
        let knl = Kernels::linear();
        let params = &SVCParameters::default().with_c(200.0).with_kernel(knl);
        let svc = SVC::fit(&x, &y, params).unwrap();

        // Serialize the model to JSON
        let svc_serialized = serde_json::to_string(&svc).unwrap();

        // Deserialize the model.  The model must be mutable since we need to reinsert the missing parameters field
        let mut svc_deserialized: SVC<f32, i32, DenseMatrix<f32>, Vec<i32>> =  serde_json::from_str(&svc_serialized).expect("Could not parse json");
        
        // Test to make sure that parameters field is empty, as exptected.
        assert!(svc_deserialized.parameters.is_none());

        // Calling predict on svc_deserialized will result in an error due to the missing parameters field.
        // We need to recreate the same SVCParameters that we used to train the model
        let params_same = &SVCParameters::default().with_c(200.0).with_kernel(Kernels::linear());

        // Now we can update the model with params_same.  The fork changes the visbility of the parameters field of the SVM model struct to public to allow for this reinsertion
        svc_deserialized.parameters = Some(params_same);

        // Calling predict on svc_deserialized will now work.
        let y_hats: Vec<f32> = svc_deserialized.predict(&x).unwrap();
        
        let y_expected: Vec<f32> = vec![
            -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
            ]; 

        assert_eq!(y_hats, y_expected);
    }
}