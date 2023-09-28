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

use smartcore::linalg::basic::matrix::DenseMatrix;
use smartcore::tree::decision_tree_classifier::*;
use smartcore::readers;

use std::fs::File;
use std::io::{Write, Error};
use polars::prelude::*;
use serde_json;
use rmp_serde;

fn main() -> Result<(), Error> {
    
    // This code below is adapted from the Jupyter Notebook.
    // We import the input data from a CSV file.
    let input = readers::csv::matrix_from_csv_source::<f64, Vec<_>, DenseMatrix<_>>(
        File::open("./csv-files/iris_input_data.csv").unwrap(),
        readers::csv::CSVDefinition::default()
    ).unwrap();

    // We import the target classes from a separate CSV file and convert it to a Vec<u32>.
    let filepath_iris_classes = "./csv-files/iris_classes.csv";
    let df_classes = CsvReader::from_path(filepath_iris_classes).unwrap().finish().unwrap();
    let column_series: Series = df_classes.column("variety").unwrap().clone();
    let as_vec: Vec<i64> = column_series.i64().unwrap().into_no_null_iter().collect();
    let y_u32s: Vec<u32> = as_vec.into_iter().map(|x| x as u32).collect();

    // We can now train the classifier using the input data and the target classes.
    let model = DecisionTreeClassifier::fit(&input, &y_u32s, Default::default()).unwrap();

    let model_bytes = rmp_serde::to_vec(&model).unwrap();
    let data_bytes = rmp_serde::to_vec(&input).unwrap();

    // We serialize the model and input data byte arrays for export as JSON files.
    // Note:  Custom inputs can be formatted here or in the host code.
    let model_json = serde_json::to_string(&model_bytes)?;
    let x_json = serde_json::to_string(&data_bytes)?;

    // We export the model to the res/ml-model directory.
    let mut f = File::create("../res/ml-model/tree_model_bytes.json").expect("unable to create file");
    f.write_all(model_json.as_bytes())?;

    // We export the model to the res/ml-data directory.
    let mut f1 = File::create("../res/input-data/tree_model_data_bytes.json").expect("unable to create file");
    f1.write_all(x_json.as_bytes())?;

    Ok(())
}