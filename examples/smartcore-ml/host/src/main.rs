use methods::{ML_TEMPLATE_ELF};
use risc0_zkvm::{default_prover, ExecutorEnv};
use risc0_zkvm::serde::{to_vec, from_slice};

use std::fs::File;
use std::io::{Read};
use serde_json;

// The serialized trained model and input data are contained in files with the corresponding paths listed below.  
// Alternatively, the model can be trained in the host and/or data can be manually inputted as a smartcore DenseMatrix.  If this
// approach is desired, be sure to import the corresponding SmartCore modules and serialize the model and data to byte arrays before 
// transfer to the guest.  
const JSON_PATH_MODEL: &str = "./res/ml-model/tree_model_bytes.json";
const JSON_PATH_DATA: &str = "./res/input-data/tree_model_data_bytes.json";

// Helper function to import JSON files
fn import_json(json: &str) -> String {
    let mut data = String::new();
    let mut f1 = File::open(json).expect("unable to open file");
    f1.read_to_string(&mut data).expect("Unable to read string");
    data
}

fn main() {
    // Import the model and input data. 
    let model = import_json(JSON_PATH_MODEL);
    let x_data = import_json(JSON_PATH_DATA);

    // Convert the model and input data from string format into byte arrays.
    let model_rmp: Vec<u8> = serde_json::from_str(&model).unwrap();
    let data_rmp: Vec<u8> = serde_json::from_str(&x_data).unwrap();

    // In order for the byte arrays to be transmitted to the guest, we need to construct buffers that the byte arrays can be read into. 
    // So we must construct buffers with the correct length for both the model and data byte arrays. Note:  len() returns a usize so no casting is necessary here.
    let model_length = model_rmp.len();
    let data_length = data_rmp.len();
    
    // We construct an executor environment and add the length data along with both byte arrays.
    let env = ExecutorEnv::builder().add_input(&to_vec(&model_length).unwrap()).add_input(&to_vec(&data_length).unwrap()).add_input(&model_rmp).add_input(&data_rmp).build().unwrap();
    
    // Obtain the default prover.  Note that for development purposes we do not need to run the prover.  To bypass the prover, use DEV_MODE = TRUE cargo run -r.
    let prover = default_prover();

    // This initiates a session, runs the STARK prover on the resulting exection trace, and produces a receipt.
    let receipt = prover.prove_elf(env, ML_TEMPLATE_ELF).unwrap();

    // We read the result that the guest code committed to the journal.  The receipt can also be serialized and sent to a verifier.
    let result: Vec<u32> = from_slice(&receipt.journal).unwrap();

    println!("Prediction sent to the host is: {:?}", &result);
}