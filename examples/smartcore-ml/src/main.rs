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

use risc0_zkvm::{default_prover, ExecutorEnv};
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
const MODEL_SERIALIZED: &[u8] = include_bytes!("../res/ml-model/tree_model_bytes.bin");
const DATA_SERIALIZED: &[u8] = include_bytes!("../res/input-data/tree_model_data_bytes.bin");

fn main() {
    let result = predict();
    println!("Prediction recorded in journal is: {:?}", &result);
}

fn predict() -> Vec<u32> {
    // We set a boolean to establish whether we are using a SVM model.  This will be
    // passed to the guest and is important for execution of the guest code.
    // SVM models require an extra step that is not required of other SmartCore
    // models.
    let is_svm: bool = false;

    // Deserialize the data from rmp into native rust types.
    type Model = DecisionTreeClassifier<f64, u32, DenseMatrix<f64>, Vec<u32>>;
    let model: Model =
        rmp_serde::from_slice(MODEL_SERIALIZED).expect("model failed to deserialize byte array");
    let data: DenseMatrix<f64> =
        rmp_serde::from_slice(DATA_SERIALIZED).expect("data filed to deserialize byte array");

    let env = ExecutorEnv::builder()
        .write(&is_svm)
        .expect("bool failed to serialize")
        .write(&model)
        .expect("model failed to serialize")
        .write(&data)
        .expect("data failed to serialize")
        .build()
        .unwrap();

    // Obtain the default prover.
    // Note that for development purposes we do not need to run the prover. To
    // bypass the prover, use:
    // ```
    // RISC0_DEV_MODE=1 cargo run -r
    // ```
    let prover = default_prover().unwrap();

    // This initiates a session, runs the STARK prover on the resulting execution
    // trace, and produces a receipt.
    let receipt = prover.prove(env, ML_TEMPLATE_ELF).unwrap().receipt;

    // We read the result that the guest code committed to the journal. The
    // receipt can also be serialized and sent to a verifier.
    receipt.journal.decode().unwrap()
}

#[cfg(test)]
mod test {
    use risc0_zkvm::{default_executor, ExecutorEnv};
    use smartcore::{
        linalg::basic::matrix::DenseMatrix,
        svm::{
            svc::{SVCParameters, SVC},
            Kernels,
        },
    };
    use smartcore_ml_methods::ML_TEMPLATE_ELF;
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
        // We set is_svm equal to true for a SVC model.
        let is_svm: bool = true;

        // Create sample x and y data to train a SVC.
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

        // We create the SVC params and train the SVC model.
        // The parameters will NOT get serialized due to a serde_skip command in the
        // source code for the SVC struct.
        let knl = Kernels::linear();
        let params = &SVCParameters::default().with_c(200.0).with_kernel(knl);
        let svc = SVC::fit(&x, &y, params).unwrap();

        // This simulates importing a serialized model.
        let svc_serialized = rmp_serde::to_vec(&svc).expect("failed to serialize");
        let svc_deserialized: SVC<f64, i32, DenseMatrix<f64>, Vec<i32>> =
            rmp_serde::from_slice(&svc_serialized).expect("unable to deserialize JSON");

        let env = ExecutorEnv::builder()
            .write(&is_svm)
            .expect("bool failed to serialize")
            .write(&svc_deserialized)
            .expect("model failed to serialize")
            .write(&x)
            .expect("data failed to serialize")
            .build()
            .unwrap();

        // We run the executor and bypass the prover.
        let exec = default_executor();
        let session = exec.execute(env, ML_TEMPLATE_ELF).unwrap();

        // We read the result committed to the journal by the guest code.
        let result: Vec<f64> = session.journal.decode().unwrap();

        let y_expected: Vec<f64> = vec![
            -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
            1.0, 1.0, 1.0, 1.0, 1.0,
        ];

        assert_eq!(result, y_expected);
    }
}
