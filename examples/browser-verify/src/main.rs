use borsh::to_vec;
use guest::FIBONACCI_ELF;
use risc0_zkvm::{compute_image_id, default_prover, ExecutorEnv, ProverOpts, VerifierContext};
use std::fs::{create_dir_all, File};
use std::io::Write;

fn main() {
    // Initialize tracing. In order to view logs, run `RUST_LOG=info cargo run`
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::filter::EnvFilter::from_default_env())
        .init();

    let input: u32 = 1000000;
    let env = ExecutorEnv::builder()
        .write(&input)
        .unwrap()
        .build()
        .unwrap();

    let receipt = default_prover()
        .prove_with_ctx(
            env,
            &VerifierContext::default(),
            FIBONACCI_ELF,
            &ProverOpts::succinct(),
        )
        .expect("Proving failed")
        .receipt;

    let output: u32 = receipt.journal.decode().unwrap();
    println!("Fibonacci({}) has {} digits", input, output);

    // serialize the receipt into bytes
    let receipt_bytes = to_vec(&receipt).expect("Serialization failed");

    // compute the image ID
    let image_id_digest = compute_image_id(FIBONACCI_ELF).expect("Compute Image ID failed");
    let image_id_bytes = image_id_digest.as_bytes();

    // make sure data dir exists
    create_dir_all("../../web/public/proof_data/").expect("Couldn't create data dir in web app");

    // save imageID bytes + receipt bytes to file
    let mut receipt_file = File::create("../../../web/public/proof_data/receipt.bin")
        .expect("Couldn't create receipt.bin");
    receipt_file
        .write_all(&receipt_bytes)
        .expect("Couldn't write receipt data to receipt.bin");

    let mut image_id_file = File::create("../../web/public/proof_data/image_id.bin")
        .expect("Couldn't create image_id.bin");
    image_id_file
        .write_all(&image_id_bytes)
        .expect("Couldn't write image ID to image_id.bin")
}
