// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use forust_ml::{GradientBooster, Matrix};
use risc0_zkvm::guest::env;
use rmp_serde;

fn main() {
    // read the input data
    let input: Vec<f64> = env::read();

    // We read in the model struct
    let model_bytes: Vec<u8> = env::read();

    // We deserialize the byte array into the trained model.
    let xgboost_model: GradientBooster = rmp_serde::from_slice(&model_bytes).unwrap();

    // In order for the trained model to make a prediction using the input data, the input data must be formatted as a forust_ml::Matrix type.
    // Note:  We cannot send the data from the host to the guest as a Matrix struct because the forust-ml crate does not enable serialization
    // for Matrix objects.

    // To construct a Matrix object, we need three inputs:
    // The first input is the raw input data.
    // The second value is the number of instances, which in this case is one.
    // The third value is the number of variables per instance, which in our case is two (block number and number of transactions in a block).
    // Note: You will need to adjust the second and third inputs depending on how many instances you pass the model and how many variables
    // comprise each instance.
    //*************************************************//
    // MODIFY THE MATRIX TO MATCH YOUR INPUT DATA HERE //
    //*************************************************//
    let matrix = Matrix::new(&input, 1, 2);

    // We call the predict() function on the trained XGBoost model to perform inference
    let answer: f64 = xgboost_model.predict(&matrix, true)[0];

    // write public output to the journal
    env::commit(&answer);

    // If you want to obtain total cycle count to benchmark performance, you can use the code below.
    println!("cycles: {}", env::cycle_count());
}
